#ifndef LEAKSD_HH
#define LEAKSD_HH

#include "runAction.hh"
#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4AnalysisManager.hh"
#include <array>
#include <vector>
#include "leakHit.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4TouchableHistory.hh"
#include "G4Run.hh"


class leakSD : public G4VSensitiveDetector
{
public:
    leakSD(const G4String& nombre, const G4String& NameHistCollection);
    ~leakSD();
    G4double fAbsTotalEnergyDeposited=0;
    void Initialize (G4HCofThisEvent *hce) override;
    void EndOfEvent (G4HCofThisEvent *hce) override ;
    G4bool ProcessHits(G4Step *aStep,G4TouchableHistory *hist) override;
private:
    //G4double ApplyEnergyResolution(G4double edep);
    
    
    MyleakHits *fHitsCollection=nullptr;
    G4int ID=0;
};



#endif