
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "info.h"

void help(void)
{
  fputs
  (
    "\n"
    "CHPchk -h | {ime | -f datoteka}\n"
    "\n"
    "\t-h\tispisuje ovo upustvo\n"
    "\t-f D\tproverava datoteke zapisane u datoteci D\n"
    "\t-d\tne ispisuje datum (ispise 0)\n"
    "\t-D\tponovo ispisuje datum\n"
    "\n"
    "Napisao: Goran \"CHUPCKO\" Lazic, koji ne snosi nikakvu odgovornost\n"
    "povodom eventualno nastalih problema u radu.\n"
    "\n",
    stderr
  );
  exit(1);
}

void info_file(FILE *fp,char *s)
{
  char buf[MAXNL];
  int c;
  int r=0;
  do
  {
    int n=0;
    while((c=fgetc(fp))!='\n'&&c!=EOF&&n<MAXNL)
      buf[n++]=(char)c;
    if(n==MAXNL)
    {
      fprintf(stderr,"Red %d datoteke %s je predugacak\n",r,s);
      while((c=fgetc(fp))!='\n'&&c!=EOF);
    }
    else
      if(n)
      {
        buf[n]='\0';
        info(buf);
      }
    r++;
  }
  while(c!=EOF);
}

int main(int argc,char *argv[])
{
  int n;
  NePisiDatum=0;
  puts("CHPchk 0.03");
  if(argc==1)
    info_file(stdin,"stdin");
  for(n=1;n<argc;n++)
    if(argv[n][0]=='-')
      if(argv[n][1]=='f')
        if(++n<argc)
          if(strcmp(argv[n],"-"))
          {
            FILE *fp;
            if((fp=fopen(argv[n],"r"))==NULL)
              fprintf(stderr,"Ne mogu otvoriti datoteku %s sa spiskom\n",argv[n]);
            else
            {
              info_file(fp,argv[n]);
              fclose(fp);
            }
          }
          else
            info_file(stdin,"stdin");
        else
          fputs("Posle -f treba da dodje ime datoteke\n",stderr);
      else if(argv[n][1]=='d')
        NePisiDatum=1;
      else if(argv[n][1]=='D')
        NePisiDatum=0;
      else if(argv[n][1]=='-')
      {
        n++;
        break;
      }
      else
        help();
    else
      info(argv[n]);
  while(n<argc)
    info(argv[n++]);
  return 0;
}
