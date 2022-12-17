#include <stddef.h>

int
gcd(int a, int b)
{
  while (b != 0)
    {
      a %= b;

      int tmp = a;
      a = b;
      b = tmp;
    }

  return a;
}

int
smallest_possible_sum(size_t n, const int arr[n])
{
  int res = 0;

  for (size_t i = 0; i < n; i++)
    res = gcd(arr[i], res);

  return res * n;
}
