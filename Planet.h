#ifndef PLANET_H
#define PLANET_H

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class Planet {
public:
	char name[15];

private:
	static int count;
	double satellites[5];

protected:
	double diameter;

public:
	Planet();
	Planet(const char* n, double d, double dist[]);
	Planet(const Planet& other);
	~Planet();

	static int GetCount();
	static void setcount(int count);

	double* getSatellites() const;
	void setSatellites(double s[]);
	double getDistance() const;
	double getDiameter() const;
	void setDiameter(double d);

	double satellitesB(int number);
	int satellitesB(double distance);
	int findIndex(double arr[], int size, double value);
	void satellitesB(int number, double distance);

	void printPlanetInfo() const;


	friend ostream& operator<<(ostream& os, const Planet& p);
	friend istream& operator>>(istream& is, Planet& p);
	friend ofstream& operator<<(ofstream& ofs, const Planet& p);
	friend ifstream& operator>>(ifstream& ifs, Planet& p);

	bool operator<(const Planet& other) const;
	bool operator>(const Planet& other) const;
	bool operator==(const Planet& other) const;

	void compareSatellites(const Planet& other) const;
};
#endif
