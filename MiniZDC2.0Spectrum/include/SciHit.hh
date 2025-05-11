#ifndef SCIHIT_HH
#define SCIHIT_HH


#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Threading.hh"

#include "G4UnitsTable.hh"
#include "G4VisAttributes.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
class SciHit : public G4VHit
{
public:
    SciHit()=default;
    SciHit(const SciHit&)=default;
    ~SciHit() override =default;
    // operators
    SciHit& operator=(const SciHit&) = default;
    G4bool operator==(const SciHit&) const;

    virtual void Draw();// override{}
    virtual void Print();

    inline void SetEnergy(G4double energy);

    inline G4double GetEnergy() const;

    
   // inline void SetPos(G4ThreeVector pos);

    //inline G4ThreeVector GetPos () const;

    inline void SetLayer(G4int layer);

    inline G4double GetLayer() const;

inline void SetCopy(G4int copy);

    inline G4double GetCopy() const;
    
    inline void SetID(G4int ID);

    inline G4int GetID() const;

    
    //Operadores new y delete sobrecargados para usar G4Allocator

    inline void* operator new(size_t);
    inline void operator delete(void*);

private:
    G4double fEnergy=0.;
    G4double fTime=0.;
    G4ThreeVector fPos;
    G4int fLayer=0;
    G4int fCopy=0;
    G4int fID=0;
    




};
//typedef G4THitsCollection<SciHit> MyHitsSci;
using MyHitsSci = G4THitsCollection<SciHit>;
extern G4ThreadLocal G4Allocator<SciHit>* SciHitAllocator;
 
inline void* SciHit::operator new(size_t)
{
    if(!SciHitAllocator)
    {
        SciHitAllocator = new G4Allocator<SciHit>;

    }
    void *hit;
    hit = (void *) SciHitAllocator->MallocSingle();
    return hit;
}

inline void SciHit::operator delete(void* hit)
{
    if (!SciHitAllocator) {
    SciHitAllocator = new G4Allocator<SciHit>;
  }
  SciHitAllocator->FreeSingle((SciHit*) hit);

    //SciHitAllocator->FreeSingle((SciHit*) hit);
}

inline void SciHit::SetEnergy(G4double energy)
    {
        fEnergy=energy;
    }

    inline G4double SciHit::GetEnergy() const
    {
        return fEnergy;
    }

    /*void SetTime(G4double time)
    {
        fTime=time;
    }

    G4double GetTime() {return fTime; }
*/
    /*inline void SciHit::SetPos(G4ThreeVector pos)
    {
        fPos=pos;
    }
    inline G4ThreeVector SciHit::GetPos () const
    {return fPos;}*/

    inline void SciHit::SetLayer(G4int layer)
    {
        fLayer=layer;
    }

    inline G4double SciHit::GetLayer() const {return fLayer; }

inline void SciHit::SetCopy(G4int copy)
    {
        fCopy=copy;
    }

    inline G4double SciHit::GetCopy() const {return fCopy; }

    
    inline void SciHit::SetID(G4int ID)
    {
        fID=ID;
    }

    inline G4int SciHit::GetID() const {return fID;}




#endif