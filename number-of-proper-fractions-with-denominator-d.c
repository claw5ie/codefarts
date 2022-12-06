long
properFractions(long n)
{
  if (n < 2)
    return 0;

  long res = 1;

  for (long i = 2; i * i <= n; i++)
    {
      if (n % i == 0)
        {
          long powah = 1;
          while ((n /= i) % i == 0)
            powah *= i;

          res *= powah * (i - 1);
        }
    }

  if (n > 1)
    res *= n - 1;

  return res;
}
