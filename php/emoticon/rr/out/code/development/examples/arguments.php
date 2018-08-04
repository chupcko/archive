<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  $xml =
    '  <m>'.htmlspecialchars($m).'</m>'."\n".
    '  <o>'.htmlspecialchars($o).'</o>'."\n";

  return rr_make_xml_result_long(0, 'OK', $xml);

?>
