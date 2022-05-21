#include <stdio.h>
#include <stdlib.h>
#include "../include/typedef.h"
#include "../include/checkit.h"
#include "../include/arraylist.h"

void test_load_data_1(LocationArrayList *list)
{
    checkit_string(list->data[0].county, "Autauga County");
    checkit_string(list->data[0].state, "AL");
    checkit_double(list->data[0].education[0], 20.9);
    checkit_double(list->data[0].education[1], 85.6);
    checkit_double(list->data[0].ethnicity[0], 0.5);
    checkit_double(list->data[0].ethnicity[1], 1.1);
    checkit_double(list->data[0].ethnicity[2], 18.7);
    checkit_double(list->data[0].ethnicity[3], 2.7);
    checkit_double(list->data[0].ethnicity[4], 0.1);
    checkit_double(list->data[0].ethnicity[5], 1.8);
    checkit_double(list->data[0].ethnicity[6], 77.9);
    checkit_double(list->data[0].ethnicity[7], 75.6);
    checkit_int(list->data[0].median_household_income, 53682);
    checkit_int(list->data[0].per_capita_income, 24571);
    checkit_double(list->data[0].persons_below_poverty_level, 12.1);
    checkit_int(list->data[0].population, 55395);


    checkit_string(list->data[12].county, "Clarke County");
    checkit_string(list->data[12].state, "AL");
    checkit_double(list->data[12].education[0], 11.2);
    checkit_double(list->data[12].education[1], 78.3);
    checkit_double(list->data[12].ethnicity[0], 0.4);
    checkit_double(list->data[12].ethnicity[1], 0.5);
    checkit_double(list->data[12].ethnicity[2], 44.2);
    checkit_double(list->data[12].ethnicity[3], 1.3);
    checkit_double(list->data[12].ethnicity[4], 0.0);
    checkit_double(list->data[12].ethnicity[5], 0.8);
    checkit_double(list->data[12].ethnicity[6], 54.0);
    checkit_double(list->data[12].ethnicity[7], 53.1);
    checkit_int(list->data[12].median_household_income, 29357);
    checkit_int(list->data[12].per_capita_income, 18979);
    checkit_double(list->data[12].persons_below_poverty_level, 29.3);
    checkit_int(list->data[12].population, 24945);
}

void test_remove_data_1(LocationArrayList *list)
{
    checkit_string(list->data[2].county, "Barbour County");
    checkit_string(list->data[2].state, "AL");
    checkit_double(list->data[2].education[0], 13.4);
    checkit_double(list->data[2].education[1], 73.7);
    checkit_double(list->data[2].ethnicity[0], 0.6);
    checkit_double(list->data[2].ethnicity[1], 0.5);
    checkit_double(list->data[2].ethnicity[2], 47.6);
    checkit_double(list->data[2].ethnicity[3], 4.5);
    checkit_double(list->data[2].ethnicity[4], 0.2);
    checkit_double(list->data[2].ethnicity[5], 0.9);
    checkit_double(list->data[2].ethnicity[6], 50.2);
    checkit_double(list->data[2].ethnicity[7], 46.6);
    checkit_int(list->data[2].median_household_income, 32911);
    checkit_int(list->data[2].per_capita_income, 16829);
    checkit_double(list->data[2].persons_below_poverty_level, 26.7);
    checkit_int(list->data[2].population, 26887);

    location_array_remove(list, 2);

    checkit_string(list->data[2].county, "Bibb County");
    checkit_string(list->data[2].state, "AL");
    checkit_double(list->data[2].education[0], 12.1);
    checkit_double(list->data[2].education[1], 77.5);
    checkit_double(list->data[2].ethnicity[0], 0.4);
    checkit_double(list->data[2].ethnicity[1], 0.2);
    checkit_double(list->data[2].ethnicity[2], 22.1);
    checkit_double(list->data[2].ethnicity[3], 2.1);
    checkit_double(list->data[2].ethnicity[4], 0.1);
    checkit_double(list->data[2].ethnicity[5], 0.9);
    checkit_double(list->data[2].ethnicity[6], 76.3);
    checkit_double(list->data[2].ethnicity[7], 74.5);
    checkit_int(list->data[2].median_household_income, 36447);
    checkit_int(list->data[2].per_capita_income, 17427);
    checkit_double(list->data[2].persons_below_poverty_level, 18.1);
    checkit_int(list->data[2].population, 22506);
}

