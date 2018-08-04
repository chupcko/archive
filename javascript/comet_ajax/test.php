<?
set_time_limit(0);
while(true)
{
  echo rand()."\n";
  ob_flush();
  flush();
  sleep(1);
}
?>
