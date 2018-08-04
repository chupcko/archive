<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  $ep_mysql_database = 'ep';
  $ep_mysql_hostname = 'localhost';
  $ep_mysql_username = 'ep';
  $ep_mysql_password = 'ep';

  $ep_mysql_connection = new rr_mysql_connection($ep_mysql_database, $ep_mysql_hostname, $ep_mysql_username, $ep_mysql_password);
  if($ep_mysql_connection->connect() === false)
    rr_die_500($ep_mysql_connection->error);
  $ep_mysql_query = new rr_mysql_query($ep_mysql_connection);

?>
