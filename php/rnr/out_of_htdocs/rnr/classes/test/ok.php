<?php

  namespace test\ok
  {

    if(isset($rnr_pass) === false or $rnr_pass !== true)
      exit();

    class main implements \rnr\main
    {
      public function run()
      {
        return \rnr\out::ok();
      }
    }

  }

?>
