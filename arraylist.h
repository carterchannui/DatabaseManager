#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include "typedef.h"

StringArrayList * string_array_list_new();
LocationArrayList * location_array_list_new();
void location_array_add(LocationArrayList * arr, Location location);
void string_array_add(StringArrayList * arr, char string[]);

#endif