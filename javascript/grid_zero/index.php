<?= '<?xml version="1.0" encoding="utf-8"?>'.PHP_EOL ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <title>Grid Zero</title>
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
  include 'js/box.js';

  include 'js/main.js';
?>
      /*]]>*/
    </script>
  </head>
  <body class="body" onload="init();">
    N: <select id="N" onchange="init(); return false;">
<?php

  $minN = 2;
  $defaultN = 3;
  $maxN = 15;

  for($i = $minN; $i <= $maxN; $i++)
    if($i == $defaultN)
      echo '      <option selected="selected">'.$i.'</option>'.PHP_EOL;
    else
      echo '      <option>'.$i.'</option>'.PHP_EOL;

?>
    </select>
    Edit: <input type="checkbox" id="edit" onchange="Box.toggleMode(); return false;"/>
    Show Input: <input type="checkbox" id="show_input" onchange="toggleInput(); return false;"/>
    <input type="submit" id="clear_input" value="Clear Input" onclick="Box.clearInput(); return false;"/>
    <input type="submit" id="count_input" value="Count Input" onclick="alert(Box.countInput()); return false;"/>
    <input type="submit" value="Reset" onclick="Box.reset(); return false;"/>
    <input type="submit" value="Random" onclick="Box.fillRandom(); return false;"/>
    <input type="submit" value="Shuffle" onclick="Box.shuffle(); return false;"/>
    <input type="submit" value="Save" onclick="Box.save(); return false;"/>
    <input type="submit" value="Load" onclick="Box.load(); return false;"/>
    <input type="submit" value="Help" onclick="alert('Kowalski said: no HELP !'); return false;"/>
    <p/>
    <canvas id="box"></canvas>
    <p/>
    <b>Goran "CHUPCKO" Lazic</b>
  </body>
</html>
