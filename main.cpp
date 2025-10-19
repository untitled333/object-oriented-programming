#include "Planet.h"

int main() {

    Planet::setcount(0);

    Planet planet1;
    planet1.printPlanetInfo();

    double dist[5] = { 489657894, 4897654, 4906, 8976948376, 8947584 };
    Planet* planetPtr = new Planet("Mars", 6779.0, dist);
    planetPtr->printPlanetInfo();

    dist[1] = 7867865;
    planet1.setSatellites(dist);
    planet1.setDiameter(12000.0);
    cout << "\nChanged Mars(to show how setters work):";
    planet1.printPlanetInfo();

    double dist1[5] = { 553728389, 7776948376, 77777584, 111111, 2222222 };
    Planet* dynamicPlanet = new Planet("Jupiter", 139820.0, dist1);
    cout<<""<<dynamicPlanet->satellitesB(2);
    dynamicPlanet->printPlanetInfo();


    cout << "\nCount of planets: " << Planet::GetCount();
    delete dynamicPlanet;
    cout << "Count of planets now: " << Planet::GetCount()<<"\n";

    double dist2[5] = { 11111111, 2222222, 3333, 4444, 5555555 };
    Planet* planet3 = new Planet("Venus", 12105.0, dist2);
    cout << *planet3;

    double dist3[5] = { 487, 2275, 8547, 6868, 934853 };
    Planet* planet4 = new Planet("Saturn", 116460.0, dist3);
    cout << *planet4;

    Planet loadedPlanet;
    ifstream inFile("pl1.txt");
    if (inFile) {
        inFile >> loadedPlanet;
        inFile.close();
        cout << "\nPlanet loaded from pl1.txt file:\n" << loadedPlanet;
    }
    else {
        cout << "Error opening file pl1.txt for reading.\n";
    }

    Planet userPlanet;
    cout << "\nLets create a new planet!:)\n";
    cin >> userPlanet;

    ofstream outFile("pl2.txt");
    if (outFile) {
        outFile << userPlanet;
        outFile.close();
        cout << "Planet information saved to pl2.txt.\n";
    }
    else {
        cout << "Error opening file pl2.txt for writing.\n";
    }
   
    Planet* planets[] = { planetPtr, dynamicPlanet, planet3, planet4 };
    int size = sizeof(planets) / sizeof(planets[0]);

    int choice1, choice2;
    cout << "\nSelect two planets to compare:\n";
    cout << "1.Mars\n2.Jupiter\n3.Saturn\n4.Venus\n";
    cout << "Choose number of the first planet: ";
    cin >> choice1;
    cout << "Choose number of the second planet: ";
    cin >> choice2;

    if (choice1 < 1 || choice1 > size || choice2 < 1 || choice2 > size) {
        cout << "Invalid choice! Please enter valid planet numbers.\n";
        return 0;
    }
   
    Planet* selectedPlanet1 = planets[choice1 - 1];
    Planet* selectedPlanet2 = planets[choice2 - 1];

    int choice;
    cout << "\nWhat do you want to compare?\n";
    cout << "1.Diameter\n2.Satellites distances\n";
    cout << "Enter your choice: ";
    cin >> choice;
    
    switch (choice) {
    case 1:
   
        if (* selectedPlanet1 < *selectedPlanet2) {
            cout << selectedPlanet1->name << " has a smaller diameter than " << selectedPlanet2->name << ".\n";
        }
        else if (*selectedPlanet1 > *selectedPlanet2) {
            cout << selectedPlanet1->name << " has a larger diameter than " << selectedPlanet2->name << ".\n";
        }
        else {
            cout << selectedPlanet1->name << " and " << selectedPlanet2->name << " have the same diameter.\n";
        }
        break;

    case 2:
    
        selectedPlanet1->compareSatellites(*selectedPlanet2);
        break;

    default:
        cout << "Invalid choice.\n";
        break;
    }

    return 0;
}
