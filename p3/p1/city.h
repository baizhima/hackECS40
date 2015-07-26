#ifndef CITY_H_DEFINED
#define CITY_H_DEFINED

typedef struct {
    char *name;
    char *state;
    int population;
    double longitude;
    double latitude;
    char airportAbbr[4];
} City;

void initCity (City *c);
void deallocCity (City *c);
void printCityInfo (City *c);

double calcDistance (City *, City *);
double calcPassengers (City *, City *);

bool hasAirport (City *);
bool isEqual (City *, City *);
void copyLocation (City *, City *);

#endif
