<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  rr_start_html();
  $title = 'Licences List';
  include($rr_dir.'/templates/development/header.php');
  include($rr_dir.'/templates/development/message.php');
  include($rr_dir.'/templates/development/header_menu.php');

?>
  <table>
    <tr>
      <th>&nbsp;</th>
      <th>&nbsp;</th>
      <th>Name</th>
      <th>Default Value</th>
    </tr>
<?php

  if($rr_mysql_query->execute('SELECT id, name, default_value FROM rr_licenses ORDER BY name') === false)
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
    $default_value = $rr_mysql_query->get_field('default_value') != 0 ? 'True' : 'False';

?>
    <tr>
      <td><a href="<?php echo($rr_php_self); ?>?rr_request=development/licenses/delete&id=<?php echo($id); ?>">Delete</a></td>
      <td><a href="<?php echo($rr_php_self); ?>?rr_request=development/licenses/edit/form&id=<?php echo($id); ?>">Edit</a></td>
      <td><?php echo($name); ?></td>
      <td><?php echo($default_value); ?></td>
    </tr>
<?php

  }

?>
  </table>
  <br/>
  <form action="<?php echo($rr_php_self); ?>" method="GET">
    <input type="hidden" name="rr_request" value="development/licenses/add"/>
    <table>
      <tr>
        <td>Name:</td>
        <td><input type="text" name="name" value=""/></td>
      </tr>
      <tr>
        <td>Default Value:</td>
        <td>
          <select name="default_value">
            <option value="false" selected="selected">False</option>
            <option value="true">True</option>
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
