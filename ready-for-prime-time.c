#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <limits.h>

typedef unsigned uint;
typedef unsigned char uchar;

void
prime(uint limit, size_t *count_loc, uint *primes)
{
  size_t char_count = limit / CHAR_BIT + 1;
  uchar *is_prime = malloc(char_count);
  memset(is_prime, UCHAR_MAX, char_count);

  size_t count = 0;
  for (size_t i = 2; i <= limit; i++)
    {
      if (is_prime[i / CHAR_BIT] & (1 << (i % CHAR_BIT)))
        {
          primes[count++] = i;
          for (size_t j = 2 * i; j <= limit; j += i)
            is_prime[j / CHAR_BIT] &= ~(1 << (j % CHAR_BIT));
        }
    }

  *count_loc = count;
  free(is_prime);
}
