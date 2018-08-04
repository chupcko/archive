class julia_c
{
  private final int COUNT = 50;
  private final int CALCULATE_COUNT = 25000;
  private int size_x;
  private int size_y;

  public PImage image;
  private int calculate_x;
  private int calculate_y;
  public boolean calculate_do;

  private box_c box;
  private point_c c;

  public julia_c(int _size_x, int _size_y)
  {
    size_x = _size_x;
    size_y = _size_y;
    image = createImage(SIZE_X, SIZE_Y, RGB);
    box = new box_c(new point_c(-2.0, 2.0), new point_c(2.0, -2.0));
    c = new point_c();
    init(0.0, 0.0);
  }

  private void calculate_init()
  {
    calculate_x = 0;
    calculate_y = 0;
    calculate_do = true;
  }

  private void calculate_next()
  {
    calculate_x++;
    if(calculate_x == size_x)
    {
      calculate_x = 0;
      calculate_y++;
      if(calculate_y == size_y)
      {
        calculate_y = 0;
        calculate_do = false;
      }
    }
  }

  private color calculate_color()
  {
    point_c p = new point_c(box.get_point_x(calculate_x, size_x), box.get_point_y(calculate_y, size_y));
    point_c z = new point_c(p);
    point_c zz = new point_c();
    int n;

    for(n = 0; n < COUNT; n++)
    {
      zz.x = z.x*z.x;
      zz.y = z.y*z.y;
      if(zz.x+zz.y > 4.0)
        break;
      z.y = 2.0*z.x*z.y+c.y;
      z.x = zz.x-zz.y+c.x;
    }
    if(n == COUNT)
      return color(0);
    return color(255-n*255/COUNT, 255-n*255/COUNT, 255);
  }

  public void calculate()
  {
    if(calculate_do == true)
      for(int i = 0; i < CALCULATE_COUNT; i++)
      {
        image.set(calculate_x, calculate_y, calculate_color());
        calculate_next();
      }
  }

  public void init(double c_x, double c_y)
  {
    c.x = c_x;
    c.y = c_y;
    calculate_init();
  }

  public double get_c_x()
  {
    return c.x;
  }

  public double get_c_y()
  {
    return c.y;
  }
}
