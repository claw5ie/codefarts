#include <vector>

using namespace std;

vector<int>
move_zeroes(const vector<int> &input)
{
  vector<int> res;

  for (auto elem: input)
    if (elem != 0)
      res.push_back(elem);

  for (size_t i = input.size() - res.size(); i-- > 0; )
    res.push_back(0);

  return res;
}
