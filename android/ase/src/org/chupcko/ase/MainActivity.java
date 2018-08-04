package org.chupcko.ase;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends Activity
{
  @Override
  public void onCreate(Bundle savedInstanceState)
  {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.main);
    ((TextView)findViewById(R.id.jar_1)).setText(org.chupcko.ase.jar_1.Library.data());
    ((TextView)findViewById(R.id.jar_2)).setText(org.chupcko.ase.jar_2.Library.data());
    ((TextView)findViewById(R.id.jni_1)).setText(jni1Data());
    ((TextView)findViewById(R.id.jni_2)).setText(jni2Data());
  }

  public native String jni1Data();
  public native String jni2Data();

  static
  {
    System.loadLibrary("ase_1");
    System.loadLibrary("ase_2");
  }
}
