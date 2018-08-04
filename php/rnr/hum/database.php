<?php

  #
  # staticna klasa sa parametrima za konekciju ka database
  #
  class database_params
  {
    public static $hostname = 'localhost';
    public static $username = 'hum';
    public static $password = 'hum';
    public static $database = 'hum';
  }

  #
  # singleton za database, prosto se koristi database::pdo() za konkeciju
  # koristi staticku klasu database_params za parametre
  #
  class database
  {
    private static $_pdo = null;

    # sprecavamo pravljenje objekta
    public function __construct()
    {
    }

    # a i kloniranje
    public function __clone()
    {
    }

    # staticka metoda koja instancira $_pdo i vraca ga
    public static function pdo()
    {
      if(is_null(self::$_pdo) === true)
      {
        try
        {
          self::$_pdo = new PDO
          (
            'mysql:host='.database_params::$hostname.';dbname='.database_params::$database,
            database_params::$username,
            database_params::$password
          );
        }
        catch(PDOException $e)
        {
          error_log::set_error($e->getMessage());
        }
      }
      return self::$_pdo;
    }
  }

?>
