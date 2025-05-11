#ifndef MYEVENTACTION_HH
#define MYEVENTACTION_HH

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "runAction.hh"
#include "G4UserEventAction.hh"
#include "rootcreator.hh"
#include "TTree.h"
//#include "AbsHit.hh"
#include "SciHit.hh"
#include "leakHit.hh"

#include "generador.hh"
#include "globals.hh"
class MyEventAction : public G4UserEventAction
{
public:
    MyEventAction(rootcreator *);//, MyGenerator *);
    ~MyEventAction();
    virtual void BeginOfEventAction(const G4Event *event);
    virtual void EndOfEventAction(const G4Event *event);
private:
rootcreator *fRoot = nullptr;
G4int fHitsCollectionID1;
G4int fHitsCollectionID2;

G4PrimaryVertex *primaryvertex=nullptr;
G4PrimaryParticle *primaryparticle = nullptr;

G4double albedo;
G4double longitudinal;
G4double lateral;
//G4int fHitsCollectionID2;

};




#endif