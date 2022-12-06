#include <math.h>

void
add_rows(double factor, double *dst, double *src)
{
  for (int i = 0; i < 4; i++)
    dst[i] += factor * src[i];
}

void
pivot(double *matrix, int *perms, int row)
{
  double max = 0;
  int col = row;

  for (int i = row; i < 3; i++)
    {
      double val = abs(matrix[row * 4 + i]);
      if (val > max)
        {
          max = val;
          col = i;
        }
    }

  if (col != row)
    {
      for (int i = 0; i < 3; i++)
        {
          double tmp = matrix[i * 4 + col];
          matrix[i * 4 + col] = matrix[i * 4 + row];
          matrix[i * 4 + row] = tmp;
        }

      int tmp = perms[col];
      perms[col] = perms[row];
      perms[row] = tmp;
    }
}

int *
solveEq(int eq[3][4])
{
  static int res[3];
  static int perms[3];
  static double matrix[3][4];

  perms[0] = 0;
  perms[1] = 1;
  perms[2] = 2;

  for (int i = 0; i < 3 * 4; i++)
    ((double *)matrix)[i] = (double)((int *)eq)[i];

  pivot((double *)matrix, perms, 0);
  add_rows(-matrix[1][0] / matrix[0][0], matrix[1], matrix[0]);
  add_rows(-matrix[2][0] / matrix[0][0], matrix[2], matrix[0]);
  pivot((double *)matrix, perms, 1);
  add_rows(-matrix[2][1] / matrix[1][1], matrix[2], matrix[1]);

  double z = matrix[2][3] / matrix[2][2];
  double y = (matrix[1][3] - matrix[1][2] * z) / matrix[1][1];
  double x = (matrix[0][3] - matrix[0][1] * y - matrix[0][2] * z) / matrix[0][0];

  res[perms[0]] = round(x);
  res[perms[1]] = round(y);
  res[perms[2]] = round(z);

  return res;
}
