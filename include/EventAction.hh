//
#ifndef Pero2DEventAction_h
#define Pero2DEventAction_h 1

#include "G4UserEventAction.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

class G4Event;

namespace Pero2D
{

class RunAction;

/// Event action class

class EventAction : public G4UserEventAction
{
  public:
    EventAction(RunAction* runAction);
    ~EventAction() override = default;

    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event* event) override;

    void AddEdep(G4double edep) { fEdep += edep; }
    void AddNIEdep(G4double edep) { fNIEdep += edep; }
    void SetNumOfTracks(G4int id) { if (id > iNumOfTracks) iNumOfTracks = id;}

  private:
    RunAction* fRunAction = nullptr;
    G4double fEdep = 0.;
    G4double fNIEdep = 0.;
    G4int iNumOfTracks = 0;
};

}  // namespace Pero2D

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
