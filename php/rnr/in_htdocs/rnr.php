<?php

  #
  # Please set directory of RnR
  #

  $rnr_dir = '../out_of_htdocs/rnr';

  #
  #
  #

  $rnr_pass = true;

  include_once($rnr_dir.'/core/rnr_core.php');

  function rnr_error_handler($type, $message, $file, $line)
  {
    if
    (
      $type !== E_WARNING and
      $type !== E_NOTICE
    )
    {
      ob_end_clean();
      rnr\out::fatal(-101, $message.' on '.$file.':'.$line);
    }
  }

  function rnr_shutdown_handler()
  {
    $last_error = error_get_last();
    if(is_null($last_error) === false)
      rnr_error_handler($last_error['type'], $last_error['message'], $last_error['file'], $last_error['line']);
  }

  ini_set('display_errors', false);
  ini_set('log_errors', true);
  error_reporting(E_ALL);
  set_error_handler('rnr_error_handler');
  register_shutdown_function('rnr_shutdown_handler');
  ignore_user_abort(true);
  set_time_limit(0);

  include_once($rnr_dir.'/core/rnr_mysql.php');
  include_once($rnr_dir.'/core/rnr_auth.php');
  include_once($rnr_dir.'/core/rnr_extra.php');

  include_once($rnr_dir.'/conf/rnr_conf.php');

  if(rnr\in::register_server($rnr_request, 'PATH_INFO') === false)
    rnr\out::error(101, 'Missing request');

  $rnr_request_file = realpath($rnr_dir.'/classes'.$rnr_request.'.php');
  if
  (
    $rnr_request_file === false or
    file_exists($rnr_request_file) === false or
    is_readable($rnr_request_file) === false
  )
    rnr\out::error(102, 'Missing file '.$rnr_request_file);
  include($rnr_request_file);
  $rnr_request_class = str_replace('/', '\\', $rnr_request).'\\main';
  if(class_exists($rnr_request_class) === false)
    rnr\out::error(103, 'Missing class '.$rnr_request_class);
  if(array_key_exists('rnr\\main', class_implements($rnr_request_class)) === false)
    rnr\out::error(104, 'Bad implements in class '.$rnr_request_class);
  $rnr_instance = new $rnr_request_class();

  ob_start();
  $rnr_return = $rnr_instance->run();
  if($rnr_return !== true)
  {
    ob_end_clean();
    rnr\out::error(105, $rnr_return);
  }
  ob_end_flush();

?>
