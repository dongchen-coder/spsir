#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Instructions.h"
#include <assert.h> 
#include <map>
#include <iostream>
#include <string>

using namespace llvm;

struct ExprNode {
	unsigned opCode;
	int64_t val;
	std::string varName;
	ExprNode *left;
	ExprNode *right;
	int64_t leftVal;
	int64_t rightVal;
	ExprNode(unsigned x = -1) : opCode(x), left(NULL), right(NULL) {} 
};

enum OpCode {
	addOP = 13,
	mulOP = 17,
	allocaOP = 31,
	loadOP = 32, 
	getElementPtrOP = 34,
	sextOP = 40
};

ExprNode* ConstructExprTree(Instruction* pInst) {
	
	if (pInst == NULL) {
		return NULL;
	}

	pInst->dump();
	std::cout << pInst->getOpcode() << std::endl;
	
	ExprNode *node = new ExprNode(pInst->getOpcode());
	if (pInst->isCast()) {
		node->left = ConstructExprTree(dyn_cast<Instruction>(pInst->getOperand(0)));
		return node;
	} 
	else if (isa<GetElementPtrInst>(pInst)) {
		assert(pInst->getNumOperands() > 1);
		if (pInst->getNumOperands() == 3) {
			Instruction *baseInst = dyn_cast<Instruction>(pInst->getOperand(1));
        	Instruction *idxInst = dyn_cast<Instruction>(pInst->getOperand(2));
			node->left = ConstructExprTree(baseInst);
        	node->right = ConstructExprTree(idxInst);
		} else {
			Instruction *idxInst = dyn_cast<Instruction>(pInst->getOperand(1));
			node->left = ConstructExprTree(idxInst);
		}
		return node;
	} 
	else if (isa<Argument>(pInst)) {
		Argument *argValue = dyn_cast<Argument>(pInst);
		node->varName = argValue->getName().str();
		return node;
	}
	else if (isa<BinaryOperator>(pInst)) {
		BinaryOperator *boInst = dyn_cast<BinaryOperator>(pInst);
		if (isa<Instruction>(boInst->getOperand(0))) {
			node->left = ConstructExprTree(dyn_cast<Instruction>(boInst->getOperand(0)));
		} else if (isa<Constant>(boInst->getOperand(0))) {
			Constant *constValue = dyn_cast<Constant>(boInst->getOperand(0));
			node->leftVal = constValue->getUniqueInteger().getLimitedValue();
		}
		if (isa<Instruction>(boInst->getOperand(1))) {
			node->right = ConstructExprTree(dyn_cast<Instruction>(boInst->getOperand(1)));
		} else if (isa<Constant>(boInst->getOperand(1))) {
            Constant *constValue = dyn_cast<Constant>(boInst->getOperand(1));
            node->rightVal = constValue->getUniqueInteger().getLimitedValue();
        }
		return node;
	}
	else if (isa<LoadInst>(pInst)) {
		LoadInst *ldInst = dyn_cast<LoadInst>(pInst);
		node->varName = ldInst->getOperand(0)->getName();	
		node->left = ConstructExprTree(dyn_cast<Instruction>(pInst->getOperand(0)));
		return node;
	} 

	return NULL;
}


std::map<Instruction*, ExprNode*> FindExprsToSample(Loop* curLoop) {
	std::map<Instruction*, ExprNode*> exprsToSample;
	for (auto BB_iter = curLoop->getBlocks().begin(), BB_end = curLoop->getBlocks().end(); BB_iter != BB_end; ++BB_iter) {
    	for (auto I_iter = (*BB_iter)->begin(), I_end = (*BB_iter)->end(); I_iter != I_end; ++I_iter) {
			Instruction* pInst = dyn_cast<Instruction>(I_iter);
			if (isa<LoadInst>(pInst)) {
				LoadInst *ld = dyn_cast<LoadInst>(pInst);
				if (isa<GetElementPtrInst>(ld->getOperand(0))) {
					Instruction *gep = dyn_cast<Instruction>(ld->getOperand(0));
					exprsToSample[pInst] = ConstructExprTree(gep);
				}
			}
		}
	}
	return exprsToSample;
}

int64_t sampleValueFromExpr(ExprNode* expr) {
	int64_t result = 0;
	switch (expr->opCode) {
        case(OpCode::sextOP):
            result = sampleValueFromExpr(expr->left);
            break;
        case(OpCode::loadOP):
            result = rand() % 1024;
            break;
        case(OpCode::getElementPtrOP):
			result = (expr->right == NULL) ? sampleValueFromExpr(expr->left)  : sampleValueFromExpr(expr->left) + sampleValueFromExpr(expr->right);
			break;
        case(OpCode::mulOP):
            result = ((expr->left == NULL) ?  expr->leftVal : sampleValueFromExpr(expr->left)) * ((expr->right == NULL) ?  expr->rightVal : sampleValueFromExpr(expr->right)) ;
            break;
        case(OpCode::addOP):
            result = ((expr->left == NULL) ?  expr->leftVal : sampleValueFromExpr(expr->left)) + ((expr->right == NULL) ?  expr->rightVal : sampleValueFromExpr(expr->right)) ;
			break;
        default: result = 0;
    }
	return result;
}



std::string DumpExpr(ExprNode* expr) {
	if (expr == NULL) {
		return "";
	}

	std::string exprStr = "";
	switch (expr->opCode) {
		case(OpCode::sextOP): 
			exprStr = "";
			break;
		case(OpCode::allocaOP): 
			exprStr = "";
			break;
    	case(OpCode::loadOP): 
			exprStr = expr->varName;
			break;
    	case(OpCode::getElementPtrOP): 
			exprStr = " Access " + expr->varName;
			break;
		case(OpCode::mulOP):
			exprStr = " * ";
			break;
		case(OpCode::addOP):
			exprStr = " + ";
            break;
		default: exprStr = "";
	}
	
	std::string left = "";
    std::string right = "";
	if (expr->left == NULL && (expr->opCode == OpCode::mulOP || expr->opCode == OpCode::addOP)) {
		left = std::to_string(expr->leftVal);
	} else {
		left = DumpExpr(expr->left);
	}
	if (expr->right == NULL && (expr->opCode == OpCode::mulOP || expr->opCode == OpCode::addOP)) {
		right = std::to_string(expr->rightVal);
	} else {
		right = DumpExpr(expr->right);
	}

	return "(" + exprStr + " " + left + " " + right + ")";
}

void DumpExprsToSample(std::map<Instruction*, ExprNode*> exprsToSample) {
 	for (auto it = exprsToSample.begin(), eit = exprsToSample.end(); it != eit; ++it) {
		std::cout << it->first << " " << DumpExpr(it->second) << std::endl;
	}
	return;
}

