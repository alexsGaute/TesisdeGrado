#include "leakHit.hh"

G4ThreadLocal G4Allocator<leakHit>* leakHitAllocator=nullptr;
//leakHit::leakHit():fEnergy(0),fTime(0),fPos(G4ThreeVector()){}

//leakHit::~leakHit(){}
G4bool leakHit::operator==(const leakHit& right) const
{
  return ( this == &right ) ? true : false;
}


void leakHit::Draw()
{
    /*G4VVisManager * vismanager= G4VVisManager::GetConcreteInstance();

    if (vismanager)
    {
        G4Circle circle(fPos);
        circle.SetScreenSize(5.0);
        circle.SetFillStyle(G4Circle::filled);
        G4Colour red(1.0,0.0,0.0);
        G4VisAttributes atributes (red);
        circle.SetVisAttributes(atributes);
        vismanager->Draw(circle);
    }*/


}

void leakHit::Print()
{
   /*G4cout<<"En el centelleante la "
     << "Edep: "
     << std::setw(7) << G4BestUnit(fEnergy,"Energy")
     << " Position: "
     << std::setw(7) << G4BestUnit(fPos,"Length")
     << "  Layer: "
     << std::setw(7) << fLayer
     << "  Copy: "
     << std::setw(7) << fCopy<<" ID del evento "
     <<std::setw(7) << fID
     << G4endl;
     G4cout<< "En el centelleante de la capa "<<fLayer<< " el tiempo del hit es "<<G4BestUnit(fTime,"Time")<< " en el evento "<<fID<<G4endl; */
    
}
