//

#ifndef Pero2DActionInitialization_h
#define Pero2DActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

namespace Pero2D
{

/// Action initialization class.

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization() = default;
    ~ActionInitialization() override = default;

    void BuildForMaster() const override;
    void Build() const override;
};

}  // namespace Pero2D

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
