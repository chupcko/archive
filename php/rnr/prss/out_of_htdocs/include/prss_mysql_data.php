<?php

  if(isset($prss_pass) === false or $prss_pass !== true)
    die();

  class prss_mysql_data_c extends prss_root_c
  {
    const FIELDS = '##FIELDS##';
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
        return $this->set_error($this->mysql_query->error);
      $mysql_array = array();
      foreach($fields_description as $fields_description_value)
      {
        $name = $fields_description_value['name'];
        $mysql_array[$name] = $this->mysql_query->get_field($name);
        if($mysql_array[$name] === false)
          return $this->set_error($this->mysql_query->error);
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

    public function make_xml($fields_description, $query, $data_description, &$result, $indent = 1)
    {
      $this->clean_error();
      if($this->mysql_query === false)
        return $this->set_error('Not connected');
      if($this->mysql_query->execute(str_replace(self::FIELDS, $this->make_query_fields($fields_description), $query)) === false)
        return $this->set_error($this->mysql_query->error);
      $number_rows = $this->mysql_query->get_number_rows();
      if($number_rows === false)
        return $this->set_error($this->mysql_query->error);
      if($number_rows == 0)
      {
        $result = str_repeat('  ', $indent).'<data number="0"/>'.PHP_EOL;
        return true;
      }
      $result = str_repeat('  ', $indent).'<data number="'.$number_rows.'">'.PHP_EOL;
      for($count = 0; $count < $number_rows; $count++)
      {
        $data_array = $this->make_data_array($fields_description, $data_description);
        if($data_array === false)
          return false;
        $result .= str_repeat('  ', $indent+1).'<row count="'.$count.'">'.PHP_EOL;
        foreach($data_array as $data_array_key => $data_array_value)
          $result .= str_repeat('  ', $indent+2).'<'.htmlspecialchars($data_array_key).'>'.htmlspecialchars($data_array_value).'</'.htmlspecialchars($data_array_key).'>'.PHP_EOL;
        $result .= str_repeat('  ', $indent+1).'</row>'.PHP_EOL;
      }
      $result .= str_repeat('  ', $indent).'</data>'.PHP_EOL;
      return true;
    }

    public function make_json($fields_description, $query, $data_description, &$result, $indent = 1)
    {
      $this->clean_error();
      if($this->mysql_query === false)
        return $this->set_error('Not connected');
      if($this->mysql_query->execute(str_replace(self::FIELDS, $this->make_query_fields($fields_description), $query)) === false)
        return $this->set_error($this->mysql_query->error);
      $number_rows = $this->mysql_query->get_number_rows();
      if($number_rows === false)
        return $this->set_error($this->mysql_query->error);
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
      return true;
    }

    public function make_array($fields_description, $query, $data_description, &$result)
    {
      $this->clean_error();
      if($this->mysql_query === false)
        return $this->set_error('Not connected');
      if($this->mysql_query->execute(str_replace(self::FIELDS, $this->make_query_fields($fields_description), $query)) === false)
        return $this->set_error($this->mysql_query->error);
      $number_rows = $this->mysql_query->get_number_rows();
      if($number_rows === false)
        return $this->set_error($this->mysql_query->error);

      $result = array();
      for($count = 0; $count < $number_rows; $count++)
      {
        $data_array = $this->make_data_array($fields_description, $data_description);
        if($data_array === false)
          return false;
        $result[$count] = $data_array;
      }
      return true;
    }
  }

?>
