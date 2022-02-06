#ifndef POKEMON_H
#define POKEMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../file_helper/file_helper.h"

typedef struct pokemon {
    int id;
    char* name;
    int type_1;
    int type_2;
    int next_evolution;
} pokemon;

pokemon find_pokemon_by_id(json_response response, int id);
pokemon find_pokemon_by_name(json_response response, char* name);

#endif