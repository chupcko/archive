<?php

  namespace test\upload
  {

    if(isset($rnr_pass) === false or $rnr_pass !== true)
      exit();

    class main implements \rnr\main
    {
      public function run()
      {
        \rnr\in::register_mandatory_file($file, 'file');

        return \rnr\out::ok_json
        (
          sprintf
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
            addslashes($file['name']),
            addslashes($file['type']),
            addslashes($file['tmp_name']),
            $file['size']
          )
        );
      }
    }

  }

?>
