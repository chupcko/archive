typedef enum
{
  FALCOM_RETURN_OK = 0,
  FALCOM_RETURN_LOCK,
  FALCOM_RETURN_NOT_FOUND,
  FALCOM_RETURN_TIMEOUT,
  FALCOM_RETURN_ERROR,
  FALCOM_RETURN_BAD_CALL,
  FALCOM_RETURN_OVERSIZED
} falcom_return_code;
#define FALCOM_RETURN_FOUND FALCOM_RETURN_OK

typedef enum
{
  FALCOM_FALSE = 0,
  FALCOM_TRUE
} falcom_boolean;

extern falcom_boolean falcom_verbose;

falcom_return_code falcom_unlock(void);
falcom_return_code falcom_lock(void);
falcom_return_code falcom_open(char *);
falcom_return_code falcom_close(void);
falcom_return_code falcom_send(char *);
falcom_return_code falcom_expect_string(char *, int);
falcom_return_code falcom_expect_regex(char *, int, char *, int);
falcom_return_code falcom_test(void);
falcom_return_code falcom_send_sms(char *, char *, char *);
falcom_return_code falcom_test_ussd(char *, char *);
falcom_return_code falcom_test_sms(char *, char *, char *, char *);
