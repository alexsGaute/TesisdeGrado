#include "rootcreator.hh"

rootcreator::rootcreator()
{}

rootcreator::~rootcreator()
{}

void rootcreator::initializeRoot(G4int thread)
{
    ROOT::EnableThreadSafety();
   
    std::string G4output= "FTFP_BERT_EMZ-Opt1-12GeVPoint" +std::to_string(thread) + ".root";

    file=new TFile (G4output.c_str(),"RECREATE");
    if(file)
    {
    tree=new TTree("Sci","Sci");
    //tree1 = new TTree("Abs","Abs");
    tree->Branch("fEnergy",&fEnergy,"fEnergy/D");
    //tree->Branch("fTime",&fTime,"fEnergy/D");
    /*tree->Branch("fX",&fX,"fX/D");
    tree->Branch("fY",&fY,"fY/D");
    tree->Branch("fZ",&fZ,"fZ/D");*/
    tree->Branch("fLayer",&fLayer,"fLayer/I");
    tree->Branch("fCopy",&fCopy,"fCopy/I");
    tree->Branch("fID",&fID,"fID/I");
    tree->Branch("E0",&E0,"E0/I");
    /*tree1->Branch("fAbsEnergy",&fAbsEnergy,"fAbsEnergy/D");
    tree1->Branch("fAbsTime",&fAbsTime,"fAbsTime/D");
    tree1->Branch( "fAbsX",&fAbsX,"fAbsX/D");
    tree1->Branch("fAbsY",&fAbsY,"fAbsY/D");
    tree1->Branch("fAbsZ",&fAbsZ,"fAbsZ/D");
    tree1->Branch("fAbsLayer",&fAbsLayer,"fAbsLayer/I");
    tree1->Branch("fAbsID",&fAbsID,"fAbsID/I");
    tree1->Branch("E0_Abs",&E0_Abs,"E0_Abs/I");
    */
    }

}

void rootcreator::writteRoot(G4double GenEnergy, G4int GenLayer,G4int GenCopy,
                    G4int GenID, G4int GenE0)
{
    fEnergy=GenEnergy;
    fID=GenID;
    fLayer=GenLayer;
    fCopy=GenCopy;
    E0=GenE0;
     


    tree->Fill();

}
/*void rootcreator::writteRoot(G4double GenEnergy, G4double GenX,
                    G4double GenY, G4double GenZ,
                    G4int GenLayer, G4int GenCopy,
                    G4int GenID,G4int GenE0)
{
    fEnergy=GenEnergy;
    fX=GenX;
    fY=GenY;
    fZ=GenZ;
    fLayer=GenLayer;
    fCopy=GenCopy;
    fID=GenID;
    E0=GenE0;
     


    tree->Fill();

}*/
/*void rootcreator::writteAbsRoot(G4double GenEnergy, G4double GenX,
                    G4double GenY, G4double GenZ,
                    G4int GenLayer,
                    G4int GenID,G4double GenE0)
{
    fAbsEnergy=GenEnergy;
     //fAbsTime=;
     fAbsX=GenX;
     fAbsY=GenY;
     fAbsZ=GenZ;
     fAbsLayer=GenLayer;
     fAbsID=GenID;
    E0_Abs=GenE0;
     tree1->Fill();
}*/


void rootcreator::finishRoot()
{
    file->Write();

    file->Close();
}