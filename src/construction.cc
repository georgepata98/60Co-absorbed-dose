#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    return DefineVolumes();
}

G4VPhysicalVolume *MyDetectorConstruction::DefineVolumes()
{
    //variables declaration
    G4Tubs *solidSource[5];
    G4LogicalVolume *logicSource[5];
    G4VPhysicalVolume *physSource[5];


    //materials
    G4NistManager *nist = G4NistManager::Instance();

    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

    G4Element *C = nist->FindOrBuildElement("C");
    G4Element *Mn = nist->FindOrBuildElement("Mn");
    G4Element *P = nist->FindOrBuildElement("P");
    G4Element *S = nist->FindOrBuildElement("S");
    G4Element *Si = nist->FindOrBuildElement("Si");
    G4Element *Cr = nist->FindOrBuildElement("Cr");
    G4Element *Ni = nist->FindOrBuildElement("Ni");
    G4Element *Fe = nist->FindOrBuildElement("Fe");

    G4Material *steelMat = new G4Material("steelMat", 8.03*g/cm3, 8);  //steel-304
    steelMat->AddElement(C, .08*perCent);
    steelMat->AddElement(Mn, 2.*perCent);
    steelMat->AddElement(P, .045*perCent);
    steelMat->AddElement(S, .03*perCent);
    steelMat->AddElement(Si, 1.*perCent);
    steelMat->AddElement(Cr, 19.*perCent);
    steelMat->AddElement(Ni, 9.5*perCent);
    steelMat->AddElement(Fe, 68.345*perCent);

    G4Material *CoMat = nist->FindOrBuildMaterial("G4_Co");

    G4Element *H = nist->FindOrBuildElement("H");
    G4Element *O = nist->FindOrBuildElement("O");

    G4Material *PMMA = new G4Material("PMMA", 1.19*g/cm3, 3);
    PMMA->AddElement(C, 5);
    PMMA->AddElement(H, 8);
    PMMA->AddElement(O, 2);

    G4Material *AlMat = nist->FindOrBuildMaterial("G4_Al");

    G4Material *CMat = nist->FindOrBuildMaterial("G4_C");


    //world
    G4Box *solidWorld = new G4Box("solidWorld", 1.25*m, 1.25*m, 1.25*m);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicWorld, "physWorld", 0, false, 0, true);


    //60Co source
    for(G4int i=0; i<5; i++)
    {
        solidSource[i] = new G4Tubs(("solidSource"+std::to_string(i)).c_str(), 0*mm, 10.*mm, 3.*mm, 0*deg, 360*deg);
        logicSource[i] = new G4LogicalVolume(solidSource[i], CoMat, ("logicSource"+std::to_string(i)).c_str());
        physSource[i] = new G4PVPlacement(0, G4ThreeVector(0, 0, (6.*i-12.)*mm), logicSource[i], ("physSource"+std::to_string(i)).c_str(), logicWorld, false, 0, true);
    }

    G4Tubs *solidCapsuleUp = new G4Tubs("solidCapsuleUp", 10.*mm, 11.7*mm, 1.6*mm, 0*deg, 360*deg);
    G4Tubs *solidCapsuleDown = new G4Tubs("solidCapsuleDown", 10.*mm, 11.7*mm, 1.6*mm, 0*deg, 360*deg);
    G4LogicalVolume *logicCapsuleUp = new G4LogicalVolume(solidCapsuleUp, steelMat, "logicCapsuleUp");
    G4LogicalVolume *logicCapsuleDown = new G4LogicalVolume(solidCapsuleDown, steelMat, "logicCapsuleDown");
    G4VPhysicalVolume *physCapsuleUp = new G4PVPlacement(0, G4ThreeVector(0, 0, 16.6*mm), logicCapsuleUp, "physCapsuleUp", logicWorld, false, 0, true);
    G4VPhysicalVolume *physCapsuleDown = new G4PVPlacement(0, G4ThreeVector(0, 0, -16.6*mm), logicCapsuleDown, "physCapsuleDown", logicWorld, false, 0, true);

    G4Tubs *solidCapsule = new G4Tubs("solidCapsule", 10.*mm, 11.7*mm, 15.*mm, 0*deg, 360*deg);
    G4LogicalVolume *logicCapsule = new G4LogicalVolume(solidCapsule, steelMat, "logicCapsule");
    G4VPhysicalVolume *physCapsule = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicCapsule, "physCapsule", logicWorld, false, 0, true);


    //dosimeter
    G4Tubs *solidElectrode = new G4Tubs("solidElectrode", 0*mm, .55*mm, 10.6*mm, 0*deg, 360*deg);
    G4LogicalVolume *logicElectrode = new G4LogicalVolume(solidElectrode, AlMat, "logicElectrode");
    G4VPhysicalVolume *physElectrode = new G4PVPlacement(0, G4ThreeVector(0, 0, 5*cm), logicElectrode, "physElectrode", logicWorld, false, 0, true);

    G4Tubs *solidGas = new G4Tubs("solidGas", .55*mm, 3.05*mm, 11.8*mm, 0*deg, 360*deg);
/*    G4LogicalVolume *logicGas = new G4LogicalVolume(solidGas, worldMat, "logicGas");  //volumul sensibil cu aer al detectorului
    G4VPhysicalVolume *physGas = new G4PVPlacement(0, G4ThreeVector(0, 0, 5*cm), logicGas, "physGas", logicWorld, false, 0, true); */

    G4Tubs *solidGraphite = new G4Tubs("solidGraphite", 3.05*mm, 3.14*mm, 11.8*mm, 0*deg, 360*deg);
    G4LogicalVolume *logicGraphite = new G4LogicalVolume(solidGraphite, CMat, "logicGraphite");
    G4VPhysicalVolume *physGraphite = new G4PVPlacement(0, G4ThreeVector(0, 0, 5*cm), logicGraphite, "physGraphite", logicWorld, false, 0, true);

    G4Tubs *solidPMMA = new G4Tubs("solidPMMA", 3.14*mm, 3.475*mm, 11.8*mm, 0*deg, 360*deg);
    G4LogicalVolume *logicPMMA = new G4LogicalVolume(solidPMMA, PMMA, "logicPMMA");
    G4VPhysicalVolume *physPMMA = new G4PVPlacement(0, G4ThreeVector(0, 0, 5*cm), logicPMMA, "physPMMA", logicWorld, false, 0, true);


    G4MultiUnion *solidSD = new G4MultiUnion("solidSD");
    G4Tubs *solidGasUp = new G4Tubs("solidGasUp", 0*mm, .55*mm, .6*mm, 0*deg, 360*deg);
    G4Tubs *solidGasDown = new G4Tubs("solidGasDown", 0*mm, .55*mm, .6*mm, 0*deg, 360*deg);
    // + *solidGas creat mai sus
    G4RotationMatrix *rot = new G4RotationMatrix();
    G4Transform3D tr1 = G4Transform3D(*rot, G4ThreeVector(0, 0, -11.2*mm));  //solidGasUp transf
    G4Transform3D tr2 = G4Transform3D(*rot, G4ThreeVector(0, 0, 0));         //solidGas transf
    G4Transform3D tr3 = G4Transform3D(*rot, G4ThreeVector(0, 0, +11.2*mm));  //solidGasDown transf
    solidSD->AddNode(*solidGasUp, tr1);
    solidSD->AddNode(*solidGas, tr2);
    solidSD->AddNode(*solidGasDown, tr3);
    solidSD->Voxelize();
    G4LogicalVolume *logicSD = new G4LogicalVolume(solidSD, worldMat, "logicSD");
    G4VPhysicalVolume *physSD = new G4PVPlacement(0, G4ThreeVector(0, 0, 5*cm), logicSD, "physSD", logicWorld, false, 0, true);


    G4cout << G4endl <<  "--------------------------------------------------" << G4endl << "Active region mass (detector): " << logicSD->GetMass() / kg << " kg" << G4endl << "--------------------------------------------------" << G4endl;





    //visualization
    logicCapsule->SetVisAttributes(G4Colour::Gray());
    logicCapsuleUp->SetVisAttributes(G4Colour::Gray());
    logicCapsuleDown->SetVisAttributes(G4Colour::Gray());
    for(G4int i=0; i<5; i++)
    {
        logicSource[i]->SetVisAttributes(G4Colour::Yellow());
    }
    logicElectrode->SetVisAttributes(G4Colour::Green());
    logicSD->SetVisAttributes(G4Colour::Blue());
    logicGraphite->SetVisAttributes(G4Colour::Red());
    logicPMMA->SetVisAttributes(G4Colour::Red());


    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
    G4VPrimitiveScorer *primitive;
    G4MultiFunctionalDetector *doseDet;

    doseDet = new G4MultiFunctionalDetector("doseDet");
    G4SDManager::GetSDMpointer()->AddNewDetector(doseDet);

    primitive = new G4PSDoseDeposit("Ddep");
    doseDet->RegisterPrimitive(primitive);

    SetSensitiveDetector("logicSD", doseDet);
}
