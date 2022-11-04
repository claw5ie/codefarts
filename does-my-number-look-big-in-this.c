#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

int
powi(int b, int e)
{
  if (e == 0)
    return 1;

  int res = powi(b, e / 2);
  res *= res;

  if (e % 2 == 0)
    return res;
  else
    return b * res;
}

bool
narcissistic(int n)
{
  static char digits[(sizeof(int) * CHAR_BIT) / 2];

  size_t count = 0;

  for (int tmp = n; tmp != 0; tmp /= 10)
    digits[count++] = tmp % 10;

  for (size_t i = count; i-- > 0; )
    n -= powi(digits[i], count);

  return n == 0;
}
