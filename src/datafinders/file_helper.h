#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../../external_lib/jsmn.h"

typedef struct json_response {
    int nb;
    jsmntok_t *tokens;
    char *file_content;
} json_response;

char *readJsonFile(char *filename);
json_response parseJson(char *file_content);
int jsoneq(char *json, jsmntok_t *tok, char *s);
char *read_token(char *file_content, int from, int to);

static off_t fsize(char *filename);

/**
 * @brief Use it to return string data of a file.
 *
 * @param filename String value of filename to read.
 * @return String content of file.
 */
char *readJsonFile(char *filename) {
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

/**
 * @brief Use this while looping in data of response struct (json_response) to find specific key of json value.
 * You should use json_response structure attributes from parseJson function.
 *
 * @param file_content String content of a file from json_response struct.
 * @param tokens Array of tokens from a json_response struct.
 * @param s
 * @return  int
 */
int check_tokken_value(char *file_content, jsmntok_t *tokens, char *key) {
    if (tokens->type == JSMN_STRING && (int)strlen(key) == tokens->end - tokens->start &&
        strncmp(file_content + tokens->start, key, tokens->end - tokens->start) == 0) {
        return 1;
    }
    return 0;
}

/**
 * @brief Get a string from first char to last char in a complete string content of file.
 *
 * @param file_content String content of file.
 * @param from First char to get
 * @param to Last char to get
 * @return String value
 */
char *read_token(char *file_content, int start, int end) {
    char *value = (char *)malloc(sizeof(char) * (end - start));
    strncpy(value, file_content + start, end - start);
    return value;
}

// ================================================================================================================================================================================================================================================================================================================================================================================================================================================================
// ? static functions ?
// ================================================================================================================================================================================================================================================================================================================================================================================================================================================================

/**
 * @brief Use this to get the size in byte of a file.
 * Usefull to allocate enought space to read a file for example.
 * Usage in :
 *  - readJsonFile() function.
 *
 * @param filename String taht reprensent name of the file.
 * @return A long value that represent the size.
 */
static off_t fsize(char *filename) {
    struct stat st;
    if (stat(filename, &st) == 0) return st.st_size;
    return -1;
}