#ifndef TRACKINACTION_HH
#define TRACKINACTION_HH

#include "G4UserTrackingAction.hh"
#include "globals.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "rootcreator.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4Allocator.hh"
#include "G4Threading.hh"
#include "MyEventAction.hh"


class TrackingAction : public G4UserTrackingAction
{
public:

    TrackingAction(rootcreator *,MyEventAction*);
    ~TrackingAction() ;

    void  PreUserTrackingAction(const G4Track* track) override;   
    void PostUserTrackingAction(const G4Track* ) override;


private:

G4double *counter;
G4PrimaryParticle *primaryparticle = nullptr;
rootcreator *root = nullptr;
MyEventAction *fEventaction = nullptr;
G4double K0;
G4int TrackID=-1;
G4int ParentID = -1;
const G4ParticleDefinition *Partdef = nullptr ;
G4ThreeVector cascadePos;
G4int type =0;

    



};



#endif