//
#include "PrimaryGeneratorAction.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4RootAnalysisManager.hh"


namespace Pero2D
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);
  fParticleGPS = new G4GeneralParticleSource();

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName = "gamma");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
  
  //default to 241 Americium
  fParticleGun->SetParticleEnergy(59.54 * keV);

  fMessengerParticleSource = new G4GenericMessenger(this, "/particleSource/", "Particle source generator");
	fMessengerParticleSource->DeclareProperty("sourceType", sourceType, "gun or gps");
	sourceType = "gun";
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fParticleGPS;;
  delete fMessengerParticleSource;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
  // this function is called at the begining of ecah event
  // In order to avoid dependence of PrimaryGeneratorAction
  G4double peroLayerSizeX = 0;
  G4double peroLayerSizeY = 0;
  G4double peroLayerSizeZ = 0;
  if (!fPero2DBox) {
    G4LogicalVolume* envLV = G4LogicalVolumeStore::GetInstance()->GetVolume("PeroLayer");
    if (envLV) fPero2DBox = dynamic_cast<G4Box*>(envLV->GetSolid());
  }
  if (fPero2DBox) {
    peroLayerSizeX = fPero2DBox->GetXHalfLength() * 2.;
    peroLayerSizeY = fPero2DBox->GetYHalfLength() * 2.;
    peroLayerSizeZ = fPero2DBox->GetZHalfLength() * 2.;
  }
  else {
    G4ExceptionDescription msg;
    msg << "Envelope volume of box shape not found.\n";
    msg << "Perhaps the geometry changed.\n";
    msg << "The gun will be placed at the center.";
    G4Exception("PrimaryGeneratorAction::GeneratePrimaries()", "Pero2D", JustWarning, msg);
  }

  // now use either particle gun or generic particle source according to messenger

  auto man = G4RootAnalysisManager::Instance();
  
  if (sourceType == "gun" ){
    // gamma are randomly distributed in front of the perovskite + elecrode assembly
    G4double size = 0.99;
    G4double x0 = size * peroLayerSizeX * (G4UniformRand() - 0.5);
    //G4double y0 = size * (peroLayerSizeY + 1 * mm ) * (G4UniformRand() - 0.5);
    G4double y0 = size * peroLayerSizeY * (G4UniformRand() - 0.5);
    G4double z0 = - 1.5 * cm;   
    fParticleGun->SetParticlePosition(G4ThreeVector(x0, y0, z0));
    fParticleGun->GeneratePrimaryVertex(event);
    G4double E = fParticleGun->GetParticleEnergy();
    man ->FillNtupleDColumn(0, 0, E);
    man ->FillNtupleDColumn(0, 1, x0);
    man ->FillNtupleDColumn(0, 2, y0);
    man ->FillNtupleDColumn(0, 3, z0);
    man->AddNtupleRow(0);
  }
  else if (sourceType == "gps") {
    //Use source 
    fParticleGPS->GeneratePrimaryVertex(event);
		//SaveVertexPosition(fParticleGPS->GetParticlePosition());
		//SavePrimaryEnergy(fParticleGPS->GetParticleEnergy());

  }
  
}
void PrimaryGeneratorAction::SavePrimaryEnergy(G4double energy)
{
	//G4AnalysisManager *man = G4AnalysisManager::Instance();
	//man->FillNtupleDColumn(Tuples::kGeneration, TGeneration::kEini, energy / keV); // [keV]
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace Pero2D
