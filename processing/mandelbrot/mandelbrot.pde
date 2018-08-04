final int SIZE_X = 500;
final int SIZE_Y = 500;
final float SIZE_X_OVER_SIZE_Y = float(SIZE_X)/float(SIZE_Y);
final float SIZE_Y_OVER_SIZE_X = float(SIZE_Y)/float(SIZE_X);
final int WORK_COUNT = 25000;

final int COUNT = 200;
double M_1_X;
double M_1_Y;
double M_2_X;
double M_2_Y;

void mandelbrot_init(int w, int h)
{
  M_1_X = -2.0; /**/
  M_1_Y = 2.0;
  M_2_X = 2.0;
  M_2_Y = -2.0;
}

void mandelbrot_new(int point_1_x, int point_1_y, int point_2_x, int point_2_y, int w, int h)
{
  double n_1_x = M_1_X+(M_2_X-M_1_X)*float(point_1_x)/float(w);
  double n_1_y = M_1_Y+(M_2_Y-M_1_Y)*float(point_1_y)/float(h);
  double n_2_x = M_1_X+(M_2_X-M_1_X)*float(point_2_x)/float(w);
  double n_2_y = M_1_Y+(M_2_Y-M_1_Y)*float(point_2_y)/float(h);
  M_1_X = n_1_x;
  M_1_Y = n_1_y;
  M_2_X = n_2_x;
  M_2_Y = n_2_y;
}

color mandelbrot_calculate(int point_x, int point_y, int w, int h)
{
  double p_x = M_1_X+(M_2_X-M_1_X)*float(point_x)/float(w);
  double p_y = M_1_Y+(M_2_Y-M_1_Y)*float(point_y)/float(h);
  double x = p_x;
  double y = p_y;
  double xx;
  double yy;
  int n;
  
  for(n = 0; n < COUNT; n++)
  {
    xx = x*x;
    yy = y*y;
    if(xx+yy > 4.0)
       break;
    y = 2.0*x*y+p_y;
    x = xx-yy+p_x;
  }
  if(n == COUNT)
    return color(0);
  return color(255-n*255/COUNT);
}

int work_x;
int work_y;
boolean work_flag;
PImage work_image;

void work_init()
{
  work_x = 0;
  work_y = 0;
  work_flag = true;
}

void work_next()
{
  work_x++;
  if(work_x == width)
  {
    work_x = 0;
    work_y++;
    if(work_y == height)
    {
      work_y = 0;
      work_flag = false;
    }
  }
}

int mouse_1_x;
int mouse_1_y;
boolean mouse_set_1;
int mouse_2_x;
int mouse_2_y;

void mouse_handling()
{
  if(mouse_set_1 == true)
  {
    if(mousePressed == true)
    {
      float diff_x = mouseX-mouse_1_x;
      float diff_y = mouseY-mouse_1_y;
      if(diff_x/diff_y < SIZE_X_OVER_SIZE_Y)
      {
        mouse_2_x = mouse_1_x+int(diff_y*SIZE_X_OVER_SIZE_Y);
        mouse_2_y = mouse_1_y+int(diff_y);
      }
      else
      {
        mouse_2_x = mouse_1_x+int(diff_x);
        mouse_2_y = mouse_1_y+int(diff_x*SIZE_Y_OVER_SIZE_X);
      }
      stroke(0, 255, 0);
      rectMode(CORNER);
      noFill();
      rect(mouse_1_x, mouse_1_y, mouse_2_x-mouse_1_x, mouse_2_y-mouse_1_y);
    }
    else
    {
      mouse_set_1 = false;
      if(mouse_2_x < mouse_1_x || mouse_2_y < mouse_1_y)
      {
        int t = mouse_1_x;
        mouse_1_x = mouse_2_x;
        mouse_2_x = t;
        t = mouse_1_y;
        mouse_1_y = mouse_2_y;
        mouse_2_y = t;
      }
      mandelbrot_new(mouse_1_x, mouse_1_y, mouse_2_x, mouse_2_y, width, height);
      work_init();
    }
  }
  else
    if(mousePressed == true)
    {
      mouse_set_1 = true;
      mouse_1_x = mouseX;
      mouse_1_y = mouseY;
    }
}

void setup()
{
  size(SIZE_X, SIZE_Y);
  work_image = createImage(SIZE_X, SIZE_Y, RGB);
  smooth();
  work_init();
  mouse_set_1 = false;
  mandelbrot_init(SIZE_X, SIZE_Y);
}

void draw()
{
  image(work_image, 0, 0);
  if(work_flag == true)
    for(int i = 0; i < WORK_COUNT; i++)
    {
      work_image.set(work_x, work_y, mandelbrot_calculate(work_x, work_y, width, height));
      work_next();
    }
  mouse_handling();
}

void keyTyped()
{
  if(key == '0')
  {
    mandelbrot_init(width, height);
    work_init();
  }
}

