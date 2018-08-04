<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  if($rr_session !== false)
  {
    $rr_user_id = $rr_authentication->get_user_id_from_session($rr_session);
    if($rr_user_id === false and $rr_authentication->error !== false)
      return $rr_authentication->error;
    if($rr_user_id !== false)
    {
      $have_permission = $rr_authentication->have_permission($rr_user_id, RR_ADMIN_LICENSE_ID);
      if($have_permission === false and $rr_authentication->error !== false)
        return $rr_authentication->error;
      if($have_permission === true)
      {
        if($rr_authentication->refresh_session($rr_session) === false)
          return $rr_authentication->error;
        return rr_redirect($rr_php_self.'?rr_request=development/execute/list');
      }
    }
  }

  rr_start_html();
  $title = 'Login';
  include($rr_dir.'/templates/development/header.php');
  include($rr_dir.'/templates/development/message.php');

?>

  <form action="<?php echo($rr_php_self); ?>" method="GET">
    <input type="hidden" name="rr_request" value="development/login"/>
    <table>
      <tr>
        <td>Username:</td>
        <td><input type="text" name="username" value=""/></td>
      </tr>
      <tr>
        <td>Password:</td>
        <td><input type="password" name="password" value=""/></td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td><input type="submit" value="Login"/></td>
      </tr>
    </table>
  </form>
<?php

  include($rr_dir.'/templates/development/footer.php');

?>
