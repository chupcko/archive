<?php

  if(isset($prss_pass) === false or $prss_pass !== true)
    die();

  class prss_mysql_query_c extends prss_root_c
  {
    private $connection;
    private $register_id;
    private $link_id;
    private $query_id;
    public $row;

    function __construct(&$connection)
    {
      parent::__construct();
      $this->connection = false;
      $this->register_id = false;
      $this->link_id = false;
      if(@get_class($connection) === 'prss_mysql_connection_c')
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

    public function clean()
    {
      $this->clean_error();
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if
      (
        $this->query_id !== false and
        $this->query_id !== true
      )
      {
        @mysql_free_result($this->query_id);
        $this->query_id = false;
      }
      return true;
    }

    public function execute($query)
    {
      $this->clean_error();
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if
      (
        $this->query_id !== false and
        $this->query_id !== true
      )
        @mysql_free_result($this->query_id);
      $this->query_id = @mysql_query($query, $this->link_id);
      if($this->query_id === false)
        return $this->set_error('Bad query: '.$query);
      $this->row = false;
      return true;
    }

    public function get_number_rows()
    {
      $this->clean_error();
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if
      (
        $this->query_id === false or
        $this->query_id === true
      )
        return $this->set_error('Not queried');
      return @mysql_num_rows($this->query_id);
    }

    public function get_number_fields()
    {
      $this->clean_error();
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if
      (
        $this->query_id === false or
        $this->query_id === true
      )
        return $this->set_error('Not queried');
      return @mysql_num_fields($this->query_id);
    }

    public function get_affected_rows()
    {
      $this->clean_error();
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if($this->query_id !== true)
        return $this->set_error('Not queried');
      return @mysql_affected_rows($this->link_id);
    }

    public function get_insert_id()
    {
      $this->clean_error();
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if($this->query_id !== true)
        return $this->set_error('Not queried');
      return @mysql_insert_id($this->link_id);
    }

    public function seek_row($position)
    {
      $this->clean_error();
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if
      (
        $this->query_id === false or
        $this->query_id === true
      )
        return $this->set_error('Not queried');
      @mysql_data_seek($this->query_id, $position);
    }

    public function load_next_row()
    {
      $this->clean_error();
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if
      (
        $this->query_id === false or
        $this->query_id === true
      )
        return $this->set_error('Not queried');
      $this->row = @mysql_fetch_array($this->query_id);
      if($this->row === false)
        return false;
      return true;
    }

    public function get_field($name)
    {
      $this->clean_error();
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if($this->row === false)
        return $this->set_error('Not rowed');
      if(array_key_exists($name, $this->row) === false)
        return $this->set_error('No exists field: '.$name);
      return $this->row[$name];
    }

    public function escape($input)
    {
      $this->clean_error();
      return $this->connection->escape($input);
    }
  }

?>
