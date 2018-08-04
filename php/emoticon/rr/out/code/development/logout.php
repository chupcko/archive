<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  $rr_authentication->unregister_session($rr_session);
  $rr_authentication->unregister_cookie();
  return rr_redirect($rr_php_self.'?rr_request=development/index&message=Logout');

?>
