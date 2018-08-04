class mandelbrot_c
{
  private final int COUNT = 200;
  private final int CALCULATE_COUNT = 25000;
  private int size_x;
  private int size_y;

  public PImage image;
  private int calculate_x;
  private int calculate_y;
  public boolean calculate_do;

  private ArrayList boxes;
  private int boxes_number;

  public mandelbrot_c(int _size_x, int _size_y)
  {
    size_x = _size_x;
    size_y = _size_y;
    image = createImage(SIZE_X, SIZE_Y, RGB);
    box_init();
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
    box_c box = (box_c)boxes.get(boxes_number);
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
      z.y = 2.0*z.x*z.y+p.y;
      z.x = zz.x-zz.y+p.x;
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

  public void box_init()
  {
    boxes = new ArrayList();
    boxes.add(new box_c(new point_c(-2.0, 2.0), new point_c(2.0, -2.0)));
    boxes_number = 0;
    calculate_init();
  }

  public void box_zoom(double box_1_x, double box_1_y, double box_2_x, double box_2_y)
  {
    boxes.add(new box_c(new point_c(box_1_x, box_1_y), new point_c(box_2_x, box_2_y)));
    boxes_number++;
    calculate_init();
  }

  public void box_unzoom()
  {
    if(boxes_number > 0)
    {
      boxes.remove(boxes_number);
      boxes_number--;
      calculate_init();
    }
  }

  public double box_get_point_x(int x)
  {
    return ((box_c)boxes.get(boxes_number)).get_point_x(x, size_x);
  }

  public double box_get_point_y(int y)
  {
    return ((box_c)boxes.get(boxes_number)).get_point_y(y, size_y);
  }

  public double box_get_index_x(double x)
  {
    return ((box_c)boxes.get(boxes_number)).get_index_x(x, size_x);
  }

  public double box_get_index_y(double y)
  {
    return ((box_c)boxes.get(boxes_number)).get_index_y(y, size_y);
  }
}
