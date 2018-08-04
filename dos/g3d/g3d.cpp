#include <owl/applicat.h>
#include <owl/dc.h>
#include <owl/dialog.h>
#include <owl/mdi.h>
#include <owl/owlpch.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "g3d.rc"

#define MAX_BROJ_TACAKA 256
#define MAX_BROJ_TEMENA 1024
#define MAX_BROJ_PLJOSNI 256
#define MAX_VELICINA_POLIGONA 32
#define STR_MAX_VELICINA_POLIGONA "32"
#define TACAKA_OSE 5
#define VELICINA_NIZA 32766

#define MAXPATH 80
#define AGLA_LEN_VALUE 128
#define AGLA_MAX_CLASS 5
#define BS 11
#define BT 40

class MojDijalog_ugao:public TDialog
{
  public:
    MojDijalog_ugao(TWindow *tata,double *a):TWindow(tata),TDialog(tata,"Dijalog_ugao")
    {
      ugao=a;
    }
    bool CanClose(void);
    void SetupWindow(void)
    {
      TDialog::SetupWindow();
      ::SetScrollRange(GetDlgItem(RC_ugao_s),SB_CTL,0,360,false);
      SetDlgItemText(RC_ugao_b,"10.0");
    };
    void EvHScroll(uint,uint,HWND);
    void Cm_promena(void);
  protected:
    double *ugao;
  DECLARE_RESPONSE_TABLE(MojDijalog_ugao);
};

DEFINE_RESPONSE_TABLE1(MojDijalog_ugao,TDialog)
  EV_WM_HSCROLL,
  EV_EN_CHANGE(RC_ugao_b,Cm_promena),
END_RESPONSE_TABLE;

bool MojDijalog_ugao::CanClose(void)
{
  char s[11];
  double a;
  int greska;
  GetDlgItemText(RC_ugao_b,s,10);
  greska=sscanf(s,"%lf",&a);
  if(greska==1&&a>=-180.0&&a<=180.0)
  {
    *ugao=a;
    return true;
  }
  else
  {
    MessageBox("Ugao mora biti broj\nizmedju -180.0 i 180.0 !","Greska",MB_OK);
    return false;
  }
}

void MojDijalog_ugao::EvHScroll(uint kod,uint s_pos,HWND prozor)
{
  char s[11];
  uint pos=::GetScrollPos(prozor,SB_CTL);
  switch(kod)
  {
    case SB_LINEUP:
      if(pos>0)
        pos--;
      break;
    case SB_LINEDOWN:
      if(pos<360)
        pos++;
      break;
    case SB_PAGEUP:
      if(pos>10)
        pos-=10;
      else
        pos=0;
      break;
    case SB_PAGEDOWN:
      if(pos<350)
        pos+=10;
      else
        pos=360;
      break;
    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
      pos=s_pos;
      break;
  }
  sprintf(s,"%-.2lf",(double)pos-180);
  SetDlgItemText(RC_ugao_b,s);
}

void MojDijalog_ugao::Cm_promena(void)
{
  char s[11];
  double a;
  GetDlgItemText(RC_ugao_b,s,10);
  sscanf(s,"%lf",&a);
  ::SetScrollPos(GetDlgItem(RC_ugao_s),SB_CTL,(int)a+180,true);
}

class MojDijalog_skala:public TDialog
{
  public:
    MojDijalog_skala(TWindow *tata,double *a):TWindow(tata),TDialog(tata,"Dijalog_skala")
    {
      skala=a;
    }
    bool CanClose(void);
    void SetupWindow(void)
    {
      TDialog::SetupWindow();
      ::SetScrollRange(GetDlgItem(RC_skala_s),SB_CTL,0,200,false);
      SetDlgItemText(RC_skala_b,"0.25");
    };
    void EvHScroll(uint,uint,HWND);
    void Cm_promena(void);
  protected:
    double *skala;
  DECLARE_RESPONSE_TABLE(MojDijalog_skala);
};

DEFINE_RESPONSE_TABLE1(MojDijalog_skala,TDialog)
  EV_WM_HSCROLL,
  EV_EN_CHANGE(RC_skala_b,Cm_promena),
END_RESPONSE_TABLE;

bool MojDijalog_skala::CanClose(void)
{
  char s[11];
  double a;
  int greska;
  GetDlgItemText(RC_skala_b,s,10);
  greska=sscanf(s,"%lf",&a);
  if(greska==1&&a!=0.0)
  {
    *skala=a;
    return true;
  }
  else
  {
    MessageBox("Skaliranje mora biti\nrealan broj razlicit od 0 !","Greska",MB_OK);
    return false;
  }
}

void MojDijalog_skala::EvHScroll(uint kod,uint s_pos,HWND prozor)
{
  char s[11];
  uint pos=::GetScrollPos(prozor,SB_CTL);
  switch(kod)
  {
    case SB_LINEUP:
      if(pos>0)
        pos--;
      break;
    case SB_LINEDOWN:
      if(pos<200)
        pos++;
      break;
    case SB_PAGEUP:
      if(pos>10)
        pos-=10;
      else
        pos=0;
      break;
    case SB_PAGEDOWN:
      if(pos<190)
        pos+=10;
      else
        pos=200;
      break;
    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
      pos=s_pos;
      break;
  }
  sprintf(s,"%-.2lf",(double)((int)pos-100)/4.0);
  SetDlgItemText(RC_skala_b,s);
}

void MojDijalog_skala::Cm_promena(void)
{
  char s[11];
  double a;
  GetDlgItemText(RC_skala_b,s,10);
  sscanf(s,"%lf",&a);
  ::SetScrollPos(GetDlgItem(RC_skala_s),SB_CTL,(int)(a*4.0)+100,true);
}

class MojDijalog_zoom:public TDialog
{
  public:
    MojDijalog_zoom(TWindow *tata,double *a):TWindow(tata),TDialog(tata,"Dijalog_zoom")
    {
      zoom=a;
    }
    bool CanClose(void);
    void SetupWindow(void);
    void EvHScroll(uint,uint,HWND);
    void Cm_promena(void);
  protected:
    double *zoom;
  DECLARE_RESPONSE_TABLE(MojDijalog_zoom);
};

DEFINE_RESPONSE_TABLE1(MojDijalog_zoom,TDialog)
  EV_WM_HSCROLL,
  EV_EN_CHANGE(RC_zoom_b,Cm_promena),
END_RESPONSE_TABLE;

bool MojDijalog_zoom::CanClose(void)
{
  char s[11];
  double a;
  int greska;
  GetDlgItemText(RC_zoom_b,s,10);
  greska=sscanf(s,"%lf",&a);
  if(greska==1&&a>0.0)
  {
    *zoom=a;
    return true;
  }
  else
  {
    MessageBox("Zoom faktor mora biti realan\nbroj strogo veci od 0 !","Greska",MB_OK);
    return false;
  }
}

void MojDijalog_zoom::SetupWindow(void)
{
  TDialog::SetupWindow();
  ::SetScrollRange(GetDlgItem(RC_zoom_s),SB_CTL,1,400,false);
  char s[11];
  sprintf(s,"%-.2lf",*zoom);
  SetDlgItemText(RC_zoom_b,s);
};

void MojDijalog_zoom::EvHScroll(uint kod,uint s_pos,HWND prozor)
{
  char s[11];
  uint pos=::GetScrollPos(prozor,SB_CTL);
  switch(kod)
  {
    case SB_LINEUP:
      if(pos>1)
        pos--;
      break;
    case SB_LINEDOWN:
      if(pos<400)
        pos++;
      break;
    case SB_PAGEUP:
      if(pos>11)
        pos-=10;
      else
        pos=1;
      break;
    case SB_PAGEDOWN:
      if(pos<390)
        pos+=10;
      else
        pos=400;
      break;
    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
      pos=s_pos;
      break;
  }
  sprintf(s,"%-.2lf",(double)pos/2);
  SetDlgItemText(RC_zoom_b,s);
}

void MojDijalog_zoom::Cm_promena(void)
{
  char s[11];
  double a;
  GetDlgItemText(RC_zoom_b,s,10);
  sscanf(s,"%lf",&a);
  ::SetScrollPos(GetDlgItem(RC_zoom_s),SB_CTL,(int)(a*2.0),true);
};

class MojDijalog_oko:public TDialog
{
  public:
    MojDijalog_oko(TWindow *tata,double *a):TWindow(tata),TDialog(tata,"Dijalog_oko")
    {
      oko=a;
    }
    bool CanClose(void);
    void SetupWindow(void);
    void EvHScroll(uint,uint,HWND);
    void Cm_promena(void);
  protected:
    double *oko;
  DECLARE_RESPONSE_TABLE(MojDijalog_oko);
};

DEFINE_RESPONSE_TABLE1(MojDijalog_oko,TDialog)
  EV_WM_HSCROLL,
  EV_EN_CHANGE(RC_oko_b,Cm_promena),
END_RESPONSE_TABLE;

bool MojDijalog_oko::CanClose(void)
{
  char s[11];
  double a;
  int greska;
  GetDlgItemText(RC_oko_b,s,10);
  greska=sscanf(s,"%lf",&a);
  if(greska==1&&a>0.0)
  {
    *oko=a;
    return true;
  }
  else
  {
    MessageBox("Rastojanje oka mora biti realan\nbroj strogo veci od 0 !","Greska",MB_OK);
    return false;
  }
}

void MojDijalog_oko::SetupWindow(void)
{
  TDialog::SetupWindow();
  ::SetScrollRange(GetDlgItem(RC_oko_s),SB_CTL,1,800,false);
  char s[11];
  sprintf(s,"%-.2lf",*oko);
  SetDlgItemText(RC_oko_b,s);
};


void MojDijalog_oko::EvHScroll(uint kod,uint s_pos,HWND prozor)
{
  char s[11];
  uint pos=::GetScrollPos(prozor,SB_CTL);
  switch(kod)
  {
    case SB_LINEUP:
      if(pos>1)
        pos--;
      break;
    case SB_LINEDOWN:
      if(pos<800)
        pos++;
      break;
    case SB_PAGEUP:
      if(pos>21)
        pos-=20;
      else
        pos=1;
      break;
    case SB_PAGEDOWN:
      if(pos<780)
        pos+=20;
      else
        pos=800;
      break;
    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
      pos=s_pos;
      break;
  }
  sprintf(s,"%-.2lf",(double)pos);
  SetDlgItemText(RC_oko_b,s);
}

void MojDijalog_oko::Cm_promena(void)
{
  char s[11];
  double a;
  GetDlgItemText(RC_oko_b,s,10);
  sscanf(s,"%lf",&a);
  ::SetScrollPos(GetDlgItem(RC_oko_s),SB_CTL,(int)a,true);
}

class MojDijalog_teme:public TDialog
{
  public:
    MojDijalog_teme(TWindow *tata,int *a):TWindow(tata),TDialog(tata,"Dijalog_teme")
    {
      teme=a;
    }
    bool CanClose(void);
    void SetupWindow(void)
    {
      TDialog::SetupWindow();
      ::SetScrollRange(GetDlgItem(RC_teme_s),SB_CTL,3,MAX_VELICINA_POLIGONA,false);
      SetDlgItemInt(RC_teme_b,3);
    };
    void EvHScroll(uint,uint,HWND);
    void Cm_promena(void)
    {
      ::SetScrollPos(GetDlgItem(RC_teme_s),SB_CTL,GetDlgItemInt(RC_teme_b),true);
    };
  protected:
    int *teme;
  DECLARE_RESPONSE_TABLE(MojDijalog_teme);
};

DEFINE_RESPONSE_TABLE1(MojDijalog_teme,TDialog)
  EV_WM_HSCROLL,
  EV_EN_CHANGE(RC_teme_b,Cm_promena),
END_RESPONSE_TABLE;

bool MojDijalog_teme::CanClose(void)
{
  int a;
  bool nema_greske;
  a=GetDlgItemInt(RC_teme_b,&nema_greske);
  if(nema_greske&&a>=3&&a<=MAX_VELICINA_POLIGONA)
  {
    *teme=a;
    return true;
  }
  else
  {
    MessageBox("Broj temena je ceo broj\nizmedju 3 i " STR_MAX_VELICINA_POLIGONA " !","Greska",MB_OK);
    return false;
  }
}

void MojDijalog_teme::EvHScroll(uint kod,uint s_pos,HWND prozor)
{
  uint pos=::GetScrollPos(prozor,SB_CTL);
  switch(kod)
  {
    case SB_LINEUP:
      if(pos>3)
        pos--;
      break;
    case SB_LINEDOWN:
      if(pos<MAX_VELICINA_POLIGONA)
        pos++;
      break;
    case SB_PAGEUP:
      if(pos>6)
        pos-=3;
      else
        pos=3;
      break;
    case SB_PAGEDOWN:
      if(pos<MAX_VELICINA_POLIGONA-1)
        pos+=3;
      else
        pos=MAX_VELICINA_POLIGONA;
      break;
    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
      pos=s_pos;
      break;
  }
  SetDlgItemInt(RC_teme_b,pos);
}

class MojDijalog_tacka:public TDialog
{
  public:
    MojDijalog_tacka(TWindow *tata,double *a,double *b,double *c):TWindow(tata),TDialog(tata,"Dijalog_tacka")
    {
      x=a;
      y=b;
      z=c;
    }
    bool CanClose(void);
    void SetupWindow(void);
  protected:
    double *x;
    double *y;
    double *z;
};

bool MojDijalog_tacka::CanClose(void)
{
  char s[11];
  double a;
  double b;
  double c;
  int greska;
  GetDlgItemText(RC_tacka_x,s,10);
  greska=sscanf(s,"%lf",&a);
  GetDlgItemText(RC_tacka_y,s,10);
  greska+=sscanf(s,"%lf",&b);
  GetDlgItemText(RC_tacka_z,s,10);
  greska+=sscanf(s,"%lf",&c);
  if(greska==3)
  {
    *x=a;
    *y=b;
    *z=c;
    return true;
  }
  else
  {
    MessageBox("Kordinate moraju biti\nrealani brojevi !","Greska",MB_OK);
    return false;
  }
}

void MojDijalog_tacka::SetupWindow(void)
{
  TDialog::SetupWindow();
  char s[11];
  sprintf(s,"%-.2lf",*x);
  SetDlgItemText(RC_tacka_x,s);
  sprintf(s,"%-.2lf",*y);
  SetDlgItemText(RC_tacka_y,s);
  sprintf(s,"%-.2lf",*z);
  SetDlgItemText(RC_tacka_z,s);
};

class MojProzor:public TMDIClient
{
  public:
    MojProzor(TTextGadget *tg):TMDIClient()
    {
      TextGadget=tg;
      Smaxx=TScreenDC().GetDeviceCaps(HORZRES);
      Smaxy=TScreenDC().GetDeviceCaps(VERTRES);
      Dib=new TDib(Smaxx,Smaxy,256);
      Dibdc=new TDibDC(*Dib);
      Dibdc->FillRect(0,0,Smaxx,Smaxy,TBrush(TColor::White));
      Boja=TColor::Black;
      Model=ZICANI;
      Projekcija=CENTRALNA;
      Osa=false;
      Fpx=0.0;
      Fpy=0.0;
      Fpz=0.0;
      Fvx=0.0;
      Fvy=0.0;
      Fvz=1.0;
      Fvsxz=1.0;
      Fo=100.0;
      Fe=99.0;
      Fs=40.0;
      Tacke[0].x=0.0;
      Tacke[0].y=0.0;
      Tacke[0].z=0.0;
      normalizuj(0);
      projektuj(0);
      Tacke[1].x=1.0;
      Tacke[1].y=0.0;
      Tacke[1].z=0.0;
      normalizuj(1);
      projektuj(1);
      Tacke[2].x=0.0;
      Tacke[2].y=1.0;
      Tacke[2].z=0.0;
      normalizuj(2);
      projektuj(2);
      Tacke[3].x=0.0;
      Tacke[3].y=0.0;
      Tacke[3].z=1.0;
      normalizuj(3);
      projektuj(3);
      Broj_tacaka=TACAKA_OSE;
      Broj_temena=0;
      Broj_pljosni=0;
      Magnet=false;
      Unos_tacaka=0;
      *Ime_fajla='\0';
      Prljavo=false;
      SetCursor(GetModule(),"Kurzor");
    };
    ~MojProzor(void)
    {
      delete Dibdc;
      delete Dib;
    };
  protected:
    TTextGadget *TextGadget;
    TDib *Dib;
    TDC *Dibdc;
    TDC *Dc;
    TColor Boja;
    int Smaxx;
    int Smaxy;
    int Maxx;
    int Maxy;
    double Dmaxx;
    double Dmaxy;
    double Dmaxx2;
    double Dmaxy2;
    void tacka(int x,int y)
    {
      Dibdc->SetPixel(x,y,Boja);
    };
    void linija(int,int,int,int);
    void kliping(double,double,double,double,double,double,double,double);
    enum
    {
      ZICANI,
      PLJOSNI,
      SVETLO
    } Model;
    enum
    {
      CENTRALNA,
      PARALELNA
    } Projekcija;
    bool Osa;
    double Fpx;
    double Fpy;
    double Fpz;
    double Fvx;
    double Fvy;
    double Fvz;
    double Fvsxz;
    double Fo;
    double Fe;
    double Fs;
    struct
    {
      double x;
      double y;
      double z;
      double nx;
      double ny;
      double nz;
      double px;
      double py;
    } Tacke[MAX_BROJ_TACAKA];
    int Broj_tacaka;
    int Temena[MAX_BROJ_TEMENA];
    int Broj_temena;
    struct
    {
      int p;
      int k;
      int cr;
      int cg;
      int cb;
    } Pljosni[MAX_BROJ_PLJOSNI];
    int Broj_pljosni;
    struct TACKA
    {
      double x;
      double y;
    } *Tac;
    int B_tac;
    struct PLJOSAN
    {
      int p;
      int k;
      int staro;
      double a;
      double b;
      double c;
      double d;
      double xmin;
      double ymin;
      double xmax;
      double ymax;
    } *Plj;
    int B_plj;
    enum
    {
      RADI_ROTACIJU,
      RADI_TRANSLACIJU,
      RADI_SVETLO,
      RADI_POGLED,
      RADI_UNOS
    } Sta_radim;
    bool Magnet;
    int Unos_tacaka;
    int Bafer;
    char Ime_fajla[MAXPATH];
    bool Prljavo;
    enum
    {
      NISTA=-1,
      AGLA_tacka,
      AGLA_sekcija,
      AGLA_broj,
      AGLA_boja,
      AGLA_EOF
    } AGLA_class;
    char AGLA_value[AGLA_LEN_VALUE+1];
    int AGLA_len;
    int AGLA_old_nl;
    int AGLA_new_nl;
    int AGLA_old_pos;
    int AGLA_new_pos;
    FILE *AGLA_file;
    char *AGLA_error;
    int AGLA_scanner(void);
    int ubaci_tacku(void);
    int ubaci_teme(void);
    int ubaci_prvo_teme(void);
    int zavrsi_pljosan(void);
    int AGSA_t(void);
    int AGSA_q(void);
    int AGSA_p(void);
    int AGSA_s(void);
    int AGSA_parser(void);
    int snimi(char *);
    void uradi_kliping(int,double,double,double,double);
    double c_projekcija(double,double);
    void iscrtaj_liniju(int,int,int);
    void iscrtaj_4_liniju(bool,int,int);
    void iscrtaj_zicani(bool);
    bool senka(double,double,double,int);
    void iscrtaj_svetlo(bool,int,int);
    bool unutra(int,int,int,int);
    void iscrtaj_pljosni(bool);
    void iscrtaj(void);
    void normalizuj(int);
    void projektuj(int);
    void normalizuj_projektuj_iscrtaj(void);
    void uradi_rotaciju(void);
    void uradi_translaciju(void);
    void uradi_pogled(void);
    void uradi_unos(void);
    void ubaci_u_bafer(double,double,double);
    void zahtevaj_unos_tacaka(int);
    bool CanClose(void);
    void EvLButtonDown(uint,TPoint&);
    void EvRButtonDown(uint,TPoint&);
    void EvSize(uint,TSize&);
    void Paint(TDC&,bool,TRect&);
    void Cm_novi(void);
    void Cm_otvori(void);
    void Cm_snimi(void);
    void Cm_snimi_kao(void);
    void Cm_rotacija_x(void);
    void Cm_rotacija_y(void);
    void Cm_rotacija_z(void);
    void Cm_rotacija_p(void);
    void Cm_translacija(void);
    void Cm_skaliranje(void);
    void Cm_zicani(void);
    void Cm_pljosni(void);
    void Cm_svetlo(void);
    void Cm_centralna(void);
    void Cm_paralelna(void);
    void Cm_osa(void);
    void Cm_pogled(void);
    void Cm_zoom(void);
    void Cm_rastojanje_oka(void);
    void Cm_unos_pljosni(void);
    void Cm_magnet(void);
    void Cm_unos_tacke(void);
    void Cm_sledeca_tacka(void);
    void Ce_snimi(TCommandEnabler &ce)
    {
      ce.Enable(Prljavo);
    };
    void Ce_snimi_kao(TCommandEnabler &ce)
    {
      ce.Enable(Prljavo);
    };
    void Ce_zicani(TCommandEnabler &ce)
    {
      ce.SetCheck(Model==ZICANI?TCommandEnabler::Checked:TCommandEnabler::Unchecked);
    };
    void Ce_pljosni(TCommandEnabler &ce)
    {
      ce.SetCheck(Model==PLJOSNI?TCommandEnabler::Checked:TCommandEnabler::Unchecked);
    };
    void Ce_svetlo(TCommandEnabler &ce)
    {
      ce.SetCheck(Model==SVETLO?TCommandEnabler::Checked:TCommandEnabler::Unchecked);
    };
    void Ce_centralna(TCommandEnabler &ce)
    {
      ce.SetCheck(Projekcija==CENTRALNA?TCommandEnabler::Checked:TCommandEnabler::Unchecked);
    };
    void Ce_paralelna(TCommandEnabler &ce)
    {
      ce.SetCheck(Projekcija==PARALELNA?TCommandEnabler::Checked:TCommandEnabler::Unchecked);
    };
    void Ce_osa(TCommandEnabler &ce)
    {
      ce.SetCheck(Osa?TCommandEnabler::Checked:TCommandEnabler::Unchecked);
      ce.Enable(Model==ZICANI||Unos_tacaka);
    };
    void Ce_rastojanje_oka(TCommandEnabler &ce)
    {
      ce.Enable(Projekcija==CENTRALNA);
    };
    void Ce_magnet(TCommandEnabler &ce)
    {
      ce.SetCheck(Magnet?TCommandEnabler::Checked:TCommandEnabler::Unchecked);
      ce.Enable(Unos_tacaka);
    };
    void Ce_unos_tacke(TCommandEnabler &ce)
    {
      ce.Enable(Unos_tacaka);
    };
    void Ce_sledeca_tacka(TCommandEnabler &ce)
    {
      ce.Enable(Unos_tacaka);
    };
  DECLARE_RESPONSE_TABLE(MojProzor);
};

DEFINE_RESPONSE_TABLE1(MojProzor,TWindow)
  EV_WM_LBUTTONDOWN,
  EV_WM_RBUTTONDOWN,
  EV_WM_SIZE,
  EV_COMMAND(RC_novi,Cm_novi),
  EV_COMMAND(RC_otvori,Cm_otvori),
  EV_COMMAND(RC_snimi,Cm_snimi),
  EV_COMMAND(RC_snimi_kao,Cm_snimi_kao),
  EV_COMMAND(RC_rotacija_x,Cm_rotacija_x),
  EV_COMMAND(RC_rotacija_y,Cm_rotacija_y),
  EV_COMMAND(RC_rotacija_z,Cm_rotacija_z),
  EV_COMMAND(RC_rotacija_p,Cm_rotacija_p),
  EV_COMMAND(RC_translacija,Cm_translacija),
  EV_COMMAND(RC_skaliranje,Cm_skaliranje),
  EV_COMMAND(RC_zicani,Cm_zicani),
  EV_COMMAND(RC_pljosni,Cm_pljosni),
  EV_COMMAND(RC_svetlo,Cm_svetlo),
  EV_COMMAND(RC_centralna,Cm_centralna),
  EV_COMMAND(RC_paralelna,Cm_paralelna),
  EV_COMMAND(RC_osa,Cm_osa),
  EV_COMMAND(RC_pogled,Cm_pogled),
  EV_COMMAND(RC_zoom,Cm_zoom),
  EV_COMMAND(RC_rastojanje_oka,Cm_rastojanje_oka),
  EV_COMMAND(RC_unos_pljosni,Cm_unos_pljosni),
  EV_COMMAND(RC_magnet,Cm_magnet),
  EV_COMMAND(RC_unos_tacke,Cm_unos_tacke),
  EV_COMMAND(RC_sledeca_tacka,Cm_sledeca_tacka),
  EV_COMMAND_ENABLE(RC_snimi,Ce_snimi),
  EV_COMMAND_ENABLE(RC_snimi_kao,Ce_snimi_kao),
  EV_COMMAND_ENABLE(RC_zicani,Ce_zicani),
  EV_COMMAND_ENABLE(RC_pljosni,Ce_pljosni),
  EV_COMMAND_ENABLE(RC_svetlo,Ce_svetlo),
  EV_COMMAND_ENABLE(RC_centralna,Ce_centralna),
  EV_COMMAND_ENABLE(RC_paralelna,Ce_paralelna),
  EV_COMMAND_ENABLE(RC_osa,Ce_osa),
  EV_COMMAND_ENABLE(RC_rastojanje_oka,Ce_rastojanje_oka),
  EV_COMMAND_ENABLE(RC_unos_tacke,Ce_unos_tacke),
  EV_COMMAND_ENABLE(RC_magnet,Ce_magnet),
  EV_COMMAND_ENABLE(RC_sledeca_tacka,Ce_sledeca_tacka),
END_RESPONSE_TABLE;

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

void MojProzor::kliping(double ax,double ay,double bx,double by,double xmin,double ymin,double xmax,double ymax)
{
  bool crtaj=true;
  bool radi=true;
  int i=0;
  while(i<4&&radi)
  {
    int ka=((ay<ymin)?1:0)+((ay>ymax)?2:0)+((ax<xmin)?4:0)+((ax>xmax)?8:0);
    int kb=((by<ymin)?1:0)+((by>ymax)?2:0)+((bx<xmin)?4:0)+((bx>xmax)?8:0);
    if(ka&kb)
    {
      crtaj=false;
      radi=false;
    }
    else
      if(!(ka|kb))
      {
        crtaj=true;
        radi=false;
      }
      else
      {
        if(((ka>>i)&1)!=((kb>>i)&1))
        {
          if(!((ka>>i)&1))
          {
            double t=ax;
            ax=bx;
            bx=t;
            t=ay;
            ay=by;
            by=t;
          }
          switch(i)
          {
            case 0:
              ax+=(bx-ax)*(ymin-ay)/(by-ay);
              ay=ymin;
              break;
            case 1:
              ax+=(bx-ax)*(ymax-ay)/(by-ay);
              ay=ymax;
              break;
            case 2:
              ay+=(by-ay)*(xmin-ax)/(bx-ax);
              ax=xmin;
              break;
            case 3:
              ay+=(by-ay)*(xmax-ax)/(bx-ax);
              ax=xmax;
          }
        }
        i++;
      }
  }
  if(crtaj)
    linija((int)ax,(int)ay,(int)bx,(int)by);
}

int MojProzor::AGLA_scanner(void)
{
  static int len[AGLA_MAX_CLASS-1];
  static int nl[AGLA_MAX_CLASS-1];
  static int pos[AGLA_MAX_CLASS-1];
  static unsigned char ss[UCHAR_MAX+1]=
  {
    10,10,10,10,10,10,10,10,10,0,2,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
    0,10,10,8,10,1,10,10,10,10,10,6,10,6,7,10,4,4,4,4,4,4,4,4,4,4,9,10,10,10,10,10,
    10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,3,10,5,10,10,
    10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
    10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
    10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
    10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
    10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10
  };
  static int pr[BT][BS]=
  {
    {0,1,0,6,2,BT,8,BT,3,9,BT},
    {1,1,0,1,1,1,1,1,1,1,1},
    {BT,BT,BT,BT,2,BT,BT,10,BT,BT,BT},
    {BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT},
    {37,22,37,23,4,BT,BT,BT,BT,BT,BT},
    {BT,BT,BT,BT,5,BT,BT,BT,BT,BT,BT},
    {6,6,6,6,6,0,6,6,6,6,6},
    {BT,BT,BT,BT,7,BT,BT,BT,BT,BT,BT},
    {BT,BT,BT,BT,32,BT,BT,BT,BT,BT,BT},
    {9,11,9,12,13,BT,BT,BT,BT,BT,BT},
    {33,14,33,15,16,BT,36,BT,BT,BT,BT},
    {11,11,9,11,11,11,11,11,11,11,11},
    {12,12,12,12,12,9,12,12,12,12,12},
    {39,17,39,18,19,BT,BT,BT,BT,BT,BT},
    {14,14,33,14,14,14,14,14,14,14,14},
    {15,15,15,15,15,33,15,15,15,15,15},
    {33,14,33,15,16,BT,36,21,BT,BT,BT},
    {17,17,39,17,17,17,17,17,17,17,17},
    {18,18,18,18,18,39,18,18,18,18,18},
    {37,22,37,23,4,BT,BT,BT,BT,BT,BT},
    {BT,BT,BT,BT,20,BT,BT,21,BT,BT,BT},
    {35,24,35,25,26,BT,38,BT,BT,BT,BT},
    {22,22,37,22,22,22,22,22,22,22,22},
    {23,23,23,23,23,37,23,23,23,23,23},
    {24,24,35,24,24,24,24,24,24,24,24},
    {25,25,25,25,25,35,25,25,25,25,25},
    {35,24,35,25,26,BT,38,5,BT,BT,BT},
    {27,28,27,29,7,BT,BT,BT,BT,BT,BT},
    {28,28,27,28,28,28,28,28,28,28,28},
    {29,29,29,29,29,27,29,29,29,29,29},
    {BT,BT,BT,BT,30,BT,BT,5,BT,BT,BT},
    {27,28,27,29,31,BT,BT,BT,BT,BT,BT},
    {BT,BT,BT,BT,32,BT,BT,10,BT,BT,BT},
    {33,14,33,15,20,BT,36,BT,BT,BT,BT},
    {27,28,27,29,31,BT,BT,BT,BT,BT,BT},
    {35,24,35,25,30,BT,38,BT,BT,BT,BT},
    {BT,BT,BT,BT,20,BT,BT,BT,BT,BT,BT},
    {37,22,37,23,31,BT,BT,BT,BT,BT,BT},
    {BT,BT,BT,BT,30,BT,BT,BT,BT,BT,BT},
    {39,17,39,18,34,BT,BT,BT,BT,BT,BT}
  };
  int c;
  int n;
  int st;
  st=0;
  do
  {
    switch(st)
    {
      case 0:
        AGLA_old_nl=AGLA_new_nl;
        AGLA_old_pos=AGLA_new_pos;
        n=0;
        AGLA_class=NISTA;
        break;
      case 2:
        AGLA_class=AGLA_broj;
        len[AGLA_broj]=n;
        nl[AGLA_broj]=AGLA_new_nl;
        pos[AGLA_broj]=AGLA_new_pos;
        break;
      case 3:
        AGLA_class=AGLA_sekcija;
        len[AGLA_sekcija]=n;
        nl[AGLA_sekcija]=AGLA_new_nl;
        pos[AGLA_sekcija]=AGLA_new_pos;
        break;
      case 4:
      case 7:
      case 31:
        AGLA_class=AGLA_boja;
        len[AGLA_boja]=n;
        nl[AGLA_boja]=AGLA_new_nl;
        pos[AGLA_boja]=AGLA_new_pos;
        break;
      case 5:
        AGLA_class=AGLA_tacka;
        len[AGLA_tacka]=n;
        nl[AGLA_tacka]=AGLA_new_nl;
        pos[AGLA_tacka]=AGLA_new_pos;
    }
    if((c=fgetc(AGLA_file))==EOF)
      switch(st)
      {
        case 0:
          AGLA_class=AGLA_EOF;
        default:
          st=BT;
      }
    else
    {
      if(c==(int)'\n')
      {
        AGLA_new_nl++;
        AGLA_new_pos=0;
      }
      else
        AGLA_new_pos++;
      if(n==AGLA_LEN_VALUE)
      {
        AGLA_error="Predugacka vrednost lekseme";
        return 1;
      }
      AGLA_value[n]=(char)c;
      n++;
      st=ss[c]==BS?BT:pr[st][ss[c]];
    }
  }
  while(st!=BT);
  if(AGLA_class==NISTA)
  {
    AGLA_error="Nepoznata leksema";
    return 1;
  }
  else
  {
    if(AGLA_class==AGLA_EOF)
      AGLA_len=0;
    else
    {
      AGLA_len=len[AGLA_class];
      fseek(AGLA_file,(long)(AGLA_len-n),SEEK_CUR);
      AGLA_new_nl=nl[AGLA_class];
      AGLA_new_pos=pos[AGLA_class];
    }
    AGLA_value[AGLA_len]='\0';
  }
  return 0;
}

int MojProzor::ubaci_tacku(void)
{
  if(Broj_tacaka==MAX_BROJ_TACAKA)
  {
    AGLA_error="Mnogo tacaka";
    return 1;
  }
  if(sscanf(AGLA_value,"%lf %lf %lf",&Tacke[Broj_tacaka].x,&Tacke[Broj_tacaka].y,&Tacke[Broj_tacaka].z)!=3)
  {
    AGLA_error="Neispravne koordinante";
    return 1;
  }
  Broj_tacaka++;
  return 0;
}

int MojProzor::ubaci_teme(void)
{
  int b;
  if(Broj_temena==MAX_BROJ_TEMENA)
  {
    AGLA_error="Mnogo temena";
    return 1;
  }
  if((b=atoi(AGLA_value))>=Broj_tacaka-TACAKA_OSE)
  {
    AGLA_error="Nepostojeca tacka";
    return 1;
  }
  Temena[Broj_temena++]=b+TACAKA_OSE;
  return 0;
}

int MojProzor::ubaci_prvo_teme(void)
{
  if(Broj_pljosni==MAX_BROJ_PLJOSNI)
  {
    AGLA_error="Mnogo pljosni";
    return 0;
  }
  Pljosni[Broj_pljosni].p=Broj_temena;
  return ubaci_teme();
}

int MojProzor::zavrsi_pljosan(void)
{
  Pljosni[Broj_pljosni].k=Broj_temena;
  if(sscanf(AGLA_value+1,"%d %d %d",&Pljosni[Broj_pljosni].cr,&Pljosni[Broj_pljosni].cg,&Pljosni[Broj_pljosni].cb)!=3)
  {
    AGLA_error="Neispravna boja";
    return 1;
  }
  Broj_pljosni++;
  return 0;
}

int MojProzor::AGSA_t(void)
{
  while(AGLA_class==AGLA_tacka)
  {
    if(ubaci_tacku())
      return 1;
    if(AGLA_scanner())
      return 1;
  }
  if(AGLA_class!=AGLA_sekcija)
  {
    AGLA_error="Ocekivao sam lekseme : tacka sekcija";
    return 1;
  }
  return 0;
}

int MojProzor::AGSA_q(void)
{
  while(AGLA_class==AGLA_broj)
  {
    if(ubaci_teme())
      return 1;
    if(AGLA_scanner())
      return 1;
  }
  if(AGLA_class!=AGLA_boja)
  {
    AGLA_error="Ocekivao sam lekseme : broj boja";
    return 1;
  }
  return 0;
}

int MojProzor::AGSA_p(void)
{
  while(AGLA_class==AGLA_broj)
  {
    if(ubaci_prvo_teme())
      return 1;
    if(AGLA_scanner())
      return 1;
    for(int i=0;i<2;i++)
    {
      if(AGLA_class!=AGLA_broj)
      {
        AGLA_error="Ocekivao sam leksemu broj";
        return 1;
      }
      if(ubaci_teme())
        return 1;
      if(AGLA_scanner())
        return 1;
    }
    if(AGSA_q())
      return 1;
    if(AGLA_class!=AGLA_boja)
    {
      AGLA_error="Ocekivao sam leksemu boja";
      return 1;
    }
    if(zavrsi_pljosan())
      return 1;
    if(AGLA_scanner())
      return 1;
  }
  if(AGLA_class!=AGLA_EOF)
  {
    AGLA_error="Ocekivao sam lekseme : AGLA_EOF broj";
    return 1;
  }
  return 0;
}

int MojProzor::AGSA_s(void)
{
  switch(AGLA_class)
  {
    case AGLA_tacka:
      if(ubaci_tacku())
        return 1;
      if(AGLA_scanner())
        return 1;
      if(AGSA_t())
        return 1;
      if(AGLA_class!=AGLA_sekcija)
      {
        AGLA_error="Ocekivao sam leksemu sekcija";
        return 1;
      }
      if(AGLA_scanner())
        return 1;
      if(AGSA_p())
        return 1;
      break;
    default:
      AGLA_error="Ocekivao sam lekseme : tacka";
      return 1;
  }
  return 0;
}

int MojProzor::AGSA_parser(void)
{
  if(AGLA_scanner())
    return 1;
  return AGSA_s();
}

int MojProzor::snimi(char *ime)
{
  if((AGLA_file=fopen(ime,"w"))==NULL)
  {
    MessageBox("Ne mogu otvoriti tu datoteku !","Greska",MB_OK);
    return 0;
  }
  for(int i=TACAKA_OSE;i<Broj_tacaka;i++)
    fprintf(AGLA_file,"%lf %lf %lf\n",Tacke[i].x,Tacke[i].y,Tacke[i].z);
  fputs("#\n",AGLA_file);
  for(i=0;i<Broj_pljosni;i++)
  {
    for(int j=Pljosni[i].p;j<Pljosni[i].k;j++)
      fprintf(AGLA_file,"%d ",Temena[j]-TACAKA_OSE);
    fprintf(AGLA_file,": %d %d %d\n",Pljosni[i].cr,Pljosni[i].cg,Pljosni[i].cb);
  }
  fclose(AGLA_file);
  return 1;
}

void MojProzor::uradi_kliping(int mod,double x1,double y1,double x2,double y2)
{
  double ax=Dmaxx2+x1*Fs;
  double ay=Dmaxy2-y1*Fs;
  double bx=Dmaxx2+x2*Fs;
  double by=Dmaxy2-y2*Fs;
  double xmin;
  double xmax;
  double ymin;
  double ymax;
  switch(mod)
  {
    case 0:
      xmin=0.0;
      xmax=Dmaxx;
      ymin=0.0;
      ymax=Dmaxy;
      break;
    case 1:
      ax/=2.0;
      ay/=2.0;
      bx/=2.0;
      by/=2.0;
      xmin=0.0;
      xmax=Dmaxx2;
      ymin=0.0;
      ymax=Dmaxy2;
      break;
    case 2:
      ax=(ax+Dmaxx)/2.0;
      ay/=2.0;
      bx=(bx+Dmaxx)/2.0;
      by/=2.0;
      xmin=Dmaxx2;
      xmax=Dmaxx;
      ymin=0.0;
      ymax=Dmaxy2;
      break;
    case 3:
      ax/=2.0;
      ay=(ay+Dmaxy)/2.0;
      bx/=2.0;
      by=(by+Dmaxy)/2.0;
      xmin=0.0;
      xmax=Dmaxx2;
      ymin=Dmaxy2;
      ymax=Dmaxy;
      break;
    case 4:
      ax=(ax+Dmaxx)/2.0;
      ay=(ay+Dmaxy)/2.0;
      bx=(bx+Dmaxx)/2.0;
      by=(by+Dmaxy)/2.0;
      xmin=Dmaxx2;
      xmax=Dmaxx;
      ymin=Dmaxy2;
      ymax=Dmaxy;
  }
  kliping(ax,ay,bx,by,xmin,ymin,xmax,ymax);
}

double MojProzor::c_projekcija(double x,double z)
{
  return x*Fo/(Fo+z);
}

void MojProzor::iscrtaj_liniju(int mod,int lp,int lk)
{
  if(Projekcija==CENTRALNA)
  {
    if(Tacke[lp].nz>=-Fe&&Tacke[lk].nz>=-Fe)
      uradi_kliping(mod,Tacke[lp].px,Tacke[lp].py,Tacke[lk].px,Tacke[lk].py);
    else
      if(Tacke[lp].nz>=-Fe||Tacke[lk].nz>=-Fe)
      {
        if(Tacke[lk].nz>=-Fe)
        {
          int t=lp;
          lp=lk;
          lk=t;
        }
        double t=(Fe+Tacke[lp].nz)/(Tacke[lp].nz-Tacke[lk].nz);
        uradi_kliping(mod,Tacke[lp].px,Tacke[lp].py,c_projekcija(Tacke[lp].nx+(Tacke[lk].nx-Tacke[lp].nx)*t,-Fe),c_projekcija(Tacke[lp].ny+(Tacke[lk].ny-Tacke[lp].ny)*t,-Fe));
      }
  }
  else
    uradi_kliping(mod,Tacke[lp].nx,Tacke[lp].ny,Tacke[lk].nx,Tacke[lk].ny);
}

void MojProzor::iscrtaj_4_liniju(bool unos,int lp,int lk)
{
  if(unos)
  {
    uradi_kliping(1,Tacke[lp].x,Tacke[lp].y,Tacke[lk].x,Tacke[lk].y);
    uradi_kliping(2,Tacke[lp].z,Tacke[lp].y,Tacke[lk].z,Tacke[lk].y);
    uradi_kliping(3,Tacke[lp].x,Tacke[lp].z,Tacke[lk].x,Tacke[lk].z);
  }
  iscrtaj_liniju(unos?4:0,lp,lk);
}

void MojProzor::iscrtaj_zicani(bool unos)
{
  static struct
  {
    int p;
    int k;
  } il[MAX_BROJ_TEMENA];
  if(Osa)
  {
    Boja=TColor::LtRed;
    iscrtaj_4_liniju(unos,0,1);
    Boja=TColor::LtGreen;
    iscrtaj_4_liniju(unos,0,2);
    Boja=TColor::LtBlue;
    iscrtaj_4_liniju(unos,0,3);
  }
  Boja=TColor::Black;
  int bil=0;
  for(int i=0;i<Broj_pljosni;i++)
    for(int j=Pljosni[i].p;j<Pljosni[i].k;j++)
    {
      int lp=Temena[j];
      int lk=Temena[j+1==Pljosni[i].k?Pljosni[i].p:j+1];
      if(lk>lp)
      {
        int t=lp;
        lp=lk;
        lk=t;
      }
      int n=0;
      while(n<bil&&(il[n].p!=lp||il[n].k!=lk))
        n++;
      if(n==bil)
      {
        iscrtaj_4_liniju(unos,lp,lk);
        il[bil].p=lp;
        il[bil++].k=lk;
      }
    }
  if(unos)
  {
    if(Bafer>Broj_tacaka)
    {
      Boja=TColor::LtMagenta;
      for(i=Broj_tacaka;i<Bafer;i++)
        iscrtaj_4_liniju(true,i,i+1);
      if(Bafer>Broj_tacaka+1)
        iscrtaj_4_liniju(true,Broj_tacaka,Bafer);
    }
    Dibdc->SetROP2(R2_XORPEN);
    Boja=TColor::LtRed;
    int t=(int)((Dmaxx2+Tacke[Bafer].x*Fs)/2);
    if(t>=0&&t<(Maxx>>1))
      linija(t,0,t,Maxy);
    t=(int)((Dmaxy2-Tacke[Bafer].y*Fs)/2);
    if(t>=0&&t<(Maxy>>1))
      linija(0,t,Maxx,t);
    t=(int)((Dmaxx+Dmaxx2+Tacke[Bafer].z*Fs)/2);
    if(t>=(Maxx>>1)&&t<=Maxx)
      linija(t,0,t,Maxy>>1);
    t=(int)((Dmaxy+Dmaxy2-Tacke[Bafer].z*Fs)/2);
    if(t>=(Maxy>>1)&&t<=Maxy)
      linija(0,t,Maxx>>1,t);
    Dibdc->SetROP2(R2_COPYPEN);
    Boja=TColor::Black;
    linija(0,Maxy>>1,Maxx,Maxy>>1);
    linija(Maxx>>1,0,Maxx>>1,Maxy);
  }
  Invalidate(false);
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

inline double orjentacija_2d(double x1,double y1,double x2,double y2,double x3,double y3)
{
  return (x1-x2)*(y3-y2)-(y1-y2)*(x3-x2);
}

inline double orjentacija_3d(double x1,double y1,double z1,double x2,double y2,double z2,double x3,double y3,double z3,double x4,double y4,double z4)
{
  return (x1-x2)*orjentacija_2d(y3,z3,y2,z2,y4,z4)+(y1-y2)*orjentacija_2d(z3,x3,z2,x2,z4,x4)+(z1-z2)*orjentacija_2d(x3,y3,x2,y2,x4,y4);
}

bool MojProzor::senka(double x,double y,double z,int n)
{
  if((Plj[n].a*Tacke[4].nx+Plj[n].b*Tacke[4].ny+Plj[n].c*Tacke[4].nz+Plj[n].d>0)!=(Plj[n].d-Plj[n].c*Fo>0))
    return true;
  for(int i=0;i<B_plj;i++)
    if(i!=n)
    {
      double t=Plj[i].a*(Tacke[4].nx-x)+Plj[i].b*(Tacke[4].ny-y)+Plj[i].c*(Tacke[4].nz-z);
      if(t!=0.0)
      {
        t=-(Plj[i].a*x+Plj[i].b*y+Plj[i].c*z+Plj[i].d)/t;
        if(t>0.0&&t<1.0)
        {
          int s=Plj[i].staro;
          int j=Pljosni[s].p;
          bool znak=orjentacija_3d(Tacke[4].nx,Tacke[4].ny,Tacke[4].nz,x,y,z,Tacke[Temena[Pljosni[s].k-1]].nx,Tacke[Temena[Pljosni[s].k-1]].ny,Tacke[Temena[Pljosni[s].k-1]].nz,Tacke[Temena[j]].nx,Tacke[Temena[j]].ny,Tacke[Temena[j]].nz)<0.0;
          while(j<Pljosni[s].k-1&&znak==(orjentacija_3d(Tacke[4].nx,Tacke[4].ny,Tacke[4].nz,x,y,z,Tacke[Temena[j]].nx,Tacke[Temena[j]].ny,Tacke[Temena[j]].nz,Tacke[Temena[j+1]].nx,Tacke[Temena[j+1]].ny,Tacke[Temena[j+1]].nz)<0.0))
            j++;
          if(j==Pljosni[s].k-1)
            return true;
        }
      }
    }
  return false;
}

void MojProzor::iscrtaj_svetlo(bool svetlo,int xp,int yp)
{
  double xt=(double)xp+0.5;
  double yt=(double)yp+0.5;
  double xm;
  double ym;
  double zm=0.0;
  int find=-1;
  for(int i=0;i<B_plj;i++)
  {
    int j=Plj[i].p;
    bool znak=orjentacija_2d(xt,yt,Tac[Plj[i].k-1].x,Tac[Plj[i].k-1].y,Tac[j].x,Tac[j].y)<0.0;
    while(j<Plj[i].k-1&&znak==(orjentacija_2d(xt,yt,Tac[j].x,Tac[j].y,Tac[j+1].x,Tac[j+1].y)<0.0))
      j++;
    if(j==Plj[i].k-1)
    {
      double xr=(xt-Dmaxx2)/Fs;
      double yr=(Dmaxy2-yt)/Fs;
      if(Projekcija==CENTRALNA)
      {
        double t=Plj[i].a*xr+Plj[i].b*yr+Plj[i].c*Fo;
        if(t!=0)
        {
          t=(Plj[i].c*Fo-Plj[i].d)/t;
          double z=Fo*(t-1);
          if(find==-1||z<zm)
          {
            find=i;
            zm=z;
            xm=xr*t;
            ym=yr*t;
          }
        }
      }
      else
        if(Plj[i].c!=0)
        {
          double z=-(Plj[i].a*xr+Plj[i].b*yr+Plj[i].d)/Plj[i].c;
          if(find==-1||z<zm)
          {
            find=i;
            zm=z;
            xm=xr;
            ym=yr;
          }
        }
    }
  }
  if(find!=-1)
    if(svetlo)
    {
      if(senka(xm,ym,zm,find))
      {
        Dibdc->SetPixel(xp,yp,TColor(Pljosni[Plj[find].staro].cr>>1,Pljosni[Plj[find].staro].cg>>1,Pljosni[Plj[find].staro].cb>>1));
        Dc->SetPixel(xp,yp,TColor(Pljosni[Plj[find].staro].cr>>1,Pljosni[Plj[find].staro].cg>>1,Pljosni[Plj[find].staro].cb>>1));
      }
      else
      {
        Dibdc->SetPixel(xp,yp,TColor(Pljosni[Plj[find].staro].cr,Pljosni[Plj[find].staro].cg,Pljosni[Plj[find].staro].cb));
        Dc->SetPixel(xp,yp,TColor(Pljosni[Plj[find].staro].cr,Pljosni[Plj[find].staro].cg,Pljosni[Plj[find].staro].cb));
      }
    }
    else
    {
      Dibdc->SetPixel(xp,yp,TColor(Pljosni[Plj[find].staro].cr,Pljosni[Plj[find].staro].cg,Pljosni[Plj[find].staro].cb));
      Dc->SetPixel(xp,yp,TColor(Pljosni[Plj[find].staro].cr,Pljosni[Plj[find].staro].cg,Pljosni[Plj[find].staro].cb));
    }
}

bool MojProzor::unutra(int x,int y,int r,int i)
{
  if(Plj[i].xmin>(double)(x+r-1))
    return true;
  if(Plj[i].xmax<(double)x)
    return true;
  if(Plj[i].ymin>(double)(y+r-1))
    return true;
  if(Plj[i].ymax<(double)y)
    return true;
  return false;
}

void MojProzor::iscrtaj_pljosni(bool svetlo)
{
  SetCursor(0,IDC_WAIT);
  Dc=new TClientDC(*this);
  Dc->FillRect(0,0,Smaxx,Smaxy,TBrush(TColor::White));
  B_plj=0;
  B_tac=0;
  if((Tac=new struct TACKA[MAX_BROJ_TEMENA])==NULL||(Plj=new struct PLJOSAN[MAX_BROJ_PLJOSNI])==NULL)
  {
    MessageBox("Nema dovoljno memorije !","Fatalana Greska",MB_OK);
    exit(1);
  }
  for(int i=0;i<Broj_pljosni;i++)
  {
    Plj[B_plj].staro=i;
    Plj[B_plj].p=B_tac;
    if(Projekcija==CENTRALNA)
    {
      int p=Pljosni[i].p;
      int k=Pljosni[i].k;
      int f=p;
      while(f<k&&Tacke[Temena[f]].nz<-Fe)
        f++;
      if(f<k)
      {
        f-=p;
        for(int j=0;j<(k-p);j++)
        {
          int l=Temena[(j+f)%(k-p)+p];
          int r=Temena[(j+f+1)%(k-p)+p];
          if((Tacke[l].nz>=-Fe&&Tacke[r].nz<-Fe)||(Tacke[l].nz<-Fe&&Tacke[r].nz>=-Fe))
          {
            double t=(Fe+Tacke[l].nz)/(Tacke[l].nz-Tacke[r].nz);
            Tac[B_tac].x=Dmaxx2+c_projekcija(Tacke[l].nx+(Tacke[r].nx-Tacke[l].nx)*t,-Fe)*Fs;
            Tac[B_tac++].y=Dmaxy2-c_projekcija(Tacke[l].ny+(Tacke[r].ny-Tacke[l].ny)*t,-Fe)*Fs;
          }
          if(Tacke[r].nz>=-Fe)
          {
            Tac[B_tac].x=Dmaxx2+Tacke[r].px*Fs;
            Tac[B_tac++].y=Dmaxy2-Tacke[r].py*Fs;
          }
        }
        Plj[B_plj++].k=B_tac;
      }
    }
    else
    {
      for(int j=Pljosni[i].p;j<Pljosni[i].k;j++)
      {
        Tac[B_tac].x=Dmaxx2+Tacke[Temena[j]].nx*Fs;
        Tac[B_tac++].y=Dmaxy2-Tacke[Temena[j]].ny*Fs;
      }
      Plj[B_plj++].k=B_tac;
    }
  }
  for(i=0;i<B_plj;i++)
  {
    int t=Pljosni[Plj[i].staro].p;
    int t0=Temena[t];
    int t1=Temena[t+1];
    int t2=Temena[t+2];
    Plj[i].a=(Tacke[t1].ny-Tacke[t0].ny)*(Tacke[t2].nz-Tacke[t0].nz)-(Tacke[t1].nz-Tacke[t0].nz)*(Tacke[t2].ny-Tacke[t0].ny);
    Plj[i].b=(Tacke[t1].nz-Tacke[t0].nz)*(Tacke[t2].nx-Tacke[t0].nx)-(Tacke[t1].nx-Tacke[t0].nx)*(Tacke[t2].nz-Tacke[t0].nz);
    Plj[i].c=(Tacke[t1].nx-Tacke[t0].nx)*(Tacke[t2].ny-Tacke[t0].ny)-(Tacke[t1].ny-Tacke[t0].ny)*(Tacke[t2].nx-Tacke[t0].nx);
    Plj[i].d=-Plj[i].a*Tacke[t0].nx-Plj[i].b*Tacke[t0].ny-Plj[i].c*Tacke[t0].nz;
    Plj[i].xmin=Tac[Plj[i].p].x;
    Plj[i].xmax=Plj[i].xmin;
    Plj[i].ymin=Tac[Plj[i].p].y;
    Plj[i].ymax=Plj[i].ymin;
    for(t=Plj[i].p+1;t<Plj[i].k;t++)
    {
      if(Tac[t].x<Plj[i].xmin)
        Plj[i].xmin=Tac[t].x;
      if(Tac[t].x>Plj[i].xmax)
        Plj[i].xmax=Tac[t].x;
      if(Tac[t].y<Plj[i].ymin)
        Plj[i].ymin=Tac[t].y;
      if(Tac[t].y>Plj[i].ymax)
        Plj[i].ymax=Tac[t].y;
    }
  }
  stack st(this);
  st.push(0);
  st.push(0);
  st.push(1024);
  while(st.not_empty())
  {
    int r=st.pop();
    int yp=st.pop();
    int xp=st.pop();
    if(xp<=Maxx&&yp<=Maxy)
    {
      i=0;
      while(i<B_plj&&unutra(xp,yp,r,i))
        i++;
      if(i<B_plj)
        if(r>1)
        {
          r>>=1;
          st.push(xp+r);
          st.push(yp+r);
          st.push(r);
          st.push(xp);
          st.push(yp+r);
          st.push(r);
          st.push(xp+r);
          st.push(yp);
          st.push(r);
          st.push(xp);
          st.push(yp);
          st.push(r);
        }
        else
          iscrtaj_svetlo(svetlo,xp,yp);
    }
  }
  delete[] Plj;
  delete[] Tac;
  delete Dc;
  SetCursor(GetModule(),"Kurzor");
}

void MojProzor::iscrtaj(void)
{
  Dibdc->FillRect(0,0,Smaxx,Smaxy,TBrush(TColor::White));
  if(Unos_tacaka)
    iscrtaj_zicani(true);
  else
    switch(Model)
    {
      case ZICANI:
        iscrtaj_zicani(false);
        break;
      case PLJOSNI:
        iscrtaj_pljosni(false);
        break;
      case SVETLO:
        iscrtaj_pljosni(true);
    }
}

void MojProzor::normalizuj(int i)
{
  if(Fvsxz==0.0)
  {
    Tacke[i].nx=Tacke[i].x-Fpx;
    Tacke[i].ny=Fpz-Tacke[i].z;
    Tacke[i].nz=Tacke[i].y-Fpy;
  }
  else
  {
    double mx=Tacke[i].x-Fpx;
    double my=Tacke[i].y-Fpy;
    double mz=Tacke[i].z-Fpz;
    double m=mx*Fvx+mz*Fvz;
    Tacke[i].nx=(mx*Fvz-mz*Fvx)/Fvsxz;
    Tacke[i].ny=my*Fvsxz-m*Fvy/Fvsxz;
    Tacke[i].nz=my*Fvy+m;
  }
}

void MojProzor::projektuj(int i)
{
  if(Tacke[i].nz>-Fe)
  {
    Tacke[i].px=c_projekcija(Tacke[i].nx,Tacke[i].nz);
    Tacke[i].py=c_projekcija(Tacke[i].ny,Tacke[i].nz);
  }
}

void MojProzor::normalizuj_projektuj_iscrtaj(void)
{
  for(int i=0;i<(Unos_tacaka?Bafer+1:Broj_tacaka);i++)
  {
    normalizuj(i);
    projektuj(i);
  }
  iscrtaj();
}

void MojProzor::uradi_rotaciju(void)
{
  double u;
  if(MojDijalog_ugao(this,&u).Execute()==IDOK)
  {
    u=u*M_PI/180.0;
    double cu=cos(u);
    double su=sin(u);
    double vx=Tacke[Bafer-1].x-Tacke[Bafer-2].x;
    double vy=Tacke[Bafer-1].y-Tacke[Bafer-2].y;
    double vz=Tacke[Bafer-1].z-Tacke[Bafer-2].z;
    double a=sqrt(vx*vx+vy*vy+vz*vz);
    vx/=a;
    vy/=a;
    vz/=a;
    double vsxz=sqrt(vx*vx+vz*vz);
    for(int i=TACAKA_OSE;i<(Unos_tacaka?Bafer+1:Broj_tacaka);i++)
    {
      double rx;
      double ry;
      double rz;
      if(vsxz==0.0)
      {
        rx=Tacke[i].x-Tacke[Bafer-2].x;
        ry=Tacke[Bafer-2].z-Tacke[i].z;
        rz=Tacke[i].y-Tacke[Bafer-2].y;
      }
      else
      {
        double mx=Tacke[i].x-Tacke[Bafer-2].x;
        double my=Tacke[i].y-Tacke[Bafer-2].y;
        double mz=Tacke[i].z-Tacke[Bafer-2].z;
        double m=mx*vx+mz*vz;
        rx=(mx*vz-mz*vx)/vsxz;
        ry=my*vsxz-m*vy/vsxz;
        rz=my*vy+m;
      }
      double t=cu*rx-su*ry;
      ry=su*rx+cu*ry;
      rx=t;
      if(vsxz==0.0)
      {
        Tacke[i].x=rx+Tacke[Bafer-2].x;
        Tacke[i].y=Tacke[Bafer-2].y-ry;
        Tacke[i].z=rz+Tacke[Bafer-2].z;
      }
      else
      {
        double m=rz*vsxz-ry*vy;
        Tacke[i].x=(vx*m+rx*vz)/vsxz+Tacke[Bafer-2].x;
        Tacke[i].y=ry*vsxz+rz*vy+Tacke[Bafer-2].y;
        Tacke[i].z=(vz*m-rx*vx)/vsxz+Tacke[Bafer-2].z;
      }
      normalizuj(i);
      projektuj(i);
    }
  }
  Prljavo=true;
  iscrtaj();
}

void MojProzor::uradi_translaciju(void)
{
  double bx=Tacke[Bafer-1].x-Tacke[Bafer-2].x;
  double by=Tacke[Bafer-1].y-Tacke[Bafer-2].y;
  double bz=Tacke[Bafer-1].z-Tacke[Bafer-2].z;
  for(int i=TACAKA_OSE;i<Broj_tacaka;i++)
  {
    Tacke[i].x+=bx;
    Tacke[i].y+=by;
    Tacke[i].z+=bz;
    normalizuj(i);
    projektuj(i);
  }
  Prljavo=true;
  iscrtaj();
}

void MojProzor::uradi_pogled(void)
{
  Fpx=Tacke[Bafer-2].x;
  Fpy=Tacke[Bafer-2].y;
  Fpz=Tacke[Bafer-2].z;
  Fvx=Tacke[Bafer-1].x-Fpx;
  Fvy=Tacke[Bafer-1].y-Fpy;
  Fvz=Tacke[Bafer-1].z-Fpz;
  double a=sqrt(Fvx*Fvx+Fvy*Fvy+Fvz*Fvz);
  Fvx/=a;
  Fvy/=a;
  Fvz/=a;
  Fvsxz=sqrt(Fvx*Fvx+Fvz*Fvz);
  normalizuj_projektuj_iscrtaj();
}

void MojProzor::uradi_unos(void)
{

  TChooseColorDialog::TData izbor;
  static TColor boje[16]=
  {
    0x010101l,0x101010l,0x202020l,0x303030l,
    0x404040l,0x505050l,0x606060l,0x707070l,
    0x808080l,0x909090l,0xA0A0A0l,0xB0B0B0l,
    0xC0C0C0l,0xD0D0D0l,0xE0E0E0l,0xF0F0F0l
  };
  static TColor boja=TColor::Black;
  izbor.Flags=CC_RGBINIT;
  izbor.Color=boja;
  izbor.CustColors=boje;
  if(TChooseColorDialog(this,izbor,0,"Izbor Boje").Execute()==IDOK)
  {
    Prljavo=true;
    Pljosni[Broj_pljosni].p=Broj_temena;
    Pljosni[Broj_pljosni].cr=izbor.Color.Red();
    Pljosni[Broj_pljosni].cg=izbor.Color.Green();
    Pljosni[Broj_pljosni].cb=izbor.Color.Blue();
    for(int i=Broj_tacaka;i<Bafer;i++)
    {
      int k=TACAKA_OSE;
      while(k<Broj_tacaka&&(Tacke[i].x!=Tacke[k].x||Tacke[i].y!=Tacke[k].y||Tacke[i].z!=Tacke[k].z))
        k++;
      Temena[Broj_temena++]=k;
      if(k==Broj_tacaka&&i!=Broj_tacaka)
      {
        Tacke[Broj_tacaka].x=Tacke[i].x;
        Tacke[Broj_tacaka].y=Tacke[i].y;
        Tacke[Broj_tacaka].z=Tacke[i].z;
        Tacke[Broj_tacaka].nx=Tacke[i].nx;
        Tacke[Broj_tacaka].ny=Tacke[i].ny;
        Tacke[Broj_tacaka].nz=Tacke[i].nz;
        Tacke[Broj_tacaka].px=Tacke[i].px;
        Tacke[Broj_tacaka].py=Tacke[i].py;
      }
      Broj_tacaka++;
    }
    Pljosni[Broj_pljosni++].k=Broj_temena;
  }
  iscrtaj();
}

void MojProzor::ubaci_u_bafer(double x,double y,double z)
{
  Tacke[Bafer].x=x;
  Tacke[Bafer].y=y;
  Tacke[Bafer].z=z;
  normalizuj(Bafer);
  projektuj(Bafer);
  static char str[33];
  sprintf(str,"%d (%-.2lf,%-.2lf,%-.2lf)",Unos_tacaka,x,y,z);
  TextGadget->SetText(str);
}

void MojProzor::zahtevaj_unos_tacaka(int i)
{
  if(Broj_tacaka+i>MAX_BROJ_TACAKA)
    MessageBox("Nema dovoljno memorije !","Greska",IDOK);
  else
  {
    if(Unos_tacaka)
      MessageBox("Prekidam prethodno trazeni posao !","Upozorenje",MB_OK);
    Unos_tacaka=i;
    if(i)
    {
      Bafer=Broj_tacaka;
      ubaci_u_bafer(1.0,1.0,1.0);
    }
  }
}

bool MojProzor::CanClose(void)
{
  return MessageBox("Stvarno izlazis ?","Izlazak",MB_YESNO|MB_ICONQUESTION)==IDYES;
}

void MojProzor::EvLButtonDown(uint,TPoint &p)
{
  if(Unos_tacaka)
  {
    double x=Tacke[Bafer].x;
    double y=Tacke[Bafer].y;
    double z=Tacke[Bafer].z;
    if(p.y<(Maxy>>1))
    {
      y=(Dmaxy2-(double)(p.y<<1))/Fs;
      if(p.x<(Maxx>>1))
        x=((double)(p.x<<1)-Dmaxx2)/Fs;
      else
        z=((double)(p.x<<1)-Dmaxx-Dmaxx2)/Fs;
    }
    else
      if(p.x<(Maxx>>1))
      {
        x=((double)(p.x<<1)-Dmaxx2)/Fs;
        z=(Dmaxy+Dmaxy2-(double)(p.y<<1))/Fs;
      }
      else
        MessageBeep(MB_OK);
    if(Magnet)
    {
      x=((double)(int)(x*2.0+(x>=0?0.5:-0.5)))/2;
      y=((double)(int)(y*2.0+(y>=0?0.5:-0.5)))/2;
      z=((double)(int)(z*2.0+(z>=0?0.5:-0.5)))/2;
    }
    ubaci_u_bafer(x,y,z);
    iscrtaj();
  }
}

void MojProzor::EvRButtonDown(uint,TPoint&)
{
  if(Unos_tacaka)
    Cm_sledeca_tacka();
}

void MojProzor::EvSize(uint SizeType,TSize &Size)
{
  TWindow::EvSize(SizeType,Size);
  Maxx=Size.cx-1;
  Maxy=Size.cy-1;
  Dmaxx=(double)Maxx;
  Dmaxy=(double)Maxy;
  Dmaxx2=Dmaxx/2.0;
  Dmaxy2=Dmaxy/2.0;
  iscrtaj();
}

void MojProzor::Paint(TDC &dc,bool,TRect&)
{
  dc.SetROP2(R2_COPYPEN);
  dc.SetDIBitsToDevice(TRect(0,0,Smaxx,Smaxy),TPoint(0,0),*Dib);
}

void MojProzor::Cm_novi(void)
{
  zahtevaj_unos_tacaka(0);
  Broj_tacaka=TACAKA_OSE;
  Broj_temena=0;
  Broj_pljosni=0;
  *Ime_fajla='\0';
  Prljavo=false;
  iscrtaj();
}

void MojProzor::Cm_otvori(void)
{
  zahtevaj_unos_tacaka(0);
  static TOpenSaveDialog::TData data(OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_NOREADONLYRETURN,"3D Fajlovi (*.3D)|*.3d|",0,"","3D");
  if(TFileOpenDialog(this,data).Execute()==IDOK)
  {
    int f;
    char ime[MAXPATH];
    static char poruka[128];
    TOpenSaveDialog::GetFileTitle(data.FileName,ime,MAXPATH);
    if((AGLA_file=fopen(ime,"r"))==NULL)
    {
      MessageBox("Ne mogu otvoriti tu datoteku !","Greska",MB_OK);
      f=2;
    }
    else
    {
      AGLA_new_nl=1;
      AGLA_new_pos=1;
      Broj_tacaka=TACAKA_OSE;
      Broj_temena=0;
      Broj_pljosni=0;
      f=AGSA_parser();
      fclose(AGLA_file);
    }
    switch(f)
    {
      case 0:
        normalizuj_projektuj_iscrtaj();
        strcpy(Ime_fajla,ime);
        Prljavo=false;
        break;
      case 1:
        sprintf(poruka,"Red %d, slovo %d :\n%s !",AGLA_old_nl,AGLA_old_pos,AGLA_error);
        MessageBox(poruka,"Greska",MB_OK);
        Cm_novi();
    }
  }
}

void MojProzor::Cm_snimi(void)
{
  zahtevaj_unos_tacaka(0);
  if(*Ime_fajla)
  {
    if(snimi(Ime_fajla))
      Prljavo=false;
  }
  else
    Cm_snimi_kao();
}

void MojProzor::Cm_snimi_kao(void)
{
  zahtevaj_unos_tacaka(0);
  static TOpenSaveDialog::TData data(OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_NOREADONLYRETURN,"3D Fajlovi (*.3D)|*.3d|",0,"","3D");
  if(TFileSaveDialog(this,data).Execute()==IDOK)
  {
    char ime[MAXPATH];
    TOpenSaveDialog::GetFileTitle(data.FileName,ime,MAXPATH);
    if(snimi(ime))
    {
      strcpy(Ime_fajla,ime);
      Prljavo=false;
    }
  }
}

void MojProzor::Cm_rotacija_x(void)
{
  double u;
  if(MojDijalog_ugao(this,&u).Execute()==IDOK)
  {
    u=u*M_PI/180.0;
    double cu=cos(u);
    double su=sin(u);
    for(int i=TACAKA_OSE;i<(Unos_tacaka?Bafer+1:Broj_tacaka);i++)
    {
      double t=su*Tacke[i].z+cu*Tacke[i].y;
      Tacke[i].z=cu*Tacke[i].z-su*Tacke[i].y;
      Tacke[i].y=t;
      normalizuj(i);
      projektuj(i);
    }
    Prljavo=true;
    iscrtaj();
  }
}

void MojProzor::Cm_rotacija_y(void)
{
  double u;
  if(MojDijalog_ugao(this,&u).Execute()==IDOK)
  {
    u=u*M_PI/180.0;
    double cu=cos(u);
    double su=sin(u);
    for(int i=TACAKA_OSE;i<(Unos_tacaka?Bafer+1:Broj_tacaka);i++)
    {
      double t=cu*Tacke[i].x-su*Tacke[i].z;
      Tacke[i].z=su*Tacke[i].x+cu*Tacke[i].z;
      Tacke[i].x=t;
      normalizuj(i);
      projektuj(i);
    }
    Prljavo=true;
    iscrtaj();
  }
}

void MojProzor::Cm_rotacija_z(void)
{
  double u;
  if(MojDijalog_ugao(this,&u).Execute()==IDOK)
  {
    u=u*M_PI/180.0;
    double cu=cos(u);
    double su=sin(u);
    for(int i=TACAKA_OSE;i<(Unos_tacaka?Bafer+1:Broj_tacaka);i++)
    {
      double t=cu*Tacke[i].x-su*Tacke[i].y;
      Tacke[i].y=su*Tacke[i].x+cu*Tacke[i].y;
      Tacke[i].x=t;
      normalizuj(i);
      projektuj(i);
    }
    Prljavo=true;
    iscrtaj();
  }
}

void MojProzor::Cm_rotacija_p(void)
{
  zahtevaj_unos_tacaka(2);
  Sta_radim=RADI_ROTACIJU;
  iscrtaj();
}

void MojProzor::Cm_translacija(void)
{
  zahtevaj_unos_tacaka(2);
  Sta_radim=RADI_TRANSLACIJU;
  iscrtaj();
}

void MojProzor::Cm_skaliranje(void)
{
  double s;
  if(MojDijalog_skala(this,&s).Execute()==IDOK)
  {
    for(int i=TACAKA_OSE;i<(Unos_tacaka?Bafer+1:Broj_tacaka);i++)
    {
      Tacke[i].x*=s;
      Tacke[i].y*=s;
      Tacke[i].z*=s;
      normalizuj(i);
      projektuj(i);
    }
    Prljavo=true;
    iscrtaj();
  }
}

void MojProzor::Cm_zicani(void)
{
  zahtevaj_unos_tacaka(0);
  Model=ZICANI;
  iscrtaj();
}

void MojProzor::Cm_pljosni(void)
{
  zahtevaj_unos_tacaka(0);
  Model=PLJOSNI;
  iscrtaj();
}

void MojProzor::Cm_svetlo(void)
{
  zahtevaj_unos_tacaka(1);
  Sta_radim=RADI_SVETLO;
  iscrtaj();
}

void MojProzor::Cm_centralna(void)
{
  if(Projekcija!=CENTRALNA)
  {
    Projekcija=CENTRALNA;
    iscrtaj();
  }
}

void MojProzor::Cm_paralelna(void)
{
  if(Projekcija!=PARALELNA)
  {
    Projekcija=PARALELNA;
    iscrtaj();
  }
}

void MojProzor::Cm_osa(void)
{
  Osa=!Osa;
  iscrtaj();
}

void MojProzor::Cm_pogled(void)
{
  zahtevaj_unos_tacaka(2);
  Sta_radim=RADI_POGLED;
  iscrtaj();
}

void MojProzor::Cm_zoom(void)
{
  if(MojDijalog_zoom(this,&Fs).Execute()==IDOK)
    iscrtaj();
}

void MojProzor::Cm_rastojanje_oka(void)
{
  if(MojDijalog_oko(this,&Fo).Execute()==IDOK)
  {
    Fe=Fo*0.99;
    for(int i=0;i<(Unos_tacaka?Bafer:Broj_tacaka);i++)
      projektuj(i);
    iscrtaj();
  }
}

void MojProzor::Cm_unos_pljosni(void)
{
  int t;
  if(MojDijalog_teme(this,&t).Execute()==IDOK)
    if(Broj_pljosni==MAX_BROJ_PLJOSNI||Broj_temena+t>MAX_BROJ_TEMENA)
      MessageBox("Nemam dovoljno memorije\nza novu pljosan !","Greska",MB_OK);
    else
    {
      zahtevaj_unos_tacaka(t);
      Sta_radim=RADI_UNOS;
      iscrtaj();
    }
}

void MojProzor::Cm_magnet(void)
{
  Magnet=!Magnet;
}

void MojProzor::Cm_unos_tacke(void)
{
  double x=Tacke[Bafer].x;
  double y=Tacke[Bafer].y;
  double z=Tacke[Bafer].z;
  if(MojDijalog_tacka(this,&x,&y,&z).Execute()==IDOK)
  {
    ubaci_u_bafer(x,y,z);
    iscrtaj();
  }
}

void MojProzor::Cm_sledeca_tacka(void)
{
  bool prolaz;
  static double a;
  static double b;
  static double c;
  double w;
  switch(Bafer-Broj_tacaka)
  {
    case 0:
      prolaz=true;
      break;
    case 1:
      prolaz=Tacke[Bafer-1].x!=Tacke[Bafer].x||Tacke[Bafer-1].y!=Tacke[Bafer].y||Tacke[Bafer-1].z!=Tacke[Bafer].z;
      break;
    case 2:
      a=(Tacke[Bafer-1].y-Tacke[Bafer-2].y)*(Tacke[Bafer].z-Tacke[Bafer-2].z)-(Tacke[Bafer-1].z-Tacke[Bafer-2].z)*(Tacke[Bafer].y-Tacke[Bafer-2].y);
      b=(Tacke[Bafer-1].z-Tacke[Bafer-2].z)*(Tacke[Bafer].x-Tacke[Bafer-2].x)-(Tacke[Bafer-1].x-Tacke[Bafer-2].x)*(Tacke[Bafer].z-Tacke[Bafer-2].z);
      c=(Tacke[Bafer-1].x-Tacke[Bafer-2].x)*(Tacke[Bafer].y-Tacke[Bafer-2].y)-(Tacke[Bafer-1].y-Tacke[Bafer-2].y)*(Tacke[Bafer].x-Tacke[Bafer-2].x);
      w=sqrt(a*a+b*b+c*c);
      prolaz=w>0.0;
      if(prolaz)
      {
        a/=w;
        b/=w;
        c/=w;
      }
      break;
    default:
      prolaz=true;
      w=(Tacke[Bafer].x-Tacke[Broj_tacaka].x)*a+(Tacke[Bafer].y-Tacke[Broj_tacaka].y)*b+(Tacke[Bafer].z-Tacke[Broj_tacaka].z)*c;
      Tacke[Bafer].x-=w*a;
      Tacke[Bafer].y-=w*b;
      Tacke[Bafer].z-=w*c;
  }
  if(prolaz)
  {
    Bafer++;
    Unos_tacaka--;
    if(Unos_tacaka)
    {
      ubaci_u_bafer(Tacke[Bafer-1].x,Tacke[Bafer-1].y,Tacke[Bafer-1].z);
      iscrtaj();
    }
    else
    {
      TextGadget->SetText("");
      switch(Sta_radim)
      {
        case RADI_ROTACIJU:
          uradi_rotaciju();
          break;
        case RADI_TRANSLACIJU:
          uradi_translaciju();
          break;
        case RADI_SVETLO:
          Tacke[4].x=Tacke[Bafer-1].x;
          Tacke[4].y=Tacke[Bafer-1].y;
          Tacke[4].z=Tacke[Bafer-1].z;
          normalizuj(4);
          Model=SVETLO;
          iscrtaj();
          break;
        case RADI_POGLED:
          uradi_pogled();
          break;
        case RADI_UNOS:
          uradi_unos();
      }
    }
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
      TTextGadget *tg=new TTextGadget(0,TGadget::Embossed,TTextGadget::Center,15);
      TDecoratedMDIFrame *frame=new TDecoratedMDIFrame("Grafika 3D",TResId("Komanda"),*new MojProzor(tg),true);
      TStatusBar *sb=new TStatusBar(frame);
      sb->Insert(*tg);
      TControlBar *cb=new TControlBar(frame);
      cb->Insert(*new TButtonGadget(CM_EXIT,CM_EXIT));
      cb->Insert(*new TSeparatorGadget);
      cb->Insert(*new TButtonGadget(RC_novi,RC_novi));
      cb->Insert(*new TButtonGadget(RC_otvori,RC_otvori));
      cb->Insert(*new TButtonGadget(RC_snimi,RC_snimi));
      cb->Insert(*new TButtonGadget(RC_snimi_kao,RC_snimi_kao));
      cb->Insert(*new TSeparatorGadget);
      cb->Insert(*new TButtonGadget(RC_rotacija_x,RC_rotacija_x));
      cb->Insert(*new TButtonGadget(RC_rotacija_y,RC_rotacija_y));
      cb->Insert(*new TButtonGadget(RC_rotacija_z,RC_rotacija_z));
      cb->Insert(*new TButtonGadget(RC_rotacija_p,RC_rotacija_p));
      cb->Insert(*new TButtonGadget(RC_translacija,RC_translacija));
      cb->Insert(*new TButtonGadget(RC_skaliranje,RC_skaliranje));
      cb->Insert(*new TSeparatorGadget);
      cb->Insert(*new TButtonGadget(RC_zicani,RC_zicani));
      cb->Insert(*new TButtonGadget(RC_pljosni,RC_pljosni));
      cb->Insert(*new TButtonGadget(RC_svetlo,RC_svetlo));
      cb->Insert(*new TSeparatorGadget);
      cb->Insert(*new TButtonGadget(RC_centralna,RC_centralna));
      cb->Insert(*new TButtonGadget(RC_paralelna,RC_paralelna));
      cb->Insert(*new TSeparatorGadget);
      cb->Insert(*new TButtonGadget(RC_osa,RC_osa));
      cb->Insert(*new TSeparatorGadget);
      cb->Insert(*new TButtonGadget(RC_pogled,RC_pogled));
      cb->Insert(*new TButtonGadget(RC_zoom,RC_zoom));
      cb->Insert(*new TButtonGadget(RC_rastojanje_oka,RC_rastojanje_oka));
      cb->Insert(*new TSeparatorGadget);
      cb->Insert(*new TButtonGadget(RC_unos_pljosni,RC_unos_pljosni));
      cb->Insert(*new TSeparatorGadget);
      cb->Insert(*new TButtonGadget(RC_magnet,RC_magnet));
      cb->Insert(*new TSeparatorGadget);
      cb->Insert(*new TButtonGadget(RC_unos_tacke,RC_unos_tacke));
      cb->Insert(*new TButtonGadget(RC_sledeca_tacka,RC_sledeca_tacka));
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
