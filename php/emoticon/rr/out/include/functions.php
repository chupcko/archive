<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  function rr_strip_slashes(&$variable)
  {
    if(is_array($variable) === true)
      foreach($variable as $key => $value)
        rr_strip_slashes($variable[$key]);
    else
      $variable = stripslashes($variable);
  }

  function rr_register_get_variable($variable, $name, $default = false)
  {
    if(array_key_exists($name, $_GET) !== false)
    {
      $GLOBALS[$variable] = &$_GET[$name];
      if(get_magic_quotes_gpc() === 1)
        rr_strip_slashes($GLOBALS[$variable]);
      return true;
    }
    $GLOBALS[$variable] = $default;
    return false;
  }

  function rr_register_post_variable($variable, $name, $default = false)
  {
    if(array_key_exists($name, $_POST) !== false)
    {
      $GLOBALS[$variable] = &$_POST[$name];
      if(get_magic_quotes_gpc() === 1)
        rr_strip_slashes($GLOBALS[$variable]);
      return true;
    }
    $GLOBALS[$variable] = $default;
    return false;
  }

  function rr_register_request_variable($variable, $name, $default = false)
  {
    if(rr_register_get_variable($variable, $name, $default) === false)
      return rr_register_post_variable($variable, $name, $default);
    return true;
  }

  function rr_register_cookie_variable($variable, $name, $default = false)
  {
    if(array_key_exists($name, $_COOKIE) !== false)
    {
      $GLOBALS[$variable] = &$_COOKIE[$name];
      if(get_magic_quotes_gpc() === 1)
        rr_strip_slashes($GLOBALS[$variable]);
      return true;
    }
    $GLOBALS[$variable] = $default;
    return false;
  }

  function rr_register_server_variable($variable, $name, $default = false)
  {
    if(array_key_exists($name, $_SERVER) === true)
    {
      $GLOBALS[$variable] = &$_SERVER[$name];
      return true;
    }
    $GLOBALS[$variable] = $default;
    return false;
  }

  function rr_die_400($text)
  {
    header('HTTP/1.0 400 Bad Request');
    die
    (
      '400 Bad Request'."\n".
      $text."\n"
    );
  }

  function rr_die_401($auth_name)
  {
    header('WWW-Authenticate: Basic realm="'.$auth_name.'"');
    header('HTTP/1.0 401 Unauthorized');
    die
    (
      '401 Unauthorized'."\n".
      $auth_name."\n"
    );
  }

  function rr_die_403()
  {
    header('HTTP/1.0 403 Forbidden');
    die('403 Forbidden'."\n");
  }

  function rr_die_404()
  {
    header('HTTP/1.0 404 Not Found');
    die('404 Not Found'."\n");
  }

  function rr_die_500($text)
  {
    header('HTTP/1.0 500 Internal Server Error');
    die
    (
      '500 Internal Server Error'."\n".
      $text."\n"
    );
  }

  function rr_flush()
  {
    ob_flush();
    flush();
  }

  function rr_no_cache()
  {
    header('Cache-Control: no-cache, must-revalidate');
    header('Expires: Thu,  1 Jan 1970 00:00:00 GMT');
  }

  function rr_start($content_type)
  {
    rr_no_cache();
    header('Content-Type: '.$content_type);
  }

  function rr_start_text()
  {
    rr_start('text/plain');
  }

  function rr_start_download($name)
  {
    rr_start('application/octet-stream');
    header('Content-disposition: filename="'.$name.'"');
  }

  function rr_set_length($length)
  {
    header('Content-length: '.$length);
  }

  function rr_echo_xml()
  {
    echo('<?xml version="1.0" encoding="utf-8"?>'."\n");
  }

  function rr_start_xml()
  {
    rr_start('text/xml');
    rr_echo_xml();
  }

  function rr_start_html()
  {
    rr_start('text/html');
    rr_echo_xml();
  }

  function rr_redirect($url)
  {
    header('Location: '.$url);
    return RR_INCLUDE_RETURN_CODE_OK;
  }

  function rr_make_result_value($result)
  {
    var_dump($result);
    return RR_INCLUDE_RETURN_CODE_OK;
  }

  function rr_make_result(&$result)
  {
    var_dump($result);
    return RR_INCLUDE_RETURN_CODE_OK;
  }

  function rr_make_xml_result_short($code, $text)
  {
    rr_start_xml();
    echo('<result code="'.$code.'" text="'.htmlspecialchars($text).'"/>'."\n");
    return RR_INCLUDE_RETURN_CODE_OK;
  }

  function rr_make_xml_result_long($code, $text, $xml)
  {
    rr_start_xml();
    echo('<result code="'.$code.'" text="'.htmlspecialchars($text).'">'."\n".$xml.'</result>'."\n");
    return RR_INCLUDE_RETURN_CODE_OK;
  }

?>
