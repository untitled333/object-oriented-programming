#include <iostream>
#include <string>


using namespace std;


class IAutoNumbering {

public:

    virtual int getCurrentNumber() const = 0;
    virtual int getTotalCount() const = 0;
    virtual ~IAutoNumbering() = default;

};




class IConvertible {

public:

    virtual std::string toString() const = 0;
    virtual void fromString() = 0;  
    virtual ~IConvertible() = default;

};




class CosmicBody {

protected:

    char name[20];
    double mass;

public:

    CosmicBody(const char* n = "", double m = 0) : mass(m) {
        int i = 0;
        while (n[i] != '\0' && i < 19) {
            name[i] = n[i];
            i++;
        }
        name[i] = '\0';
    }

    const char* getName() const {
        return name;
    }


    virtual void displayInfo() const = 0;
    virtual ~CosmicBody() {}

};




class GasGiant : virtual public CosmicBody {

protected:

    double hydrogenProcent;

public:

    GasGiant(double h = 0) : hydrogenProcent(h) {}

};




class TerrestrialPlanet : virtual public CosmicBody {

protected:

    bool hasLife;

public:

    TerrestrialPlanet(bool life = false) : hasLife(life) {}

};




class PlanetWithSatellites : virtual public CosmicBody {

protected:

    double diameter;
    double satellites[5];

public:

    PlanetWithSatellites(double d = 0, const double s[5] = nullptr) : diameter(d) {
        for (int i = 0; i < 5; ++i) {
            satellites[i] = (s ? s[i] : 0);
        }
    }

};




class Planet : public GasGiant, public TerrestrialPlanet, public PlanetWithSatellites, public IAutoNumbering, public IConvertible {

private:

    static int totalCount;  
    int currentNumber;      

public:

    
    Planet(const char* n, double m, double d, const double s[5], double h, bool life)
        : CosmicBody(n, m),
        GasGiant(h),
        TerrestrialPlanet(life),
        PlanetWithSatellites(d, s),
        currentNumber(++totalCount) {}

    
    Planet()
        : CosmicBody("", 0),
        GasGiant(0),
        TerrestrialPlanet(false),
        PlanetWithSatellites(0, nullptr),
        currentNumber(0) {}  Planet(bool incrementCounter = true)
        : CosmicBody("", 0),
        GasGiant(0),
        TerrestrialPlanet(false),
        PlanetWithSatellites(0, nullptr),
        currentNumber(0) {
        if (incrementCounter) {
            currentNumber = ++totalCount;
        }
    } 


    void displayInfo() const override {
        cout << "\nPlanet number: " << currentNumber << endl;
        cout << "Planet name: " << name << endl;
        cout << "Mass: " << mass << " kg" << endl;
        cout << "Diameter: " << diameter << " km" << endl;
        cout << "Hydrogen content: " << hydrogenProcent << "%" << endl;
        cout << "Life presence: " << (hasLife ? "Yes" : "No") << endl;
        for (int i = 0; i < 5; ++i) {
            cout << "Satellite " << i + 1 << " at distance: " << satellites[i] << " km\n";
        }
    }

    int getCurrentNumber() const override {
        return currentNumber;
    }

    int getTotalCount() const override {
        return totalCount;
    }

    string toString() const override {
        return "Planet name: " + string(name) + ", Mass: " + to_string(mass) + ", Diameter: " + to_string(diameter);
    }

    void fromString() override {
        cout << "Enter planet name: ";
        cin.getline(name, 20);

        cout << "Enter mass of the planet (in kg): ";
        cin >> mass;

        cout << "Enter diameter of the planet (in km): ";
        cin >> diameter;

        cout << "Enter hydrogen content percentage: ";
        cin >> hydrogenProcent;

        cout << "Does the planet have life? (1 for Yes, 0 for No): ";
        cin >> hasLife;

        cout << "Enter distances to the 5 satellites (in km): ";
        for (int i = 0; i < 5; ++i) {
            cin >> satellites[i];
        }

       
        currentNumber = ++totalCount;
        cin.ignore(); 
    }

    ~Planet() {
        cout << "\nDestructor called for: " << name << endl;
    }

    static int getTotalObjectsCount() {
        return totalCount;
    }
};




int Planet::totalCount = 0;




void sortByNumber(IAutoNumbering* arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1 - i; ++j) {
            if (arr[j]->getCurrentNumber() > arr[j + 1]->getCurrentNumber()) {
                IAutoNumbering* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void outputInfo(const IConvertible& obj) {
    cout << obj.toString() << endl;
}

void inputInfo(IConvertible& obj) {
    obj.fromString(); 
}




int main() {

    double earthSat[5] = { 10000, 20000, 15000, 25000, 30000 };
    double marsSat[5] = { 11000, 21000, 16000, 24000, 28000 };

    Planet earth("Earth", 5.97e24, 12742, earthSat, 0.1, true);
    Planet mars("Mars", 0.64e24, 6779, marsSat, 0.05, false);

    earth.displayInfo();
    mars.displayInfo();

    Planet* planets[2] = { &earth, &mars };
    sortByNumber(reinterpret_cast<IAutoNumbering**>(planets), 2);

    cout << "\nAfter sorting by numbers and planet names:" << endl;
    for (int i = 0; i < 2; ++i) {
        cout << "Planet number: " << planets[i]->getCurrentNumber()
            << ", Name: " << planets[i]->getName() << endl;
    }


    cout << "\nPlanet info using outputInfo function: ";
    outputInfo(earth);
    outputInfo(mars);

    cout << "\nInput data for a new planet:\n";
    Planet newPlanet(false);
    inputInfo(newPlanet);
    newPlanet.displayInfo();

    cout << "\nTotal number of Planet objects created: " << Planet::getTotalObjectsCount() << endl;

    return 0;
}