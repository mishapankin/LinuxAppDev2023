#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int steps[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int size = 13;
char wall = '#';
char path = '.';

char get(int x, int y, char *labyrinth) {
    return labyrinth[x * size + y];
}

char set(int x, int y, char *labyrinth, char value) {
    labyrinth[x * size + y] = value;
}

void fill_labyrinth(int x, int y, char *labyrinth) {
    unsigned been = 0;
    for (int i = 0; i < 4;) {
        unsigned step = rand() % 4;

        if (been & (1 << step)) {
            continue;
        }
        been |= 1 << step;
        ++i;

        int new_x = x + steps[step][0] * 2;
        int new_y = y + steps[step][1] * 2;

        if (new_x < 1 || new_x >= size - 1 || new_y < 1 || new_y >= size - 1) {
            continue;
        }

        if (get(new_x, new_y, labyrinth) == wall) {
            set(x + steps[step][0], y + steps[step][1], labyrinth, path);
            set(new_x, new_y, labyrinth, path);
            fill_labyrinth(new_x, new_y, labyrinth);
        }
    }
}

int main(int argc, char **argv) {
    srand(time(NULL));
    if (argc == 2) {
        size = atoi(argv[1]);
    }
    if (argc == 3) {
        path = argv[1][0];
        wall = argv[1][1];
        size = atoi(argv[2]);
    }

    char *labyrinth = malloc(size * size * sizeof(char));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            set(i, j, labyrinth, wall);
        }
    }

    fill_labyrinth(1, 1, labyrinth);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%c", get(i, j, labyrinth));
        }
        printf("\n");
    }

    free(labyrinth);

    return 0;
}