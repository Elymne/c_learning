#include "./../file_helper.h"

typedef struct {
    int id;
    char* name;
    int type_1;
    int type_2;
    int next_evolution;
} pokemon;

pokemon find_pokemon_by_id(jsmntok_t* data, int id);
pokemon find_pokemon_by_name(jsmntok_t* data, char* name);

pokemon find_pokemon_by_id(jsmntok_t* data, int id) {
    if (data[0].type != JSMN_OBJECT) {
        printf("Object expected\n");
        return;
    }
}
