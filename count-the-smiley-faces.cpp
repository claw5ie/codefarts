#include <string>

using namespace std;

char automaton[5][7]
  = { { 0, 0, 0, 0, 0, 0, 0 },
      { 2, 2, 0, 0, 0, 0, 0 },
      { 0, 0, 3, 3, 4, 4, 0 },
      { 0, 0, 0, 0, 4, 4, 0 },
      { 0, 0, 0, 0, 0, 0, 0 } };

int
char_to_trans(char ch)
{
  switch (ch)
    {
    case ':': return 0;
    case ';': return 1;
    case '-': return 2;
    case '~': return 3;
    case ')': return 4;
    case 'D': return 5;
    default:
      return 6;
    }
}

int
countSmileys(vector<string> arr)
{
  int count = 0;

  for (auto &smiley: arr)
    {
      int state = 1;

      for (auto ch: smiley)
        state = automaton[state][char_to_trans(ch)];

      count += state == 4;
    }

  return count;
}
