#include <stdio.h>
#include <stdlib.h>
#include "typedef.h"

ArrayList * array_list_new()
{
    ArrayList *list = malloc(sizeof(ArrayList));
    
    // Number of occupied slots
    list->num_values = 0;
    // Number o slots allocated
    list->length = 10;
    list->data = calloc(10, sizeof(char *));
    
    return list;
}

void array_add(ArrayList *arr, char string[])
{
    // Check if more memory needs to be allocated.
    if (arr->num_values == arr->length)
    {
        // Adds new slot for new string.
        arr->length += 1;
    }
    // Reallocates data to account for the addition of the new object (String or Structure).
    void ** new_data = realloc(arr->data, (sizeof(void *) * arr->length));
    // Add new string to end of newly allocated memory.
    new_data[arr->num_values] = string;
    // Update num_values.
    arr->num_values++;
    // Update arr->data.
    arr->data = new_data;
}