#ifndef VECTOR_H_DEFINED
#define VECTOR_H_DEFINED
#include "city.h"
class Vector {
public:
    City *cityArray;
    int size;
    int capacity;

public:
    Vector();
    ~Vector();
    void resize();

    void readCities();
    void readAirports();
    void cleanCities();    
    void showCities();
    
    int calcDistance(int, int);
    int calcPassengers(int, int);
    void calcAirportTraffic();
    int findAirport(const char *);

private:
    void insertCity(const char *, const char *, int);
};

#endif
