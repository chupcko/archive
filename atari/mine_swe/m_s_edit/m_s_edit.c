/* No stack checking */
#include <aes.h>
#include <tos.h>
#include <vdi.h>

#define TREE1 0
#define TREE2 1
#define ABOUT 8
#define LOAD 17
#define STANDARD 18
#define SAVE 20
#define QUIT 22
#define CLEAR 24
#define INVERT 26
#define SHIRIGHT 28
#define SHILEFT 29
#define SHIUP 30
#define SHIDOWN 31
#define MIRX 33
#define MIRY 34
#define ACONT 5

#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))

unsigned int FFARR[25][16],EFF[16]=
{
  43690u,    0u,32896u,    0u,32896u,    0u,32896u,    0u,
  43690u,    0u,32896u,    0u,32896u,    0u,32896u,    0u
};
int Handle,X0=160,Y0=144,Sel=0,WHandle,Wx,Wy,Ww,Wh;

void standard_ff(void)
{
  unsigned int d[25][16]=
  {
    65535u,49153u,40963u,38231u,35499u,38231u,35499u,38231u,
    35499u,38231u,35499u,38231u,35499u,38231u,49149u,65535u,
    65535u,49153u,40963u,38231u,34827u,36871u,33219u,37863u,
    33635u,37863u,33219u,36871u,34827u,38231u,49149u,65535u,
    65535u,32768u,32780u,34802u,36834u,40004u,39308u,39708u,
    39468u,40044u,39116u,37148u,41976u,42992u,38912u,32768u,
    65535u,32768u,49150u,47118u,45062u,41954u,42546u,42002u,
    42130u,42002u,42546u,41954u,45062u,47118u,49150u,32768u,
    65535u,32768u,32768u,34800u,36856u,39964u,39372u,39916u,
    39788u,39916u,39372u,39964u,36856u,34800u,32768u,32768u,
    65535u,32768u,32768u,32768u,32768u,32768u,32768u,32768u,
    32768u,32768u,32768u,32768u,32768u,32768u,32768u,32768u,
    65535u,32768u,32768u,32960u,33216u,33728u,34752u,33216u,
    33216u,33216u,33216u,33216u,33216u,33760u,32768u,32768u,
    65535u,32768u,32768u,36856u,39964u,32796u,32796u,32796u,
    36856u,39936u,39936u,39936u,39936u,40956u,32768u,32768u,
    65535u,32768u,32768u,36856u,39964u,32796u,32796u,32796u,
    33272u,32796u,32796u,32796u,39964u,36856u,32768u,32768u,
    65535u,32768u,32768u,33216u,33664u,34560u,36380u,39964u,
    39964u,40956u,32796u,32796u,32796u,32796u,32768u,32768u,
    65535u,32768u,32768u,40956u,39964u,39936u,39936u,39936u,
    40952u,32796u,32796u,32796u,39964u,36856u,32768u,32768u,
    65535u,32768u,32768u,36856u,39964u,39936u,39936u,39936u,
    40952u,39964u,39964u,39964u,39964u,36856u,32768u,32768u,
    65535u,32768u,32768u,40956u,39964u,32796u,32824u,32880u,
    32992u,33216u,33216u,33216u,33216u,33216u,32768u,32768u,
    65535u,32768u,32768u,36856u,39964u,39964u,39964u,39964u,
    36856u,39964u,39964u,39964u,39964u,36856u,32768u,32768u,
        0u,    0u,32752u,57400u,57400u,57464u,57528u,57656u,
    57912u,58424u,59448u,61496u,57400u,57400u,32752u,    0u,
        0u,    0u,  768u, 1792u, 3840u, 7936u, 1792u, 1792u,
     1792u, 1792u, 1792u, 1792u, 1792u, 1792u, 3968u,    0u,
        0u,    0u,32752u,57400u,   56u,   56u,   56u,   56u,
    32752u,57344u,57344u,57344u,57344u,57344u,65528u,    0u,
        0u,    0u,32752u,57400u,   56u,   56u,   56u,   56u,
     4080u,   56u,   56u,   56u,   56u,57400u,32752u,    0u,
        0u,    0u, 3584u, 7168u,14336u,28728u,57400u,57400u,
    57400u,65528u,   56u,   56u,   56u,   56u,   56u,    0u,
        0u,    0u,65528u,57400u,57344u,57344u,57344u,57344u,
    65520u,   56u,   56u,   56u,   56u,57400u,32752u,    0u,
        0u,    0u,32752u,57400u,57344u,57344u,57344u,57344u,
    65520u,57400u,57400u,57400u,57400u,57400u,32752u,    0u,
        0u,    0u,65528u,57400u,   56u,   56u,  112u,  224u,
      448u,  896u, 1792u, 1792u, 1792u, 1792u, 1792u,    0u,
        0u,    0u,32752u,57400u,57400u,57400u,57400u,57400u,
    32752u,57400u,57400u,57400u,57400u,57400u,32752u,    0u,
        0u,    0u,32752u,57400u,57400u,57400u,57400u,57400u,
    32760u,   56u,   56u,   56u,   56u,57400u,32752u,    0u,
        0u,    0u,    0u,    0u,    0u,    0u,    0u, 8128u,
    16352u, 8128u,    0u,    0u,    0u,    0u,    0u,    0u
  };
  int x,y;
  for(x=0;x<25;x++)
    for(y=0;y<16;y++)
      FFARR[x][y]=d[x][y];
}

void obnovi(void)
{
  form_dial(FMD_START,Wx,Wy,Ww,Wh,Wx,Wy,Ww,Wh);
  form_dial(FMD_FINISH,Wx,Wy,Ww,Wh,Wx,Wy,Ww,Wh);
}

void tacka(int x,int y)
{
  int p[4];
  p[0]=(x+1)*8+X0+161;
  p[1]=(y+1)*8+Y0+1;
  p[2]=p[0]+6;
  p[3]=p[1]+6;
  vsf_interior(Handle,(FFARR[Sel][y]&(0x8000>>x))?FIS_SOLID:FIS_HOLLOW);
  vr_recfl(Handle,p);
}

void postavi_sve_tacke(void)
{
  int x,y;
  for(x=0;x<16;x++)
    for(y=0;y<16;y++)
      tacka(y,x);
}

void oblik(int n)
{
  int p[4];
  p[0]=X0+32*(n%5);
  p[1]=Y0+32*(n/5);
  p[2]=p[0]+15;
  p[3]=p[1]+15;
  vsf_interior(Handle,FIS_USER);
  vsf_udpat(Handle,(int *)FFARR[n],1);
  vr_recfl(Handle,p);
}

void prikazi(int flag,int x,int y)
{
  int p[4],fx,fy,fw,fh;
  wind_update(BEG_UPDATE);
  wind_get(WHandle,WF_FIRSTXYWH,&fx,&fy,&fw,&fh);
  while(fw&&fh)
  {
    p[0]=fx;
    p[1]=fy;
    p[2]=fx+fw-1;
    p[3]=fy+fh-1;
    if(p[0]<=p[2]&&p[1]<=p[3])
    {
      vs_clip(Handle,1,p);
      graf_mouse(M_OFF,(void *)0l);
      if(flag)
        tacka(x,y);
      else
        postavi_sve_tacke();
      oblik(Sel);
      graf_mouse(M_ON,(void *)0l);
      vs_clip(Handle,0,p);
    }
    wind_get(WHandle,WF_NEXTXYWH,&fx,&fy,&fw,&fh);
  }
  wind_update(END_UPDATE);
}

void clr(void)
{
  int i;
  for(i=0;i<16;i++)
    FFARR[Sel][i]=0u;
  prikazi(0,0,0);
}

void inv(void)
{
  int i;
  for(i=0;i<16;i++)
    FFARR[Sel][i]=~FFARR[Sel][i];
  prikazi(0,0,0);
}

void sri(void)
{
  int i;
  for(i=0;i<16;i++)
    FFARR[Sel][i]=(FFARR[Sel][i]>>1)|(FFARR[Sel][i]<<15);
  prikazi(0,0,0);
}

void sle(void)
{
  int i;
  for(i=0;i<16;i++)
    FFARR[Sel][i]=(FFARR[Sel][i]<<1)|(FFARR[Sel][i]>>15);
  prikazi(0,0,0);
}

void sup(void)
{
  int i;
  unsigned int pom;
  pom=FFARR[Sel][0];
  for(i=0;i<15;i++)
    FFARR[Sel][i]=FFARR[Sel][i+1];
  FFARR[Sel][15]=pom;
  prikazi(0,0,0);
}

void sdo(void)
{
  int i;
  unsigned int pom;
  pom=FFARR[Sel][15];
  for(i=15;i>0;i--)
    FFARR[Sel][i]=FFARR[Sel][i-1];
  FFARR[Sel][0]=pom;
  prikazi(0,0,0);
}

void mrx(void)
{
  int i;
  unsigned int pom;
  for(i=0;i<8;i++)
  {
    pom=FFARR[Sel][i];
    FFARR[Sel][i]=FFARR[Sel][15-i];
    FFARR[Sel][15-i]=pom;
  }
  prikazi(0,0,0);
}

void mry(void)
{
  int i,j;
  unsigned int pom;
  for(i=0;i<16;i++)
  {
    pom=FFARR[Sel][i];
    FFARR[Sel][i]=0u;
    for(j=0;j<8;j++)
    {
      FFARR[Sel][i]|=(pom&(0x8000>>j))>>(15-2*j);
      FFARR[Sel][i]|=(pom&(0x0001<<j))<<(15-2*j);
    }
  }
  prikazi(0,0,0);
}

void zaokruzi(void)
{
  int p[10];
  p[0]=X0+32*(Sel%5)-6;
  p[1]=Y0+32*(Sel/5)-6;
  p[2]=p[0]+27;
  p[3]=p[1];
  p[4]=p[0]+27;
  p[5]=p[1]+27;
  p[6]=p[0];
  p[7]=p[1]+27;
  p[8]=p[0];
  p[9]=p[1];
  v_pline(Handle,5,p);
  p[0]+=1;
  p[1]+=1;
  p[2]-=1;
  p[3]+=1;
  p[4]-=1;
  p[5]-=1;
  p[6]+=1;
  p[7]-=1;
  p[8]+=1;
  p[9]+=1;
  v_pline(Handle,5,p);
}

int main(void)
{
  int work_in[11]={0,SOLID,1,0,0,0,0,FIS_USER,0,1,2},work_out[57],msg[8],flag=1,fhand,fx,fy,fw,fh,x,y,key,trash;
  OBJECT *drvo1,*drvo2;
  appl_init();
  Handle=graf_handle(&trash,&trash,&trash,&trash);
  v_opnvwk(work_in,&Handle,work_out);
  vswr_mode(Handle,MD_REPLACE);
  vsf_perimeter(Handle,1);
  if(Getrez()!=2)
    form_alert(1,"[3][|  Only high resolution ! ][  OK  ]");
  else
    if(!rsrc_load("m_s_edit.rsc"))
      form_alert(1,"[3][|  Not find  .RSC file ! ][  OK  ]");
    else
    {
      rsrc_gaddr(R_TREE,TREE1,&drvo1);
      rsrc_gaddr(R_TREE,TREE2,&drvo2);
      if((fhand=Fopen("mine_swe.spr",FO_READ))>0)
      {
        Fread(fhand,800l,FFARR);
        Fclose(fhand);
        drvo1[LOAD].ob_state=NORMAL;
      }
      else
        standard_ff();
      graf_mouse(ARROW,(void *)0l);
      graf_mouse(M_OFF,(void *)0l);
      menu_bar(drvo1,1);
      graf_mouse(M_ON,(void *)0l);
      WHandle=wind_create(NAME|MOVER,0,0,0,0);
      wind_calc(WC_BORDER,NAME|MOVER,X0-14,Y0-14,333,173,&Wx,&Wy,&Ww,&Wh);
      wind_set(WHandle,WF_NAME," Sprite editor for Mine sweeper ");
      wind_open(WHandle,Wx,Wy,Ww,Wh);
      wind_get(WHandle,WF_WORKXYWH,&Wx,&Wy,&Ww,&Wh);
      do
        switch(evnt_multi(MU_MESAG|MU_BUTTON|MU_KEYBD,1,1,1,0,0,0,0,0,0,0,0,0,0,msg,0,0,&x,&y,&trash,&trash,&key,&trash))
        {
          case MU_KEYBD:
          case MU_KEYBD|MU_BUTTON:
            switch(key)
            {
              case 0x4700:
                clr();
                break;
              case 0x5200:
                inv();
                break;
              case 0x4d00:
                sri();
                break;
              case 0x4b00:
                sle();
                break;
              case 0x4800:
                sup();
                break;
              case 0x5000:
                sdo();
                break;
              case 0x6200:
                mrx();
                break;
              case 0x6100:
                mry();
            }
            break;
          case MU_BUTTON:
            if(x>=Wx&&y>=Wy&&x<=(Wx+Ww)&&y<=(Wy+Wh))
            {
              x-=X0;
              y-=Y0;
              x/=(x<0)?1:8;
              y/=(y<0)?1:8;
              if(x>=21&&x<=36&&y>=1&&y<=16)
              {
                unsigned int pom;
                int bit,izlaz;
                x-=21;
                y-=1;
                pom=0x8000>>x;
                FFARR[Sel][y]=FFARR[Sel][y]^pom;
                bit=FFARR[Sel][y]&pom;
                prikazi(1,x,y);
                izlaz=1;
                do
                {
                  fx=X0+x*8+168;
                  fy=Y0+y*8+8;
                  switch(evnt_multi(MU_M1|MU_BUTTON,1,1,0,1,fx,fy,8,8,0,0,0,0,0,(void *)0l,0,0,&x,&y,&trash,&trash,&trash,&trash))
                  {
                    case MU_BUTTON:
                    case MU_BUTTON|MU_M1:
                      izlaz=0;
                      break;
                    case MU_M1:
                      x-=X0;
                      y-=Y0;
                      x/=(x<0)?1:8;
                      y/=(y<0)?1:8;
                      if(x>=21&&x<=36&&y>=1&&y<=16)
                      {
                        x-=21;
                        y-=1;
                        pom=0x8000>>x;
                        FFARR[Sel][y]=bit?FFARR[Sel][y]|pom:FFARR[Sel][y]&~pom;
                        prikazi(1,x,y);
                      }
                      else
                        Cconout('\a');
                  }
                }
                while(izlaz);
              }
              else
                if(x>=0&&x<=17&&y>=0&&y<=17&&(x%4)<2&&(y%4)<2)
                {
                  wind_update(BEG_UPDATE);
                  wind_get(WHandle,WF_FIRSTXYWH,&fx,&fy,&fw,&fh);
                  while(fw&&fh)
                  {
                    int p[4];
                    p[0]=fx;
                    p[1]=fy;
                    p[2]=fx+fw-1;
                    p[3]=fy+fh-1;
                    if(p[0]<=p[2]&&p[1]<=p[3])
                    {
                      vs_clip(Handle,1,p);
                      graf_mouse(M_OFF,(void *)0l);
                      vsl_color(Handle,0);
                      zaokruzi();
                      Sel=(y/4)*5+(x/4);
                      vsl_color(Handle,1);
                      zaokruzi();
                      postavi_sve_tacke();
                      graf_mouse(M_ON,(void *)0l);
                      vs_clip(Handle,0,p);
                    }
                    wind_get(WHandle,WF_NEXTXYWH,&fx,&fy,&fw,&fh);
                  }
                  wind_update(END_UPDATE);
                  evnt_button(1,1,0,&trash,&trash,&trash,&trash);
                }
                else
                {
                  Cconout('\a');
                  evnt_button(1,1,0,&trash,&trash,&trash,&trash);
                }
            }
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
                  case ABOUT:
                    form_center(drvo2,&fx,&fy,&fw,&fh);
                    wind_update(BEG_UPDATE);
                    form_dial(FMD_START,fx,fy,fw,fh,fx,fy,fw,fh);
                    objc_draw(drvo2,0,1,fx,fy,fw,fh);
                    form_do(drvo2,0);
                    form_dial(FMD_FINISH,fx,fy,fw,fh,fx,fy,fw,fh);
                    wind_update(END_UPDATE);
                    drvo2[ACONT].ob_state=NORMAL;
                    break;
                  case LOAD:
                    if(form_alert(2,"[2][|  Are you sure ?][  LOAD  | CANCEL ]")==1)
                    {
                      graf_mouse(BUSYBEE,(void *)0l);
                      if((fhand=Fopen("mine_swe.spr",FO_READ))>0)
                      {
                        Fread(fhand,800l,FFARR);
                        Fclose(fhand);
                      }
                      graf_mouse(ARROW,(void *)0l);
                      Sel=0;
                      obnovi();
                    }
                    break;
                  case STANDARD:
                    if(form_alert(2,"[2][|  Are you sure ?][STANDARD| CANCEL ]")==1)
                    {
                      standard_ff();
                      Sel=0;
                      obnovi();
                    }
                    break;
                  case SAVE:
                    if(form_alert(2,"[2][|  Are you sure ?][  SAVE  | CANCEL ]")==1)
                    {
                      graf_mouse(BUSYBEE,(void *)0l);
                      if((fhand=Fcreate("mine_swe.spr",FA_ARCHIVE))>0)
                      {
                        Fwrite(fhand,800l,FFARR);
                        Fclose(fhand);
                      }
                      drvo1[LOAD].ob_state=NORMAL;
                      graf_mouse(ARROW,(void *)0l);
                    }
                    break;
                  case QUIT:
                    if(form_alert(2,"[2][|  Are you sure ?][  QUIT  | CANCEL ]")==1)
                      flag=0;
                    break;
                  case CLEAR:
                    clr();
                    break;
                  case INVERT:
                    inv();
                    break;
                  case SHIRIGHT:
                    sri();
                    break;
                  case SHILEFT:
                    sle();
                    break;
                  case SHIUP:
                    sup();
                    break;
                  case SHIDOWN:
                    sdo();
                    break;
                  case MIRX:
                    mrx();
                    break;
                  case MIRY:
                    mry();
                }
                evnt_button(1,1,0,&trash,&trash,&trash,&trash);
                menu_tnormal(drvo1,msg[3],1);
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
                    int p[4];
                    vs_clip(Handle,1,q);
                    graf_mouse(M_OFF,(void *)0l);
                    p[0]=X0-14;
                    p[1]=Y0-14;
                    p[2]=p[0]+332;
                    p[3]=p[1]+172;
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
                    for(trash=0;trash<25;trash++)
                      oblik(trash);
                    zaokruzi();
                    p[0]=X0+164;
                    p[1]=Y0+4;
                    p[2]=p[0]+136;
                    p[3]=p[1]+136;
                    vsf_interior(Handle,FIS_HOLLOW);
                    v_bar(Handle,p);
                    p[0]+=2;
                    p[1]+=2;
                    p[2]-=2;
                    p[3]-=2;
                    v_bar(Handle,p);
                    p[0]+=2;
                    p[1]+=2;
                    p[2]-=2;
                    p[3]-=2;
                    vsf_interior(Handle,FIS_USER);
                    vsf_udpat(Handle,(int *)EFF,1);
                    vr_recfl(Handle,p);
                    postavi_sve_tacke();
                    graf_mouse(M_ON,(void *)0l);
                    vs_clip(Handle,0,q);
                  }
                  wind_get(msg[3],WF_NEXTXYWH,&fx,&fy,&fw,&fh);
                }
                wind_update(END_UPDATE);
                break;
              case WM_TOPPED:
                wind_set(msg[3],WF_TOP);
                break;
              case WM_MOVED:
                wind_calc(WC_WORK,NAME|MOVER,msg[4],msg[5],msg[6],msg[7],&fx,&fy,&fw,&fh);
                X0=(fx+14)/16;
                Y0=(fy+14)/16;
                X0=(X0<2)?16:X0*16;
                Y0=(Y0<4)?64:Y0*16;
                fx=X0-14;
                fy=Y0-14;
                wind_calc(WC_BORDER,NAME|MOVER,fx,fy,fw,fh,&Wx,&Wy,&Ww,&Wh);
                wind_set(msg[3],WF_CURRXYWH,Wx,Wy,Ww,Wh);
                wind_get(msg[3],WF_WORKXYWH,&Wx,&Wy,&Ww,&Wh);
            }
        }
      while(flag);
      wind_close(WHandle);
      wind_delete(WHandle);
      rsrc_free();
    }
  v_clsvwk(Handle);
  appl_exit();
  return 0;
}
