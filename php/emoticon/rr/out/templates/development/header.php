<?php

  if(isset($rr_check) === false or $rr_check !== true)
    die();

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <title>RR-<?php echo($rr_version); ?> <?php echo($title); ?></title>
    <meta http-equiv="Content-Type" content="text/html;charset=utf-8"/>
    <style type="text/css">
      /*<![CDATA[*/
      a
      {
        color: rgb(10%, 0%, 100%);
        text-decoration: none;
      }

      a:active
      a:link,
      a:visited
      {
        color: rgb(10%, 0%, 100%);
      }

      a:focus,
      a:hover
      {
        text-decoration: underline;
      }

      body
      {
        background-color: rgb(100%, 100%, 100%);
        color: rgb(0%, 0%, 0%);
        font-family: lucida grande, tahoma, verdana, arial, helvetica, sans-serif;
        font-size: 10pt;
      }

      input,
      select
      {
        background-color: rgb(100%, 100%, 100%);
        border-color: rgb(0%, 0%, 0%);
        border-style: solid;
        border-width: 1px;
        font-family: lucida grande, tahoma, verdana, arial, helvetica, sans-serif;
        font-size: 10pt;
        margin: 1px;
        padding: 1px;
      }

      input[type="text"],
      input[type="password"]
      {
        width: 32em;
      }

      input[type="submit"]:focus,
      input[type="submit"]:hover
      {
        color: rgb(10%, 0%, 100%);
      }

      table,
      th,
      td
      {
        border-collapse:collapse;
        border-color: rgb(0%, 0%, 0%);
        border-style: solid;
        border-width: 1px;
        padding: 2px;
      }

      tr:hover
      {
        background-color: rgb(90%, 100%, 90%);
      }

      .message
      {
        color: rgb(100%, 0%, 0%);
      }
      /*]]>*/
    </style>
    <script type="text/javascript">
      /*<![CDATA[*/
      function toggle(id)
      {
        var element = document.getElementById(id);
        element.disabled = !element.disabled;
      }

      function select(from_id, to_id)
      {
        document.getElementById(to_id).value = document.getElementById(from_id).value;
      }
      /*]]>*/
    </script>
  </head>
  <body>
