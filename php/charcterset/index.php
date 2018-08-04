<?
  $charsets[] = 'iso-8859-1';
  $charsets[] = 'iso-8859-2';
  $charsets[] = 'iso-8859-3';
  $charsets[] = 'iso-8859-4';
  $charsets[] = 'iso-8859-5';
  $charsets[] = 'iso-8859-6';
  $charsets[] = 'iso-8859-7';
  $charsets[] = 'iso-8859-8';
  $charsets[] = 'iso-8859-9';
  $charsets[] = 'windows-1250';
  $charsets[] = 'windows-1251';
  $charsets[] = 'windows-1252';
  $charsets[] = 'windows-1253';
  $charsets[] = 'UTF-8';
  #
?>
<html>
  <head>
<?
  #
  $charset = $_GET["charset"];
  if(isset($charset))
  {
    #
?>
    <meta http-equiv="Content-Type" content="text/html; charset=<?= $charset ?>">
    <title>Charcter Set <?= $charset ?></title>
<?
    #
  }
  else
  {
    #
?>
    <title>Charcter Set</title>
<?
    #
  }
  #
?>
  </head>
  <body>
<?
  #
  foreach($charsets as $c)
  {
    #
?>
    <a href="<?= $PHP_SELF ?>?charset=<?= $c ?>"><?= $c ?></a><br>
<?
    #
  }
  if(isset($charset))
  {
    #
?>
    <p>
    <table cols="16" border="1" width="100%">
<?
    #
    for($x = 0; $x < 16; $x++)
    {
      #
?>
      <tr align="center">
<?
      #
      for($y = 0; $y < 16; $y++)
      {
        $c = $x*16+$y;
        #
?>
        <td>
          <font color="red"><?= sprintf('%03d', $c); ?></font><br>
          <font color="green"><?= sprintf('%02X', $c); ?></font><br>
          <?= chr($c) ?><br>
          &#<?= $c ?>;<br>
        </td>
<?
        #
      }
      #
?>
      </tr>
<?
      #
    }
    #
?>
    </table>
<?
    #
  }
  #
?>
  </body>
</html>
<?
  #
?>
