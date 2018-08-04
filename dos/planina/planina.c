#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "planina.h"

static char Class[32]="Planina";

typedef struct
{
  RECT Oblast;
  struct
  {
    int x;
    int y;
  } Tac[8385];
  struct
  {
    int p;
    int k;
    int l;
  } Lin[24768];
  int Blin;
} Extra_podaci;

#define EXTRA_DATA_OFFSET 0

#define BROJ_ITERACIJA 7

int rnd(int r)
{
  return r?rand()%(r<<1)-r:0;
}

void pripremi(Extra_podaci *e)
{
  static int tro[16384][3];
  int btro=0;
  int btac=2;
  int r=(e->Oblast.right-e->Oblast.left)>>4;
  int i;
  e->Blin=2;
  for(i=0;i<3;i++)
  {
    e->Lin[i].p=i;
    e->Lin[i].k=(i+1)%3;
    tro[0][i]=i;
  }
  e->Tac[0].x=e->Oblast.left+r;
  e->Tac[0].y=e->Oblast.bottom-(r<<1);
  e->Tac[1].x=e->Oblast.right-r;
  e->Tac[1].y=e->Tac[0].y;
  e->Tac[2].x=(e->Tac[0].x+e->Tac[1].x)>>1;
  e->Tac[2].y=e->Oblast.top+r;
  srand((unsigned int)time(NULL));
  for(i=0;i<BROJ_ITERACIJA;i++)
  {
    int broj=e->Blin;
    int j;
    for(j=0;j<=broj;j++)
    {
      btac++;
      e->Tac[btac].x=((e->Tac[e->Lin[j].p].x+e->Tac[e->Lin[j].k].x)>>1)+rnd(r);
      e->Tac[btac].y=((e->Tac[e->Lin[j].p].y+e->Tac[e->Lin[j].k].y)>>1)+rnd(r);
      e->Blin++;
      e->Lin[e->Blin].p=btac;
      e->Lin[e->Blin].k=e->Lin[j].k;
      e->Lin[j].k=btac;
      e->Lin[j].l=e->Blin;
    }
    r>>=1;
    broj=btro;
    for(j=0;j<=broj;j++)
    {
      int m;
      for(m=0;m<3;m++)
      {
        e->Blin++;
        e->Lin[e->Blin].p=e->Lin[tro[j][m]].k,
        e->Lin[e->Blin].k=e->Lin[tro[j][(m+2)%3]].k;
        btro++;
        tro[btro][0]=tro[j][m];
        tro[btro][1]=e->Blin;
        tro[btro][2]=e->Lin[tro[j][(m+2)%3]].l;
      }
      for(m=0;m<3;m++)
        tro[j][m]=e->Blin-m;
    }
  }
}

LONG _EXPORT FAR PASCAL WindowProc(HWND hwnd,unsigned msg,WORD wparam,LONG lparam)
{
  Extra_podaci *e;
  HDC hdc;
  PAINTSTRUCT ps;
  int i;
  switch(msg)
  {
    case WM_COMMAND:
      if(wparam==MENU_ITEM)
      {
        e=(Extra_podaci*)GetWindowLong(hwnd,EXTRA_DATA_OFFSET);
        pripremi(e);
        InvalidateRect(hwnd,&e->Oblast,TRUE);
      }
      break;
    case WM_SIZE:
      e=(Extra_podaci*)GetWindowLong(hwnd,EXTRA_DATA_OFFSET);
      GetClientRect(hwnd,&e->Oblast);
      pripremi(e);
      InvalidateRect(hwnd,&e->Oblast,TRUE);
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    case WM_PAINT:
      e=(Extra_podaci*)GetWindowLong(hwnd,EXTRA_DATA_OFFSET);
      hdc=BeginPaint(hwnd,&ps);
      for(i=0;i<=e->Blin;i++)
      {
        MoveTo(hdc,e->Tac[e->Lin[i].p].x,e->Tac[e->Lin[i].p].y);
        LineTo(hdc,e->Tac[e->Lin[i].k].x,e->Tac[e->Lin[i].k].y);
      }
      EndPaint(hwnd,&ps);
      break;
    default:
      return DefWindowProc(hwnd,msg,wparam,lparam);
  }
  return 0L;
}

static BOOL FirstInstance(HANDLE this_inst)
{
  WNDCLASS wc;
  wc.style=CS_HREDRAW|CS_VREDRAW;
  wc.lpfnWndProc=(LPVOID)WindowProc;
  wc.cbClsExtra=0;
  wc.cbWndExtra=sizeof(DWORD);
  wc.hInstance=this_inst;
  wc.hIcon=LoadIcon(this_inst,"Ikona");
  wc.hCursor=LoadCursor(NULL,IDC_ARROW);
  wc.hbrBackground=GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName="Meni";
  wc.lpszClassName=Class;
  return RegisterClass(&wc);
}

static BOOL AnyInstance(HANDLE this_inst,int cmdshow)
{
  HWND hwnd;
  Extra_podaci *e;
  hwnd=CreateWindow(
    Class,
    "Chupcko WIN-16 program u WATCOM-u",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    NULL,
    NULL,
    this_inst,
    NULL
  );
  if(!hwnd)
    return FALSE;
  if((e=malloc(sizeof(Extra_podaci)))==NULL)
    return FALSE;
  GetClientRect(hwnd,&e->Oblast);
  SetWindowLong(hwnd,EXTRA_DATA_OFFSET,(DWORD)e);
  ShowWindow(hwnd,cmdshow);
  UpdateWindow(hwnd);
  return TRUE;
}

int PASCAL WinMain(HANDLE this_inst,HANDLE prev_inst,LPSTR cmdline,int cmdshow)
{
  MSG msg;
  prev_inst=prev_inst;
  cmdline=cmdline;
  sprintf(Class,"Proba%d",this_inst);
  if(!FirstInstance(this_inst))
    return FALSE;
  if(!AnyInstance(this_inst,cmdshow))
    return FALSE;
  while(GetMessage(&msg,NULL,NULL,NULL))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}
