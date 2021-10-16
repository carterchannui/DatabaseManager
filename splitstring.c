#define _BSD_SOURCE
#include <stdio.h>
#include <string.h>
#include "typedef.h"
#include "arraylist.h"

ArrayList * split(char string_pointer[], char *delim)
{
    // Duplicate string so that original string is not mutated by strsep().
    char *string = string_pointer;
    // Token that's separated from dup'ed string by strsep().
    char *token;
    // Declare ArrayList to store the tokens.
    ArrayList *list = array_list_new();

    // Parse through dup'ed string with strsep().
    while ((token = strsep(&string, delim)) != NULL)
    {
        // Add token to ArrayList.
        array_list_add_to_end(list, token);
    }
    
    // Return list of fresh copies of tokens.
    return list;
}