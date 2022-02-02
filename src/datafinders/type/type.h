#ifndef TYPE_H
#define TYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../file_helper/file_helper.h"

typedef struct pokemon_type {
    int id;
    char* name;
} pokemon_type;

pokemon_type find_pokemon_type_by_id(json_response response, int id);
pokemon_type find_pokemon_type_by_name(json_response response, char* name);

#endif