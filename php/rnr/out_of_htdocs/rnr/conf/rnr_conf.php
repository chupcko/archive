<?php

  namespace rnr
  {

    if(isset($rnr_pass) === false or $rnr_pass !== true)
      exit();

    class conf
    {
      const AUTH = array
      (
        'mysql_hostname'                 => 'localhost',
        'mysql_username'                 => 'rnr',
        'mysql_password'                 => 'rnr',
        'mysql_database'                 => 'rnr',
        'session_expire_time_in_seconds' => 24*60*60,
        'session_cookie_path'            => '/'
      );
    }
  }

?>
