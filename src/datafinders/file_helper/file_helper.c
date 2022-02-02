#include "file_helper.h"

static off_t fsize(char *filename) {
    struct stat st;
    if (stat(filename, &st) == 0) return st.st_size;
    return -1;
}

char *readJsonFile(char *filename) {
    long file_size = fsize(filename);
    if (file_size == -1) return NULL;

    char *file_content = (char *)malloc(file_size);
    FILE *json_file = fopen(filename, "rb");
    fread(file_content, sizeof(char), file_size, json_file);
    return file_content;
}

json_response parseJson(char *file_content) {
    jsmn_parser parser_to_count;
    jsmn_init(&parser_to_count);
    int num_tokkens = jsmn_parse(&parser_to_count, file_content, strlen(file_content), NULL, -1);

    jsmntok_t *tokens = malloc(sizeof(jsmntok_t) * num_tokkens);
    jsmn_parser parser;
    jsmn_init(&parser);
    jsmn_parse(&parser, file_content, strlen(file_content), tokens, num_tokkens);

    json_response response = {num_tokkens, tokens, file_content};
    return response;
}

int check_tokken_value(char *file_content, jsmntok_t *tokens, char *key) {
    if (tokens->type == JSMN_STRING && (int)strlen(key) == tokens->end - tokens->start &&
        strncmp(file_content + tokens->start, key, tokens->end - tokens->start) == 0) {
        return 1;
    }
    return 0;
}

char *read_token(char *file_content, int start, int end) {
    char *value = (char *)malloc(sizeof(char) * (end - start));
    strncpy(value, file_content + start, end - start);
    return value;
}
