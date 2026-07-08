// trick to not include multiple times
#ifndef Pero2DPhysicsList_h
#define Pero2DPhysicsList_h 1

#include "G4VModularPhysicsList.hh"

namespace Pero2D
{

class PhysicsList : public G4VModularPhysicsList
{
public:
	PhysicsList();
	~PhysicsList() override = default;

	void SetCuts() override;
};

}  // namespace Pero2D

#endif
