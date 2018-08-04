class calculate_c
{
  private int points;
  private int lines;
  private int triangles;

  public calculate_c(int steps)
  {
    int current_points;
    int current_lines;
    int current_triangles;
    int i;

    current_points = 3;
    current_lines = 3;
    current_triangles = 1;
    points =  current_points;
    lines =  current_lines;
    triangles =  current_triangles;
    for(i = 1; i < steps; i++)
    {
      current_points += current_lines;
      current_lines *= 2;
      current_lines += 3*current_triangles;
      current_triangles *= 4;
      points += current_points;
      lines += current_lines;
      triangles += current_triangles;
    }
  }

  public int points()
  {
    return points;
  }

  public int lines()
  {
    return lines;
  }

  public int triangles()
  {
    return triangles;
  }
}
