<?php

  if(isset($prss_pass) === false or $prss_pass !== true)
    die();

  $prss_mysql_database = 'prss';
  $prss_mysql_hostname = 'localhost';
  $prss_mysql_username = 'prss';
  $prss_mysql_password = 'prss';

  $prss_session_expire_time_in_seconds = 24*60*60;
  $prss_session_cookie_path = '/';

  $prss_requests = (new prss_requests_c())
  ->add
  (
    (new prss_request_c('core/login', 'core/login.php', 'core_login_c'))
    ->all()
    ->mandatory_argument('username')
    ->mandatory_argument('password')
  )
  ->add((new prss_request_c('core/logout', 'core/logout.php', 'core_logout_c'))->logged())
  ->add((new prss_request_c('core/info', 'core/info.php', 'core_info_c'))->logged())

  ->add((new prss_request_c('admin/list_sessions', 'admin/list_sessions.php', 'admin_list_sessions_c'))->license('admin'))
  ->add((new prss_request_c('admin/prune_sessions', 'admin/prune_sessions.php', 'admin_prune_sessions_c'))->license('admin'))

  ->add
  (
    (new prss_request_c('test/arguments', 'test/arguments.php', 'test_arguments_c'))
    ->license('test')
    ->mandatory_argument('m')
    ->optional_argument('o', 'v')
  )
  ->add
  (
    (new prss_request_c('test/upload', 'test/upload.php', 'test_upload_c'))
    ->license('test')
    ->file_argument('f')
  )
  ->add((new prss_request_c('test/mysql_data', 'test/mysql_data.php', 'test_mysql_data_c'))->license('test'))
  ->add((new prss_request_c('test/who_i_am', 'test/who_i_am.php', 'test_who_i_am_c'))->license('test'))
  ;

?>
