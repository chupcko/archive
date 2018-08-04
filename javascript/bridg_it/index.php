<?= '<?xml version="1.0" encoding="utf-8"?>'.PHP_EOL ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <title>Bridg-It</title>
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
  include 'js/game.js';
  include 'js/game_view.js';

  include 'js/main.js';
?>
      /*]]>*/
    </script>
  </head>
  <body class="body" onload="init();">
    Connect top red line with bottom red line if you play as first, or left blue line with right blue line if you play as second.
    <div style="overflow: auto;">
      <div class="left_div" id="game_view_7"></div>
      <div class="left_div" id="game_view_6"></div>
      <div class="left_div" id="game_view_5"></div>
      <div class="left_div" id="game_view_4"></div>
      <div class="left_div" id="game_view_3"></div>
      <div class="left_div" id="game_view_2"></div>
    </div><p/>
    <b>Goran "CHUPCKO" Lazic</b>
  </body>
</html>
