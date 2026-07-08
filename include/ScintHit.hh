
/// \file ScintHit.hh
/// \brief Definition of the Scint Hit class

#pragma once

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class ScintHit : public G4VHit
{
 public:
  ScintHit();
  ~ScintHit() = default;
  ScintHit(const ScintHit&);
  const ScintHit& operator=(const ScintHit&);
  G4bool operator==(const ScintHit&) const;
  inline void* operator new(size_t);
  inline void operator delete(void*);
  void Draw() final;
  inline void Print() final
  {
    G4cout << "Scint Hit  id:  " << fid << " Edep: " << fEdep
           << " em_Edep: " << fem_Edep << " time: " << ftime
           << " X: " << fposition.getX() << " Y: " << fposition.getY()
           << " Z: " << fposition.getZ() << G4endl;
  }
  ScintHit(unsigned int i, G4double e, G4double em, G4double t,
                 G4ThreeVector p);
  inline void SetPosition(G4ThreeVector position) { fposition = position; };
  inline G4ThreeVector GetPosition() const { return fposition; };
  inline void SetTime(G4double time) { ftime = time; };
  inline G4double GetTime() const { return ftime; };
  inline void SetId(unsigned int id) { fid = id; };
  inline unsigned int GetId() const { return fid; };
  inline void SetEdep(G4double Edep) { fEdep = Edep; };
  inline G4double GetEdep() const { return fEdep; };
  inline void Setem_Edep(G4double em_Edep) { fem_Edep = em_Edep; };
  inline G4double Getem_Edep() const { return fem_Edep; };

 private:
  unsigned int fid{ 0 };
  G4double fEdep{ 0 };
  G4double fem_Edep{ 0 };
  G4double ftime{ 0 };
  G4ThreeVector fposition{ 0, 0, 0 };
};

using ScintHitsCollection = G4THitsCollection<ScintHit>;
extern G4ThreadLocal G4Allocator<ScintHit>* ScintHitAllocator;

inline void* ScintHit::operator new(size_t)
{
  if(!ScintHitAllocator)
  {
    ScintHitAllocator = new G4Allocator<ScintHit>;
  }
  return (void*) ScintHitAllocator->MallocSingle();
}

inline void ScintHit::operator delete(void* aHit)
{
  ScintHitAllocator->FreeSingle((ScintHit*) aHit);
}
