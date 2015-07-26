#include "city.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void initCity (City *c)
{
    c->name = NULL;
    c->state = NULL;
    c->population = -1;
    c->longitude = 0;
    c->latitude = 0;
    c->airportAbbr[0] = '\0';
}

void deallocCity (City *c)
{
    free(c->name);
    free(c->state);
    c->airportAbbr[0] = '\0';
}

double degree2radius (double deg)
{
    return deg * M_PI / 180.0;
}

double calcDistance (City *c1, City *c2)
{
    double phi1 = degree2radius(c1->latitude);
    double phi2 = degree2radius(c2->latitude);
    double gamma1 = degree2radius(c1->longitude);
    double gamma2 = degree2radius(c2->longitude);
    int R = 3963;
    return 1.0 * acos(sin(phi1)*sin(phi2)+cos(phi1)*cos(phi2)*cos(gamma1-gamma2)) * R;
}

double calcPassengers (City *c1, City *c2)
{
    if (calcDistance(c1, c2) < 100)
        return 0;
    return 1.0 * c1->population * c2->population / 250000000;
}

void printCityInfo (City *c)
{
    printf("name:%15s, state:%15s, population:%7d, longitude:%.2f, latitude:%.2f, airport:%s\n", c->name, c->state, c->population, c->longitude, c->latitude, c->airportAbbr);
}


void copyLocation (City *dest, City *src)
{
    strcpy(dest->airportAbbr, src->airportAbbr);
    dest->latitude = src->latitude;
    dest->longitude = src->longitude;

}

bool hasAirport (City *c1)
{
    return c1->airportAbbr[0] != '\0';
}

bool isEqual (City *c1, City *c2)
{
    return strcmp(c1->name, c2->name) == 0;
}
