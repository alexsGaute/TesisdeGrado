#include "MyEventAction.hh"
#include "G4RunManager.hh"
#include <vector>
#include <array>
using namespace std;

MyEventAction::MyEventAction(rootcreator* createRoot1) : fRoot(createRoot1) , fHitsCollectionID1(-1), fHitsCollectionID2(-1)
{
    
}
MyEventAction::~MyEventAction()
{
    
}

void MyEventAction::BeginOfEventAction(const G4Event *event)
{
    
    albedo=0;
    longitudinal=0;
    lateral=0;
     
    if (fHitsCollectionID1==-1 && fHitsCollectionID2)
    {
        fHitsCollectionID1=G4SDManager::GetSDMpointer()->GetCollectionID("SciHitsCollection");
        fHitsCollectionID2 = G4SDManager::GetSDMpointer()->GetCollectionID("LeakersCollections");
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
    auto hc2 =static_cast<MyleakHits*>(event->GetHCofThisEvent()->GetHC(fHitsCollectionID2));
    if(!hc1) return;
    if(!hc2) return;
    G4int runID = G4RunManager::GetRunManager()->GetCurrentRun()->GetRunID()+1;


    G4int nSciHits = hc1->entries();
    G4int nleakHits = hc2->entries();
    G4int nEvent = event->GetEventID()+1;
    array <vector <double>,7>time34;
    array <vector <double>,7>time22;
    array <vector <double>,7>time24;
    array <vector <double>,7>time43;
    
    array <vector <double>,7>energy34;
    array <vector <double>,7>energy22;
    array <vector <double>,7>energy24;
    array <vector <double>,7>energy43;
    
    G4cout<< G4endl
       << "-------->In event "<<nEvent<<" La energia es: "<< G4BestUnit(K0,"Energy") <<" they are " << nSciHits<< " scintilleator hits " <<G4endl; //and "<< nAbsHits<<" absorber hits"<< G4endl;
    
    for (G4int i=0;i<nSciHits;i++)
    {
        SciHit *hitSci= (*hc1)[i];
        //hitSci->Draw();
        //hitSci->Print();

        /*if(fRoot){
        fRoot->writteRoot(hitSci->GetTime(),hitSci->GetLayer(),K0);
        }*/
       if(hitSci->GetCopy()==34)
        {
            time34[hitSci->GetLayer()].push_back(hitSci->GetTime());
            //energy34[hitSci->GetLayer()].push_back(hitSci->GetEnergy());
        }
        else if(hitSci->GetCopy()==22)
        {
            time22[hitSci->GetLayer()].push_back(hitSci->GetTime());
            //energy22[hitSci->GetLayer()].push_back(hitSci->GetEnergy());
        }
        else if(hitSci->GetCopy()==33)
        {
            time24[hitSci->GetLayer()].push_back(hitSci->GetTime());
            //energy24[hitSci->GetLayer()].push_back(hitSci->GetEnergy());

        }
        else if(hitSci->GetCopy()==43)
        {
            time43[hitSci->GetLayer()].push_back(hitSci->GetTime());
            //energy43[hitSci->GetLayer()].push_back(hitSci->GetEnergy());
        }

    }
    /*for(G4int o =0;o<7;o++)
    {
        //G4cout<< "El tiempo para la placa " << o<<" y el centelleante 34 es: "<<G4endl;
        for (G4int y =0 ; y<time34[o].size(); y++)
        {
            G4cout<< time34[o].at(y)<<"      ";
        }
        //G4cout<< "El tiempo para la placa " << o<<" y el centelleante 22 es: "<<G4endl;
        for (G4int y =0 ; y<time22[o].size(); y++)
        {
            G4cout<< time22[o].at(y)<<"      ";
        }
        G4cout<<G4endl;
    }*/
    array <double,7> firstTime34;
    array <double,7> firstTime22;
    array <double,7> firstTime24;
    array <double,7> firstTime43;
    array <double,7> firstEnergy34;
    array <double,7> firstEnergy22;
    array <double,7> firstEnergy24;
    array <double,7> firstEnergy43;
    G4double Resultado;

    for (G4int k = 0; k <7;k++)
    {
        if(time34[k].size()>0&&time22[k].size()>0)
        {
            firstTime34[k] = time34[k].at(0);
            firstTime22[k] = time22[k].at(0);
            for (G4int l = 1 ;l<time34[k].size();l++)
            {
                if(firstTime34[k]>time34[k].at(l))
                {
                    firstTime34[k]=time34[k].at(l);
                    //firstEnergy34[k]=energy34[k].at(l);
                }
            }

            for (G4int l = 1 ;l<time22[k].size();l++)
            {
                if(firstTime22[k]>time22[k].at(l))
                {
                    firstTime22[k]=time22[k].at(l);
                    //firstEnergy22[k]=energy22[k].at(l);
                }
            }
            Resultado = firstTime34[k]-firstTime22[k];
            if (fRoot)
            {
                fRoot->writteRoot(Resultado,k,0,K0);
            }
            
        }
        
        if(time24[k].size()>0&&time43[k].size()>0)
        {
            firstTime24[k] = time24[k].at(0);
            firstTime43[k] = time43[k].at(0);
            for (G4int l = 1 ;l<time24[k].size();l++)
            {
                if(firstTime24[k]>time24[k].at(l))
                {
                    firstTime24[k]=time24[k].at(l);
                    //firstEnergy24[k]=energy24[k].at(l);
                }
            }
            for (G4int l = 1 ;l<time43[k].size();l++)
            {
                if(firstTime43[k]>time43[k].at(l))
                {
                    firstTime43[k]=time43[k].at(l);
                    //firstEnergy43[k]=energy43[k].at(l);
                }
            }
            Resultado= firstEnergy43[k]-firstTime24[k];
            if (fRoot)
            {
                fRoot->writteRoot(Resultado,k,1,K0);
            }
        }
    
    


    }
    for(G4int i = 0; i<nleakHits;i++)
    {
        leakHit *leakHit= (*hc2)[i];
        if(leakHit->GetCopy()==1)
        {
            longitudinal+=leakHit->GetEnergy();
        }
        else if(leakHit->GetCopy()==0)
        {
            albedo+=leakHit->GetEnergy();
        }
        else{
            lateral+=leakHit->GetEnergy();
        }
    }
    G4cout<<"Lateral: "<<lateral<<"\n"<<"Longitudinal: "<<longitudinal<<"\n albedo: "<<albedo<<G4endl;
    if(fRoot)
    {
        fRoot->writteleakRoot(longitudinal,albedo,lateral,K0);
    }
    
    
    
   /*for (G4int j = 0 ; j<nAbsHits;j++)
    {
        AbsHit *hitAbs = (*hc2)[j];
        //hitAbs->Print();
        //hitAbs->Draw();
        fRoot->writteAbsRoot(hitAbs->GetEnergy(),hitAbs->GetPos().x(),hitAbs->GetPos().y(),hitAbs->GetPos().z(),hitAbs->GetLayer(),hitAbs->GetID(),K0);
    }*/
}