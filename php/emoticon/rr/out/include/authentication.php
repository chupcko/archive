<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  class rr_authentication
  {
    public $error;
    private $mysql_query;

    function __construct(&$mysql_query)
    {
      $this->mysql_query = false;
      if(@get_class($mysql_query) === 'rr_mysql_query')
        $this->mysql_query = &$mysql_query;
    }

    function __destruct()
    {
      $this->mysql_query = false;
    }

    private function set_error($error)
    {
      $this->error = $error;
      return false;
    }

    public function expire_all_sessions()
    {
      $this->error = false;
      if($this->mysql_query === false)
        return $this->set_error('Not connected');
      if($this->mysql_query->execute('DELETE FROM rr_sessions WHERE expire_time < NOW()') === false)
        return $this->set_error($this->mysql_query->error);
      return true;
    }

    public function get_request_data($name, $developing)
    {
      $this->error = false;
      if($this->mysql_query === false)
        return $this->set_error('Not connected');
      if($developing === false)
        $developing_query = ' AND developing = FALSE';
      else
        $developing_query = '';
      if($this->mysql_query->execute('SELECT id, filename, license_id FROM rr_requests WHERE name = \''.addslashes($name).'\''.$developing_query) === false)
        return $this->set_error($this->mysql_query->error);
      if($this->mysql_query->get_number_rows() != 1)
        return false;
      if($this->mysql_query->load_next_row() === false)
        return $this->set_error('System Error');
      $request_array = array
      (
        'id'         => $this->mysql_query->get_field('id'),
        'filename'   => $this->mysql_query->get_field('filename'),
        'license_id' => $this->mysql_query->get_field('license_id')
      );
      if
      (
        $request_array['id'] === false or
        $request_array['filename'] === false or
        $request_array['license_id'] === false
      )
        return $this->set_error($this->mysql_query->error);
      return $request_array;
    }

    public function get_user_id_from_session($session_value)
    {
      $this->error = false;
      if($this->mysql_query === false)
        return $this->set_error('Not connected');
      if($this->mysql_query->execute('SELECT user_id FROM rr_sessions WHERE value = \''.addslashes($session_value).'\' AND expire_time >= NOW()') === false)
        return $this->set_error($this->mysql_query->error);
      if($this->mysql_query->get_number_rows() != 1)
        return false;
      if($this->mysql_query->load_next_row() === false)
        return $this->set_error('System Error');
      $user_id = $this->mysql_query->get_field('user_id');
      if($user_id === false)
        return $this->set_error($this->mysql_query->error);
      return $user_id;
    }

    public function get_username($user_id)
    {
      $this->error = false;
      if($this->mysql_query === false)
        return $this->set_error('Not connected');
      if($this->mysql_query->execute('SELECT username FROM rr_users WHERE id = \''.addslashes($user_id).'\'') === false)
        return $this->set_error($this->mysql_query->error);
      if($this->mysql_query->get_number_rows() != 1)
        return false;
      if($this->mysql_query->load_next_row() === false)
        return $this->set_error('System Error');
      $username = $this->mysql_query->get_field('username');
      if($username === false)
        return $this->set_error($this->mysql_query->error);
      return $username;
    }

    public function have_permission($user_id, $license_id)
    {
      $this->error = false;
      if($this->mysql_query === false)
        return $this->set_error('Not connected');
      if($this->mysql_query->execute('SELECT value FROM rr_permissions WHERE user_id = \''.addslashes($user_id).'\' AND license_id = \''.addslashes($license_id).'\'') === false)
        return $this->set_error($this->mysql_query->error);
      if($this->mysql_query->get_number_rows() != 1)
      {
        if($this->mysql_query->execute('SELECT default_value FROM rr_licenses WHERE id = \''.addslashes($license_id).'\'') === false)
          return $this->set_error($this->mysql_query->error);
        if($this->mysql_query->get_number_rows() != 1 or $this->mysql_query->load_next_row() === false)
          return $this->set_error('System Error');
        $default_value = $this->mysql_query->get_field('default_value');
        if($default_value === false)
          return $this->set_error($this->mysql_query->error);
        if($default_value == 0)
          return false;
        return true;
      }
      if($this->mysql_query->load_next_row() === false)
        return $this->set_error('System Error');
      $value = $this->mysql_query->get_field('value');
      if($value === false)
        return $this->set_error($this->mysql_query->error);
      if($value == 0)
        return false;
      return true;
    }

    public function register_arguments($request_id)
    {
      $this->error = false;
      if($this->mysql_query === false)
        return $this->set_error('Not connected');
      if($this->mysql_query->execute('SELECT name, type, default_value FROM rr_arguments WHERE request_id = \''.addslashes($request_id).'\'') === false)
        return $this->set_error($this->mysql_query->error);
      $number_rows = $this->mysql_query->get_number_rows();
      if($number_rows === false)
        return $this->set_error($this->mysql_query->error);
      for($count = 0; $count < $number_rows; $count++)
      {
        if($this->mysql_query->load_next_row() === false)
          return $this->set_error($this->mysql_query->error);
        $name = $this->mysql_query->get_field('name');
        $type = $this->mysql_query->get_field('type');
        $default_value = $this->mysql_query->get_field('default_value');
        if($name === false or $type === false or $default_value === false)
          return $this->set_error($this->mysql_query->error);
        switch($type)
        {
          case 'MANDATORY':
            if(rr_register_request_variable($name, $name) === false)
              return $this->set_error('Argument "'.$name.'" is mandatory');
            break;
          case 'OPTIONAL':
            rr_register_request_variable($name, $name, $default_value);
            break;
          case 'FILE':
            if(array_key_exists($name, $_FILES) === false)
              return $this->set_error('File "'.$name.'" is mandatory');
            if($_FILES[$name]['error'] != UPLOAD_ERR_OK)
              return $this->set_error('No file "'.$name.'"');
            $GLOBALS[$name] = $_FILES[$name];
            break;
        }
      }
      return true;
    }

    public function get_arguments($request_id)
    {
      $this->error = false;
      if($this->mysql_query === false)
        return $this->set_error('Not connected');
      if($this->mysql_query->execute('SELECT name, type, default_value FROM rr_arguments WHERE request_id = \''.addslashes($request_id).'\'') === false)
        return $this->set_error($this->mysql_query->error);
      $number_rows = $this->mysql_query->get_number_rows();
      if($number_rows === false)
        return $this->set_error($this->mysql_query->error);
      $arguments = array();
      for($count = 0; $count < $number_rows; $count++)
      {
        if($this->mysql_query->load_next_row() === false)
          return $this->set_error($this->mysql_query->error);
        $name = $this->mysql_query->get_field('name');
        $type = $this->mysql_query->get_field('type');
        $default_value = $this->mysql_query->get_field('default_value');
        if($name === false or $type === false or $default_value === false)
          return $this->set_error($this->mysql_query->error);
        if($type == 'FILE')
          return $this->set_error('File arguments is not permitted in internal request');
        $arguments[$count] = array('type' => $type, 'name' => $name, 'default_value' => $default_value);
      }
      return $arguments;
    }

    public function get_user_id($username, $password)
    {
      $this->error = false;
      if($this->mysql_query === false)
        return $this->set_error('Not connected');
      if($this->mysql_query->execute('SELECT id FROM rr_users WHERE username = \''.addslashes($username).'\' AND password = \''.addslashes($password).'\'') === false)
        return $this->set_error($this->mysql_query->error);
      if($this->mysql_query->get_number_rows() != 1)
        return false;
      if($this->mysql_query->load_next_row() === false)
        return $this->set_error('System Error');
      $user_id = $this->mysql_query->get_field('id');
      if($user_id === false)
        return $this->set_error($this->mysql_query->error);
      return $user_id;
    }

    public function make_session($username, $password)
    {
      return strrev(sha1(strrev($username.':'.uniqid('rr.', true).':'.$password)));
    }

    public function register_session($user_id, $session_value)
    {
      global $rr_session_expire_time_in_seconds;
      global $rr_remote_ip;
      $this->error = false;
      if($this->mysql_query === false)
        return $this->set_error('Not connected');
      if($this->mysql_query->execute('INSERT INTO rr_sessions (user_id, value, expire_time, remote_address) VALUES (\''.addslashes($user_id).'\', \''.addslashes($session_value).'\', TIMESTAMPADD(SECOND, \''.addslashes($rr_session_expire_time_in_seconds).'\', NOW()), \''.$rr_remote_ip.'\')') === false)
        return $this->set_error($this->mysql_query->error);
      return true;
    }

    public function register_cookie($session_value)
    {
      global $rr_session_expire_time_in_seconds;
      global $rr_session_cookie_path;
      $this->error = false;
      setcookie('rr_session', $session_value, time()+$rr_session_expire_time_in_seconds, $rr_session_cookie_path);
      return true;
    }

    public function refresh_session($session_value)
    {
      global $rr_session_expire_time_in_seconds;
      $this->error = false;
      if($this->mysql_query === false)
        return $this->set_error('Not connected');
      if($this->mysql_query->execute('UPDATE rr_sessions SET expire_time = TIMESTAMPADD(SECOND, \''.addslashes($rr_session_expire_time_in_seconds).'\', NOW()) WHERE value = \''.addslashes($session_value).'\'') === false)
        return $this->set_error($this->mysql_query->error);
      return true;
    }

    public function unregister_session($session_value)
    {
      $this->error = false;
      if($this->mysql_query === false)
        return $this->set_error('Not connected');
      if($this->mysql_query->execute('DELETE FROM rr_sessions WHERE value = \''.addslashes($session_value).'\'') === false)
        return $this->set_error($this->mysql_query->error);
      return true;
    }

    public function unregister_cookie()
    {
      global $rr_session_cookie_path;
      $this->error = false;
      setcookie('rr_session', '', 0, $rr_session_cookie_path);
      return true;
    }
  }

?>
