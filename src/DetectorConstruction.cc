//

#include "DetectorConstruction.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4VisAttributes.hh"

namespace Pero2D
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
{
  G4cout << "In DetectorConstruction::DetectorConstruction" << G4endl;
	
  //perovskite layer 
  fMessengerPerovskite = new G4GenericMessenger(this, "/perovskite/", "Construction of Peroskite layer"); 
  fMessengerPerovskite->DeclarePropertyWithUnit("layerThickness", "mm", layerThickness, 
    "Thickness of the perovskite layer");
  fMessengerPerovskite->DeclarePropertyWithUnit("layerDriftLenght", "mm", layerDriftLenght, 
    " drift lenght within the perovskite layer");
  fMessengerPerovskite->DeclareProperty("flavorBr", flavorBr, "true or false"); 

  //polysiloxane scint
  fMessengerScintillator = new G4GenericMessenger(this, "/scint/", "polissilossane sciontillator"); 
  fMessengerScintillator->DeclarePropertyWithUnit("scintThickness", "mm", scintThickness, "polys. scint Thickness");
  fMessengerScintillator->DeclareProperty("scintExists", scintExists, "true or false");
  
  //kapton foil
  fMessengerKaptonFoil = new G4GenericMessenger(this, "/kapton/", "detector supporting foil"); 
  fMessengerKaptonFoil->DeclarePropertyWithUnit("foilThickness", "mm", foilThickness, 
    "Thickness of the detector supporting foil");
  fMessengerKaptonFoil->DeclareProperty("foilExists", foilExists, "true or false");
  
  //Gold electrodes
  fMessengerElectrodes = new G4GenericMessenger(this, "/electrodes/", "Interdigitated electrodes"); 
  fMessengerElectrodes->DeclareProperty("electrodeExists", electrodeExists, "true or false");
  fMessengerElectrodes->DeclarePropertyWithUnit("SizeY", "mm", electrodeSizeY, 
    " electrode size Y");

  // default thickness and drift lenght of Perovskite layer, kapton foil default thickness and presence
  // electrodes presence

  layerThickness = 0.1 * mm;
  layerDriftLenght = 2.0 * mm;
  flavorBr = false;
  fScoringPero2DVolume = 0;

  foilExists = true;
  foilThickness = 0.5 * mm;

  electrodeSizeY = 1 * mm;
  electrodeExists = true;
 
  scintExists = true;
  scintThickness = 1.0 * mm;
  fScoringScintVolume = 0;
  
  DefineMaterial();
  DefineOpticalSurfaceProperties();
} 

DetectorConstruction::~DetectorConstruction()
{
	delete fMessengerPerovskite;
  delete fMessengerKaptonFoil;
  delete fMessengerElectrodes;
  delete fMessengerScintillator;
}

void DetectorConstruction::DefineOpticalSurfaceProperties()
{
  // scintillator surfaces
	// absorption = 1 - reflectivity, thus
	//  reflectivity 0 and transmission 0 means total absorption
	//  reflectivity 0 and transmission 1 means total transmission
	//  reflectivity 1 and transmission 0 (or whatever) means Fresnel

  // material properties table for a fully Fresnel surface
	std::vector<G4double> ephoton = {1.0*eV, 7.0*eV};
  std::vector<G4double> reflectivity = { 1., 1. };
	std::vector<G4double> transmittance = { 0., 0. };
	G4MaterialPropertiesTable* MPTfresnel = new G4MaterialPropertiesTable();
	MPTfresnel->AddProperty("REFLECTIVITY", ephoton, reflectivity);
	MPTfresnel->AddProperty("TRANSMITTANCE", ephoton, transmittance);

  // build Fresnel surface
	G4OpticalSurface* opScintAirSurface = new G4OpticalSurface("opScintAirSurface");
	opScintAirSurface->SetModel(unified);
	opScintAirSurface->SetType(dielectric_dielectric);
	opScintAirSurface->SetFinish(polished); // ground would be more appropriated but requires time
	opScintAirSurface->SetMaterialPropertiesTable(MPTfresnel);

  if (scintExists){
      new G4LogicalBorderSurface("logicBorderScintAirSurface", 
			  physScint, physWorld, opScintAirSurface);
  }
}


void DetectorConstruction::DefineMaterial()
{
	// Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  air = nist->FindOrBuildMaterial("G4_AIR");
  G4cout<<" POINTER TO AIR " << air << G4endl;
	G4double ephoton[2] = {1.0*eV, 7.0*eV};
  G4double refractiveIndexAir[2] = {1.000, 1.000};
	G4MaterialPropertiesTable* mptAir = new G4MaterialPropertiesTable();
	mptAir->AddProperty("RINDEX", ephoton, refractiveIndexAir, 2);
	air->SetMaterialPropertiesTable(mptAir);

  
  electrodeMaterial = nist->FindOrBuildMaterial("G4_Au");
  G4cout<<" POINTER TO Au " << electrodeMaterial << G4endl;

  foilMaterial = nist->FindOrBuildMaterial("G4_KAPTON");
  if (foilMaterial != nullptr)
    G4cout<<" POINTER TO kapton " << foilMaterial << G4endl;
  else
    G4cout<<" POINTER TO kapton is null" << G4endl;

  //perovskite material I
  perovskiteI = new G4Material("perovskiteI", 2.55*g/cm3, 5); 
  perovskiteI->AddElement(nist->FindOrBuildElement("C"), 16); 
  perovskiteI->AddElement(nist->FindOrBuildElement("H"), 24);
  perovskiteI->AddElement(nist->FindOrBuildElement("N"), 2);
  perovskiteI->AddElement(nist->FindOrBuildElement("Pb"), 1);
  perovskiteI->AddElement(nist->FindOrBuildElement("I"), 4); 

  //perovskite material Br
  perovskiteBr = new G4Material("perovskiteBr", 2.35*g/cm3, 5); 
  perovskiteBr->AddElement(nist->FindOrBuildElement("C"), 16); 
  perovskiteBr->AddElement(nist->FindOrBuildElement("H"), 24);
  perovskiteBr->AddElement(nist->FindOrBuildElement("N"), 2);
  perovskiteBr->AddElement(nist->FindOrBuildElement("Pb"), 1);
  perovskiteBr->AddElement(nist->FindOrBuildElement("Br"), 4); 

  //scintillator from LNL example code
  scintillator = new G4Material("scintillator", 1.06*g/cm3, 4);
  scintillator-> AddElement(nist->FindOrBuildElement("C"), 62.1 * perCent); 
  scintillator-> AddElement(nist->FindOrBuildElement("H"),  6.4 * perCent);
  scintillator-> AddElement(nist->FindOrBuildElement("O"), 20.8 * perCent);
  scintillator-> AddElement(nist->FindOrBuildElement("Si"), 10.7 * perCent);   

  const G4int nEntries = 5;
  G4double PhotonEnergy[nEntries] = {
      2.00*eV,   // ~620 nm
      2.48*eV,   // ~500 nm
      2.88*eV,   // ~430 nm (Peak Emission)
      3.10*eV,   // ~400 nm
      3.50*eV    // ~354 nm (UV edge)
  };
  
  // Refractive Index (LNL high-phenyl matrices sit around 1.50 - 1.53)
  G4double RefractiveIndex[nEntries] = {1.50, 1.51, 1.52, 1.53, 1.55};
  // Absorption Length (Highly transparent matrix, slightly decreases in UV)
  G4double AbsorptionLength[nEntries] = {5.0*m, 4.5*m, 4.0*m, 2.0*m, 0.1*m};
  // Scintillation Emission Spectrum (Relative intensity peaked around 420-430 nm due to dPOPOP)
  G4double ScintillationSpectrum[nEntries] = {0.01, 0.15, 1.00, 0.40, 0.00};

  G4MaterialPropertiesTable* MPT = new G4MaterialPropertiesTable();
  MPT->AddProperty("RINDEX", PhotonEnergy, RefractiveIndex, nEntries);
  MPT->AddProperty("ABSLENGTH", PhotonEnergy, AbsorptionLength, nEntries);   
  // Set Scintillation component spectrum
  MPT->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy, ScintillationSpectrum, nEntries);   
  // Constant parameters
  // Light Yield: LNL scintillators show ~45-55% of EJ-212 (~4500 photons/MeV)
  MPT->AddConstProperty("SCINTILLATIONYIELD", 4500. / MeV); 
  MPT->AddConstProperty("RESOLUTIONSCALE", 1.0);
  // Fast Decay Time (typical value: ~2.7 ns)
  MPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 2.7 * ns);
  MPT->AddConstProperty("SCINTILLATIONYIELD1", 1.0); // 100% of light allocated to component 1

  // Attach the property table scintillator material
  scintillator->SetMaterialPropertiesTable(MPT);

}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  
  G4bool checkOverlaps = true;
  //
  // World
  //
  
  G4double world_sizeX = 4. * cm; 
  G4double world_sizeY = 3. * cm; 
  G4double world_sizeZ = 5. * cm;

  solidWorld =
    new G4Box("World",  // its name
              0.5 * world_sizeX, 0.5 * world_sizeY, 0.5 * world_sizeZ);  // its size

  logicWorld = new G4LogicalVolume(solidWorld,  // its solid
                                    air,  // its material
                                    "logicWorld");  // its name

  physWorld = new G4PVPlacement(nullptr,  // no rotation
                                     G4ThreeVector(),  // at (0,0,0)
                                     logicWorld,  // its logical volume
                                     "physicalWorld",  // its name
                                     nullptr,  // its mother  volume
                                     false,  // no boolean operation
                                     0,  // copy number
                                     checkOverlaps);  // overlaps checking

  // do not draw world volume
  auto invisible = new G4VisAttributes(G4VisAttributes::GetInvisible());
  logicWorld->SetVisAttributes(invisible);

  //
  // Pero2D Layer
  // 
  G4double peroLayer_sizeX = 3 * cm;
  G4ThreeVector peroLayer_pos = G4ThreeVector(0, 0, 0);
  G4cout<<" *** Pero Layer thickness is "<<layerThickness<<" mm"<<G4endl;

  solidPeroLayer =
    new G4Box("PeroLayer",  // its name
              0.5 * peroLayer_sizeX , 0.5 * layerDriftLenght , 0.5 * layerThickness );   // its size

  
  // select perovskite flavor
  if(flavorBr){
    G4cout<<" *** Simulating Br Perovskite "<<G4endl;
    logicPeroLayer = new G4LogicalVolume(solidPeroLayer,  // its solid
                                          perovskiteBr,  // its material
                                          "PeroLayer");  // its name
  }
  else{
    G4cout<<" *** Simulating I Perovskite "<<G4endl;
    logicPeroLayer = new G4LogicalVolume(solidPeroLayer,  // its solid
                                          perovskiteI,  // its material
                                          "PeroLayer");  // its name
  }  
  
  physPeroLayer = new G4PVPlacement(nullptr,  // no rotation
                    peroLayer_pos,  // at position
                    logicPeroLayer,  // its logical volume
                    "PeroLayer",  // its name
                    logicWorld,  // its mother  volume
                    false,  // no boolean operation
                    0,  // copy number
                    checkOverlaps);  // overlaps checking

  // User Limits for tracking
  // Sets a max step length in the Pero2D region, with G4StepLimiter
  G4double maxStep = 0.07 * layerThickness;
  fStepLimit = new G4UserLimits(maxStep);
  logicPeroLayer->SetUserLimits(fStepLimit);                   
  // Visualization attributes
  G4VisAttributes pero2DVisAtt(G4Colour::Yellow());
  logicPeroLayer->SetVisAttributes(pero2DVisAtt);
  // Set pero2D layer as scoring volume
  fScoringPero2DVolume = logicPeroLayer;

  //
  // electrodes
  // 

  if(electrodeExists) {
    G4cout<<" *** Including electrodes in simulation "<<G4endl;
    G4double electrode_sizeX = peroLayer_sizeX;  
    G4double electrode_sizeY = electrodeSizeY;

    solidElectrode = new G4Box("Electrode",  // its name
              0.5 * electrode_sizeX , 0.5 * electrode_sizeY , 0.5 * layerThickness );   // its size
    logicElectrode = new G4LogicalVolume(solidElectrode,  // its solid
                                            electrodeMaterial,  // its material
                                            "Electrode");  // its name
    G4ThreeVector electrode_pos1 = G4ThreeVector(0, 0.5*(electrode_sizeY + layerDriftLenght), 0);
    G4ThreeVector electrode_pos2 = G4ThreeVector(0, -0.5*(electrode_sizeY + layerDriftLenght), 0);
    physElectrode = new G4PVPlacement(nullptr,  // no rotation
                    electrode_pos1,  // at position
                    logicElectrode,  // its logical volume
                    "Electrode",  // its name
                    logicWorld,  // its mother  volume
                    false,  // no boolean operation
                    0,  // copy number
                    checkOverlaps);  // overlaps checking
    physElectrode = new G4PVPlacement(nullptr,  // no rotation
                    electrode_pos2,  // at position
                    logicElectrode,  // its logical volume
                    "Electrode",  // its name
                    logicWorld,  // its mother  volume
                    false,  // no boolean operation
                    1,  // copy number
                    checkOverlaps);  // overlaps checking 

    // Visualization attributes
    G4VisAttributes electrodeVisAtt(G4Colour::Red());
    logicElectrode->SetVisAttributes(electrodeVisAtt);
 
  }
  else{
     G4cout<<" *** Gold electrodes not included in simulation "<<G4endl;
  }
                  
  //kapton foil 
  if (foilExists){
    G4cout<<" *** Including kapton foil in simulation "<<G4endl;
    G4double kaptonFoil_sizeZ = foilThickness;
    solidKaptonFoil = new G4Box("kaptonFoil",  // its name
              0.5 * world_sizeX , 0.5 * world_sizeY , 0.5 * kaptonFoil_sizeZ );   // its size
  
    logicKaptonFoil = new G4LogicalVolume(solidKaptonFoil,  // its solid
                                        foilMaterial,  // its material
                                        "Foil");  // its name

    G4ThreeVector foil_pos = G4ThreeVector(0, 0, 0.5*(layerThickness + foilThickness));
    physKaptonFoil = new G4PVPlacement(nullptr,  // no rotation
                    foil_pos,  // at position
                    logicKaptonFoil,  // its logical volume
                    "kaptonFoil",  // its name
                    logicWorld,  // its mother  volume
                    false,  // no boolean operation
                    0,  // copy number
                    checkOverlaps);  // overlaps checking
  }
  else{
     G4cout<<" *** kapton foil not included in simulation "<<G4endl;
  }

  //scintillator
  if (scintExists){
    G4cout<<" *** Including scintillator in simulation "<<G4endl;
    G4double scint_sizeZ = scintThickness;
    G4double scint_sizeX = peroLayer_sizeX ;
    G4double scint_sizeY = layerDriftLenght + 2 *  electrodeSizeY ;
    
    solidScint = new G4Box("scintillator", // its name
                 0.5 * scint_sizeX , 0.5 * scint_sizeY , 0.5 * scint_sizeZ );   // its size
    
    logicScint = new G4LogicalVolume(solidScint, // its solid
                                     scintillator, // its material
                                     "PolyScint"); // its name
    
    G4ThreeVector scint_pos = G4ThreeVector(0, 0, -0.5*(layerThickness + scintThickness));
    physScint = new G4PVPlacement(nullptr,  // no rotation
                scint_pos,  // at position
                logicScint,  // its logical volume
                "PolyScint",  // its name
                logicWorld,  // its mother  volume
                false,  // no boolean operation
                0,  // copy number
                checkOverlaps);  // overlaps checking

    G4VisAttributes scintVisAtt(G4Colour::Blue());
    logicScint->SetVisAttributes(scintVisAtt);
    fScoringScintVolume = logicScint;
  }
  else{
     G4cout<<" *** scintillator not included in simulation "<<G4endl;
  }

  G4cout<<" #############################################  DETECTOR CONSTRUCTION DONE"<<G4endl;
  // always return the physical World
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace Pero2D
