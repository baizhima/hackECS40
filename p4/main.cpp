#include <string.h>
#include <fstream>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <climits>
#include "vector.h"
#include "plane.h"

using namespace std;

void run(Vector *v)
{

        char airport[80], airport2[80];
        cout << "\nPlease enter two airport abbreviations (XXX XXX): ";
        cin >> airport >> airport2;
        cin.ignore();
        int idx = -1, idx2= -1;
        if ((idx = v->findAirport(airport)) < 0)
        {
            cout << airport << " is not a valid airport" << endl;
        }
        if ((idx2 = v->findAirport(airport2)) < 0)
        {
            cout << airport2 << " is not a valid airport" << endl;
        }
        if (idx < 0 || idx2 < 0) return;
        int distance = v->calcDistance (idx, idx2);
        int passengers = v->calcPassengers (idx, idx2);
        cout << passengers << " passengers fly from the " << distance << " miles from" << endl;
        cout << v->cityArray[idx].name << ", " << v->cityArray[idx].state << " to "
             << v->cityArray[idx2].name << ", " << v->cityArray[idx2].state << endl;

}

int readPlanes (Plane *p)
{
    ifstream inf("planes.dat", ios::binary);
    int size = 0;
    if (inf.is_open())
    {
       size = inf.tellg();
       inf.seekg(0, ios::beg);
       inf.read ((char *)p,10 * sizeof(Plane));
       inf.close();
    }
    for (int i = 0; i < 10; i++)
    {
        if (p[i].passengers == -1) return i;
    }
    return -1;
}

void displayPlaneInformation (Plane *p, int *pCount)
{
    cout << "Plane Information" << endl;
    cout << setw(12) << left << "Name"
         << setw(6) << left << "Pass."
         << setw(6) << left <<  "Range"
         << setw(6) << left << "Speed"
         << setw(7) << "Fuel"
         << setw(6) << "MPG"
         << setw(6) << "$/mi"
         << "Price * 10^6" << endl;
    
    for (int i = 0; i < *pCount; i++)
    {
        cout << p[i] << endl;
    }
}

void addPlaneInformation(Plane *p, int *pCount)
{
    char name[12];
    int passengers, fuelCapacity, range, speed, price;
    ofstream outf("planes.dat", ios::binary | ios::out | ios::app);
    cout << "Name: ";
    cin >> name;
    cin.ignore();
    cout << "Passengers: ";
    cin >> passengers;
    cin.ignore();
    cout << "Fuel Capacity (in U.S. gallons): ";
    cin >> fuelCapacity;
    cin.ignore();
    cout << "Range (in miles): ";
    cin >> range;
    cin.ignore();
    cout << "Speed (in mph): ";
    cin >> speed;
    cin.ignore();
    cout << "Price: ";
    cin >> price;
    cin.ignore();
    Plane plane(name, passengers, fuelCapacity, range, speed, price);
    p[*pCount] = plane;
    *pCount += 1;
    plane.write(outf);
    outf.close();
}

void determineBestPlane(Vector *v, Plane *p, int *pCount)
{
    char airport[80], airport2[80];
    cout << "\nPlease enter two airport abbreviations (XXX XXX): ";
    cin >> airport >> airport2;
    cin.ignore();
    int idx = -1, idx2= -1;
    if ((idx = v->findAirport(airport)) < 0)
    {
        cout << airport << " is not a valid airport" << endl;
    }
    if ((idx2 = v->findAirport(airport2)) < 0)
    {
        cout << airport2 << " is not a valid airport" << endl;
    }
    if (idx < 0 || idx2 < 0) return;
    int passengers = v->calcPassengers (idx, idx2);
    int distance = v->calcDistance (idx, idx2);
    int minCost = INT_MAX;
    int minIdx = -1;
    cout << setw(11) << left << "Passengers"
         << setw(8) << left << "Miles"
         << setw(6) << left << "Trips"
         << setw(12) << left << "Name"
         << "Cost" << endl;
    for (int i = 0; i < *pCount; i++)
    {
        int trips = ceil(passengers * 1.0 / p[i].passengers);
        double currCost = p[i].calcCost(distance, passengers);
        if (currCost < minCost)
        {
            minCost = currCost;
            minIdx = i;
        }
    }
}

void getChoice (Vector *v, Plane *p, int *pCount)
{
    while (true)
    {
        int choice;
        cout << "\nFlight Simulator Menu" << endl;
        cout << "0. Done" << endl;
        cout << "1. Determine distance and passengers between two airports" << endl;
        cout << "2. Determine all traffic from one airport" << endl;
        cout << "3. Display planes information" << endl;
        cout << "4. Add plane information" << endl;
        cout << "5. Determine best plane between two airports" << endl;
        cout << "\nYour choice (0 - 5): ";
        cin >> choice;
        cin.ignore();
        bool quit = false;
        switch (choice)
        {
            case 0: quit = true; break;
            case 1: run(v); break;
            case 2: v->calcAirportTraffic(); break;
            case 3: displayPlaneInformation(p, pCount); break;
            case 4: addPlaneInformation(p, pCount); break;
            case 5: determineBestPlane(v, p, pCount); break;
            default: cout << "Your choice must between 0 and 5. Please try again." << endl;
        }
        if (quit) break;
    }
}


int main (int argc, char *argv[])
{
    Vector v;
    v.readCities();
    v.readAirports();
    v.cleanCities();
    Plane planes[10];
    int pCount = readPlanes(planes);
    cout << "pCount=" << pCount << endl;
    getChoice(&v, planes, &pCount);
    return 0;

}
