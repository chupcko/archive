#include <stdio.h>
#include <stdlib.h>

#define Max(x,y) ((x)<(y)?(y):(x))
#define Min(x,y) ((x)<(y)?(x):(y))

typedef unsigned char BYTE;

typedef struct
{
  BYTE *colorred;
  BYTE *colorgreen;
  BYTE *colorblue;
  BYTE *pixels;
  int columns; /* width (x)*/
  int rows; /* height (y) */
  int colors;
  char *comments;
} Image;

int InitImage(Image *img,int x,int y,int c)
{
  img->colorred=(BYTE *)calloc(c,sizeof(BYTE));
  img->colorgreen=(BYTE *)calloc(c,sizeof(BYTE));
  img->colorblue=(BYTE *)calloc(c,sizeof(BYTE));
  img->pixels=(BYTE *)calloc(x*y,sizeof(BYTE));
  img->columns=x;
  img->rows=y;
  img->colors=c;
  img->comments=NULL;
  return
    img->colorred==NULL||
    img->colorgreen==NULL||
    img->colorblue==NULL||
    img->pixels==NULL;
}

void DeleteImage(Image *img)
{
  free(img->colorred);
  free(img->colorgreen);
  free(img->colorblue);
  free(img->pixels);
  if(img->comments!=NULL)
    free(img->comments);
}

#define GetPixel(img,x,y) ((img)->pixels[(y)*(img)->columns+(x)])
#define SetPixel(img,x,y,c) GetPixel(img,x,y)=(BYTE)(c)

#define GetRed(img,c) ((img)->colorred[c])
#define GetGreen(img,c) ((img)->colorgreen[c])
#define GetBlue(img,c) ((img)->colorblue[c])

void SetColor(Image *img,int c,int r,int g,int b)
{
  img->colorred[c]=(BYTE)r;
  img->colorgreen[c]=(BYTE)g;
  img->colorblue[c]=(BYTE)b;
}

void SetCPixel(Image *img,int x,int y,int cl)
{
  if(x>=0&&x<img->columns&&y>=0&&y<img->rows)
    SetPixel(img,x,y,cl);
}

void SetHLine(Image *img,int xl,int xr,int y,int cl)
{
  int i;
  for(i=xl;i<=xr;i++)
    SetCPixel(img,i,y,cl);
}

#define sign(x) ((x)<0?-1:((x)?1:0))

void SetLine(Image *img,int x1,int y1,int x2,int y2,int cl)
{
  int dx=abs(x2-x1);
  int dy=abs(y2-y1);
  int s1=sign(x2-x1);
  int s2=sign(y2-y1);
  int ic;
  int e=(dy<<1)-dx;
  int i;
  if(dy>dx)
  {
    int t=dx;
    dx=dy;
    dy=t;
    ic=1;
  }
  else
    ic=0;
  for(i=1;i<=dx;i++)
  {
    SetCPixel(img,x1,y1,cl);
    if(e>0)
    {
      if(ic)
        x1+=s1;
      else
        y1+=s2;
      e-=dx<<1;
    }
    if(ic)
      y1+=s2;
    else
      x1+=s1;
    e+=dy<<1;
  }
  SetCPixel(img,x1,y1,cl);
}

void SetCircle(Image *img,int xo,int yo,int r,int cl)
{
  int p;
  int x=0;
  int y=r;
  int x2=0;
  int y2=r<<1;
  int c=(1-r)<<1;
  while(y>0)
  {
    SetCPixel(img,xo+x,yo+y,cl);
    SetCPixel(img,xo+x,yo-y,cl);
    if(x)
    {
      SetCPixel(img,xo-x,yo+y,cl);
      SetCPixel(img,xo-x,yo-y,cl);
    }
    if(c<0)
      if((c<<1)+y2-1<=0)
        p=1;
      else
        p=3;
    else
      if(c>0)
        if((c<<1)-x2-1<=0)
          p=3;
        else
          p=2;
      else
        p=3;
      if(p%2)
      {
        x++;
        x2+=2;
        c+=1+x2;
      }
    if(p/2)
    {
      y--;
      y2-=2;
      c+=1-y2;
    }
  }
  SetCPixel(img,xo+x,yo,cl);
  SetCPixel(img,xo-x,yo,cl);
}

void SetFCircle(Image *img,int xo,int yo,int r,int cl)
{
  int p;
  int x=0;
  int y=r;
  int xm=x;
  int x2=0;
  int y2=r<<1;
  int c=(1-r)<<1;
  while(y>0)
  {
    if(x>xm)
      xm=x;
    if(c<0)
      if((c<<1)+y2-1<=0)
        p=1;
      else
        p=3;
    else
      if(c>0)
        if((c<<1)-x2-1<=0)
          p=3;
        else
          p=2;
      else
        p=3;
    if(p%2)
    {
      x++;
      x2+=2;
      c+=1+x2;
    }
    if(p/2)
    {
      SetHLine(img,xo-xm,xo+xm,yo-y,cl);
      SetHLine(img,xo-xm,xo+xm,yo+y,cl);
      xm=x;
      y--;
      y2-=2;
      c+=1-y2;
    }
  }
  SetHLine(img,xo-x,xo+x,yo,cl);
}

void SetEllipse(Image *img,int xo,int yo,int a,int b,int cl)
{
  int p;
  int x=0;
  int y=b;
  const long int aa=(long int)a*(long int)a;
  const long int bb=(long int)b*(long int)b;
  const long int aa2=aa<<1;
  const long int bb2=bb<<1;
  long int xbb2=0;
  long int yaa2=(long int)y*aa2;
  long int c=(long int)(1-(b<<1))*aa+bb;
  while(y>0)
  {
    SetCPixel(img,xo+x,yo+y,cl);
    SetCPixel(img,xo+x,yo-y,cl);
    if(x)
    {
      SetCPixel(img,xo-x,yo+y,cl);
      SetCPixel(img,xo-x,yo-y,cl);
    }
    if(c<0)
      if((c<<1)+yaa2-aa<=0)
        p=1;
      else
        p=3;
    else
      if(c>0)
        if((c<<1)-xbb2-bb<=0)
          p=3;
        else
          p=2;
      else
        p=3;
    if(p%2)
    {
      x++;
      xbb2+=bb2;
      c+=bb+xbb2;
    }
    if(p/2)
    {
      y--;
      yaa2-=aa2;
      c+=aa-yaa2;
    }
  }
  SetCPixel(img,xo+x,yo,cl);
  SetCPixel(img,xo-x,yo,cl);
}

void SetFEllipse(Image *img,int xo,int yo,int a,int b,int cl)
{
  int p;
  int x=0;
  int y=b;
  int xm=x;
  const long int aa=(long int)a*(long int)a;
  const long int bb=(long int)b*(long int)b;
  const long int aa2=aa<<1;
  const long int bb2=bb<<1;
  long int xbb2=0;
  long int yaa2=(long int)y*aa2;
  long int c=(long int)(1-(b<<1))*aa+bb;
  while(y>0)
  {
    if(x>xm)
      xm=x;
    if(c<0)
      if((c<<1)+yaa2-aa<=0)
        p=1;
      else
        p=3;
    else
      if(c>0)
        if((c<<1)-xbb2-bb<=0)
          p=3;
        else
          p=2;
      else
        p=3;
    if(p%2)
    {
      x++;
      xbb2+=bb2;
      c+=bb+xbb2;
    }
    if(p/2)
    {
      SetHLine(img,xo-xm,xo+xm,yo-y,cl);
      SetHLine(img,xo-xm,xo+xm,yo+y,cl);
      xm=x;
      y--;
      yaa2-=aa2;
      c+=aa-yaa2;
    }
  }
  SetHLine(img,xo-x,xo+x,yo,cl);
}

int LZWEncodeImage(Image *img,unsigned int data_size,FILE *fp)
{
  #define MaxCode(number_bits) ((1<<(number_bits))-1)
  #define MaxHashTable 5003
  #define MaxLZWBits 12
  #define MaxLZWTable (1<<MaxLZWBits)
  #define LZWOutputCode(code)\
  {\
    /* Emit a code */\
    if(bits>0)\
      datum|=(long)code<<bits;\
    else\
      datum=(long)code;\
    bits+=number_bits;\
    while(bits>=8)\
    {\
      /* Add a character to current packet */\
      packet[byte_count++]=(unsigned char)(datum&0xff);\
      if(byte_count>=254)\
      {\
        fputc(byte_count,fp);\
        fwrite((char *)packet,1,byte_count,fp);\
        byte_count=0;\
      }\
      datum>>=8;\
      bits-=8;\
    }\
    if(free_code>max_code)\
    {\
      number_bits++;\
      if(number_bits==MaxLZWBits)\
        max_code=MaxLZWTable;\
      else\
        max_code=MaxCode(number_bits);\
    }\
  }
  int bits;
  int byte_count;
  int next_pixel;
  int number_bits;
  long datum;
  int displacement;
  int i;
  int j;
  unsigned char *p;
  short clear_code;
  short end_of_information_code;
  short free_code;
  short *hash_code;
  short *hash_prefix;
  short index;
  short max_code;
  short waiting_code;
  unsigned char *packet;
  unsigned char *hash_suffix;
  /* Allocate encoder tables */
  packet=(unsigned char *)calloc(256,sizeof(unsigned char));
  hash_code=(short *)calloc(MaxHashTable,sizeof(short));
  hash_prefix=(short *)calloc(MaxHashTable,sizeof(short));
  hash_suffix=(unsigned char *)calloc(MaxHashTable,sizeof(unsigned char));
  if(
    (packet==(unsigned char *)NULL)||
    (hash_code==(short *)NULL)||
    (hash_prefix==(short *)NULL)||
    (hash_suffix==(unsigned char *)NULL)
  )
    return 0;
  /* Initialize LZW encoder */
  number_bits=data_size;
  max_code=MaxCode(number_bits);
  clear_code=((short)1<<(data_size-1));
  end_of_information_code=clear_code+1;
  free_code=clear_code+2;
  byte_count=0;
  datum=0;
  bits=0;
  for(i=0;i<MaxHashTable;i++)
    hash_code[i]=0;
  LZWOutputCode(clear_code);
  /* Encode pixels */
  p=img->pixels;
  waiting_code=*p;
  for(i=1;i<(img->columns*img->rows);i++)
  {
    /* Probe hash table */
    p++;
    index=*p;
    j=(int)((int)index<<(MaxLZWBits-8))+waiting_code;
    if(j>=MaxHashTable)
      j-=MaxHashTable;
    if(hash_code[j]>0)
    {
      if((hash_prefix[j]==waiting_code)&&(hash_suffix[j]==index))
      {
        waiting_code=hash_code[j];
        continue;
      }
      if(j==0)
        displacement=1;
      else
        displacement=MaxHashTable-j;
      next_pixel=0;
      for(;;)
      {
        j-=displacement;
        if(j<0)
          j+=MaxHashTable;
        if(hash_code[j]==0)
          break;
        if((hash_prefix[j]==waiting_code)&&(hash_suffix[j]==index))
        {
          waiting_code=hash_code[j];
          next_pixel=1;
          break;
        }
      }
      if (next_pixel==1)
        continue;
    }
    LZWOutputCode(waiting_code);
    if(free_code<MaxLZWTable)
    {
      hash_code[j]=free_code++;
      hash_prefix[j]=waiting_code;
      hash_suffix[j]=index;
    }
    else
    {
      /* Fill the hash table with empty entries */
      for(j=0;j<MaxHashTable;j++)
        hash_code[j]=0;
      /* Reset compressor and issue a clear code */
      free_code=clear_code+2;
      LZWOutputCode(clear_code);
      number_bits=data_size;
      max_code=MaxCode(number_bits);
    }
    waiting_code=index;
  }
  /* Flush out the buffered code */
  LZWOutputCode(waiting_code);
  LZWOutputCode(end_of_information_code);
  if(bits>0)
  {
    /* Add a character to current packet */
    packet[byte_count++]=(unsigned char)(datum&0xff);
    if(byte_count>=254)
    {
      fputc(byte_count,fp);
      fwrite((char *)packet,1,byte_count,fp);
      byte_count=0;
    }
  }
  /* Flush accumulated data */
  if(byte_count>0)
  {
    fputc(byte_count,fp);
    fwrite((char *)packet,1,byte_count,fp);
  }
  /* Free encoder memory */
  free((char *)hash_suffix);
  free((char *)hash_prefix);
  free((char *)hash_code);
  free((char *)packet);
  return 1;
}

void LSBFirstWriteShort(unsigned int value,FILE *file)
{
  unsigned char buffer[2];
  buffer[0]=(unsigned char)value;
  buffer[1]=(unsigned char)(value>>8);
  fwrite((char *)buffer,1,2,file);
}

int WriteGIFImage(Image *img)
{
  int i;
  BYTE bits_per_pixel;
  BYTE c;
  int colors;
  FILE *fp=stdout;
  BYTE *p;
  fp=stdout;
  colors=img->colors;
  for(bits_per_pixel=1;bits_per_pixel<8;bits_per_pixel++)
    if((1<<bits_per_pixel)>=colors)
      break;
  /* Write GIF Header */
  fwrite("GIF89a",1,6,fp);
  LSBFirstWriteShort(img->columns,fp);
  LSBFirstWriteShort(img->rows,fp);
  c=0xf0;
  c|=(bits_per_pixel-1);
  fputc((char)c,fp);
  fputc(0,fp);
  fputc(0,fp);
  /* write colormap */
  for(i=0;i<img->colors;i++)
  {
    fputc((char)img->colorred[i],fp);
    fputc((char)img->colorgreen[i],fp);
    fputc((char)img->colorblue[i],fp);
  }
  for(;i<(int)(1<<bits_per_pixel);i++)
  {
    fputc(0,fp);
    fputc(0,fp);
    fputc(0,fp);
  }
  if(img->comments!=(char *)NULL)
  {
    char *p;
    unsigned int count;
    /* write comment extension block */
    fputc(0x21,fp);
    fputc(0xfe,fp);
    p=img->comments;
    while((int)strlen(p)>0)
    {
      count=Min((int)strlen(p),255);
      fputc(count,fp);
      for(i=0;i<count;i++)
        fputc(*p++,fp);
    }
    fputc(0,fp);
  }
  /* write gifimage separator */
  fputc(',',fp);
  LSBFirstWriteShort(0,fp);
  LSBFirstWriteShort(0,fp);
  LSBFirstWriteShort(img->columns,fp);
  LSBFirstWriteShort(img->rows,fp);
  fputc(0,fp);
  c=Max(bits_per_pixel,2);
  fputc((char)c,fp);
  if(!LZWEncodeImage(img,Max(bits_per_pixel,2)+1,fp))
    return 1;
  fputc(0,fp);
  fputc(';',fp);
  return 0;
}
