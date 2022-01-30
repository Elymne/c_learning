#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "./external_lib/jsmn.h"
#include "./src/file_helper.h"

int main(void) {
    const char* file_content = readJsonFile("data/pokemon.json");
    const jsmntok_t* parsedJson = parseJson(file_content);

    free((char*)file_content);
    free((jsmntok_t*)parsedJson);

    return 1;
}
