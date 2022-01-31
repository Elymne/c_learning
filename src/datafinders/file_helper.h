#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../../external_lib/jsmn.h"

typedef struct {
    int nb;
    jsmntok_t *tokens;
    char *file_content;
} json_response;

const char *readJsonFile(const char *filename);
const json_response parseJson(const char *file_content);
int jsoneq(const char *json, jsmntok_t *tok, const char *s);
static off_t fsize(const char *filename);

/**
 * @brief Use it to return string data of a file.
 *
 * @param filename String value of filename to read.
 * @return String content of file.
 */
const char *readJsonFile(const char *filename) {
    long file_size = fsize(filename);
    if (file_size == -1) return NULL;

    char *file_content = (char *)malloc(file_size);
    FILE *json_file = fopen(filename, "rb");
    fread(file_content, sizeof(char), file_size, json_file);
    return file_content;
}

/**
 * @brief Use this to parse data and get a structure that represent a json response.
 * The stucture that you'll get contains everything you need for datafinds functions.
 *
 * @param file_content String value of file content.
 * @return Response stucture.
 */
const json_response parseJson(const char *file_content) {
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

/**
 * @brief Use this while looping in data of response struct (json_response) to find specific key of json value.
 * You should use json_response structure attributes from parseJson function.
 *
 * @param file_content String content of a file from json_response struct.
 * @param tokens Array of tokens from a json_response struct.
 * @param s
 * @return const int
 */
const int check_tokken_value(const char *file_content, jsmntok_t *tokens, const char *key) {
    if (tokens->type == JSMN_STRING && (int)strlen(key) == tokens->end - tokens->start &&
        strncmp(file_content + tokens->start, key, tokens->end - tokens->start) == 0) {
        return 1;
    }
    return 0;
}

/**
 * @brief Use this to get the size in byte of a file.
 * Usefull to allocate enought space to read a file for example.
 * Usage in :
 *  - readJsonFile() function.
 *
 * @param filename String taht reprensent name of the file.
 * @return A long value that represent the size.
 */
static const off_t fsize(const char *filename) {
    struct stat st;
    if (stat(filename, &st) == 0) return st.st_size;
    return -1;
}