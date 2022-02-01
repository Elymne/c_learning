#include <stdlib.h>

typedef struct pokemon {
    int id;
    char* name;
    int type_1;
    int type_2;
    int next_evolution;
} pokemon;

static int get_id_key(int i);
static int get_name_key(int i);
static int get_type_1_key(int i);
static int get_type_2_key(int i);
static int get_next_evolution_key(int i);

pokemon find_pokemon_by_id(json_response response, int id);
pokemon find_pokemon_by_name(json_response response, char* name);

pokemon find_pokemon_by_id(json_response response, int id) {
    if (response.tokens[0].type != JSMN_ARRAY) {
        printf("Array expected\n");
        pokemon result = {1, "oui", 1, 1, 1};
        return result;
    }

    for (int i = 1; i < response.nb; i++) {
        if (response.tokens[i].type == JSMN_OBJECT) {
            if (atoi(read_token(response.file_content, response.tokens[get_id_key(i)].start, response.tokens[get_id_key(i)].end)) == id) {
                pokemon pok = {
                    atoi(read_token(response.file_content, response.tokens[get_id_key(i)].start, response.tokens[get_id_key(i)].end)),
                    read_token(response.file_content, response.tokens[get_name_key(i)].start, response.tokens[get_name_key(i)].end),
                    atoi(read_token(response.file_content, response.tokens[get_type_1_key(i)].start, response.tokens[get_type_1_key(i)].end)),
                    atoi(read_token(response.file_content, response.tokens[get_type_2_key(i)].start, response.tokens[get_type_2_key(i)].end)),
                    atoi(read_token(response.file_content, response.tokens[get_next_evolution_key(i)].start, response.tokens[get_next_evolution_key(i)].end)),
                };
                return pok;
            }
        }
    }

    pokemon none = {1, "oui", 1, 1, 1};
    return none;
}

static int get_id_key(int i) {
    return i + 2;
}

static int get_name_key(int i) {
    return i + 4;
}

static int get_type_1_key(int i) {
    return i + 6;
}

static int get_type_2_key(int i) {
    return i + 8;
}

static int get_next_evolution_key(int i) {
    return i + 10;
}