#include <string>

using namespace std;

string
format_duration(int seconds)
{
  if (seconds == 0)
    return "now";

  static int values[5];
  static unsigned types[5];
  static const char *names[5]
    = { " year",
        " day",
        " hour",
        " minute",
        " second" };
  static int const secs[5]
    = { 365 * 24 * 60 * 60,
        24 * 60 * 60,
        60 * 60,
        60,
        1 };

  size_t count = 0;
  for (size_t i = 0; i < 5; i++)
    {
      values[count] = seconds / secs[i];
      types[count] = i;
      seconds %= secs[i];
      // Advance forward if value is non-zero.
      count += (values[count] != 0);
    }

  string res;
  for (size_t i = 0; i < count; i++)
    {
      if (i > 0)
        {
          if (i < count - 1)
            res += ", ";
          else if (i == count - 1)
            res += " and ";
        }

      res += to_string(values[i]);
      res += names[types[i]];

      if (values[i] > 1)
        res.push_back('s');
    }

  return res;
}
