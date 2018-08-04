<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  $xml =
    '  <f>'."\n".
    '    <name>'.htmlspecialchars($f['name']).'</name>'."\n".
    '    <type>'.htmlspecialchars($f['type']).'</type>'."\n".
    '    <size>'.htmlspecialchars($f['size']).'</size>'."\n".
    '    <tmp_name>'.htmlspecialchars($f['tmp_name']).'</tmp_name>'."\n".
    '    <error>'.htmlspecialchars($f['error']).'</error>'."\n".
    '    <md5>'.md5(file_get_contents($f['tmp_name'])).'</md5>'."\n".
    '  </f>'."\n";

  return rr_make_xml_result_long(0, 'OK', $xml);

?>
