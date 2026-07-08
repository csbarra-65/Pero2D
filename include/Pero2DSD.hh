// ********************************************************************
//
/// \file Pero2DSD.hh

#pragma once

#include "G4VSensitiveDetector.hh"
#include "Pero2DHit.hh"
class G4Step;
class G4HCofThisEvent;

class Pero2DSD : public G4VSensitiveDetector
{
 public:
  Pero2DSD(G4String);
  ~Pero2DSD() = default;
  void Initialize(G4HCofThisEvent*) final;
  G4bool ProcessHits(G4Step*, G4TouchableHistory*) final;
  void EndOfEvent(G4HCofThisEvent* hitCollection) final;

 private:
  Pero2DHitsCollection* fPero2DHitsCollection{ nullptr };
  G4int fHCID;
  G4bool verbose{ false };
};
