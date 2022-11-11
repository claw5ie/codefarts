#include <cstdio>
#include <string>

using namespace std;

string
seriesSum(int n)
{
  double sum = 0;

  while (n-- > 0)
    sum += 1.0 / (3 * n + 1);

  string res;
  res.resize(64);
  res.resize(sprintf(&res[0], "%.2f", sum));

  return res;
}
