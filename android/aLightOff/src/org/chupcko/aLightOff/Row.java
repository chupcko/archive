package org.chupcko.aLightOff;

public class Row
{
  private int size;
  private boolean lights[];

  public Row(int newSize)
  {
    size = newSize;
    lights = new boolean[size];
  }

  public Row(Row row)
  {
    size = row.size;
    lights = new boolean[size];
    for(int x = 0; x < size; x++)
      lights[x] = row.lights[x];
  }

  public Row copy()
  {
    return new Row(this);
  }

  public int getSize()
  {
    return size;
  }

  public boolean getLight(int x)
  {
    if(x >= 0 && x < size)
      return lights[x];
    return false;
  }

  public void setLight(int x, boolean value)
  {
    if(x >= 0 && x < size)
      lights[x] = value;
  }

  public void setLightOff(int x)
  {
    if(x >= 0 && x < size)
      lights[x] = false;
  }

  public void setLightOn(int x)
  {
    if(x >= 0 && x < size)
      lights[x] = true;
  }

  public void toggleLight(int x)
  {
    if(x >= 0 && x < size)
      lights[x] = !lights[x];
  }

  public void setAllLightOff()
  {
    for(int x = 0; x < size; x++)
      lights[x] = false;
  }

  public void setAllLightOn()
  {
    for(int x = 0; x < size; x++)
      lights[x] = true;
  }

  public int countCombinations()
  {
    int count = 1;
    for(int i = 0; i < size; i++)
      count *= 2;
    return count;
  }

  public void setCombinations(int combination)
  {
    for(int x = 0; x < size; x++)
    {
      lights[x] = combination%2 == 1;
      combination /= 2;
    }
  }

  public int ligthsNumber()
  {
    int number = 0;
    for(int x = 0; x < size; x++)
      if(lights[x])
        number++;
    return number;
  }

  public int countDifferent(Row row)
  {
    int count = 0;
    for(int x = 0; x < size; x++)
      if(lights[x] != row.lights[x])
        count++;
    return count;
  }

  public boolean equals(Row row)
  {
    if(size != row.size)
      return false;
    for(int x = 0; x < size; x++)
      if(lights[x] != row.lights[x])
        return false;
    return true;
  }

  public boolean equals(Object object)
  {
    if(getClass().getName().compareTo(object.getClass().getName()) != 0)
      return false;
    return equals((Row)object);
  }

  public int hashCode()
  {
    if(lights[0])
      return 1;
    return 0;
  }
}
