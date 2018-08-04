<?= '<?xml version="1.0" encoding="utf-8"?>'.PHP_EOL ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <title>Minesweeper</title>
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
  include 'js/box.js';
  include 'js/images.js';

  include 'js/main.js';
?>
      /*]]>*/
    </script>
  </head>
  <body onload="init();" class="body">
    <form onsubmit="initFinish(); return false;">
      X: <input type="text" id="dimX" value="40"/>
      Y: <input type="text" id="dimY" value="40"/>
      Mines: <input type="text" id="minesNumber" value="200"/>
      <input type="submit" value="New"/>
    </form>
    <p/>
    <input type="submit" value="Open Random" onclick="Box.openRandom(); return false;"/>
    <input type="submit" value="Mark One" onclick="Box.markOne(); return false;"/>
    <input type="submit" value="Open One" onclick="Box.openOne(); return false;"/>
    <input type="submit" value="Mark All" onclick="Box.markAll(); return false;"/>
    <input type="submit" value="Open All" onclick="Box.openAll(); return false;"/>
    <input type="submit" value="Play" onclick="Box.play(); return false;"/>
    <p/>
    <form onsubmit="autoPlayStartStop(); return false;">
    Time: <input type="text" id="time" value="500"/>
    <input type="submit" value="Auto Play Start/Stop"/>
    </form>
    <p/>
    <canvas id="box"></canvas>
    <p/>
    <b>Goran "CHUPCKO" Lazic</b>
  </body>
</html>
