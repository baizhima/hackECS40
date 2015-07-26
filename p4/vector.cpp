#include "vector.h"
#include <cstdlib>
#include <cstring>

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

Vector::Vector()
{
    size = 0;
    capacity = 10;
    cityArray = new City[capacity];
}

Vector::~Vector()
{
    delete[] cityArray;
}

void
Vector::resize()
{
    City *newCityArray = new City[2 * capacity];
    for (int i = 0; i < capacity; i++)
    {
        newCityArray[i] = cityArray[i]; // operator=
    }
    delete[] cityArray;
    cityArray = newCityArray;
    capacity *= 2;
}


void
Vector::insertCity (const char *name, const char *state, int population)
{
    if (size >= capacity)
    {
        resize();
    }
    cityArray[size].name = strdup(name);
    cityArray[size].state = strdup(state);
    cityArray[size].population = population;
    size += 1;
}

void
Vector::readCities ()
{
    ifstream fin("citypopulations.csv");
    char line[200];
    while (fin.getline(line, 200))
    {
        char *name = NULL, *state = NULL;
        name = strtok(line,",");
        state = strtok(NULL, ",");
        int population = atoi(strtok(NULL, "\0"));
        insertCity(name, state, population);
    }
    fin.close();
}

void
Vector::readAirports ()
{
    ifstream fin("airportLL.txt");
    char line[200];
    char currState[30]="";
    while (fin.getline(line, 200))
    {
        if (strcmp(line, "Location") == 0) continue; // first line
        if (line[0] >= 'A' && line[0] <= 'Z')
        {
            strcpy(currState, line);
        }
        if (line[0] == '[')
        {
            char *abbr = NULL, *name = NULL;
            abbr = strtok(line, " ");
            abbr[4] = '\0';
            abbr++;
            double lat = atof(strtok(NULL, " "));
            double lon = atof(strtok(NULL, " "));
            name = strtok(NULL, ",");
            name++;
            City city;
            city.name = strdup(name);
            city.state = strdup(currState);
            city.latitude = lat;
            city.longitude = lon;
            strcpy(city.airportAbbr, abbr);
            for (int i = 0; i < size; i++)
            {
                if (city.isEqual(&cityArray[i]))
                {
                    cityArray[i].copyLocation(&city);
                    break;
                }
            }
        }
    }
    fin.close();
}

void
Vector::cleanCities ()
{
    int removeCount = 0;
    for (int i = 0; i < size; i++)
    {
        if (!cityArray[i].hasAirport())
            removeCount++;
    }
    int src = size - 1, dest = 0;
    for (int i = 0; i < removeCount; i++)
    {
       while (cityArray[dest].hasAirport())
       {
            dest++;
       }
       while (!cityArray[src].hasAirport())
       {
            src--;
       }
       if (dest >= src || dest >= size || src < 0) break;
       cityArray[dest] = cityArray[src]; // operator=
       dest++;
       src--;
    }
    size -= removeCount;
}

void
Vector::showCities ()
{
    for (int i = 0; i < size; i++)
    {
        cout << "[" << setw(2) << i << "]";
        cityArray[i].printCityInfo();
    }
}


int 
Vector::calcDistance (int idx1, int idx2)
{
    return (int) cityArray[idx1].calcDistance(&cityArray[idx2]);
}

int
Vector::calcPassengers (int idx1, int idx2)
{
    return (int) cityArray[idx1].calcPassengers(&cityArray[idx2]);
}


void
Vector::calcAirportTraffic ()
{
    char airport[80];
    int idx;
    while (true)
    {
        cout << "Please enter an airport abbreviation (XXX): ";
        cin >> airport;
        cin.ignore();
        if ((idx = findAirport(airport)) < 0)
        {
            cout << airport << " is not a valid airport" << endl;
        }
        if (idx >= 0) break;
    }
    int totalPassengers = 0;
    for (int i = 0; i < size; i++)
    {
        int passengers = cityArray[idx].calcPassengers(&cityArray[i]);
        if (passengers == 0) continue;
        cout << cityArray[i].name << ", " << cityArray[i].state << ": "
             << passengers << endl;
        totalPassengers += passengers;
    }
    cout << "\nTotal passengers: "<< totalPassengers << endl;
}

int
Vector::findAirport (const char *abbr)
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(cityArray[i].airportAbbr, abbr) == 0)
        {
            return i;
        }
    }
    return -1;
}

