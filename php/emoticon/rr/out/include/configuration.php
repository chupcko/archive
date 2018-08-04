<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  $rr_version = '0.0';

  $rr_mysql_database = 'rr';
  $rr_mysql_hostname = 'localhost';
  $rr_mysql_username = 'rr';
  $rr_mysql_password = 'rr';

  $rr_developing = true;

  $rr_session_expire_time_in_seconds = 24*60*60;
  $rr_session_cookie_path = '/';

  $rr_default_request = 'development/index';

  define('RR_ADMIN_LICENSE_ID', 1);
  define('RR_ALL_LICENSE_ID',   2);

?>
