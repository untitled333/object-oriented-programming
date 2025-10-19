#include "Planet.h"

int Planet::count = 0;

Planet::Planet() {
    name[0] = '\0';
    diameter = 0.0;
    for (int i = 0; i < 5; ++i) {
        satellites[i] = 0;
    }
    count++;
}

Planet::Planet(const char* n, double d, double dist[]) {
    int i = 0;
    while (n[i] != '\0' && i < 14) {
        name[i] = n[i];
        i++;
    }
    name[i] = '\0';

    diameter = d;
    for (i = 0; i < 5; ++i) {
        satellites[i] = dist[i];
    }

    cout << "\nConstructor with parameters called for: " << name << endl;
    count++;
}

Planet::Planet(const Planet& other) {
    int i = 0;
    while (other.name[i] != '\0' && i < 14) {
        name[i] = other.name[i];
        i++;
    }
    name[i] = '\0';

    diameter = other.diameter;
    for (i = 0; i < 5; ++i) {
        satellites[i] = other.satellites[i];
    }
    cout << "\nCopy constructor called for: " << name << endl;
    count++;
}

Planet::~Planet() {
    cout << "\nDestructor called for: " << name << endl;
    count--;
}

int Planet::GetCount() {
    return count;
}

void Planet::setcount(int count) {
    Planet::count = count;
}


double* Planet::getSatellites() const {
    double* arr = new double[5];
    for (int i = 0; i < 5; ++i) {
        arr[i] = satellites[i];
    }
    return arr;
}

void Planet::setSatellites(double s[]) {
    for (int i = 0; i < 5; ++i) {
        this->satellites[i] = s[i];
    }
}

double Planet::getDistance() const {
    return 5;
}

double Planet::getDiameter() const {
    return diameter;
}

void Planet::setDiameter(double d) {
    this->diameter = d;
}

double Planet::satellitesB(int number) {
    return satellites[number];
}

int Planet::satellitesB(double distance) {
    return findIndex(satellites, 5, distance);
}

int Planet::findIndex(double arr[], int size, double value) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

void Planet::satellitesB(int number, double distance) {
    satellites[number] = distance;
}

void Planet::printPlanetInfo() const {
        cout << fixed << setprecision(2);
        cout << "\nPlanet Name: " << name << endl;
        cout << "Diameter: " << diameter << " km" << endl;
        for (int i = 0; i < 5; ++i) {
            cout << "Satellite " << i + 1 << " distance: " << satellites[i] << " km" << endl;
        }
    }

ostream& operator<<(ostream& os, const Planet& p) {
    os << fixed << setprecision(2);
    os << "Planet Name: " << p.name << "\n";
    os << "Diameter: " << p.diameter << " km\n";
    os << "Satellites distances:\n";
    for (int i = 0; i < 5; ++i) {
        os << "Satellite " << i + 1 << ": " << p.satellites[i] << " km\n";
    }
    return os;
}

istream& operator>>(istream& is, Planet& p) {
    cout << "Enter the name of the planet: ";
    is.ignore();
    is.getline(p.name, 15);

    cout << "Enter the diameter of the planet (in km): ";
    is >> p.diameter;

    cout << "Enter distances to 5 satellites:\n";
    for (int i = 0; i < 5; ++i) {
        cout << "Satellite " << i + 1 << ": ";
        is >> p.satellites[i];
    }

    return is;
}

ofstream& operator<<(ofstream& ofs, const Planet& p) {
    ofs << p.name << "\n";
    ofs << p.diameter << "\n";
    for (int i = 0; i < 5; ++i) {
        ofs << p.satellites[i] << "\n";
    }
    return ofs;
}


ifstream& operator>>(ifstream& ifs, Planet& p) {
    ifs.getline(p.name, 15);
    ifs >> p.diameter;
    for (int i = 0; i < 5; ++i) {
        ifs >> p.satellites[i];
    }
    return ifs;
}

bool Planet::operator<(const Planet& other) const {
    return this->diameter < other.diameter;
}

bool Planet::operator>(const Planet& other) const {
    return this->diameter > other.diameter;
}

bool Planet::operator==(const Planet& other) const {
    return this->diameter == other.diameter;
}

void Planet::compareSatellites(const Planet& other) const {
    for (int i = 0; i < 5; ++i) {
        if (this->satellites[i] < other.satellites[i]) {
            cout << this->name << " has a smaller distance to satellite " << i + 1 << " than " << other.name << ".\n";
        }
        else if (this->satellites[i] > other.satellites[i]) {
            cout << this->name << " has a greater distance to satellite " << i + 1 << " than " << other.name << ".\n";
        }
        else {
            cout << this->name << " and " << other.name << " have the same distance to satellite " << i + 1 << ".\n";
        }
    }
}
