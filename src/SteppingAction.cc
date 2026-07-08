//

#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4LogicalVolume.hh"
#include "G4TrackStatus.hh" 

namespace Pero2D
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction) : fEventAction(eventAction) {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringPero2DVolume) {
    const auto detConstruction = static_cast<const DetectorConstruction*>(
      G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringPero2DVolume = detConstruction->GetScoringPero2DVolume();
    G4cout<<" *************** got pointer to Pero2D scoring volume "<<G4endl;
  }

  // get volume of the current step
  G4LogicalVolume* volume =
    step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  // check if we are in scoring volume
  if (volume != fScoringPero2DVolume) return;

  // get track associated to step
  G4Track* thisTrack=step->GetTrack();
  fEventAction->SetNumOfTracks(thisTrack->GetTrackID());
  // investigate on secondaries and process
  //if( thisTrack->GetTrackID() > 3 ){
    //if (thisTrack->GetParentID() == 1) { //only consider processes on primary gamma only
    //G4cout<<" *** track ID is: " <<thisTrack->GetTrackID()<<G4endl;    
    //G4cout<<" particle name: " <<thisTrack->GetDefinition()->GetParticleName()<<G4endl;
    //G4cout<<" parent particle ID: " <<thisTrack->GetParentID()<<G4endl;
    //G4cout<<" particle total Energy is: " <<thisTrack->GetTotalEnergy()<<G4endl;
    // G4cout<<" particle kinetic Energy is: " <<thisTrack->GetKineticEnergy()<<G4endl; 
    // G4cout<<" particle status is: " <<thisTrack->GetTrackStatus()<<G4endl;  
    //G4cout<<" particle creator process name: " <<thisTrack->GetCreatorProcess()->GetProcessName()<<G4endl; 
    //} 
  //} 

  // collect energy deposited in this step
  //total energy
  G4double edepStep = step->GetTotalEnergyDeposit();
  fEventAction->AddEdep(edepStep);
  // non ionising
  G4double nonIonE = step->GetNonIonizingEnergyDeposit();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace Pero2D
