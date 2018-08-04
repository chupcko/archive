#include "crc.h"
#include "crct.h"

void CRCInit(CRC_CTX *c)
{
  c->crc=0;
  c->len=0;
}

void CRCUpdate(CRC_CTX *c,unsigned char *buf,long n)
{
  unsigned char *cp=buf;
  c->len+=n;
  while(n--)
    c->crc=(c->crc<<8)^CRCTable[((c->crc>>24)^*(cp++))&0xFF];
}

unsigned long CRCFinal(CRC_CTX *c)
{
  while(c->len>0)
  {
    c->crc=(c->crc<<8)^CRCTable[((c->crc>>24)^c->len)&0xFF];
    c->len>>=8;
  }
  return ~c->crc;
}
