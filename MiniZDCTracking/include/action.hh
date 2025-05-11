#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"
#include "generador.hh"
#include "runAction.hh"
#include "MyEventAction.hh"
#include "rootcreator.hh"
#include "TrackingAction.hh"

class MyActionIni : public G4VUserActionInitialization
{
    public:
    MyActionIni();
    ~MyActionIni();

    virtual void BuildForMaster() const;
    virtual void Build() const;

};





#endif