<?php

  namespace auth\admin\list_sessions
  {

    if(isset($rnr_pass) === false or $rnr_pass !== true)
      exit();

    class main implements \rnr\main
    {
      public function run()
      {
        $auth = new \rnr\auth(\rnr\conf::AUTH);
        $auth->allow('admin');

        $mysql = new \rnr\mysql
        (
          array
          (
            'hostname' => \rnr\conf::AUTH['mysql_hostname'],
            'username' => \rnr\conf::AUTH['mysql_username'],
            'password' => \rnr\conf::AUTH['mysql_password'],
            'database' => \rnr\conf::AUTH['mysql_database']
          )
        );
        $mysql_data = new \rnr\mysql_data($mysql);

        if
        (
          $mysql_data->make_json
          (
            array
            (
              array('expression' => 'rnr_f_users_username(user_id)', 'name' => 'username'     ),
              array('expression' => 'value',                         'name' => 'session'      ),
              array('expression' => 'creation_time',                 'name' => 'creation_time')
            ),
            'SELECT '.\rnr\mysql_data::FIELDS.' FROM rnr_sessions',
            true,
            $json_result
          ) === false
        )
          return $mysql_data->get_error();
        return \rnr\out::ok_json($json_result);
      }
    }

  }

?>
