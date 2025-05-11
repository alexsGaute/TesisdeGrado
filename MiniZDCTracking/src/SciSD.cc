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
//
//--------------------------------------------------------------------------------------------------------------
//
//              EN ESTE PROCESS HIT ES DONDE SE CLASIFICA QUE PARTÍCULA ES LA QUE DEPOSITA
//              Y SE GUARDA EN EL ROOT ENERGÍA DEPOSITADA Y EL TIPO DE PARTÍCULA, 
//              PARA LA EM EL TYPE ES -1; PARA LA HAD ES 1. EN LA CLASE DE HITS HAY QUE DEFINIR 
//              UN NUEVO MÉTODO SetType(G4double) QUE SIGUE LA MISMA LÓGICA QUE SetEnergy(G4double)
//              EL RESTO ES MÁS DE LO MISMO.
//
//-------------------------------------------------------------------------------------------------------------
G4bool SciSD::ProcessHits(G4Step *aStep, G4TouchableHistory *hist)
{
    G4double fEnergyDeposited = aStep->GetTotalEnergyDeposit(); //se accede a la energía depositada del hit
    //Para analizar solamente la electromagnetica:
    G4String particle = aStep->GetTrack()->GetParticleDefinition()->GetParticleName(); //con esto se pide el nombre de la partícula que provoca el hit
    G4String Partdef = aStep->GetTrack()->GetParticleDefinition()->GetParticleType(); //se pide el tipo de partícula (lepton, mesón o barión)
    //if(fEnergyDeposited==0 ) return false;
    if (fEnergyDeposited!=0) //Si la energía depositada es diferente de 0 entra en este if
    {
        if(Partdef == "lepton" || particle =="gamma") //Si la partícula es un leptón o un gamma entra en este if y se guarda el type -1 junto con el resto de las cosas
        {
            //G4int ParticleId = aStep->GetTrack()->GetParticleDefinition()->GetParticleDefinitionID();
            //G4int parentId = aStep->GetTrack()->GetParentID();
            //G4int trackID = aStep->GetTrack()->GetTrackID();
            G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID()+1; //accede al evento actual, eso dice que número es el neutrón de 1-100000, esto es importante para marcar los eventos

            G4int runID = G4RunManager::GetRunManager()->GetCurrentRun()->GetRunID()+1; //Esto no es necesario 
            G4int ID = eventID;
            //G4cout<<"el ID del evento es: "<< eventID<< " y el del Run es "<<runID<<G4endl;
            // G4AnalysisManager *man1 = G4AnalysisManager::Instance();
            SciHit *hit = new SciHit(); //inicia la colección de hits

    
            G4StepPoint *prestepPoint = aStep->GetPreStepPoint(); //esto no es necesario para el espectro
   
    
            //G4ThreeVector pos = prestepPoint->GetPosition();  
            const G4VTouchable *touchable = prestepPoint->GetTouchable(); //no es necesario para el espectro
            G4VPhysicalVolume *physvol = touchable->GetVolume(); //no es necesario para el espectro
            //G4double energyRes=ApplyEnergyResolution(fEnergyDeposited);//esta energyRes es la energ\'ia con la resolucion aplicada
            G4int copy = touchable->GetCopyNumber(); //no es necesario para el espectro
            G4int flayerNo=copy/100; //no es necesario para el espectro
            G4int copyNo=copy%100; //no es necesario para el espectro
            hit->SetEnergy(fEnergyDeposited); //Aquí se guarda en la colección la energía del hit
            //hit->SetTime(aStep->GetPostStepPoint()->GetGlobalTime());
            //hit->SetPos(pos);
            hit->SetLayer(flayerNo); //no es necesario para el espectro
            hit->SetCopy(copyNo); //no es necesario para el espectro
            hit->SetID(ID); //Aquí se guarda el ID del neutrón para poder separar cada neutrón del evento 
            hit ->SetType(-1); //Aquí se defino el tipo 
            fHitsCollection->insert(hit); //Aquí se inserta el hit a la colección
            //G4cout<< "Track ID: "<<trackID<<", ParentID: "<<parentId<<", Particle Name: "<<particle<<G4endl;    //
        }
        else if(Partdef == "baryon" || Partdef == "meson" ) //Si no entró en el anterior evalúa si es un hadrón y realiza exactamente lo mismo que lo anterior
        {

            G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID()+1;

            G4int runID = G4RunManager::GetRunManager()->GetCurrentRun()->GetRunID()+1;
            G4int ID = eventID;
            //G4cout<<"el ID del evento es: "<< eventID<< " y el del Run es "<<runID<<G4endl;
            // G4AnalysisManager *man1 = G4AnalysisManager::Instance();
            SciHit *hit = new SciHit();

    
            G4StepPoint *prestepPoint = aStep->GetPreStepPoint();
   
    
            //G4ThreeVector pos = prestepPoint->GetPosition();  
            const G4VTouchable *touchable = prestepPoint->GetTouchable();
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
            hit ->SetType(1);
            fHitsCollection->insert(hit);
        }
    }
    else {return false;}//Aquí si la energía es = 0 return (false) y sale del process hit
    
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

