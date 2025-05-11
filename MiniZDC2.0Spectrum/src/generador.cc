#include "generador.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4UImanager.hh"
#include "G4ParticleTable.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"

MyGenerator::MyGenerator(): G4VUserPrimaryGeneratorAction(), fParticleGun(0) 
{
    G4int n_particles=1;
    fParticleGun = new G4ParticleGun(n_particles);
    

    //fMessenger = new generadorMessenger(this);

    /*ROOT::EnableThreadSafety();
    
    fRootFile = new TFile("salida_data1.root");
    //fRootFile = TFile::Open("salida_data1.root","READ");//carga el file en la variable fRootFile
    //auto T = new TTree();
    
    fRootFile->GetObject("event",T); //coge el  file que tiene un tree con el nombre "event" y lo guarda en el tree creado en el .hh 
    //------agrega la direccion del tree al con el nombre de cada una de las variables en el tree y le dice la variable en la que se va a guardar
    
    T->SetBranchAddress("px",&px);
    T->SetBranchAddress("pY",&py);
    T->SetBranchAddress("pz",&pz);
    T->SetBranchAddress("x",&x);
    T->SetBranchAddress("y",&y);
    T->SetBranchAddress("ID",&id);
    T->SetBranchAddress("z",&z);
    T->SetBranchAddress("e",&e);
    number_entries=T->GetEntries();
    
    number_particles = 0;
*/
}

MyGenerator::~MyGenerator()
{
    delete fParticleGun;
    //delete fMessenger;
}

void MyGenerator::GeneratePrimaries(G4Event *anEvent)

{
	
   //T->GetEntry(number_particles); //toma la entrada del Tree numero number_particles
   
   

    	
    	
    G4ParticleTable *particletable = G4ParticleTable::GetParticleTable();
    
    G4ParticleDefinition *particle = particletable->FindParticle(2112); //toma el id de la particula
    //G4ParticleDefinition *particle = particletable->FindParticle(22); //toma el id de la particula
    fParticleGun->SetParticleDefinition(particle);
    //G4double Pmod = sqrt(px*px+py*py+pz*pz);
    
    //G4ThreeVector pos(x,y,z); //vector que determina la posicion del vertice del particle gun
    G4ThreeVector pos(0,0,0);
    G4ThreeVector momento(0,0,1);
    G4double rand1 = CLHEP::RandFlat::shoot(-1,1);
    G4double rand2 = CLHEP::RandFlat::shoot(-1,1);
    G4ThreeVector pos2((143/2)*rand1,(102/2)*rand2,0);
    //G4cout<<"La energia de la particula es: "<<e<<" GeV" <<"\n"<<"El momento es: "<<momento<<G4endl;
    //G4ThreeVector mom(px/ptot,py/ptot,pz/ptot);
    if(fParticleGun){
    //fParticleGun->SetParticlePosition(pos2*mm);
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(momento);
    //fParticleGun->SetParticleMomentum(momento*GeV);
    //fParticleGun->SetParticleEnergy(2*GeV);
    
    
    fParticleGun->GeneratePrimaryVertex(anEvent);
    }

   /* number_particles= number_particles+1;
    if(number_particles==number_entries)
    {
        number_particles=0;
    }
	*/
}
/*void MyGenerator::SetPrimaryEnergy(G4double energy)

{
    fPrimaryEnergy=energy;
}

G4double MyGenerator::GetPrimaryEnergy() const
{
    return fPrimaryEnergy;
}*/