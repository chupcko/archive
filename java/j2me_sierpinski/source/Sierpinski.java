package sierpinski;

import javax.microedition.lcdui.*;
import javax.microedition.midlet.MIDlet;

public class Sierpinski
  extends MIDlet
  implements CommandListener
{
  private Display display;
  private Sierpinski_Canvas canvas;
  private Command exit_command = new Command("Exit", Command.EXIT, 1);
  private Command about_command = new Command("About", Command.HELP, 1);

  public Sierpinski()
  {
    display = Display.getDisplay(this);
    canvas = new Sierpinski_Canvas();
    canvas.addCommand(exit_command);
    canvas.addCommand(about_command);
    canvas.setCommandListener(this);
  }

  public void startApp()
  {
    display.setCurrent(canvas);
    try
    {
      new Thread(canvas).start();
    }
    catch(Error e)
    {
      destroyApp(false);
      notifyDestroyed();
    }
  }

  public void pauseApp()
  {
  }

  public void destroyApp(boolean unconditional)
  {
  }

  public void commandAction(Command c, Displayable s)
  {
    if(c == exit_command)
    {
      destroyApp(true);
      notifyDestroyed();
    }
    else if(c == about_command)
      About.show(display);
  }
}
