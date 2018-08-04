<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  rr_start_html();
  $title = 'Requests Test';
  include($rr_dir.'/templates/development/header.php');
  include($rr_dir.'/templates/development/header_menu.php');

?>
  <table>
    <tr>
      <th>Name</th>
      <th>Licence</th>
      <th>Developing</th>
      <th>&nbsp;</th>
    </tr>
<?php

  if($rr_mysql_query->execute('SELECT id, name, (SELECT name FROM rr_licenses WHERE id = rr_requests.license_id) AS license, developing FROM rr_requests ORDER BY developing, name') === false)
    return $rr_mysql_query->error;
  $number_rorr = $rr_mysql_query->get_number_rows();
  if($number_rorr === false)
    return $rr_mysql_query->error;
  for($count = 0; $count < $number_rorr; $count++)
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
      <td><?php echo($name); ?></td>
      <td><?php echo($license); ?></td>
      <td><?php echo($developing); ?></td>
      <td><a href="<?php echo($rr_php_self); ?>?rr_request=development/execute/execute&id=<?php echo($id); ?>">Execute</a></td>
    </tr>
<?php

  }

?>
  </table>
<?php

  include($rr_dir.'/templates/development/footer_menu.php');
  include($rr_dir.'/templates/development/footer.php');

?>
