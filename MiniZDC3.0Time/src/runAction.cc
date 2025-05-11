#include "runAction.hh"

MyRunAction::MyRunAction(rootcreator *createRoot) : fRoot(createRoot)
{
    //Creacion de las Ntuples antes de que comience el Run
    //Hay un histograma 2D creado que se tiene que llenar en cada una de las
    //implementaciones de las clases de los sensitives detectors
    
   /*G4AnalysisManager *man1 = G4AnalysisManager::Instance();
    //man1->CreateH1("fEdep","title",100,0,50);
    //man1->CreateH2("H2","title",7,0,7,100,0,10);
    man1->CreateNtuple("Sci","Sci");
   
    man1->CreateNtupleIColumn("NLayer");//aqui se guarda el numero del layer de un hit
    man1->CreateNtupleIColumn("NCopy");//aqui se guarda el numero de la copia del pixel del hit
    man1->CreateNtupleDColumn("fX");//aqui se guarda la posicion en X del hit
    man1->CreateNtupleDColumn("fY");//aqui se guarda la posicion en Y del hit
    man1->CreateNtupleDColumn("fZ");//aqui se guarda la posicion en Z del hit
    man1->CreateNtupleDColumn("fEdep");//aqui se guarda la energia depositada
    man1->CreateNtupleIColumn("feventID");
    //man1->CreateNtupleDColumn("globaltime");
    
    man1->FinishNtuple(); */

    
    G4int thread = G4Threading::G4GetThreadId();
    if(fRoot)
    {fRoot->initializeRoot( thread);}
    
    
}
MyRunAction::~MyRunAction()
{
    fRoot->finishRoot();
}

void MyRunAction::BeginOfRunAction(const G4Run *run)
{
     G4int runID = run->GetRunID()+1;
    G4int thread = G4Threading::G4GetThreadId();
    
    G4cout<<"\n"<<"INITIALAZING RUN NO "<<runID<<"\n"<<"========================================="<<G4endl;


     
    //Aqui crea un archivo .root donde guardaremos la data,
    //El formato del nombre viene dado por el numero del Run
    /*G4AnalysisManager *man1 = G4AnalysisManager::Instance();
    man1->Reset();
    G4int runID = run->GetRunID();
    runID+=1;
    std::stringstream strRunID;
    strRunID<<runID;
    man1->OpenFile("output"+strRunID.str()+".root");*/
}
void MyRunAction::EndOfRunAction(const G4Run *run)
{
    G4int thread = G4Threading::G4GetThreadId();
      
    //Para escribir las Ntuplas en el .root
    //y cerrarlo 
    /*G4AnalysisManager *man1 = G4AnalysisManager::Instance();

    man1->Write();
    man1->CloseFile();
    */
    
    G4int runID = run->GetRunID()+1;
    
    
    G4cout<<"\n"<<"FINISHING RUN NO "<<runID<<"\n"<<"========================================="<<G4endl;
}
