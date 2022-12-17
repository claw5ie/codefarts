#include <malloc.h>
#include <string.h>

char *
strsum(const char *a, const char *b)
{
  while (*a == '0')
    ++a;

  while (*b == '0')
    ++b;

  size_t a_len = strlen(a);
  size_t b_len = strlen(b);
  size_t r_len = (a_len > b_len ? a_len : b_len) + 1;
  char *r = malloc(r_len + 1);

  int rem = 0;
  for (size_t i = 0; i < r_len; i++)
    {
      rem += (i < a_len ? a[a_len - 1 - i] : '0') - '0'
             + (i < b_len ? b[b_len - 1 - i] : '0') - '0';
      r[r_len - 1 - i] = rem % 10 + '0';
      rem /= 10;
    }

  r[r_len] = '\0';
  if (r[0] == '0' && r_len > 1)
    {
      memmove(r, r + 1, r_len - 1);
      r[r_len - 1] = '\0';
    }

  return r;
}
