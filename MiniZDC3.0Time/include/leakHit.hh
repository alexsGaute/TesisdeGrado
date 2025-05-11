#ifndef LEAKHIT_HH
#define LEAKHIT_HH



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
class leakHit : public G4VHit
{
public:
    leakHit()=default;
    leakHit(const leakHit&)=default;
    ~leakHit() override =default;
    // operators
    leakHit& operator=(const leakHit&) = default;
    G4bool operator==(const leakHit&) const;

    virtual void Draw();// override{}
    virtual void Print();

    inline void SetEnergy(G4double energy);

    inline G4double GetEnergy() const;

    inline void SetCopy(G4int copy);

    inline G4double GetCopy() const;   
  
    inline void SetID(G4int ID);

    inline G4int GetID() const;


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
//typedef G4THitsCollection<leakHit> MyleakHits;
using MyleakHits = G4THitsCollection<leakHit>;
extern G4ThreadLocal G4Allocator<leakHit>* leakHitAllocator;
 
inline void* leakHit::operator new(size_t)
{
    if(!leakHitAllocator)
    {
        leakHitAllocator = new G4Allocator<leakHit>;

    }
    void *hit;
    hit = (void *) leakHitAllocator->MallocSingle();
    return hit;
}

inline void leakHit::operator delete(void* hit)
{
    if (!leakHitAllocator) {
    leakHitAllocator = new G4Allocator<leakHit>;
  }
  leakHitAllocator->FreeSingle((leakHit*) hit);

    //leakHitAllocator->FreeSingle((leakHit*) hit);
}

inline void leakHit::SetEnergy(G4double energy)
    {
        fEnergy=energy;
    }

    inline G4double leakHit::GetEnergy() const
    {
        return fEnergy;
    }

    /*void SetTime(G4double time)
    {
        fTime=time;
    }

    G4double GetTime() {return fTime; }

    inline void leakHit::SetPos(G4ThreeVector pos)
    {
        fPos=pos;
    }
    inline G4ThreeVector leakHit::GetPos () const
    {return fPos;}
*/
   
inline void leakHit::SetCopy(G4int copy)
    {
        fCopy=copy;
    }

    inline G4double leakHit::GetCopy() const {return fCopy; }

    
    inline void leakHit::SetID(G4int ID)
    {
        fID=ID;
    }

    inline G4int leakHit::GetID() const {return fID;}





#endif