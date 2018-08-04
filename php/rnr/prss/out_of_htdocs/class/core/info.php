<?php

  if(isset($prss_pass) === false or $prss_pass !== true)
    die();

  class core_info_c implements prss_request_i
  {
    public function run($who, $arguments)
    {
      global $prss_authentication;

      $array_result = $prss_authentication->get_licenses($who['user_id']);
      if($array_result === false)
        return $prss_authentication->error;

      if(count($array_result) == 0)
        $licenses_result = '[]';
      else
      {
        $licenses_result = '['.PHP_EOL;
        $first = true;
        foreach($array_result as $value)
        {
          if($first !== true)
            $licenses_result .= ','.PHP_EOL;
          $first = false;
          $licenses_result .= '      "'.addslashes($value).'"';
        }
        $licenses_result .= PHP_EOL.'    ]';
      }

      $json_result = sprintf
      (
        <<< 'END'
  {
    "session":"%s",
    "username":"%s",
    "user_id":%d,
    "licenses":%s
  }
END
        ,
        addslashes($who['session']),
        addslashes($who['username']),
        $who['user_id'],
        $licenses_result
      );
      return prss_out_c::json($json_result);
    }
  }

?>
