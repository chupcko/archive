<?php

  if(isset($prss_pass) === false or $prss_pass !== true)
    die();

  class prss_authentication_c extends prss_root_c
  {
    private $mysql_query;

    function __construct(&$mysql_connection)
    {
      parent::__construct();
      $this->mysql_query = false;
      if(@get_class($mysql_connection) === 'prss_mysql_connection_c')
        $this->mysql_query = new prss_mysql_query_c($mysql_connection);
    }

    function __destruct()
    {
      if($this->mysql_query !== false)
        $this->mysql_query->clean();
      $this->mysql_query = false;
    }

    public function get_data($session, $license)
    {
      $this->clean_error();
      if($this->mysql_query === false)
        return $this->set_error('Not connected');

      if($license === false)
        $query = sprintf
        (
          <<< 'END'
SELECT
  prss_f_users_username(user_id) as username,
  user_id as user_id
FROM
  prss_sessions
WHERE
  value = "%s"
END
          ,
          $this->mysql_query->escape($session)
        );
      else
        $query = sprintf
        (
          <<< 'END'
SELECT
  prss_f_users_username(prss_sessions.user_id) as username,
  prss_sessions.user_id as user_id
FROM
  prss_sessions,
  prss_permissions
WHERE
  prss_sessions.value = "%s" AND
  prss_sessions.user_id = prss_permissions.user_id AND
  prss_permissions.license_id = prss_f_licenses_id("%s")
END
          ,
          $this->mysql_query->escape($session),
          $license
        );
      if($this->mysql_query->execute($query) === false)
        return $this->set_error($this->mysql_query->error);
      if($this->mysql_query->get_number_rows() != 1)
        return $this->set_error('Bad authentication');
      if($this->mysql_query->load_next_row() === false)
        return $this->set_error($this->mysql_query->error);
      $username = $this->mysql_query->get_field('username');
      $user_id = $this->mysql_query->get_field('user_id');
      if
      (
        $username === false or
        $user_id === false
      )
        return $this->set_error('System ERROR');
      return array
      (
        'username' => $username,
        'user_id'  => $user_id
      );
    }

    public function get_session_data($session)
    {
      $this->clean_error();
      return $this->get_data($session, false);
    }

    private function make_session($username)
    {
      return strrev(sha1(strrev($username.':'.uniqid('prss', true).':'.$username)));
    }

    public function register_cookie($session)
    {
      global $prss_session_expire_time_in_seconds;
      global $prss_session_cookie_path;
      $this->clean_error();
      setcookie('prss_session', $session, time()+$prss_session_expire_time_in_seconds, $prss_session_cookie_path);
      return true;
    }

    public function unregister_cookie()
    {
      global $prss_session_cookie_path;
      $this->clean_error();
      setcookie('prss_session', '', 0, $prss_session_cookie_path);
      return true;
    }

    public function register($username, $password)
    {
      $this->clean_error();
      if($this->mysql_query === false)
        return $this->set_error('Not connected');

      $query = sprintf
      (
        <<< 'END'
SELECT
  id as user_id
FROM
  prss_users
WHERE
  username = "%s" AND
  password = "%s"
END
        ,
        $this->mysql_query->escape($username),
        md5($password)
      );
      if($this->mysql_query->execute($query) === false)
        return $this->set_error($this->mysql_query->error);
      if($this->mysql_query->get_number_rows() != 1)
        return $this->set_error('Bad authentication');
      if($this->mysql_query->load_next_row() === false)
        return $this->set_error($this->mysql_query->error);
      $user_id = $this->mysql_query->get_field('user_id');
      if($user_id === false)
        return $this->set_error('System ERROR');

      $session = $this->make_session($username);
      $query = sprintf
      (
        <<< 'END'
INSERT INTO prss_sessions
(
  user_id,
  value,
  creation_time
)
VALUES
(
  %d,
  "%s",
  NOW()
)
END
        ,
        $user_id,
        $session
      );
      if($this->mysql_query->execute($query) === false)
        return $this->set_error($this->mysql_query->error);

      $this->register_cookie($session);
      return true;
    }

    public function unregister($session)
    {
      $this->clean_error();
      if($this->mysql_query === false)
        return $this->set_error('Not connected');

      $query = sprintf
      (
        <<< 'END'
DELETE FROM
  prss_sessions
WHERE
  value = "%s"
END
        ,
        $this->mysql_query->escape($session)
      );
      if($this->mysql_query->execute($query) === false)
        return $this->set_error($this->mysql_query->error);
      $this->unregister_cookie();
      return true;
    }

    public function clean_sessions()
    {
      global $prss_session_expire_time_in_seconds;
      $this->clean_error();
      if($this->mysql_query === false)
        return $this->set_error('Not connected');

      $query = sprintf
      (
        <<< 'END'
DELETE FROM
  prss_sessions
WHERE
  DATE_ADD(creation_time, INTERVAL %d SECOND) < NOW()
END
        ,
        $prss_session_expire_time_in_seconds
      );
      if($this->mysql_query->execute($query) === false)
        return $this->set_error($this->mysql_query->error);
      return true;
    }

    public function get_licenses($user_id)
    {
      $query = sprintf
      (
        <<< 'END'
SELECT
  prss_f_licenses_name(license_id) as name
FROM
  prss_permissions
WHERE
  user_id = %d
ORDER BY
  name
END
        ,
        $user_id
      );
      if($this->mysql_query->execute($query) === false)
        return $this->set_error($this->mysql_query->error);
      $number_rows = $this->mysql_query->get_number_rows();
      if($number_rows === false)
        return $this->set_error($this->mysql_query->error);
      $result_array = array();
      for($count = 0; $count < $number_rows; $count++)
      {
        if($this->mysql_query->load_next_row() === false)
          return $this->set_error($this->mysql_query->error);
        $result_array[$count] = $this->mysql_query->get_field('name');
        if($result_array[$count] === false)
          return $this->set_error($this->mysql_query->error);
      }
      return $result_array;
    }
  }

?>
