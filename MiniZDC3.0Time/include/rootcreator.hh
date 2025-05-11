#ifndef ROOTCREATOR_HH
#define ROOTCREATOR_HH

#include "TFile.h"
#include "TTree.h"
#include "globals.hh"
#include "TROOT.h"
#include "TObject.h"
#include <string>

class rootcreator
{
    public:
    rootcreator();
    ~rootcreator();

    void initializeRoot(G4int thread);
    /*void writteRoot(G4double GenEnergy, G4double GenX,
                    G4double GenY, G4double GenZ,
                    G4int GenLayer, G4int GenCopy,
                    G4int GenID, G4int GenE0 );*/
    void writteRoot(G4double GenTime, G4int GenLayer, G4int GenID,
                     G4int GenE0 );
    
    void writteleakRoot(G4double Genlongitudinal, G4double Genalbedo, G4double Genlateral,
                    G4double GenE0);
    void finishRoot();
    private:
    G4double fEnergy=0.;
    G4double fTime=0.;

    G4double fX;
    G4double fY;
    G4double fZ;
    G4int fLayer=0;
    G4int fCopy=0;
    G4int fID=0;
    G4int E0=0;
    G4double longitudinal;
    G4double lateral;
    G4double albedo;
    G4int E_0leak;
    TFile *file=nullptr;
    TTree *tree=nullptr;
    TTree *tree1=nullptr;
    



};





#endif