package org.chupcko.aLightOff;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Random;

import org.chupcko.aLightOff.Lights;
import org.chupcko.aLightOff.Row;

public class GameState
{
  private int size;
  private Lights lights;
  private Lights solution;
  private Map<Row, List<Row>> corrections;

  public GameState(int newSize)
  {
    size = newSize;
    lights = new Lights(size);
    lights.setAllLightOn();
    solution = new Lights(size);
    corrections = new HashMap<Row, List<Row>>();
    Row firstRow = new Row(size);
    int countCombinations = firstRow.countCombinations();
    Lights table = new Lights(size);
    for(int i = 0; i < countCombinations; i++)
    {
      firstRow.setCombinations(i);
      table.setAllLightOff();
      table.playFirstRow(firstRow);
      table.normalize();
      Row lastRow = table.getLastRow().copy();
      List<Row> list = corrections.get(lastRow);
      if(list == null)
      {
        list = new ArrayList<Row>();
        corrections.put(lastRow, list);
      }
      list.add(firstRow.copy());
    }
  }

  public void reset()
  {
    lights.setAllLightOn();
  }

  public void mix()
  {
    lights.setAllLightOn();
    Random random = new Random();
    for(int y = 0; y < size; y++)
      for(int x = 0; x < size; x++)
        if(random.nextInt(2) == 0)
          lights.play(x, y);
  }

  public void play(int x, int y)
  {
    lights.play(x, y);
  }

  public boolean getLight(int x, int y)
  {
    return lights.getLight(x, y);
  }

  public boolean getSolutionLight(int x, int y)
  {
    return solution.getLight(x, y);
  }

  public boolean calculateSolution()
  {
    Lights table = lights.copy();
    table.normalize();
    List<Row> list = corrections.get(table.getLastRow());
    if(list == null || list.isEmpty())
      return false;
    Lights oldSolution = solution;
    int minLightsNumber = size*size;
    int minDifferent = size*size;
    solution = null;
    Iterator<Row> rows = list.iterator();
    while(rows.hasNext())
    {
      Row firstRow = rows.next();
      table = lights.copy();
      table.playFirstRow(firstRow);
      Lights currentSolution = table.normalize();
      currentSolution.setFirstRow(firstRow);
      int ligthsNumber = currentSolution.ligthsNumber();
      if(solution == null || ligthsNumber < minLightsNumber)
      {
        solution = currentSolution;
        minLightsNumber = ligthsNumber;
        minDifferent = oldSolution.countDifferent(currentSolution);
      }
      else if(ligthsNumber == minLightsNumber)
      {
        int different = oldSolution.countDifferent(currentSolution);
        if(different < minDifferent)
        {
          solution = currentSolution;
          minDifferent = different;
        }
      }
    }
    return true;
  }

  public void cleanSolution()
  {
    solution.setAllLightOff();
  }
}
