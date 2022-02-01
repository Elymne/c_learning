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

    pokemon poki = find_pokemon_by_id(response, 1);
    printf("%s", poki.name);

    free((char*)file_content);
    free((jsmntok_t*)response.tokens);

    return 1;
}