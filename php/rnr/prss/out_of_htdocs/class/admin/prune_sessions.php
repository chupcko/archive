<?php

  if(isset($prss_pass) === false or $prss_pass !== true)
    die();

  class admin_prune_sessions_c implements prss_request_i
  {
    public function run($who, $arguments)
    {
      global $prss_mysql_query;

      if($prss_mysql_query->execute('DELETE FROM prss_sessions') === false)
        return $prss_mysql_query->error;
      return prss_out_c::ok();
    }
  }

?>
