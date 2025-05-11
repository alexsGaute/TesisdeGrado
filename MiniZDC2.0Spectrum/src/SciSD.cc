#include "SciSD.hh"

SciSD::SciSD(const G4String& nombre, const G4String& NameHistCollection) : G4VSensitiveDetector(nombre)
{
    collectionName.insert(NameHistCollection);
    
}

SciSD::~SciSD()
{}
/*G4double SciSD::ApplyEnergyResolution(G4double edep)
{
    return 0.05*edep;
}*/
void SciSD::Initialize(G4HCofThisEvent *hce)
{
    //Crea la coleccion de hits
    fHitsCollection=new MyHitsSci(SensitiveDetectorName, collectionName[0]);

    //Aniade la coleccion de hits al evento
    G4int hcID= G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    hce->AddHitsCollection(hcID,fHitsCollection);
    //fHitsCollection->insert(new SciHit());
}
G4bool SciSD::ProcessHits(G4Step *aStep, G4TouchableHistory *hist)
{
    G4double fEnergyDeposited = aStep->GetTotalEnergyDeposit();
    if(fEnergyDeposited==0) return false;
    
    
    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID()+1;
    G4int runID = G4RunManager::GetRunManager()->GetCurrentRun()->GetRunID()+1;
    G4int ID = eventID;
    //G4cout<<"el ID del evento es: "<< eventID<< " y el del Run es "<<runID<<G4endl;
   // G4AnalysisManager *man1 = G4AnalysisManager::Instance();
    SciHit *hit = new SciHit();

    
    G4StepPoint *prestepPoint = aStep->GetPreStepPoint();
   
    
    //G4ThreeVector pos = prestepPoint->GetPosition();  
    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4VPhysicalVolume *physvol = touchable->GetVolume();
    //G4double energyRes=ApplyEnergyResolution(fEnergyDeposited);//esta energyRes es la energ\'ia con la resolucion aplicada
    G4int copy = touchable->GetCopyNumber();
    G4int flayerNo=copy/100;
    G4int copyNo=copy%100;
    hit->SetEnergy(fEnergyDeposited);
    //hit->SetTime(aStep->GetPostStepPoint()->GetGlobalTime());
    //hit->SetPos(pos);
    hit->SetLayer(flayerNo);
    hit->SetCopy(copyNo);
    hit->SetID(ID);
    fHitsCollection->insert(hit);
    return true;
}
void SciSD::EndOfEvent(G4HCofThisEvent *)
{
  /* G4int nHits = fHitsCollection->entries();
     G4AnalysisManager *analysismanager = G4AnalysisManager::Instance();
   G4cout
       << G4endl
       << "-------->Hits Collection: in this event they are " << nHits
       << G4endl;
   for (G4int i =0; i<nHits;i++)
   {
   (*fHitsCollection)[i]->Print();
       analysismanager->FillNtupleIColumn(0,(*fHitsCollection)[i]->GetLayer());
        analysismanager->FillNtupleIColumn(1,(*fHitsCollection)[i]->GetCopy());
        analysismanager->FillNtupleDColumn(2,(*fHitsCollection)[i]->GetPos().x());
        analysismanager->FillNtupleDColumn(3,(*fHitsCollection)[i]->GetPos().y());
        analysismanager->FillNtupleDColumn(4,(*fHitsCollection)[i]->GetPos().z());
        analysismanager->FillNtupleDColumn(5,(*fHitsCollection)[i]->GetEnergy());
        //analysismanager->FillNtupleDColumn(6,(*fHitsCollection)[i]->GetTime());
        analysismanager->AddNtupleRow();

   }*/
}

