#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Analysis/LoopInfo.h"
#include "fstream"
#include "ExprsToSample.hpp"

using namespace llvm;

namespace {
    struct SPSIR : public FunctionPass {
        static char ID;
        SPSIR() : FunctionPass(ID) {}

        /* Analysis pass main function */
        bool runOnFunction(Function &F) override {
            errs() << " /* Analyze function ";
            errs() << F.getName() << " : ";

			LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
			int loopCnt = 0;
			for (auto it = LI.begin(), eit = LI.end(); it != eit; ++it) {
				(*it)->dump();
				loopCnt += 1;

				Loop* curLoop = (*it);
				std::map<Instruction*, ExprNode*> exprsToSample = FindExprsToSample(curLoop);
				DumpExprsToSample(exprsToSample);
				for (auto expr_it = exprsToSample.begin(), expr_eit = exprsToSample.end(); expr_it != expr_eit; ++expr_it) {
					for (int i = 0; i < 10; i++) {
						errs() << sampleValueFromExpr((*expr_it).second) << " ";
					}
					errs() << "\n";
				}
			}
			errs() << " Num of Loops : " << loopCnt << "\n";

            return false;
        }

		void getAnalysisUsage(AnalysisUsage &AU) const override {
        	AU.setPreservesAll();
        	AU.addRequired<LoopInfoWrapperPass>();
        	return;
    	}
    };
}

char SPSIR::ID = 0;
static RegisterPass<SPSIR> X("spsir", "Static Parallel Sampling in IR level Pass",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder,
       legacy::PassManagerBase &PM) { PM.add(new SPSIR()); });

