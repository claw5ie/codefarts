#include <string>

using namespace std;

bool
expand_string(string &front, string &back)
{
  auto find_next_closing_paren_and_expand
    = [&front, &back](int repeat_count, size_t start) -> size_t
    {
      size_t end = start;
      for (int open_paren_count = 1; end < front.size(); end++)
        {
          open_paren_count += (front[end] == '(');
          open_paren_count -= (front[end] == ')');

          if (open_paren_count == 0)
            break;
        }

      while (repeat_count-- > 0)
        back += string(front, start, end - start);

      return end;
    };

  bool has_more_expansions = false;

  back.resize(0);
  for (size_t i = 0; i < front.size(); i++)
    {
      if (front[i] == '(')
        {
          has_more_expansions = true;
          i = find_next_closing_paren_and_expand(1, i + 1);
        }
      else if (isdigit(front[i]))
        {
          has_more_expansions = true;
          i = find_next_closing_paren_and_expand(front[i] - '0', i + 2);
        }
      else
        back.push_back(front[i]);
    }

  return has_more_expansions;
}

string
solve(const string &s)
{
  string front = s, back;

  while (expand_string(front, back))
    front.swap(back);

  return back;
}
