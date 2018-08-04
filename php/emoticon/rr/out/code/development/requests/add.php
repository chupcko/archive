<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  if(preg_match('/^[a-zA-Z0-9_.\\/-]+$/', $name) == 0)
    return rr_redirect($rr_php_self.'?rr_request=development/requests/list&message=Bad%20name');
  if(preg_match('/^[a-zA-Z0-9_.\\/-]+$/', $filename) == 0)
    return rr_redirect($rr_php_self.'?rr_request=development/requests/list&message=Bad%20filename');
  if($license_id != 'NULL')
    $license_id = (int)$license_id;
  if($developing == 'yes')
    $developing = 'true';
  else
    $developing = 'false';

  if($rr_mysql_query->execute('SELECT COUNT(*) AS count FROM rr_requests WHERE name = \''.addslashes($name).'\'') === false)
    return $rr_mysql_query->error;
  if($rr_mysql_query->load_next_row() === false)
    return $rr_mysql_query->error;
  if($rr_mysql_query->get_field('count') != 0)
    return rr_redirect($rr_php_self.'?rr_request=development/requests/list&message=Duplicate%20name');

  if($rr_mysql_query->execute('SELECT COUNT(*) AS count FROM rr_requests WHERE filename = \''.addslashes($filename).'\'') === false)
    return $rr_mysql_query->error;
  if($rr_mysql_query->load_next_row() === false)
    return $rr_mysql_query->error;
  if($rr_mysql_query->get_field('count') != 0)
    return rr_redirect($rr_php_self.'?rr_request=development/requests/list&message=Duplicate%20filename');

  if($rr_mysql_query->execute('INSERT INTO rr_requests (name, filename, license_id, developing) VALUES (\''.addslashes($name).'\', \''.addslashes($filename).'\', '.$license_id.', '.$developing.')') === false)
    return $rr_mysql_query->error;
  return rr_redirect($rr_php_self.'?rr_request=development/requests/list&message=Added');

?>
