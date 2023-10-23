#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GREEN "\033[0;32m"
#define END "\033[0m"

enum {
    ERR_BUFF_SIZE = 1024,
    MAX_MATCH = 128,
};

bool use_color = true;

void print_error(int errcode, regex_t *regex) {
    char errbuf[ERR_BUFF_SIZE];
    regerror(errcode, regex, errbuf, ERR_BUFF_SIZE);

    printf("Error: %s\n", errbuf);
}

void replace_matches(char *string, char *substitution, regmatch_t *matches) {
    printf("%.*s", matches[0].rm_so, string);

    if (use_color) {
        printf(GREEN);
    }

    while (*substitution) {
        if (*substitution != '\\') {
            printf("%c", *substitution);
            substitution++;
        } else {
            int i = 0, shift = 0;
            sscanf(substitution, "\\%d%n", &i, &shift);

            printf("%.*s", matches[i].rm_eo - matches[i].rm_so,
                   string + matches[i].rm_so);

            substitution += shift;
        }
    }

    if (use_color) {
        printf(END);
    }
    printf("%s\n", string + matches[0].rm_eo);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s <regexp> <substitution> <string> [-nc]\n", argv[0]);
        printf("Optional: -nc (no color)\n");
        return 1;
    }

    if (argc > 4 && strcmp(argv[4], "-nc") == 0) {
        use_color = false;
    }

    char *regexp = argv[1];
    char *substitution = argv[2];
    char *string = argv[3];

    regex_t regex;
    int errcode = regcomp(&regex, regexp, REG_EXTENDED);
    if (errcode) {
        print_error(errcode, &regex);
        return 1;
    }

    regmatch_t matches[MAX_MATCH];

    errcode = regexec(&regex, string, MAX_MATCH, matches, 0);
    if (errcode) {
        printf("%s\n", string);
        return 0;
    }

    replace_matches(string, substitution, matches);

    regfree(&regex);
}