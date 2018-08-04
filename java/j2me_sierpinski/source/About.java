package sierpinski;

import javax.microedition.lcdui.*;

public class About
{
  public About()
  {
  }

  public static void show(Display display)
  {
    Alert alert = new Alert("About sierpinski");

    alert.setTimeout(Alert.FOREVER);
    alert.setString("CHUPCKO");
    display.setCurrent(alert);
  }
}
