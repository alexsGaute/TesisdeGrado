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
    G4double time = aStep->GetTrack()->GetGlobalTime();
    const G4VTouchable *touchable = aStep->GetTrack()->GetTouchable();
    G4VPhysicalVolume *physvol = touchable->GetVolume();
    G4int copy = touchable->GetCopyNumber();
    G4int copyNo=copy%100;
    if(fEnergyDeposited==0||time>5.0) return false;
    
    
    G4int ID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID()+1;
    
    SciHit *hit = new SciHit();

    
    //G4StepPoint *prestepPoint = aStep->GetPreStepPoint();
   
   G4int trackID = aStep->GetTrack()->GetTrackID();
   G4String partName = aStep->GetTrack()->GetParticleDefinition()->GetParticleName();

    G4int ParticleId = aStep->GetTrack()->GetParticleDefinition()->GetParticleDefinitionID();
    G4int parentId = aStep->GetTrack()->GetParentID();
    //G4ThreeVector pos = prestepPoint->GetPosition();  
    
    //G4double energyRes=ApplyEnergyResolution(fEnergyDeposited);//esta energyRes es la energ\'ia con la resolucion aplicada
    
    G4int flayerNo=copy/100;
    
    //hit->SetEnergy(fEnergyDeposited);
    //hit->SetTime(aStep->GetPostStepPoint()->GetGlobalTime());
    //hit->SetPos(pos);
    hit->SetLayer(flayerNo);
    hit->SetCopy(copyNo);
    hit->SetTime(time);
    //hit->SetID(ID);
    fHitsCollection->insert(hit);
    /*G4cout<< "Track ID: "<<trackID<<", ParentID: "<<parentId<<", Particle Name: "<<partName<<", Global Time: "<<
  G4BestUnit(time,"Time")<<", el Layer es:  "<< flayerNo<<" el numero de la copia es: "<<copyNo<<G4endl;*/
    

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

