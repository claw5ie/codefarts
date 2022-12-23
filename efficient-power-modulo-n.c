#include <string.h>
#include <stdint.h>

typedef uint64_t u64;

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
    return pow_mod(base, exp, modulo);
}
