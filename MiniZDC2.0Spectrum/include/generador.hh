#ifndef GENERADOR_HH
#define GENERADOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "TROOT.h"
#include "TObject.h"
#include "TFile.h" //aqui declaro las clases de root que necesito
#include "TTree.h"
#include "G4RandomTools.hh"
#include "CLHEP/Random/RandFlat.h"
/*#include "generadorMessenger.hh"
class generadorMessenger;*/
//#include "TChain.h"



class MyGenerator : public G4VUserPrimaryGeneratorAction
{
    public:
    MyGenerator();
    ~MyGenerator();

    virtual void GeneratePrimaries(G4Event*);
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
    //void SetPrimaryEnergy(G4double energy);
    //G4double GetPrimaryEnergy() const;

private:
//G4double fPrimaryEnergy = 1.0 ;
//G4UIcmdWithADoubleAndUnit *fSetEnergyCmd;
/*TFile* fRootFile; //puntero nulo hacia un  tfile
TTree* T; //puntero nulo hacia un ttree
    G4double px , py,pz,e , x, y, z; //variables donde guardamos la data
    G4int id, number_entries, number_particles; //guardamos el id, el numero de entrada y el numero de la particula*/
    G4ParticleGun *fParticleGun; //puntero hacia la variable particlegun
    //generadorMessenger *fMessenger;
};




#endif  
