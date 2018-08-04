<?php

  if(isset($prss_pass) === false or $prss_pass !== true)
    die();

  class prss_requests_c extends prss_root_c
  {
    private $requests;

    function __construct()
    {
      parent::__construct();
      $this->requests = array();
      return $this;
    }

    public function add(&$request)
    {
      $this->clean_error();
      if
      (
        @get_class($request) === 'prss_request_c' and
        array_key_exists($request->request_name, $this->requests) === false
      )
        $this->requests[$request->request_name] = $request;
      return $this;
    }

    public function get_info(&$authentication, $request_name, $session)
    {
      $this->clean_error();
      if(array_key_exists($request_name, $this->requests) === false)
        return $this->set_error('Bad request');
      $return_value = $this->requests[$request_name]->get_info($authentication, $session);
      if($return_value === false)
        return $this->set_error($this->requests[$request_name]->error);
      return $return_value;
    }
  }

?>
