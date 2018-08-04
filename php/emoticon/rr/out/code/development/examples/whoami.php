<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  $xml =
    '  <request>'.htmlspecialchars($rr_request).'</request>'."\n".
    '  <session>'.htmlspecialchars($rr_session).'</session>'."\n".
    '  <user_id>'.htmlspecialchars($rr_user_id).'</user_id>'."\n".
    '  <username>'.htmlspecialchars($rr_authentication->get_username($rr_user_id)).'</username>'."\n";

  return rr_make_xml_result_long(0, 'OK', $xml);

?>
