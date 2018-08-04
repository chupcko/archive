final int SIZE_X       = 20;
final int SIZE_Y       = 20;
final int MINES_NUMBER = 40;

final int IMAGE_SPACE_SIZE_X = 16;
final int IMAGE_SPACE_SIZE_Y = 16;
final int PADDING_SIZE_X     = 13;
final int PADDING_SIZE_Y     = 13;
final int FRAME_SIZE_X       = 3;
final int FRAME_SIZE_Y       = 3;
final int SPACE_SIZE_X       = IMAGE_SPACE_SIZE_X;
final int SPACE_SIZE_Y       = IMAGE_SPACE_SIZE_Y;
final color GAME_COLOR       = color(192);
final color WIN_COLOR        = color(0,   255, 0);
final color LOSE_COLOR       = color(255, 0,   0);

game_c Game;
automat_c Automat;
PImage Frame;
int Sprites_id;
PImage Sprites;

void setup()
{
  size
  (
    PADDING_SIZE_X+FRAME_SIZE_X+SPACE_SIZE_X*SIZE_X+FRAME_SIZE_X+PADDING_SIZE_X,
    PADDING_SIZE_Y+FRAME_SIZE_Y+SPACE_SIZE_Y*SIZE_Y+FRAME_SIZE_Y+PADDING_SIZE_Y
  );
  noLoop();
  Game = new game_c(SIZE_X, SIZE_Y, MINES_NUMBER);
  Automat = new automat_c(SIZE_X, SIZE_Y, MINES_NUMBER, Game);
  Frame = loadImage("frame.png");
  load_sprites(1);
}

void draw()
{
  int x;
  int y;

  if(Game.is_ended() == true)
    if(Game.is_win() == true)
      background(WIN_COLOR);
    else
      background(LOSE_COLOR);
  else
    background(GAME_COLOR);

  copy
  (
    Frame,
    0,                                               0,
    FRAME_SIZE_X,                                    FRAME_SIZE_Y,
    PADDING_SIZE_X,                                  PADDING_SIZE_Y,
    FRAME_SIZE_X,                                    FRAME_SIZE_Y
  );
  copy
  (
    Frame,
    FRAME_SIZE_X*2,                                  0,
    FRAME_SIZE_X,                                    FRAME_SIZE_Y,
    PADDING_SIZE_X+FRAME_SIZE_X,                     PADDING_SIZE_Y,
    SPACE_SIZE_X*SIZE_X,                             FRAME_SIZE_Y
  );
  copy
  (
    Frame,
    FRAME_SIZE_X*4,                                  0,
    FRAME_SIZE_X,                                    FRAME_SIZE_Y,
    PADDING_SIZE_X+FRAME_SIZE_X+SPACE_SIZE_X*SIZE_X, PADDING_SIZE_Y,
    FRAME_SIZE_X,                                    FRAME_SIZE_Y
  );
  copy
  (
    Frame,
    0,                                               FRAME_SIZE_Y*2,
    FRAME_SIZE_X,                                    FRAME_SIZE_Y,
    PADDING_SIZE_X,                                  PADDING_SIZE_Y+FRAME_SIZE_Y,
    FRAME_SIZE_X,                                    SPACE_SIZE_Y*SIZE_Y
  );
  copy
  (
    Frame,
    FRAME_SIZE_X*4,                                  FRAME_SIZE_Y*2,
    FRAME_SIZE_X,                                    FRAME_SIZE_Y,
    PADDING_SIZE_X+FRAME_SIZE_X+SPACE_SIZE_X*SIZE_X, PADDING_SIZE_Y+FRAME_SIZE_Y,
    FRAME_SIZE_X,                                    SPACE_SIZE_Y*SIZE_Y
  );
  copy
  (
    Frame,
    0,                                               FRAME_SIZE_Y*4,
    FRAME_SIZE_X,                                    FRAME_SIZE_Y,
    PADDING_SIZE_X,                                  PADDING_SIZE_Y+FRAME_SIZE_Y+SPACE_SIZE_Y*SIZE_Y,
    FRAME_SIZE_X,                                    FRAME_SIZE_Y
  );
  copy
  (
    Frame,
    FRAME_SIZE_X*2,                                  FRAME_SIZE_Y*4,
    FRAME_SIZE_X,                                    FRAME_SIZE_Y,
    PADDING_SIZE_X+FRAME_SIZE_X,                     PADDING_SIZE_Y+FRAME_SIZE_Y+SPACE_SIZE_Y*SIZE_Y,
    SPACE_SIZE_X*SIZE_X,                             FRAME_SIZE_Y
  );
  copy
  (
    Frame,
    FRAME_SIZE_X*4,                                  FRAME_SIZE_Y*4,
    FRAME_SIZE_X,                                    FRAME_SIZE_Y,
    PADDING_SIZE_X+FRAME_SIZE_X+SPACE_SIZE_X*SIZE_X, PADDING_SIZE_Y+FRAME_SIZE_Y+SPACE_SIZE_Y*SIZE_Y,
    FRAME_SIZE_X,                                    FRAME_SIZE_Y
  );

  for(x = 0; x < SIZE_X; x++)
    for(y = 0; y < SIZE_Y; y++)
      copy
      (
        Sprites,
        IMAGE_SPACE_SIZE_X*Game.get_field(x, y),    0,
        IMAGE_SPACE_SIZE_X,                         IMAGE_SPACE_SIZE_Y,
        PADDING_SIZE_X+FRAME_SIZE_X+SPACE_SIZE_X*x, PADDING_SIZE_Y+FRAME_SIZE_Y+SPACE_SIZE_Y*y,
        SPACE_SIZE_X,                               SPACE_SIZE_Y
      );
}

void mousePressed()
{
  int mouse_x;
  int mouse_y;

  mouse_x = mouseX;
  mouse_y = mouseY;
  if
  (
    Game.is_ended() != true &&
    mouse_x >= PADDING_SIZE_X+FRAME_SIZE_X &&
    mouse_x <= PADDING_SIZE_X+FRAME_SIZE_X+SPACE_SIZE_X*SIZE_X &&
    mouse_y >= PADDING_SIZE_Y+FRAME_SIZE_Y &&
    mouse_y <= PADDING_SIZE_Y+FRAME_SIZE_Y+SPACE_SIZE_Y*SIZE_Y
  )
  {
    int x;
    int y;

    x = (mouse_x-PADDING_SIZE_X-FRAME_SIZE_X)/SPACE_SIZE_X;
    y = (mouse_y-PADDING_SIZE_Y-FRAME_SIZE_Y)/SPACE_SIZE_Y;
    if(mouseButton == LEFT)
    {
      Game.play(x, y);
      redraw();
    }
    else if(mouseButton == RIGHT)
    {
      Game.mark(x, y);
      redraw();
    }
  }
}

boolean load_sprites(int id)
{
  if
  (
    id >= 1 && id <= 2 &&
    Sprites_id != id
  )
  {
    Sprites_id = id;
    Sprites = loadImage("sprites-"+Sprites_id+".png");
    return true;
  }
  return false;
}

void keyTyped()
{
  boolean pass;

  switch(key)
  {
    case '1':
      if(load_sprites(1) == true)
        redraw();
      break;
    case '2':
      if(load_sprites(2) == true)
        redraw();
      break;
    case ' ':
      Game.init();
      redraw();
      break;
    case 'p':
      if(Game.is_ended() != true)
      {
        Automat.play();
        redraw();
      }
      break;
    case 'P':
      pass = false;
      while
      (
        Game.is_ended() != true &&
        Automat.play() == true
      )
        pass = true;
      if(pass == true)
        redraw();
      break;
    case 'm':
      if(Game.is_ended() != true)
      {
        Automat.mark();
        redraw();
      }
      break;
    case 'M':
      pass = false;
      while
      (
        Game.is_ended() != true &&
        Automat.mark() == true
      )
        pass = true;
      if(pass == true)
        redraw();
      break;
  }
}
