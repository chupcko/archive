<?
  header("Cache-Control: no-cache, must-revalidate");
  header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");
  #
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <title>Comet php backend</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  </head>
  <body>

<?
  #
  while(true)
  {
    #
?>
    <script type="text/javascript">window.parent.ttt(<?= time() ?>);</script>
<?
    #
    flush();
    sleep(1);
  }
  #
?>
</body>
</html>
