#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"
#include "G4Threading.hh"
#include "SciSD.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "rootcreator.hh"
#include "SciHit.hh"
#include "TFile.h"
#include "TTree.h"

class MyRunAction : public G4UserRunAction
{
    public:
    MyRunAction(rootcreator *);
    ~MyRunAction();
    
    virtual void BeginOfRunAction(const G4Run *run);
    virtual void EndOfRunAction(const G4Run *run);
    private:

    rootcreator *fRoot = nullptr;
    


};




#endif