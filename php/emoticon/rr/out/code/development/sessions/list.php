<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  rr_start_html();
  $title = 'Sessions List';
  include($rr_dir.'/templates/development/header.php');
  include($rr_dir.'/templates/development/message.php');
  include($rr_dir.'/templates/development/header_menu.php');

?>
  <table>
    <tr>
      <th>&nbsp;</th>
      <th>Username</th>
      <th>Value</th>
      <th>Expire time</th>
      <th>Remote address</th>
      <th>&nbsp;</th>
    </tr>
<?php

  if($rr_mysql_query->execute('SELECT rr_sessions.id AS id, rr_users.username AS username, rr_sessions.value AS value, rr_sessions.expire_time AS expire_time, rr_sessions.remote_address AS remote_address FROM rr_sessions, rr_users WHERE rr_sessions.user_id = rr_users.id ORDER BY username, expire_time, value') === false)
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
    $value = $rr_mysql_query->get_field('value');
    $expire_time = $rr_mysql_query->get_field('expire_time');
    $remote_address = $rr_mysql_query->get_field('remote_address');

?>
    <tr>
      <td><a href="<?php echo($rr_php_self); ?>?rr_request=development/sessions/delete&id=<?php echo($id); ?>">Delete</a></td>
      <td><?php echo($username); ?></td>
      <td><?php echo($value); ?></td>
      <td><?php echo($expire_time); ?></td>
      <td><?php echo($remote_address); ?></td>
      <td><a href="<?php echo($rr_php_self); ?>?rr_request=development/sessions/refresh&id=<?php echo($id); ?>">Refresh</a></td>
    </tr>
<?php

  }

?>
  </table>
<?php

  include($rr_dir.'/templates/development/footer_menu.php');
  include($rr_dir.'/templates/development/footer.php');

?>
