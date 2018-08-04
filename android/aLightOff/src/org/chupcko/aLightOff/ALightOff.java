package org.chupcko.aLightOff;

import android.app.Activity;
import android.app.AlertDialog;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.TextView;

import org.chupcko.aLightOff.GameView.GameViewListener;
import org.chupcko.aLightOff.GameView;

public class ALightOff extends Activity
{
  private TextView info;
  private GameView gameView;

  private class ALightOffListener implements GameViewListener
  {
    @Override public void changeInfo(String text)
    {
      info.setText(text);
    }
  }

  @Override public void onCreate(Bundle savedInstanceState)
  {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.main);
    info = (TextView)findViewById(R.id.info);
    gameView = (GameView)findViewById(R.id.game_view);
    gameView.setListener(new ALightOffListener());
    gameView.setSize(5);/***/
    CheckBox checkBoxSolution = (CheckBox)findViewById(R.id.checkbox_solution);
    checkBoxSolution.setChecked(false);
    checkBoxSolution.setOnCheckedChangeListener
    (
      new CompoundButton.OnCheckedChangeListener()
      {
        @Override public void onCheckedChanged(CompoundButton buttonView, boolean isChecked)
        {
          gameView.toggleDoCalculateSolution();
        }
      }
    );
    Button buttonMix = (Button)findViewById(R.id.button_mix);
    buttonMix.setOnClickListener
    (
      new View.OnClickListener()
      {
        @Override public void onClick(View view)
        {
          gameView.mix();
        }
      }
    );
    Button buttonReset = (Button)findViewById(R.id.button_reset);
    buttonReset.setOnClickListener
    (
      new View.OnClickListener()
      {
        @Override public void onClick(View view)
        {
          gameView.reset();
        }
      }
    );
  }

  @Override public boolean onCreateOptionsMenu(Menu menu)
  {
    MenuInflater inflater = getMenuInflater();
    inflater.inflate(R.menu.main, menu);
    return true;
  }

  @Override public boolean onOptionsItemSelected(MenuItem item)
  {
    switch(item.getItemId())
    {
      case R.id.menu_reset:
        gameView.reset();
        return true;
      case R.id.menu_mix:
        gameView.mix();
        return true;
      case R.id.menu_solution:
        gameView.toggleDoCalculateSolution();
        return true;
      case R.id.menu_about:
        showAbout();
        return true;
    }
    return super.onOptionsItemSelected(item);
  }

  protected void showAbout()
  {
    AlertDialog.Builder builder = new AlertDialog.Builder(this);
    builder.setTitle(R.string.app_name);
    builder.setMessage("CHUPCKO");
    builder.create();
    builder.show();
  }
}
