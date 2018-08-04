#include <stdio.h>

typedef long double my_float_t;

#define MY_INF (1.0L/0.0L)
#define MY_NAN (-(MY_INF-MY_INF))

int my_isnan(my_float_t x)
{
  if(x != x)
    return -1;
  return 0;
}

int my_isinf(my_float_t x)
{
  if(my_isnan(x) != 0)
    return 0;
  if(my_isnan(x-x) != 0)
    if(x < 0.0L)
      return -1;
    else
      return 1;
  return 0;
}

int my_iszero(my_float_t x)
{
  if(x == 0.0L)
    if(1.0L/x == MY_INF)
      return 1;
    else
      return -1;
  return 0;
}

void debug(long double x)
{
  printf
  (
    "%+4.2Lf\tmy_isnan:% d\tmy_isinf:% d\tmy_iszero:% d\n",
    x,
    my_isnan(x),
    my_isinf(x),
    my_iszero(x)
  );
}

int main(void)
{
  debug(-MY_NAN);
  debug(-MY_INF);
  debug(-1.0L);
  debug(-0.0L);
  debug(0.0L);
  debug(1.0L);
  debug(MY_INF);
  debug(MY_NAN);

  return 0;
}
