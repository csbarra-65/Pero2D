//
//

#ifndef Pero2DDetectorConstruction_h
#define Pero2DDetectorConstruction_h 1


#include <G4SystemOfUnits.hh>
#include <G4PhysicalConstants.hh>
#include "G4VUserDetectorConstruction.hh"
#include "G4GenericMessenger.hh"
#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include <G4PVPlacement.hh>
#include "G4UserLimits.hh"
//class G4VPhysicalVolume;
//class G4LogicalVolume;

namespace Pero2D
{

/// Detector construction class to define materials and geometry.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    ~DetectorConstruction();

    G4VPhysicalVolume* Construct() override;

    G4LogicalVolume* GetScoringPero2DVolume() const { return fScoringPero2DVolume; } 
    G4LogicalVolume* GetScoringScintVolume() const { return fScoringScintVolume; } 


  protected:
    G4LogicalVolume* fScoringPero2DVolume = nullptr;
    G4LogicalVolume* fScoringScintVolume = nullptr;

  private:

    //virtual void ConstructSDandField();

    G4Box *solidWorld, *solidPeroLayer, *solidElectrode, *solidKaptonFoil, *solidScint;
    G4LogicalVolume *logicWorld, *logicPeroLayer, *logicElectrode, *logicKaptonFoil, *logicScint; 
    G4VPhysicalVolume *physWorld, *physPeroLayer, *physElectrode, *physKaptonFoil, *physScint;     

    G4GenericMessenger *fMessengerPerovskite;
    G4double layerThickness;
    G4double layerDriftLenght;
    G4bool flavorBr;
    G4GenericMessenger *fMessengerKaptonFoil;
    G4double foilThickness;
    G4bool foilExists;
    G4GenericMessenger *fMessengerElectrodes; 
    G4double electrodeSizeY;
    G4bool electrodeExists;
    G4GenericMessenger *fMessengerScintillator;
    G4double scintThickness;
    G4bool scintExists;

    G4Material* foilMaterial;
    G4Material* perovskiteI;
    G4Material* perovskiteBr;
    G4Material* scintillator;
    G4Material* air;
    G4Material* electrodeMaterial;
    
    G4UserLimits* fStepLimit = nullptr;  // pointer to user step limits
    
    void DefineMaterial();
    void DefineOpticalSurfaceProperties();

};

}  // namespace Pero2D

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
