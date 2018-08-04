#include "main.h"

int main(void)
{
  expression_t e;
  result_t r;

  expression_init(&e);
  r = expression_load(&e, "S K 1 2 3 4 rest");
  if(r != RESULT_OK)
  {
    printf("Error \"%s\"\n", result_text(r));
    return 10;
  }
  expression_print(&e, stdout);
  printf("\n");

  for(;;)
  {
    if(expression_reduction(&e) == RESULT_OK)
      break;
    expression_print(&e, stdout);
    printf("\n");
  }
  expression_dump(&e, stdout);
  printf("\n");

  return 0;
}
