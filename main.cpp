#include <iostream>

using namespace std;

class Planet {
public:
    char name[50];  

private:
    struct Satellite {
        int number;
        double distance;
    };

    static const int MAX_SATELLITES = 10; 
    Satellite satellites[MAX_SATELLITES]; 
    int satelliteCount = 0;               

protected:
    double diameter;

public:
    
    Planet(const char* name, double diameter) {
        
        int i = 0;
        while (name[i] != '\0' && i < 49) {
            this->name[i] = name[i];
            i++;
        }
        this->name[i] = '\0'; 
        this->diameter = diameter;
    }


    double satellite(int number) {
        for (int i = 0; i < satelliteCount; ++i) {
            if (satellites[i].number == number) {
                return satellites[i].distance;  
            }
        }
        return -1;  
    }

    
    double satellite(double distance) {
        for (int i = 0; i < satelliteCount; ++i) {
            if (satellites[i].distance == distance) {
                return satellites[i].number;  
            }
        }
        return -1; 
    }

    
    void satellite(int number, double distance) {
        for (int i = 0; i < satelliteCount; ++i) {
            if (satellites[i].number == number) {
                satellites[i].distance = distance;  
                return;
            }
        }

        if (satelliteCount < MAX_SATELLITES) {
            satellites[satelliteCount].number = number;
            satellites[satelliteCount].distance = distance;
            ++satelliteCount; 
        }
        else {
            cout << "Cannot add more satellites!" << endl;
        }
    }
};

int main() {
    Planet earth("Earth", 12742);  

    earth.satellite(1, 384400);  

    cout << "Distance to satellite 1: " << earth.satellite(1) << " km" << endl;
    cout << "Satellite number at distance 384400 km: " << earth.satellite(384400) << endl;

    earth.satellite(1, 400000); \

    cout << "New distance to satellite 1: " << earth.satellite(1) << " km" << endl;

    return 0;
}
