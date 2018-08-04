<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  rr_start_html();
  $title = 'Users Search';
  include($rr_dir.'/templates/development/header.php');
  include($rr_dir.'/templates/development/message.php');
  include($rr_dir.'/templates/development/header_menu.php');

?>
  <table>
    <tr>
      <th>&nbsp;</th>
      <th>&nbsp;</th>
      <th>Username</th>
      <th>Password</th>
      <th>&nbsp;</th>
      <th>&nbsp;</th>
    </tr>
<?php

  if($rr_mysql_query->execute('SELECT id, username, password FROM rr_users ORDER BY username') === false)
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

?>
    <tr>
      <td><a href="<?php echo($rr_php_self); ?>?rr_request=development/users/delete&id=<?php echo($id); ?>">Delete</a></td>
      <td><a href="<?php echo($rr_php_self); ?>?rr_request=development/users/edit/form&id=<?php echo($id); ?>">Edit</a></td>
      <td><?php echo($username); ?></td>
      <td><?php echo($password); ?></td>
      <td><a href="<?php echo($rr_php_self); ?>?rr_request=development/users/authorize&id=<?php echo($id); ?>">Authorize</a></td>
      <td><a href="<?php echo($rr_php_self); ?>?rr_request=development/users/permissions/list&id=<?php echo($id); ?>">Permissions</a></td>
    </tr>
<?php

  }

?>
  </table>
  <br/>
  <form action="<?php echo($rr_php_self); ?>" method="GET">
    <input type="hidden" name="rr_request" value="development/users/add"/>
    <table>
      <tr>
        <td>Username:</td>
        <td><input type="text" name="username" value=""/></td>
      </tr>
      <tr>
        <td>Password:</td>
        <td><input type="text" name="password" value=""/></td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td><input type="submit" value="Add"/></td>
      </tr>
    </table>
  </form>
<?php

  include($rr_dir.'/templates/development/footer_menu.php');
  include($rr_dir.'/templates/development/footer.php');

?>
