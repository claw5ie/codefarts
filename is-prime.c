#include <stdbool.h>
#include <stddef.h>

bool
is_prime(int n)
{
  if (n < 2 || n == 4)
    return false;

  for (size_t i = 2; i * i <= n; i++)
    if (n % i == 0)
      return false;

  return true;
}
