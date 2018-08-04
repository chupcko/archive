<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  return rr_make_xml_result_short(0, 'OK');

?>
