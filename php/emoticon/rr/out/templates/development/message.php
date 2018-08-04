<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

  if($message != '')
  {

?>
    <div class="message"><?php echo($message); ?></div>
    <hr/>
<?php

  }

?>
