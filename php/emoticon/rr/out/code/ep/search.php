<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  include_once($rr_dir.'/include/ep.php');

  if($query == '')
    return rr_make_xml_result_short(100, 'Not found');

  $query = $ep_mysql_connection->escape(str_replace('%', '\%', str_replace('_', '\_', $query)));
  if
  (
    $ep_mysql_query->execute
    (
      'SELECT DISTINCT '.
      '  ep_emoticon.id AS id, '.
      '  ep_emoticon.emoticon AS emoticon '.
      'FROM '.
      '  ep_emoticon, '.
      '  ep_description '.
      'WHERE '.
      '  ep_emoticon.id = ep_description.emoticon_id AND '.
      '  ( '.
      '    UPPER(ep_emoticon.emoticon) LIKE UPPER(\'%'.$query.'%\') OR '.
      '    UPPER(ep_description.description) LIKE UPPER(\'%'.$query.'%\') '.
      '  ) '.
      'ORDER BY '.
      '  emoticon '
    ) === false
  )
    return rr_make_xml_result_short(-501, $ep_mysql_query->error);
  $number_rows = $ep_mysql_query->get_number_rows();
  if($number_rows === false)
    return rr_make_xml_result_short(-501, $ep_mysql_query->error);
  if($number_rows != 0)
  {
    $xml = '  <emoticons count="'.$number_rows.'">'."\n";
    for($count = 0; $count < $number_rows; $count++)
    {
      if($ep_mysql_query->load_next_row() === false)
        return rr_make_xml_result_short(-501, $ep_mysql_query->error);
      $id = $ep_mysql_query->get_field('id');
      $emoticon = $ep_mysql_query->get_field('emoticon');
      if($id === false or $emoticon === false)
        return rr_make_xml_result_short(-500, 'System error');
      $xml .= '    <emoticon id="'.$id.'">'.htmlspecialchars($emoticon).'</emoticon>'."\n";
    }
    $xml .= '  </emoticons>'."\n";
  }
  else
    $xml = '  <emoticons count="0"/>'."\n";

  return rr_make_xml_result_long(0, 'OK', $xml);

?>
