<?
  $MSESSION_mysql_link=0;
  $MSESSION_mysql_host='{{host}}';
  $MSESSION_mysql_user='{{user}}';
  $MSESSION_mysql_password='{{password}}';
  $MSESSION_mysql_database='{{database}}';
  $MSESSION_mysql_table='{{table}}';
  $MSESSION_name='';

  function MSESSION_open($path,$name)
  {
    global $MSESSION_mysql_link;
    global $MSESSION_mysql_host;
    global $MSESSION_mysql_user;
    global $MSESSION_mysql_password;
    global $MSESSION_mysql_database;
    global $MSESSION_name;
    $MSESSION_name=$name;
    if(($MSESSION_mysql_link=mysql_connect($MSESSION_mysql_host,$MSESSION_mysql_user,$MSESSION_mysql_password))===false)
      return false;
    if(mysql_select_db($MSESSION_mysql_database,$MSESSION_mysql_link)===false)
      return false;
    return true;
  }

  function MSESSION_close()
  {
    global $MSESSION_mysql_link;
    mysql_close($MSESSION_mysql_link);
    return true;
  }

  function MSESSION_read($key)
  {
    global $MSESSION_mysql_link;
    global $MSESSION_mysql_table;
    global $MSESSION_name;
    if(($result=mysql_query('select * from '.$MSESSION_mysql_table.' where name="'.$MSESSION_name.'" and id="'.$key.'"',$MSESSION_mysql_link))===false)
      return false;
    $row=mysql_fetch_array($result);
    mysql_free_result($result);
    if($row===false)
      return false;
    else
      return base64_decode($row['data']);
  }

  function MSESSION_write($key,$data)
  {
    global $MSESSION_mysql_link;
    global $MSESSION_mysql_table;
    global $MSESSION_name;
    if(($result=mysql_query('select * from '.$MSESSION_mysql_table.' where name="'.$MSESSION_name.'" and id="'.$key.'"',$MSESSION_mysql_link))===false)
      return false;
    $num=mysql_num_rows($result);
    mysql_free_result($result);
    if($num==0)
    {
      if(mysql_query('insert into '.$MSESSION_mysql_table.' (name,id,data,date) values ("'.$MSESSION_name.'","'.$key.'","'.base64_encode($data).'",now())',$MSESSION_mysql_link)===false)
        return false;
    }
    else
      if(mysql_query('update '.$MSESSION_mysql_table.' set data="'.base64_encode($data).'", date=now() where name="'.$MSESSION_name.'" and id="'.$key.'"',$MSESSION_mysql_link)===false)
        return false;
    return true;
  }

  function MSESSION_destroy($key)
  {
    global $MSESSION_mysql_link;
    global $MSESSION_mysql_table;
    global $MSESSION_name;
    if(mysql_query('delete from '.$MSESSION_mysql_table.' where name="'.$MSESSION_name.'" and id="'.$key.'"',$MSESSION_mysql_link)===false)
      return false;
    return true;
  }

  function MSESSION_gc($maxlifetime)
  {
    global $MSESSION_mysql_link;
    global $MSESSION_mysql_table;
    global $MSESSION_name;
    if(mysql_query('delete from '.$MSESSION_mysql_table.' where name="'.$MSESSION_name.'" and unix_timestamp()-unix_timestamp(date)>"'.$maxlifetime.'"',$MSESSION_mysql_link)===false)
      return false;
    return true;
  }

  session_set_save_handler('MSESSION_open','MSESSION_close','MSESSION_read','MSESSION_write','MSESSION_destroy','MSESSION_gc');
# session_name('MSESSIONID');
  session_start();
?>
