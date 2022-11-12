#include <vector>

using namespace std;

static
long
findMissing(vector<long> list)
{
  if (list.size() == 3)
    {
      long diff0 = list[1] - list[0], diff1 = list[2] - list[1];

      if (diff0 - diff1 > 0)
        return list[0] + diff1;
      else
        return list[1] + diff0;
    }

  long diff = list[1] - list[0];

  if (diff != list[2] - list[1])
    diff = list[3] - list[2];

  for (size_t i = 1; i < list.size(); i++)
    if (list[i] - list[i - 1] != diff)
      return list[i - 1] + diff;

  return 0;
}
