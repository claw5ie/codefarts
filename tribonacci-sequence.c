#include <stdlib.h>

long long *
tribonacci(const long long sig[3], size_t n)
{
  if (n == 0)
    return NULL;

  long long *seq = malloc(n * sizeof(*seq));
  seq[0] = sig[0];
  seq[1] = sig[1];
  seq[2] = sig[2];

  for (size_t i = 3; i < n; i++)
    seq[i] = seq[i - 1] + seq[i - 2] + seq[i - 3];

  return seq;
}
