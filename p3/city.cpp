#include "city.h"
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;


City::City ()
{
    name = NULL;
    state = NULL;
    population = -1;
    longitude = 0;
    latitude = 0;
    airportAbbr[0] = airportAbbr[3] = '\0';
}

City::~City ()
{
    free(name);
    free(state);
    airportAbbr[0] = '\0';
}

double
City::degree2radius (double deg)
{
    return deg * M_PI / 180.0;
}

double
City::calcDistance (City *c2)
{
    double phi1 = degree2radius(latitude);
    double phi2 = degree2radius(c2->latitude);
    double gamma1 = degree2radius(longitude);
    double gamma2 = degree2radius(c2->longitude);
    int R = 3963;
    return 1.0 * acos(sin(phi1)*sin(phi2)+cos(phi1)*cos(phi2)*cos(gamma1-gamma2)) * R;
}

double
City::calcPassengers (City *c2)
{
    if (calcDistance(c2) < 100)
        return 0;
    return 1.0 * population * c2->population / 2500000000;
}

void
City::printCityInfo ()
{
    cout << "name:" << setw(15) << name
         << ", state:" << setw(15) << state
         << ", population:" << population
         << ", longitude:" << fixed << setprecision(2) <<  longitude
         << ", latitude:" << fixed << setprecision(2) << latitude
         << ", airport:" << airportAbbr << endl;
}

City &
City::operator=(const City &src)
{
    free(name);
    free(state);
    name = strdup(src.name);
    state = strdup(src.state);
    population = src.population;
    longitude = src.longitude;
    latitude = src.latitude;
    strcpy(airportAbbr, src.airportAbbr);
    return *this;
}

void
City::copyLocation (City *src)
{
    strcpy(airportAbbr, src->airportAbbr);
    latitude = src->latitude;
    longitude = src->longitude;
}

bool
City::hasAirport ()
{
    return airportAbbr[0] != '\0';
}

bool
City::isEqual (City *c2)
{
    return strcmp(name, c2->name) == 0;
}
