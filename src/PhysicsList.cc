//
#include "PhysicsList.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysicsWVI.hh"
#include "G4OpticalPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

namespace Pero2D
{

PhysicsList::PhysicsList()
{
//Ionisation in thin absorbers (class name G4PAIModel)?
//Ionisation in thin absorbers (class name G4PAIPhotModel)?
  RegisterPhysics(new G4DecayPhysics()); 
  RegisterPhysics(new G4RadioactiveDecayPhysics()); 
  // EM 3  
  RegisterPhysics(new G4EmStandardPhysics_option3());
  RegisterPhysics(new G4OpticalPhysics());
}

void PhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace Pero2D