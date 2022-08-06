#include "string_commun_service.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* string_concat(const char* str1, const char* str2) {
    char* result = (char*) malloc(strlen(str1) + strlen(str2) + 1);
    if (result == NULL) {
        return NULL;
    }
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

char* int_to_string(int n) {
    char* result = (char*) malloc(sizeof(int) * 10);
    if (result == NULL) {
        return NULL;
    }
    sprintf(result, "%d", n);
    return result;
}