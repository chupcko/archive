<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  $user_id = (int)$user_id;
  $license_id = (int)$license_id;
  if($value != 'true')
    $value = 'false';

  if($rr_mysql_query->execute('INSERT INTO rr_permissions (user_id, license_id, value) VALUES (\''.$user_id.'\', \''.$license_id.'\', '.$value.')') === false)
    return $rr_mysql_query->error;

  return rr_redirect($rr_php_self.'?rr_request=development/users/permissions/list&id='.$user_id.'&message=Added');

?>
