#ifndef CITY_H_DEFINED
#define CITY_H_DEFINED

class City {
public:
    char *name;
    char *state;
    int population;
    double longitude;
    double latitude;
    char airportAbbr[4];

public:
    City();
    ~City();
    
    double calcDistance (City *);
    double calcPassengers (City *);
  
    void printCityInfo();
  
    bool hasAirport();
    bool isEqual (City *);
    City & operator=(const City &);
    void copyLocation (City *);
private:
    double degree2radius(double);
} ;


#endif
