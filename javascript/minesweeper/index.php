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
    <button onclick="initNew(8, 8, 10); return false;">Beginner</button>
    <button onclick="initNew(16, 16, 40); return false;">Intermediate</button>
    <button onclick="initNew(30, 16, 99); return false;">Expert</button>
    X: <input type="text" id="dimX" value="40"/>
    Y: <input type="text" id="dimY" value="40"/>
    Mines: <input type="text" id="minesNumber" value="200"/>
    <button onclick="initFinish(); return false;">New</button>
    <p/>
    <button onclick="Box.openRandom(); return false;">Open Random</button>
    <button onclick="Box.markOne(); return false;">Mark One</button>
    <button onclick="Box.openOne(); return false;">Open One</button>
    <button onclick="Box.markAll(); return false;">Mark All</button>
    <button onclick="Box.openAll(); return false;">Open All</button>
    <button onclick="Box.play(); return false;">Play</button>
    Delay: <input type="text" id="delay" value="100"/>
    <button onclick="autoPlayStartStop(); return false;">Auto Play Start/Stop</button>
    <p/>
    Time: <span id="time" class="number">0.0</span> Mines: <span id="mines" class="number">0</span>
    <p/>
    <canvas id="box"></canvas>
    <p/>
    <b>Goran "CHUPCKO" Lazic</b>
  </body>
</html>
