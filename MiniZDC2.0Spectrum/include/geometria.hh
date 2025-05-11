#ifndef GEOMETRIA_HH
#define GEOMETRIA_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"

#include "SciSD.hh"
#include "G4VisAttributes.hh"
#include <G4Colour.hh>
#include "G4SDManager.hh"
//#include "AbsSD.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    virtual void ConstructSDandField();//funcion para construir los sensitive detectors
    virtual G4VPhysicalVolume *Construct();
private:
G4double  AbsThick = 30*mm;
G4double  SciThick = 5*mm;
G4double kaptonThick = 0.12*mm;//grosor del kapton
G4double reflectiveThickness = 0.1*mm;
//G4double XSize = 102*mm;//tamanio de la mitad de la placa en x
//G4double YSize =143*mm;//tamanio de la mitad de la placa en Y 
G4double XSize = 143*mm;
G4double YSize = 102*mm;
G4double SiPMsize=3*mm;//dimensiones del SiPM
G4double PCBThick =1.5*mm;//Espesor de la pcb
G4double totalthick = 37*mm; //Ancho de las siguinete composicion |absorbente||Cenetellante||PCB||Mylar|
/*Volumenes logicos que se tienen que definir aqui puesto que se usaran para ser llamados como sensitives detectors*/
G4double Z0 = 6.94*mm;
G4LogicalVolume *logicSci;
G4LogicalVolume *logicAbs;
G4LogicalVolume *SiPMlogic;
G4MaterialPropertiesTable *fSci_mt = nullptr;
G4MaterialPropertiesTable *SiPM_mt=nullptr;
G4Material* poli =nullptr;

};






#endif