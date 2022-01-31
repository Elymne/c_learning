#include "./file_helper.h"

typedef struct {
    int id;
    char* name;
    int type_1;
    int type_2;
    int next_evolution;
} pokemon;

pokemon find_pokemon_by_id(jsmntok_t* data, int id);
pokemon find_pokemon_by_name(jsmntok_t* data, char* name);

pokemon find_pokemon_by_id(json_response response, int id) {
    if (response.tokens[0].type != JSMN_ARRAY) {
        printf("Array expected\n");
        return;
    }

    for (int i = 1; i < response.nb; i++) {
        if (jsoneq((char*)response.file_content, &response.tokens[i], "user")) {
        }
    }
}
