#include <vector>

using namespace std;

class Dioph
{
public:
  static
  vector<pair<long, long>>
  solEquaStr(long long n)
  {
    vector<pair<long, long>> res;

    for (long long i = 1; i * i <= n; i++)
      {
        if (n % i == 0)
          {
            long y = n / i, x = y + i;

            if (x % 2 == 0)
              {
                x /= 2;
                y -= x;
                if (y % 2 == 0)
                  res.emplace_back(x, y /= 2);
              }
          }
      }

    return res;
  }
};
