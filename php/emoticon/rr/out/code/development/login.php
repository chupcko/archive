<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  if($rr_session !== false)
  {
    $rr_user_id = $rr_authentication->get_user_id_from_session($rr_session);
    if($rr_user_id === false and $rr_authentication->error !== false)
      return $rr_authentication->error;
    if($rr_user_id !== false)
    {
      $have_permission = $rr_authentication->have_permission($rr_user_id, RR_ADMIN_LICENSE_ID);
      if($have_permission === false and $rr_authentication->error !== false)
        return $rr_authentication->error;
      if($have_permission === true)
        return rr_redirect($rr_php_self.'?rr_request=development/execute/list');
    }
  }

  $rr_user_id = $rr_authentication->get_user_id($username, $password);
  if($rr_user_id === false)
    if($rr_authentication->error === false)
      return rr_redirect($rr_php_self.'?rr_request=development/index&message=Login%20denied');
    else
      return $rr_authentication->error;

  $have_permission = $rr_authentication->have_permission($rr_user_id, RR_ADMIN_LICENSE_ID);
  if($have_permission === false)
    if($rr_authentication->error === false)
      return rr_redirect($rr_php_self.'?rr_request=development/index&message=Login%20denied');
    else
      return $rr_authentication->error;

  $rr_session = $rr_authentication->make_session($username, $password);
  if($rr_authentication->register_session($rr_user_id, $rr_session) === false)
    return $rr_authentication->error;
  $rr_authentication->register_cookie($rr_session);
  return rr_redirect($rr_php_self.'?rr_request=development/execute/list');

?>
