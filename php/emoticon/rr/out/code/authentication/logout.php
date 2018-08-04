<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  $rr_authentication->unregister_session($rr_session);
  $rr_authentication->unregister_cookie();
  return rr_make_xml_result_short(0, 'OK');

?>
