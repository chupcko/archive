class box_c
{
  public point_c point_1;
  public point_c point_2;

  public box_c(point_c _point_1, point_c _point_2)
  {
    point_1 = _point_1;
    point_2 = _point_2;
  }

  public double get_point_x(int x, int size_x)
  {
    return point_1.x+(point_2.x-point_1.x)*(double)x/(double)size_x;
  }

  public double get_point_y(int y, int size_y)
  {
    return point_1.y+(point_2.y-point_1.y)*(double)y/(double)size_y;
  }

  public double get_index_x(double x, int size_x)
  {
    return (x-point_1.x)*(double)size_x/(point_2.x-point_1.x);
  }

  public double get_index_y(double y, int size_y)
  {
    return (y-point_1.y)*(double)size_y/(point_2.y-point_1.y);
  }
}
