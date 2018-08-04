#ifndef CRC_H
#define CRC_H

typedef struct
{
  unsigned long crc;
  long len;
} CRC_CTX;

void CRCInit(CRC_CTX *);
void CRCUpdate(CRC_CTX *,unsigned char *,long);
unsigned long CRCFinal(CRC_CTX *);

#endif
