#include <stdio.h>
#include <string.h>
#include "vector.h"
void run(Vector *v)
{
    while (true)
    {
        char airport[80], airport2[80];
        printf("\nPlease enter two airport abbreviations (XXX XXX = done): ");
        scanf("%s%s", airport, airport2);
        if (strcmp(airport,"XXX") == 0 && strcmp(airport2, "XXX") == 0) break;
        int idx = -1, idx2= -1;
        if ((idx = findAirport(v, airport)) < 0)
        {
            printf("%s is not a valid airport\n", airport);
        }
        if ((idx2 = findAirport(v, airport2)) < 0)
        {
            printf("%s is not a valid airport\n", airport2);
        }
        if (idx < 0 || idx2 < 0) continue;
        int distance = calcDistance (v, idx, idx2);
        int passengers = calcPassengers (v, idx, idx2);
        printf("%d passengers fly from the %d miles from\n", passengers, distance);
        printf("%s, %s to %s, %s\n", v->cityArray[idx].name, v->cityArray[idx].state,
                                     v->cityArray[idx2].name, v->cityArray[idx2].state);
    }

}

int main (int argc, char *argv[])
{
    Vector *v = initVector();
    readCities(v);
    readAirports(v);
    cleanCities(v);
    run(v);
    deallocVector(v);
    return 0;

}
