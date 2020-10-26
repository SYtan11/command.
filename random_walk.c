#include <stdio.h>
#include <stdlib.h>

double frand(void);

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "How to use: random_walk n seed");
    exit(1);
  }
  int n = atoi(argv[1]);
  if (n <= 0) {
    fprintf(stderr, "%d n must be positive\n", n);
    exit(1);
  }
  int seed = atoi(argv[2]);
  if (seed <= 0) {
    fprintf(stderr, "seed must be ? ");
    exit(1);
  }

  srand(seed);
  double x = 0.0, y = 0.0;
  printf("%lf %lf\n", x, y);

  // random walk
  for (int i = 0; i < n; i++) {
    x += (frand() - 0.5) * 2;
    y += (frand() - 0.5) * 2;

    printf("%lf %lf\n", x, y);
  }

  return 0;
}

double frand(void) { return (double)rand() / RAND_MAX; }