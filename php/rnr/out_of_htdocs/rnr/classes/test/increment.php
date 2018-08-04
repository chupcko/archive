<?php

  namespace test\increment
  {

    if(isset($rnr_pass) === false or $rnr_pass !== true)
      exit();

    class main implements \rnr\main
    {
      public function run()
      {
        \rnr\in::register_mandatory_argument($value, 'value');
        \rnr\in::register_argument($extra, 'extra', 42);

        $value++;

        return \rnr\out::ok_json
        (
          sprintf
          (
            <<< 'END'
  {
    "value":%d,
    "extra":%d
  }
END
            ,
            $value,
            $extra
          )
        );
      }
    }

  }

?>
