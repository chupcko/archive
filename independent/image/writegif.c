#include "image.h"

int main(void)
{
  Image img;
  int i;
  int j;
  if(InitImage(&img,256,256,256))
    return 1;
  for(i=0;i<256;i++)
    SetColor(&img,i,(BYTE)i,(BYTE)i,(BYTE)i);
  for(i=0;i<256;i++)
    for(j=0;j<256;j++)
      SetPixel(&img,i,j,i);
  SetLine(&img,10,15,36,78,140);
  SetFCircle(&img,10,10,45,120);
  WriteGIFImage(&img);
  DeleteImage(&img);
  return 0;
}
