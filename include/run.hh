#ifndef RUN_HH
#define RUN_HH

#include "G4SystemOfUnits.hh"
#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4Accumulable.hh"
#include "G4AccumulableManager.hh"

class MyRunAction : public G4UserRunAction
{
public:
    MyRunAction();
    ~MyRunAction();

    virtual void BeginOfRunAction(const G4Run* run);
    virtual void EndOfRunAction(const G4Run* run);

    void AddDdep(G4double dose) { totalDose += dose; }

private:
    G4Accumulable<G4double> totalDose = 0;
};

#endif