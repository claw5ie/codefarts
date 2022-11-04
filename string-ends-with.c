#include <string.h>
#include <stdbool.h>

bool
solution(const char *str, const char *end)
{
  size_t len0 = strlen(str), len1 = strlen(end);

  while (len0 > 0 && len1 > 0)
    if (str[--len0] != end[--len1])
      return false;

  return len1 == 0;
}
