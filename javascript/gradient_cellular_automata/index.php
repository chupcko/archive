<?= '<?xml version="1.0" encoding="utf-8"?>'.PHP_EOL ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <title>Gradient Cellular Automata</title>
    <meta http-equiv="Content-Type" content="text/html;charset=utf-8"/>
    <style type="text/css">
      /*<![CDATA[*/
<?php
  include 'index.css';
?>
      /*]]>*/
    </style>
    <script type="text/javascript">
      /*<![CDATA[*/
<?php
  include 'js/gca.js';
  include 'js/gca_control.js';

  include 'js/main.js';
?>
      /*]]>*/
    </script>
  </head>
  <body onload="main();" class="main">
    <div>
      <canvas id="gca" class="left"></canvas>
      <div id="gca_control" class="left padding"></div>
    </div>
    <div class="clear"></div>
    <p/>
    <b>Goran "CHUPCKO" Lazic</b>
  </body>
</html>
