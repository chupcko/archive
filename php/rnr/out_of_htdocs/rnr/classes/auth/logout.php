<?php

  namespace auth\logout
  {

    if(isset($rnr_pass) === false or $rnr_pass !== true)
      exit();

    class main implements \rnr\main
    {
      public function run()
      {
        $auth = new \rnr\auth(\rnr\conf::AUTH);
        $auth->allow();

        $auth->unregister();
        return \rnr\out::ok();
      }
    }

  }

?>
