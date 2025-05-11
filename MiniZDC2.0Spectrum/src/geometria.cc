#include "geometria.hh"
#include <vector>




MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{   
    delete fSci_mt;
    delete SiPM_mt;
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    /*Definir materiales si estan creados si no estan creados ver como se crean
    Usando*/
    G4NistManager *nist = G4NistManager::Instance();
    //
    //world Material
    //
    G4Material *worldMaterial = nist->FindOrBuildMaterial("G4_Galactic");
    /*G4Element *C = nist->FindOrBuildElement("G4_C");
    G4Element *C = nist->FindOrBuildElement("G4_H");
    G4Element *C = nist->FindOrBuildElement("G4_O");*/
    //
    //Tugsteno Material
    //
    //G4Material *tugs =nist->FindOrBuildMaterial("G4_W");
    //
    //Copper Material
    //
    G4Material *Cu = new G4Material("Copper",   29., 63.55*g/mole,  8.960*g/cm3);
    G4Material *Ag = new G4Material("Silver",47., 107.85*g/mole,10.490*g/cm3);
    //
    //centellante Material
    //
    poli =
    new G4Material("Scintillator", 1.032*g/cm3, 2);
    poli->AddElement(nist->FindOrBuildElement("C"), 8);
    poli->AddElement(nist->FindOrBuildElement("H"), 8);
    fSci_mt = new G4MaterialPropertiesTable();
    fSci_mt ->AddConstProperty("SCINTILLATIONYIELD",20. /MeV);
    fSci_mt->AddConstProperty("SCINTILLATIONTIMECONSTANT1",2. *ns);

    poli->SetMaterialPropertiesTable(fSci_mt);



    //
    //SiPm Material
    //
    G4Material *SiPM =
    new G4Material("SiPM", 2.33*g/cm3, 3);
    SiPM->AddElement(nist->FindOrBuildElement("Si"), 0.95);
    SiPM->AddElement(nist->FindOrBuildElement("O"), 0.03);
    SiPM->AddElement(nist->FindOrBuildElement("Al"), 0.02);
    SiPM_mt = new G4MaterialPropertiesTable();
    //G4ThreeVector WLabsRange =()0.000002 100 0.000005 200 0.000008 300

    G4MaterialPropertyVector *absprop = new G4MaterialPropertyVector(3);
    absprop->InsertValues(0.000002, 100);
    absprop->InsertValues(0.000005, 200);
    absprop->InsertValues(0.000008, 300);
    SiPM_mt->AddProperty("WLSABSLENGTH",absprop);
    SiPM->SetMaterialPropertiesTable(SiPM_mt);
    //
    //PCB Material
    //
    G4Material *G10 =
          new G4Material("PCB",1.700 * g / cm3, 4);
    G10->AddElement(G4NistManager::Instance()->FindOrBuildElement("Si"),  1);
    G10->AddElement(G4NistManager::Instance()->FindOrBuildElement("O"),  2);
    G10->AddElement(G4NistManager::Instance()->FindOrBuildElement("C"),  3);
    G10->AddElement(G4NistManager::Instance()->FindOrBuildElement("H"),  3);
    
    //
    //Isolated Mylar
    //
    G4Material* Mylar =
    new G4Material("Mylar",  1.4*g/cm3, 3);
    Mylar -> AddElement(nist->FindOrBuildElement("H"),0.042);
    Mylar -> AddElement(nist->FindOrBuildElement("C"),0.625);
    Mylar -> AddElement(nist->FindOrBuildElement("O"),0.333);

    //
    //Reflector
    //
    G4Material *C10H8O4 = new G4Material("Reflector",1.38*g/cm3,3);
    C10H8O4->AddElement(nist->FindOrBuildElement("C"),10);
    C10H8O4->AddElement(nist->FindOrBuildElement("H"),8);
    C10H8O4->AddElement(nist->FindOrBuildElement("O"),4);


    //G4Material *poli=nist->FindOrBuildMaterial("G4PLASTICSCVINYLTOLUENE");
    
    /*G4Material *SiO2=new G4Material("SiO2",2.201*g/cm3,2);
    SiO2->AddElement(nist->FindOrBuildElement("Si"),1);
    SiO2->AddElement(nist->FindOrBuildElement("O"),2);

    G4Material *H2O=new G4Material("H2O",1.000*g/cm3,2);
    H2O->AddElement(nist->FindOrBuildElement("O"),1);
    H2O->AddElement(nist->FindOrBuildElement("H"),2);

    G4Element *C =nist->FindOrBuildElement("C");


    G4Material *aerogel = new G4Material("Aerogel", 0.200*g/cm3,3);
    aerogel->AddMaterial(SiO2,62.5*perCent);
    aerogel->AddMaterial(H2O,37.4*perCent);
    aerogel->AddElement(C,0.1*perCent);*/
    //---------------------------------


    /*Aqui estan definidos todos los volumenes solidos*/
    G4Box *solidWorld= new G4Box("NameWorld",20.*cm,20.*cm,25*cm);
    
    G4Box *SciBox2 =new G4Box("solidSci1",XSize/14,YSize/10,SciThick/2);
    G4Box *solidAbs =new G4Box("solidAbs",XSize/2,YSize/2,AbsThick/2);
    G4Box *SolidSiPM = new G4Box("SolidSiPM",SiPMsize/2,SiPMsize/2,SiPMsize/2);//volumen solido de los SiPM

    G4Box *SolidPCB =new G4Box("SolidPCB",XSize/2,YSize/2,PCBThick/2);//columen solido del PCB
    G4Box *solidreflective = new G4Box("solidreflective",XSize/2,YSize/2, reflectiveThickness/2);
    G4Box *solidKapton = new G4Box("solidMylar",XSize/2,YSize/2,kaptonThick/2);//volumen solido del Mylar

    G4ThreeVector zTrans1(0,0,1*mm);
    G4SubtractionSolid *SolidSci = new G4SubtractionSolid("sub1",SciBox2,SolidSiPM,0,zTrans1);
    /*G4SubtractionSolid *HasolidSci = new G4SubtractionSolid("subs", SciBox, SolidSiPM,0,zTrans);/*Aqui mediante una operacion booleana se 
    substrae el volumen del SiPM con el de la caja del centellante para que quede una caja con un hueco que es donde quedara el SiPM ubicado*/
    
    /*Definicion de los volumenes logicos*/
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld,worldMaterial,"logicWorld");//World
    logicAbs = new G4LogicalVolume(solidAbs,Cu,"EmlogicAbs");
    logicSci = new G4LogicalVolume(SolidSci,poli,"EmSolidSci");
    
    SiPMlogic = new G4LogicalVolume(SolidSiPM,SiPM,"SiPMlogic");//SiPM

    G4LogicalVolume *reflectivelogic = new G4LogicalVolume(solidreflective,C10H8O4,"logicreflective");
    
    G4LogicalVolume *PCBlogic = new G4LogicalVolume(SolidPCB,G10,"PCBlogic");//PCB
    
    G4LogicalVolume *Kaptonlogic = new G4LogicalVolume(solidKapton,Mylar,"Kaptonlogic");//Mylar


    /*Posicionamiento de los volumenes*/
    G4VPhysicalVolume *physicalWorld = new G4PVPlacement(0,
                                                        G4ThreeVector(0.,0.,0.),
                                                        logicWorld,
                                                        "mundofisico",
                                                        0,false,0,true);
    
    G4VPhysicalVolume *firstKapton1 = new G4PVPlacement(0,G4ThreeVector(0,0,kaptonThick/2),Kaptonlogic,"firstKapton1",logicWorld,false,0,false);
    G4VPhysicalVolume *firstPCB = new G4PVPlacement(0,G4ThreeVector(0,0,kaptonThick+PCBThick/2),PCBlogic,"firstPCB",logicWorld,false,0,false);
    G4VPhysicalVolume *firstReflective1 = new G4PVPlacement(0,G4ThreeVector(0,0,kaptonThick+PCBThick+reflectiveThickness/2),reflectivelogic,"firstReflective1",logicWorld,false,0,false);
    G4double zSci0 = kaptonThick + PCBThick+reflectiveThickness+SciThick/2;
    G4double zSiPM0 = kaptonThick + PCBThick+reflectiveThickness+SciThick - SiPMsize/2 ;
    G4VPhysicalVolume *firstReflective2 = new G4PVPlacement(0,G4ThreeVector(0,0,kaptonThick+PCBThick+reflectiveThickness+SciThick+reflectiveThickness/2),reflectivelogic,"firstReflective2",logicWorld,false,0,false);
    G4VPhysicalVolume *firstKapton2 = new G4PVPlacement(0,G4ThreeVector(0,0,kaptonThick+PCBThick+2*reflectiveThickness+SciThick+kaptonThick/2),Kaptonlogic,"firstKapton2",logicWorld,false,0,false);

    for (G4int i = 0;i<7;i++)
            {
                for (G4int j = 0;j<5;j++)
                {
                    if (!(i == 0 && j == 0)){
                        if (!(i == 0 && j == 4)){
                            if (!(i == 6&& j == 0)){
                                if (!(i == 6 && j == 4)){
                                    //Posicionamiento en X y Y de cada uno de los elementos de la matriz
                                    //El numero de copia tiene el siguiente formato LFC, es un numero de 3 digitos donde las centenas designa el Layer,
                                    //las decenas la fila y las unidades las columnas.
                                    G4double xSci = ((2*i+1)*(XSize/2))/7-XSize/2;
                                    G4double ySci = (YSize/2)-((2*j+1)*(YSize/2))/5;
                                    /*G4double ySci = ((2*j+1)*(YSize/2))/7-YSize/2;
                                    G4double xSci = (XSize/2)-((2*i+1)*(XSize/2))/5;*/
                                    G4VPhysicalVolume *PhysSci = new G4PVPlacement(0,G4ThreeVector(xSci,ySci,zSci0),logicSci,"PhysSci",logicWorld,false,10*(j+1) + i+1,false);
                                    G4VPhysicalVolume *SiPMPhy = new G4PVPlacement(0,G4ThreeVector(xSci,ySci,zSiPM0),SiPMlogic,"SiPMPhy",logicWorld,false,10*(j+1) + i+1,false);
                                }
                            }
                        }
                    }
                    /*G4double xSci = ((2*j+1)*XSize)/5-XSize;
                    G4double ySci = YSize-((2*i+1)*YSize)/7;
                    G4VPhysicalVolume *HaPhysSci = new G4PVPlacement(0,G4ThreeVector(xSci,ySci,zSci),HalogicSci,"HaPhysSci",logicWorld,false,100*(k+1)+j+1+i*5,false);
                    G4VPhysicalVolume *SiPMPhy = new G4PVPlacement(0,G4ThreeVector(xSci,ySci,zSiPM),SiPMlogic,"SiPMPhy",logicWorld,false,100*(k+1)+j+1+i*5,false);
                    */
                }
            }
    for (G4int k=0;k<6;k++)
    {
        //Posiciones en Z de cada una de los componentes, las variables estan explicadas en el geometria.hh
        
            G4double zAbs = Z0+AbsThick/2 + (totalthick*k)*mm;
            G4double zref1 = Z0+AbsThick + reflectiveThickness/2 +  (totalthick*k)*mm;
            G4double zSci = Z0+AbsThick + reflectiveThickness + SciThick/2 + (totalthick*k)*mm;
            G4double zSiPM = Z0+AbsThick + SciThick + reflectiveThickness- SiPMsize/2 + (totalthick*k)*mm;
            G4double zref2 = Z0+AbsThick + SciThick + reflectiveThickness*1.5 + (totalthick*k)*mm;
            G4double zPCB = Z0+AbsThick + SciThick + 2*reflectiveThickness + PCBThick/2 + (totalthick*k)*mm;
            G4double zKapton =Z0+AbsThick + SciThick + 2*reflectiveThickness+PCBThick + kaptonThick/2*mm + (totalthick*k)*mm;
            
            
            
            G4VPhysicalVolume *PhyAbs = new G4PVPlacement(0,G4ThreeVector(0,0,zAbs),logicAbs,"PhyAbs",logicWorld,false,k+1,false);
            G4VPhysicalVolume *PCBPhy =new G4PVPlacement(0,G4ThreeVector(0,0,zPCB),PCBlogic,"PCBPhy",logicWorld,false,k+1,false);//Posicion del PCB
            G4VPhysicalVolume *KaptonPhy =new G4PVPlacement(0,G4ThreeVector(0,0,zKapton),Kaptonlogic,"KaptonPhy",logicWorld,false,k+1,false);//Posicion del Mylar
            G4VPhysicalVolume *reflecivephys1 = new G4PVPlacement(0,G4ThreeVector(0,0,zref1),reflectivelogic,"refphy1",logicWorld,false,k+1,false);
            G4VPhysicalVolume *reflecivephys2 = new G4PVPlacement(0,G4ThreeVector(0,0,zref2),reflectivelogic,"refphy2",logicWorld,false,k+1,false);
            
            for (G4int i = 0;i<7;i++)
            {
                for (G4int j = 0;j<5;j++)
                {
                    if (!(i == 0 && j == 0)){
                        if (!(i == 0 && j == 4)){
                            if (!(i == 6&& j == 0)){
                                if (!(i == 6 && j == 4)){
                                    //Posicionamiento en X y Y de cada uno de los elementos de la matriz
                                    //El numero de copia tiene el siguiente formato LFC, es un numero de 3 digitos donde las centenas designa el Layer,
                                    //las decenas la fila y las unidades las columnas.
                                    G4double xSci = ((2*i+1)*(XSize/2))/7-XSize/2;
                                    G4double ySci = (YSize/2)-((2*j+1)*(YSize/2))/5;
                                    /*G4double ySci = ((2*j+1)*(YSize/2))/7-YSize/2;
                                    G4double xSci = (XSize/2)-((2*i+1)*(XSize/2))/5;*/
                                    G4VPhysicalVolume *PhysSci = new G4PVPlacement(0,G4ThreeVector(xSci,ySci,zSci),logicSci,"PhysSci",logicWorld,false,100*(k+1)+10*(j+1) + i+1,false);
                                    G4VPhysicalVolume *SiPMPhy = new G4PVPlacement(0,G4ThreeVector(xSci,ySci,zSiPM),SiPMlogic,"SiPMPhy",logicWorld,false,100*(k+1)+10*(j+1) + i+1,false);
                                }
                            }
                        }
                    }
                    /*G4double xSci = ((2*j+1)*XSize)/5-XSize;
                    G4double ySci = YSize-((2*i+1)*YSize)/7;
                    G4VPhysicalVolume *HaPhysSci = new G4PVPlacement(0,G4ThreeVector(xSci,ySci,zSci),HalogicSci,"HaPhysSci",logicWorld,false,100*(k+1)+j+1+i*5,false);
                    G4VPhysicalVolume *SiPMPhy = new G4PVPlacement(0,G4ThreeVector(xSci,ySci,zSiPM),SiPMlogic,"SiPMPhy",logicWorld,false,100*(k+1)+j+1+i*5,false);
                    */
                }
            }
        
        
        /*G4cout<<"La z del absorbente es: " <<-ZdistHa+zAbs<<G4endl;
        G4cout<<"La z del Sci es: " <<-ZdistHa+zSci<<G4endl;
        G4cout<<"La z del SiMP es: " <<-ZdistHa+zSiPM<<G4endl;    
        G4cout<<"La z del PCB es: " <<-ZdistHa+zPCB<<G4endl;
        G4cout<<"La z del Mylar es: " <<-ZdistHa+zMylar<<G4endl;
        G4cout<<"\n"<<"--------------------"<<"\n";*/

        
        
    }
    
    /*Definicion de los atributos */
    G4VisAttributes invisible(G4VisAttributes::GetInvisible());
    G4VisAttributes bluek(G4Colour(0.0, 0.0, 1.0, 1.0)); // approx blue
    G4VisAttributes cyank(G4Colour(0.0, 1.0, 1.0, 0.6)); // approx cyan
    G4VisAttributes brownk(G4Colour(0.6, 0.4, 0.0, 1.0)); // approx brown
    G4VisAttributes redk(G4Colour(1.0, 0.2, 0.2, 0.4)); // approx red
    G4VisAttributes greenk(G4Colour(0.2, 1.0, 0.2, 0.6)); // approx green
    G4VisAttributes yellowk(G4Colour(1.0, 1.0, 0.0, 0.5)); // approx yellow
    G4VisAttributes morao(G4Colour(0.5,0.0,0.5));
    G4VisAttributes orange(G4Colour(1.0,0.5,0.0));


    //Este es para hacer invisible el World
    logicWorld->SetVisAttributes(invisible);


    G4VisAttributes *visAbsEm = new G4VisAttributes(greenk);
    visAbsEm->SetVisibility(true);
    visAbsEm->SetForceSolid(false);
    logicAbs->SetVisAttributes(visAbsEm);


    G4VisAttributes *visSciEm = new G4VisAttributes(cyank);
    visSciEm->SetVisibility(true);
    visSciEm->SetForceSolid(true);
    logicSci->SetVisAttributes(visSciEm);



    /*G4VisAttributes *vistugs = new G4VisAttributes(greenk);
    vistugs->SetVisibility(true);
    vistugs->SetForceSolid(false);  // default: SetForceWireframe(true);
    HalogicAbs->SetVisAttributes(vistugs);
    
    G4VisAttributes *viscente = new G4VisAttributes(cyank);
    viscente->SetVisibility(true);
    viscente->SetForceSolid(false);  // default: SetForceWireframe(true);
    HalogicSci->SetVisAttributes(viscente);
*/
    G4VisAttributes *visfoto = new G4VisAttributes(redk);
    visfoto->SetVisibility(true);
    visfoto->SetForceSolid(true);  // default: SetForceWireframe(true);
    SiPMlogic->SetVisAttributes(visfoto);

    G4VisAttributes *visPCB = new G4VisAttributes(yellowk);
    visPCB->SetVisibility(true);
    visPCB->SetForceSolid(true);  // default: SetForceWireframe(true);
    PCBlogic->SetVisAttributes(visPCB);


    G4VisAttributes *visrefl = new G4VisAttributes(bluek);
    visrefl->SetVisibility(true);
    visrefl->SetForceSolid(false);
    reflectivelogic->SetVisAttributes(visrefl);
    
    return physicalWorld;


    
}

void MyDetectorConstruction::ConstructSDandField()
{
    //Puntero al SDManager
    auto sdManager = G4SDManager::GetSDMpointer();
    
    
    

    //Defiinicion del centellante como SD
    SciSD *centSD = new SciSD("SensitiveSci","SciHitsCollection");
    logicSci->SetSensitiveDetector(centSD);
    sdManager->AddNewDetector(centSD);

/*
    //Definicion del absorbente como SD
    AbsSD *AbsorberSD = new AbsSD("SensitiveAbs","AbsHitCollection");
    logicAbs->SetSensitiveDetector(AbsorberSD);
    sdManager->AddNewDetector(AbsorberSD);
  */  
   
}