<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  rr_start_html();
  $title = 'Users Permissions';
  include($rr_dir.'/templates/development/header.php');
  include($rr_dir.'/templates/development/message.php');
  include($rr_dir.'/templates/development/header_menu.php');

?>
  <table>
    <tr>
      <th>License</th>
      <th>Default</th>
      <th>Permissions</th>
      <th>Finaly Premissions</th>
      <th>&nbsp;</th>
    </tr>
<?php

  $id = (int)$id;
  if
  (
    $rr_mysql_query->execute
    (
      'SELECT '.
      '  id AS license_id, '.
      '  name, '.
      '  default_value, '.
      '  (SELECT value FROM rr_permissions WHERE user_id = \''.$id.'\' AND license_id = rr_licenses.id) AS permissions_value,'.
      '  (SELECT id FROM rr_permissions WHERE user_id = \''.$id.'\' AND license_id = rr_licenses.id) AS permissions_id '.
      'FROM rr_licenses'
    ) === false
  )
    return $rr_mysql_query->error;
  $number_rows = $rr_mysql_query->get_number_rows();
  if($number_rows === false)
    return $rr_mysql_query->error;

  for($count = 0; $count < $number_rows; $count++)
  {
    if($rr_mysql_query->load_next_row() === false)
      return $rr_mysql_query->error;
    $license_id = $rr_mysql_query->get_field('license_id');
    $name = $rr_mysql_query->get_field('name');
    $default_value = $rr_mysql_query->get_field('default_value');
    $permissions_value = $rr_mysql_query->get_field('permissions_value');
    $permissions_id = $rr_mysql_query->get_field('permissions_id');

    if($default_value != 0)
    {
      $default_value = 'True';
      $not_default_value = 'false';
    }
    else
    {
      $default_value = 'False';
      $not_default_value = 'true';
    }

    if(is_null($permissions_value) === true || is_null($permissions_id) === true)
    {
      $permissions_value = '&nbsp;';
      $finaly_premissions = $default_value;
      $action_url = $rr_php_self.'?rr_request=development/users/permissions/add&user_id='.$id.'&license_id='.$license_id.'&value='.$not_default_value;
      $action_name = 'Add';
    }
    else
    {
      if($permissions_value != 0)
        $permissions_value = 'True';
      else
        $permissions_value = 'False';
      $finaly_premissions = $permissions_value;
      $action_url = $rr_php_self.'?rr_request=development/users/permissions/delete&id='.$permissions_id.'&user_id='.$id;
      $action_name = 'Delete';
    }

?>
    <tr>
      <td><?php echo($name); ?></td>
      <td><?php echo($default_value); ?></td>
      <td><?php echo($permissions_value); ?></td>
      <td><?php echo($finaly_premissions); ?></td>
      <td><a href="<?php echo($action_url); ?>"><?php echo($action_name); ?></a></td>
    </tr>
<?php

  }

?>
  </table>
<?php

  include($rr_dir.'/templates/development/footer_menu.php');
  include($rr_dir.'/templates/development/footer.php');

?>
