#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "md5.h"
#include "crc.h"
#include "info.h"

void info(char *s)
{
  struct stat stf;
  if(lstat(s,&stf))
    printf("r %s\n",s);
  else
  {
    if(NePisiDatum)
      stf.st_ctime=0;
    if(S_ISDIR(stf.st_mode))
    {
      DIR *dir;
      if((dir=opendir(s))==NULL)
        fprintf(stderr,"Ne mogu otvoriti direktorijum: %s\n",s);
      else
      {
        long n;
        n=0l;
        while(readdir(dir)!=NULL)
          n++;
        closedir(dir);
        printf
        (
          "d %07o %hu %hu %ld %ld %s\n",
          stf.st_mode,
          stf.st_uid,
          stf.st_gid,
          stf.st_ctime,
          n,
          s
        );
      }
    }
    else if(S_ISLNK(stf.st_mode))
    {
      char buf[MAXNL];
      int bs;
      bs=readlink(s,buf,MAXNL);
      buf[bs<MAXNL?bs:(MAXNL-1)]='\0';
      printf
      (
        "l %07o %hu %hu %ld %s %s\n",
        stf.st_mode,
        stf.st_uid,
        stf.st_gid,
        stf.st_ctime,
        buf,
        s
      );
    }
    else if(S_ISBLK(stf.st_mode))
      printf
      (
        "b %07o %hu %hu %04x %ld %s\n",
        stf.st_mode,
        stf.st_uid,
        stf.st_gid,
        stf.st_rdev,
        stf.st_ctime,
        s
      );
    else if(S_ISCHR(stf.st_mode))
      printf
      (
        "c %07o %hu %hu %04x %ld %s\n",
        stf.st_mode,
        stf.st_uid,
        stf.st_gid,
        stf.st_rdev,
        stf.st_ctime,
        s
      );
    else if(S_ISREG(stf.st_mode))
    {
      int fp;
      if((fp=open(s,O_RDONLY))==-1)
        fprintf(stderr,"Ne mogu otvoriti datoteku: %s\n",s);
      else
      {
        unsigned char d[16];
        unsigned char buf[MAXNL];
        MD5_CTX md5c;
        CRC_CTX crcc;
        int n;
        MD5Init(&md5c);
        CRCInit(&crcc);
        while((n=read(fp,buf,MAXNL))>0)
        {
          MD5Update(&md5c,buf,n);
          CRCUpdate(&crcc,buf,n);
        }
        close(fp);
        printf
        (
          "f %07o %hu %hu %ld %ld %lu ",
          stf.st_mode,
          stf.st_uid,
          stf.st_gid,
          stf.st_size,
          stf.st_ctime,
          CRCFinal(&crcc)
        );
        MD5Final(d,&md5c);
        for(n=0;n<16;n++)
          printf("%02x",(int)d[n]);
        printf(" %s\n",s);
      }
    }
    else
      printf
      (
        "n %07o %hu %hu %04x %ld %s\n",
        stf.st_mode,
        stf.st_uid,
        stf.st_gid,
        stf.st_rdev,
        stf.st_ctime,
        s
      );
  }
}
