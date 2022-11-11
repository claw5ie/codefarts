int
divisors(int n)
{
  int count = n == 1 ? 1 : 2;

  int i = 2;
  for (; i * i < n; i++)
    count += 2 * (n % i == 0);

  return count + (i * i == n);
}
