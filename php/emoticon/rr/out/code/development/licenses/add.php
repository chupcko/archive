<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  if(preg_match('/^[a-zA-Z0-9_]+$/', $name) == 0)
    return rr_redirect($rr_php_self.'?rr_request=development/licenses/list&message=Bad%20name');
  if($default_value != 'true')
    $default_value = 'false';

  if($rr_mysql_query->execute('SELECT COUNT(*) AS count FROM rr_licenses WHERE name = \''.addslashes($name).'\'') === false)
    return $rr_mysql_query->error;
  if($rr_mysql_query->load_next_row() === false)
    return $rr_mysql_query->error;
  if($rr_mysql_query->get_field('count') != 0)
    return rr_redirect($rr_php_self.'?rr_request=development/licenses/list&message=Duplicate%20name');

  if($rr_mysql_query->execute('INSERT INTO rr_licenses (name, default_value) VALUES (\''.addslashes($name).'\', '.$default_value.')') === false)
    return $rr_mysql_query->error;
  return rr_redirect($rr_php_self.'?rr_request=development/licenses/list&message=Added');

?>
