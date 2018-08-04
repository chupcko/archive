#include <stdio.h> /* fprintf, stderr, */

#include "falcom.h"

int main(void)
{
  falcom_verbose = FALCOM_TRUE;
  if(falcom_open("/dev/modem") != FALCOM_RETURN_OK)
    return 10;
  if(falcom_test() != FALCOM_RETURN_OK)
    return 11;
/*
  if(falcom_test_ussd("*912#", "Neispravan format poruke. Unesite poruku u formatu *912*skriveni broj sa vaucera#") == FALCOM_RETURN_OK)
    fprintf(stderr, "USSD OK\n");
  else
    fprintf(stderr, "USSD ERROR\n");
*/

/*
  if(falcom_send_sms("+38163100100", "+381638302366", "proba") == FALCOM_RETURN_OK)
    fprintf(stderr, "Send SMS OK\n");
  else
    fprintf(stderr, "Send SMS ERROR\n");
*/

  if(falcom_test_sms("+38163100063", "+381637777156", "proba12", "proba12") == FALCOM_RETURN_OK)
    fprintf(stderr, "SMS OK\n");
  else
  {
    fprintf(stderr, "SMS ERROR\n");
    falcom_test();
    falcom_send_sms("+38163100100", "+381638302366", "SMSC problem");
  }

  if(falcom_close() != FALCOM_RETURN_OK)
    return 12;
  return 0;
}
