#include "./datafinders/file_helper/file_helper.h"
#include "./datafinders/pokemon/pokemon.h"
#include "./datafinders/type/type.h"

int main(void) {
    char* file_content_pokemon = readJsonFile("data/pokemons.json");
    json_response response_pokemon = parseJson(file_content_pokemon);

    pokemon pokemon_1 = find_pokemon_by_id(response_pokemon, 1);
    printf("Founded pokemon by id : %s\n", pokemon_1.name);

    pokemon pokemon_2 = find_pokemon_by_name(response_pokemon, pokemon_1.name);
    printf("Founded pokemon by name : %s\n", pokemon_2.name);

    char* file_content_type = readJsonFile("data/types.json");
    json_response response_type = parseJson(file_content_type);

    pokemon_type type_1 = find_pokemon_type_by_id(response_type, pokemon_1.type_1);
    printf("Founded type of %s by id : %s\n", pokemon_1.name, type_1.name);

    pokemon_type type_2 = find_pokemon_type_by_name(response_type, type_1.name);
    printf("Founded type by his own name : %s\n", type_2.name);

    return 1;
}