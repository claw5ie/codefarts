int
digital_root(int n)
{
  do
    {
      int root = 0;

      while (n != 0)
        {
          root += n % 10;
          n /= 10;
        }

      n = root;
    }
  while (n > 9);

  return n;
}
