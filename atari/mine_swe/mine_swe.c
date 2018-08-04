/* Project MINE_SWE.PRJ, Stack 131072 bytes, No stack checking */

#include <aes.h>
#include <tos.h>
#include <vdi.h>

#define rnd(x) ((unsigned int)(Random()%(x)))
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

int FFARR[25][16]=
{
  0xffff,0xc001,0xa003,0x9557,0x8aab,0x9557,0x8aab,0x9557,
  0x8aab,0x9557,0x8aab,0x9557,0x8aab,0x9557,0xbffd,0xffff,
  0xffff,0xc001,0xa003,0x9557,0x880b,0x9007,0x81c3,0x93e7,
  0x8363,0x93e7,0x81c3,0x9007,0x880b,0x9557,0xbffd,0xffff,
  0xffff,0x8000,0x800c,0x87f2,0x8fe2,0x9c44,0x998c,0x9b1c,
  0x9a2c,0x9c6c,0x98cc,0x911c,0xa3f8,0xa7f0,0x9800,0x8000,
  0xffff,0x8000,0xbffe,0xb80e,0xb006,0xa3e2,0xa632,0xa412,
  0xa492,0xa412,0xa632,0xa3e2,0xb006,0xb80e,0xbffe,0x8000,
  0xffff,0x8000,0x8000,0x87f0,0x8ff8,0x9c1c,0x99cc,0x9bec,
  0x9b6c,0x9bec,0x99cc,0x9c1c,0x8ff8,0x87f0,0x8000,0x8000,
  0xffff,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,
  0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,
  0xffff,0x8000,0x8000,0x80c0,0x81c0,0x83c0,0x87c0,0x81c0,
  0x81c0,0x81c0,0x81c0,0x81c0,0x81c0,0x83e0,0x8000,0x8000,
  0xffff,0x8000,0x8000,0x8ff8,0x9c1c,0x801c,0x801c,0x801c,
  0x8ff8,0x9c00,0x9c00,0x9c00,0x9c00,0x9ffc,0x8000,0x8000,
  0xffff,0x8000,0x8000,0x8ff8,0x9c1c,0x801c,0x801c,0x801c,
  0x81f8,0x801c,0x801c,0x801c,0x9c1c,0x8ff8,0x8000,0x8000,
  0xffff,0x8000,0x8000,0x81c0,0x8380,0x8700,0x8e1c,0x9c1c,
  0x9c1c,0x9ffc,0x801c,0x801c,0x801c,0x801c,0x8000,0x8000,
  0xffff,0x8000,0x8000,0x9ffc,0x9c1c,0x9c00,0x9c00,0x9c00,
  0x9ff8,0x801c,0x801c,0x801c,0x9c1c,0x8ff8,0x8000,0x8000,
  0xffff,0x8000,0x8000,0x8ff8,0x9c1c,0x9c00,0x9c00,0x9c00,
  0x9ff8,0x9c1c,0x9c1c,0x9c1c,0x9c1c,0x8ff8,0x8000,0x8000,
  0xffff,0x8000,0x8000,0x9ffc,0x9c1c,0x801c,0x8038,0x8070,
  0x80e0,0x81c0,0x81c0,0x81c0,0x81c0,0x81c0,0x8000,0x8000,
  0xffff,0x8000,0x8000,0x8ff8,0x9c1c,0x9c1c,0x9c1c,0x9c1c,
  0x8ff8,0x9c1c,0x9c1c,0x9c1c,0x9c1c,0x8ff8,0x8000,0x8000,
  0x0000,0x0000,0x7ff0,0xe038,0xe038,0xe078,0xe0b8,0xe138,
  0xe238,0xe438,0xe838,0xf038,0xe038,0xe038,0x7ff0,0x0000,
  0x0000,0x0000,0x0300,0x0700,0x0f00,0x1f00,0x0700,0x0700,
  0x0700,0x0700,0x0700,0x0700,0x0700,0x0700,0x0f80,0x0000,
  0x0000,0x0000,0x7ff0,0xe038,0x0038,0x0038,0x0038,0x0038,
  0x7ff0,0xe000,0xe000,0xe000,0xe000,0xe000,0xfff8,0x0000,
  0x0000,0x0000,0x7ff0,0xe038,0x0038,0x0038,0x0038,0x0038,
  0x0ff0,0x0038,0x0038,0x0038,0x0038,0xe038,0x7ff0,0x0000,
  0x0000,0x0000,0x0e00,0x1c00,0x3800,0x7038,0xe038,0xe038,
  0xe038,0xfff8,0x0038,0x0038,0x0038,0x0038,0x0038,0x0000,
  0x0000,0x0000,0xfff8,0xe038,0xe000,0xe000,0xe000,0xe000,
  0xfff0,0x0038,0x0038,0x0038,0x0038,0xe038,0x7ff0,0x0000,
  0x0000,0x0000,0x7ff0,0xe038,0xe000,0xe000,0xe000,0xe000,
  0xfff0,0xe038,0xe038,0xe038,0xe038,0xe038,0x7ff0,0x0000,
  0x0000,0x0000,0xfff8,0xe038,0x0038,0x0038,0x0070,0x00e0,
  0x01c0,0x0380,0x0700,0x0700,0x0700,0x0700,0x0700,0x0000,
  0x0000,0x0000,0x7ff0,0xe038,0xe038,0xe038,0xe038,0xe038,
  0x7ff0,0xe038,0xe038,0xe038,0xe038,0xe038,0x7ff0,0x0000,
  0x0000,0x0000,0x7ff0,0xe038,0xe038,0xe038,0xe038,0xe038,
  0x7ff8,0x0038,0x0038,0x0038,0x0038,0xe038,0x7ff0,0x0000,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x1fc0,
  0x3fe0,0x1fc0,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
};
int Handle;
int Max;
int May;
int WHandle;
int Flag;
int _p[38][20];
int _b[38][20];
int _x;
int _y;
int _w;
int _h;
int _m;
int _o;
int _n;
int _hlp=0;
int _sscr;
int _scr;
int _igra;
extern void str_copy(char *,char *);
extern void new_msvc(void);
void (*old_msvc)(void);

void mina(void)
{
  int p[4]={560,0,623,15};
  int s;
  vsf_interior(Handle,FIS_HOLLOW);
  vr_recfl(Handle,p);
  vsf_interior(Handle,FIS_USER);
  s=_n>0?_n:-_n;
  p[0]=608;
  do
  {
    vsf_udpat(Handle,FFARR[14+s%10],1);
    vr_recfl(Handle,p);
    s/=10;
    p[0]-=16;
    p[2]-=16;
  }
  while(s);
  if(_n<0)
  {
    vsf_udpat(Handle,FFARR[24],1);
    vr_recfl(Handle,p);
  }
}

void score(void)
{
  int p[4]={320,0,415,15};
  int s;
  vsf_interior(Handle,FIS_HOLLOW);
  vr_recfl(Handle,p);
  vsf_interior(Handle,FIS_USER);
  s=_scr>0?_scr:-_scr;
  p[0]=400;
  do
  {
    vsf_udpat(Handle,FFARR[14+s%10],1);
    vr_recfl(Handle,p);
    s/=10;
    p[0]-=16;
    p[2]-=16;
  }
  while(s);
  if(_scr<0)
  {
    vsf_udpat(Handle,FFARR[24],1);
    vr_recfl(Handle,p);
  }
}

void centriraj(int w,int h,int m)
{
  _w=w;
  _h=h;
  _m=m;
  _x=((Max-_w)/2)+1;
  _y=((May-_h)/2)+4;
}

void izbroji(int x,int y)
{
  if(x>=0&&x<_w&&y>=0&&y<_h&&_p[x][y]!=-1)
    _p[x][y]++;
}

void novaigra(void)
{
  int x;
  int y;
  int u;
  int fx;
  int fy;
  int fw;
  int fh;
  for(x=0;x<_w;x++)
    for(y=0;y<_h;y++)
    {
      _p[x][y]=0;
      _b[x][y]=0;
    }
  for(u=0;u<_m;u++)
  {
    while(_p[x=rnd(_w)][y=rnd(_h)]==-1);
    _p[x][y]=-1;
    izbroji(x-1,y-1);
    izbroji(x,y-1);
    izbroji(x+1,y-1);
    izbroji(x+1,y);
    izbroji(x+1,y+1);
    izbroji(x,y+1);
    izbroji(x-1,y+1);
    izbroji(x-1,y);
  }
  _o=_w*_h;
  _n=_m;
  if(_hlp)
    for(u=0;u<_m/2;u++)
    {
      while(_b[x=rnd(_w)][y=rnd(_h)]);
      if(_p[x][y]==-1)
      {
        _n--;
        _b[x][y]=1;
      }
      else
      {
        _o--;
        _b[x][y]=_p[x][y]?3:2;
      }
    }
  _sscr=0;
  _scr=(int)((10000.0/(float)_o)*(float)_n*(1.0-(float)_hlp*0.25));
  Flag=_o==_m?3:1;
  _igra=0;
  graf_mouse(M_OFF,(MFORM *)0);
  mina();
  score();
  graf_mouse(M_ON,(MFORM *)0);
  wind_calc(WC_BORDER,NAME|FULLER|MOVER|INFO,_x*16-6,_y*16-6,_w*16+13,_h*16+13,&fx,&fy,&fw,&fh);
  wind_set(WHandle,WF_INFO," Play the game");
  wind_set(WHandle,WF_CURRXYWH,fx,fy,fw,fh);
  wind_set(WHandle,WF_TOP);
  wind_get(WHandle,WF_WORKXYWH,&fx,&fy,&fw,&fh);
  form_dial(FMD_START,fx,fy,fw,fh,fx,fy,fw,fh);
  form_dial(FMD_FINISH,fx,fy,fw,fh,fx,fy,fw,fh);
}

void simbol(int x,int y,int uzorak)
{
  int p[4];
  if(_x+x<Max+2&&_y+y<May+4)
  {
    p[0]=(x+_x)*16;
    p[1]=(y+_y)*16;
    p[2]=p[0]+15;
    p[3]=p[1]+15;
    vsf_udpat(Handle,FFARR[uzorak],1);
    vr_recfl(Handle,p);
  }
}

void popuni(int,int);

void puni(int x,int y)
{
  if(x>=0&&x<_w&&y>=0&&y<_h&&_b[x][y]!=3)
    popuni(x,y);
}

void popuni(int x,int y)
{
  if(_b[x][y]<2)
  {
    if(_b[x][y]==1)
    {
      _n++;
      mina();
      _scr-=25;
      score();
    }
    simbol(x,y,_p[x][y]+5);
    _o--;
  }
  _b[x][y]=3;
  if(!_p[x][y])
  {
    puni(x-1,y-1);
    puni(x,y-1);
    puni(x+1,y-1);
    puni(x+1,y);
    puni(x+1,y+1);
    puni(x,y+1);
    puni(x-1,y+1);
    puni(x-1,y);
  }
}

int broj(char *s)
{
  int r=0;
  while(*s)
    r=10*r+*s++-'0';
  return r;
}

void dok(int n,char *d,char *s)
{
  int i;
  int x=62;
  for(i=0;i<n;i++)
  {
    d[i]=s[i]^x;
    x=s[i];
  }
}

void kod(int n,char *d,char *s)
{
  int i;
  int x=62;
  for(i=0;i<n;i++)
  {
    d[i]=s[i]^x;
    x=d[i];
  }
}

void main(void)
{
  #define T0_ 29
  #define T1_ 6
  #define T2_ 7
  #define T3_ 23
  #define T4_ 4
  enum
  {
    T0_ABOUT=8,
    T0_NEWGAME=17,T0_HELP,
    T0_BEGINNER=20,T0_ADVANCED,T0_EXPERT,T0_CUSTOM,
    T0_QUIT=25,
    T0_VIEW=27,T0_SAVE
  };
  enum
  {
    T1_CONTINUE=5
  };
  enum
  {
    T2_X=2,T2_Y,T2_MINE,T2_CANCEL,T2_OK
  };
  enum
  {
    T3_N1=7,T3_N2,T3_N3,T3_N4,T3_N5,
    T3_S1=17,T3_S2,T3_S3,T3_S4,T3_S5,T3_CONTINUE
  };
  enum
  {
    T4_NAME=2,T4_OK
  };
  static char file_hig[13]="mine_swe.hig";
  static char tw[3]="  ";
  static char th[3]="  ";
  static char tm[4]="   ";
  static char pom[20]="Lazic Goran Chupcko";
  static char rsc_string_0[1]="";
  static char rsc_string_1[21]=" ~~~~~~~~~~~~~~~~~~~";
  static char rsc_string_2[9]="CONTINUE";
  static char rsc_string_3[3]="OK";
  static char rsc_string_4[2]=":";
  int sel=T0_BEGINNER;
  int x;
  int y;
  int b;
  int s1;
  int s2;
  int key;
  int trash;
  int fhand;
  int fx;
  int fy;
  int fw;
  int fh;
  static int work_in[11]=
  {
    0,SOLID,1,0,0,0,0,FIS_USER,0,1,2
  };
  static int work_out[57];
  static int msg[8];
  static rsc_image[64]=
  {
    0x0001,0x8000,0x0001,0x8000,0x1ff1,0x8ff8,0x3839,0x9c1c,
    0x3839,0x9c0c,0x0039,0x9c00,0x0039,0x9c00,0x0039,0x9c00,
    0x0039,0x9c00,0x0039,0x9c00,0x3039,0x9c0c,0x3839,0x9c1c,
    0x1ff1,0x8ff8,0x0001,0x8000,0x0001,0x8000,0xffff,0xffff,
    0xffff,0xffff,0x0001,0x8000,0x0001,0x8000,0x1ff1,0x8ff8,
    0x3839,0x9c1c,0x3819,0x9c0c,0x3801,0x9c00,0x3801,0x9c00,
    0x1ff1,0x9c00,0x0039,0x9c00,0x0039,0x9c00,0x3039,0x9c0c,
    0x3839,0x9c1c,0x1ff1,0x8ff8,0x0001,0x8000,0x0001,0x8000
  };
  static BITBLK rsc_bitblk=
  {
    rsc_image,4,32,0,0,BLACK
  };
  static TEDINFO rsc_tedinfo[4]=
  {
    "38","X (2..38)     : __","99",IBM,6,TE_LEFT,0x1180,0,255,3,19,
    "20","Y (2..20)     : __","99",IBM,6,TE_LEFT,0x1180,0,255,3,19,
    "200","Mine (2..200) : ___","999",IBM,6,TE_LEFT,0x1180,0,255,4,20,
    "Lazic Goran Chupcko","Your name : ___________________","nnnnnnnnnnnnnnnnnnn",IBM,6,TE_LEFT,0x1180,0,255,20,32
  };
  static OBJECT rsc_drvo_0[T0_]=
  {
    -1,1,6,G_IBOX,NONE,NORMAL,0x00000000l,0,0,80,25,
    6,2,2,G_BOX,NONE,NORMAL,0x00001100l,0,0,80,513,
    1,3,5,G_IBOX,NONE,NORMAL,0x00000000l,2,0,17,769,
    4,-1,-1,G_TITLE,NONE,NORMAL,(long)" ",0,0,4,769,
    5,-1,-1,G_TITLE,NONE,NORMAL,(long)" Game",4,0,6,769,
    2,-1,-1,G_TITLE,NONE,NORMAL,(long)" Score",10,0,7,769,
    0,7,26,G_IBOX,NONE,NORMAL,0x00000000l,0,769,80,19,
    16,8,15,G_BOX,NONE,NORMAL,0x00ff1100l,2,0,20,8,
    9,-1,-1,G_STRING,NONE,NORMAL,(long)"  About program...",0,0,20,1,
    10,-1,-1,G_STRING,NONE,DISABLED,(long)" ~~~~~~~~~~~~~~~~~~",0,1,20,1,
    11,-1,-1,G_STRING,NONE,NORMAL,(long)rsc_string_0,0,2,20,1,
    12,-1,-1,G_STRING,NONE,NORMAL,(long)rsc_string_0,0,3,20,1,
    13,-1,-1,G_STRING,NONE,NORMAL,(long)rsc_string_0,0,4,20,1,
    14,-1,-1,G_STRING,NONE,NORMAL,(long)rsc_string_0,0,5,20,1,
    15,-1,-1,G_STRING,NONE,NORMAL,(long)rsc_string_0,0,6,20,1,
    7,-1,-1,G_STRING,NONE,NORMAL,(long)rsc_string_0,0,7,20,1,
    26,17,25,G_BOX,NONE,NORMAL,0x00ff1100l,6,0,21,9,
    18,-1,-1,G_STRING,NONE,NORMAL,(long)"  New game - <Undo>",0,0,21,1,
    19,-1,-1,G_STRING,NONE,NORMAL,(long)"  Help     - <Help>",0,1,21,1,
    20,-1,-1,G_STRING,NONE,DISABLED,(long)rsc_string_1,0,2,21,1,
    21,-1,-1,G_STRING,NONE,CHECKED|DISABLED,(long)"  Beginner",0,3,21,1,
    22,-1,-1,G_STRING,NONE,NORMAL,(long)"  Advanced",0,4,21,1,
    23,-1,-1,G_STRING,NONE,NORMAL,(long)"  Expert",0,5,21,1,
    24,-1,-1,G_STRING,NONE,NORMAL,(long)"  Custom...",0,6,21,1,
    25,-1,-1,G_STRING,NONE,DISABLED,(long)rsc_string_1,0,7,21,1,
    16,-1,-1,G_STRING,NONE,NORMAL,(long)"  Quit...",0,8,21,1,
    6,27,28,G_BOX,NONE,NORMAL,0x00ff1100l,12,0,11,2,
    28,-1,-1,G_STRING,NONE,NORMAL,(long)"  View...",0,0,11,1,
    26,-1,-1,G_STRING,LASTOB,NORMAL,(long)"  Save...",0,1,11,1
  };
  static OBJECT rsc_drvo_1[T1_]=
  {
    -1,1,5,G_BOX,NONE,OUTLINED,0x00021100L,0,0,36,13,
    2,-1,-1,G_STRING,NONE,NORMAL,(long)"Mine sweeper  V .",4,2,19,1,
    3,-1,-1,G_IMAGE,NONE,NORMAL,(long)&rsc_bitblk,28,2,4,2,
    4,-1,-1,G_STRING,NONE,NORMAL,(long)"Author : Lazic Goran Chupcko",4,6,28,1,
    5,-1,-1,G_STRING,NONE,NORMAL,(long)"... Serbia",9,7,18,1,
    0,-1,-1,G_BUTTON,SELECTABLE|DEFAULT|EXIT|LASTOB,NORMAL,(long)rsc_string_2,12,10,12,1
  };
  static OBJECT rsc_drvo_2[T2_]=
  {
    -1,1,6,G_BOX,NONE,OUTLINED,0x00021100l,0,0,37,13,
    2,-1,-1,G_STRING,NONE,NORMAL,(long)"Dimension of the game field :",4,2,29,1,
    3,-1,-1,G_FTEXT,EDITABLE,NORMAL,(long)&rsc_tedinfo[0],9,5,18,1,
    4,-1,-1,G_FTEXT,EDITABLE,NORMAL,(long)&rsc_tedinfo[1],9,6,18,1,
    5,-1,-1,G_FTEXT,EDITABLE,NORMAL,(long)&rsc_tedinfo[2],9,7,19,1,
    6,-1,-1,G_BUTTON,SELECTABLE|EXIT,NORMAL,(long)"CANCEL",5,10,10,1,
    0,-1,-1,G_BUTTON,SELECTABLE|DEFAULT|EXIT|LASTOB,NORMAL,(long)rsc_string_3,22,10,10,1
  };
  static OBJECT rsc_drvo_3[T3_]=
  {
    -1,1,22,G_BOX,NONE,OUTLINED,0x00021100l,0,0,38,14,
    2,-1,-1,G_STRING,NONE,NORMAL,(long)"High score :",13,2,12,1,
    3,-1,-1,G_STRING,NONE,NORMAL,(long)"1.",4,4,2,1,
    4,-1,-1,G_STRING,NONE,NORMAL,(long)"2.",4,5,2,1,
    5,-1,-1,G_STRING,NONE,NORMAL,(long)"3.",4,6,2,1,
    6,-1,-1,G_STRING,NONE,NORMAL,(long)"4.",4,7,2,1,
    7,-1,-1,G_STRING,NONE,NORMAL,(long)"5.",4,8,2,1,
    8,-1,-1,G_STRING,NONE,NORMAL,(long)"Lazic Goran Chupcko",7,4,19,1,
    9,-1,-1,G_STRING,NONE,NORMAL,(long)"Lazic Goran Chupcko",7,5,19,1,
    10,-1,-1,G_STRING,NONE,NORMAL,(long)"Lazic Goran Chupcko",7,6,19,1,
    11,-1,-1,G_STRING,NONE,NORMAL,(long)"Lazic Goran Chupcko",7,7,19,1,
    12,-1,-1,G_STRING,NONE,NORMAL,(long)"Lazic Goran Chupcko",7,8,19,1,
    13,-1,-1,G_STRING,NONE,NORMAL,(long)rsc_string_4,27,4,1,1,
    14,-1,-1,G_STRING,NONE,NORMAL,(long)rsc_string_4,27,5,1,1,
    15,-1,-1,G_STRING,NONE,NORMAL,(long)rsc_string_4,27,6,1,1,
    16,-1,-1,G_STRING,NONE,NORMAL,(long)rsc_string_4,27,7,1,1,
    17,-1,-1,G_STRING,NONE,NORMAL,(long)rsc_string_4,27,8,1,1,
    18,-1,-1,G_STRING,NONE,NORMAL,(long)"02500",29,4,5,1,
    19,-1,-1,G_STRING,NONE,NORMAL,(long)"02000",29,5,5,1,
    20,-1,-1,G_STRING,NONE,NORMAL,(long)"01500",29,6,5,1,
    21,-1,-1,G_STRING,NONE,NORMAL,(long)"01000",29,7,5,1,
    22,-1,-1,G_STRING,NONE,NORMAL,(long)"00500",29,8,5,1,
    0,-1,-1,G_BUTTON,SELECTABLE|DEFAULT|EXIT|LASTOB,NORMAL,(long)rsc_string_2,13,11,12,1
  };
  static OBJECT rsc_drvo_4[T4_]=
  {
    -1,1,3,G_BOX,NONE,OUTLINED,0x00021100l,0,0,39,11,
    2,-1,-1,G_STRING,NONE,NORMAL,(long)"Congratulation !",5,2,16,1,
    3,-1,-1,G_FTEXT,EDITABLE,NORMAL,(long)&rsc_tedinfo[3],4,5,31,1,
    0,-1,-1,G_BUTTON,SELECTABLE|DEFAULT|EXIT|LASTOB,NORMAL,(long)rsc_string_3,22,8,12,1
  };
  KBDVBASE *kbd=Kbdvbase();
  old_msvc=kbd->kb_mousevec;
  kbd->kb_mousevec=new_msvc;
  appl_init();
  Handle=graf_handle(&trash,&trash,&trash,&trash);
  v_opnvwk(work_in,&Handle,work_out);
  vswr_mode(Handle,MD_REPLACE);
  vsf_perimeter(Handle,1);
  if(Getrez()!=2)
    form_alert(1,"[3][|  Only high resolution ! ][  OK  ]");
  else
  {
    for(trash=0;trash<T0_;trash++)
      rsrc_obfix(rsc_drvo_0,trash);
    for(trash=0;trash<T1_;trash++)
      rsrc_obfix(rsc_drvo_1,trash);
    for(trash=0;trash<T2_;trash++)
      rsrc_obfix(rsc_drvo_2,trash);
    for(trash=0;trash<T3_;trash++)
      rsrc_obfix(rsc_drvo_3,trash);
    for(trash=0;trash<T4_;trash++)
      rsrc_obfix(rsc_drvo_4,trash);
    rsc_drvo_4[T4_NAME].ob_spec.tedinfo->te_ptext[0]='\0';
    if((fhand=Fopen(file_hig,FO_READ))>0)
    {
      for(trash=0;trash<5;trash++)
      {
        Fread(fhand,19l,(void *)pom);
        dok(19,rsc_drvo_3[T3_N1+trash].ob_spec.free_string,pom);
        Fread(fhand,5l,(void *)pom);
        dok(5,rsc_drvo_3[T3_S1+trash].ob_spec.free_string,pom);
      }
      Fclose(fhand);
    }
    if((fhand=Fopen("mine_swe.spr",FO_READ))>0)
    {
      Fread(fhand,800l,(void *)FFARR);
      Fclose(fhand);
    }
    graf_mouse(ARROW,(MFORM *)0);
    graf_mouse(M_OFF,(MFORM *)0);
    menu_bar(rsc_drvo_0,1);
    graf_mouse(M_ON,(MFORM *)0);
    wind_get(0,WF_CURRXYWH,&trash,&trash,&Max,&May);
    Max=Max/16-2;
    May=May/16-5;
    WHandle=wind_create(NAME|FULLER|MOVER|INFO,0,0,0,0);
    wind_set(WHandle,WF_NAME," Mine sweeper ");
    wind_set(WHandle,WF_INFO,rsc_string_0);
    wind_open(WHandle,249,117,143,179);
    centriraj(8,8,10);
    novaigra();
    do
    {
      switch(evnt_multi(MU_KEYBD|MU_BUTTON|MU_MESAG,1,1,1,0,0,0,0,0,0,0,0,0,0,msg,0,0,&x,&y,&b,&s1,&key,&trash))
      {
        case MU_KEYBD:
        case MU_KEYBD|MU_BUTTON:
          switch(key)
          {
            case 0x011b:
              if(Flag==1&&s1==(K_LSHIFT|K_RSHIFT)&&broj(rsc_drvo_3[T3_S1].ob_spec.free_string)>9999)
              {
                graf_mouse(M_OFF,(MFORM *)0);
                for(y=0;y<_h;y++)
                  for(x=0;x<_w;x++)
                    if(_b[x][y]<2)
                      simbol(x,y,_p[x][y]+5);
                evnt_timer(500,0);
                for(y=0;y<_h;y++)
                  for(x=0;x<_w;x++)
                    if(_b[x][y]<2)
                simbol(x,y,_b[x][y]);
                graf_mouse(M_ON,(MFORM *)0);
              }
              break;
            case 0x6200:
              rsc_drvo_0[T0_HELP].ob_state=_hlp?NORMAL:CHECKED;
              _hlp=!_hlp;
              novaigra();
              break;
            case 0x6100:
              novaigra();
          }
          break;
        case MU_BUTTON:
          evnt_button(1,3,0,&x,&y,&trash,&s2);
          x=(x/16)-_x;
          y=(y/16)-_y;
          if(x>=0&&x<_w&&y>=0&&y<_h)
            if(Flag==1&&_b[x][y]<2)
              if(s1==(K_ALT|K_CTRL)&&s2==K_LSHIFT)
              {
                graf_mouse(M_OFF,(MFORM *)0);
                simbol(x,y,_p[x][y]+5);
                evnt_timer(500,0);
                simbol(x,y,_b[x][y]);
                graf_mouse(M_ON,(MFORM *)0);
              }
              else
                if(b==3)
                {
                  graf_mouse(M_OFF,(MFORM *)0);
                  _b[x][y]=!_b[x][y];
                  simbol(x,y,_b[x][y]);
                  if(_b[x][y])
                  {
                    _n--;
                    _sscr+=(_p[x][y]==-1)*20;
                  }
                  else
                  {
                    _n++;
                    _scr-=25;
                    score();
                  }
                  mina();
                  graf_mouse(M_ON,(MFORM *)0);
                }
                else
                  if(_b[x][y])
                    Cconout((int)'\a');
                  else
                  {
                    _igra++;
                    if(_p[x][y]==-1)
                    {
                      int xx;
                      int yy;
                      Dosound((void *)"\x0\xd0\x1\x2\x6\x3f\x8\x10\xb\x3f\xc\x60\xd\x0\x7\x36\xff");
                      wind_set(WHandle,WF_INFO," Game over !");
                      _p[x][y]=-2;
                      _b[x][y]=3;
                      graf_mouse(M_OFF,(MFORM *)0);
                      simbol(x,y,_p[x][y]+5);
                      for(yy=0;yy<_h;yy++)
                        for(xx=0;xx<_w;xx++)
                          if(_p[xx][yy]==-1)
                          {
                            _b[xx][yy]=3;
                            simbol(xx,yy,_p[xx][yy]+5);
                          }
                          else
                            if(_b[xx][yy]==1)
                            {
                              _p[xx][yy]=-3;
                              _b[xx][yy]=3;
                              simbol(xx,yy,_p[xx][yy]+5);
                              _scr-=25;
                              score();
                            }
                      _scr+=_sscr;
                      _scr=_scr<0?_scr:-_scr;
                      score();
                      graf_mouse(M_ON,(MFORM *)0);
                      Flag=2;
                    }
                    else
                    {
                      _scr+=10;
                      graf_mouse(M_OFF,(MFORM *)0);
                      popuni(x,y);
                      score();
                      graf_mouse(M_ON,(MFORM *)0);
                      if(_o==_m)
                        Flag=3;
                    }
                  }
            else
              Cconout((int)'\a');
          break;
        case MU_MESAG:
        case MU_KEYBD|MU_MESAG:
        case MU_BUTTON|MU_MESAG:
        case MU_KEYBD|MU_BUTTON|MU_MESAG:
          switch(msg[0])
          {
            case MN_SELECTED:
              switch(msg[4])
              {
                case T0_ABOUT:
                  form_center(rsc_drvo_1,&fx,&fy,&fw,&fh);
                  wind_update(BEG_UPDATE);
                  form_dial(FMD_START,fx,fy,fw,fh,fx,fy,fw,fh);
                  objc_draw(rsc_drvo_1,0,1,fx,fy,fw,fh);
                  form_do(rsc_drvo_1,0);
                  form_dial(FMD_FINISH,fx,fy,fw,fh,fx,fy,fw,fh);
                  wind_update(END_UPDATE);
                  rsc_drvo_1[T1_CONTINUE].ob_state=NORMAL;
                  break;
                case T0_NEWGAME:
                  novaigra();
                  break;
                case T0_HELP:
                  rsc_drvo_0[T0_HELP].ob_state=_hlp?NORMAL:CHECKED;
                  _hlp=!_hlp;
                  novaigra();
                  break;
                case T0_BEGINNER:
                  rsc_drvo_0[sel].ob_state=NORMAL;
                  rsc_drvo_0[sel=T0_BEGINNER].ob_state=CHECKED|DISABLED;
                  centriraj(8,8,10);
                  novaigra();
                  break;
                case T0_ADVANCED:
                  rsc_drvo_0[sel].ob_state=NORMAL;
                  rsc_drvo_0[sel=T0_ADVANCED].ob_state=CHECKED|DISABLED;
                  centriraj(16,16,45);
                  novaigra();
                  break;
                case T0_EXPERT:
                  rsc_drvo_0[sel].ob_state=NORMAL;
                  rsc_drvo_0[sel=T0_EXPERT].ob_state=CHECKED|DISABLED;
                  centriraj(32,16,100);
                  novaigra();
                  break;
                case T0_CUSTOM:
                  str_copy(tw,rsc_drvo_2[T2_X].ob_spec.tedinfo->te_ptext);
                  str_copy(th,rsc_drvo_2[T2_Y].ob_spec.tedinfo->te_ptext);
                  str_copy(tm,rsc_drvo_2[T2_MINE].ob_spec.tedinfo->te_ptext);
                  form_center(rsc_drvo_2,&fx,&fy,&fw,&fh);
                  wind_update(BEG_UPDATE);
                  form_dial(FMD_START,fx,fy,fw,fh,fx,fy,fw,fh);
                  do
                  {
                    objc_draw(rsc_drvo_2,0,1,fx,fy,fw,fh);
                    if(form_do(rsc_drvo_2,T2_X)==T2_OK)
                    {
                      int daw;
                      int dah;
                      int dam;
                      rsc_drvo_2[T2_OK].ob_state=NORMAL;
                      daw=broj(rsc_drvo_2[T2_X].ob_spec.tedinfo->te_ptext);
                      dah=broj(rsc_drvo_2[T2_Y].ob_spec.tedinfo->te_ptext);
                      dam=broj(rsc_drvo_2[T2_MINE].ob_spec.tedinfo->te_ptext);
                      if(2<=daw&&daw<=38&&2<=dah&&dah<=20&&2<=dam&&dam<=200&&dam<daw*dah)
                      {
                        rsc_drvo_0[sel].ob_state=NORMAL;
                        rsc_drvo_0[sel=T0_CUSTOM].ob_state=CHECKED;
                        centriraj(daw,dah,dam);
                        novaigra();
                        trash=0;
                      }
                      else
                      {
                        Cconout((int)'\a');
                        form_alert(1,"[3][|  Wrong dimension|  of the game field ! ][  OK  ]");
                        trash=3;
                      }
                    }
                    else
                    {
                      rsc_drvo_2[T2_CANCEL].ob_state=NORMAL;
                      trash=2;
                    }
                    if(trash>1)
                    {
                      str_copy(rsc_drvo_2[T2_X].ob_spec.tedinfo->te_ptext,tw);
                      str_copy(rsc_drvo_2[T2_Y].ob_spec.tedinfo->te_ptext,th);
                      str_copy(rsc_drvo_2[T2_MINE].ob_spec.tedinfo->te_ptext,tm);
                    }
                  }
                  while(trash%2);
                  form_dial(FMD_FINISH,fx,fy,fw,fh,fx,fy,fw,fh);
                  wind_update(END_UPDATE);
                  break;
                case T0_QUIT:
                  if(form_alert(2,"[2][|  Are you sure ?][  QUIT  | CANCEL ]")==1)
                    Flag=0;
                  break;
                case T0_VIEW:
                  form_center(rsc_drvo_3,&fx,&fy,&fw,&fh);
                  wind_update(BEG_UPDATE);
                  form_dial(FMD_START,fx,fy,fw,fh,fx,fy,fw,fh);
                  objc_draw(rsc_drvo_3,0,1,fx,fy,fw,fh);
                  form_do(rsc_drvo_3,0);
                  form_dial(FMD_FINISH,fx,fy,fw,fh,fx,fy,fw,fh);
                  wind_update(END_UPDATE);
                  rsc_drvo_3[T3_CONTINUE].ob_state=NORMAL;
                  break;
                case T0_SAVE:
                  if(form_alert(2,"[2][|  Are you sure ?][  SAVE  | CANCEL ]")==1)
                  {
                    graf_mouse(BUSYBEE,(MFORM *)0);
                    if((fhand=Fcreate(file_hig,FA_ARCHIVE))>0)
                    {
                      for(trash=0;trash<5;trash++)
                      {
                        kod(19,pom,rsc_drvo_3[T3_N1+trash].ob_spec.free_string);
                        Fwrite(fhand,19l,(void *)pom);
                        kod(5,pom,rsc_drvo_3[T3_S1+trash].ob_spec.free_string);
                        Fwrite(fhand,5l,(void *)pom);
                      }
                      Fclose(fhand);
                    }
                    graf_mouse(ARROW,(MFORM *)0);
                  }
              }
              evnt_button(1,3,0,&trash,&trash,&trash,&trash);
              menu_tnormal(rsc_drvo_0,msg[3],1);
              break;
            case WM_REDRAW:
              wind_update(BEG_UPDATE);
              wind_get(msg[3],WF_FIRSTXYWH,&fx,&fy,&fw,&fh);
              while(fw&&fh)
              {
                int q[4];
                q[0]=max(fx,msg[4]);
                q[1]=max(fy,msg[5]);
                q[2]=min(fx+fw,msg[4]+msg[6])-1;
                q[3]=min(fy+fh,msg[5]+msg[7])-1;
                if(q[0]<=q[2]&&q[1]<=q[3])
                {
                  int x;
                  int y;
                  int p[4];
                  int r[4];
                  vs_clip(Handle,1,q);
                  graf_mouse(M_OFF,(MFORM *)0);
                  p[0]=_x*16;
                  p[1]=_y*16;
                  p[2]=p[0]+_w*16;
                  p[3]=p[1]+_h*16;
                  if(q[0]<=p[0]||q[1]<=p[1]||q[2]>=p[2]||q[3]>=p[3])
                  {
                    p[0]-=6;
                    p[1]-=6;
                    p[2]+=6;
                    p[3]+=6;
                    vsf_interior(Handle,FIS_HOLLOW);
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
                    vsf_interior(Handle,FIS_USER);
                  }
                  p[0]=(q[0]/16)-_x;
                  p[0]=p[0]>0?p[0]:0;
                  r[0]=(p[0]+_x)*16;
                  p[1]=(q[1]/16)-_y;
                  p[1]=p[1]>0?p[1]:0;
                  r[1]=(p[1]+_y)*16;
                  p[2]=(q[2]/16)-_x;
                  p[2]=p[2]<_w?p[2]+1:_w;
                  r[2]=(p[2]+_x)*16;
                  p[3]=(q[3]/16)-_y;
                  p[3]=p[3]<_h?p[3]+1:_h;
                  r[3]=(p[3]+_y)*16;
                  vsf_udpat(Handle,FFARR[0],1);
                  vr_recfl(Handle,r);
                  for(y=p[1];y<p[3];y++)
                    for(x=p[0];x<p[2];x++)
                      switch(_b[x][y])
                      {
                        case 1:
                          simbol(x,y,1);
                          break;
                        case 2:
                        case 3:
                          simbol(x,y,_p[x][y]+5);
                      }
                  graf_mouse(M_ON,(MFORM *)0);
                  vs_clip(Handle,0,q);
                }
                wind_get(msg[3],WF_NEXTXYWH,&fx,&fy,&fw,&fh);
              }
              wind_update(END_UPDATE);
              break;
            case WM_TOPPED:
              wind_set(msg[3],WF_TOP);
              break;
            case WM_FULLED:
              novaigra();
              break;
            case WM_MOVED:
              wind_calc(WC_WORK,NAME|FULLER|MOVER|INFO,msg[4],msg[5],msg[6],msg[7],&fx,&fy,&fw,&fh);
              _x=(fx+6)/16;
              _y=(fy+6)/16;
              _x=_x<1?1:_x;
              _y=_y<5?4:_y;
              wind_calc(WC_BORDER,NAME|FULLER|MOVER|INFO,_x*16-6,_y*16-6,fw,fh,&fx,&fy,&fw,&fh);
              wind_set(msg[3],WF_CURRXYWH,fx,fy,fw,fh);
          }
      }
      if(Flag==3)
      {
        wind_set(WHandle,WF_INFO," You are win !");
        _scr+=_sscr;
        _scr=(int)((float)_scr*(_scr>0&&_igra>9?1.0:_igra/10.0));
        graf_mouse(M_OFF,(MFORM *)0);
        score();
        for(y=0;y<_h;y++)
          for(x=0;x<_w;x++)
            if(_p[x][y]==-1)
            {
              _b[x][y]=3;
              simbol(x,y,_p[x][y]+5);
            }
        graf_mouse(M_ON,(MFORM *)0);
        wind_update(BEG_UPDATE);
        if(_scr>broj(rsc_drvo_3[T3_S5].ob_spec.free_string))
        {
          int i;
          int j;
          form_center(rsc_drvo_4,&fx,&fy,&fw,&fh);
          form_dial(FMD_START,fx,fy,fw,fh,fx,fy,fw,fh);
          objc_draw(rsc_drvo_4,0,1,fx,fy,fw,fh);
          form_do(rsc_drvo_4,T4_NAME);
          form_dial(FMD_FINISH,fx,fy,fw,fh,fx,fy,fw,fh);
          rsc_drvo_4[T4_OK].ob_state=NORMAL;
          str_copy(rsc_drvo_3[T3_N5].ob_spec.free_string,rsc_drvo_4[T4_NAME].ob_spec.tedinfo->te_ptext);
          for(i=4,j=_scr;i>=0;i--,j/=10)
            rsc_drvo_3[T3_S5].ob_spec.free_string[i]=j%10+'0';
          for(i=0;i<4;i++)
            for(j=i+1;j<5;j++)
              if(broj(rsc_drvo_3[T3_S1+i].ob_spec.free_string)<broj(rsc_drvo_3[T3_S1+j].ob_spec.free_string))
              {
                str_copy(pom,rsc_drvo_3[T3_S1+i].ob_spec.free_string);
                str_copy(rsc_drvo_3[T3_S1+i].ob_spec.free_string,rsc_drvo_3[T3_S1+j].ob_spec.free_string);
                str_copy(rsc_drvo_3[T3_S1+j].ob_spec.free_string,pom);
                str_copy(pom,rsc_drvo_3[T3_N1+i].ob_spec.free_string);
                str_copy(rsc_drvo_3[T3_N1+i].ob_spec.free_string,rsc_drvo_3[T3_N1+j].ob_spec.free_string);
                str_copy(rsc_drvo_3[T3_N1+j].ob_spec.free_string,pom);
              }
        }
        wind_update(END_UPDATE);
        Flag=2;
      }
    }
    while(Flag);
    wind_close(WHandle);
    wind_delete(WHandle);
  }
  v_clsvwk(Handle);
  appl_exit();
  kbd->kb_mousevec=old_msvc;
}
