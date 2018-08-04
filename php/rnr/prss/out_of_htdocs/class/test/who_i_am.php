<?php

  if(isset($prss_pass) === false or $prss_pass !== true)
    die();

  class test_who_i_am_c implements prss_request_i
  {
    public function run($who, $arguments)
    {
      $json_result = sprintf
      (
        <<< 'END'
  {
    "session":"%s",
    "username":"%s",
    "user_id":%d
  }
END
        ,
        addslashes($who['session']),
        addslashes($who['username']),
        $who['user_id']
      );
      return prss_out_c::json($json_result);
    }
  }

?>
