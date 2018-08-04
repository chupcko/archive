<?php

  $rr_dir = '../../emoticon-0.0/rr-0.0/out';

  $rr_check = true;

  ini_set('display_errors', false);
  ini_set('log_errors', true);
  error_reporting(E_ALL);
  ignore_user_abort(true);
  set_time_limit(0);

  include_once($rr_dir.'/include/configuration.php');
  include_once($rr_dir.'/include/functions.php');
  include_once($rr_dir.'/include/mysql.php');
  include_once($rr_dir.'/include/authentication.php');
  include_once($rr_dir.'/include/data_mysql.php');
  include_once($rr_dir.'/include/local.php');

  define('RR_INCLUDE_RETURN_CODE_OK', 1);

  rr_register_server_variable('rr_remote_ip', 'REMOTE_ADDR', '');
  rr_register_server_variable('rr_remote_port', 'REMOTE_PORT', '');
  rr_register_server_variable('rr_php_self', 'PHP_SELF', '');
  if(rr_register_request_variable('rr_session', 'rr_session') === false)
    rr_register_cookie_variable('rr_session', 'rr_session');
  rr_register_request_variable('rr_request', 'rr_request', $rr_default_request);

  $rr_mysql_connection = new rr_mysql_connection($rr_mysql_database, $rr_mysql_hostname, $rr_mysql_username, $rr_mysql_password);
  if($rr_mysql_connection->connect() === false)
    rr_die_500($rr_mysql_connection->error);
  $rr_mysql_query = new rr_mysql_query($rr_mysql_connection);

  $rr_authentication = new rr_authentication($rr_mysql_query);
  if($rr_authentication->expire_all_sessions() === false)
    rr_die_500($rr_authentication->error);
  $rr_request_data = $rr_authentication->get_request_data($rr_request, $rr_developing);
  if($rr_request_data === false)
    if($rr_authentication->error === false)
      rr_die_403();
    else
      rr_die_500($rr_authentication->error);
  if(is_null($rr_request_data['license_id']) === true)
    $rr_user_id = false;
  else
  {
    if($rr_session === false)
      rr_die_403();
    $rr_user_id = $rr_authentication->get_user_id_from_session($rr_session);
    if($rr_user_id === false)
      if($rr_authentication->error === false)
        rr_die_403();
      else
        rr_die_500($rr_authentication->error);
    if($rr_authentication->have_permission($rr_user_id, $rr_request_data['license_id']) !== true)
      if($rr_authentication->error === false)
        rr_die_403();
      else
        rr_die_500($rr_authentication->error);
  }

  $rr_request_realpath = realpath($rr_dir.'/code/'.$rr_request_data['filename']);
  if($rr_request_realpath === false)
    rr_die_500('Missing code "'.$rr_dir.'/code/'.$rr_request_data['filename'].'"');
  if(file_exists($rr_request_realpath) === false)
    rr_die_500('Missing code "'.$rr_request_realpath.'"');
  if(is_readable($rr_request_realpath) === false)
    rr_die_500('Unreadable file "'.$rr_request_realpath.'"');
  if($rr_authentication->register_arguments($rr_request_data['id']) === false)
    rr_die_500($rr_authentication->error);

  ob_start();
  $rr_return_value = include($rr_request_realpath);
  if($rr_return_value !== RR_INCLUDE_RETURN_CODE_OK)
  {
    ob_end_clean();
    rr_die_500($rr_return_value);
  }
  ob_end_flush();

?>
