#include <iostream>
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "G4RunManagerFactory.hh"


#include "FTFP_BERT.hh"
#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"

#include "geometria.hh"
//#include "DetectorConstruction.hh"
#include "action.hh"


int main(int argc, char ** argv)
{

	G4int nThreads = 4;
	auto runManager =
    G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);
#ifdef G4MULTITHREADED
  if ( nThreads > 0 ) {
    runManager->SetNumberOfThreads(nThreads);
  }
#endif
//auto runManager= new G4RunManager();
	runManager->SetUserInitialization(new MyDetectorConstruction());
	//runManager->SetUserInitialization(new MyPhysicsList());
	auto factory = new G4PhysListFactory();
	auto fisica = factory->GetReferencePhysList("FTFP_BERT_EMZ");
	runManager->SetUserInitialization(fisica);
	//auto physicslist = new FTFP_BERT;
	//runManager->SetUserInitialization(physicslist);
	runManager->SetUserInitialization(new MyActionIni());
	runManager->Initialize();
	
	//G4UIExecutive *ui = new G4UIExecutive(argc,argv);
	
	G4UIExecutive *ui;
	if (argc == 1)
	{
		ui=new G4UIExecutive(argc,argv);
	}


	G4VisManager *visman = new G4VisExecutive();
	visman->Initialize();
	
		
	G4UImanager *UIman = G4UImanager::GetUIpointer();
	if(ui){
	UIman->ApplyCommand("/control/execute vis.mac");
	ui->SessionStart();
	delete ui;
	}
	else{
		G4String command = "/control/execute ";
		G4String filename = argv[1];
		UIman->ApplyCommand(command+filename);
		
	}
	delete runManager;
	delete visman;
	//return 0;
}
