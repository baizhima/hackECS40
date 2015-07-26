#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
Vector *initVector()
{
    Vector *v = (Vector *) malloc(sizeof(Vector));
    v->size = 0;
    v->capacity = 10;
    v->cityArray = (City *) malloc(sizeof(City) * v->capacity);
    for (int i = 0; i < v->capacity; i++)
    {
        initCity(&v->cityArray[i]);
    }
    return v;
}

void insertCity (Vector *v, char *name, char *state, int population)
{
    if (v->size >= v->capacity)
    {
        resize(v);
    }
    v->cityArray[v->size].name = strdup(name);
    v->cityArray[v->size].state = strdup(state);
    v->cityArray[v->size].population = population;
    v->size += 1;
}

void readCities (Vector *v)
{
    FILE *fp = fopen("citypopulations.csv","r");
    char line[200];
    while (fgets(line, 200, fp))
    {
        char *ptr = line;
        while (*ptr != '\n')
        {
            ptr++;
        }
        *ptr = '\0';
        char *name = NULL, *state = NULL;
        name = strtok(line,",");
        state = strtok(NULL, ",");
        int population = atoi(strtok(NULL, "\0"));
        insertCity(v, name, state, population);
    }
    fclose(fp);
}

void readAirports (Vector *v)
{
    FILE *fp = fopen("airportLL.txt","r");
    char line[200];
    char currState[30]="";
    while (fgets(line, 200, fp))
    {
        if (strcmp(line, "Location") == 0) continue; // first line
        if (line[0] == '\n') continue;
        if (line[0] >= 'A' && line[0] <= 'Z')
        {
            char *ptr = line;
            for (; *ptr != '\n'; ptr++);
            *ptr = '\0';
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
            
            for (int i = 0; i < v->size; i++)
            {
                if (isEqual(&city, &v->cityArray[i]))
                {
                    copyLocation(&v->cityArray[i], &city);
                    break;
                }
            }
            deallocCity(&city);
        }
    }
    fclose(fp);
}

void cleanCities (Vector *v)
{
    int removeCount = 0;
    for (int i = 0; i < v->size; i++)
    {
        if (!hasAirport(&v->cityArray[i]))
            removeCount++;
    }
    int src = v->size - 1, dest = 0;
    for (int i = 0; i < removeCount; i++)
    {
       while (hasAirport(&v->cityArray[dest]))
       {
            dest++;
       }
       while (!hasAirport(&v->cityArray[src]))
       {
            src--;
       }
       if (dest >= src || dest >= v->size || src < 0) break;
       deallocCity(&v->cityArray[dest]);
       memcpy(&v->cityArray[dest], &v->cityArray[src], sizeof(City));
       dest++;
       src--;
    }
    v->size -= removeCount;
}

void showCities (Vector *v)
{
    for (int i = 0; i < v->size; i++)
    {
        printf("[%2d] ",i);
        printCityInfo(&v->cityArray[i]);
    }
}


int calcDistance (Vector *v, int idx1, int idx2)
{
    return (int) calcDistance(&v->cityArray[idx1],&v->cityArray[idx2]);
}

int calcPassengers (Vector *v, int idx1, int idx2)
{
    return (int) calcPassengers(&v->cityArray[idx1],&v->cityArray[idx2]);
}

void resize(Vector *v)
{
    v->cityArray = (City *) realloc(v->cityArray, sizeof(City) * 2 * v->capacity);
    for (int i = v->capacity; i < v->capacity * 2; i++)
        initCity(&v->cityArray[i]);
    v->capacity *= 2;
}

int findAirport (Vector *v, const char *abbr)
{
    for (int i = 0; i < v->size; i++)
    {
        if (strcmp(v->cityArray[i].airportAbbr, abbr) == 0)
        {
            return i;
        }
    }
    return -1;
}

void deallocVector (Vector *v)
{ 
    for (int i = 0; i < v->size; i++)
    {
        deallocCity(&v->cityArray[i]);
    }
    free(v);
}
