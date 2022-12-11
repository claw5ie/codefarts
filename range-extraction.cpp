#include <vector>
#include <string>

using namespace std;

string
range_extraction(vector<int> args)
{
  string res;

  for (size_t i = 0; i < args.size(); i++)
    {
      size_t j = i;
      while (j + 1 < args.size() && args[j + 1] == args[j] + 1)
        ++j;

      res += to_string(args[i]);

      if (i != j)
        {
          if (j - i == 1)
            {
              res.push_back(',');
              res += to_string(args[j]);
            }
          else
            {
              res.push_back('-');
              res += to_string(args[j]);
            }

          i = j;
        }

      res.push_back(',');
    }

  // Remove trailing comma.
  res.pop_back();

  return res;
}
