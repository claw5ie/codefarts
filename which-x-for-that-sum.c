#include <math.h>

double
solve(double m)
{
  double b = (1 + 0.5 / m);
  double d = sqrt(b * b - 1);
  double x = b + d;

  if (-1 < x && x < 1)
    return x;
  else
    return b - d;
}
