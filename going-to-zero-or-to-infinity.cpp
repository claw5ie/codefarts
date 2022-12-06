class Suite
{
public:
  static
  double
  going(int n)
  {
    float term = 1, res = 0;

    while (n > 0)
      {
        res += term;
        term /= n--;
      }

    return res;
  }
};
