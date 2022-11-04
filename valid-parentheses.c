#include <stdbool.h>

bool
validParentheses(const char *str)
{
  int count = 0;

  while (*str != '\0')
    {
      count += *str == '(';
      count -= *str++ == ')';

      if (count < 0)
        return false;
    }

  return count == 0;
}
