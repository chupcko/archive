<?php

  if(isset($prss_pass) === false or $prss_pass !== true)
    die();

  class prss_root_c
  {
    public $error;

    function __construct()
    {
      $this->clean_error();
    }

    protected function set_error($error)
    {
      $this->error = $error;
      return false;
    }

    protected function clean_error()
    {
      $this->error = false;
    }
  }

  interface prss_request_i
  {
    public function run($who, $arguments);
  }

  include_once($prss_dir.'/include/prss_mysql_connection.php');
  include_once($prss_dir.'/include/prss_mysql_query.php');
  include_once($prss_dir.'/include/prss_mysql_data.php');

  include_once($prss_dir.'/include/prss_out.php');
  include_once($prss_dir.'/include/prss_register.php');

  include_once($prss_dir.'/include/prss_authentication.php');

  include_once($prss_dir.'/include/prss_request.php');
  include_once($prss_dir.'/include/prss_requests.php');

  function error_handler($errno, $errstr, $errfile, $errline)
  {
    if($errno === E_ERROR)
      prss_out_c::end_die($errstr.' '.$errfile.' '.$errline);
  }

  function shutdown_handler()
  {
    $last_error = error_get_last();
    if($last_error['type'] === E_ERROR)
      error_handler(E_ERROR, $last_error['message'], $last_error['file'], $last_error['line']);
  }

  ini_set('display_errors', false);
  ini_set('log_errors', true);
  error_reporting(E_ALL);
  set_error_handler('error_handler');
  register_shutdown_function('shutdown_handler');
  ignore_user_abort(true);
  set_time_limit(0);

?>
