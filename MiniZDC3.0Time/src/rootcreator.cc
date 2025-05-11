#include "rootcreator.hh"

rootcreator::rootcreator()
{}

rootcreator::~rootcreator()
{}

void rootcreator::initializeRoot(G4int thread)
{
    ROOT::EnableThreadSafety();
   
    std::string G4output= "Analisis_del_tiempo2test" +std::to_string(thread) + ".root";

    file=new TFile (G4output.c_str(),"RECREATE");
    if(file)
    {
    tree=new TTree("Sci","Sci");
    tree1 = new TTree("leak","leak");
    //tree->Branch("fEnergy",&fEnergy,"fEnergy/D");
    tree->Branch("fTime",&fTime,"fTime/D");
    //tree->Branch("fX",&fX,"fX/D");
    /*tree->Branch("fY",&fY,"fY/D");
    tree->Branch("fZ",&fZ,"fZ/D");
    
    tree->Branch("fCopy",&fCopy,"fCopy/I");*/
    tree->Branch("fLayer",&fLayer,"fLayer/I");
    tree->Branch("fID",&fID,"fID/I");
    tree->Branch("E0",&E0,"E0/I");

    tree1->Branch("longitudinal",&longitudinal,"longitudinal/D");
    tree1->Branch("albedo",&albedo,"albedo/D");
    tree1->Branch("lateral",&lateral,"lateral/D");
    tree1->Branch("E_0leak",&E_0leak,"E_0leak/I");
    }

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
void rootcreator::writteRoot(G4double GenTime,G4int GenLayer,G4int GenID,
                    G4int GenE0)
{
    fTime=GenTime;
    fLayer = GenLayer;
    fID = GenID;
    E0=GenE0;
     


    tree->Fill();

}
void rootcreator::writteleakRoot(G4double Genlongitudinal, G4double Genalbedo, G4double Genlateral,
                    G4double GenE0)
{
    longitudinal=Genlongitudinal;
    albedo=Genalbedo;
    lateral = Genlateral;
    
     
    E_0leak=GenE0;
     tree1->Fill();
}


void rootcreator::finishRoot()
{
    file->Write();

    file->Close();
}