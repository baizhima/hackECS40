#ifndef PLANE_H_DEFINED
#define PLANE_H_DEFINED
#include <iostream>
using namespace std;
static const double dollarsPerGallon = 3.39;

class Plane {

public:
    char name[12];
    int passengers;
    int range;
    int speed;
    int fuel;
    int price;

public:
    Plane();
    Plane(const char *, int, int, int, int, int);
    ~Plane();

    friend ostream &operator<< (ostream &out, const Plane &);
    Plane & operator=(const Plane &);

    void write (ofstream &);
    void printInfo();
    const char *getName();

    double calcCost(int distance, int passengers);
};



#endif
