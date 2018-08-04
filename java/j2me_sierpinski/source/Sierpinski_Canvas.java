package sierpinski;

import javax.microedition.lcdui.*;
import javax.microedition.midlet.MIDlet;
import java.util.Random;

public class Sierpinski_Canvas
  extends Canvas
  implements Runnable
{
  private static final int number_point = 3;
  private static final int series = 750;
  private static final double step_theta = 3.0;
  private static final double step_phi = 10.0;
  private static final int delay = 1;
  private int width;
  private int height;
  private Image image;
  private Graphics graphics;
  private Random random = new Random();

  public Sierpinski_Canvas()
  {
    width = getWidth();
    height = getHeight();
    image = Image.createImage(width, height);
    graphics = image.getGraphics();
  }

  private void triangle(double x, double y, double radius, double angle)
  {
    int xp[] = new int[number_point];
    int yp[] = new int[number_point];
    int xt;
    int yt;
    int i;
  
    for(i = 0; i < number_point; i++)
    {
      xp[i] = (int)(x+radius*Math.cos(Math.toRadians(angle+(double)i*120.0)));
      yp[i] = (int)(y+radius*Math.sin(Math.toRadians(angle+(double)i*120.0)));
    }
    xt = xp[0];
    yt = yp[0];
    for(i = 0; i < series; i++)
    {
      int r = random.nextInt(number_point);
      
      xt += xp[r];
      xt /= 2;
      yt += yp[r];
      yt /= 2;
      graphics.drawLine(xt, yt, xt, yt);
    }
  }
  
  private double min(double a, double b)
  {
    return a < b ? a : b;
  }

  public void run()
  {
    double xc = (double)width/2.0;
    double yc = (double)height/2.0;
    double radius = min(xc, yc)/2.0-1.0;
    double theta = 0.0;
    double phi = 0.0;
    
    while(true)
    {
      clear();
      for(int i = 0; i < number_point; i++)
      {
        graphics.setColor
        (
          i % number_point == 0 ? 255 : 0,
          i % number_point == 1 ? 255 : 0,
          i % number_point == 2 ? 255 : 0
        );
        triangle
        (
          xc+radius*Math.cos(Math.toRadians(theta+(double)i*120.0)),
          yc+radius*Math.sin(Math.toRadians(theta+(double)i*120.0)),
          radius,
          phi
        );
      }
      repaint();
      try
      {
        Thread.sleep(delay);
      }
      catch(InterruptedException e)
      {
      }
      theta += step_theta;
      if(theta > 360.0)
        theta -= 360.0;
      phi += step_phi;
      if(phi > 360.0)
        phi -= 360.0;
    }
  }
  
  public void clear()
  {
    graphics.setColor(255, 255, 255);
    graphics.fillRect(0, 0, width, height);
  }

  protected void paint(Graphics g)
  {
    g.drawImage(image, 0, 0, 0);
  }
}
