<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  rr_start_html();
  $title = 'Licences Edit';
  include($rr_dir.'/templates/development/header.php');
  include($rr_dir.'/templates/development/message.php');
  include($rr_dir.'/templates/development/header_menu.php');

  $id = (int)$id;

  if($rr_mysql_query->execute('SELECT id, name, default_value FROM rr_licenses WHERE id = \''.$id.'\'') === false)
    return $rr_mysql_query->error;
  if($rr_mysql_query->load_next_row() === false)
    return $rr_mysql_query->error;
  $id = $rr_mysql_query->get_field('id');
  $name = $rr_mysql_query->get_field('name');
  $default_value = $rr_mysql_query->get_field('default_value') != 0 ? true : false;

?>
  <form action="<?php echo($rr_php_self); ?>" method="GET">
    <input type="hidden" name="rr_request" value="development/licenses/edit/execute"/>
    <input type="hidden" name="id" value="<?php echo($id); ?>"/>
    <table>
      <tr>
        <td>Name:</td>
        <td><input type="text" name="name" value="<?php echo($name); ?>"/></td>
      </tr>
      <tr>
        <td>Default Value:</td>
        <td>
          <select name="default_value">
            <option value="false"<?php if($default_value === false) echo(' selected="selected"'); ?>>False</option>
            <option value="true"<?php if($default_value === true) echo(' selected="selected"'); ?>>True</option>
          </select>
        </td>
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
