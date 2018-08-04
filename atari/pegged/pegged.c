/* This is accessory */
/* Project PEGGED.PRJ, No stack checking */

#include <aes.h>
#include <tos.h>
#include <vdi.h>

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define as(p,q) ((p)>(q)?(p)-(q):(q)-(p))
#define gs(p,q) ((p)+((q)-(p))/2)

#define T 29
enum
{
  OB0=18,OB1,OB2,OB3,OB4,OB5,OB6,OB7,OB8,OB9,
  CANCEL=28
};
int rsc_image[11][64]=
{
  0x0001,0x8000,0x0001,0x8000,0x1ff1,0x8ff8,0x3839,0x9c1c,
  0x3039,0x9c0c,0x0039,0x9c00,0x0039,0x9c00,0x0039,0x9c00,
  0x0039,0x9c00,0x0039,0x9c00,0x3039,0x9c0c,0x3839,0x9c1c,
  0x1ff1,0x8ff8,0x0001,0x8000,0x0001,0x8000,0xffff,0xffff,
  0xffff,0xffff,0x0001,0x8000,0x0001,0x8000,0x1ff1,0x8ff8,
  0x3839,0x9c1c,0x3801,0x9c0c,0x3801,0x9c00,0x3801,0x9c00,
  0x1ff1,0x9c00,0x0039,0x9c00,0x0039,0x9c00,0x0039,0x9c0c,
  0x3839,0x9c1c,0x1ff1,0x8ff8,0x0001,0x8000,0x0001,0x8000,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
  0x003f,0xfc00,0x0020,0x0400,0x0020,0x0400,0x0020,0x0400,
  0x0020,0x0400,0x0021,0x8400,0x0fe1,0x87f0,0x0800,0x0010,
  0x080d,0xb010,0x080d,0xb010,0x0800,0x0010,0x0801,0x8010,
  0x0801,0x8010,0x0800,0x0010,0x0801,0x8010,0x0801,0x8010,
  0x0800,0x0010,0x0fe0,0x07f0,0x0020,0x0400,0x0020,0x0400,
  0x0020,0x0400,0x0020,0x0400,0x0020,0x0400,0x003f,0xfc00,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
  0x003f,0xfc00,0x0020,0x0400,0x0020,0x0400,0x0020,0x0400,
  0x0020,0x0400,0x0021,0x8400,0x0fe1,0x87f0,0x0800,0x0010,
  0x0801,0x8010,0x0801,0x8010,0x0800,0x0010,0x086d,0xb610,
  0x086d,0xb610,0x0800,0x0010,0x0801,0x8010,0x0801,0x8010,
  0x0800,0x0010,0x0fe1,0x87f0,0x0021,0x8400,0x0020,0x0400,
  0x0020,0x0400,0x0020,0x0400,0x0020,0x0400,0x003f,0xfc00,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
  0x003f,0xfc00,0x0020,0x0400,0x002d,0xb400,0x002d,0xb400,
  0x0020,0x0400,0x002d,0xb400,0x0fed,0xb7f0,0x0800,0x0010,
  0x080d,0xb010,0x080d,0xb010,0x0800,0x0010,0x080c,0x3010,
  0x080c,0x3010,0x0800,0x0010,0x0800,0x0010,0x0800,0x0010,
  0x0800,0x0010,0x0fe0,0x07f0,0x0020,0x0400,0x0020,0x0400,
  0x0020,0x0400,0x0020,0x0400,0x0020,0x0400,0x003f,0xfc00,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
  0x003f,0xfc00,0x0020,0x0400,0x0020,0x0400,0x0020,0x0400,
  0x0020,0x0400,0x0021,0x8400,0x0fe1,0x87f0,0x0800,0x0010,
  0x080d,0xb010,0x080d,0xb010,0x0800,0x0010,0x086c,0x3610,
  0x086c,0x3610,0x0800,0x0010,0x080d,0xb010,0x080d,0xb010,
  0x0800,0x0010,0x0fe1,0x87f0,0x0021,0x8400,0x0020,0x0400,
  0x0020,0x0400,0x0020,0x0400,0x0020,0x0400,0x003f,0xfc00,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
  0x003f,0xfc00,0x0020,0x0400,0x0020,0x0400,0x0020,0x0400,
  0x0020,0x0400,0x0021,0x8400,0x0fe1,0x87f0,0x0800,0x0010,
  0x080d,0xb010,0x080d,0xb010,0x0800,0x0010,0x086d,0xb610,
  0x086d,0xb610,0x0800,0x0010,0x0b6d,0xb6d0,0x0b6d,0xb6d0,
  0x0800,0x0010,0x0fe0,0x07f0,0x0020,0x0400,0x0020,0x0400,
  0x0020,0x0400,0x0020,0x0400,0x0020,0x0400,0x003f,0xfc00,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
  0x003f,0xfc00,0x0020,0x0400,0x0021,0x8400,0x0021,0x8400,
  0x0020,0x0400,0x002d,0xb400,0x0fed,0xb7f0,0x0800,0x0010,
  0x086d,0xb610,0x086d,0xb610,0x0800,0x0010,0x0801,0x8010,
  0x0801,0x8010,0x0800,0x0010,0x0801,0x8010,0x0801,0x8010,
  0x0800,0x0010,0x0fed,0xb7f0,0x002d,0xb400,0x0020,0x0400,
  0x002d,0xb400,0x002d,0xb400,0x0020,0x0400,0x003f,0xfc00,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
  0x001f,0xfe00,0x0010,0x0200,0x0010,0xc200,0x0010,0xc200,
  0x0010,0x0200,0x0016,0xda00,0x07f6,0xdbf8,0x0400,0x0008,
  0x0436,0x1b08,0x0436,0x1b08,0x0400,0x0008,0x05b0,0x0368,
  0x05b0,0x0368,0x0400,0x0008,0x0436,0x1b08,0x0436,0x1b08,
  0x0400,0x0008,0x07f6,0xdbf8,0x0016,0xda00,0x0010,0x0200,
  0x0010,0xc200,0x0010,0xc200,0x0010,0x0200,0x001f,0xfe00,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
  0x003f,0xfc00,0x0020,0x0400,0x0021,0x8400,0x0021,0x8400,
  0x0020,0x0400,0x002d,0xb400,0x0fed,0xb7f0,0x0800,0x0010,
  0x086d,0xb610,0x086d,0xb610,0x0800,0x0010,0x0b6c,0x36d0,
  0x0b6c,0x36d0,0x0800,0x0010,0x086d,0xb610,0x086d,0xb610,
  0x0800,0x0010,0x0fed,0xb7f0,0x002d,0xb400,0x0020,0x0400,
  0x0021,0x8400,0x0021,0x8400,0x0020,0x0400,0x003f,0xfc00,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
  0x003f,0xfc00,0x0020,0x0400,0x002d,0xb400,0x002d,0xb400,
  0x0020,0x0400,0x002d,0xb400,0x0fed,0xb7f0,0x0800,0x0010,
  0x0b61,0x86d0,0x0b61,0x86d0,0x0800,0x0010,0x0b6d,0xb6d0,
  0x0b6d,0xb6d0,0x0800,0x0010,0x0b61,0x86d0,0x0b61,0x86d0,
  0x0800,0x0010,0x0fed,0xb7f0,0x002d,0xb400,0x0020,0x0400,
  0x002d,0xb400,0x002d,0xb400,0x0020,0x0400,0x003f,0xfc00,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
  0x003f,0xfc00,0x0020,0x0400,0x002d,0xb400,0x002d,0xb400,
  0x0020,0x0400,0x002d,0xb400,0x0fed,0xb7f0,0x0800,0x0010,
  0x0b6d,0xb6d0,0x0b6d,0xb6d0,0x0800,0x0010,0x0b6c,0x36d0,
  0x0b6c,0x36d0,0x0800,0x0010,0x0b6d,0xb6d0,0x0b6d,0xb6d0,
  0x0800,0x0010,0x0fed,0xb7f0,0x002d,0xb400,0x0020,0x0400,
  0x002d,0xb400,0x002d,0xb400,0x0020,0x0400,0x003f,0xfc00,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
};
BITBLK rsc_bitblk[11]=
{
  rsc_image[0],4,32,0,0,BLACK,
  rsc_image[1],4,32,0,0,BLACK,
  rsc_image[2],4,32,0,0,BLACK,
  rsc_image[3],4,32,0,0,BLACK,
  rsc_image[4],4,32,0,0,BLACK,
  rsc_image[5],4,32,0,0,BLACK,
  rsc_image[6],4,32,0,0,BLACK,
  rsc_image[7],4,32,0,0,BLACK,
  rsc_image[8],4,32,0,0,BLACK,
  rsc_image[9],4,32,0,0,BLACK,
  rsc_image[10],4,32,0,0,BLACK
};
OBJECT rsc_drvo[T]=
{
  -1,1,28,G_BOX,NONE,OUTLINED,0x00021100l,0,0,36,23,
  2,-1,-1,G_STRING,NONE,NORMAL,(long)"Pegged  V .",4,2,13,1,
  3,-1,-1,G_IMAGE,NONE,NORMAL,(long)&rsc_bitblk[0],28,2,4,2,
  4,-1,-1,G_STRING,NONE,NORMAL,(long)"Author : Lazic Goran Chupcko",4,5,36,1,
  5,-1,-1,G_STRING,NONE,NORMAL,(long)"... Serbia",4,6,36,1,
  6,-1,-1,G_STRING,NONE,NORMAL,(long)"Back move - <Backspace>",4,8,36,1,
  7,-1,-1,G_STRING,NONE,NORMAL,(long)"Select    - <Help>",4,9,36,1,
  8,-1,-1,G_STRING,NONE,NORMAL,(long)"New game  - <Undo>",4,10,36,1,
  9,-1,-1,G_BOX,NONE,NORMAL,0x00fe1100l,4,13,4,2,
  10,-1,-1,G_BOX,NONE,NORMAL,0x00fe1100l,10,13,4,2,
  11,-1,-1,G_BOX,NONE,NORMAL,0x00fe1100l,16,13,4,2,
  12,-1,-1,G_BOX,NONE,NORMAL,0x00fe1100l,22,13,4,2,
  13,-1,-1,G_BOX,NONE,NORMAL,0x00fe1100l,28,13,4,2,
  14,-1,-1,G_BOX,NONE,NORMAL,0x00fe1100l,4,16,4,2,
  15,-1,-1,G_BOX,NONE,NORMAL,0x00fe1100l,10,16,4,2,
  16,-1,-1,G_BOX,NONE,NORMAL,0x00fe1100l,16,16,4,2,
  17,-1,-1,G_BOX,NONE,NORMAL,0x00fe1100l,22,16,4,2,
  18,-1,-1,G_BOX,NONE,NORMAL,0x00fe1100l,28,16,4,2,
  19,-1,-1,G_IMAGE,SELECTABLE|EXIT,NORMAL,(long)&rsc_bitblk[1],4,13,4,2,
  20,-1,-1,G_IMAGE,SELECTABLE|EXIT,NORMAL,(long)&rsc_bitblk[2],10,13,4,2,
  21,-1,-1,G_IMAGE,SELECTABLE|EXIT,NORMAL,(long)&rsc_bitblk[3],16,13,4,2,
  22,-1,-1,G_IMAGE,SELECTABLE|EXIT,NORMAL,(long)&rsc_bitblk[4],22,13,4,2,
  23,-1,-1,G_IMAGE,SELECTABLE|EXIT,NORMAL,(long)&rsc_bitblk[5],28,13,4,2,
  24,-1,-1,G_IMAGE,SELECTABLE|EXIT,NORMAL,(long)&rsc_bitblk[6],4,16,4,2,
  25,-1,-1,G_IMAGE,SELECTABLE|EXIT,NORMAL,(long)&rsc_bitblk[7],10,16,4,2,
  26,-1,-1,G_IMAGE,SELECTABLE|EXIT,NORMAL,(long)&rsc_bitblk[8],16,16,4,2,
  27,-1,-1,G_IMAGE,SELECTABLE|EXIT,NORMAL,(long)&rsc_bitblk[9],22,16,4,2,
  28,-1,-1,G_IMAGE,SELECTABLE|EXIT,NORMAL,(long)&rsc_bitblk[10],28,16,4,2,
  0,-1,-1,G_BUTTON,SELECTABLE|DEFAULT|EXIT|LASTOB,NORMAL,(long)"CANCEL",12,20,12,1
};
struct
{
  int _sx;
  int _sy;
  int _dx;
  int _dy;
} Bm[31];
char Por_0[18]=" Congratulation !";
char Por_1[17]=" No more moves !";
char Por_2[17]=" Play the game !";
int PAT[2][16]=
{
  0x0000,0x0000,0x0000,0x0000,0x03c0,0x0420,0x0810,0x0810,
  0x0850,0x0890,0x0420,0x03c0,0x0000,0x0000,0x0000,0x0000,
  0x0000,0x0000,0x0000,0x03c0,0x0ff0,0x0ff0,0x1cf8,0x1cf8,
  0x1ff8,0x1ff8,0x0ff0,0x0ff0,0x03c0,0x0000,0x0000,0x0000,
},Handle,WHandle,Wx,Wy,Ww,Wh,X0=496,Y0=256,Mat[7][7],Nkugl,Kraj,Bmb,Opn,Sel;

void simbol(int x,int y)
{
  int p[4];
  p[0]=X0+x*16;
  p[1]=Y0+y*16;
  p[2]=p[0]+15;
  p[3]=p[1]+15;
  vsf_udpat(Handle,PAT[Mat[x][y]-1],1);
  vr_recfl(Handle,p);
}

void obnovi(void)
{
  struct
  {
    int ux;
    int zx;
    int uy;
    int zy;
  } okvir[12]=
  {
    2,-1,2,-1,2,-1,0,-1,5,1,0,-1,5,1,2,-1,
    7,1,2,-1,7,1,5,1,5,1,5,1,5,1,7,1,
    2,-1,7,1,2,-1,5,1,0,-1,5,1,0,-1,2,-1
  };
  int p[24];
  int x;
  int y;
  p[0]=X0-21;
  p[1]=Y0-21;
  p[2]=X0+132;
  p[3]=Y0+132;
  vsf_interior(Handle,FIS_HOLLOW);
  graf_mouse(M_OFF,(MFORM *)0);
  vr_recfl(Handle,p);
  p[0]+=2;
  p[1]+=2;
  p[2]-=2;
  p[3]-=2;
  v_bar(Handle,p);
  p[0]+=1;
  p[1]+=1;
  p[2]-=1;
  p[3]-=1;
  v_bar(Handle,p);
  for(x=0;x<12;x++)
  {
    p[x*2]=X0+okvir[x].ux*16+(okvir[x].zx<0?-9:8);
    p[x*2+1]=Y0+okvir[x].uy*16+(okvir[x].zy<0?-9:8);
  }
  v_fillarea(Handle,12,p);
  for(x=0;x<12;x++)
  {
    p[x*2]-=okvir[x].zx;
    p[x*2+1]-=okvir[x].zy;
  }
  v_fillarea(Handle,12,p);
  for(x=0;x<12;x++)
  {
    p[x*2]-=okvir[x].zx*3;
    p[x*2+1]-=okvir[x].zy*3;
  }
  vsf_interior(Handle,FIS_USER);
  vsf_udpat(Handle,PAT[0],1);
  v_fillarea(Handle,12,p);
  for(x=0;x<7;x++)
    for(y=0;y<7;y++)
      if(Mat[x][y]==2)
        simbol(x,y);
  graf_mouse(M_ON,(MFORM *)0);
}

void novaigra(int l)
{
  int uzorci[10][7][7]=
  {
    0,0,1,1,1,0,0,
    0,0,1,1,1,0,0,
    1,1,2,1,1,1,1,
    1,2,2,2,2,1,1,
    1,1,2,1,1,1,1,
    0,0,1,1,1,0,0,
    0,0,1,1,1,0,0,
    0,0,1,1,1,0,0,
    0,0,1,2,1,0,0,
    1,1,1,2,1,1,1,
    1,2,2,2,2,2,1,
    1,1,1,2,1,1,1,
    0,0,1,2,1,0,0,
    0,0,1,1,1,0,0,
    0,0,1,1,1,0,0,
    0,0,1,1,1,0,0,
    2,2,2,2,1,1,1,
    2,2,2,1,1,1,1,
    2,2,2,2,1,1,1,
    0,0,1,1,1,0,0,
    0,0,1,1,1,0,0,
    0,0,1,1,1,0,0,
    0,0,1,2,1,0,0,
    1,1,2,2,2,1,1,
    1,2,2,1,2,2,1,
    1,1,2,2,2,1,1,
    0,0,1,2,1,0,0,
    0,0,1,1,1,0,0,
    0,0,1,1,2,0,0,
    0,0,1,2,2,0,0,
    1,1,2,2,2,1,1,
    1,2,2,2,2,1,1,
    1,1,2,2,2,1,1,
    0,0,1,2,2,0,0,
    0,0,1,1,2,0,0,
    0,0,1,1,1,0,0,
    0,0,2,1,1,0,0,
    1,2,2,1,1,2,2,
    2,2,2,2,2,2,2,
    1,2,2,1,1,2,2,
    0,0,2,1,1,0,0,
    0,0,1,1,1,0,0,
    0,0,1,2,1,0,0,
    0,0,2,2,2,0,0,
    1,2,2,1,2,2,1,
    2,2,1,1,1,2,2,
    1,2,2,1,2,2,1,
    0,0,2,2,2,0,0,
    0,0,1,2,1,0,0,
    0,0,1,2,1,0,0,
    0,0,2,2,2,0,0,
    1,2,2,2,2,2,1,
    2,2,2,1,2,2,2,
    1,2,2,2,2,2,1,
    0,0,2,2,2,0,0,
    0,0,1,2,1,0,0,
    0,0,2,2,2,0,0,
    0,0,2,2,2,0,0,
    2,2,1,2,1,2,2,
    2,2,2,2,2,2,2,
    2,2,1,2,1,2,2,
    0,0,2,2,2,0,0,
    0,0,2,2,2,0,0,
    0,0,2,2,2,0,0,
    0,0,2,2,2,0,0,
    2,2,2,2,2,2,2,
    2,2,2,1,2,2,2,
    2,2,2,2,2,2,2,
    0,0,2,2,2,0,0,
    0,0,2,2,2,0,0
  };
  int x;
  int y;
  Bmb=0;
  Nkugl=0;
  for(x=0;x<7;x++)
    for(y=0;y<7;y++)
    {
      Mat[x][y]=uzorci[l][x][y];
      if(Mat[x][y]==2)
        Nkugl++;
    }
  if(Opn&&Kraj)
  {
    wind_set(WHandle,WF_INFO,Por_2);
    Kraj=0;
  }
}

void select(void)
{
  int fx;
  int fy;
  int fw;
  int fh;
  int iz;
  form_center(rsc_drvo,&fx,&fy,&fw,&fh);
  wind_update(BEG_UPDATE);
  wind_update(BEG_MCTRL);
  form_dial(FMD_START,fx,fy,fw,fh,fx,fy,fw,fh);
  objc_draw(rsc_drvo,0,1,fx,fy,fw,fh);
  iz=form_do(rsc_drvo,0);
  rsc_drvo[iz].ob_state=NORMAL;
  if(iz!=CANCEL)
  {
    novaigra(Sel=iz-OB0);
    form_dial(FMD_START,Wx,Wy,Ww,Wh,Wx,Wy,Ww,Wh);
    form_dial(FMD_FINISH,Wx,Wy,Ww,Wh,Wx,Wy,Ww,Wh);
  }
  form_dial(FMD_FINISH,fx,fy,fw,fh,fx,fy,fw,fh);
  wind_update(END_MCTRL);
  wind_update(END_UPDATE);
}

void main(void)
{
  static int work_in[11]=
  {
    0,SOLID,1,0,0,0,0,FIS_USER,0,1,2
  };
  static int work_out[57];
  static int msg[8];
  int gapp;
  int trash;
  int fx;
  int fy;
  int fw;
  int fh;
  int sx;
  int sy;
  int dx;
  int dy;
  int px;
  int py;
  int key;
  static MFORM Mf=
  {
    7,7,1,0,1,
    0x0000,0x0000,0x07e0,0x1ff8,0x1ff8,0x3ffc,0x3ffc,0x3ffc,
    0x3ffc,0x3ffc,0x3ffc,0x1ff8,0x1ff8,0x07e0,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x03c0,0x0ff0,0x0ff0,0x1cf8,0x1cf8,
    0x1ff8,0x1ff8,0x0ff0,0x0ff0,0x03c0,0x0000,0x0000,0x0000
  };
  gapp=appl_init();
  Handle=graf_handle(&trash,&trash,&trash,&trash);
  v_opnvwk(work_in,&Handle,work_out);
  vswr_mode(Handle,MD_REPLACE);
  vsf_perimeter(Handle,1);
  if(Getrez()!=2)
    form_alert(1,"[3][|  Only high resolution ! ][  OK  ]");
  else
  {
    menu_register(gapp,"  Pegged");
    for(trash=0;trash<T;trash++)
      rsrc_obfix(rsc_drvo,trash);
    Opn=0;
    novaigra(Sel=0);
    while(1)
      switch(evnt_multi(MU_MESAG|MU_BUTTON|MU_KEYBD,1,1,1,0,0,0,0,0,0,0,0,0,0,msg,0,0,&sx,&sy,&trash,&trash,&key,&trash))
      {
        case MU_KEYBD:
        case MU_KEYBD|MU_BUTTON:
          switch(key)
          {
            case 0x0e08:
              if(Bmb>0)
              {
                Nkugl++;
                Bmb--;
                Mat[Bm[Bmb]._sx][Bm[Bmb]._sy]=2;
                Mat[Bm[Bmb]._dx][Bm[Bmb]._dy]=1;
                Mat[px=gs(Bm[Bmb]._sx,Bm[Bmb]._dx)][py=gs(Bm[Bmb]._sy,Bm[Bmb]._dy)]=2;
                graf_mouse(M_OFF,(MFORM *)0);
                simbol(Bm[Bmb]._sx,Bm[Bmb]._sy);
                simbol(px,py);
                simbol(Bm[Bmb]._dx,Bm[Bmb]._dy);
                graf_mouse(M_ON,(MFORM *)0);
                if(Kraj)
                {
                  wind_set(WHandle,WF_INFO,Por_2);
                  Kraj=0;
                }
              }
              else
                Cconout((int)'\a');
              break;
            case 0x6200:
              select();
              break;
            case 0x6100:
              novaigra(Sel);
              obnovi();
          }
          break;
        case MU_BUTTON:
          if(sx>=Wx&&sy>=Wy&&sx<=(Wx+Ww)&&sy<=(Wy+Wh))
          {
            sx-=X0;
            sy-=Y0;
            sx/=sx<0?1:16;
            sy/=sy<0?1:16;
            if(sx>=0&&sx<7&&sy>=0&&sy<7&&Mat[sx][sy]==2)
            {
              Mat[sx][sy]=1;
              graf_mouse(M_OFF,(MFORM *)0);
              simbol(sx,sy);
              graf_mouse(M_ON,(MFORM *)0);
              graf_mouse(USER_DEF,&Mf);
              evnt_button(1,1,0,&dx,&dy,&trash,&trash);
              dx-=X0;
              dy-=Y0;
              dx/=dx<0?1:16;
              dy/=dy<0?1:16;
              if(dx>=0&&dx<7&&dy>=0&&dy<7&&Mat[dx][dy]==1&&((as(sx,dx)==2&&sy==dy)||(sx==dx&&as(sy,dy)==2))&&Mat[px=gs(sx,dx)][py=gs(sy,dy)]==2)
              {
                Nkugl--;
                Mat[dx][dy]=2;
                Mat[px][py]=1;
                Bm[Bmb]._sx=sx;
                Bm[Bmb]._sy=sy;
                Bm[Bmb]._dx=dx;
                Bm[Bmb]._dy=dy;
                Bmb++;
                graf_mouse(M_OFF,(MFORM *)0);
                simbol(dx,dy);
                simbol(px,py);
                graf_mouse(M_ON,(MFORM *)0);
                graf_mouse(ARROW,(MFORM *)0);
                Kraj=1;
                for(fx=0;Kraj&&fx<5;fx++)
                  for(fy=0;Kraj&&fy<7;fy++)
                    if((Mat[fx][fy]==2&&Mat[fx+1][fy]==2&&Mat[fx+2][fy]==1)||(Mat[fx][fy]==1&&Mat[fx+1][fy]==2&&Mat[fx+2][fy]==2)||(Mat[fy][fx]==2&&Mat[fy][fx+1]==2&&Mat[fy][fx+2]==1)||(Mat[fy][fx]==1&&Mat[fy][fx+1]==2&&Mat[fy][fx+2]==2))
                      Kraj=0;
                if(Kraj)
                  wind_set(WHandle,WF_INFO,Nkugl==1?Por_0:Por_1);
              }
              else
              {
                Cconout((int)'\a');
                Mat[sx][sy]=2;
                graf_mouse(M_OFF,(MFORM *)0);
                simbol(sx,sy);
                graf_mouse(M_ON,(MFORM *)0);
                graf_mouse(ARROW,(MFORM *)0);
              }
            }
            else
              Cconout((int)'\a');
          }
          break;
        case MU_MESAG:
        case MU_KEYBD|MU_MESAG:
        case MU_BUTTON|MU_MESAG:
        case MU_KEYBD|MU_BUTTON|MU_MESAG:
          switch(msg[0])
          {
            case AC_OPEN:
              if(Opn)
                wind_set(WHandle,WF_TOP);
              else
              {
                WHandle=wind_create(NAME|CLOSER|FULLER|MOVER|INFO,0,0,0,0);
                wind_calc(WC_BORDER,NAME|CLOSER|FULLER|MOVER|INFO,X0-21,Y0-21,154,154,&Wx,&Wy,&Ww,&Wh);
                wind_set(WHandle,WF_NAME," Pegged ");
                wind_set(WHandle,WF_INFO,Kraj?Nkugl==1?Por_0:Por_1:Por_2);
                wind_open(WHandle,Wx,Wy,Ww,Wh);
                Opn=1;
              }
              break;
            case AC_CLOSE:
              Opn=0;
              break;
            case WM_REDRAW:
              wind_update(BEG_UPDATE);
              wind_get(msg[3],WF_FIRSTXYWH,&fx,&fy,&fw,&fh);
              while(fw&&fh)
              {
                int p[4];
                p[0]=max(fx,msg[4]);
                p[1]=max(fy,msg[5]);
                p[2]=min(fx+fw,msg[4]+msg[6])-1;
                p[3]=min(fy+fh,msg[5]+msg[7])-1;
                if(p[0]<=p[2]&&p[1]<=p[3])
                {
                  vs_clip(Handle,1,p);
                  obnovi();
                  vs_clip(Handle,0,p);
                }
                wind_get(msg[3],WF_NEXTXYWH,&fx,&fy,&fw,&fh);
              }
              wind_update(END_UPDATE);
              break;
            case WM_TOPPED:
              wind_set(msg[3],WF_TOP);
              break;
            case WM_CLOSED:
              wind_close(msg[3]);
              wind_delete(msg[3]);
              Opn=0;
              break;
            case WM_FULLED:
              select();
              break;
            case WM_MOVED:
              wind_calc(WC_WORK,NAME|CLOSER|FULLER|MOVER|INFO,msg[4],msg[5],msg[6],msg[7],&fx,&fy,&fw,&fh);
              X0=(fx+21)/16;
              Y0=(fy+21)/16;
              X0=X0<2?32:X0*16;
              Y0=Y0<5?80:Y0*16;
              fx=X0-21;
              fy=Y0-21;
              wind_calc(WC_BORDER,NAME|CLOSER|FULLER|MOVER|INFO,fx,fy,fw,fh,&Wx,&Wy,&Ww,&Wh);
              wind_set(msg[3],WF_CURRXYWH,Wx,Wy,Ww,Wh);
          }
      }
  }
  v_clsvwk(Handle);
  appl_exit();
}
