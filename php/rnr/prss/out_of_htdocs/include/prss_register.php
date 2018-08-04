<?php

  if(isset($prss_pass) === false or $prss_pass !== true)
    die();

  class prss_register_c
  {
    private static function strip_slashes(&$variable)
    {
      if(is_array($variable) === true)
        foreach($variable as $key => $value)
          static::strip_slashes($variable[$key]);
      else
        $variable = stripslashes($variable);
    }

    public static function register_get_variable(&$variable, $name, $default = false)
    {
      if(array_key_exists($name, $_GET) !== false)
      {
        $variable = $_GET[$name];
        if(get_magic_quotes_gpc() === 1)
          static::strip_slashes($variable);
        return true;
      }
      $variable = $default;
      return false;
    }

    public static function register_post_variable(&$variable, $name, $default = false)
    {
      if(array_key_exists($name, $_POST) !== false)
      {
        $variable = $_POST[$name];
        if(get_magic_quotes_gpc() === 1)
          static::strip_slashes($variable);
        return true;
      }
      $variable = $default;
      return false;
    }

    public static function register_request_variable(&$variable, $name, $default = false)
    {
      if(static::register_get_variable($variable, $name, $default) === false)
        return static::register_post_variable($variable, $name, $default);
      return true;
    }

    public static function register_cookie_variable(&$variable, $name, $default = false)
    {
      if(array_key_exists($name, $_COOKIE) !== false)
      {
        $variable = $_COOKIE[$name];
        if(get_magic_quotes_gpc() === 1)
          static::strip_slashes($variable);
        return true;
      }
      $variable = $default;
      return false;
    }

    public static function register_variable(&$variable, $name, $default = false)
    {
      if(static::register_request_variable($variable, $name, $default) === false)
        return static::register_cookie_variable($variable, $name, $default);
      return true;
    }

    public static function register_file(&$variable, $name)
    {
      if(array_key_exists($name, $_FILES) !== false)
      {
        $variable = $_FILES[$name];
        return true;
      }
      $variable = false;
      return false;
    }
  }

?>
