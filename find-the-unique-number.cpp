float
find_uniq(const std::vector<float> &v)
{
  float repeated = v[0];

  if (repeated != v[1])
    repeated = v[2];

  for (float val: v)
    if (val != repeated)
      return val;

  return 0;
}
