#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "./external_lib/jsmn.h"
#include "./src/file_helper.h"

int main(void) {
    char* file_content = readJsonFile("data/pokemons.json");
    json_response response = parseJson(file_content);

    free((char*)file_content);
    free((jsmntok_t*)response.data);

    return 1;
}
