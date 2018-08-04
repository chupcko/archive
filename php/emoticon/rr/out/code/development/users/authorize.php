<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  $id = (int)$id;

  $username = $rr_authentication->get_username($id);
  if($username === false)
    return $rr_authentication->error;

  $session = $rr_authentication->make_session($username, $username);
  if($rr_authentication->register_session($id, $session) === false)
    return $rr_authentication->error;

  return rr_redirect($rr_php_self.'?rr_request=development/users/list&message=Authorized');

?>
