#include <stdio.h>
#include <stdlib.h>

#define DUZINA 128

long int Stek[DUZINA];
int Brojac=0;

int f_ispis(void)
{
  printf("Rezultat je : 0%lo %ld 0x%lX\n",Stek[0],Stek[0],Stek[0]);
  return 0;
}

int f_plus(void)
{
  Brojac--;
  Stek[Brojac-1]+=Stek[Brojac];
  return 0;
}

int f_minus(void)
{
  Brojac--;
  Stek[Brojac-1]-=Stek[Brojac];
  return 0;
}

int f_puta(void)
{
  Brojac--;
  Stek[Brojac-1]*=Stek[Brojac];
  return 0;
}

int f_podeljeno(void)
{
  Brojac--;
  Stek[Brojac-1]/=Stek[Brojac];
  return 0;
}

int f_u_minus(void)
{
  Stek[Brojac]=-Stek[Brojac];
  return 0;
}

int smesti(long int l)
{
  if(Brojac==DUZINA)
  {
    AGLA_error="Nema mesta na steku";
    return 1;
  }
  Stek[Brojac]=l;
  Brojac++;
  return 0;
}

int f_oct_broj(void)
{
  long int l;
  sscanf(AGLA_value+1,"%lo",&l);
  return smesti(l);
}

int f_dec_broj(void)
{
  return smesti(atol(AGLA_value));
}

int f_hex_broj(void)
{
  long int l;
  sscanf(AGLA_value+2,"%lx",&l);
  return smesti(l);
}
