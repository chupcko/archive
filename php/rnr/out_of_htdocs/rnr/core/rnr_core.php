<?php

  namespace rnr
  {

    if(isset($rnr_pass) === false or $rnr_pass !== true)
      exit();

    class out
    {
      private static function prepare_header()
      {
        header('Cache-Control: no-cache, must-revalidate');
        header('Expires: Thu,  1 Jan 1970 00:00:00 GMT');
        header('Content-Type: application/json');
      }

      public static function flush()
      {
        ob_flush();
        flush();
      }

      private static function out_code_message($status, $code, $message)
      {
        global $rnr_request;
        if(isset($rnr_request) === false)
          $request = '';
        else
          $request = $rnr_request;
        static::prepare_header();
        echo
        (
          sprintf
          (
            <<< 'END'
{
  "request":"%s",
  "status":"%s",
  "code":%d,
  "message":"%s"
}
END
            ,
            addslashes($request),
            addslashes($status),
            $code,
            $message
          )
        );
      }

      private static function out_result($status, $result, $quote_result = true)
      {
        global $rnr_request;
        if(isset($rnr_request) === false)
          $request = '';
        else
          $request = $rnr_request;
        if($quote_result === true)
          $result = '"'.$result.'"';
        static::prepare_header();
        echo
        (
          sprintf
          (
            <<< 'END'
{
  "request":"%s",
  "status":"%s",
  "result":%s
}
END
            ,
            addslashes($request),
            addslashes($status),
            $result
          )
        );
      }

      public static function fatal($code, $message)
      {
        static::out_code_message('fatal', $code, addslashes($message));
        exit();
      }

      public static function error($code, $message)
      {
        static::out_code_message('error', $code, addslashes($message));
        exit();
      }

      public static function bad($message = 'bad')
      {
        static::out_result('bad', addslashes($message));
        return true;
      }

      public static function bad_json($json)
      {
        static::out_result('bad', ltrim($json), false);
        return true;
      }

      public static function ok($message = 'ok')
      {
        static::out_result('ok', addslashes($message));
        return true;
      }

      public static function ok_json($json)
      {
        static::out_result('ok', ltrim($json), false);
        return true;
      }
    }

    class in
    {
      private static function register_mandatory(&$variable, &$where, $name)
      {
        if(array_key_exists($name, $where) === true)
        {
          $variable = $where[$name];
          return true;
        }
        return false;
      }

      public static function register_mandatory_server(&$variable, $name)
      {
        return static::register_mandatory($variable, $_SERVER, $name);
      }

      public static function register_mandatory_get(&$variable, $name)
      {
        return static::register_mandatory($variable, $_GET, $name);
      }

      public static function register_mandatory_post(&$variable, $name)
      {
        return static::register_mandatory($variable, $_POST, $name);
      }

      public static function register_mandatory_cookie(&$variable, $name)
      {
        return static::register_mandatory($variable, $_COOKIE, $name);
      }

      public static function register_mandatory_argument(&$variable, $name)
      {
        if(static::register_mandatory_get($variable, $name) === true)
          return true;
        if(static::register_mandatory_post($variable, $name) === true)
          return true;
        if(static::register_mandatory_cookie($variable, $name) === true)
          return true;
        out::error(201, '"'.$name.'" is mandatory argument');
      }

      public static function register_mandatory_file(&$variable, $name)
      {
        if(static::register_mandatory($variable, $_FILES, $name) === true)
          return true;
        out::error(202, '"'.$name.'" is mandatory file');
      }

      private static function register(&$variable, &$where, $name, $default = false)
      {
        if(array_key_exists($name, $where) === true)
        {
          $variable = $where[$name];
          return true;
        }
        $variable = $default;
        return false;
      }

      public static function register_server(&$variable, $name, $default = false)
      {
        return static::register($variable, $_SERVER, $name, $default);
      }

      public static function register_get(&$variable, $name, $default = false)
      {
        return static::register($variable, $_GET, $name, $default);
      }

      public static function register_post(&$variable, $name, $default = false)
      {
        return static::register($variable, $_POST, $name, $default);
      }

      public static function register_cookie(&$variable, $name, $default = false)
      {
        return static::register($variable, $_COOKIE, $name, $default);
      }

      public static function register_argument(&$variable, $name, $default = false)
      {
        if(static::register_get($variable, $name, $default) === true)
          return true;
        if(static::register_post($variable, $name, $default) === true)
          return true;
        if(static::register_cookie($variable, $name, $default) === true)
          return true;
        return false;
      }

      public static function register_file(&$variable, $name, $default = false)
      {
        return static::register($variable, $_FILES, $name, $default);
      }
    }

    trait error_base
    {
      private $error_value = false;

      protected function clean_error()
      {
        $this->error_value = false;
      }

      protected function set_error($error)
      {
        $this->error_value = $error;
        return false;
      }

      public function get_error()
      {
        return $this->error_value;
      }
    }

    interface main
    {
      public function run();
    }

  }

?>
