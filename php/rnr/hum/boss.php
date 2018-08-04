<?php

  #
  # Klasa koja reprezenutuje boss-a, nasledjuje sve od employer, ali auth
  # proverava da li je boss (ima ga kao boss_id negde)
  #
  class boss extends employer
  {
    # proverava da li ima onih kojim boss_id podesan na ovaj id
    public function is_boss()
    {
      if($this->have_id() === true)
      {
        if(count(static::find_by_value(array('boss_id' => $this->id))) > 0)
        {
          return true;
        }
      }
      return false;
    }

    # staticna provera da li je zadovoljena autentikacija
    # ako nije vraca false, a ako jeste vraca objekat boss
    # koristi se na pocetku svih akcija koje izvrsava boss
    public static function auth($username, $password)
    {
      $result = static::find_by_value(array('username' => $username, 'password' => md5($password)));
      if(count($result) === 0)
      {
        error_log::set_error('employer bad auth');
        return false;
      }
      if($result[0]->is_boss() !== true)
      {
        error_log::set_error('not boss');
        return false;
      }
      return $result[0];
    }

    # vraca niz svih zaposlenih ovog boss-a
    public function all_employers()
    {
      if($this->have_id() !== true)
      {
        return [];
      }
      return static::find_by_value(array('boss_id' => $this->id));
    }
  }

?>
