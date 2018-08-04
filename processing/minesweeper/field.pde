class field_c
{
  private static final int CONTENT_MINE  = -1;
  private static final int CONTENT_EMPTY = 0;
  private static final int CONTENT_MIN   = 1;
  private static final int CONTENT_MAX   = 8;

  private static final int STATE_INVISIBLE = 0;
  private static final int STATE_VISIBLE   = 1;
  private static final int STATE_MARKED    = 2;

  private int content;
  private int state;

  public void init()
  {
    content = 0;
    state = STATE_INVISIBLE;
  }

  public void set_content(int _content)
  {
    if(_content >= CONTENT_MINE && _content <= CONTENT_MAX)
      content = _content;
  }

  public void set_mine()
  {
    content = CONTENT_MINE;
  }

  public int get_content()
  {
    return content;
  }

  public boolean is_empty()
  {
    if(content == CONTENT_EMPTY)
      return true;
    return false;
  }

  public boolean has_mine()
  {
    if(content == CONTENT_MINE)
      return true;
    return false;
  }

  public void invisible()
  {
    state = STATE_INVISIBLE;
  }

  public void visible()
  {
    state = STATE_VISIBLE;
  }

  public void mark()
  {
    state = STATE_MARKED;
  }

  public boolean is_invisible()
  {
    if(state == STATE_INVISIBLE)
      return true;
    return false;
  }

  public boolean is_visible()
  {
    if(state == STATE_VISIBLE)
      return true;
    return false;
  }

  public boolean is_marked()
  {
    if(state == STATE_MARKED)
      return true;
    return false;
  }
}
