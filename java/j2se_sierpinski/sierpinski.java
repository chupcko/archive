import java.awt.*;
import java.applet.*;
import java.util.*;

public class sierpinski
  extends Applet
  implements Runnable
{
  private static final int number_point = 3;
  private static final int series = 10000;
  private static final double step_theta = 3.0;
  private static final double step_phi = 10.0;
  private static final int delay = 1;
  private int width;
  private int height;
  private Image image;
  private Graphics graphics;
  private Random random = new Random();

  public void init()
  {
    width = getSize().width;
    height = getSize().height;
    image = createImage(width, height);
    graphics = image.getGraphics();
  }

  public void start()
  {
    new Thread(this).start();
  }

  public void stop()
  {
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
    Color colors[] = {Color.RED, Color.GREEN, Color.BLUE};
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
        graphics.setColor(colors[i%number_point]);
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

  private void clear()
  {
    graphics.setColor(Color.WHITE);
    graphics.fillRect(0, 0, width, height);
  }

  public void paint(Graphics g)
  {
    g.drawImage(image, 0, 0, this);
  }

  public String getAppletInfo()
  {
    return "Sierpinski";
  }
}
