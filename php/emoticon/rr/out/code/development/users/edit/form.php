<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  rr_start_html();
  $title = 'Users Edit';
  include($rr_dir.'/templates/development/header.php');
  include($rr_dir.'/templates/development/message.php');
  include($rr_dir.'/templates/development/header_menu.php');

  $id = (int)$id;

  if($rr_mysql_query->execute('SELECT id, username, password FROM rr_users WHERE id = \''.$id.'\'') === false)
    return $rr_mysql_query->error;
  if($rr_mysql_query->load_next_row() === false)
    return $rr_mysql_query->error;
  $id = $rr_mysql_query->get_field('id');
  $username = $rr_mysql_query->get_field('username');
  $password = $rr_mysql_query->get_field('password');

?>
  <form action="<?php echo($rr_php_self); ?>" method="GET">
    <input type="hidden" name="rr_request" value="development/users/edit/execute"/>
    <input type="hidden" name="id" value="<?php echo($id); ?>"/>
    <table>
      <tr>
        <td>Username:</td>
        <td><input type="text" name="username" value="<?php echo($username); ?>"/></td>
      </tr>
      <tr>
        <td>Password:</td>
        <td><input type="text" name="password" value="<?php echo($password); ?>"/></td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td><input type="submit" value="Edit"/></td>
      </tr>
    </table>
  </form>
<?php

  include($rr_dir.'/templates/development/footer_menu.php');
  include($rr_dir.'/templates/development/footer.php');

?>
