<?php

  if(isset($prss_pass) === false or $prss_pass !== true)
    die();

  class prss_mysql_connection_c extends prss_root_c
  {
    private $database;
    private $hostname;
    private $username;
    private $password;
    public $link_id;
    private $db_queries_next_index;
    private $db_queries;

    function __construct($database = 'prss', $hostname = 'localhost', $username = 'prss', $password = 'prss')
    {
      parent::__construct();
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

    public function connect()
    {
      $this->clean_error();
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
      $this->clean_error();
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
      $this->clean_error();
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if(@mysql_ping($this->link_id) === false)
        return $this->set_error('Lost connection');
      return true;
    }

    public function register_db_query(&$query)
    {
      $this->clean_error();
      if(@get_class($query) !== 'prss_mysql_query_c')
        return $this->set_error('Bad query class');
      if($this->link_id === false)
        return $this->set_error('Not connected');
      $register_id = $this->db_queries_next_index;
      $this->db_queries_next_index++;
      $this->db_queries[$register_id] = &$query;
      return $register_id;
    }

    public function unregister_db_query($register_id)
    {
      $this->clean_error();
      if($this->link_id === false)
        return $this->set_error('Not connected');
      if(array_key_exists($register_id, $this->db_queries) === false)
        return $this->set_error('Not registered');
      unset($this->db_queries[$register_id]);
      return true;
    }

    public function escape($input)
    {
      $this->clean_error();
      return @mysql_real_escape_string($input, $this->link_id);
    }
  }

?>
