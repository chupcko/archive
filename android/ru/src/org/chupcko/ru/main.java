package org.chupcko.ru;

import android.app.Activity;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import java.io.*;

public class main extends Activity
{
  private static final String Name = "RU";
  private static final int BufferSize = 4096;

  @Override
  public void onCreate(Bundle savedInstanceState)
  {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.main);

    copyFromAssets(getAssets(), "busybox",        "/data/data/"+getApplicationContext().getPackageName()+"/assets/busybox",        false, true);
    copyFromAssets(getAssets(), "device.db",      "/data/data/"+getApplicationContext().getPackageName()+"/assets/device.db",      true,  false);
    copyFromAssets(getAssets(), "prepare",        "/data/data/"+getApplicationContext().getPackageName()+"/assets/prepare",        false, true);
    copyFromAssets(getAssets(), "ru",             "/data/data/"+getApplicationContext().getPackageName()+"/assets/ru",             false, true);
    copyFromAssets(getAssets(), "run_root_shell", "/data/data/"+getApplicationContext().getPackageName()+"/assets/run_root_shell", false, true);
    copyFromAssets(getAssets(), "su",             "/data/data/"+getApplicationContext().getPackageName()+"/assets/su",             false, true);
    copyFromAssets(getAssets(), "temproot",       "/data/data/"+getApplicationContext().getPackageName()+"/assets/temproot",       false, true);
  }

  public void copyFromAssets(AssetManager assetManager, String fromPath, String toPath, Boolean writeOther,  Boolean executableAll)
  {
    Log.d(Name, "copy "+toPath);
    File toPathFile = new File(toPath);
    if(toPathFile.isFile() != true)
      try
      {
        if(toPathFile.getParentFile().mkdirs() == true)
        {
          toPathFile.getParentFile().setReadable(true, false);
          toPathFile.getParentFile().setWritable(true, false);
          toPathFile.getParentFile().setExecutable(true, false);
        }
        toPathFile.createNewFile();
        InputStream in = assetManager.open(fromPath);
        OutputStream out = new FileOutputStream(toPath);
        byte[] buffer = new byte[BufferSize];
        int read;
        while(true)
        {
          read = in.read(buffer);
          if(read == -1)
            break;
          out.write(buffer, 0, read);
        }
        in.close();
        out.flush();
        out.close();
        toPathFile.setReadable(true, false);
        toPathFile.setWritable(true, !writeOther);
        toPathFile.setExecutable(executableAll, false);
      }
      catch(Exception e)
      {
        Toast.makeText(getApplicationContext(), "File ERROR", Toast.LENGTH_LONG).show();
      }
  }

  public void execute(View view)
  {
    String command = new String("/data/data/"+getApplicationContext().getPackageName()+"/assets/ru");
    Log.d(Name, "execute "+command);
    try
    {
      Runtime.getRuntime().exec(command);
      Toast.makeText(getApplicationContext(), "Started "+command, Toast.LENGTH_LONG).show();
    }
    catch(Exception e)
    {
      Toast.makeText(getApplicationContext(), "Execution ERROR", Toast.LENGTH_LONG).show();
    }
  }
}
