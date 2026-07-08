//

#ifndef Pero2DRunAction_h
#define Pero2DRunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

class G4Run;

namespace Pero2D
{

/// Run action class

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    ~RunAction() override = default;

    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;

    void AddEdep(G4double edep);

  private:
    G4Accumulable<G4double> fEdep = 0.;
    G4Accumulable<G4double> fEdep2 = 0.;
};

}  // namespace Pero2D

#endif
