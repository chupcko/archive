#include "setof.h"

void _SO_ubaci_sve(long l,unsigned char *x)
{
  int i;
  for(i=0;i<l;i++)
    x[i]=(unsigned char)~0;
}

void _SO_izbaci_sve(long l,unsigned char *x)
{
  int i;
  for(i=0;i<l;i++)
    x[i]=(unsigned char)0;
}

void _SO_unija(long l,unsigned char *d,unsigned char *s)
{
  int i;
  for(i=0;i<l;i++)
    d[i]|=s[i];
}

void _SO_presek(long l,unsigned char *d,unsigned char *s)
{
  int i;
  for(i=0;i<l;i++)
    d[i]&=s[i];
}

void _SO_razlika(long l,unsigned char *d,unsigned char *s)
{
  int i;
  for(i=0;i<l;i++)
    d[i]&=~s[i];
}

void _SO_komplement(long l,unsigned char *x)
{
  int i;
  for(i=0;i<l;i++)
    x[i]=~x[i];
}

int _SO_podskup(long l,unsigned char *d,unsigned char *s)
{
  int n;
  int i;
  n=1;
  for(i=0;n&&i<l;i++)
    n=!(int)(~d[i]&s[i]);
  return n;
}

int _SO_disjunktni(long l,unsigned char *d,unsigned char *s)
{
  int n;
  int i;
  n=1;
  for(i=0;n&&i<l;i++)
    n=!(int)(d[i]&s[i]);
  return n;
}

int _SO_jednaki(long l,unsigned char *d,unsigned char *s)
{
  int n;
  int i;
  n=1;
  for(i=0;n&&i<l;i++)
    n=(int)(d[i]==s[i]);
  return n;
}

int _SO_prazan_skup(long l,unsigned char *x)
{
  int n;
  int i;
  n=1;
  for(i=0;n&&i<l;i++)
    n=!(int)x[i];
  return n;
}

void _SO_dodeli(long l,unsigned char *d,unsigned char *s)
{
  int i;
  for(i=0;i<l;i++)
    d[i]=s[i];
}

void SO_ubaci(unsigned char *x,int n)
{
  x[n/CHAR_BIT]|=1u<<n%CHAR_BIT;
}

void SO_izbaci(unsigned char *x,int n)
{
  x[n/CHAR_BIT]&=~(1u<<n%CHAR_BIT);
}

int SO_element(unsigned char *x,int n)
{
  return x[n/CHAR_BIT]&(1u<<n%CHAR_BIT);
}
