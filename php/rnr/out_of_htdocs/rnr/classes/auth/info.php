<?php

  namespace auth\info
  {

    if(isset($rnr_pass) === false or $rnr_pass !== true)
      exit();

    class main implements \rnr\main
    {
      public function run()
      {
        $auth = new \rnr\auth(\rnr\conf::AUTH);
        $auth->allow();

        $licenses = $auth->get_licenses();
        if(count($licenses) == 0)
          $licenses_json = '[]';
        else
        {
          $licenses_json = '['.PHP_EOL;
          $first = true;
          foreach($licenses as $value)
          {
            if($first !== true)
              $licenses_json .= ','.PHP_EOL;
            $first = false;
            $licenses_json .= '      "'.addslashes($value).'"';
          }
          $licenses_json .= PHP_EOL.'    ]';
        }

        return \rnr\out::ok_json
        (
          sprintf
          (
            <<< 'END'
  {
    "user_id":%d,
    "username":"%s",
    "session":"%s",
    "licenses":%s
  }
END
            ,
            $auth->user_id,
            addslashes($auth->username),
            addslashes($auth->session),
            $licenses_json
          )
        );
      }
    }

  }

?>
