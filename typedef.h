#ifndef TYPEDEF_H
#define TYPEDEF_H

typedef struct
{
    char *county;
    char *state;
    float education[2];
    float ethnicity[8];
    int median_household_income;
    int per_capita_income;
    float persons_below_poverty_level;
    int population;
} Location;

typedef struct 
{
    size_t length;
    size_t num_values;
    // Array of pointers to strings.
    char **data;
} StringArrayList;

typedef struct 
{
    size_t length;
    size_t num_values;
    // Array of pointers to Locations.
    Location *data;
} LocationArrayList;

#endif