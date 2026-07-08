//
#include "EventAction.hh"
#include "RunAction.hh"
#include <G4RootAnalysisManager.hh>

namespace Pero2D
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction* runAction) : fRunAction(runAction) 
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{
  fEdep = 0.;
  fNIEdep = 0.;
  iNumOfTracks = 0; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event*)
{
  // accumulate statistics in run action
  fRunAction->AddEdep(fEdep);
  G4double IonizationEnergy = 9 * eV;
  G4int iNumFreeChargePairs = fEdep/IonizationEnergy;
  G4cout<<" Deposited energy is "<<fEdep<<" number of generated ep is " <<iNumFreeChargePairs<<G4endl;
  // Fill event by event ntupla
  //G4double Et=fEdep/1000.;
  //G4double Eni=fNIEdep/1000.;
  auto man = G4RootAnalysisManager::Instance();
  man ->FillNtupleDColumn(1, 0, fEdep * keV);
  man ->FillNtupleDColumn(1, 1, fNIEdep * keV);
  man ->FillNtupleIColumn(1, 2, iNumOfTracks);
  man ->FillNtupleIColumn(1, 3, iNumFreeChargePairs);
  man->AddNtupleRow(1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace Pero2D
