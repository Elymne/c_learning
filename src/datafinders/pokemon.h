#include <stdlib.h>

typedef struct pokemon {
    int id;
    char* name;
    int type_1;
    int type_2;
    int next_evolution;
} pokemon;

static int get_id_key(int i);
static int get_id_value(json_response response, int i);

static int get_name_key(int i);
static char* get_name_value(json_response response, int i);

static int get_type_1_key(int i);
static int get_type_1_value(json_response response, int i);

static int get_type_2_key(int i);
static int get_type_2_value(json_response response, int i);

static int get_next_evolution_key(int i);
static int get_next_evolution_value(json_response response, int i);

static pokemon create_pokemon_object(json_response response, int i);
static pokemon create_undifined_pokemon_object();

pokemon find_pokemon_by_id(json_response response, int id);
pokemon find_pokemon_by_name(json_response response, char* name);

/**
 * @brief Get a pokemon Object by id.
 *
 * @param response
 * @param id
 * @return pokemon
 */
pokemon find_pokemon_by_id(json_response response, int id) {
    if (response.tokens[0].type != JSMN_ARRAY) {
        printf("Array expected in top parent while searching in pokemon.json\nCheck pokemon.json file\nValue return is pokemon object with undifined values\n");
        return create_undifined_pokemon_object();
    }
    for (int i = 1; i < response.nb; i++) {
        if (response.tokens[i].type == JSMN_OBJECT && get_id_value(response, i) == id) {
            return create_pokemon_object(response, i);
        }
    }
    printf("No value founded in pokemon.json file with id : %d\nValue return is pokemon object with undifined values\n", id);
    return create_undifined_pokemon_object();
}

/**
 * @brief Get a pokemon Object by id.
 *
 * @param response
 * @param id
 * @return pokemon
 */
pokemon find_pokemon_by_name(json_response response, char* name) {
    if (response.tokens[0].type != JSMN_ARRAY) {
        printf("Array expected in top parent while searching in pokemon.json\nCheck pokemon.json file\nValue return is pokemon object with undifined values\n");
        return create_undifined_pokemon_object();
    }
    for (int i = 1; i < response.nb; i++) {
        if (response.tokens[i].type == JSMN_OBJECT && strcmp(get_name_value(response, i), name) == 0) {
            return create_pokemon_object(response, i);
        }
    }
    printf("No value founded in pokemon.json file with name : %s\nValue return is pokemon object with undifined values\n", name);
    return create_undifined_pokemon_object();
}

// ================================================================================================================================================================================================================================================================================================================================================================================================================================================================
// static functions
// ================================================================================================================================================================================================================================================================================================================================================================================================================================================================

static int get_id_key(int i) {
    return i + 2;
}

static int get_id_value(json_response response, int i) {
    return atoi(read_token(response.file_content, response.tokens[get_id_key(i)].start, response.tokens[get_id_key(i)].end));
}

static int get_name_key(int i) {
    return i + 4;
}

static char* get_name_value(json_response response, int i) {
    return read_token(response.file_content, response.tokens[get_name_key(i)].start, response.tokens[get_name_key(i)].end);
}

static int get_type_1_key(int i) {
    return i + 6;
}

static int get_type_1_value(json_response response, int i) {
    return atoi(read_token(response.file_content, response.tokens[get_type_1_key(i)].start, response.tokens[get_type_1_key(i)].end));
}

static int get_type_2_key(int i) {
    return i + 8;
}

static int get_type_2_value(json_response response, int i) {
    return atoi(read_token(response.file_content, response.tokens[get_type_2_key(i)].start, response.tokens[get_type_2_key(i)].end));
}

static int get_next_evolution_key(int i) {
    return i + 10;
}

static int get_next_evolution_value(json_response response, int i) {
    return atoi(read_token(response.file_content, response.tokens[get_next_evolution_key(i)].start, response.tokens[get_next_evolution_key(i)].end));
}

static pokemon create_pokemon_object(json_response response, int i) {
    return (pokemon){
        get_id_value(response, i),
        get_name_value(response, i),
        get_type_1_value(response, i),
        get_type_2_value(response, i),
        get_next_evolution_value(response, i),
    };
}

static pokemon create_undifined_pokemon_object() {
    return (pokemon){0, "unknown", 0, 0, 0};
}