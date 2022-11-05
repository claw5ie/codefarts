#define LAST(arr) arr[sizeof(arr) / sizeof(*arr) - 1]

long
zeros(long n)
{
  static char pattern5[] = { 0, 1, 2, 3, 4, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 18, 19, 20, 21, 22, 24, 25, 26, 27, 28 };

  long fives = 0;

  for (long i = 5, j = 0; i <= n; i *= 25, j += 2)
    {
      long ind = n / i % 25;
      fives += j * ind + pattern5[ind]
        + n / (i * 25) * (LAST(pattern5) + j * 24);
    }

  return fives;
}
