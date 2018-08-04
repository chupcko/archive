<?php

  #
  # Staticna klasa za logovanje gresaka
  #
  class error_log
  {
    public static $errors = [];

    # staticka metoda za dodavanje nove greske
    public static function set_error($what)
    {
      static::$errors[] = $what;
    }

    public static function trace()
    {
      var_dump(static::$errors);
    }
  }

  #
  # Neke funkcije vracaju niz objekata, objekti kroz magic __toString
  # dobijaju JSON reprezentaciju, ovim se dobija JSON reprezenatcija za
  # niz objekata.
  #
  function array_to_json_string(array $array)
  {
    $output = '[';
    $first = true;
    foreach($array as $value)
    {
      if($first !== true)
      {
        $output .= ',';
      }
      $first = false;
      $output .= $value->__toString();
    }
    $output .= ']';
    return $output;
  }

?>
