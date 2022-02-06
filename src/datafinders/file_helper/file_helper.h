#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../../../external_libs/jsmn.h"

typedef struct json_response {
    int nb;
    jsmntok_t *tokens;
    char *file_content;
} json_response;

char *readJsonFile(char *filename);
json_response parseJson(char *file_content);
int jsoneq(char *json, jsmntok_t *tok, char *s);
char *read_token(char *file_content, int from, int to);

#endif