class game_c
{
  public static final int FIELD_NUMBER_0  = 0;
  public static final int FIELD_NUMBER_1  = 1;
  public static final int FIELD_NUMBER_2  = 2;
  public static final int FIELD_NUMBER_3  = 3;
  public static final int FIELD_NUMBER_4  = 4;
  public static final int FIELD_NUMBER_5  = 5;
  public static final int FIELD_NUMBER_6  = 6;
  public static final int FIELD_NUMBER_7  = 7;
  public static final int FIELD_NUMBER_8  = 8;
  public static final int FIELD_UNACTED   = 9;
  public static final int FIELD_MARKED    = 10;
  public static final int FIELD_EXPLOSION = 11;
  public static final int FIELD_MINE_YES  = 12;
  public static final int FIELD_MINE_NO   = 13;

  private int size_x;
  private int size_y;
  private int mines_count;

  private boolean ended;
  private boolean win;
  private int count_play;
  private field_c[][] fields;

  public game_c(int _size_x, int _size_y, int _mines_count)
  {
    int _x;
    int _y;

    size_x = _size_x;
    size_y = _size_y;
    mines_count = _mines_count;
    if(mines_count >= size_x*size_y)
      mines_count = size_x*size_y-1;
    fields = new field_c[size_x][size_y];
    for(_x = 0; _x < size_x; _x++)
      for(_y = 0; _y < size_y; _y++)
        fields[_x][_y] = new field_c();
    init();
  }

  public void init()
  {
    int _x;
    int _y;

    ended = false;
    win = false;
    count_play = 0;
    for(_x = 0; _x < size_x; _x++)
      for(_y = 0; _y < size_y; _y++)
        fields[_x][_y].init();
  }

  public void play(int x, int y)
  {
    if
    (
      ended != true &&
      x >= 0 && x < size_x &&
      y >= 0 && y < size_y &&
      fields[x][y].is_marked() != true
    )
    {
      if(fields[x][y].is_invisible() == true)
        play_on_invisible(x, y);
      if(fields[x][y].is_visible() == true)
        play_on_visible(x, y);
    }
  }

  private void play_on_invisible(int x, int y)
  {
    if(fields[x][y].has_mine() == true)
    {
      ended = true;
      fields[x][y].visible();
    }
    else
    {
      if(count_play == 0)
        shuffle(x, y);
      play_on_invisible_arround(x, y);
      if(count_play == size_x*size_y-mines_count)
      {
        int _x;
        int _y;

        ended = true;
        win = true;
        for(_x = 0; _x < size_x; _x++)
          for(_y = 0; _y < size_y; _y++)
            if(fields[_x][_y].has_mine() == true)
              fields[_x][_y].mark();
      }
    }
  }

  private void shuffle(int no_x, int no_y)
  {
    int i;
    int _x;
    int _y;

    for(i = 0; i < mines_count; i++)
    {
      do
      {
        _x = int(random(size_x));
        _y = int(random(size_y));
      }
      while
      (
        (_x == no_x && _y == no_y) ||
        fields[_x][_y].has_mine() == true
      );
      fields[_x][_y].set_mine();
    }
    for(_x = 0; _x < size_x; _x++)
      for(_y = 0; _y < size_y; _y++)
        if(fields[_x][_y].has_mine() != true)
          fields[_x][_y].set_content(number_mines_arround(_x, _y));
  }

  private int number_mines_arround(int x, int y)
  {
    return
      number_mine_on(x-1, y-1)+
      number_mine_on(x-1, y  )+
      number_mine_on(x-1, y+1)+
      number_mine_on(x,   y-1)+
      number_mine_on(x,   y+1)+
      number_mine_on(x+1, y-1)+
      number_mine_on(x+1, y  )+
      number_mine_on(x+1, y+1);
  }

  private int number_mine_on(int x, int y)
  {
    if
    (
      x >= 0 && x < size_x &&
      y >= 0 && y < size_y &&
      fields[x][y].has_mine() == true
    )
      return 1;
    return 0;
  }

  private void play_on_invisible_arround(int x, int y)
  {
    if
    (
      x >= 0 && x < size_x &&
      y >= 0 && y < size_y &&
      fields[x][y].is_invisible() == true
    )
    {
      fields[x][y].visible();
      count_play++;
      if(fields[x][y].is_empty() == true)
      {
        play_on_invisible_arround(x-1, y-1);
        play_on_invisible_arround(x-1, y  );
        play_on_invisible_arround(x-1, y+1);
        play_on_invisible_arround(x,   y-1);
        play_on_invisible_arround(x,   y+1);
        play_on_invisible_arround(x+1, y-1);
        play_on_invisible_arround(x+1, y  );
        play_on_invisible_arround(x+1, y+1);
      }
    }
  }

  private void play_on_visible(int x, int y)
  {
    if(fields[x][y].get_content() == number_marked_arround(x, y))
    {
      play_on_visible_helper(x-1, y-1);
      play_on_visible_helper(x-1, y  );
      play_on_visible_helper(x-1, y+1);
      play_on_visible_helper(x,   y-1);
      play_on_visible_helper(x,   y+1);
      play_on_visible_helper(x+1, y-1);
      play_on_visible_helper(x+1, y  );
      play_on_visible_helper(x+1, y+1);
    }
  }

  private int number_marked_arround(int x, int y)
  {
    return
      number_marked_on(x-1, y-1)+
      number_marked_on(x-1, y  )+
      number_marked_on(x-1, y+1)+
      number_marked_on(x,   y-1)+
      number_marked_on(x,   y+1)+
      number_marked_on(x+1, y-1)+
      number_marked_on(x+1, y  )+
      number_marked_on(x+1, y+1);
  }

  private int number_marked_on(int x, int y)
  {
    if
    (
      x >= 0 && x < size_x &&
      y >= 0 && y < size_y &&
      fields[x][y].is_marked() == true
    )
      return 1;
    return 0;
  }

  private void play_on_visible_helper(int x, int y)
  {
    if
    (
      ended != true &&
      x >= 0 && x < size_x &&
      y >= 0 && y < size_y &&
      fields[x][y].is_invisible() == true
    )
      play_on_invisible(x, y);
  }

  public void mark(int x, int y)
  {
    if
    (
      ended != true &&
      x >= 0 && x < size_x &&
      y >= 0 && y < size_y &&
      fields[x][y].is_visible() != true
    )
      if(fields[x][y].is_marked() != true)
        fields[x][y].mark();
      else
        fields[x][y].invisible();
  }

  public boolean is_ended()
  {
    if(ended == true)
      return true;
    return false;
  }

  public boolean is_win()
  {
    if
    (
      ended == true &&
      win == true
    )
      return true;
    return false;
  }

  public int get_field(int x, int y)
  {
    if
    (
      x >= 0 && x < size_x &&
      y >= 0 && y < size_y
    )
      if(ended != true)
      {
        if(fields[x][y].is_invisible() == true)
          return FIELD_UNACTED;
        if(fields[x][y].is_visible() == true)
          return fields[x][y].get_content();
        if(fields[x][y].is_marked() == true)
          return FIELD_MARKED;
      }
      else
        if(fields[x][y].has_mine() == true)
        {
          if(fields[x][y].is_invisible() == true)
            return FIELD_MINE_YES;
          if(fields[x][y].is_visible() == true)
            return FIELD_EXPLOSION;
          if(fields[x][y].is_marked() == true)
            return FIELD_MARKED;
        }
        else
        {
          if(fields[x][y].is_invisible() == true)
            return FIELD_UNACTED;
          if(fields[x][y].is_visible() == true)
            return fields[x][y].get_content();
          if(fields[x][y].is_marked() == true)
            return FIELD_MINE_NO;
        }
    return FIELD_UNACTED;
  }
}
