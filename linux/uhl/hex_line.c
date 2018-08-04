#include <ctype.h>

#include "uhl.h"

int chop_line(char *line)
{
  int length;

  length = 0;
  if(line[length] == HEX_COLUMN)
  {
    length++;
    while(isxdigit(line[length]) != 0)
      length++;
  }
  line[length] = '\0';
  return length;
}

static byte hexadecimal_digit(char c)
{
  if(isdigit(c) != 0)
    return (byte)(c-'0');
  else
    return (byte)(tolower(c)-'a')+10;
}

integer found_in_hex_line(char *line, int size, int offset)
{
  integer result;
  int i;

  if(size > sizeof(integer))
    size = sizeof(integer);
  size *= 2;
  result = 0;
  i = 0;
  while
  (
    i < size &&
    isxdigit(line[offset+i]) != '\0'
  )
  {
    result <<= 4;
    result |= hexadecimal_digit(line[offset+i]);
    i++;
  }
  return result;
}
