#include <stdio.h>
#include <stdlib.h>

#include "core/services/string/string_commun_service_spec.h"

#ifdef _WIN32
#include <windows.h>
#endif

void check(bool test_result, const char* test_name);

void set_green();
void set_red();
void set_blue();
void reset_color();

int main(int argc, char* argv[]) {
    set_blue();
    printf("Test ----------------------- \n");

    check(should_be_true_when_strings_concat(), "should_be_true_when_strings_concat");
    check(should_be_true_when_int_to_string(), "should_be_true_when_int_to_string");

    printf("fin des tests ----------------------- \n");

    return EXIT_SUCCESS;
}

void check(bool test_result, const char* test_name) {
    if (test_result) {
        set_green();
    } else {
        set_red();
    }
    printf("%s\n", test_name);
    reset_color();
}

void set_green() {
    #ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    #endif
}

void set_red() {
    #ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    #endif
}

void set_blue() {
    #ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
    #endif
}

void reset_color() {
    #ifdef _WIN32
    set_blue();
    #endif
}
