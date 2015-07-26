#ifndef VECTOR_H_DEFINED
#define VECTOR_H_DEFINED
#include "city.h"
typedef struct {
    City *cityArray;
    int size;
    int capacity;
} Vector;

Vector *initVector();
void readCities(Vector *);
void readAirports (Vector *);
void cleanCities (Vector *);

void showCities (Vector *v);
void resize (Vector *v);

int calcDistance (Vector *v, int idx1, int idx2);
int calcPassengers (Vector *v, int idx1, int idx2);

int findAirport(Vector *v, const char *);


void deallocVector (Vector *v);

#endif
