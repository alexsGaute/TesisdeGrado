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
    /*void writteAbsRoot(G4double GenEnergy, G4double GenX,
                    G4double GenY, G4double GenZ,
                    G4int GenLayer,
                    G4int GenID,G4double GenE0);*/
    void writteRoot(G4double GenEnergy, G4int GenCopy, G4int GenLayer,
                    G4int GenID,G4int GenE0, G4int GenType);
    
    void writteTracking(G4double GenX,
                    G4double GenY, G4double GenZ, G4int Gentype,G4int GenE0);
    void writteCount(G4int GenEMcount,G4int GenHADcount,G4int GenE0);
    void finishRoot();
    private:
    G4int type; //-1 EM, 1 HAD
    G4double fEnergy=0.;
    //G4double fTime=0.;
    G4double fX;
    G4double fY;
    G4double fZ;
    G4int fLayer=0;
    G4int fCopy=0;
    G4int fID=0;
    G4int E0=0;
    G4int HADTot;
    G4int EMTot;
    /*G4int E0_Abs=0;
    G4double fAbsEnergy=0.;
    G4double fAbsTime=0.;
    G4double fAbsX;
    G4double fAbsY;
    G4double fAbsZ;
    G4int fAbsLayer=0;
    G4int fAbsID=0;*/
    TFile *file=nullptr;
    TTree *tree=nullptr;
    TTree *tracking = nullptr;
    TTree *count = nullptr;
    //TTree *tree1=nullptr;
    



};





#endif