
//

#ifndef Pero2DPrimaryGeneratorAction_h
#define Pero2DPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4GenericMessenger.hh"

class G4ParticleGun;
class G4Event;
class G4Box;

namespace Pero2D
{

/// The primary generator action class with particle gun.

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() override;

    // method from the base class
    void GeneratePrimaries(G4Event*) override;

    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }


  private:
	  void SavePrimaryEnergy(G4double);
    G4ParticleGun* fParticleGun = nullptr;  // pointer a to G4 gun class
    G4Box* fPero2DBox = nullptr;
    G4GeneralParticleSource* fParticleGPS;
    G4GenericMessenger *fMessengerParticleSource;
    G4String sourceType;
};


}  // namespace Pero2D

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
