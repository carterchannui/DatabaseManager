#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "typedef.h"
#include "arraylist.h"
#include "splitstring.h"


char *remove_quotes(char *str)
{
    if (str == NULL)
    {
        return NULL;
    }
    size_t len = strlen(str);
    if (str[len - 1] == '\"')
    {
        str[len - 1] = '\0';
    }
    if (str[0] == '\"')
    {
        return str + 1;
    }
    return str;
}

void load_ethnicity(Location location, StringArrayList *list)
{
    size_t i;
    // Declare j as the index of first index of ethnicity data in ArrayList list.
    size_t j = 11;

    // Visualization of data stored in ethnicity field:
    // location.ethnicity[0] = Ethnicities.American Indian and Alaska Native Alone
    // location.ethnicity[1] = Ethnicities.Asian Alone
    // location.ethnicity[2] = Ethnicities.Black Alone
    // location.ethnicity[3] = Ethnicities.Hispanic or Latino
    // location.ethnicity[4] = Ethnicities.Native Hawaiian and Other Pacific Islander Alone
    // location.ethnicity[5] = Ethnicities.Two or More Races 	
    // location.ethnicity[6] = Ethnicities.White Alone 	
    // location.ethnicity[7] = Ethnicities.White Alone, not Hispanic or Latino 	
    for (i = 0; i < 8; i++)
    {
        location.ethnicity[i] = strtof(list->data[j], NULL);
        j++;
    }
}

Location load_demographics(char *line)
{
    Location location;
    size_t i;
    // Remove comma delimiter from current line.
    StringArrayList *list = split(line, ",");
    
    for (i = 0; i < list->num_values; i++)
    {
        list->data[i] = remove_quotes(list->data[i]);
    }

    // Load county data.
    location.county = list->data[0];
    // printf("County: %s\n", location.county);
    // Load state data.
    location.state = list->data[1];
    // printf("    State: %s\n", location.state);
    // Load "Education.Bachelor's Degree or Higher" data.
    location.education[0] = strtof(list->data[5], NULL);
    // printf("    Education.Bachelor's Degree or Higher: %f\n", location.education[0]);
    // Load "Education.High School or Higher" data.
    location.education[1] = strtof(list->data[6], NULL);
    // printf("    Education.High School or Higher: %f\n", location.education[1]);
    // Load ethnicity data.
    load_ethnicity(location, list);
    // Load "Income.Median Houseold Income" data.
    location.median_household_income = atoi(list->data[25]);
    // Load "Income.Per Capita Income" data.
    location.per_capita_income = atoi(list->data[26]);
    // Load "Income.Persons Below Poverty Level" data.
    location.persons_below_poverty_level = strtof(list->data[27], NULL);
    // Load population data.
    location.population = atoi(list->data[38]);

    return location;
}

void read_demographics(FILE * demographics, LocationArrayList *list)
{
    size_t len = 0;
    char *line = NULL;
    size_t i;
    // Skip first line of headers in CSV file.
    getline(&line, &len, demographics);
    
    while (getline(&line, &len, demographics) != -1)
    {
        // Declare Location structure.
        Location location = load_demographics(line);
        location_array_add(list, location);
        for (i = 0; i < list->num_values; i++)
        {
            printf("County: %s | State: %s | Education.High School or Higher: %f\n", list->data[i].county, list->data[i].state, list->data[i].education[0]);
        }
        printf("\n");
    }
    
}

FILE * validate_argument(char *file_name)
{
    FILE * file = fopen(file_name, "r");
    // Check if file exists.
    if (file == NULL)
    {
        perror(file_name);
        exit(1);
    }
    return file;
}

int main(int argc, char *argv[])
{
    // Check if valid number of arguments.
    if (argc == 3)
    {
        FILE * demographics = validate_argument(argv[1]);
        // FILE * operations = validate_argument(argv[2]);

        // Initialize ArrayList of Location structures.
        LocationArrayList *list = location_array_list_new();
        read_demographics(demographics, list); 
    } else {
        fprintf(stderr, "Invalid number of arguments: %d", argc);
        exit(1);
    }
    return 0;   
}