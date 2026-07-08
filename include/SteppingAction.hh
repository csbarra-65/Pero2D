//

#ifndef Pero2DSteppingAction_h
#define Pero2DSteppingAction_h 1

#include "G4UserSteppingAction.hh"

class G4LogicalVolume;
class G4Step;

namespace Pero2D
{

class EventAction;

/// Stepping action class

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(EventAction* eventAction);
    ~SteppingAction() override = default;

    // method from the base class
    void UserSteppingAction(const G4Step*) override;

  private:
    EventAction* fEventAction = nullptr;
    G4LogicalVolume* fScoringPero2DVolume = nullptr;
};

}  // namespace Pero2D

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
