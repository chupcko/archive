class point_c
{
  public double x;
  public double y;

  public point_c()
  {
    x = 0.0;
    y = 0.0;
  }

  public point_c(double _x, double _y)
  {
    x = _x;
    y = _y;
  }

  public point_c(point_c point)
  {
    x = point.x;
    y = point.y;
  }
}
