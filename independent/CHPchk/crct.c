#include <stdio.h>

#define BIT(x) ((unsigned long)1<<(x))
#define SBIT BIT(31)
#define GEN (BIT(26)|BIT(23)|BIT(22)|BIT(16)|BIT(12)|BIT(11)|BIT(10)|BIT(8)|BIT(7)|BIT(5)|BIT(4)|BIT(2)|BIT(1)|BIT(0));

unsigned long r[8];

unsigned long remainder(int m)
{
  unsigned long rem=0;
  int i;
  for(i=0;i<8;i++)
    if(BIT(i)&m)
      rem=rem^r[i];
  return rem;
}

int main (void)
{
  int i;
  r[0]=GEN;
  for(i=1;i<8;i++)
    r[i]=(r[i-1]&SBIT)?(r[i-1]<<1)^r[0]:r[i-1]<<1;
  puts
  (
    "#ifndef CRCT_H\n"
    "#define CRCT_H\n"
    "\n"
    "unsigned long CRCTable[256]=\n"
    "{"
  );
  for(i=0;i<32;i++)
  {
    if(i)
      puts(",");
    printf
    (
      "  0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X",
      remainder(i*8+0),
      remainder(i*8+1),
      remainder(i*8+2),
      remainder(i*8+3),
      remainder(i*8+4),
      remainder(i*8+5),
      remainder(i*8+6),
      remainder(i*8+7)
     );
  }
  puts
  (
    "\n"
    "};\n"
    "#endif"
  );
  return 0;
}
