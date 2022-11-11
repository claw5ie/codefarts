#include <string>

using namespace std;

string
cleanString(const string &s)
{
  string res;

  for (auto ch: s)
    {
      if (ch != '#')
        res.push_back(ch);
      else if (res.size() > 0)
        res.pop_back();
    }

  return res;
}
