#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class CosmicBody {
protected:
    char name[20];
    double mass;

public:
    CosmicBody(const char* n, double m) : mass(m) {
        int i = 0;
        while (n[i] != '\0' && i < 19) {
            name[i] = n[i];
            i++;
        }
        name[i] = '\0';
    }

    virtual void displayInfo() const = 0; 
    virtual ~CosmicBody() {}
};

class SphericalBody : public CosmicBody {
protected:
    double diameter;

public:
    SphericalBody(const char* n, double m, double d)
        : CosmicBody(n, m), diameter(d) {}

    void displayInfo() const override {
        cout << "Name of spherical body: " << name
            << ", Mass: " << mass
            << " kg, Diameter: " << diameter << endl;
    }
};


class Planet : public SphericalBody {
private:

    double satellites[5];

public:
    Planet() : SphericalBody("", 0, 0) {
        for (int i = 0; i < 5; ++i) {
            satellites[i] = 0;
        }
       
    }

    Planet(const char* n, double m, double d, double s[5])
        : SphericalBody(n, m, d) {
        for (int i = 0; i < 5; ++i) {
            satellites[i] = s[i];
        }
       
    }


    ~Planet() {
        cout << "\nDestructor called for: " << name << endl;
    }

   

    void displayInfo() const override {
        cout << "Planet: " << name
            << ", Mass: " << mass
            << " kg, Diameter: " << diameter;
        for (int i = 0; i < 5; ++i) {
            cout << "Satellite " << i + 1 << " at distance: " << satellites[i] << " km.\n";
        }
    }

};



class GasGiant : public Planet {
private:
    double hydrogenPercentage;

public:
    GasGiant(const char* n, double m, double d, double s[5], double h)
        : Planet(n, m, d,  s), hydrogenPercentage(h) {}

    void displayInfo() const override {
        Planet::displayInfo();
        cout << "Hydrogen Content: " << hydrogenPercentage << "%\n";
    }
};

class TerrestrialPlanet : protected Planet {
private:
    bool hasLife;

public:
    TerrestrialPlanet(const char* n, double m, double d, double s[5], bool life)
        : Planet(n, m, d, s), hasLife(life) {}

    void displayInfo() const override {
        Planet::displayInfo();
        cout << "Life Presence: " << (hasLife ? "Yes" : "No") << "\n";
    }
};


void showCosmicInfo(const CosmicBody* body) {
    body->displayInfo();
}

int main() {
    cout << "=== Demonstrating Class Hierarchy ===\n";

    double marsSatellites[5] = { 4879, 6789, 1500, 2200, 3300 };
    Planet mars("Mars", 6.417e23, 227.9, marsSatellites);
    mars.displayInfo();

    double jupiterSatellites[5] = { 778500, 1072000, 1340000, 1850000, 2100000 };
    GasGiant jupiter("Jupiter", 1.898e27, 778.5, jupiterSatellites, 89.8);
    jupiter.displayInfo();

    double earthSatellites[5] = { 985734, 38439843, 1340, 1850, 210 };
    TerrestrialPlanet earth("Earth", 5.972e24, 149.6, marsSatellites, true);
    earth.displayInfo();

    cout << "\n=== Demonstrating Polymorphic Function ===\n";
    showCosmicInfo(&mars);
    showCosmicInfo(&jupiter);


    return 0;
}
