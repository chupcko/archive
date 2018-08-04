#include <owl/applicat.h>
#include <owl/dc.h>
#include <owl/dialog.h>
#include <owl/mdi.h>
#include <owl/owlpch.h>
#include <stdio.h>
#include <stdlib.h>
#include "g2d.rc"

#define MAX_BROJ_TACAKA 256
#define VELICINA_NIZA 32766

class MojDijalog:public TDialog
{
  public:
    MojDijalog(TWindow *tata,int *a):TWindow(tata),TDialog(tata,"Dijalog")
    {
      broj=a;
    }
    bool CanClose(void);
    void SetupWindow(void)
    {
      TDialog::SetupWindow();
      ::SetScrollRange(GetDlgItem(RC_f_scroll),SB_CTL,3,100,false);
      SetDlgItemInt(RC_f_broj,*broj,false);
    };
    void EvHScroll(uint,uint,HWND);
    void CmPromena(void)
    {
      ::SetScrollPos(GetDlgItem(RC_f_scroll),SB_CTL,GetDlgItemInt(RC_f_broj),true);
    };
  protected:
    int *broj;
  DECLARE_RESPONSE_TABLE(MojDijalog);
};

DEFINE_RESPONSE_TABLE1(MojDijalog,TDialog)
  EV_WM_HSCROLL,
  EV_EN_CHANGE(RC_f_broj,CmPromena),
END_RESPONSE_TABLE;

bool MojDijalog::CanClose(void)
{
  bool nema_greske;
  int b=GetDlgItemInt(RC_f_broj,&nema_greske,false);
  if(nema_greske&&b>=3&&b<=100)
  {
    *broj=b;
    return true;
  }
  else
  {
    MessageBox("Frekfencija mora biti\nbroj izmedju 3 i 100 !","Greska",MB_OK);
    return false;
  }
}

void MojDijalog::EvHScroll(uint kod,uint s_pos,HWND prozor)
{
  uint pos=::GetScrollPos(prozor,SB_CTL);
  switch(kod)
  {
    case SB_LINEUP:
      if(pos>3)
        pos--;
      break;
    case SB_LINEDOWN:
      if(pos<100)
        pos++;
      break;
    case SB_PAGEUP:
      if(pos>13)
        pos-=10;
      else
        pos=3;
      break;
    case SB_PAGEDOWN:
      if(pos<90)
        pos+=10;
      else
        pos=100;
      break;
    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
      pos=s_pos;
      break;
  }
  SetDlgItemInt(RC_f_broj,pos,false);
}

class MojProzor:public TMDIClient
{
  public:
    MojProzor(TTextGadget *tg):TMDIClient()
    {
      TextGadget=tg;
      Maxx=TScreenDC().GetDeviceCaps(HORZRES);
      Maxy=TScreenDC().GetDeviceCaps(VERTRES);
      Dib=new TDib(Maxx,Maxy,256);
      Dibdc=new TDibDC(*Dib);
      Dibdc->FillRect(0,0,Maxx,Maxy,TBrush(TColor::White));
      Boja=TColor::Black;
      Sta_crtam=LINIJA;
      Crtam_pomoc=false;
      Resetka=false;
      Frekfencija=10;
      SetCursor(GetModule(),"Kurzor");
    };
    ~MojProzor(void)
    {
      delete Dibdc;
      delete Dib;
      delete Dc;
    };
  protected:
    TTextGadget *TextGadget;
    TDib *Dib;
    TDC *Dibdc;
    TDC *Dc;
    TColor Boja;
    int Maxx;
    int Maxy;
    void tacka(int x,int y)
    {
      if(Crtam_pomoc)
        Dc->SetPixel(x,y,Boja);
      else
        Dibdc->SetPixel(x,y,Boja);
    };
    void h_linija(int,int,int);
    void linija(int,int,int,int);
    void o_krug(int,int,int);
    void p_krug(int,int,int);
    void o_elipsa(int,int,int,int);
    void p_elipsa(int,int,int,int);
    long int Ax;
    long int Ay;
    long int Bx;
    long int By;
    long int Cx;
    long int Cy;
    long int Dx;
    long int Dy;
    int Nn;
    void beiser_r(void);
    void beiser(int ax,int ay,int bx,int by,int cx,int cy,int dx,int dy)
    {
      Ax=(long int)ax<<18;
      Ay=(long int)ay<<18;
      Bx=(long int)bx<<18;
      By=(long int)by<<18;
      Cx=(long int)cx<<18;
      Cy=(long int)cy<<18;
      Dx=(long int)dx<<18;
      Dy=(long int)dy<<18;
      Nn=6;
      beiser_r();
    };
    void fil(int,int);
    void poligon(int*,int*,int);
    void SetupWindow(void)
    {
      Dc=new TClientDC(*this);
    }
    bool CanClose(void);
    bool Crtam_pomoc;
    int Mx[MAX_BROJ_TACAKA];
    int My[MAX_BROJ_TACAKA];
    int Mb;
    enum
    {
      LINIJA,
      O_KRUG,
      P_KRUG,
      O_ELIPSA,
      P_ELIPSA,
      BEISER,
      O_POLIGON,
      P_POLIGON,
      FIL
    } Sta_crtam;
    bool Resetka;
    int Frekfencija;
    void EvLButtonDown(uint,TPoint&);
    void EvMouseMove(uint,TPoint&);
    void EvRButtonDown(uint,TPoint&);
    void Paint(TDC&,bool,TRect&);
    void Cm_novi(void)
    {
      if(!Crtam_pomoc)
      {
        Dibdc->FillRect(0,0,Maxx,Maxy,TBrush(TColor::White));
        Invalidate(false);
      }
    };
    void Cm_linija(void)
    {
      if(!Crtam_pomoc)
        Sta_crtam=LINIJA;
    };
    void Cm_o_krug(void)
    {
      if(!Crtam_pomoc)
        Sta_crtam=O_KRUG;
    };
    void Cm_p_krug(void)
    {
      if(!Crtam_pomoc)
        Sta_crtam=P_KRUG;
    };
    void Cm_o_elipsa(void)
    {
      if(!Crtam_pomoc)
        Sta_crtam=O_ELIPSA;
    };
    void Cm_p_elipsa(void)
    {
      if(!Crtam_pomoc)
        Sta_crtam=P_ELIPSA;
    };
    void Cm_beiser(void)
    {
      if(!Crtam_pomoc)
        Sta_crtam=BEISER;
    };
    void Cm_o_poligon(void)
    {
      if(!Crtam_pomoc)
        Sta_crtam=O_POLIGON;
    };
    void Cm_p_poligon(void)
    {
      if(!Crtam_pomoc)
        Sta_crtam=P_POLIGON;
    };
    void Cm_fil(void)
    {
      if(!Crtam_pomoc)
        Sta_crtam=FIL;
    };
    void Cm_resetka(void)
    {
      if(!Crtam_pomoc)
      {
        Resetka=!Resetka;
        Invalidate(false);
      }
    };
    void Cm_frekfencija(void)
    {
      if(!Crtam_pomoc)
      {
        MojDijalog(this,&Frekfencija).Execute();
        Invalidate(false);
      }
    };
    void Cm_boja(void);
    void Ce_linija(TCommandEnabler &ce)
    {
      ce.SetCheck(Sta_crtam==LINIJA?TCommandEnabler::Checked:TCommandEnabler::Unchecked);
    };
    void Ce_o_krug(TCommandEnabler &ce)
    {
      ce.SetCheck(Sta_crtam==O_KRUG?TCommandEnabler::Checked:TCommandEnabler::Unchecked);
    };
    void Ce_p_krug(TCommandEnabler &ce)
    {
      ce.SetCheck(Sta_crtam==P_KRUG?TCommandEnabler::Checked:TCommandEnabler::Unchecked);
    };
    void Ce_o_elipsa(TCommandEnabler &ce)
    {
      ce.SetCheck(Sta_crtam==O_ELIPSA?TCommandEnabler::Checked:TCommandEnabler::Unchecked);
    };
    void Ce_p_elipsa(TCommandEnabler &ce)
    {
      ce.SetCheck(Sta_crtam==P_ELIPSA?TCommandEnabler::Checked:TCommandEnabler::Unchecked);
    };
    void Ce_beiser(TCommandEnabler &ce)
    {
      ce.SetCheck(Sta_crtam==BEISER?TCommandEnabler::Checked:TCommandEnabler::Unchecked);
    };
    void Ce_o_poligon(TCommandEnabler &ce)
    {
      ce.SetCheck(Sta_crtam==O_POLIGON?TCommandEnabler::Checked:TCommandEnabler::Unchecked);
    };
    void Ce_p_poligon(TCommandEnabler &ce)
    {
      ce.SetCheck(Sta_crtam==P_POLIGON?TCommandEnabler::Checked:TCommandEnabler::Unchecked);
    };
    void Ce_fil(TCommandEnabler &ce)
    {
      ce.SetCheck(Sta_crtam==FIL?TCommandEnabler::Checked:TCommandEnabler::Unchecked);
    };
    void Ce_resetka(TCommandEnabler &ce)
    {
      ce.SetCheck(Resetka?TCommandEnabler::Checked:TCommandEnabler::Unchecked);
    };
    void Ce_frekfencija(TCommandEnabler &ce)
    {
      ce.Enable(Resetka);
    };

  DECLARE_RESPONSE_TABLE(MojProzor);
};

DEFINE_RESPONSE_TABLE1(MojProzor,TWindow)
  EV_WM_LBUTTONDOWN,
  EV_WM_MOUSEMOVE,
  EV_WM_RBUTTONDOWN,
  EV_COMMAND(RC_novi,Cm_novi),
  EV_COMMAND(RC_linija,Cm_linija),
  EV_COMMAND(RC_o_krug,Cm_o_krug),
  EV_COMMAND(RC_p_krug,Cm_p_krug),
  EV_COMMAND(RC_o_elipsa,Cm_o_elipsa),
  EV_COMMAND(RC_p_elipsa,Cm_p_elipsa),
  EV_COMMAND(RC_beiser,Cm_beiser),
  EV_COMMAND(RC_o_poligon,Cm_o_poligon),
  EV_COMMAND(RC_p_poligon,Cm_p_poligon),
  EV_COMMAND(RC_fil,Cm_fil),
  EV_COMMAND(RC_resetka,Cm_resetka),
  EV_COMMAND(RC_frekfencija,Cm_frekfencija),
  EV_COMMAND(RC_boja,Cm_boja),
  EV_COMMAND_ENABLE(RC_linija,Ce_linija),
  EV_COMMAND_ENABLE(RC_o_krug,Ce_o_krug),
  EV_COMMAND_ENABLE(RC_p_krug,Ce_p_krug),
  EV_COMMAND_ENABLE(RC_o_elipsa,Ce_o_elipsa),
  EV_COMMAND_ENABLE(RC_p_elipsa,Ce_p_elipsa),
  EV_COMMAND_ENABLE(RC_beiser,Ce_beiser),
  EV_COMMAND_ENABLE(RC_o_poligon,Ce_o_poligon),
  EV_COMMAND_ENABLE(RC_p_poligon,Ce_p_poligon),
  EV_COMMAND_ENABLE(RC_fil,Ce_fil),
  EV_COMMAND_ENABLE(RC_resetka,Ce_resetka),
  EV_COMMAND_ENABLE(RC_frekfencija,Ce_frekfencija),
END_RESPONSE_TABLE;

void MojProzor::h_linija(int xl,int xr,int y)
{
  for(int i=xl;i<=xr;i++)
  {
    Dibdc->SetPixel(i,y,Boja);
    Dc->SetPixel(i,y,Boja);
  }
};

inline int sign(int x)
{
  return x<0?-1:(x?1:0);
}

void MojProzor::linija(int x1,int y1,int x2,int y2)
{
  int dx=abs(x2-x1);
  int dy=abs(y2-y1);
  int s1=sign(x2-x1);
  int s2=sign(y2-y1);
  int ic;
  if(dy>dx)
  {
    int t=dx;
    dx=dy;
    dy=t;
    ic=1;
  }
  else
    ic=0;
  int e=(dy<<1)-dx;
  for(int i=1;i<=dx;i++)
  {
    tacka(x1,y1);
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
  tacka(x1,y1);
}

void MojProzor::o_krug(int xo,int yo,int r)
{
  int p;
  int x=0;
  int y=r;
  int x2=0;
  int y2=r<<1;
  int c=(1-r)<<1;
  while(y>0)
  {
    tacka(xo+x,yo+y);
    tacka(xo+x,yo-y);
    if(x)
    {
      tacka(xo-x,yo+y);
      tacka(xo-x,yo-y);
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
  tacka(xo+x,yo);
  tacka(xo-x,yo);
}

void MojProzor::p_krug(int xo,int yo,int r)
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
      h_linija(xo-xm,xo+xm,yo-y);
      h_linija(xo-xm,xo+xm,yo+y);
      xm=x;
      y--;
      y2-=2;
      c+=1-y2;
    }
  }
  h_linija(xo-x,xo+x,yo);
}

void MojProzor::o_elipsa(int xo,int yo,int a,int b)
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
    tacka(xo+x,yo+y);
    tacka(xo+x,yo-y);
    if(x)
    {
      tacka(xo-x,yo+y);
      tacka(xo-x,yo-y);
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
  tacka(xo+x,yo);
  tacka(xo-x,yo);
}

void MojProzor::p_elipsa(int xo,int yo,int a,int b)
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
      h_linija(xo-xm,xo+xm,yo-y);
      h_linija(xo-xm,xo+xm,yo+y);
      xm=x;
      y--;
      yaa2-=aa2;
      c+=aa-yaa2;
    }
  }
  h_linija(xo-x,xo+x,yo);
}

void MojProzor::beiser_r(void)
{
  if(Nn)
  {
    Nn--;
    Dx=(Dx+Cx)>>1;
    Dy=(Dy+Cy)>>1;
    Cx=(Cx+Bx)>>1;
    Cy=(Cy+By)>>1;
    Bx=(Bx+Ax)>>1;
    By=(By+Ay)>>1;
    Dx=(Dx+Cx)>>1;
    Dy=(Dy+Cy)>>1;
    Cx=(Cx+Bx)>>1;
    Cy=(Cy+By)>>1;
    Dx=(Dx+Cx)>>1;
    Dy=(Dy+Cy)>>1;
    beiser_r();
    Dx=(Dx<<1)-Cx;
    Dy=(Dy<<1)-Cy;
    Cx=(Cx<<1)-Bx;
    Cy=(Cy<<1)-By;
    Dx=(Dx<<1)-Cx;
    Dy=(Dy<<1)-Cy;
    Bx=(Bx<<1)-Ax;
    By=(By<<1)-Ay;
    Cx=(Cx<<1)-Bx;
    Cy=(Cy<<1)-By;
    Dx=(Dx<<1)-Cx;
    Dy=(Dy<<1)-Cy;
    Ax=(Ax+Bx)>>1;
    Ay=(Ay+By)>>1;
    Bx=(Bx+Cx)>>1;
    By=(By+Cy)>>1;
    Cx=(Cx+Dx)>>1;
    Cy=(Cy+Dy)>>1;
    Ax=(Ax+Bx)>>1;
    Ay=(Ay+By)>>1;
    Bx=(Bx+Cx)>>1;
    By=(By+Cy)>>1;
    Ax=(Ax+Bx)>>1;
    Ay=(Ay+By)>>1;
    beiser_r();
    Ax=(Ax<<1)-Bx;
    Ay=(Ay<<1)-By;
    Bx=(Bx<<1)-Cx;
    By=(By<<1)-Cy;
    Ax=(Ax<<1)-Bx;
    Ay=(Ay<<1)-By;
    Cx=(Cx<<1)-Dx;
    Cy=(Cy<<1)-Dy;
    Bx=(Bx<<1)-Cx;
    By=(By<<1)-Cy;
    Ax=(Ax<<1)-Bx;
    Ay=(Ay<<1)-By;
    Nn++;
  }
  else
    linija(((int)(Ax>>17)+1)>>1,((int)(Ay>>17)+1)>>1,((int)(Dx>>17)+1)>>1,((int)(Dy>>17)+1)>>1);
}

void MojProzor::poligon(int *xu,int *yu,int bu)
{
  int *xl=new int[VELICINA_NIZA];
  int *xr=new int[VELICINA_NIZA];
  int *yn=new int[VELICINA_NIZA];
  int bn=0;
  for(int i=0;i<bu;i++)
  {
    int y1=yu[i];
    int y2=yu[(i+1)%bu];
    if(y1!=y2)
    {
      int x1=xu[i];
      int x2=xu[(i+1)%bu];
      if(y1>y2)
      {
        int t=x1;
        x1=x2;
        x2=t;
        t=y1;
        y1=y2;
        y2=t;
      }
      int yp=y1+1;
      int dx=abs(x2-x1);
      int dy=y2-y1;
      int s=sign(x2-x1);
      int ic;
      if(dy>dx)
      {
        int t=dx;
        dx=dy;
        dy=t;
        ic=1;
      }
      else
        ic=0;
      int e=(dy<<1)-dx;
      for(int i=1;i<=dx;i++)
      {
        if(y1==y2)
          tacka(x1,y1);
        else
          if(yp==y1)
          {
            if(x1<xl[bn-1])
              xl[bn-1]=x1;
            if(x1>xr[bn-1])
              xr[bn-1]=x1;
          }
          else
          {
            if(bn==VELICINA_NIZA)
            {
              MessageBox("Prevelika ivica poligona !","Fatalna greska",MB_OK);
              exit(1);
            }
            xl[bn]=x1;
            xr[bn]=x1;
            yn[bn++]=y1;
            yp=y1;
          }
        if(e>0)
        {
          if(ic)
            x1+=s;
          else
            y1++;
          e-=dx<<1;
        }
        if(ic)
          y1++;
        else
          x1+=s;
        e+=dy<<1;
      }
      tacka(x1,y1);
    }
  }
  for(i=0;i<bn-1;i++)
    for(int j=i+1;j<bn;j++)
      if(yn[i]>yn[j]||(yn[i]==yn[j]&&xl[i]>xr[j]))
      {
        int t=xl[i];
        xl[i]=xl[j];
        xl[j]=t;
        t=xr[i];
        xr[i]=xr[j];
        xr[j]=t;
        t=yn[i];
        yn[i]=yn[j];
        yn[j]=t;
      }
  for(i=0;i<bn-1;i+=2)
    h_linija(xl[i],xr[i+1],yn[i]);
  delete yn;
  delete xr;
  delete xl;
}

class stack
{
  public:
    stack(TWindow *t)
    {
      tata=t;
      st=new int[VELICINA_NIZA];
      vrh=0;
    };
    ~stack(void)
    {
      delete st;
    };
    bool not_empty(void)
    {
      return vrh;
    };
    int pop(void)
    {
      return st[--vrh];
    };
    void push(int c);
  protected:
    TWindow *tata;
    int *st;
    int vrh;
};

void stack::push(int c)
{
  if(vrh==VELICINA_NIZA)
  {
    tata->MessageBox("Preopterecenje steka !","Fatalna greska",MB_OK);
    exit(1);
  }
  st[vrh++]=c;
}

void MojProzor::fil(int x,int y)
{
  TColor sb=Dibdc->GetPixel(x,y);
  stack st(this);
  Dibdc->SetPixel(x,y,Boja);
  if(!(sb==Dibdc->GetPixel(x,y)))
  {
    st.push(x);
    st.push(y);
    while(st.not_empty())
    {
      y=st.pop();
      x=st.pop();
      int xl=x-1;
      while(xl>=0&&sb==Dibdc->GetPixel(xl,y))
        xl--;
      xl++;
      int xr=x+1;
      while(xr<=Maxx&&sb==Dibdc->GetPixel(xr,y))
        xr++;
      xr--;
      h_linija(xl,xr,y);
      y++;
      for(int i=0;i<2;i++,y-=2)
        if(y>=0&&y<=Maxy)
        {
          x=xl;
          while(x<=xr)
          {
            bool flag=false;
            while(x<=xr&&sb==Dibdc->GetPixel(x,y))
            {
              flag=true;
              x++;
            }
            if(flag)
            {
              st.push(x-1);
              st.push(y);
            }
            do
              x++;
            while(x<=xr&&!(sb==Dibdc->GetPixel(x,y)));
          }
        }
    }
  }
}

bool MojProzor::CanClose(void)
{
  return MessageBox("Stvarno izlazis ?","Izlazak",MB_YESNO|MB_ICONQUESTION)==IDYES;
}

void MojProzor::EvLButtonDown(uint,TPoint &p)
{
  if(Resetka&&Sta_crtam!=FIL)
  {
    p.x=((p.x+(Frekfencija>>1))/Frekfencija)*Frekfencija;
    p.y=((p.y+(Frekfencija>>1))/Frekfencija)*Frekfencija;
  }
  switch(Sta_crtam)
  {
    case LINIJA:
      if(Crtam_pomoc)
      {
        linija(Mx[0],My[0],Mx[1],My[1]);
        Mx[1]=p.x;
        My[1]=p.y;
        Crtam_pomoc=false;
        linija(Mx[0],My[0],Mx[1],My[1]);
        Invalidate(false);
      }
      else
      {
        Dc->SetROP2(R2_NOT);
        Crtam_pomoc=true;
        Mx[0]=p.x;
        My[0]=p.y;
        Mx[1]=p.x;
        My[1]=p.y;
        linija(Mx[0],My[0],Mx[1],My[1]);
      }
      break;
    case O_KRUG:
    case P_KRUG:
      if(Crtam_pomoc)
      {
        o_krug(Mx[0],My[0],Mx[1]);
        Mx[1]=max(abs(Mx[0]-p.x),abs(My[0]-p.y));
        if(Sta_crtam==O_KRUG)
          Crtam_pomoc=false;
        o_krug(Mx[0],My[0],Mx[1]);
        if(Sta_crtam==P_KRUG)
        {
          Crtam_pomoc=false;
          SetCursor(0,IDC_WAIT);
          p_krug(Mx[0],My[0],Mx[1]);
          SetCursor(GetModule(),"Kurzor");
        }
        Invalidate(false);
      }
      else
      {
        Dc->SetROP2(R2_NOT);
        Crtam_pomoc=true;
        Mx[0]=p.x;
        My[0]=p.y;
        Mx[1]=0;
        o_krug(Mx[0],My[0],Mx[1]);
      }
      break;
    case O_ELIPSA:
    case P_ELIPSA:
      if(Crtam_pomoc)
      {
        o_elipsa(Mx[0],My[0],Mx[1],My[1]);
        Mx[1]=abs(Mx[0]-p.x);
        My[1]=abs(My[0]-p.y);
        if(Sta_crtam==O_ELIPSA)
          Crtam_pomoc=false;
        o_elipsa(Mx[0],My[0],Mx[1],My[1]);
        if(Sta_crtam==P_ELIPSA)
        {
          Crtam_pomoc=false;
          SetCursor(0,IDC_WAIT);
          p_elipsa(Mx[0],My[0],Mx[1],My[1]);
          SetCursor(GetModule(),"Kurzor");
        }
        Invalidate(false);
      }
      else
      {
        Dc->SetROP2(R2_NOT);
        Crtam_pomoc=true;
        Mx[0]=p.x;
        My[0]=p.y;
        Mx[1]=0;
        My[1]=0;
        o_elipsa(Mx[0],My[0],Mx[1],My[1]);
      }
      break;
    case BEISER:
      if(Crtam_pomoc)
      {
        if(Mb>1)
          linija(Mx[Mb],My[Mb],Mx[Mb-2],My[Mb-2]);
        beiser(Mx[0],My[0],Mx[2],My[2],Mx[3],My[3],Mx[1],My[1]);
        Mx[Mb]=p.x;
        My[Mb++]=p.y;
        if(Mb==4)
          Crtam_pomoc=false;
        else
        {
          Mx[Mb]=p.x;
          My[Mb]=p.y;
          linija(Mx[Mb],My[Mb],Mx[Mb-2],My[Mb-2]);
        }
        beiser(Mx[0],My[0],Mx[2],My[2],Mx[3],My[3],Mx[1],My[1]);
        if(Mb==4)
          Invalidate(false);
      }
      else
      {
        Dc->SetROP2(R2_NOT);
        Crtam_pomoc=true;
        for(int i=0;i<4;i++)
        {
          Mx[i]=p.x;
          My[i]=p.y;
        }
        Mb=1;
        beiser(Mx[0],My[0],Mx[2],My[2],Mx[3],My[3],Mx[1],My[1]);
      }
      break;
    case O_POLIGON:
    case P_POLIGON:
      if(Crtam_pomoc)
      {
        if(Mb>1)
          linija(Mx[0],My[0],Mx[Mb],My[Mb]);
        linija(Mx[Mb-1],My[Mb-1],Mx[Mb],My[Mb]);
        Mx[Mb]=p.x;
        My[Mb]=p.y;
        Crtam_pomoc=false;
        linija(Mx[Mb-1],My[Mb-1],Mx[Mb],My[Mb]);
        Crtam_pomoc=true;
        linija(Mx[Mb-1],My[Mb-1],Mx[Mb],My[Mb]);
        if(Mb==MAX_BROJ_TACAKA)
        {
          MessageBox("Ima previse tacaka poligona !","Fatalna greska",MB_OK);
          exit(1);
        }
        Mb++;
        Mx[Mb]=p.x;
        My[Mb]=p.y;
        linija(Mx[0],My[0],Mx[Mb],My[Mb]);
        linija(Mx[Mb-1],My[Mb-1],Mx[Mb],My[Mb]);
      }
      else
      {
        Dc->SetROP2(R2_NOT);
        Crtam_pomoc=true;
        Mx[0]=p.x;
        My[0]=p.y;
        Mx[1]=p.x;
        My[1]=p.y;
        Mb=1;
        linija(Mx[0],My[0],Mx[1],My[1]);
      }
      break;
    case FIL:
      Dc->SetROP2(R2_NOT);
      SetCursor(0,IDC_WAIT);
      fil(p.x,p.y);
      SetCursor(GetModule(),"Kurzor");
      Invalidate(false);
  }
}

void MojProzor::EvMouseMove(uint,TPoint &p)
{
  if(Resetka)
  {
    p.x=((p.x+(Frekfencija>>1))/Frekfencija)*Frekfencija;
    p.y=((p.y+(Frekfencija>>1))/Frekfencija)*Frekfencija;
  }
  static char str[12];
  sprintf(str,"(%d,%d)",p.x,p.y);
  TextGadget->SetText(str);
  if(Crtam_pomoc&&Sta_crtam!=FIL)
    switch(Sta_crtam)
    {
      case LINIJA:
        linija(Mx[0],My[0],Mx[1],My[1]);
        Mx[1]=p.x;
        My[1]=p.y;
        linija(Mx[0],My[0],Mx[1],My[1]);
        break;
      case O_KRUG:
      case P_KRUG:
        o_krug(Mx[0],My[0],Mx[1]);
        Mx[1]=max(abs(Mx[0]-p.x),abs(My[0]-p.y));
        o_krug(Mx[0],My[0],Mx[1]);
        break;
      case O_ELIPSA:
      case P_ELIPSA:
        o_elipsa(Mx[0],My[0],Mx[1],My[1]);
        Mx[1]=abs(Mx[0]-p.x);
        My[1]=abs(My[0]-p.y);
        o_elipsa(Mx[0],My[0],Mx[1],My[1]);
        break;
      case BEISER:
        if(Mb>1)
          linija(Mx[Mb],My[Mb],Mx[Mb-2],My[Mb-2]);
        beiser(Mx[0],My[0],Mx[2],My[2],Mx[3],My[3],Mx[1],My[1]);
        Mx[Mb]=p.x;
        My[Mb]=p.y;
        if(Mb>1)
          linija(Mx[Mb],My[Mb],Mx[Mb-2],My[Mb-2]);
        beiser(Mx[0],My[0],Mx[2],My[2],Mx[3],My[3],Mx[1],My[1]);
        break;
      case O_POLIGON:
      case P_POLIGON:
        if(Mb>1)
          linija(Mx[0],My[0],Mx[Mb],My[Mb]);
        linija(Mx[Mb-1],My[Mb-1],Mx[Mb],My[Mb]);
        Mx[Mb]=p.x;
        My[Mb]=p.y;
        if(Mb>1)
          linija(Mx[0],My[0],Mx[Mb],My[Mb]);
        linija(Mx[Mb-1],My[Mb-1],Mx[Mb],My[Mb]);
    }
}

void MojProzor::EvRButtonDown(uint,TPoint &p)
{
  if(Crtam_pomoc&&(Sta_crtam==O_POLIGON||Sta_crtam==P_POLIGON))
  {
    if(Resetka)
    {
      p.x=((p.x+(Frekfencija>>1))/Frekfencija)*Frekfencija;
      p.y=((p.y+(Frekfencija>>1))/Frekfencija)*Frekfencija;
    }
    if(Mb>1)
      linija(Mx[0],My[0],Mx[Mb],My[Mb]);
    linija(Mx[Mb-1],My[Mb-1],Mx[Mb],My[Mb]);
    Mx[Mb]=p.x;
    My[Mb++]=p.y;
    if(Sta_crtam==O_POLIGON)
      Crtam_pomoc=false;
    if(Mb>2)
      linija(Mx[0],My[0],Mx[Mb-1],My[Mb-1]);
    linija(Mx[Mb-2],My[Mb-2],Mx[Mb-1],My[Mb-1]);
    if(Sta_crtam==P_POLIGON)
    {
      Crtam_pomoc=false;
      SetCursor(0,IDC_WAIT);
      poligon(Mx,My,Mb);
      SetCursor(GetModule(),"Kurzor");
    }
    Invalidate(false);
  }
}

void MojProzor::Paint(TDC &dc,bool,TRect&)
{
  dc.SetROP2(R2_COPYPEN);
  dc.SetDIBitsToDevice(TRect(0,0,Maxx,Maxy),TPoint(0,0),*Dib);
  if(Resetka)
  {
    dc.SetROP2(R2_NOT);
    for(int x=0;x<=Maxx;x+=Frekfencija)
      for(int y=0;y<=Maxy;y+=Frekfencija)
        dc.SetPixel(x,y,TColor::Black);
  }
}

void MojProzor::Cm_boja(void)
{
  if(!Crtam_pomoc)
  {
    TChooseColorDialog::TData izbor;
    static TColor boje[16]=
    {
      0x010101l,0x101010l,0x202020l,0x303030l,
      0x404040l,0x505050l,0x606060l,0x707070l,
      0x808080l,0x909090l,0xA0A0A0l,0xB0B0B0l,
      0xC0C0C0l,0xD0D0D0l,0xE0E0E0l,0xF0F0F0l
    };
    izbor.Flags=CC_RGBINIT;
    izbor.Color=Boja;
    izbor.CustColors=boje;
    if(TChooseColorDialog(this,izbor,0,"Izbor Boje").Execute()==IDOK)
      Boja=izbor.Color;
  }
}

class MojProgram:public TApplication
{
  public:
    MojProgram(void):TApplication()
    {
    }
    void InitMainWindow(void)
    {
      TTextGadget *tg=new TTextGadget(0,TGadget::Embossed,TTextGadget::Center,8,0);
      TDecoratedMDIFrame *frame=new TDecoratedMDIFrame("Grafika 2D",TResId("Komanda"),*new MojProzor(tg),true);
      TStatusBar *sb=new TStatusBar(frame);
      sb->Insert(*tg);
      TControlBar *cb=new TControlBar(frame);
      cb->Insert(*new TButtonGadget(CM_EXIT,CM_EXIT));
      cb->Insert(*new TSeparatorGadget);
      cb->Insert(*new TButtonGadget(RC_novi,RC_novi));
      cb->Insert(*new TSeparatorGadget);
      cb->Insert(*new TButtonGadget(RC_linija,RC_linija));
      cb->Insert(*new TButtonGadget(RC_o_krug,RC_o_krug));
      cb->Insert(*new TButtonGadget(RC_p_krug,RC_p_krug));
      cb->Insert(*new TButtonGadget(RC_o_elipsa,RC_o_elipsa));
      cb->Insert(*new TButtonGadget(RC_p_elipsa,RC_p_elipsa));
      cb->Insert(*new TButtonGadget(RC_beiser,RC_beiser));
      cb->Insert(*new TButtonGadget(RC_o_poligon,RC_o_poligon));
      cb->Insert(*new TButtonGadget(RC_p_poligon,RC_p_poligon));
      cb->Insert(*new TButtonGadget(RC_fil,RC_fil));
      cb->Insert(*new TSeparatorGadget);
      cb->Insert(*new TButtonGadget(RC_resetka,RC_resetka));
      cb->Insert(*new TButtonGadget(RC_frekfencija,RC_frekfencija));
      cb->Insert(*new TSeparatorGadget);
      cb->Insert(*new TButtonGadget(RC_boja,RC_boja));
      cb->SetHintMode(TGadgetWindow::EnterHints);
      frame->Insert(*sb,TDecoratedFrame::Bottom);
      frame->Insert(*cb);
      SetMainWindow(frame);
      GetMainWindow()->Attr.AccelTable="Tastatura";
      GetMainWindow()->SetIcon(this,"Ikona");
    }
};

int OwlMain(int,char*[])
{
  return MojProgram().Run();
}
