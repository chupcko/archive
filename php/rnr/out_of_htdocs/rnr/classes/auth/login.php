<?php

  namespace auth\login
  {

    if(isset($rnr_pass) === false or $rnr_pass !== true)
      exit();

    class main implements \rnr\main
    {
      public function run()
      {
        \rnr\in::register_mandatory_argument($username, 'username');
        \rnr\in::register_mandatory_argument($password, 'password');

        $auth = new \rnr\auth(\rnr\conf::AUTH);
        $auth->register($username, $password);
        return \rnr\out::ok();
      }
    }

  }

?>
