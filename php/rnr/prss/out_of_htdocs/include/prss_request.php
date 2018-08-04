<?php

  if(isset($prss_pass) === false or $prss_pass !== true)
    die();

  class prss_request_c extends prss_root_c
  {
    public $request_name;
    private $file_name;
    private $class_name;
    private $license;
    private $mandatory_arguments;
    private $optional_arguments;
    private $file_arguments;

    function __construct($request_name, $file_name, $class_name)
    {
      parent::__construct();
      $this->request_name = $request_name;
      $this->file_name = $file_name;
      $this->class_name = $class_name;
      $this->license = false;
      $this->mandatory_arguments = array();
      $this->optional_arguments = array();
      $this->file_arguments = array();
      return $this;
    }

    public function all()
    {
      $this->clean_error();
      $this->license = false;
      return $this;
    }

    public function logged()
    {
      $this->clean_error();
      $this->license = true;
      return $this;
    }

    public function license($license)
    {
      $this->clean_error();
      $this->license = $license;
      return $this;
    }

    public function mandatory_argument($name)
    {
      $this->clean_error();
      $this->mandatory_arguments[$name] = false;
      return $this;
    }

    public function optional_argument($name, $default_value)
    {
      $this->clean_error();
      $this->optional_arguments[$name] = $default_value;
      return $this;
    }

    public function file_argument($name)
    {
      $this->clean_error();
      $this->file_arguments[$name] = false;
      return $this;
    }

    public function get_info(&$authentication, $session)
    {
      $this->clean_error();
      if(@get_class($authentication) !== 'prss_authentication_c')
        return $this->set_error('Bad authentication class');
      $return_value = array
      (
        'file_name'  => $this->file_name,
        'class_name' => $this->class_name,
        'username'   => false,
        'user_id'    => false,
        'arguments'  => array()
      );
      if($authentication->clean_sessions() === false)
        return $this->set_error($authentication->error);
      if($this->license === false)
      {
        if($session !== false)
        {
          $authentication_data = $authentication->get_session_data($session);
          if($authentication_data !== false)
          {
            $return_value['username'] = $authentication_data['username'];
            $return_value['user_id'] = $authentication_data['user_id'];
          }
        }
      }
      else if($this->license === true)
      {
        $authentication_data = $authentication->get_session_data($session);
        if($authentication_data === false)
          return $this->set_error($authentication->error);
        $return_value['username'] = $authentication_data['username'];
        $return_value['user_id'] = $authentication_data['user_id'];
      }
      else
      {
        $authentication_data = $authentication->get_data($session, $this->license);
        if($authentication_data === false)
          return $this->set_error($authentication->error);
        $return_value['username'] = $authentication_data['username'];
        $return_value['user_id'] = $authentication_data['user_id'];
      }

      foreach($this->mandatory_arguments as $name => $value)
        if(prss_register_c::register_variable($return_value['arguments'][$name], $name) === false)
          return $this->set_error('Missing argument '.$name);
      foreach($this->optional_arguments as $name => $value)
        prss_register_c::register_variable($return_value['arguments'][$name], $name, $value);
      foreach($this->file_arguments as $name => $value)
      {
        if(prss_register_c::register_file($return_value['arguments'][$name], $name) === false)
          return $this->set_error('Missing file '.$name);
        if($return_value['arguments'][$name]['error'] != UPLOAD_ERR_OK)
          return $this->set_error('Upload error');
      }

      return $return_value;
    }
  }

?>
