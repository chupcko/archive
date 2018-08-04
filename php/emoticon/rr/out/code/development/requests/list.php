<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  rr_start_html();
  $title = 'Requests List';
  include($rr_dir.'/templates/development/header.php');
  include($rr_dir.'/templates/development/message.php');
  include($rr_dir.'/templates/development/header_menu.php');

?>
  <table>
    <tr>
      <th>&nbsp;</th>
      <th>&nbsp;</th>
      <th>Name</th>
      <th>Licence</th>
      <th>Developing</th>
      <th>&nbsp;</th>
    </tr>
<?php

  if($rr_mysql_query->execute('SELECT id, name, (SELECT name FROM rr_licenses WHERE id = rr_requests.license_id) AS license, developing FROM rr_requests ORDER BY developing, name') === false)
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
    $license = $rr_mysql_query->get_field('license');
    if(is_null($license) === true)
      $license = '&nbsp;';
    $developing = $rr_mysql_query->get_field('developing') != 0 ? 'Yes' : 'No';

?>
    <tr>
      <td><a href="<?php echo($rr_php_self); ?>?rr_request=development/requests/delete&id=<?php echo($id); ?>">Delete</a></td>
      <td><a href="<?php echo($rr_php_self); ?>?rr_request=development/requests/edit/form&id=<?php echo($id); ?>">Edit</a></td>
      <td><?php echo($name); ?></td>
      <td><?php echo($license); ?></td>
      <td><?php echo($developing); ?></td>
      <td><a href="<?php echo($rr_php_self); ?>?rr_request=development/execute/execute&id=<?php echo($id); ?>">Execute</a></td>
    </tr>
<?php

  }

?>
  </table>
  <br/>
  <form action="<?php echo($rr_php_self); ?>" method="GET">
    <input type="hidden" name="rr_request" value="development/requests/add"/>
    <table>
      <tr>
        <td>Name:</td>
        <td><input type="text" name="name" value="" id="name"/></td>
      </tr>
      <tr>
        <td>File Name:</td>
        <td>
          <input type="text" name="filename" value="" id="filename"/>
          <a href="" onclick="document.getElementById('filename').value = document.getElementById('name').value+'.php'; return false;">Copy</a>
        </td>
      </tr>
      <tr>
        <td>License:</td>
        <td>
          <select name="license_id">
            <option value="NULL">&nbsp;</option>
<?php

  if($rr_mysql_query->execute('SELECT id, name FROM rr_licenses ORDER BY name') === false)
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

?>
            <option value="<?php echo($id); ?>"><?php echo($name); ?></option>
<?php

  }

?>
          </select>
        </td>
      </tr>
      <tr>
        <td>Developing:</td>
        <td>
          <select name="developing">
            <option value="no" selected="selected">No</option>
            <option value="yes">Yes</option>
          </select>
        </td>
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
