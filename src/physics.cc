#include "physics.hh"

MyPhysicsList::MyPhysicsList()
:G4VModularPhysicsList(),
fEm(nullptr)
{
    SetVerboseLevel(0);
    G4EmParameters::Instance();

    fEm = new G4EmLivermorePhysics(0);
    RegisterPhysics(fEm);
}

MyPhysicsList::~MyPhysicsList()
{}