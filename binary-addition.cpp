#include <cstdint>
#include <string>
#include <algorithm>

using namespace std;

string
add_binary(uint64_t a, uint64_t b)
{
  a += b;

  string res;

  do
    {
      res.push_back(a % 2 + '0');
      a /= 2;
    }
  while (a != '\0');

  reverse(res.begin(), res.end());

  return res;
}
