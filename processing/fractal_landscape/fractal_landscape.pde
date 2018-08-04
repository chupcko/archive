final int STEPS = 9;
final int WIDTH = 1200;
final int HEIGHT = 800;
landscape_c landscape;

int step;
boolean work;

void setup()
{
  size(WIDTH, HEIGHT);
  smooth();
  landscape = new landscape_c(STEPS, WIDTH, HEIGHT);
  step = 0;
  work = true;
  noLoop();
}

void draw()
{
  work = false;
  landscape.draw(step);
  work = true;
}

void keyTyped()
{
  if(work == true)
    switch(key)
    {
      case ' ':
        landscape.calculate();
        redraw();
        break;
      case 'f':
        landscape.toggle_fill();
        redraw();
        break;
      case 'r':
        landscape.ratio_init();
        redraw();
        break;
      case '[':
        landscape.ratio_down();
        redraw();
        break;
      case ']':
        landscape.ratio_up();
        redraw();
        break;
      case '-':
        step--;
        if(step < 0)
          step = 0;
        else
          redraw();
        break;
      case '+':
        step++;
        if(step >= STEPS)
          step = STEPS-1;
        else
          redraw();
        break;
      default:
        if(key >= '1' && key <= (char)((int)'0'+STEPS) && step != (int)key-(int)'0'-1)
        {
          step = (int)key-(int)'0'-1;
          redraw();
        }
    }
}
