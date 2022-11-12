#include <vector>

using namespace std;

typedef unsigned long long ullint;

vector<ullint>
partsSum(const vector<ullint> &ls)
{
  auto res = ls;
  res.push_back(0);

  for (size_t i = res.size() - 1; i-- > 0; )
    res[i] += res[i + 1];

  return res;
}
