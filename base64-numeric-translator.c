#include <stdint.h>

typedef uint64_t u64;

u64
to_digit(char ch)
{
  if ('A' <= ch && ch <= 'Z')
    return ch - 'A';
  else if ('a' <= ch && ch <= 'z')
    return ch - 'a' + 26;
  else if ('0' <= ch && ch <= '9')
    return ch - '0' + 52;
  else if (ch == '+')
    return 62;
  else if (ch == '/')
    return 63;
}

u64
base64_to_base10(const char *num)
{
  u64 value = 0;
  while (*num != '\0')
    value = 64 * value + to_digit(*num++);

  return value;
}
