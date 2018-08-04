<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  $id = (int)$id;

  rr_start_html();
  $title = 'Requests Execute WEB';
  include($rr_dir.'/templates/development/header.php');
  include($rr_dir.'/templates/development/header_menu.php');

  if($rr_mysql_query->execute('SELECT name FROM rr_requests WHERE id = \''.$id.'\'') === false)
    return $rr_mysql_query->error;
  if($rr_mysql_query->load_next_row() === false)
    return $rr_mysql_query->error;
  $request_name = $rr_mysql_query->get_field('name');

  if($rr_mysql_query->execute('SELECT COUNT(*) AS count FROM rr_arguments WHERE request_id = \''.$id.'\' AND type = \'FILE\'') === false)
    return $rr_mysql_query->error;
  if($rr_mysql_query->load_next_row() === false)
    return $rr_mysql_query->error;
  $count = $rr_mysql_query->get_field('count');
  if($count != 0)
    $method = 'POST';
  else
    $method = 'GET';

?>
    <form action="<?php echo($rr_php_self); ?>" method="<?php echo($method); ?>" enctype="multipart/form-data">
      <input type="hidden" name="rr_request" value="<?php echo($request_name); ?>"/>
      <table>
        <tr>
          <th>Type</th>
          <th>Send</th>
          <th>Argument</th>
          <th>Value</th>
        </tr>
        <tr>
          <td>&nbsp;</td>
          <td>&nbsp;</td>
          <td>Select Session</td>
          <td>
            <select id="rr_session_select" onchange="select('rr_session_select', 'rr_session');">
<?php

  if($rr_mysql_query->execute('SELECT rr_users.username AS username, rr_sessions.value AS value FROM rr_sessions, rr_users WHERE rr_sessions.user_id = rr_users.id AND rr_sessions.expire_time >= NOW() ORDER BY username, value') === false)
    return $rr_mysql_query->error;
  $number_rows = $rr_mysql_query->get_number_rows();
  if($number_rows === false)
    return $rr_mysql_query->error;
  for($count = 0; $count < $number_rows; $count++)
  {
    if($rr_mysql_query->load_next_row() === false)
      return $rr_mysql_query->error;
    $username = $rr_mysql_query->get_field('username');
    $value = $rr_mysql_query->get_field('value');
    $selected = '';
    if($value == $rr_session)
      $selected = ' selected="selected"';

?>
              <option value="<?php echo($value); ?>"<?php echo($selected); ?>><?php echo($value); ?> - <?php echo($username); ?></option>
<?php

  }

?>
            </select>
          </td>
        </tr>
        <tr>
          <td>&nbsp;</td>
          <td><input type="checkbox" checked="checked" onchange="toggle('rr_session'); toggle('rr_session_select');"/></td>
          <td>Session</td>
          <td><input type="text" name="rr_session" value="<?php echo($rr_session); ?>" id="rr_session"/></td>
        </tr>
<?php

  if($rr_mysql_query->execute('SELECT id, name, type, default_value FROM rr_arguments WHERE request_id = \''.$id.'\' ORDER BY id') === false)
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
    $type = $rr_mysql_query->get_field('type');
    $default_value = $rr_mysql_query->get_field('default_value');
    switch($type)
    {
      case 'MANDATORY':

?>
        <tr>
          <td>Mandatory</td>
          <td><input type="checkbox" checked="checked" onchange="toggle('<?php echo($name); ?>');"/></td>
          <td><?php echo($name); ?></td>
          <td><input type="text" name="<?php echo($name); ?>" value="<?php echo($default_value); ?>" id="<?php echo($name); ?>"/></td>
        </tr>
<?php

        break;
      case 'OPTIONAL':

?>
        <tr>
          <td>Optional</td>
          <td><input type="checkbox" onchange="toggle('<?php echo($name); ?>');"/></td>
          <td><?php echo($name); ?></td>
          <td><input type="text" name="<?php echo($name); ?>" value="<?php echo($default_value); ?>" id="<?php echo($name); ?>" disabled="disabled"/></td>
        </tr>
<?php

        break;
      case 'FILE':

?>
        <tr>
          <td>File</td>
          <td><input type="checkbox" checked="checked" onchange="toggle('<?php echo($name); ?>');"/></td>
          <td><?php echo($name); ?></td>
          <td><input type="file" name="<?php echo($name); ?>" id="<?php echo($name); ?>"/></td>
        </tr>
<?php

        break;
    }
  }

?>
      </table>
      <input type="submit" value="Execute"/>
    </form>
<?php

  include($rr_dir.'/templates/development/footer_menu.php');
  include($rr_dir.'/templates/development/footer.php');

?>
