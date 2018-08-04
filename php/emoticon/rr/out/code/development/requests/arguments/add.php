<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  $request_id = (int)$request_id;
  if(preg_match('/^[a-zA-Z0-9_]+$/', $name) == 0)
    return rr_redirect($rr_php_self.'?rr_request=development/requests/edit/form&id='.$request_id.'&message=Bad%20name');
  if($type != 'MANDATORY' and $type != 'OPTIONAL' and $type != 'FILE')
    $type = 'MANDATORY';
  if($type != 'OPTIONAL')
    $default_value = '';

  if($rr_mysql_query->execute('SELECT COUNT(*) AS count FROM rr_arguments WHERE name = \''.addslashes($name).'\' and request_id = \''.$request_id.'\'') === false)
    return $rr_mysql_query->error;
  if($rr_mysql_query->load_next_row() === false)
    return $rr_mysql_query->error;
  if($rr_mysql_query->get_field('count') != 0)
    return rr_redirect($rr_php_self.'?rr_request=development/requests/edit/form&id='.$request_id.'&message=Duplicate%20name');

  if($rr_mysql_query->execute('INSERT INTO rr_arguments (name, request_id, type, default_value) VALUES (\''.addslashes($name).'\', \''.$request_id.'\', \''.$type.'\', \''.addslashes($default_value).'\')') === false)
    return $rr_mysql_query->error;
  return rr_redirect($rr_php_self.'?rr_request=development/requests/edit/form&id='.$request_id.'&message=Added');

?>
