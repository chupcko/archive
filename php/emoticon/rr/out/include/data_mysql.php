<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  define('RR_DATA_MYSQL_FIELDS', '##FIELDS##');

  class rr_data_mysql
  {
    public $error;
    private $mysql_query;

    function __construct(&$mysql_connection)
    {
      $this->mysql_query = false;
      if(@get_class($mysql_connection) === 'rr_mysql_connection')
        $this->mysql_query = new rr_mysql_query($mysql_connection);
    }

    function __destruct()
    {
      if($this->mysql_query !== false)
        $this->mysql_query->clean();
      $this->mysql_query = false;
    }

    private function set_error($error)
    {
      $this->error = $error;
      return false;
    }

    private function make_query_fields($fields)
    {
      $query_part = '';
      for($i = 0; $i < count($fields); $i++)
      {
        if($query_part != '')
          $query_part .=', ';
        $query_part .= $fields[$i]['expression'].' AS '.$fields[$i]['name'];
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

    public function make_xml($fields_description, $query, $data_description, &$result)
    {
      $this->error = false;
      if($this->mysql_query === false)
        return $this->set_error('Not connected');
      if($this->mysql_query->execute(str_replace(RR_DATA_MYSQL_FIELDS, $this->make_query_fields($fields_description), $query)) === false)
        return $this->set_error($this->mysql_query->error);
      $number_rows = $this->mysql_query->get_number_rows();
      if($number_rows === false)
        return $this->set_error($this->mysql_query->error);
      if($number_rows == 0)
      {
        $result = '  <data number="0"/>'."\n";
        return true;
      }
      $result = '  <data number="'.$number_rows.'">'."\n";
      for($count = 0; $count < $number_rows; $count++)
      {
        $data_array = $this->make_data_array($fields_description, $data_description);
        if($data_array === false)
          return false;
        $result .= '    <row count="'.$count.'">'."\n";
        foreach($data_array as $data_array_key => $data_array_value)
          $result .= '      <'.$data_array_key.'>'.htmlspecialchars($data_array_value).'</'.$data_array_key.'>'."\n";
        $result .= '    </row>'."\n";
      }
      $result .= '  </data>'."\n";
      return true;
    }

    public function make_array($fields_description, $query, $data_description, &$result)
    {
      $this->error = false;
      if($this->mysql_query === false)
        return $this->set_error('Not connected');
      if($this->mysql_query->execute(str_replace(RR_DATA_MYSQL_FIELDS, $this->make_query_fields($fields_description), $query)) === false)
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
