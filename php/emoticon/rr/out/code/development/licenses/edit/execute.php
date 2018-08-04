<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  $id = (int)$id;
  if(preg_match('/^[a-zA-Z0-9_]+$/', $name) == 0)
    return rr_redirect($rr_php_self.'?rr_request=development/licenses/edit/form&id='.$id.'&message=Bad%20name');
  if($default_value != 'true')
    $default_value = 'false';

  if($rr_mysql_query->execute('SELECT COUNT(*) AS count FROM rr_licenses WHERE name = \''.addslashes($name).'\' AND id <> \''.$id.'\'') === false)
    return $rr_mysql_query->error;
  if($rr_mysql_query->load_next_row() === false)
    return $rr_mysql_query->error;
  if($rr_mysql_query->get_field('count') != 0)
    return rr_redirect($rr_php_self.'?rr_request=development/licenses/edit/form&id='.$id.'&message=Duplicate%20name');

  if($rr_mysql_query->execute('UPDATE rr_licenses SET name = \''.addslashes($name).'\', default_value = '.$default_value.' WHERE id = \''.$id.'\'') === false)
    return $rr_mysql_query->error;

  return rr_redirect($rr_php_self.'?rr_request=development/licenses/list&message=Edited');

?>
