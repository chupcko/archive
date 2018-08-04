<?php

  if(isset($prss_pass) === false or $prss_pass !== true)
    die();

  class prss_out_c
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

    private static function out($status, $detail_name, $detail, $quote_detail = true)
    {
      global $prss_request;
      global $prss_session;
      static::prepare_header();
      if($quote_detail === true)
        $detail = '"'.$detail.'"';
      echo sprintf
      (
        <<< 'END'
{
  "request":"%s",
  "session":"%s",
  "status":"%s",
  "%s":%s
}
END
        ,
        addslashes($prss_request),
        addslashes($prss_session),
        addslashes($status),
        addslashes($detail_name), $detail
      );
    }

    public static function end_die($message)
    {
      static::out('die', 'message', addslashes($message));
      die();
    }

    public static function end_error($message)
    {
      static::out('error', 'message', addslashes($message));
      die();
    }

    public static function json($json)
    {
      static::out('ok', 'result', ltrim($json), false);
      return true;
    }

    public static function ok()
    {
      static::out('ok', 'result', 'ok');
      return true;
    }
  }

?>
