#ifndef AZOT_setof
#define AZOT_setof

#include <limits.h>

#define SO_tip_def(a,b) typedef unsigned char SO_tip_##a[(b-1)/CHAR_BIT+1]

void _SO_ubaci_sve(long,unsigned char *);
void _SO_izbaci_sve(long,unsigned char *);
void _SO_unija(long,unsigned char *,unsigned char *);
void _SO_presek(long,unsigned char *,unsigned char *);
void _SO_razlika(long,unsigned char *,unsigned char *);
void _SO_komplement(long,unsigned char *);
int _SO_podskup(long,unsigned char *,unsigned char *);
int _SO_disjunktni(long,unsigned char *,unsigned char *);
int _SO_jednaki(long,unsigned char *,unsigned char *);
int _SO_prazan_skup(long,unsigned char *);
void _SO_dodeli(long,unsigned char *,unsigned char *);
void SO_ubaci(unsigned char *,int);
void SO_izbaci(unsigned char *,int);
int SO_element(unsigned char *,int);

#define SO_ubaci_sve(x) _SO_ubaci_sve(sizeof(x),(x))
#define SO_izbaci_sve(x) _SO_izbaci_sve(sizeof(x),(x))
#define SO_unija(d,s) _SO_unija(sizeof(d),(d),(s))
#define SO_presek(d,s) _SO_presek(sizeof(d),(d),(s))
#define SO_razlika(d,s) _SO_razlika(sizeof(d),(d),(s))
#define SO_komplement(x) _SO_komplement(sizeof(x),(x))
#define SO_podskup(d,s) _SO_podskup(sizeof(d),(d),(s))
#define SO_disjunktni(d,s) _SO_disjunktni(sizeof(d),(d),(s))
#define SO_jednaki(d,s) _SO_jednaki(sizeof(d),(d),(s))
#define SO_prazan_skup(x) _SO_prazan_skup(sizeof(x),(x))
#define SO_dodeli(d,s) _SO_dodeli(sizeof(d),(d),(s))

#endif
