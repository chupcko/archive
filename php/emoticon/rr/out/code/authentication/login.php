<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  $rr_user_id = $rr_authentication->get_user_id($username, $password);
  if($rr_user_id === false)
    if($rr_authentication->error === false)
      return rr_make_xml_result_short(403, 'Forbidden');
    else
      return rr_make_xml_result_short(500, $rr_authentication->error);
  $rr_session = $rr_authentication->make_session($username, $password);
  if($rr_authentication->register_session($rr_user_id, $rr_session) === false)
    return rr_make_xml_result_short(500, $rr_authentication->error);
  $rr_authentication->register_cookie($rr_session);
  return rr_make_xml_result_short(0, 'OK');

?>
