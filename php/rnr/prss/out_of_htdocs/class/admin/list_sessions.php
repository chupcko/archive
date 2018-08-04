<?php

  if(isset($prss_pass) === false or $prss_pass !== true)
    die();

  class admin_list_sessions_c implements prss_request_i
  {
    public function run($who, $arguments)
    {
      global $prss_mysql_data;

      $fields_description = array
      (
        array('expression' => 'prss_f_users_username(user_id)', 'name' => 'username'     ),
        array('expression' => 'value',                          'name' => 'session'      ),
        array('expression' => 'creation_time',                  'name' => 'creation_time')
      );
      if($prss_mysql_data->make_json($fields_description, 'SELECT '.prss_mysql_data_c::FIELDS.' FROM prss_sessions', true, $json_result) === false)
        return $prss_mysql_data->error;

      return prss_out_c::json($json_result);
    }
  }

?>
