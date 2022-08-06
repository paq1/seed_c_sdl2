#include "string_commun_service_spec.h"

#include "../../../../src/core/services/string/string_commun_service.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool should_be_true_when_strings_concat() {
    char* hello = "Hello ";
    char* world = "world";

    char* result = string_concat(hello, world);
    char* expected = "Hello world";

    bool result_is_expected = strcmp(result, expected) == 0;

    free(result);

    return result_is_expected;
}

bool should_be_true_when_int_to_string() {
    int n = 42;

    char* result = int_to_string(n);
    char* expected = "42";

    bool result_is_expected = strcmp(result, expected) == 0;

    free(result);

    return result_is_expected;
}
