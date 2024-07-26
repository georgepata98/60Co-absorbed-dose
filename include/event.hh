#ifndef EVENT_HH
#define EVENT_HH

#include "G4SystemOfUnits.hh"
#include "G4UserEventAction.hh"
#include "G4AnalysisManager.hh"
#include "G4GenericAnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4THitsMap.hh"

#include "run.hh"

#include <iostream>
#include <fstream>
#include <cmath>

class MyEventAction : public G4UserEventAction
{
public:
    MyEventAction(MyRunAction* runAction);
    ~MyEventAction();

    virtual void BeginOfEventAction(const G4Event *event);
    virtual void EndOfEventAction(const G4Event *event);

private:
    G4THitsMap<G4double>* GetHitsCollection(G4int hcID, const G4Event *event) const;  //HitsMap created by the MultiFunctionalDetector
    G4double GetSum(G4THitsMap<G4double>* hitsMap) const;

    MyRunAction* fRunAction = nullptr;
    G4int fAbsoDdepHCID = -1;

    std::ofstream* fOutputFile;

    G4double sum = 0;
};

#endif
