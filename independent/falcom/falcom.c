#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> /* open, O_RDWR, O_NDELAY, fcntl, F_GETFL, F_SETFL, O_CREAT, O_EXCL, */
#include <termios.h> /* struct termios, tcgetattr, cfsetospeed, B9600, cfsetispeed, CSIZE, CS8, IGNBRK, CLOCAL, CREAD, CRTSCTS, IXON, IXOFF, IXANY, PARENB, PARODD, CSTOPB, tcsetattr, TCSANOW, */
#include <unistd.h> /* close, write, read, */
#include <sys/poll.h> /* struct pollfd, poll, */
#include <stdio.h> /* fprintf, stderr, NULL, snprintf, */
#include <string.h> /* strlen, strncmp, */
#include <time.h> /* time_t, time, */
#include <regex.h> /* regex_t, regcomp, REG_EXTENDED, REG_ICASE, regexec, */
#include <unistd.h> /* sleep, unlink, */

#include "falcom.h"

#define FALCOM_LOCK_FILENAME "/tmp/falcom.lck"
#define FALCOM_LOCK_TIMEOUT_SECONDS 60
#define FALCOM_MAX_BUFFER_SIZE 4096

int falcom_short_timeout_in_seconds = 5;
int falcom_long_timeout_in_seconds = 60;
falcom_boolean falcom_verbose = FALCOM_FALSE;

static falcom_boolean falcom_lock_state = FALCOM_FALSE;
static falcom_boolean falcom_set = FALCOM_FALSE;
static int falcom_file_descriptor;
static char buffer[FALCOM_MAX_BUFFER_SIZE+1];
static int buffer_size;

falcom_return_code falcom_unlock(void)
{
  if(falcom_verbose == FALCOM_TRUE)
    fprintf(stderr, "Unlock\n");
  unlink(FALCOM_LOCK_FILENAME);
  falcom_lock_state = FALCOM_FALSE;
  return FALCOM_RETURN_OK;
}

falcom_return_code falcom_lock(void)
{
  time_t start_time;
  int file_descriptor;

  if(falcom_verbose == FALCOM_TRUE)
    fprintf(stderr, "Lock test\n");
  start_time = time(NULL);
  while(time(NULL)-start_time < FALCOM_LOCK_TIMEOUT_SECONDS)
  {
    if(falcom_lock_state != FALCOM_TRUE)
    {
      file_descriptor = open(FALCOM_LOCK_FILENAME, O_RDWR|O_NDELAY|O_CREAT|O_EXCL);
      if(file_descriptor >= 0)
      {
        if(falcom_verbose == FALCOM_TRUE)
          fprintf(stderr, "Lock\n");
        falcom_lock_state = FALCOM_TRUE;
        close(file_descriptor);
        return FALCOM_RETURN_OK;
      }
    }
    sleep(1);
  }
  falcom_unlock();
  return FALCOM_RETURN_TIMEOUT;
}

falcom_return_code falcom_open(char *device)
{
  int file_fcntl;
  struct termios file_tty;

  if(falcom_set == FALCOM_TRUE)
    return FALCOM_RETURN_BAD_CALL;
  if(falcom_lock() != FALCOM_RETURN_OK)
    return FALCOM_RETURN_LOCK;
  if(falcom_verbose  == FALCOM_TRUE)
    fprintf(stderr, "Open device %s\n", device);
  falcom_file_descriptor = open(device, O_RDWR|O_NDELAY);
  if(falcom_file_descriptor < 0)
    return FALCOM_RETURN_ERROR;
  file_fcntl = fcntl(falcom_file_descriptor, F_GETFL, 0);
  fcntl(falcom_file_descriptor, F_SETFL, file_fcntl&~O_NDELAY);
  tcgetattr(falcom_file_descriptor, &file_tty);
  cfsetospeed(&file_tty, B9600);
  cfsetispeed(&file_tty, B9600);
  file_tty.c_cflag &= ~CSIZE;
  file_tty.c_cflag |= CS8;
  file_tty.c_iflag = IGNBRK;
  file_tty.c_lflag = 0;
  file_tty.c_oflag = 0;
  file_tty.c_cflag |= CLOCAL|CREAD;
  file_tty.c_cflag &= ~CRTSCTS;
  file_tty.c_cc[VMIN] = 1;
  file_tty.c_cc[VTIME] = 5;
  file_tty.c_iflag &= ~(IXON|IXOFF|IXANY);
  file_tty.c_cflag &= ~(PARENB|PARODD);
  file_tty.c_cflag &= ~CSTOPB;
  tcsetattr(falcom_file_descriptor, TCSANOW, &file_tty);
  buffer_size = 0;
  falcom_set = FALCOM_TRUE;
  return FALCOM_RETURN_OK;
}

falcom_return_code falcom_close(void)
{
  if(falcom_set != FALCOM_TRUE)
    return FALCOM_RETURN_BAD_CALL;
  falcom_unlock();
  if(falcom_verbose == FALCOM_TRUE)
    fprintf(stderr, "Close device\n");
  close(falcom_file_descriptor);
  falcom_set = FALCOM_FALSE;
  return FALCOM_RETURN_OK;
}

falcom_return_code falcom_send(char *command)
{
  int command_length;

  if(falcom_set != FALCOM_TRUE)
    return FALCOM_RETURN_BAD_CALL;
  if(falcom_verbose == FALCOM_TRUE)
    fprintf(stderr, "  Send to device: %s\n", command);
  command_length = strlen(command);
  if(write(falcom_file_descriptor, command, command_length) != command_length)
    return FALCOM_RETURN_ERROR;
  return FALCOM_RETURN_OK;
}

falcom_return_code falcom_expect_string(char *string, int timeout_in_seconds)
{
  time_t start_time;
  struct pollfd poll_array[1];

  if(falcom_set != FALCOM_TRUE)
    return FALCOM_RETURN_BAD_CALL;
  if(falcom_verbose == FALCOM_TRUE)
    fprintf(stderr, "Expect string from device: %s\n", string);
  start_time = time(NULL);
  while
  (
    buffer_size < FALCOM_MAX_BUFFER_SIZE &&
    time(NULL)-start_time < timeout_in_seconds
  )
  {
    poll_array[0].fd = falcom_file_descriptor;
    poll_array[0].events = POLLIN;
    poll_array[0].revents = 0;
    if(poll(poll_array, 1, 500) > 0)
    {
      int buffer_read;
      char *string_match;

      buffer_read = read(falcom_file_descriptor, &buffer[buffer_size], FALCOM_MAX_BUFFER_SIZE-buffer_size);
      if(buffer_read < 0)
        return FALCOM_RETURN_ERROR;
      buffer[buffer_size+buffer_read] = '\0';
      if(falcom_verbose == FALCOM_TRUE)
        fprintf(stderr, "  Receive from device: %s\n", &buffer[buffer_size]);
      buffer_size += buffer_read;
      string_match = strstr(buffer, string);
      if(string_match != NULL)
      {
        int i = 0;
        int j = (int)(string_match-buffer+strlen(string));

        while(j < buffer_size)
        {
          buffer[i] = buffer[j];
          i++;
          j++;
        }
        buffer_size = i;
        return FALCOM_RETURN_FOUND;
      }
    }
  }
  if(buffer_size < FALCOM_MAX_BUFFER_SIZE)
    return FALCOM_RETURN_TIMEOUT;
  return FALCOM_RETURN_OVERSIZED;
}

falcom_return_code falcom_expect_regex(char *regex_string, int timeout_in_seconds, char *result, int max_result_length)
{
  regex_t regex_regex;
  time_t start_time;
  struct pollfd poll_array[1];

  if(falcom_set != FALCOM_TRUE)
    return FALCOM_RETURN_BAD_CALL;
  if(falcom_verbose == FALCOM_TRUE)
    fprintf(stderr, "Expect regex from device: %s\n", regex_string);
  if(regcomp(&regex_regex, regex_string, REG_EXTENDED|REG_ICASE) != 0)
    return FALCOM_RETURN_ERROR;
  start_time = time(NULL);
  while
  (
    buffer_size < FALCOM_MAX_BUFFER_SIZE &&
    time(NULL)-start_time < timeout_in_seconds
  )
  {
    poll_array[0].fd = falcom_file_descriptor;
    poll_array[0].events = POLLIN;
    poll_array[0].revents = 0;
    if(poll(poll_array, 1, 500) > 0)
    {
      int buffer_read;
      regmatch_t regex_match[2];

      buffer_read = read(falcom_file_descriptor, &buffer[buffer_size], FALCOM_MAX_BUFFER_SIZE-buffer_size);
      if(buffer_read < 0)
        return FALCOM_RETURN_ERROR;
      buffer[buffer_size+buffer_read] = '\0';
      if(falcom_verbose == FALCOM_TRUE)
        fprintf(stderr, "  Receive from device: %s\n", &buffer[buffer_size]);
      buffer_size += buffer_read;
      if(regexec(&regex_regex, buffer, 2, regex_match, 0) == 0)
      {
        int i;
        int j;

        if(result != NULL && regex_match[1].rm_so >= 0 && regex_match[1].rm_eo >= 0)
        {
          i = 0;
          j = regex_match[1].rm_so;
          while(i < max_result_length-1 && j < regex_match[1].rm_eo)
          {
            result[i] = buffer[j];
            i++;
            j++;
          }
          result[i] = '\0';
        }
        i = 0;
        j = regex_match[0].rm_eo;
        while(j < buffer_size)
        {
          buffer[i] = buffer[j];
          i++;
          j++;
        }
        buffer_size = i;
        return FALCOM_RETURN_FOUND;
      }
    }
  }
  if(buffer_size < FALCOM_MAX_BUFFER_SIZE)
    return FALCOM_RETURN_TIMEOUT;
  return FALCOM_RETURN_OVERSIZED;
}

falcom_return_code falcom_test(void)
{
  if(falcom_set != FALCOM_TRUE)
    return FALCOM_RETURN_BAD_CALL;
  if(falcom_verbose == FALCOM_TRUE)
    fprintf(stderr, "Test\n");
  if(falcom_send("AT\r") != FALCOM_RETURN_OK)
    return FALCOM_RETURN_ERROR;
  if(falcom_expect_string("OK\r\n", falcom_short_timeout_in_seconds) != FALCOM_RETURN_FOUND)
    return FALCOM_RETURN_ERROR;
  return FALCOM_RETURN_OK;
}

falcom_return_code falcom_send_sms(char *service_center, char *phone, char *message)
{
  char string[FALCOM_MAX_BUFFER_SIZE+1];

  if(falcom_set != FALCOM_TRUE)
    return FALCOM_RETURN_BAD_CALL;
  if(falcom_verbose == FALCOM_TRUE)
    fprintf(stderr, "Send SMS\n");
  if(falcom_send("AT+CSMS=1\r") != FALCOM_RETURN_OK)
    return FALCOM_RETURN_ERROR;
  if(falcom_expect_string("OK\r\n", falcom_short_timeout_in_seconds) != FALCOM_RETURN_FOUND)
    return FALCOM_RETURN_ERROR;
  if(falcom_send("AT+CMGF=1\r") != FALCOM_RETURN_OK)
    return FALCOM_RETURN_ERROR;
  if(falcom_expect_string("OK\r\n", falcom_short_timeout_in_seconds) != FALCOM_RETURN_FOUND)
    return FALCOM_RETURN_ERROR;
  snprintf(string, FALCOM_MAX_BUFFER_SIZE, "AT+CSCA=%.32s\r", service_center);
  if(falcom_send(string) != FALCOM_RETURN_OK)
    return FALCOM_RETURN_ERROR;
  if(falcom_expect_string("OK\r\n", falcom_short_timeout_in_seconds) != FALCOM_RETURN_FOUND)
    return FALCOM_RETURN_ERROR;
  snprintf(string, FALCOM_MAX_BUFFER_SIZE, "AT+CMGS=%.32s\r", phone);
  if(falcom_send(string) != FALCOM_RETURN_OK)
    return FALCOM_RETURN_ERROR;
  if(falcom_expect_string("> ", falcom_short_timeout_in_seconds) != FALCOM_RETURN_FOUND)
    return FALCOM_RETURN_ERROR;
  snprintf(string, FALCOM_MAX_BUFFER_SIZE, "%.160s\032", message);
  if(falcom_send(string) != FALCOM_RETURN_OK)
    return FALCOM_RETURN_ERROR;
  if(falcom_expect_string("OK\r\n", falcom_long_timeout_in_seconds) != FALCOM_RETURN_FOUND)
    return FALCOM_RETURN_ERROR;
  return FALCOM_RETURN_OK;
}

falcom_return_code falcom_test_ussd(char *code, char *result)
{
  char string[FALCOM_MAX_BUFFER_SIZE+1];
  falcom_return_code return_code;

  if(falcom_set != FALCOM_TRUE)
    return FALCOM_RETURN_BAD_CALL;
  if(falcom_verbose == FALCOM_TRUE)
    fprintf(stderr, "Test USSD\n");
  snprintf(string, FALCOM_MAX_BUFFER_SIZE, "AT+CUSD=1,%s\r", code);
  if(falcom_send(string) != FALCOM_RETURN_OK)
    return FALCOM_RETURN_ERROR;
  if(falcom_expect_string("OK\r\n", falcom_short_timeout_in_seconds) != FALCOM_RETURN_FOUND)
    return FALCOM_RETURN_ERROR;
  return_code = falcom_expect_regex("[+]CUSD: 2,\"([^\"]*)\"", 30, string, FALCOM_MAX_BUFFER_SIZE);
  if(return_code == FALCOM_RETURN_TIMEOUT)
    return FALCOM_RETURN_TIMEOUT;
  if(return_code != FALCOM_RETURN_FOUND)
    return FALCOM_RETURN_ERROR;
  if(strncmp(result, string, FALCOM_MAX_BUFFER_SIZE) == 0)
    return FALCOM_RETURN_OK;
  return FALCOM_RETURN_NOT_FOUND;
}

falcom_return_code falcom_test_sms(char *service_center, char *phone, char *message, char *result)
{
  char string_1[FALCOM_MAX_BUFFER_SIZE+1];
  char string_2[FALCOM_MAX_BUFFER_SIZE+1];
  char string_3[FALCOM_MAX_BUFFER_SIZE+1];
  falcom_return_code return_code;

  if(falcom_set != FALCOM_TRUE)
    return FALCOM_RETURN_BAD_CALL;
  if(falcom_verbose == FALCOM_TRUE)
    fprintf(stderr, "Test SMS\n");
  if(falcom_send("AT+CSMS=1\r") != FALCOM_RETURN_OK)
    return FALCOM_RETURN_ERROR;
  if(falcom_expect_string("OK\r\n", falcom_short_timeout_in_seconds) != FALCOM_RETURN_FOUND)
    return FALCOM_RETURN_ERROR;
  if(falcom_send("AT+CMGF=1\r") != FALCOM_RETURN_OK)
    return FALCOM_RETURN_ERROR;
  if(falcom_expect_string("OK\r\n", falcom_short_timeout_in_seconds) != FALCOM_RETURN_FOUND)
    return FALCOM_RETURN_ERROR;
  if(falcom_send("AT+CNMI=1,1\r") != FALCOM_RETURN_OK)
    return FALCOM_RETURN_ERROR;
  if(falcom_expect_string("OK\r\n", falcom_short_timeout_in_seconds) != FALCOM_RETURN_FOUND)
    return FALCOM_RETURN_ERROR;
  snprintf(string_1, FALCOM_MAX_BUFFER_SIZE, "AT+CSCA=%.32s\r", service_center);
  if(falcom_send(string_1) != FALCOM_RETURN_OK)
    return FALCOM_RETURN_ERROR;
  if(falcom_expect_string("OK\r\n", falcom_short_timeout_in_seconds) != FALCOM_RETURN_FOUND)
    return FALCOM_RETURN_ERROR;
  snprintf(string_1, FALCOM_MAX_BUFFER_SIZE, "AT+CMGS=%.32s\r", phone);
  if(falcom_send(string_1) != FALCOM_RETURN_OK)
    return FALCOM_RETURN_ERROR;
  if(falcom_expect_string("> ", falcom_short_timeout_in_seconds) != FALCOM_RETURN_FOUND)
    return FALCOM_RETURN_ERROR;
  snprintf(string_1, FALCOM_MAX_BUFFER_SIZE, "%.160s\032", message);
  if(falcom_send(string_1) != FALCOM_RETURN_OK)
    return FALCOM_RETURN_ERROR;
  if(falcom_expect_string("OK\r\n", falcom_long_timeout_in_seconds) != FALCOM_RETURN_FOUND)
    return FALCOM_RETURN_ERROR;
  return_code = falcom_expect_regex("[+]CMTI: \"[^\"]*\",([0-9]+)", 30, string_1, FALCOM_MAX_BUFFER_SIZE);
  if(return_code == FALCOM_RETURN_TIMEOUT)
    return FALCOM_RETURN_TIMEOUT;
  if(return_code != FALCOM_RETURN_FOUND)
    return FALCOM_RETURN_ERROR;
  snprintf(string_2, FALCOM_MAX_BUFFER_SIZE, "AT+CMGR=%.4s\r", string_1);
  if(falcom_send(string_2) != FALCOM_RETURN_OK)
    return FALCOM_RETURN_ERROR;
  return_code = falcom_expect_regex("[+]CMGR: [^\r]+\r\n([^\r]*)\r\n\r\nOK\r\n", 30, string_3, FALCOM_MAX_BUFFER_SIZE);
  if(return_code == FALCOM_RETURN_TIMEOUT)
    return FALCOM_RETURN_TIMEOUT;
  if(return_code != FALCOM_RETURN_FOUND)
    return FALCOM_RETURN_ERROR;
  snprintf(string_2, FALCOM_MAX_BUFFER_SIZE, "AT+CMGD=%.4s\r", string_1);
  if(falcom_send(string_2) != FALCOM_RETURN_OK)
    return FALCOM_RETURN_ERROR;
  if(falcom_expect_string("OK\r\n", falcom_short_timeout_in_seconds) != FALCOM_RETURN_FOUND)
    return FALCOM_RETURN_ERROR;
  if(strncmp(result, string_3, FALCOM_MAX_BUFFER_SIZE) == 0)
    return FALCOM_RETURN_OK;
  return FALCOM_RETURN_NOT_FOUND;
}
