#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../external_lib/jsmn.h"

typedef struct {
    int nb;
    jsmntok_t *data;
} json_response;

char *readJsonFile(char *filename);
off_t fsize(char *filename);
json_response parseJson(char *file_content);

char *readJsonFile(char *filename) {
    long file_size = fsize(filename);
    if (file_size == -1) return NULL;

    char *file_content = (char *)malloc(file_size);
    FILE *json_file = fopen(filename, "rb");
    fread(file_content, sizeof(char), file_size, json_file);
    return file_content;
}

off_t fsize(char *filename) {
    struct stat st;
    if (stat(filename, &st) == 0) return st.st_size;
    return -1;
}

json_response parseJson(char *file_content) {
    jsmn_parser parser_to_count;
    jsmn_init(&parser_to_count);
    int num_tokkens = jsmn_parse(&parser_to_count, file_content, strlen(file_content), NULL, -1);

    jsmntok_t *tokens = malloc(sizeof(jsmntok_t) * num_tokkens);
    jsmn_parser parser;
    jsmn_init(&parser);
    jsmn_parse(&parser, file_content, strlen(file_content), tokens, num_tokkens);

    json_response response = {num_tokkens, tokens};
    return response;
}
