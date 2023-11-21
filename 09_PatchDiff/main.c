#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int steps[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

char get(int x, int y, char *labyrinth) {
    return labyrinth[x * 13 + y];
}

char set(int x, int y, char *labyrinth, char value) {
    labyrinth[x * 13 + y] = value;
}

void fill_labyrinth(int x, int y, char *labyrinth) {
    unsigned been = 0;
    for (int i = 0; i < 4;) {
        int step = rand() % 4;

        if (been & (1 << step)) {
            been |= 1 << step;
            continue;
        }
        ++i;

        int new_x = x + steps[step][0] * 2;
        int new_y = y + steps[step][1] * 2;

        if (new_x < 0 || new_x >= 13 || new_y < 0 || new_y >= 13) {
            continue;
        }

        if (get(new_x, new_y, labyrinth) == '#') {
            set(x + steps[step][0], y + steps[step][1], labyrinth, '.');
            set(new_x, new_y, labyrinth, '.');
            fill_labyrinth(new_x, new_y, labyrinth);
        }
    }
}

int main() {
    srand(time(NULL));

    char *labyrinth = malloc(13 * 13 * sizeof(char));

    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 13; ++j) {
            set(i, j, labyrinth, '#');
        }
    }

    fill_labyrinth(1, 1, labyrinth);

    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 13; ++j) {
            printf("%c", get(i, j, labyrinth));
        }
        printf("\n");
    }

    free(labyrinth);

    return 0;
}