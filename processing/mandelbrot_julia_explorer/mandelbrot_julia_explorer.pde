final int SIZE_X = 500;
final int SIZE_Y = 500;
final float SIZE_X_OVER_SIZE_Y = (float)SIZE_X/(float)SIZE_Y;
final float SIZE_Y_OVER_SIZE_X = (float)SIZE_Y/(float)SIZE_X;

mandelbrot_c mandelbrot;
julia_c julia;

final int STATE_POINT  = 0;
final int STATE_LINE   = 1;
final int STATE_CIRCLE = 2;
final int STATE_ZOOM   = 3;
int state;

int mouse_1_x;
int mouse_1_y;
boolean mouse_set_1;
int mouse_2_x;
int mouse_2_y;

double julia_1_x;
double julia_1_y;
double julia_2_x;
double julia_2_y;

boolean walk;
int walk_max_count;
int walk_count;
boolean walk_ascend;
float walk_radius;
int walk_step;
final int WALK_MAX_STEP = 10;

void mouse_handling_point()
{
  if(mouseX < SIZE_X && mouse_set_1 == true)
    if(mousePressed == true)
    {
      mouse_2_x = mouseX;
      mouse_2_y = mouseY;
      if(mouse_1_x != mouse_2_x || mouse_1_y != mouse_2_y)
      {
        mouse_1_x = mouse_2_x;
        mouse_1_y = mouse_2_y;
        julia.init(mandelbrot.box_get_point_x(mouse_1_x), mandelbrot.box_get_point_y(mouse_1_y));
      }
    }
    else
      mouse_set_1 = false;
  else
    if(mouseX < SIZE_X && mousePressed == true)
    {
      mouse_set_1 = true;
      mouse_1_x = mouseX;
      mouse_1_y = mouseY;
      julia.init(mandelbrot.box_get_point_x(mouse_1_x), mandelbrot.box_get_point_y(mouse_1_y));
    }
}

void mouse_handling_line()
{
  if(mouseX < SIZE_X && mouse_set_1 == true)
    if(mousePressed == true)
    {
      mouse_2_x = mouseX;
      mouse_2_y = mouseY;
      stroke(0, 255, 0);
      line(mouse_1_x, mouse_1_y, mouse_2_x, mouse_2_y);
    }
    else
    {
      mouse_set_1 = false;
      julia_1_x = mandelbrot.box_get_point_x(mouse_1_x);
      julia_1_y = mandelbrot.box_get_point_y(mouse_1_y);
      julia_2_x = mandelbrot.box_get_point_x(mouse_2_x);
      julia_2_y = mandelbrot.box_get_point_y(mouse_2_y);
      walk = true;
      walk_count = 0;
      walk_ascend = true;
      walk_max_count = (int)sqrt(sq((float)(mouse_2_x-mouse_1_x))+sq((float)(mouse_2_y-mouse_1_y)));
    }
  else
    if(mouseX < SIZE_X && mousePressed == true)
    {
      mouse_set_1 = true;
      mouse_1_x = mouseX;
      mouse_1_y = mouseY;
    }
}

void mouse_handling_circle()
{
  if(mouseX < SIZE_X && mouse_set_1 == true)
    if(mousePressed == true)
    {
      mouse_2_x = mouseX;
      mouse_2_y = mouseY;
      float radius = sqrt(sq(mouse_2_x-mouse_1_x)+sq(mouse_2_y-mouse_1_y));
      stroke(0, 255, 0);
      ellipseMode(RADIUS);
      noFill();
      ellipse(mouse_1_x, mouse_1_y, radius, radius);
    }
    else
    {
      mouse_set_1 = false;
      julia_1_x = mandelbrot.box_get_point_x(mouse_1_x);
      julia_1_y = mandelbrot.box_get_point_y(mouse_1_y);
      julia_2_x = mandelbrot.box_get_point_x(mouse_2_x);
      julia_2_y = mandelbrot.box_get_point_y(mouse_2_y);
      walk = true;
      walk_count = 0;
      walk_radius = sqrt(sq((float)(julia_2_x-julia_1_x))+sq((float)(julia_2_y-julia_1_y)));
      walk_max_count = (int)(TWO_PI*(float)sqrt(sq((float)(mouse_2_x-mouse_1_x))+sq((float)(mouse_2_y-mouse_1_y))));
    }
  else
    if(mouseX < SIZE_X && mousePressed == true)
    {
      mouse_set_1 = true;
      mouse_1_x = mouseX;
      mouse_1_y = mouseY;
    }
}

void mouse_handling_zoom()
{
  if(mouseX < SIZE_X && mouse_set_1 == true)
    if(mousePressed == true)
    {
      float diff_x = mouseX-mouse_1_x;
      float diff_y = mouseY-mouse_1_y;
      if(diff_x/diff_y < SIZE_X_OVER_SIZE_Y)
      {
        mouse_2_x = mouse_1_x+(int)(diff_y*SIZE_X_OVER_SIZE_Y);
        mouse_2_y = mouse_1_y+(int)(diff_y);
      }
      else
      {
        mouse_2_x = mouse_1_x+(int)(diff_x);
        mouse_2_y = mouse_1_y+(int)(diff_x*SIZE_Y_OVER_SIZE_X);
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
      mandelbrot.box_zoom
      (
        mandelbrot.box_get_point_x(mouse_1_x),
        mandelbrot.box_get_point_y(mouse_1_y),
        mandelbrot.box_get_point_x(mouse_2_x),
        mandelbrot.box_get_point_y(mouse_2_y)
      );
    }
  else
    if(mouseX < SIZE_X && mousePressed == true)
    {
      mouse_set_1 = true;
      mouse_1_x = mouseX;
      mouse_1_y = mouseY;
    }
}

void keyTyped()
{
  switch(key)
  {
    case 'r':
      mandelbrot.box_init();
      julia.init(0.0, 0.0);
      walk = false;
      walk_step = 1;
      break;
    case 'p':
      state = STATE_POINT;
      walk = false;
      break;
    case 'l':
      state = STATE_LINE;
      walk = false;
      break;
    case 'c':
      state = STATE_CIRCLE;
      walk = false;
      break;
    case 'z':
      state = STATE_ZOOM;
      walk = false;
      break;
    case 'b':
      mandelbrot.box_unzoom();
      break;
    case '+':
      walk_step++;
      if(walk_step > WALK_MAX_STEP)
        walk_step = WALK_MAX_STEP;
      break;
    case '-':
      walk_step--;
      if(walk_step < 1)
        walk_step = 1;
      break;
    case '0':
      walk_step = 1;
      break;
  }
}

void setup()
{
  size(SIZE_X*2, SIZE_Y);
  smooth();
  mandelbrot = new mandelbrot_c(SIZE_X, SIZE_Y);
  julia = new julia_c(SIZE_X, SIZE_Y);
  state = STATE_POINT;
  mouse_set_1 = false;
  walk = false;
  walk_step = 1;
}

void draw()
{
  image(mandelbrot.image, 0, 0);
  image(julia.image, SIZE_X, 0);
  mandelbrot.calculate();
  if(mandelbrot.calculate_do == false)
  {
    float red_x = (float)mandelbrot.box_get_index_x(julia.get_c_x());
    float red_y = (float)mandelbrot.box_get_index_y(julia.get_c_y());
    if(red_x < SIZE_X)
    {
      stroke(255, 0, 0);
      line(red_x-1.0, red_y, red_x+1.0, red_y);
      line(red_x, red_y-1.0, red_x, red_y+1.0);
    }
  }
  julia.calculate();
  if(walk == true && julia.calculate_do == false)
    switch(state)
    {
      case STATE_LINE:
        float offset = (float)walk_count/(float)walk_max_count;
        julia.init
        (
          julia_1_x+(julia_2_x-julia_1_x)*offset,
          julia_1_y+(julia_2_y-julia_1_y)*offset
        );
        if(walk_ascend == true)
        {
          walk_count += walk_step;
          if(walk_count > walk_max_count)
          {
            walk_count = walk_max_count;
            walk_ascend = false;
          }
        }
        else
        {
          walk_count -= walk_step;
          if(walk_count < 0)
          {
            walk_count = 0;
            walk_ascend = true;
          }
        }
        break;
      case STATE_CIRCLE:
        float angle = TWO_PI*(float)walk_count/(float)walk_max_count;
        julia.init
        (
          julia_1_x+cos(angle)*walk_radius,
          julia_1_y+sin(angle)*walk_radius
        );
        walk_count += walk_step;
        if(walk_count > walk_max_count)
          walk_count = 0;
        break;
    }
  switch(state)
  {
    case STATE_POINT:
      mouse_handling_point();
      break;
    case STATE_LINE:
      mouse_handling_line();
      break;
    case STATE_CIRCLE:
      mouse_handling_circle();
      break;
    case STATE_ZOOM:
      mouse_handling_zoom();
      break;
  }
}
