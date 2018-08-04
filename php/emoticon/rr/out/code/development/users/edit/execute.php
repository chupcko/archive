<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  $id = (int)$id;
  if(preg_match('/^[a-zA-Z0-9_.-]+$/', $username) == 0)
    return rr_redirect($rr_php_self.'?rr_request=development/users/edit/form&id='.$id.'&message=Bad%20username');

  if($rr_mysql_query->execute('SELECT COUNT(*) AS count FROM rr_users WHERE username = \''.addslashes($username).'\' AND id <> \''.$id.'\'') === false)
    return $rr_mysql_query->error;
  if($rr_mysql_query->load_next_row() === false)
    return $rr_mysql_query->error;
  if($rr_mysql_query->get_field('count') != 0)
    return rr_redirect($rr_php_self.'?rr_request=development/users/edit/form&id='.$id.'&message=Duplicate%20username');

  if($rr_mysql_query->execute('UPDATE rr_users SET username = \''.addslashes($username).'\', password = \''.addslashes($password).'\' WHERE id = \''.$id.'\'') === false)
    return $rr_mysql_query->error;

  return rr_redirect($rr_php_self.'?rr_request=development/users/list&message=Edited');

?>
