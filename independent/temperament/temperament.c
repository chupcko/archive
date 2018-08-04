#include <stdio.h>
#include <math.h>

#define SIZE 13

void print_header()
{
  printf
  (
    "72 25.4 div dup scale\n"
    "10 100 translate\n"
    "180 180 scale\n"
    "0.001 setlinewidth\n"
    "\n"
    "/point\n"
    "{\n"
    "  2 dict\n"
    "  begin\n"
    "    /y exch def\n"
    "    /x exch def\n"
    "    x y 0.004 0 361 arc\n"
    "    fill\n"
    "  end\n"
    "}\n"
    "def\n"
    "\n"
    "/line\n"
    "{\n"
    "  2 dict\n"
    "  begin\n"
    "    /y2 exch def\n"
    "    /x2 exch def\n"
    "    /y1 exch def\n"
    "    /x1 exch def\n"
    "    newpath\n"
    "      x1 y1 moveto\n"
    "      x2 y2 lineto\n"
    "    closepath\n"
    "    stroke\n"
    "  end\n"
    "}\n"
    "def\n"
  );
}

void print_footer()
{
  printf("showpage quit\n");
}

void print_equal(void)
{
  double equal[SIZE] =
  {
    pow(2.0, 0.0/12.0),
    pow(2.0, 1.0/12.0),
    pow(2.0, 2.0/12.0),
    pow(2.0, 3.0/12.0),
    pow(2.0, 4.0/12.0),
    pow(2.0, 5.0/12.0),
    pow(2.0, 6.0/12.0),
    pow(2.0, 7.0/12.0),
    pow(2.0, 8.0/12.0),
    pow(2.0, 9.0/12.0),
    pow(2.0, 10.0/12.0),
    pow(2.0, 11.0/12.0),
    pow(2.0, 12.0/12.0)
  };
  int i;

  for(i = 0; i < SIZE; i++)
    printf
    (
      "%f 0.0 %f 0.5 line\n"
      "%f 0.1 point\n",
      equal[i]-1.0,
      equal[i]-1.0,
      equal[i]-1.0
    );
}

void print_werckmeister_3(void)
{
  double werckmeister_3[SIZE] =
  {
    1.0/1.0,
    pow(2.0, 1.0/4.0)*8.0/9.0,
    9.0/8.0,
    pow(2.0, 1.0/4.0),
    pow(2.0, 1.0/2.0)*8.0/9.0,
    pow(2.0, 1.0/4.0)*9.0/8.0,
    pow(2.0, 1.0/2.0),
    3.0/2.0,
    128.0/81.0,
    pow(8.0, 1.0/4.0),
    3.0/pow(8.0, 1.0/4.0),
    pow(2.0, 1.0/2.0)*4.0/3.0,
    2.0/1.0
  };
  int i;

  for(i = 0; i < SIZE; i++)
    printf("%f 0.2 point\n", werckmeister_3[i]-1.0);
}

void print_pythagorean(void)
{
  double pythagorean[SIZE] =
  {
    pow(2.0, 0.0)/pow(3.0, 0.0),
    pow(2.0, 8.0)/pow(3.0, 5.0),
    pow(3.0, 2.0)/pow(2.0, 3.0),
    pow(2.0, 5.0)/pow(3.0, 3.0),
    pow(3.0, 4.0)/pow(2.0, 6.0),
    pow(2.0, 2.0)/pow(3.0, 1.0),
    pow(3.0, 6.0)/pow(2.0, 9.0),
    pow(3.0, 1.0)/pow(2.0, 1.0),
    pow(2.0, 7.0)/pow(3.0, 4.0),
    pow(3.0, 3.0)/pow(2.0, 4.0),
    pow(2.0, 4.0)/pow(3.0, 2.0),
    pow(3.0, 5.0)/pow(2.0, 7.0),
    pow(2.0, 1.0)/pow(3.0, 0.0)
  };
  int i;

  for(i = 0; i < SIZE; i++)
    printf("%f 0.3 point\n", pythagorean[i]-1.0);
}

void print_just_intonation_interval(void)
{
  double just_intonation_interval[SIZE] =
  {
    1.0/1.0,
    16.0/15.0,
    9.0/8.0,
    6.0/5.0,
    5.0/4.0,
    4.0/3.0,
    7.0/5.0,
    3.0/2.0,
    8.0/5.0,
    5.0/3.0,
    7.0/4.0,
    15.0/8.0,
    2.0/1.0
  };
  int i;

  for(i = 0; i < SIZE; i++)
    printf("%f 0.4 point\n", just_intonation_interval[i]-1.0);
}

int main(void)
{
  print_header();
  print_equal();
  print_werckmeister_3();
  print_pythagorean();
  print_just_intonation_interval();
  print_footer();
  return 0;
}
