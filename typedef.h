#ifndef TYPEDEF_H
#define TYPEDEF_H

typedef struct
{
    char *county;
    char *state;
    float **education;
    float **ethnicity
    void **income;
    int population;
} Location;

typedef struct 
{
    size_t length;
    size_t num_values;
    // Array of pointers to void .
    void **data;
} ArrayList;

#endif