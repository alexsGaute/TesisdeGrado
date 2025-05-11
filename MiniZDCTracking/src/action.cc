#include "action.hh"


MyActionIni::MyActionIni()
{}

MyActionIni::~MyActionIni()
{}

void MyActionIni::BuildForMaster() const
{
    auto histo = new rootcreator();
    MyRunAction *runAction = new MyRunAction(histo);
    SetUserAction(runAction);
    
}
void MyActionIni::Build() const
{
    auto histo = new rootcreator();

    MyGenerator *generator=new MyGenerator();
    SetUserAction(generator);

    MyRunAction *runAction = new MyRunAction(histo);
    SetUserAction(runAction);

    //SetUserAction(new MyEventAction(histo,generator));

    MyEventAction *evenAction = new MyEventAction(histo); 
    SetUserAction(evenAction);

    TrackingAction *trackingAction = new TrackingAction(histo,evenAction);
    SetUserAction(trackingAction);
   
}