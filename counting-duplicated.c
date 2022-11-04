#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include <limits.h>

size_t
duplicate_count(const char *text)
{
  static int lookup[CHAR_MAX];

  memset(lookup, 0, CHAR_MAX * sizeof(*lookup));

  while (*text != '\0')
    ++lookup[tolower(*text++)];

  size_t count = 0;

  for (size_t i = 0; i < CHAR_MAX; i++)
    count += lookup[i] > 1;

  return count;
}
