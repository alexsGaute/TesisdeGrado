#include "SciHit.hh"

G4ThreadLocal G4Allocator<SciHit>* SciHitAllocator=nullptr;
//SciHit::SciHit():fEnergy(0),fTime(0),fPos(G4ThreeVector()){}

//SciHit::~SciHit(){}
G4bool SciHit::operator==(const SciHit& right) const
{
  return ( this == &right ) ? true : false;
}


void SciHit::Draw()
{
    G4VVisManager * vismanager= G4VVisManager::GetConcreteInstance();

    if (vismanager)
    {
        G4Circle circle(fPos);
        circle.SetScreenSize(5.0);
        circle.SetFillStyle(G4Circle::filled);
        G4Colour red(1.0,0.0,0.0);
        G4VisAttributes atributes (red);
        circle.SetVisAttributes(atributes);
        vismanager->Draw(circle);
    }


}

void SciHit::Print()
{
   G4cout<<"En el centelleante la "
     << "Edep: "
     << std::setw(7) << G4BestUnit(fEnergy,"Energy")
     /*<< " Position: "
     << std::setw(7) << G4BestUnit(fPos,"Length")
     << "  Layer: "
     << std::setw(7) << fLayer
     << "  Copy: "
     << std::setw(7) << fCopy*/<<" ID del evento "
     <<std::setw(7) << fID
     << G4endl;
    //G4cout<< "Hit: "<< "Energy: "<<G4BestUnit(fEnergy,"Energy")<<"\n "<<" Time "<<G4BestUnit(fTime,"Time")<<"\n "<<
    //" Position "<< G4BestUnit(fPos,"Length")<<" Layer: "<< fLayer<< " copy: "<<fCopy<<G4endl;

}


