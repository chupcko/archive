<?php

  #
  # klasa employer je odraz reda tabele employers
  # pristupa se na nacin kao i apstraktnoj klasi table
  #
  class employer extends table
  {
    # ime tabele
    protected static function table_name()
    {
      return 'employers';
    }

    # imena kolona
    protected static function data_names()
    {
      return array('id', 'username', 'password', 'boss_id', 'vacation_days');
    }

    # Sta ne ispisujemo u toString
    protected static function forbiden_names()
    {
      return array('password');
    }

    # provara integriteta stranog kljuca
    public function validate()
    {
      if(is_null($this->boss_id) !== true)
      {
        if(static::find_by_id($this->boss_id) === false)
        {
          error_log::set_error('Wrong boss');
          return false;
        }
      }
      return true;
    }

    # provera autentifikacije, vraca objekat ako je ispravan, prvi korak svakog rada
    # ako nije proslo vraca false
    public static function auth($username, $password)
    {
      $result = static::find_by_value(array('username' => $username, 'password' => md5($password)));
      if(count($result) === 0)
      {
        error_log::set_error('employer bad auth');
        return false;
      }
      return $result[0];
    }
  }

?>
