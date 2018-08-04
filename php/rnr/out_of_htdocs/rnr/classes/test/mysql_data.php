<?php

  namespace test\mysql_data
  {

    if(isset($rnr_pass) === false or $rnr_pass !== true)
      exit();

    class main implements \rnr\main
    {
      public function run()
      {
        $mysql = new \rnr\mysql
        (
          array
          (
            'hostname' => 'localhost',
            'username' => 'root',
            'password' => '',
            'database' => 'mysql'
          )
        );
        $mysql_data = new \rnr\mysql_data($mysql);

        if
        (
          $mysql_data->make_json
          (
            array
            (
              array('expression' => 'host',        'name' => 'host'),
              array('expression' => 'UPPER(user)', 'name' => 'user')
            ),
            'SELECT '.\rnr\mysql_data::FIELDS.' FROM user',
            array
            (
              array('name' => 'host',     'type' => 'copy',      'from' => 'host'                                               ),
              array('name' => 'username', 'type' => 'copy',      'from' => 'user'                                               ),
              array('name' => 'rhost',    'type' => 'calculate', 'call' => '\\test\\mysql_data\\main::f', 'arguments' => array('host'))
            ),
            $json_result
          ) === false
        )
          return $mysql_data->get_error();
        return \rnr\out::ok_json($json_result);
      }

      public static function f($string)
      {
        return strrev($string);
      }
    }

  }

?>
