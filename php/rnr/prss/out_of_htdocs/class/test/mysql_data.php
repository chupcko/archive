<?php

  if(isset($prss_pass) === false or $prss_pass !== true)
    die();

  class test_mysql_data_c implements prss_request_i
  {
    public static function f1($pass)
    {
      return strrev($pass);
    }

    public function run($who, $arguments)
    {
      global $prss_mysql_data;

      $fields_description = array
      (
        array('expression' => 'id',              'name' => 'id'  ),
        array('expression' => 'UPPER(username)', 'name' => 'name'),
        array('expression' => 'password',        'name' => 'pass')
      );
      $data_description = array
      (
        array('name' => 'id',        'type' => 'copy',      'from' => 'id'                                                 ),
        array('name' => 'username',  'type' => 'copy',      'from' => 'name'                                               ),
        array('name' => 'password',  'type' => 'copy',      'from' => 'pass'                                               ),
        array('name' => 'rpassword', 'type' => 'calculate', 'call' => 'test_mysql_data_c::f1', 'arguments' => array('pass'))
      );
      if($prss_mysql_data->make_json($fields_description, 'SELECT '.prss_mysql_data_c::FIELDS.' FROM prss_users', $data_description, $json_result) === false)
        return $prss_mysql_data->error;

      return prss_out_c::json($json_result);
    }
  }

?>
