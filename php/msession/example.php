<?
  include('msession.php');

  session_register('count');
  $count++;
?>

Count is <? echo $count; ?>
