#include <string.h>
#include <stdbool.h>

bool
scramble(const char *str1, const char *str2)
{
  static unsigned lookup['z' - 'a' + 1];
  memset(lookup, 0, sizeof(lookup));

  while (*str1 != '\0')
    ++lookup[*str1++ - 'a'];

  while (*str2 != '\0')
    if (lookup[*str2++ - 'a']-- == 0)
      return false;

  return true;
}
