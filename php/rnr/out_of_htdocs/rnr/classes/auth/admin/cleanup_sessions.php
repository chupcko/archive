<?php

  namespace auth\admin\cleanup_sessions
  {

    if(isset($rnr_pass) === false or $rnr_pass !== true)
      exit();

    class main implements \rnr\main
    {
      public function run()
      {
        $auth = new \rnr\auth(\rnr\conf::AUTH);
        $auth->allow('admin');

        $auth->cleanup_sessions();
        return \rnr\out::ok();
      }
    }

  }

?>
