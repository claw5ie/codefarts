def divisors(integer):
  res = []

  for i in range(2, integer - 1):
    if integer % i == 0:
      res.append(i)

  if (len(res) != 0):
    return res
  else:
    return str(integer) + " is prime";
