class circle
{
  public complex center;
  public double radius;

  public circle()
  {
    center = new complex();
    radius = 0.0;
  }

  public circle(circle _circle)
  {
    center = new complex(_circle.center);
    radius = _circle.radius;
  }

  public circle(complex _center, double _radius)
  {
    center = new complex(_center);
    radius = _radius;
  }

  public circle(double _x, double _y, double _radius)
  {
    center = new complex(_x, _y);
    radius = _radius;
  }

  public void set(circle _circle)
  {
    center.set(_circle.center);
    radius = _circle.radius;
  }

  public void set(complex _center, double _radius)
  {
    center.set(_center);
    radius = _radius;
  }

  public void set(double _x, double _y, double _radius)
  {
    center.set(_x, _y);
    radius = _radius;
  }

  public void draw(boolean do_fill)
  {
    stroke(COLOR_BLACK);
    if(do_fill == true)
    {
      int fill_color = (int)Math.abs(radius*COLOR_SCALE);
      if(fill_color < 0)
        fill_color = 0;
      if(fill_color > 255)
        fill_color = 255;
      fill(color(fill_color, 255, fill_color));
    }
    else
      noFill();
    ellipseMode(RADIUS);
    ellipse
    (
      (float)(OFFSET_SIZE+center.real*SCALE_SIZE),
      (float)(OFFSET_SIZE+center.imaginary*SCALE_SIZE),
      (float)(radius*SCALE_SIZE),
      (float)(radius*SCALE_SIZE)
    );
  }
}
