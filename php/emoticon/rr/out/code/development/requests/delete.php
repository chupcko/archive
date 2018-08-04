<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  $id = (int)$id;

  if($rr_mysql_query->execute('DELETE FROM rr_requests WHERE id=\''.$id.'\'') === false)
    return $rr_mysql_query->error;
  return rr_redirect($rr_php_self.'?rr_request=development/requests/list&message=Deleted');

?>
