#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4SystemOfUnits.hh"
#include "G4VModularPhysicsList.hh"
#include "G4VPhysicsConstructor.hh"
#include "G4EmParameters.hh"
#include "G4ParticleDefinition.hh"

#include "G4EmLivermorePhysics.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmPenelopePhysics.hh"

class MyPhysicsList : public G4VModularPhysicsList
{
public:
    MyPhysicsList();
    ~MyPhysicsList() override;

private:
    G4VPhysicsConstructor *fEm;
};

#endif