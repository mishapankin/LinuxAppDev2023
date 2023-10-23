#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    ERR_BUFF_SIZE = 1024,
};

void print_error(int errcode, regex_t *regex) {
    char *errbuf = malloc(ERR_BUFF_SIZE);
    regerror(errcode, regex, errbuf, ERR_BUFF_SIZE);

    printf("Error: %s\n", errbuf);
    free(errbuf);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s <regexp> <substitution> <string>\n", argv[0]);
        return 1;
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

    regmatch_t match[1];

    errcode = regexec(&regex, string, 1, match, 0);
    if (errcode) {
        printf("%s\n", string);
        return 0;
    }

    memset(string + match->rm_so, 0, match->rm_eo - match->rm_so);

    printf("%s%s%s\n", string, substitution, string + match->rm_eo);

    regfree(&regex);
}