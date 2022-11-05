#define LAST(arr) arr[sizeof(arr) / sizeof(*arr) - 1]

long
zeros(long n)
{
  static char pattern2[] = { 0, 1, 3, 4, 7, 8, 10, 11, 15, 16, 18, 19, 22, 23, 25, 26 };
  static char pattern5[] = { 0, 1, 2, 3, 4, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 18, 19, 20, 21, 22, 24, 25, 26, 27, 28 };

  long twos = 0, fives = 0;

  for (long i = 2, j = 0; i <= n; i *= 16, j += 4)
    {
      long ind = n / i % 16;
      twos += j * ind + pattern2[ind]
        + n / (i * 16) * (LAST(pattern2) + j * 15);
    }

  for (long i = 5, j = 0; i <= n; i *= 25, j += 2)
    {
      long ind = n / i % 25;
      fives += j * ind + pattern5[ind]
        + n / (i * 25) * (LAST(pattern5) + j * 24);
    }

  return twos < fives ? twos : fives;
}
