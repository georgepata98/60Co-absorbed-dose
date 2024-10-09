#include <iostream>
#include <string>
#include <ctime>
#include <climits>

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4ScoringManager.hh"

#include "Randomize.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv)
{
    G4int nOfRuns = 1;  //Aici se modifica numarul de Run-uri, fiecare Run avand 2e9 evenimente
    G4bool visualization = true;  //Se seteaza: true = cu vizualizare si false = fara vizualizare (cand porneste loop-ul pe Run-uri)
    
    G4int visEvents = 10;  //Aici se modifica nr. de evenimente care se doreste vizualizat cu GUI
    G4int eventsPerRun = 2000000000;  //Aici se modifica nr. de evenimente per Run (2^31 - 1 maxim)

    /* Loop-ul cu Run-uri se executa numai cand visualization = false */


    //Initializarea simularii

    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    G4ScoringManager::GetScoringManager();

    G4UIExecutive *ui = nullptr;

    if(argc == 1)
    {
        ui = new G4UIExecutive(argc, argv);
    }

    G4RunManager *runManager = new G4RunManager();

    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());
    runManager->Initialize();

    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();

    if(ui)
    {
        if(visualization)
        {
            UImanager->ApplyCommand("/control/execute vis.mac");
            UImanager->ApplyCommand("/control/execute gps.mac");
            runManager->BeamOn(visEvents);

            ui->SessionStart();  //activare gui
        }
        if(!visualization) { UImanager->ApplyCommand("/control/execute gps.mac"); }
        delete ui;
    }
    else
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }


    //Loop-ul cu Run-urile

    if(!visualization)  //se executa loop-ul cu Run-uri cand visualization = false
    {
        for(G4int i=0; i<nOfRuns; ++i)
        {
            G4Random::setTheSeed(time(0) + i);
            runManager->BeamOn(eventsPerRun);

            std::this_thread::sleep_for(std::chrono::milliseconds(500));  //time-delay intre Run-uri pt. a ii da sistemului timp sa elibereze memoria
        }
    }
    

    delete visManager;
    delete runManager;

    return 0;
}
