package org.chupcko.aLightOff;

import org.chupcko.aLightOff.Row;

public class Lights
{
  private int size;
  private Row rows[];

  public Lights(int newSize)
  {
    size = newSize;
    rows = new Row[size];
    for(int y = 0; y < size; y++)
      rows[y] = new Row(size);
  }

  public Lights(Lights lights)
  {
    size = lights.size;
    rows = new Row[size];
    for(int y = 0; y < size; y++)
      rows[y] = lights.rows[y].copy();
  }

  public Lights copy()
  {
    return new Lights(this);
  }

  public int getSize()
  {
    return size;
  }

  public boolean getLight(int x, int y)
  {
    if(y >= 0 && y < size)
      return rows[y].getLight(x);
    return false;
  }

  public void setLight(int x, int y, boolean value)
  {
    if(y >= 0 && y < size)
      rows[y].setLight(x, value);
  }

  public void setLightOff(int x, int y)
  {
    if(y >= 0 && y < size)
      rows[y].setLightOff(x);
  }

  public void setLightOn(int x, int y)
  {
    if(y >= 0 && y < size)
      rows[y].setLightOn(x);
  }

  public void toggleLight(int x, int y)
  {
    if(y >= 0 && y < size)
      rows[y].toggleLight(x);
  }

  public void setAllLightOff()
  {
    for(int y = 0; y < size; y++)
      rows[y].setAllLightOff();
  }

  public void setAllLightOn()
  {
    for(int y = 0; y < size; y++)
      rows[y].setAllLightOn();
  }

  public void play(int x, int y)
  {
    if(x >= 0 && x < size && y >= 0 && y < size)
    {
      toggleLight(x, y-1);
      toggleLight(x-1, y);
      toggleLight(x, y);
      toggleLight(x+1, y);
      toggleLight(x, y+1);
    }
  }

  public void setFirstRow(Row row)
  {
    for(int x = 0; x < size; x++)
      rows[0].setLight(x, row.getLight(x));
  }

  public void playFirstRow(Row row)
  {
    for(int x = 0; x < size; x++)
      if(row.getLight(x))
        play(x, 0);
  }

  public Row getLastRow()
  {
    return rows[size-1];
  }

  public Lights normalize()
  {
    Lights table = new Lights(size);
    table.setAllLightOff();
    for(int y = 0; y < size-1; y++)
      for(int x = 0; x < size; x++)
        if(getLight(x, y))
        {
          play(x, y+1);
          table.setLightOn(x, y+1);
        }
    return table;
  }

  public int ligthsNumber()
  {
    int number = 0;
    for(int y = 0; y < size; y++)
      number += rows[y].ligthsNumber();
    return number;
  }

  public int countDifferent(Lights lights)
  {
    if(size != lights.size)
      return size*size;
    int count = 0;
    for(int y = 0; y < size; y++)
      count += rows[y].countDifferent(lights.rows[y]);
    return count;
  }
}
