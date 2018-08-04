<?php

  namespace rnr
  {

    if(isset($rnr_pass) === false or $rnr_pass !== true)
      exit();

    class auth
    {
      const SESSION_NAME = 'rnr';

      private $conf = false;
      private $mysql = false;
      private $mysql_query = false;

      public $user_id = false;
      public $username = false;
      public $session = false;

      public function __construct($conf)
      {
        $this->conf = $conf;
        $this->mysql = new mysql
        (
          array
          (
            'hostname' => $this->conf['mysql_hostname'],
            'username' => $this->conf['mysql_username'],
            'password' => $this->conf['mysql_password'],
            'database' => $this->conf['mysql_database']
          )
        );
        $this->mysql_query = new mysql_query($this->mysql);
      }

      private function make_session($username)
      {
        return strrev(sha1(strrev($username.':'.uniqid('rnr', true).':'.$username)));
      }

      public function register($username, $password)
      {
        if
        (
          $this->mysql_query->execute
          (
            sprintf
            (
              <<< 'END'
SELECT
  id as user_id
FROM
  rnr_users
WHERE
  username = "%s" AND
  password = "%s"
END
              ,
              $this->mysql_query->escape($username),
              md5($password)
            )
          ) === false
        )
          out::fatal(-401, $this->mysql_query->get_error());
        if($this->mysql_query->get_number_rows() != 1)
          out::error(401, 'Bad authentication');
        if($this->mysql_query->load_next_row() === false)
          out::fatal(-402, $this->mysql_query->get_error());
        $this->user_id = $this->mysql_query->get_field('user_id');
        if($this->user_id === false)
          out::fatal(-403, $this->mysql_query->get_error());
        $this->username = $username;
        $this->session = $this->make_session($username);
        if
        (
          $this->mysql_query->execute
          (
            sprintf
            (
              <<< 'END'
INSERT INTO rnr_sessions
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
              $this->user_id,
              $this->session
            )
          ) === false
        )
          out::fatal(-404, $this->mysql_query->get_error());
        setcookie(self::SESSION_NAME, $this->session, time()+$this->conf['session_expire_time_in_seconds'], $this->conf['session_cookie_path']);
      }

      public function allow($license = true)
      {
        in::register_cookie($this->session, self::SESSION_NAME, false);
        if($this->session === false)
          out::error(402, 'First authenticate');
        if($license === true)
          $query = sprintf
          (
            <<< 'END'
SELECT
  user_id as user_id,
  rnr_f_users_username(user_id) as username
FROM
  rnr_sessions
WHERE
  value = "%s"
END
            ,
            $this->mysql_query->escape($this->session)
          );
        else
          $query = sprintf
          (
            <<< 'END'
SELECT
  rnr_sessions.user_id as user_id,
  rnr_f_users_username(rnr_sessions.user_id) as username
FROM
  rnr_sessions,
  rnr_permissions
WHERE
  rnr_sessions.value = "%s" AND
  rnr_sessions.user_id = rnr_permissions.user_id AND
  rnr_permissions.license_id = rnr_f_licenses_id("%s")
END
            ,
            $this->mysql_query->escape($this->session),
            $license
          );
        if($this->mysql_query->execute($query) === false)
          out::fatal(-405, $this->mysql_query->get_error());
        if($this->mysql_query->get_number_rows() != 1)
          out::error(401, 'Bad authentication');
        if($this->mysql_query->load_next_row() === false)
          out::fatal(-406, $this->mysql_query->get_error());
        $this->user_id = $this->mysql_query->get_field('user_id');
        if($this->user_id === false)
          out::fatal(-407, $this->mysql_query->get_error());
        $this->username = $this->mysql_query->get_field('username');
        if($this->username === false)
          out::fatal(-408, $this->mysql_query->get_error());
      }

      public function get_licenses()
      {
        if($this->session === false)
          out::error(402, 'First authenticate');
        if
        (
          $this->mysql_query->execute
          (
            sprintf
            (
              <<< 'END'
SELECT
  rnr_f_licenses_name(license_id) as name
FROM
  rnr_permissions
WHERE
  user_id = %d
ORDER BY
  name
END
              ,
              $this->user_id
            )
          ) === false
        )
          out::fatal(-409, $this->mysql_query->get_error());
        $number_rows = $this->mysql_query->get_number_rows();
        if($number_rows === false)
          out::fatal(-410, $this->mysql_query->get_error());
        $result_array = array();
        for($count = 0; $count < $number_rows; $count++)
        {
          if($this->mysql_query->load_next_row() === false)
            out::fatal(-411, $this->mysql_query->get_error());
          $result_array[$count] = $this->mysql_query->get_field('name');
          if($result_array[$count] === false)
            out::fatal(-412, $this->mysql_query->get_error());
        }
        return $result_array;
      }

      public function unregister()
      {
        if($this->session === false)
          out::error(402, 'First authenticate');
        if
        (
          $this->mysql_query->execute
          (
            sprintf
            (
              <<< 'END'
DELETE FROM
  rnr_sessions
WHERE
  value = "%s"
END
              ,
              $this->mysql_query->escape($this->session)
            )
          ) === false
        )
          out::fatal(-413, $this->mysql_query->get_error());
        setcookie(self::SESSION_NAME, '', 0, $this->conf['session_cookie_path']);
      }

      public function cleanup_sessions()
      {
        if
        (
          $this->mysql_query->execute
          (
            sprintf
            (
              <<< 'END'
DELETE FROM
  rnr_sessions
WHERE
  DATE_ADD(creation_time, INTERVAL %d SECOND) < NOW()
END
              ,
              $this->conf['session_expire_time_in_seconds']
            )
          ) === false
        )
          out::fatal(-414, $this->mysql_query->get_error());
      }
    }

  }

?>
