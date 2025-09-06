#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strutils.h"

static void read_line(char *buf, size_t sz) {
    if (fgets(buf, sz, stdin)) {
        buf[strcspn(buf, "\n")] = 0;
    } else {
        buf[0] = '\0';
        clearerr(stdin);
    }
}

int main(void) {
    char input[256];
    char choice_line[32];

    for (;;) {
        printf("==== strutils option ====\n");
        printf("1) Reverse string\n");
        printf("2) Trim string\n");
        printf("3) Convert string to int\n");
        printf("0) Exit\n");
        printf("Enter choice: ");
        read_line(choice_line, sizeof(choice_line));

        int choice = -1;
        if (sscanf(choice_line, "%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n\n");
            continue;
        }
        if (choice == 0) break;

        printf("Enter your string: ");
        read_line(input, sizeof(input));

        switch (choice) {
            case 1:
                printf("Original : '%s'\n", input);
                str_reverse(input);
                printf("Reversed : '%s'\n\n", input);
                break;

            case 2:
                printf("Original : '%s'\n", input);
                str_trim(input);
                printf("Trimmed  : '%s'\n\n", input);
                break;

            case 3: {
                int value;
                int rc = str_to_int(input, &value);
                if (rc == 0) {
                    printf("Converted number: %d\n\n", value);
                } else {
                    printf("Invalid number (err=%d): '%s'\n\n", rc, input);
                }
                break;
            }

            default:
                printf("Invalid choice!\n\n");
        }
    }
    return 0;
}
