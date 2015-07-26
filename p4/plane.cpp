#include "plane.h"
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <cstring>


Plane::Plane()
{
    name[0] = '\0';
    passengers = -1;
    range = -1;
    speed = -1;
    fuel = -1;
    price = -1;
}

Plane::Plane(const char *name, int passengers, int fuel, int range, int speed, int price)
{
    strcpy (this->name, name);
    this->passengers = passengers;
    this->fuel = fuel;
    this->range = range;
    this->speed = speed;
    this->price = price;
}

Plane::~Plane()
{

}

void
Plane::write (ofstream &out)
{
    out.write ((char *)name, 12 * sizeof(char));
    out.write ((char *)&passengers, sizeof(int));
    out.write ((char *)&range, sizeof(int));
    out.write ((char *)&speed, sizeof(int));
    out.write ((char *)&fuel, sizeof(int));
    out.write ((char *)&price, sizeof(int));
}

ostream &
operator<< (ostream &out, const Plane &p)
{
    double mpg = p.range * 1.0 / p.fuel;
    double dollarPerMile = 1.0 * 15.23;
    out.imbue(locale(""));
    out << setw(12) << left << p.name
        << setw(6) << left  << p.passengers
        << setw(6) << left << p.range
        << setw(6) << left << p.speed
        << setw(6) << right << p.fuel
        << setw(6) << right << setprecision(3) << fixed << mpg
        << setw(6) << right << setprecision(2) << fixed << dollarPerMile
        << " $" 
        << setw(5) << right << setprecision(1) << fixed << p.price / 1000000.0;
    return out;
}

Plane &
Plane::operator=(const Plane &p)
{
    strcpy(this->name, p.name);
    this->passengers = p.passengers;
    this->range = p.range;
    this->speed = p.speed;
    this->fuel = p.fuel;
    this->price = p.price;
    return *this;
}

const char *
Plane::getName ()
{
    return name;
}

double
Plane::calcCost(int distance, int pas)
{
    double fuelCost, attendantSalary, pilotSalary, maintainence;
    fuelCost = 1.0 * pas / range * distance * dollarsPerGallon;
    int nrAttendants = ceil(pas / 100.0);
    
    attendantSalary = 30 * nrAttendants * (2 + ceil(distance * 1.0 / speed));
    pilotSalary = 100 * 2 * (2 + ceil(distance * 1.0 / speed));
    maintainence = 0.000025 * price * ceil(distance * 1.0 / speed);
    return fuelCost + attendantSalary + pilotSalary + maintainence;

}
