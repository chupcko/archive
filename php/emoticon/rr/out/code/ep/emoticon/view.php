<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  $id = (int)$id;

  include_once($rr_dir.'/include/ep.php');

  if($ep_mysql_query->execute('SELECT emoticon FROM ep_emoticon WHERE id = \''.$id.'\'') === false)
    return rr_make_xml_result_short(-501, $ep_mysql_query->error);
  $number_rows = $ep_mysql_query->get_number_rows();
  if($number_rows === false)
    return rr_make_xml_result_short(-501, $ep_mysql_query->error);
  if($number_rows != 1)
    return rr_make_xml_result_short(100, 'Not found');
  if($ep_mysql_query->load_next_row() === false)
    return rr_make_xml_result_short(-501, $ep_mysql_query->error);
  $emoticon = $ep_mysql_query->get_field('emoticon');
  if($emoticon === false)
    return rr_make_xml_result_short(-500, 'System error');

  $xml = '  <emoticon emoticon="'.htmlspecialchars($emoticon).'">'."\n";

  if($ep_mysql_query->execute('SELECT description FROM ep_description WHERE emoticon_id = \''.$id.'\' ORDER BY description') === false)
    return rr_make_xml_result_short(-501, $ep_mysql_query->error);
  $number_rows = $ep_mysql_query->get_number_rows();
  if($number_rows === false)
    return rr_make_xml_result_short(-501, $ep_mysql_query->error);
  if($number_rows == 0)
    $xml .= '    <descriptions count="0"/>'."\n";
  else
  {
    $xml .= '    <descriptions count="'.$number_rows.'">'."\n";
    for($count = 0; $count < $number_rows; $count++)
    {
      if($ep_mysql_query->load_next_row() === false)
        return rr_make_xml_result_short(-501, $ep_mysql_query->error);
      $description = $ep_mysql_query->get_field('description');
      if($description === false)
        return rr_make_xml_result_short(-500, 'System error');
      $xml .= '      <description order="'.$count.'">'.htmlspecialchars($description).'</description>'."\n";
    }
    $xml .= '    </descriptions>'."\n";
  }

  $xml .= '  </emoticon>'."\n";

  return rr_make_xml_result_long(0, 'OK', $xml);

?>
