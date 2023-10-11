#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int start;
  int stop;
  int step;
  int current;
} range;

void argparse(int argc, char *argv[], int *start, int *stop, int *step) {
  switch (argc) {
    case 1:
      printf("Usage:\n");
      printf("\t%s stop\n", argv[0]);
      printf("\t%s start stop\n", argv[0]);
      printf("\t%s start stop step\n", argv[0]);
      exit(1);
      break;
    case 2:
      *start = 0;
      *stop = atoi(argv[1]);
      *step = 1;
      break;
    case 3:
      *start = atoi(argv[1]);
      *stop = atoi(argv[2]);
      *step = 1;
      break;
    case 4:
      *start = atoi(argv[1]);
      *stop = atoi(argv[2]);
      *step = atoi(argv[3]);
      break;
  }
}

void range_init(range *I) { I->current = I->start; }

bool range_run(range *I) { return I->current < I->stop; }

void range_next(range *I) { I->current += I->step; }

int range_get(range *I) { return I->current; }

int main(int argc, char *argv[]) {
  range I;
  argparse(argc, argv, &I.start, &I.stop, &I.step);

  for (range_init(&I); range_run(&I); range_next(&I)) {
    printf("%d\n", range_get(&I));
  }

  return 0;
}