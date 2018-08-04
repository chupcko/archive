<?php

  if(isset($prss_pass) === false or $prss_pass !== true)
    die();

  class core_login_c implements prss_request_i
  {
    public function run($who, $arguments)
    {
      global $prss_authentication;

      if($prss_authentication->register($arguments['username'], $arguments['password']) === false)
        return $prss_authentication->error;
      return prss_out_c::ok();
    }
  }

?>
