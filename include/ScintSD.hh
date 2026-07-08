// ********************************************************************
//
/// \file ScintSD.hh

#pragma once

#include "G4VSensitiveDetector.hh"
#include "ScintHit.hh"
class G4Step;
class G4HCofThisEvent;

class ScintSD : public G4VSensitiveDetector
{
 public:
  ScintSD(G4String);
  ~ScintSD() = default;
  void Initialize(G4HCofThisEvent*) final;
  G4bool ProcessHits(G4Step*, G4TouchableHistory*) final;
  void EndOfEvent(G4HCofThisEvent* hitCollection) final;

 private:
  ScintHitsCollection* fScintHitsCollection{ nullptr };
  G4int fHCID;
  G4bool verbose{ false };
};