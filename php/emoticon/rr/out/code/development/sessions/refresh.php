<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  $id = (int)$id;

  if($rr_mysql_query->execute('UPDATE rr_sessions SET expire_time = TIMESTAMPADD(SECOND, \''.addslashes($rr_session_expire_time_in_seconds).'\', NOW()) WHERE id = \''.$id.'\'') === false)
    return $rr_mysql_query->error;
  return rr_redirect($rr_php_self.'?rr_request=development/sessions/list&message=Refreshed');

?>
