<?php

  $prss_dir = '../out_of_htdocs';

  $prss_pass = true;

  include_once($prss_dir.'/include/system.php');
  include_once($prss_dir.'/include/configuration.php');

  $prss_mysql_connection = new prss_mysql_connection_c($prss_mysql_database, $prss_mysql_hostname, $prss_mysql_username, $prss_mysql_password);
  if($prss_mysql_connection->connect() === false)
    prss_out_c::end_die($prss_mysql_connection->error);
  $prss_mysql_query = new prss_mysql_query_c($prss_mysql_connection);
  $prss_mysql_data = new prss_mysql_data_c($prss_mysql_connection);

  $prss_authentication = new prss_authentication_c($prss_mysql_connection);

  if(prss_register_c::register_variable($prss_request, 'prss_request') === false)
    prss_out_c::end_error('Missing request');
  prss_register_c::register_variable($prss_session, 'prss_session');

  $prss_info = $prss_requests->get_info($prss_authentication, $prss_request, $prss_session);
  if($prss_info === false)
    prss_out_c::end_error($prss_requests->error);

  $prss_path = realpath($prss_dir.'/class/'.$prss_info['file_name']);
  if
  (
    $prss_path === false or
    file_exists($prss_path) === false or
    is_readable($prss_path) === false
  )
    prss_out_c::end_error('Missing file '.$prss_dir.'/class/'.$prss_info['file_name']);
  include($prss_path);
  if(class_exists($prss_info['class_name']) === false)
    prss_out_c::end_error('Missing class '.$prss_info['class_name']);
  if(array_key_exists('prss_request_i', class_implements($prss_info['class_name'])) === false)
    prss_out_c::end_error('Bad implements in class '.$prss_info['class_name']);
  $prss_instance = new $prss_info['class_name'];

  ob_start();
  $prss_return = $prss_instance->run
  (
    array
    (
      'session'  => $prss_session,
      'username' => $prss_info['username'],
      'user_id'  => $prss_info['user_id']
    ),
    $prss_info['arguments']
  );
  if($prss_return !== true)
  {
    ob_end_clean();
    prss_out_c::end_error($prss_return);
  }
  ob_end_flush();

?>
