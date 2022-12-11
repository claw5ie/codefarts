typedef unsigned long long ull;

ull
perimeter(int n)
{
  ull x = 1, y = 1, z = 2;
  ull res = (n > 0) + (n > 1);

  while (--n > 0)
    {
      res += z;
      x = y;
      y = z;
      z = x + y;
    }

  return 4 * res;
}
