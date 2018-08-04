<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  ignore_user_abort(false);
  rr_start_download('rr-'.$rr_version.'_export-'.date('Y-m-d').'.mysql');

  $mysql_query = new rr_mysql_query($rr_mysql_connection);

  if($rr_mysql_query->execute('SELECT id, username, password FROM rr_users ORDER BY id') === false)
    return $rr_mysql_query->error;
  $number_rows = $rr_mysql_query->get_number_rows();
  if($number_rows === false)
    return $rr_mysql_query->error;
  for($count = 0; $count < $number_rows; $count++)
  {
    if($rr_mysql_query->load_next_row() === false)
      return $rr_mysql_query->error;
    $id = $rr_mysql_query->get_field('id');
    $username = $rr_mysql_query->get_field('username');
    $password = $rr_mysql_query->get_field('password');
    echo('INSERT INTO rr_users VALUES ('.$id.', \''.$username.'\', \''.$password.'\');'."\n");
  }

  if($rr_mysql_query->execute('SELECT id, name, default_value FROM rr_licenses ORDER BY id') === false)
    return $rr_mysql_query->error;
  $number_rows = $rr_mysql_query->get_number_rows();
  if($number_rows === false)
    return $rr_mysql_query->error;
  for($count = 0; $count < $number_rows; $count++)
  {
    if($rr_mysql_query->load_next_row() === false)
      return $rr_mysql_query->error;
    $id = $rr_mysql_query->get_field('id');
    $name = $rr_mysql_query->get_field('name');
    $default_value = $rr_mysql_query->get_field('default_value');
    echo('INSERT INTO rr_licenses VALUES ('.$id.', \''.$name.'\', '.$default_value.');'."\n");
  }

  if($rr_mysql_query->execute('SELECT id, user_id, license_id, value FROM rr_permissions ORDER BY id') === false)
    return $rr_mysql_query->error;
  $number_rows = $rr_mysql_query->get_number_rows();
  if($number_rows === false)
    return $rr_mysql_query->error;
  for($count = 0; $count < $number_rows; $count++)
  {
    if($rr_mysql_query->load_next_row() === false)
      return $rr_mysql_query->error;
    $id = $rr_mysql_query->get_field('id');
    $user_id = $rr_mysql_query->get_field('user_id');
    $license_id = $rr_mysql_query->get_field('license_id');
    $value = $rr_mysql_query->get_field('value');
    echo('INSERT INTO rr_permissions VALUES ('.$id.', '.$user_id.', '.$license_id.', '.$value.');'."\n");
  }

  if($rr_mysql_query->execute('SELECT id, name, filename, license_id, developing FROM rr_requests ORDER BY id') === false)
    return $rr_mysql_query->error;
  $number_rows = $rr_mysql_query->get_number_rows();
  if($number_rows === false)
    return $rr_mysql_query->error;
  for($count = 0; $count < $number_rows; $count++)
  {
    if($rr_mysql_query->load_next_row() === false)
      return $rr_mysql_query->error;
    $requests_id = $rr_mysql_query->get_field('id');
    $name = $rr_mysql_query->get_field('name');
    $filename = $rr_mysql_query->get_field('filename');
    $license_id = $rr_mysql_query->get_field('license_id');
    if(is_null($license_id) === true)
      $license_id = 'NULL';
    $developing = $rr_mysql_query->get_field('developing');
    echo('INSERT INTO rr_requests VALUES ('.$requests_id.', \''.$name.'\', \''.$filename.'\', '.$license_id.', '.$developing.');'."\n");

    if($mysql_query->execute('SELECT id, name, type, default_value FROM rr_arguments WHERE request_id = '.$requests_id.' ORDER BY id') === false)
      return $mysql_query->error;
    $number_rows_arguments = $mysql_query->get_number_rows();
    if($number_rows_arguments === false)
      return $mysql_query->error;
    for($count_arguments = 0; $count_arguments < $number_rows_arguments; $count_arguments++)
    {
      if($mysql_query->load_next_row() === false)
        return $mysql_query->error;
      $id = $mysql_query->get_field('id');
      $name = $mysql_query->get_field('name');
      $type = $mysql_query->get_field('type');
      $default_value = $mysql_query->get_field('default_value');
      echo('INSERT INTO rr_arguments VALUES ('.$id.', '.$requests_id.', \''.$name.'\', \''.$type.'\', \''.$default_value.'\');'."\n");
    }
  }

  rr_set_length(ob_get_length());

?>
