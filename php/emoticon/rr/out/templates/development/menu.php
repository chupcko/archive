<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

?>
    RR-<?php echo($rr_version); ?>:
    <a href="<?php echo($rr_php_self); ?>?rr_request=development/execute/list">Execute</a>
    &nbsp;
    <a href="<?php echo($rr_php_self); ?>?rr_request=development/users/list">Users</a>
    <a href="<?php echo($rr_php_self); ?>?rr_request=development/sessions/list">Sessions</a>
    <a href="<?php echo($rr_php_self); ?>?rr_request=development/licenses/list">Licences</a>
    <a href="<?php echo($rr_php_self); ?>?rr_request=development/requests/list">Requests</a>
    &nbsp;
    <a href="<?php echo($rr_php_self); ?>?rr_request=development/export">Export</a>
    &nbsp;
    <a href="<?php echo($rr_php_self); ?>?rr_request=development/logout">Logout</a>
