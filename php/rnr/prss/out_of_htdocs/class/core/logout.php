<?php

  if(isset($prss_pass) === false or $prss_pass !== true)
    die();

  class core_logout_c implements prss_request_i
  {
    public function run($who, $arguments)
    {
      global $prss_authentication;

      $prss_authentication->unregister($who['session']);
      return prss_out_c::ok();
    }
  }

?>
