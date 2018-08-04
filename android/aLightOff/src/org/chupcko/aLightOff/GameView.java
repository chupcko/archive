package org.chupcko.aLightOff;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;

import org.chupcko.aLightOff.GameState;

public class GameView extends View
{
  public interface GameViewListener
  {
    abstract void changeInfo(String text);
  }

  private int size;
  private GameViewListener listener = null;
  private GameState gameState;
  private boolean doCalculateSolution;
  private boolean touch;
  private int touchX;
  private int touchY;
  private Paint paintBack;
  private Paint paintBackTouch;
  private Paint paintOn;
  private Paint paintOff;
  private Paint paintSolutionOn;
  private Paint paintSolutionOff;

  private final float cellSize = 40.0f;
  private final float backSize = cellSize*0.45f;
  private final float lightSize = cellSize*0.40f;
  private final float solutionSize = cellSize*0.1f;

  public GameView(Context context, AttributeSet attrs)
  {
    super(context, attrs);
    doCalculateSolution = false;
    requestFocus();
    touch = false;
    paintBack = new Paint();
    paintBack.setFlags(Paint.ANTI_ALIAS_FLAG);
    paintBack.setStyle(Paint.Style.FILL);
    paintBack.setColor(Color.rgb(255, 255, 255));
    paintBackTouch = new Paint(paintBack);
    paintBackTouch.setColor(Color.rgb(0, 0, 255));
    paintOn = new Paint(paintBack);
    paintOn.setColor(Color.rgb(0, 255, 0));
    paintOff = new Paint(paintBack);
    paintOff.setColor(Color.rgb(0, 0, 0));
    paintSolutionOn = new Paint(paintBack);
    paintSolutionOn.setColor(Color.rgb(128, 0, 0));
    paintSolutionOff = new Paint(paintBack);
    paintSolutionOff.setColor(Color.rgb(128, 128, 128));
  }

  public void setListener(GameViewListener value)
  {
    listener = value;
  }

  public void setSize(int newSize)
  {
    size = newSize;
    gameState = new GameState(size);
  }

  @Override protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec)
  {
    super.onMeasure(widthMeasureSpec, heightMeasureSpec);
    int w = MeasureSpec.getSize(widthMeasureSpec);
    int h = MeasureSpec.getSize(heightMeasureSpec);
    int d = w == 0 ? h : h == 0 ? w : w < h ? w : h;
    setMeasuredDimension(d, d);/***/
  }

  @Override protected void onSizeChanged(int w, int h, int oldw, int oldh)
  {
    super.onSizeChanged(w, h, oldw, oldh);/****/
  }

  @Override protected void onDraw(Canvas canvas)
  {
    super.onDraw(canvas);
    canvas.drawColor(Color.rgb(0, 0, 0));
    for(int x = 0; x < size; x++)
      for(int y = 0; y < size; y++)
      {
        float centerX = ((float)(x)+0.5f)*cellSize;
        float centerY = ((float)(y)+0.5f)*cellSize;
        if
        ( touch &&
          touchX >= 0 && touchX < size &&
          touchY >= 0 && touchY < size &&
          (
            (x == touchX && y == touchY-1) ||
            (x == touchX-1 && y == touchY) ||
            (x == touchX && y == touchY) ||
            (x == touchX+1 && y == touchY) ||
            (x == touchX && y == touchY+1)
          )
        )
          canvas.drawCircle(centerX, centerY, backSize, paintBackTouch);
        else
          canvas.drawCircle(centerX, centerY, backSize, paintBack);
        if(gameState.getLight(x, y))
          canvas.drawCircle(centerX, centerY, lightSize, paintOn);
        else
          canvas.drawCircle(centerX, centerY, lightSize, paintOff);
        if(doCalculateSolution)
          if(gameState.getSolutionLight(x, y))
            canvas.drawRect(centerX-solutionSize, centerY-solutionSize, centerX+solutionSize, centerY+solutionSize, paintSolutionOn);
          else
            canvas.drawRect(centerX-solutionSize, centerY-solutionSize, centerX+solutionSize, centerY+solutionSize, paintSolutionOff);
      }
  }

  @Override public boolean onTouchEvent(MotionEvent event)
  {
    switch(event.getAction())
    {
      case MotionEvent.ACTION_DOWN:
      {
        touch = true;
        float rawX = event.getX();
        float rawY = event.getY();
        if(rawX >=0 && rawX < (float)size*cellSize && rawY >=0 && rawY < (float)size*cellSize)
        {
          touchX = (int)(rawX/cellSize);
          touchY = (int)(rawY/cellSize);
          invalidate();
        }
        else
        {
          touchX = -1;
          touchY = -1;
        }
        return true;
      }
      case MotionEvent.ACTION_MOVE:
      {
        float rawX = event.getX();
        float rawY = event.getY();
        int x;
        int y;
        if(rawX >=0 && rawX < (float)size*cellSize && rawY >=0 && rawY < (float)size*cellSize)
        {
          x = (int)(rawX/cellSize);
          y = (int)(rawY/cellSize);
        }
        else
        {
          x = -1;
          y = -1;
        }
        if(x != touchX || y != touchY)
        {
          touchX = x;
          touchY = y;
          invalidate();
        }
        return true;
      }
      case MotionEvent.ACTION_UP:
      {
        touch = false;
        float rawX = event.getX();
        float rawY = event.getY();
        if(rawX >=0 && rawX < (float)size*cellSize && rawY >=0 && rawY < (float)size*cellSize)
        {
          int x = (int)(rawX/cellSize);
          int y = (int)(rawY/cellSize);
          if(x >= 0 && x < size && y >= 0 && y < size)
          {
            gameState.play(x, y);
            if(doCalculateSolution)
              gameState.calculateSolution();
          }
          invalidate();
        }
        return true;
      }
    }
    return false;
  }

  public void reset()
  {
    gameState.reset();
    if(doCalculateSolution)
    {
      gameState.cleanSolution();
      gameState.calculateSolution();
    }
    invalidate();
  }

  public void mix()
  {
    gameState.mix();
    if(doCalculateSolution)
    {
      gameState.cleanSolution();
      gameState.calculateSolution();
    }
    invalidate();
  }

  public void toggleDoCalculateSolution()
  {
    doCalculateSolution = !doCalculateSolution;
    if(doCalculateSolution)
    {
      gameState.cleanSolution();
      gameState.calculateSolution();
    }
    invalidate();
  }
}
