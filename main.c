#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "typedef.h"
#include "arraylist.h"
#include "splitstring.h"
#include "main_tests.h"


char *remove_quotes(char *str)
{
    // Check if string doesn't exist or is of length 2 (just quotes).
    if (str == NULL || strlen(str) == 2 || strlen(str) == 0)
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

Location load_demographics(char *line)
{
    Location location;
    location.malformed_status = 0;
    size_t i;
    // Remove comma delimiter from current line.
    
    StringArrayList *list = split(line, ",");
    
    for (i = 0; i < list->num_values; i++)
    {
        char *temp = remove_quotes(list->data[i]);
        // Check for empty/improper data field.
        if (temp == NULL)
        {
            location.malformed_status = 1;
            return location;
        } else {
            list->data[i] = temp;
        }
    }

    // Load county data.
    location.county = strdup(list->data[0]);
    
    // Load state data.
    location.state = strdup(list->data[1]);
    
    // Load "Education.Bachelor's Degree or Higher" data.
    location.education[0] = strtof(list->data[5], NULL);
    
    // Load "Education.High School or Higher" data.
    location.education[1] = strtof(list->data[6], NULL);

    // Load "Ethnicities.American Indian and Alaska Native Alone" data.
    location.ethnicity[0] = strtof(list->data[11], NULL);

    // Load "Ethnicities.Asian Alone" data.
    location.ethnicity[1] = strtof(list->data[12], NULL);

    // Load "Ethnicities.Black Alone" data.
    location.ethnicity[2] = strtof(list->data[13], NULL);

    // Load "Ethnicities.Hispanic or Latino" data.
    location.ethnicity[3] = strtof(list->data[14], NULL);

    // Load "Ethnicities.Native Hawaiian and Other Pacific Islander Alone" data.
    location.ethnicity[4] = strtof(list->data[15], NULL);

    // Load "Ethnicities.Two or More Races" data.
    location.ethnicity[5] = strtof(list->data[16], NULL);

    // Load "Ethnicities.White Alone" data.
    location.ethnicity[6] = strtof(list->data[17], NULL);

    // Load "Ethnicities.White Alone, not Hispanic or Latino" data.
    location.ethnicity[7] = strtof(list->data[18], NULL);

    // Load "Income.Median Houseold Income" data.
    location.median_household_income = atoi(list->data[25]);
    // Load "Income.Per Capita Income" data.
    location.per_capita_income = atoi(list->data[26]);
    // Load "Income.Persons Below Poverty Level" data.
    location.persons_below_poverty_level = strtof(list->data[27], NULL);
    // Load population data.
    location.population = atoi(list->data[38]);

    free(list->data);
    free(list);

    return location;
}

void read_demographics(FILE * demographics, LocationArrayList *list)
{
    size_t len = 0;
    char *line = NULL;
    int num_entries = 0;
    int cur_line = 1;
    
    // Skip first line of headers in CSV file.
    getline(&line, &len, demographics);
    
    while (getline(&line, &len, demographics) != -1)
    {
        cur_line++;
        // Declare Location structure.
        Location location = load_demographics(line);
        if (location.malformed_status == 0)
        {
            // Add location to ArrayList.
            location_array_add(list, location);
            num_entries++;
        } else {
            // Otherwise, print line number of malformed entry.
            fprintf(stderr, "Malformed entry on CSV file line: %d\n", cur_line);
        }
    }

    free(line);
    fprintf(stdout, "Number of entries loaded: %d\n", num_entries);
}

void process_display(LocationArrayList *list)                 
{
    size_t i;
    for (i = 0; i < list->num_values; i++)
    {
        printf("County: %s\n", list->data[i].county);
        printf("    State:                                                           %s\n", list->data[i].state);
        printf("    Education.Bachelor's Degree or Higher:                           %f\n", list->data[i].education[0]);
        printf("    Education.High School or Higher:                                 %f\n", list->data[i].education[1]);
        printf("    Ethnicities.American Indian and Alaska Native Alone:             %f\n", list->data[i].ethnicity[0]);
        printf("    Ethnicities.Asian Alone:                                         %f\n", list->data[i].ethnicity[1]);
        printf("    Ethnicities.Black Alone:                                         %f\n", list->data[i].ethnicity[2]);
        printf("    Ethnicities.Hispanic or Latino:                                  %f\n", list->data[i].ethnicity[3]);
        printf("    Ethnicities.Native Hawaiian and Other Pacific Islander Alone:    %f\n", list->data[i].ethnicity[4]);
        printf("    Ethnicities.Two or More Races:                                   %f\n", list->data[i].ethnicity[5]);
        printf("    Ethnicities.White Alone:                                         %f\n", list->data[i].ethnicity[6]);
        printf("    Ethnicities.White Alone, not Hispanic or Latino:                 %f\n", list->data[i].ethnicity[7]);
        printf("    Income.Median Houseold Income                                    %d\n", list->data[i].median_household_income);
        printf("    Income.Per Capita Income                                         %d\n", list->data[i].per_capita_income);
        printf("    Income.Persons Below Poverty Level                               %f\n", list->data[i].persons_below_poverty_level);
        printf("    Population.2014 Population                                       %d\n\n", list->data[i].population);
    }
}

int process_population_total(LocationArrayList *list)
{
    size_t i;
    int population_sum = 0;

    for (i = 0; i < list->num_values; i++)
    {
        population_sum += list->data[i].population;
    }

    return population_sum;
}

void process_filter_state(LocationArrayList *list, char *state)
{
    size_t i;

    for (i = 0; i < list->num_values; i++)
    {
        if (strstr(state, list->data[i].state) == NULL)
        {
            location_array_remove(list, i);
            i = -1;
        }
    }
    
    StringArrayList *removed_nullchar_state = split(state, "\n");
    printf("Filter: state == %s (%zd entries)\n", removed_nullchar_state->data[0], list->num_values);

    free(removed_nullchar_state->data);
    free(removed_nullchar_state);
}

int validate_field(char *field)
{
    size_t i;
    char *valid_fields[] = {
                            "Education.Bachelor's Degree or Higher", 
                            "Education.High School or Higher", 
                            "Ethnicities.American Indian and Alaska Native Alone", 
                            "Ethnicities.Asian Alone", 
                            "Ethnicities.Black Alone",
                            "Ethnicities.Hispanic or Latino",
                            "Ethnicities.Native Hawaiian and Other Pacific Islander Alone",
                            "Ethnicities.Two or More Races",
                            "Ethnicities.White Alone",
                            "Ethnicities.White Alone, not Hispanic or Latino",
                            "Income.Median Houseold Income",
                            "Income.Per Capita Income",
                            "Income.Persons Below Poverty Level",
                            "Population.2014 Population"
                            };
    for (i = 0; i < 14; i++)
    {
        if (strstr(field, valid_fields[i]) != NULL)
        {
            return i;
        }
    }
    fprintf(stderr, "Invalid field for operation");
    exit(1);
}

// 0  Education.Bachelor's Degree or Higher 
// 1  Education.High School or Higher 
// 2  Ethnicities.American Indian and Alaska Native Alone 
// 3  Ethnicities.Asian Alone
// 4  Ethnicities.Black Alone
// 5  Ethnicities.Hispanic or Latino
// 6  Ethnicities.Native Hawaiian and Other Pacific Islander Alone
// 7  Ethnicities.Two or More Races
// 8  Ethnicities.White Alone
// 9  Ethnicities.White Alone, not Hispanic or Latino
// 10 Income.Median Houseold Income
// 11 Income.Per Capita Income
// 12 Income.Persons Below Poverty Level
// 13 Population.2014 Population

void process_filter(LocationArrayList *list, char *field, char *comparison, float number)
{ 
    size_t i;
    int field_id = validate_field(field);

    // If greater-than-or-equal-to.
    if (strcmp(comparison, "ge") == 0)
    {
        for (i = 0; i < list->num_values; i++)
        {
            // Education.Bachelor's Degree or Higher
            if (field_id == 0 && list->data[i].education[0] < number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Education.High School or Higher
            else if (field_id == 1 && list->data[i].education[1] < number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Ethnicities.American Indian and Alaska Native Alone
            else if (field_id == 2 && list->data[i].ethnicity[0] < number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Ethnicities.Asian Alone
            else if (field_id == 3 && list->data[i].ethnicity[1] < number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Ethnicities.Black Alone
            else if (field_id == 4 && list->data[i].ethnicity[2] < number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Ethnicities.Hispanic or Latino
            else if (field_id == 5 && list->data[i].ethnicity[3] < number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Ethnicities.Native Hawaiian and Other Pacific Islander Alone
            else if (field_id == 6 && list->data[i].ethnicity[4] < number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Ethnicities.Two or More Races
            else if (field_id == 7 && list->data[i].ethnicity[5] < number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Ethnicities.White Alone
            else if (field_id == 8 && list->data[i].ethnicity[6] < number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Ethnicities.White Alone, not Hispanic or Latino
            else if (field_id == 9 && list->data[i].ethnicity[7] < number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Income.Median Houseold Income
            else if (field_id == 10 && list->data[i].median_household_income < number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Income.Per Capita Income
            else if (field_id == 11 && list->data[i].per_capita_income < number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Income.Persons Below Poverty Level
            else if (field_id == 12 && list->data[i].persons_below_poverty_level < number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Population.2014 Population
            else if (field_id == 13 && list->data[i].population < number)
            {
                location_array_remove(list, i);
                i = -1;
            }
        }
    }
    // If less-than-or-equal-to. 
    else if (strcmp(comparison, "le") == 0)
    {
        for (i = 0; i < list->num_values; i++)
        {
            // Education.Bachelor's Degree or Higher
            if (field_id == 0 && list->data[i].education[0] > number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Education.High School or Higher
            else if (field_id == 1 && list->data[i].education[1] > number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Ethnicities.American Indian and Alaska Native Alone
            else if (field_id == 2 && list->data[i].ethnicity[0] > number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Ethnicities.Asian Alone
            else if (field_id == 3 && list->data[i].ethnicity[1] > number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Ethnicities.Black Alone
            else if (field_id == 4 && list->data[i].ethnicity[2] > number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Ethnicities.Hispanic or Latino
            else if (field_id == 5 && list->data[i].ethnicity[3] > number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Ethnicities.Native Hawaiian and Other Pacific Islander Alone
            else if (field_id == 6 && list->data[i].ethnicity[4] > number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Ethnicities.Two or More Races
            else if (field_id == 7 && list->data[i].ethnicity[5] > number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Ethnicities.White Alone
            else if (field_id == 8 && list->data[i].ethnicity[6] > number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Ethnicities.White Alone, not Hispanic or Latino
            else if (field_id == 9 && list->data[i].ethnicity[7] > number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Income.Median Houseold Income
            else if (field_id == 10 && list->data[i].median_household_income > number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Income.Per Capita Income
            else if (field_id == 11 && list->data[i].per_capita_income > number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Income.Persons Below Poverty Level
            else if (field_id == 12 && list->data[i].persons_below_poverty_level > number)
            {
                location_array_remove(list, i);
                i = -1;
            }
            // Population.2014 Population
            else if (field_id == 13 && list->data[i].population > number)
            {
                location_array_remove(list, i);
                i = -1;
            }
        }
    }
    printf("Filter: %s %s %f (%zd entries)\n", field, comparison, number, list->num_values);
}

int process_population(LocationArrayList *list, char *field)
{
    size_t i;
    int field_id = validate_field(field);
    int total_sub_population = 0;

    for (i = 0; i < list->num_values; i++)
    {
        // Education.Bachelor's Degree or Higher
        if (field_id == 0)
        {
            total_sub_population += ((list->data[i].education[0] / 100) * list->data[i].population);
        }
        // Education.High School or Higher
        else if (field_id == 1)
        {
            total_sub_population += ((list->data[i].education[1] / 100) * list->data[i].population);
        }
        // Ethnicities.American Indian and Alaska Native Alone
        else if (field_id == 2)
        {
            total_sub_population += ((list->data[i].ethnicity[0] / 100) * list->data[i].population);
        }
        // Ethnicities.Asian Alone
        else if (field_id == 3)
        {
            total_sub_population += ((list->data[i].ethnicity[1] / 100) * list->data[i].population);
        }
        // Ethnicities.Black Alone
        else if (field_id == 4)
        {
            total_sub_population += ((list->data[i].ethnicity[2] / 100) * list->data[i].population);
        }
        // Ethnicities.Hispanic or Latino
        else if (field_id == 5)
        {
            total_sub_population += ((list->data[i].ethnicity[3] / 100) * list->data[i].population);
        }
        // Ethnicities.Native Hawaiian and Other Pacific Islander Alone
        else if (field_id == 6)
        {
            total_sub_population += ((list->data[i].ethnicity[4] / 100) * list->data[i].population);   
        }
        // Ethnicities.Two or More Races
        else if (field_id == 7)
        {
            total_sub_population += ((list->data[i].ethnicity[5] / 100) * list->data[i].population);
        }
        // Ethnicities.White Alone
        else if (field_id == 8)
        {
            total_sub_population += ((list->data[i].ethnicity[6] / 100) * list->data[i].population);
        }
        // Ethnicities.White Alone, not Hispanic or Latino
        else if (field_id == 9)
        {
            total_sub_population += ((list->data[i].ethnicity[7] / 100) * list->data[i].population);
        }
        // Income.Persons Below Poverty Level
        else if (field_id == 12)
        {
            total_sub_population += ((list->data[i].persons_below_poverty_level / 100) * list->data[i].population);
        }
    }
    return total_sub_population;
}

void read_operations(FILE * operations, LocationArrayList *list)
{
    size_t len = 0;
    char *line = NULL;
    int total_population;
    int total_sub_population;
    float percent;

    // Determine operation.
    while (getline(&line, &len, operations) != -1)
    {
        // Split operation string into tokens and add to StringArrayList.
        StringArrayList *operations_list = split(line, ":");

        // Find operation.
        if (strstr("display\n", operations_list->data[0]) != NULL)
        {
            process_display(list);
        } else if (strstr("population\n", operations_list->data[0]) != NULL)
        {
            total_sub_population = process_population(list, operations_list->data[1]);
            StringArrayList *removed_nullchar_population = split(operations_list->data[1], "\n");
            printf("2014 %s population: %d\n", removed_nullchar_population->data[0], total_sub_population);
            
            free(removed_nullchar_population->data);
            free(removed_nullchar_population);
        } else if (strstr("population-total\n", operations_list->data[0]) != NULL) 
        {
            total_population = process_population_total(list);
            printf("2014 population: %d\n", total_population);
        } else if (strstr("filter\n", operations_list->data[0]) != NULL)
        {
            StringArrayList *removed_newlinechar = split(operations_list->data[3], "\n");
            process_filter(list, operations_list->data[1], operations_list->data[2], strtof(removed_newlinechar->data[0], NULL));
            
            free(removed_newlinechar->data);
            free(removed_newlinechar);
        } else if (strstr("filter-state\n", operations_list->data[0]) != NULL)
        {
            process_filter_state(list, operations_list->data[1]);
        } else if (strstr("percent\n", operations_list->data[0]) != NULL)
        {
            total_sub_population = process_population(list, operations_list->data[1]);
            total_population = process_population_total(list);
            if (total_population != 0)
            {
                percent = ((float)total_sub_population / total_population) * 100;
            } else {
                percent = 0;
            }
            StringArrayList *removed_newlinechar = split(operations_list->data[1], "\n");
            printf("2014 %s percentage: %f\n", removed_newlinechar->data[0], percent);

            free(removed_newlinechar->data);
            free(removed_newlinechar);
        }

        free(operations_list->data);
        free(operations_list);
    }
    free(line); 
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
        FILE * operations = validate_argument(argv[2]);

        // Initialize ArrayList of Location structures.
        LocationArrayList *list = location_array_list_new();
        read_demographics(demographics, list);
        read_operations(operations, list);


        // Test loading of perfect small.csv data.
        // test_load_data_1(list);

        // Test removal of Location at index 2.
        // test_remove_data_1(list);
        fclose(demographics);
        fclose(operations);
        for (int i = 0; i < list->num_values; i++)
        {
            free(list->data[i].county);
            free(list->data[i].state);
        }
        free(list->data);
        free(list);
    }
    else {
        fprintf(stderr, "Invalid number of arguments: %d", argc);
        exit(1);
    }
    return 0;
}
