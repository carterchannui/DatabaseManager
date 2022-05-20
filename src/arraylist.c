#include <stdio.h>
#include <stdlib.h>
#include "include/typedef.h"

StringArrayList * string_array_list_new()
{
    StringArrayList *list = malloc(sizeof(StringArrayList));
    
    // Number of occupied slots
    list->num_values = 0;
    // Number o slots allocated
    list->length = 10;
    list->data = calloc(10, sizeof(char *));
    
    return list;
}

LocationArrayList * location_array_list_new()
{
    LocationArrayList *list = malloc(sizeof(LocationArrayList));
    
    // Number of occupied slots
    list->num_values = 0;
    // Number o slots allocated
    list->length = 10;
    list->data = calloc(10, sizeof(Location));
    
    return list;
}

void location_array_add(LocationArrayList *arr, Location location)
{
    // Check if more memory needs to be allocated.
    if (arr->num_values == arr->length)
    {
        // Adds new slot for new location.
        arr->length += 1;
        // Reallocates data to account for the addition of the new location.
        Location *new_data = realloc(arr->data, (sizeof(Location) * arr->length));
        // Update arr->data.
        arr->data = new_data;
    }
    
    // Add new location to end of newly allocated memory.
    arr->data[arr->num_values] = location;
    // Update num_values.
    arr->num_values++;
}

void location_array_remove(LocationArrayList *list, int index)
{
    int i;
    
    free(list->data[index].county);
    free(list->data[index].state);
    
    // Shift elements forward one index to remove selected element.
    for (i = index; i < (list->num_values) - 1; i++)
    {
        list->data[i] = list->data[i + 1];
    }

    list->data[i].county = NULL;
    list->data[i].state = NULL;

    // Removes slot used for removed element.
    list->length -= 1;
    // Reallocates data to account for the removal of the desired element.
    Location *new_data = realloc(list->data, (sizeof(Location) * list->length));
    // Update list->data.
    list->data = new_data;
    // Update num_values.
    list->num_values--;
}

void string_array_add(StringArrayList *arr, char string[])
{
    // Check if more memory needs to be allocated.
    if (arr->num_values == arr->length)
    {
        // Adds new slot for new string.
        arr->length += 1;
        // Reallocates data to account for the addition of the new string.
        char ** new_data = realloc(arr->data, (sizeof(char *) * arr->length));
        // Update arr->data.
        arr->data = new_data;
    }
    
    // Add new string to end of newly allocated memory.
    arr->data[arr->num_values] = string;
    // Update num_values.
    arr->num_values++;
}
