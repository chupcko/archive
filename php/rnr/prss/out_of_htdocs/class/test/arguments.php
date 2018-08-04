<?php

  if(isset($prss_pass) === false or $prss_pass !== true)
    die();

  class test_arguments_c implements prss_request_i
  {
    public function run($who, $arguments)
    {
      $json_result = sprintf
      (
        <<< 'END'
  {
    "m":"%s",
    "o":"%s"
  }
END
        ,
        addslashes($arguments['m']),
        addslashes($arguments['o'])
      );
      return prss_out_c::json($json_result);
    }
  }

?>
