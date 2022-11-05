#include <stdlib.h>
#include <string.h>

char *
multiply(char *a0, char *a1)
{
  while (*a0 == '0')
    ++a0;

  while (*a1 == '0')
    ++a1;

  if (*a0 == '\0' || *a1 == '\0')
    {
      char *res = malloc(2);
      res[0] = '0';
      res[1] = '\0';

      return res;
    }

  size_t len0 = strlen(a0);
  size_t len1 = strlen(a1);
  size_t lenr = len0 + len1;

  char *res = malloc(lenr + 1);
  memset(res, 0, lenr + 1);

  while (len0-- > 0)
    {
      char digit = a0[len0] - '0';
      char rem = 0;

      for (size_t j = len1; j-- > 0; )
        {
          char *dst = &res[len0 + j + 1];
          *dst += digit * (a1[j] - '0') + rem;
          rem = *dst / 10;
          *dst %= 10;
        }

      res[len0] = rem;
    }

  if (res[0] == 0)
    memmove(res, res + 1, --lenr);

  for (size_t i = 0; i < lenr; i++)
    res[i] += '0';

  res[lenr] = '\0';

  return res;
}
