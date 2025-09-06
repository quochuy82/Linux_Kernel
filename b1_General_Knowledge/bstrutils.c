#include "strutils.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

void str_reverse(char *str) {
    if (!str) return;
    int len = strlen(str);
    int i = 0, j = len - 1;
    while (i < j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

void str_trim(char *str) {
    if (!str) return;
    int len = strlen(str);
    char *start = str;
    char *end = str + len - 1;

    while (isspace((unsigned char)*start)) {
        start++;
    }

    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }
    *(end + 1) = '\0';

    if (str != start) {
        memmove(str, start, end - start + 2);
    }
}

int str_to_int(const char *str, int *out) {
    char *endptr;
    long val = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        return -1; 
    }

    *out = (int)val;
    return 0; 
}