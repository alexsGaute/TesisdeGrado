#include "TrackingAction.hh"



TrackingAction::TrackingAction(rootcreator *createroot, MyEventAction *event) : root(createroot), fEventaction(event) 
{

}
TrackingAction::~TrackingAction(){}

void TrackingAction::PreUserTrackingAction(const G4Track* track)
{
    ParentID = track->GetParentID();
    Partdef = track -> GetParticleDefinition();
    if (ParentID == 0) K0 = track->GetKineticEnergy();

    if(ParentID==1)
    {
        cascadePos = track->GetVertexPosition();
        if(Partdef->GetParticleType() == "meson" || Partdef->GetParticleType() == "baryon")
        {
            type = 1;
            fEventaction->AddHad();
        }
        if(Partdef->GetParticleType() == "lepton"||Partdef->GetParticleType() == "gamma")
        {
            type = -1;
            fEventaction->AddEM();
        }    
    /*G4cout<<"La particula es "<<Partdef->GetParticleType()<<" su track ID es: "<< track->GetTrackID()<<", su parentID es: "<<
    track->GetParentID()<<" y la posicion de su creacion es: "<<cascadePos<<G4endl;
*/
    }
    else if(ParentID>1)
    {
        if(Partdef->GetParticleType() == "meson" || Partdef->GetParticleType() == "baryon")
        {
            type = 1;
            fEventaction->AddHad();
        }
        if(Partdef->GetParticleType() == "lepton"||Partdef->GetParticleType() == "gamma")
        {
            type = -1;
            fEventaction->AddEM();

        }
       /* G4cout<<"La particula es "<<Partdef->GetParticleType()<<" su track ID es: "<< track->GetTrackID()<<", su parentID es: "<<
    track->GetParentID()<<G4endl;   
*/
    }

    



}

void TrackingAction::PostUserTrackingAction(const G4Track* track)
{
    /*primaryvertex = event->GetPrimaryVertex();

    if(primaryvertex)
    {
        primaryparticle = primaryvertex->GetPrimary();
    }
    G4double K0 = primaryparticle->GetKineticEnergy();*/
    ParentID = track->GetParentID();
    if(ParentID==1)
    {
        root->writteTracking(cascadePos.x(),cascadePos.y(),cascadePos.z(),type,K0);
    }


}
