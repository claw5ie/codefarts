#include <cstring>
#include <string>

using namespace std;

bool
isAnagram(string s0, string s1)
{
  if (s0.size() != s1.size())
    return false;

  static int counts['z' - 'a' + 1];
  memset(counts, 0, sizeof(counts));

  for (size_t i = 0; i < s0.size(); i++)
    {
      --counts[tolower(s0[i]) - 'a'];
      ++counts[tolower(s1[i]) - 'a'];
    }

  for (auto count: counts)
    if (count != 0)
      return false;

  return true;
}
