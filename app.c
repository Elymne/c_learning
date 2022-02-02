#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "./external_lib/jsmn.h"
#include "./src/datafinders/file_helper.h"
#include "./src/datafinders/pokemon.h"

int main(void) {
    char* file_content = readJsonFile("data/pokemons.json");
    json_response response = parseJson(file_content);

    pokemon test_1 = find_pokemon_by_id(response, 1);
    printf("Founded pokemon by id : %s\n", test_1.name);

    printf("\n");

    pokemon test_2 = find_pokemon_by_name(response, test_1.name);
    printf("Founded pokemon by name : %s\n", test_2.name);

    return 1;
}