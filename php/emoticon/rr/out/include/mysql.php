<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  class rr_mysql_connection
  {
    public $error;
    private $database;
    private $hostname;
    private $username;
    private $password;
    public $link_id;
    private $db_queries_next_index;
    private $db_queries;

    function __construct($database = 'rr', $hostname = 'localhost', $username = 'rr', $password = 'rr')
    {
      $this->error = false;
      $this->database = $database;
      $this->hostname = $hostname;
      $this->username = $username;
      $this->password = $password;
      $this->link_id = false;
      $this->db_queries_next_index = 0;
      $this->db_queries = array();
    }

    function __destruct()
    {
      $this->disconnect();
    }

    private function set_error($error)
    {
      $this->error = $error;
      return false;
    }

    public function connect()
    {
      $this->error = false;
      if($this->link_id !== false)
        return $this->set_error('Already connected');
      $this->link_id = @mysql_connect($this->hostname, $this->username, $this->password);
      if($this->link_id === false)
        return $this->set_error('Bad connection parameters');
      if(@mysql_select_db($this->database, $this->link_id) === false)
      {
        @mysql_close($this->link_id);
        $this->link_id = false;
        return $this->set_error('Bad database');
      }
      return true;
    }

    public function disconnect()
    {
      $this->error = false;
      if($this->link_id === false)
        return $this->set_error('Not connected');
      foreach($this->db_queries as $db_query)
        $db_query->clean();
      $this->db_queries_next_index = 0;
      $this->db_queries = array();
      @mysql_close($this->link_id);
      $this->link_id = false;
      return true;
    }

    public function ping()
    {
      $this->error = false;
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if(@mysql_ping($this->link_id) === false)
        return $this->set_error('Lost connection');
      return true;
    }

    public function register_db_query(&$query)
    {
      $this->error = false;
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if(@get_class($query) !== 'rr_mysql_query')
        return $this->set_error('Bad argument');
      $register_id = $this->db_queries_next_index;
      $this->db_queries_next_index++;
      $this->db_queries[$register_id] = &$query;
      return $register_id;
    }

    public function unregister_db_query($register_id)
    {
      $this->error = false;
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if(array_key_exists($register_id, $this->db_queries) === false)
        return $this->set_error('Not registered');
      unset($this->db_queries[$register_id]);
      return true;
    }

    public function escape($input)
    {
      $this->error = false;
      return @mysql_real_escape_string($input, $this->link_id);
    }
  }

  class rr_mysql_query
  {
    public $error;
    private $connection;
    private $register_id;
    private $link_id;
    private $query_id;
    public $row;

    function __construct(&$connection)
    {
      $this->error =false;
      $thie->connection = false;
      $this->register_id = false;
      $this->link_id = false;
      if(@get_class($connection) === 'rr_mysql_connection')
      {
        $this->connection = &$connection;
        $this->register_id = $connection->register_db_query($this);
        $this->link_id = &$connection->link_id;
      }
      $this->query_id = false;
      $this->row = false;
    }

    function __destruct()
    {
      $this->clean();
      if($this->register_id !== false)
        $this->connection->unregister_db_query($this->register_id);
    }

    private function set_error($text)
    {
      $this->error = $text;
      return false;
    }

    public function clean()
    {
      $this->error = false;
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if($this->query_id !== false and $this->query_id !== true)
      {
        @mysql_free_result($this->query_id);
        $this->query_id = false;
      }
      return true;
    }

    public function execute($query)
    {
      $this->error = false;
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if($this->query_id !== false and $this->query_id !== true)
        @mysql_free_result($this->query_id);
      $this->query_id = @mysql_query($query, $this->link_id);
      if($this->query_id === false)
        return $this->set_error('Bad query: '.$query);
      $this->row = false;
      return true;
    }

    public function get_number_rows()
    {
      $this->error = false;
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if($this->query_id === false or $this->query_id === true)
        return $this->set_error('Not queried');
      return @mysql_num_rows($this->query_id);
    }

    public function get_number_fields()
    {
      $this->error = false;
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if($this->query_id === false or $this->query_id === true)
        return $this->set_error('Not queried');
      return @mysql_num_fields($this->query_id);
    }

    public function get_affected_rows()
    {
      $this->error = false;
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if($this->query_id !== true)
        return $this->set_error('Not queried');
      return @mysql_affected_rows($this->link_id);
    }

    public function get_insert_id()
    {
      $this->error = false;
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if($this->query_id !== true)
        return $this->set_error('Not queried');
      return @mysql_insert_id($this->link_id);
    }

    public function seek_row($position)
    {
      $this->error = false;
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if($this->query_id === false or $this->query_id === true)
        return $this->set_error('Not queried');
      @mysql_data_seek($this->query_id, $position);
    }

    public function load_next_row()
    {
      $this->error = false;
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if($this->query_id === false or $this->query_id === true)
        return $this->set_error('Not queried');
      $this->row = @mysql_fetch_array($this->query_id);
      if($this->row === false)
        return false;
      return true;
    }

    public function get_field($name)
    {
      $this->error = false;
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if($this->row === false)
        return $this->set_error('Not rowed');
      if(array_key_exists($name, $this->row) === false)
        return $this->set_error('No exists field: '.$name);
      return $this->row[$name];
    }
  }

?>
