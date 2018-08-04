class automat_c
{
  private int size_x;
  private int size_y;
  private int mines_count;
  private game_c game;

  public automat_c(int _size_x, int _size_y, int _mines_count, game_c _game)
  {
    size_x = _size_x;
    size_y = _size_y;
    mines_count = _mines_count;
    game = _game;
  }

  public boolean play()
  {
    if(game.is_ended() != true)
    {
      int x;
      int y;
      int content;

      for(x = 0; x < size_x; x++)
        for(y = 0; y < size_y; y++)
        {
          content = game.get_field(x, y);
          if
          (
            content != game_c.FIELD_UNACTED &&
            content != game_c.FIELD_MARKED &&
            count_arround(x, y, game_c.FIELD_UNACTED) > 0 &&
            count_arround(x, y, game_c.FIELD_MARKED) == content
          )
            return play_on_some_unacted_arround(x, y);
        }
    }
    return false;
  }

  public boolean mark()
  {
    if(game.is_ended() != true)
    {
      int x;
      int y;
      int content;
      int count_unacted;

      for(x = 0; x < size_x; x++)
        for(y = 0; y < size_y; y++)
        {
          content = game.get_field(x, y);
          if
          (
            content != game_c.FIELD_UNACTED &&
            content != game_c.FIELD_MARKED
          )
          {
            count_unacted = count_arround(x, y, game_c.FIELD_UNACTED);
            if
            (
              count_unacted > 0 &&
              count_unacted == content-count_arround(x, y, game_c.FIELD_MARKED)
            )
              return mark_on_some_unacted_arround(x, y);
          }
        }
    }
    return false;
  }

  private int count_arround(int x, int y, int content)
  {
    return
      count_arround_on(x-1, y-1, content)+
      count_arround_on(x-1, y,   content)+
      count_arround_on(x-1, y+1, content)+
      count_arround_on(x,   y-1, content)+
      count_arround_on(x,   y+1, content)+
      count_arround_on(x+1, y-1, content)+
      count_arround_on(x+1, y,   content)+
      count_arround_on(x+1, y+1, content);
  }

  private int count_arround_on(int x, int y, int content)
  {
    if
    (
      x >= 0 && x < size_x &&
      y >= 0 && y < size_y &&
      game.get_field(x, y) == content
    )
      return 1;
    return 0;
  }

  private boolean play_on_some_unacted_arround(int x, int y)
  {
    if
    (
      play_on_some_unacted_on(x-1, y-1) == true ||
      play_on_some_unacted_on(x-1, y  ) == true ||
      play_on_some_unacted_on(x-1, y+1) == true ||
      play_on_some_unacted_on(x,   y-1) == true ||
      play_on_some_unacted_on(x,   y+1) == true ||
      play_on_some_unacted_on(x+1, y-1) == true ||
      play_on_some_unacted_on(x+1, y  ) == true ||
      play_on_some_unacted_on(x+1, y+1) == true
    )
      return true;
    return false;
  }

  private boolean play_on_some_unacted_on(int x, int y)
  {
    if
    (
      x >= 0 && x < size_x &&
      y >= 0 && y < size_y &&
      game.get_field(x, y) == game_c.FIELD_UNACTED
    )
    {
      game.play(x, y);
      return true;
    }
    return false;
  }

  private boolean mark_on_some_unacted_arround(int x, int y)
  {
    if
    (
      mark_on_some_unacted_on(x-1, y-1) == true ||
      mark_on_some_unacted_on(x-1, y  ) == true ||
      mark_on_some_unacted_on(x-1, y+1) == true ||
      mark_on_some_unacted_on(x,   y-1) == true ||
      mark_on_some_unacted_on(x,   y+1) == true ||
      mark_on_some_unacted_on(x+1, y-1) == true ||
      mark_on_some_unacted_on(x+1, y  ) == true ||
      mark_on_some_unacted_on(x+1, y+1) == true
    )
      return true;
    return false;
  }

  private boolean mark_on_some_unacted_on(int x, int y)
  {
    if
    (
      x >= 0 && x < size_x &&
      y >= 0 && y < size_y &&
      game.get_field(x, y) == game_c.FIELD_UNACTED
    )
    {
      game.mark(x, y);
      return true;
    }
    return false;
  }
}
