#include "MyEventAction.hh"
#include "G4RunManager.hh"

MyEventAction::MyEventAction(rootcreator* createRoot1) : fRoot(createRoot1) , fHitsCollectionID1(-1)//, fHitsCollectionID2(-1)
{

}
MyEventAction::~MyEventAction()
{
    
}

void MyEventAction::BeginOfEventAction(const G4Event *event)
{
    
    
     
    if (fHitsCollectionID1==-1 )
    {
        fHitsCollectionID1=G4SDManager::GetSDMpointer()->GetCollectionID("SciHitsCollection");
        //fHitsCollectionID2 = G4SDManager::GetSDMpointer()->GetCollectionID("AbsHitCollection");
    }
    
}

void MyEventAction::EndOfEventAction(const G4Event *event)
{
   
    primaryvertex = event->GetPrimaryVertex();

    if(primaryvertex)
    {
        primaryparticle = primaryvertex->GetPrimary();
    }
    G4double K0 = primaryparticle->GetKineticEnergy();
    
    //G4double energy = fPrimaryEnergy->GetPrimaryEnergy();
    auto hc1 = static_cast<MyHitsSci*>(event->GetHCofThisEvent()->GetHC(fHitsCollectionID1));
    //auto hc2 =static_cast<MyHitsAbs*>(event->GetHCofThisEvent()->GetHC(fHitsCollectionID2));
    if(!hc1) return;
    //if(!hc2) return;
    G4int runID = G4RunManager::GetRunManager()->GetCurrentRun()->GetRunID()+1;


    G4int nSciHits = hc1->entries();
    //G4int nAbsHits = hc2->entries();
    G4int nEvent = event->GetEventID()+1;
    
    G4cout<< G4endl
       << "-------->In event "<<nEvent<<" La energia es: "<< G4BestUnit(K0,"Energy") <<" they are " << nSciHits<< " scintilleator hits " <<G4endl; //and "<< nAbsHits<<" absorber hits"<< G4endl;

    for (G4int i=0;i<nSciHits;i++)
    {
        SciHit *hitSci= (*hc1)[i];
        //hitSci->Draw();
        //hitSci->Print();


        if(fRoot){
        fRoot->writteRoot(hitSci->GetEnergy(),hitSci->GetLayer(),hitSci->GetCopy(),hitSci->GetID(),K0);
        }
        /*analysismanager->FillNtupleIColumn(0,hit->GetLayer());
        analysismanager->FillNtupleIColumn(1,hit->GetCopy());
        analysismanager->FillNtupleDColumn(2,hit->GetPos().x());
        analysismanager->FillNtupleDColumn(3,hit->GetPos().y());
        analysismanager->FillNtupleDColumn(4,hit->GetPos().z());
        analysismanager->FillNtupleDColumn(5,hit->GetEnergy());
        analysismanager->FillNtupleIColumn(6,hit->GetID());
        //analysismanager->FillNtupleDColumn(6,hit->GetTime());
        analysismanager->AddNtupleRow();*/

    }
   /*for (G4int j = 0 ; j<nAbsHits;j++)
    {
        AbsHit *hitAbs = (*hc2)[j];
        //hitAbs->Print();
        //hitAbs->Draw();
        fRoot->writteAbsRoot(hitAbs->GetEnergy(),hitAbs->GetPos().x(),hitAbs->GetPos().y(),hitAbs->GetPos().z(),hitAbs->GetLayer(),hitAbs->GetID(),K0);
    }*/
}