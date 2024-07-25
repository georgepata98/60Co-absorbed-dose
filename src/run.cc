#include "run.hh"

MyRunAction::MyRunAction()
{
    G4RunManager::GetRunManager()->SetPrintProgress(0);

    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->RegisterAccumulable(totalDose);
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Reset();

    G4RunManager::GetRunManager()->SetRandomNumberStore(false);
}

void MyRunAction::EndOfRunAction(const G4Run* run)
{
    G4int nOfEvents = run->GetNumberOfEvent();
    if(nOfEvents == 0) return;
    
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Merge();

    G4cout << G4endl << "--------------------------------------------------" << G4endl << "Number of primary events: " << nOfEvents << G4endl << "Total absorbed dose: " << G4BestUnit(totalDose.GetValue(), "Dose") << G4endl << "--------------------------------------------------" << G4endl << G4endl;
}