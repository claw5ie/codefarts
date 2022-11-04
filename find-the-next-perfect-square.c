#include <limits.h>

long
findNextSquare(long n)
{
  long lower = 0, upper = (1l << (sizeof(long) * CHAR_BIT / 2)) + 1;

  while (lower < upper)
    {
      long mid = lower + (upper - lower) / 2;
      long square = mid * mid;

      if (square < n)
        lower = mid + 1;
      else if (square > n)
        upper = mid;
      else
        return square + 2 * mid + 1;
    }

  return -1;
}
