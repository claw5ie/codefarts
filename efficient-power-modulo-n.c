#include <string.h>
#include <stdint.h>

typedef uint64_t u64;

static u64 was_seen[10000000];

u64
find_cycle_length(u64 x, u64 base)
{
  memset(was_seen, 0, base * sizeof(*was_seen));
  was_seen[1] = 0;

  u64 power = x;
  for (size_t i = 1; i < base; i++)
    {
      power %= base;
      if (was_seen[power] != 0)
        {
          if (power != 0)
            return i - was_seen[power];
          else
            return i;
        }

      was_seen[power] = i;
      power *= x;
    }

  return base - 1;
}

u64
pow_mod(u64 base, u64 exp, u64 mod)
{
  if (exp == 0)
    return 1;

  u64 res = pow_mod(base, exp / 2, mod);
  res *= res;

  if (exp % 2 != 0)
    res *= base;

  res %= mod;

  return res;
}

u64
modpow(u64 base, u64 exp, u64 modulo)
{
  if (modulo == 1)
    return 0;
  else
    {
      u64 cycle_length = find_cycle_length(base, modulo);

      if (was_seen[0] && exp >= cycle_length)
        return 0;
      else
        return pow_mod(base, exp % cycle_length, modulo);
    }
}
