<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  function f1($pass)
  {
    return md5($pass);
  }

  $data_mysql = new rr_data_mysql($rr_mysql_connection);
  $fields_description = array
  (
    array('expression' => 'id',              'name' => 'id' ),
    array('expression' => 'UPPER(username)', 'name' => 'name' ),
    array('expression' => 'password',        'name' => 'pass' )
  );
  $data_description = array
  (
    array('name' => 'id',       'type' => 'copy',      'from' => 'id'),
    array('name' => 'username', 'type' => 'copy',      'from' => 'name'),
    array('name' => 'password', 'type' => 'calculate', 'call' => 'f1', 'arguments' => array('pass'))
  );
  if($data_mysql->make_xml($fields_description, 'SELECT '.RR_DATA_MYSQL_FIELDS.' FROM rr_users', $data_description, $xml) === false)
    return rr_make_xml_result_short(500, $data_mysql->error);

  return rr_make_xml_result_long(0, 'OK', $xml);

?>
