#include <string.h>
#include "vector.h"
#include <iostream>
#include <iomanip>
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

void getChoice (Vector *v)
{
    while (true)
    {
        int choice;
        cout << "\nFlight Simulator Menu" << endl;
        cout << "0. Done" << endl;
        cout << "1. Determine distance and passengers between two airports" << endl;
        cout << "2. Determine all traffic from one airport" << endl;
        cout << "\nYour choice (0 - 2): ";
        cin >> choice;
        cin.ignore();
        bool quit = false;
        switch (choice)
        {
            case 0: quit = true; break;
            case 1: run(v); break;
            case 2: v->calcAirportTraffic(); break;
            default: cout << "Your choice must between 0 and 2. Please try again." << endl;
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
//    v.showCities();
    getChoice(&v);
    return 0;

}
