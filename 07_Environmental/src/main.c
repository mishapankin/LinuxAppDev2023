#include <ctype.h>
#include <rhash.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef READLINE_ENABLED
#include <readline/readline.h>
#endif

enum {
    BUFF_SIZE = 1024,
};

void upper(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

void print_hash(unsigned int algo, bool hex, char *str) {
    printf("%s\n", str);

    unsigned char hash[32];
    rhash_msg(algo, str, strlen(str), hash);

    if (hex) {
        char hex_output[65];
        rhash_print_bytes(hex_output, hash, rhash_get_digest_size(algo),
                          RHPR_HEX);

        printf("%s\n", hex_output);
    } else {
        char base64_output[45];
        rhash_print_bytes(base64_output, hash, rhash_get_digest_size(algo),
                          RHPR_BASE64);

        printf("%s\n", base64_output);
    }
}

int main() {
    rhash_library_init();

    char *line = NULL;
    size_t n;

#ifndef READLINE_ENABLED
    while (getline(&line, &n, stdin) != -1) {
#else
    while ((line = readline("> ")) != NULL) {
#endif

        char *algo_str = strtok(line, " \t");
        char *str = strtok(NULL, " \t\n");

        if (algo_str == NULL || str == NULL) {
            fprintf(stderr, "Invalid input\n");
            continue;
        }

        unsigned int id = 0;
        bool hex = 'A' <= algo_str[0] && algo_str[0] <= 'Z';

        upper(algo_str);
        if (strcmp(algo_str, "MD5") == 0) {
            id = RHASH_MD5;
        } else if (strcmp(algo_str, "SHA1") == 0) {
            id = RHASH_SHA1;
        } else if (strcmp(algo_str, "TTH") == 0) {
            id = RHASH_TTH;
        } else {
            fprintf(stderr, "Unknown algorithm: %s\n", algo_str);
            continue;
        }

        char buff[BUFF_SIZE];

        if (str[0] == '"') {
            strncpy(buff, str + 1, strlen(str) - 2);
        } else {
            FILE *fin = fopen(str, "r");
            if (fin == NULL) {
                fprintf(stderr, "Cannot open file: %s\n", str);
                continue;
            }

            fread(buff, sizeof(char), BUFF_SIZE, fin);

            fclose(fin);
        }

        print_hash(id, hex, buff);
    }

    printf("\n");
    free(line);
}
