<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  rr_start_html();
  $title = 'Requests Edit';
  include($rr_dir.'/templates/development/header.php');
  include($rr_dir.'/templates/development/message.php');
  include($rr_dir.'/templates/development/header_menu.php');

  $request_id = (int)$id;

  if($rr_mysql_query->execute('SELECT name, filename, license_id, developing FROM rr_requests WHERE id = \''.$request_id.'\'') === false)
    return $rr_mysql_query->error;
  if($rr_mysql_query->load_next_row() === false)
    return $rr_mysql_query->error;
  $name = $rr_mysql_query->get_field('name');
  $filename = $rr_mysql_query->get_field('filename');
  $license_id = $rr_mysql_query->get_field('license_id');
  $developing = $rr_mysql_query->get_field('developing') != 0 ? true : false;

?>
  <form action="<?php echo($rr_php_self); ?>" method="GET">
    <input type="hidden" name="rr_request" value="development/requests/edit/execute"/>
    <input type="hidden" name="id" value="<?php echo($request_id); ?>"/>
    <table>
      <tr>
        <td>Name:</td>
        <td><input type="text" name="name" value="<?php echo($name); ?>" id="name"/></td>
      </tr>
      <tr>
        <td>File Name:</td>
        <td>
          <input type="text" name="filename" value="<?php echo($filename); ?>" id="filename"/>
          <a href="" onclick="document.getElementById('filename').value = document.getElementById('name').value+'.php'; return false;">Copy</a>
        </td>
      </tr>
      <tr>
        <td>License:</td>
        <td>
          <select name="license_id">
            <option value="NULL"<?php if(is_null($license_id) === true) echo(' selected="selected"'); ?>>&nbsp;</option>
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
            <option value="<?php echo($id); ?>"<?php if($id === $license_id) echo(' selected="selected"'); ?>><?php echo($name); ?></option>
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
            <option value="no"<?php if($developing === false) echo(' selected="selected"'); ?>>No</option>
            <option value="yes"<?php if($developing === true) echo(' selected="selected"'); ?>>Yes</option>
          </select>
        </td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td><input type="submit" value="Edit"/></td>
      </tr>
    </table>
  </form>
  <br/>
  <table>
    <tr>
      <th>&nbsp;</th>
      <th>Name</th>
      <th>Type</th>
      <th>Default Value</th>
    </tr>
<?php

  if($rr_mysql_query->execute('SELECT id, name, type, default_value FROM rr_arguments WHERE request_id = \''.$request_id.'\' ORDER BY name') === false)
    return $rr_mysql_query->error;
  $number_rows = $rr_mysql_query->get_number_rows();
  if($number_rows === false)
    return $rr_mysql_query->error;

  if($number_rows == 0)
  {

?>
    <tr>
      <td colspan="4">No arguments</td>
    </tr>
<?php

  }
  else
    for($count = 0; $count < $number_rows; $count++)
    {
      if($rr_mysql_query->load_next_row() === false)
        return $rr_mysql_query->error;
      $id = $rr_mysql_query->get_field('id');
      $name = $rr_mysql_query->get_field('name');
      $type = $rr_mysql_query->get_field('type');
      $default_value = $rr_mysql_query->get_field('default_value');

?>
    <tr>
      <td><a href="<?php echo($rr_php_self); ?>?rr_request=development/requests/arguments/delete&id=<?php echo($id); ?>&request_id=<?php echo($request_id); ?>">Delete</a></td>
      <td><?php echo($name); ?></td>
      <td><?php echo($type); ?></td>
      <td><?php echo($default_value); ?></td>
    </tr>
<?php

    }

?>
  </table>
  <br/>
  <form action="<?php echo($rr_php_self); ?>" method="GET">
    <input type="hidden" name="rr_request" value="development/requests/arguments/add"/>
    <input type="hidden" name="request_id" value="<?php echo($request_id); ?>"/>
    <table>
      <tr>
        <td>Name:</td>
        <td><input type="text" name="name" value=""/></td>
      </tr>
      <tr>
        <td>Type:</td>
        <td>
          <select name="type">
            <option value="MANDATORY" selected="selected">Mandatory</option>
            <option value="OPTIONAL">Optional</option>
            <option value="FILE">File</option>
          </select>
        </td>
      </tr>
      <tr>
        <td>Default Value:</td>
        <td><input type="text" name="default_value" value=""/></td>
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
