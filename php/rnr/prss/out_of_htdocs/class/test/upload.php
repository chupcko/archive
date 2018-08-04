<?php

  if(isset($prss_pass) === false or $prss_pass !== true)
    die();

  class test_upload_c implements prss_request_i
  {
    public function run($who, $arguments)
    {
      $json_result = sprintf
      (
        <<< 'END'
  {
    "name":"%s",
    "type":"%s",
    "tmp_name":"%s",
    "size":%d
  }
END
        ,
        addslashes($arguments['f']['name']),
        addslashes($arguments['f']['type']),
        addslashes($arguments['f']['tmp_name']),
        addslashes($arguments['f']['size'])
      );
      return prss_out_c::json($json_result);
    }
  }

?>
