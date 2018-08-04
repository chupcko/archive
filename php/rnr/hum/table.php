<?php

  #
  # apstraktana klasa koja reflektuje sql tabelu
  # sve ostale klase koje su vezane za sql tabelu nasledjuju ovu klasu
  #
  abstract class table
  {
    # kolone tabele
    protected $data = array();

    # treba da vrati ime tabele
    protected abstract static function table_name();

    # treba da vrati array sa imenima kolona tabele, ukljucujuci i id
    protected abstract static function data_names();

    # treba da vrati array sa imenima kolona koje ne ispisujemo u toString
    protected abstract static function forbiden_names();

    # treba da vrati true ili false u zavisnosti od ispravnosti podataka
    public abstract function validate();

    # konstruktor puni kolone tabele iz spiska dozvoljenih
    public function __construct($data = null)
    {
      if
      (
        is_null($data) === false and
        is_array($data) === true
      )
      {
        foreach($data as $key => $value)
        {
          if(in_array($key, static::data_names()) === true)
          {
            $this->data[$key] = $value;
          }
        }
      }
    }

    # magic za sve kolone tabele
    public function __get($key)
    {
      if
      (
        in_array($key, static::data_names()) === true and
        array_key_exists($key, $this->data) === true
      )
      {
        return $this->data[$key];
      }
      return null;
    }

    # magic za sve kolone tabele
    public function __set($key, $value)
    {
      if(in_array($key, static::data_names()) === true)
      {
        $this->data[$key] = $value;
      }
    }

    # magic za __toString
    public function __toString()
    {
      $data = $this->data;
      foreach(static::forbiden_names() as $name)
      {
        unset($data[$name]);
      }
      return json_encode($data);
    }

    # vraca da li je objekat ima id, to jest da li je u bazi
    public function have_id()
    {
      if
      (
        array_key_exists('id', $this->data) === true and
        is_null($this->id) !== true and
        is_numeric($this->id) === true
      )
      {
        return true;
      }
      return false;
    }

    # ucitava podatke iz baze, radije koristim staticnu metodu find_by_id
    public function load()
    {
      if($this->have_id() === true)
      {
        $row = database::pdo()->prepare('SELECT * FROM '.static::table_name().' WHERE id = :id ');
        $row->execute(array('id' => $this->id));
        $this->data = $row->fetch(PDO::FETCH_ASSOC);
        if($this->data === false)
        {
          error_log::set_error($row->errorInfo());
          return false;
        }
        return true;
      }
      return false;
    }

    # snima podatke u bazu, ili kao nov ili promenjen, neophodno da izmenjen objekat "sinhronizuje" sa bazom
    public function save()
    {
      if($this->validate() !== true)
      {
        return false;
      }

      $set_string = '';
      $bind = [];
      $first = true;
      foreach($this->data as $key => $value)
      {
        if($key !== 'id')
        {
          if($first !== true)
          {
            $set_string .= ', ';
          }
          $first = false;
          $set_string .= $key.' = :'.$key;
          $bind[$key] = $value;
        }
      }

      if($this->have_id() === true)
      {
        $command = database::pdo()->prepare('UPDATE '.static::table_name().' SET '.$set_string.' WHERE id = :id');
        $bind['id'] = $this->id;
        $result = $command->execute($bind);
      }
      else
      {
        $command = database::pdo()->prepare('INSERT INTO '.static::table_name().' SET '.$set_string);
        $result = $command->execute($bind);
        $this->id = database::pdo()->lastInsertId();
      }
      if($result === false)
      {
        error_log::set_error($command->errorInfo());
      }
      return $result;
    }

    # brise iz baze
    public function delete()
    {
      if($this->have_id() === true)
      {
        $command = database::pdo()->prepare('DELETE FROM '.static::table_name().' WHERE id = :id');
        if($command->execute(array('id' => $this->id)) !== true)
        {
          error_log::set_error($command->errorInfo());
          return false;
        }
        $this->id = null;
        return $command->rowCount();
      }
      return true;
    }

    # vraca niz svih iz baze, uz dodatni sql kojim moze puno toga da se uradi, opasno mesto.
    # ali olaksava pisanje nekih staticnih upita.
    public static function all($added_sql = '')
    {
      $rows = database::pdo()->prepare('SELECT * FROM '.static::table_name().' '.$added_sql);
      $rows->execute();
      $rows->setFetchMode(PDO::FETCH_CLASS, get_called_class());
      return $rows->fetchAll();
    }

    # pronalazi objekat iz baze po id-u i vraca kao instancu iz pozvane klase, ili false
    public static function find_by_id($id)
    {
      $row = database::pdo()->prepare('SELECT * FROM '.static::table_name().' WHERE id = :id ');
      $row->execute(array('id' => $id));
      $row->setFetchMode(PDO::FETCH_CLASS, get_called_class());
      return $row->fetch();
    }

    # pronalazi niz svih onih koji zadovoljavaju da su vrednosti iz niza machovane
    public static function find_by_value(array $values)
    {
      $where_string = 'TRUE';
      $bind = [];
      foreach($values as $key => $value)
      {
        $where_string .= ' AND '.$key.' = :'.$key;
        $bind[$key] = $value;
      }
      $rows = database::pdo()->prepare('SELECT * FROM '.static::table_name().' WHERE '.$where_string);
      $rows->execute($bind);
      $rows->setFetchMode(PDO::FETCH_CLASS, get_called_class());
      return $rows->fetchAll();
    }
  }

  /*

    Neki nacini koriscenja, izvedena klasa je na primer foo, ima kolone t1 i t2 (kao i id).

    Niz svih foo-ova iz baze:
      foo::all()

    Nalazi odredjeni foo po id:
      $f = foo::find_by_id(1);

    Nalazi odredjeni foo po uslovu t1 = '111' i t2 = '222':
      $f = foo::find_by_value(array('t1' => '111', 't2' => '222'));

    Pravi novog foo:
      $f = new foo(array('t1' => '111', 't2' => '222'));
      $f->save();

    Menja nesto u postojocem foo:
      $f = foo::find_by_id(1);
      $f->t1 = '11';
      $f->save();

    Brise postojeci foo:
      $f = foo::find_by_id(1);
      $f->delete();

  */
?>
