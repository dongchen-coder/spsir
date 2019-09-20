#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
//#include "llvm/PassRegistry.h"
//#include "llvm/Support/CommandLine.h"


using namespace llvm;

//static cl::opt<bool>
//EnableSPSIR("enable-spsir", cl::Hidden,
//                   cl::desc("Enable SPS IR pass"),
//                   cl::init(false));

namespace {
    struct spsIR : public FunctionPass {
        static char ID;
        spsIR() : FunctionPass(ID) {}

        /* Analysis pass main function */
        virtual bool runOnFunction(Function &F) override {

            errs() << " /* Analyze function: ";
            errs() << F.getName() << " */ \n";

            return false;
        }

        //void getAnalysisUsage(AnalysisUsage &AU) const override {
        //    AU.setPreservesAll();
        //}
    };
}

char spsIR::ID = 0;
//static RegisterPass<spsIR> X("spsir", "Static Parallel Sampling IR-level Pass", false, false);

static void registerSpsIR(const PassManagerBuilder &, legacy::PassManagerBase &PM) {
// 	if (EnableSPSIR)
		PM.add(new spsIR());
}

static RegisterStandardPasses X(PassManagerBuilder::EP_EarlyAsPossible, registerSpsIR);
//static RegisterStandardPasses clangtoolLoader_O0(PassManagerBuilder::EP_EnabledOnOptLevel0, loadPass);



