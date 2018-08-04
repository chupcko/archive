<?php

  namespace rnr
  {

    if(isset($rnr_pass) === false or $rnr_pass !== true)
      exit();

    class mysql extends \mysqli
    {
      use error_base;

      private $conf = false;

      public function __construct($conf)
      {
        $this->conf = $conf;
        parent::__construct
        (
          $this->conf['hostname'],
          $this->conf['username'],
          $this->conf['password'],
          $this->conf['database']
        );
        if(\mysqli_connect_error())
          out::error(301, 'mysql error('.mysqli_connect_errno().') '.mysqli_connect_error());
      }

      public function __destruct()
      {
        parent::close();
      }
    }

    class mysql_query
    {
      use error_base;

      public $mysql = false;
      private $result = false;
      private $row = false;

      public function __construct(mysql $mysql)
      {
        $this->mysql = $mysql;
      }

      public function execute($query)
      {
        $this->clean_error();
        if
        (
          $this->result !== false and
          $this->result !== true
        )
           $this->result->close();
        $this->result = $this->mysql->query($query);
        if($this->result === false)
          return $this->set_error('Bad query: '.$query);
        $this->row = false;
        return true;
      }

      public function clean()
      {
        $this->clean_error();
        if
        (
          $this->result !== false and
          $this->result !== true
        )
          $this->result->close();
        $this->result = false;
        $this->row = false;
        return true;
      }

      public function get_affected_rows()
      {
        $this->clean_error();
        if($this->result !== true)
          return $this->set_error('Not queried');
        return $this->mysql->affected_rows;
      }

      public function get_insert_id()
      {
        $this->clean_error();
        if($this->result !== true)
          return $this->set_error('Not queried');
        return $this->mysql->insert_id;
      }

      public function get_number_rows()
      {
        $this->clean_error();
        if
        (
          $this->result === false or
          $this->result === true
        )
          return $this->set_error('Not queried');
        return $this->result->num_rows;
      }

      public function get_number_fields()
      {
        $this->clean_error();
        if
        (
          $this->result === false or
          $this->result === true
        )
          return $this->set_error('Not queried');
        return $this->result->field_count;
      }

      public function seek_row($position)
      {
        $this->clean_error();
        if
        (
          $this->result === false or
          $this->result === true
        )
          return $this->set_error('Not queried');
        $this->result->data_seek($position);
        return true;
      }

      public function load_next_row()
      {
        $this->clean_error();
        if
        (
          $this->result === false or
          $this->result === true
        )
          return $this->set_error('Not queried');
        $this->row = $this->result->fetch_assoc();
        if(is_null($this->row) === true)
        {
          $this->row = false;
          return false;
        }
        return true;
      }

      public function get_field($name)
      {
        $this->clean_error();
        if($this->row === false)
          return $this->set_error('Not rowed');
        if(array_key_exists($name, $this->row) === false)
          return $this->set_error('No exists field: '.$name);
        return $this->row[$name];
      }

      public function escape($input)
      {
        $this->clean_error();
        return $this->mysql->real_escape_string($input);
      }

      public function __destruct()
      {
        $this->clean();
      }
    }

    class mysql_data
    {
      use error_base;

      const FIELDS = '##FIELDS##';
      private $mysql_query = false;

      public function __construct(mysql $mysql)
      {
        $this->mysql_query = new mysql_query($mysql);
      }

      private function make_query_fields($fields)
      {
        $query_part = '';
        for($i = 0; $i < count($fields); $i++)
        {
          if($query_part != '')
            $query_part .=', ';
          $query_part .= $this->mysql_query->escape($fields[$i]['expression']).' AS '.$this->mysql_query->escape($fields[$i]['name']);
        }
        return $query_part;
      }

      private function make_data_array($fields_description, $data_description)
      {
        if($this->mysql_query->load_next_row() === false)
          return $this->set_error($this->mysql_query->get_error());
        $mysql_array = array();
        foreach($fields_description as $fields_description_value)
        {
          $name = $fields_description_value['name'];
          $mysql_array[$name] = $this->mysql_query->get_field($name);
          if($mysql_array[$name] === false)
            return $this->set_error($this->mysql_query->get_error());
        }
        if($data_description === true)
          return $mysql_array;
        $data_array = array();
        foreach($data_description as $data_description_value)
          switch($data_description_value['type'])
          {
            case 'copy':
              $data_array[$data_description_value['name']] = $mysql_array[$data_description_value['from']];
              break;
            case 'calculate':
              $arguments = '';
              foreach($data_description_value['arguments'] as $argument)
              {
                if($arguments != '')
                  $arguments .= ', ';
                $arguments .= '$mysql_array[\''.$argument.'\']';
              }
              $result = @eval('return '.$data_description_value['call'].'('.$arguments.');');
              if($result === false)
                return $this->set_error('Syntax error in eval');
              $data_array[$data_description_value['name']] = $result;
              break;
          }
        return $data_array;
      }

      public function make_json($fields_description, $query, $data_description, &$result, $indent = 1)
      {
        $this->clean_error();
        if($this->mysql_query->execute(str_replace(self::FIELDS, $this->make_query_fields($fields_description), $query)) === false)
          return $this->set_error($this->mysql_query->get_error());
        $number_rows = $this->mysql_query->get_number_rows();
        if($number_rows === false)
          return $this->set_error($this->mysql_query->get_error());
        if($number_rows === 0)
        {
          $result = '[]';
          return true;
        }
        $result = str_repeat('  ', $indent).'['.PHP_EOL;
        $first_row = true;
        for($count = 0; $count < $number_rows; $count++)
        {
          if($first_row !== true)
            $result .= ','.PHP_EOL;
          $first_row = false;
          $data_array = $this->make_data_array($fields_description, $data_description);
          if($data_array === false)
            return false;
          $result .= str_repeat('  ', $indent+1).'{'.PHP_EOL;
          $first_data = true;
          foreach($data_array as $data_array_key => $data_array_value)
          {
            if($first_data !== true)
              $result .= ','.PHP_EOL;
            $first_data = false;
            $result .= str_repeat('  ', $indent+2).'"'.addslashes($data_array_key).'":"'.addslashes($data_array_value).'"';
          }
          $result .= PHP_EOL.str_repeat('  ', $indent+1).'}';
        }
        $result .= PHP_EOL.str_repeat('  ', $indent).']';
        $this->mysql_query->clean();
        return true;
      }

      public function make_array($fields_description, $query, $data_description, &$result)
      {
        $this->clean_error();
        if($this->mysql_query->execute(str_replace(self::FIELDS, $this->make_query_fields($fields_description), $query)) === false)
          return $this->set_error($this->mysql_query->get_error());
        $number_rows = $this->mysql_query->get_number_rows();
        if($number_rows === false)
          return $this->set_error($this->mysql_query->get_error());
        $result = array();
        for($count = 0; $count < $number_rows; $count++)
        {
          $data_array = $this->make_data_array($fields_description, $data_description);
          if($data_array === false)
            return false;
          $result[$count] = $data_array;
        }
        $this->mysql_query->clean();
        return true;
      }
    }

  }

?>
