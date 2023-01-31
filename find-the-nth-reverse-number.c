#include <stddef.h>
#include <assert.h>

typedef unsigned long long ullint;

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(*arr))
#define ARRAY_LAST(arr) (arr)[ARRAY_SIZE(arr) - 1]

static const size_t pows10[]
  = { 1,
      10,
      100,
      1000,
      10000,
      100000,
      1000000,
      10000000,
      100000000,
      1000000000,
      10000000000,
      100000000000,
      1000000000000,
      10000000000000,
      100000000000000,
      1000000000000000,
      10000000000000000,
      100000000000000000,
      1000000000000000000 };

static const size_t rev_num_counts[]
  = { 0,
      10,
      19,
      109,
      199,
      1099,
      1999,
      10999,
      19999,
      109999,
      199999,
      1099999,
      1999999,
      10999999,
      19999999,
      109999999,
      199999999,
      1099999999,
      1999999999,
      10999999999 };

ullint
find_reverse_number(size_t n)
{
  if (n <= rev_num_counts[1])
    return n - 1;

  assert(n <= ARRAY_LAST(rev_num_counts) && "result cannot fit in 64 bit number");

  size_t digit_count = 0;

  for (size_t i = 0; i + 1 < ARRAY_SIZE(rev_num_counts); i++)
    {
      if (rev_num_counts[i] < n && n <= rev_num_counts[i + 1])
        {
          digit_count = i + 1;
          break;
        }
    }

  n -= rev_num_counts[digit_count - 1] + 1;

  static char digits[20];
  size_t digits_to_guess = (digit_count + 1) / 2;

  for (size_t i = digits_to_guess; i-- > 0; )
    {
      for (size_t j = 0; j < 10; j++)
        {
          if (j * pows10[i] <= n && n < (j + 1) * pows10[i])
            {
              n -= j * pows10[i];
              digits[digits_to_guess - 1 - i] = j;
              break;
            }
        }
    }

  ++digits[0];

  for (size_t i = digit_count; i-- > digits_to_guess; )
    digits[i] = digits[digit_count - 1 - i];

  ullint res = 0;
  for (size_t i = 0; i < digit_count; i++)
    res = 10 * res + digits[i];

  return res;
}
