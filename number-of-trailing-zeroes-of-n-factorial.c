#define LAST(arr) arr[sizeof(arr) / sizeof(*arr) - 1]

long
zeros(long n)
{
  static char pattern2[] = { 1, 3, 4, 7, 8, 10, 11, 15, 16, 18, 19, 22, 23, 25, 26 };
  static char pattern5[] = { 1, 2, 3, 4, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 18, 19, 20, 21, 22, 24, 25, 26, 27, 28 };

  long twos = pattern2[(n / 2) % 16 - 1]
    + (n / 32) * LAST(pattern2);
  long fives = pattern5[(n / 5) % 25 - 1]
    + (n / 125) * LAST(pattern5);

  for (long i = 32; i <= n; i += 32)
    for (long tmp = i; tmp % 2 == 0; tmp /= 2)
      ++twos;

  for (long i = 125; i <= n; i += 125)
    for (long tmp = i; tmp % 5 == 0; tmp /= 5)
      ++fives;

  return twos < fives ? twos : fives;
}
