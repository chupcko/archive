class a
{
  public    int a_public;
  protected int a_protected;
            int a_;
  private   int a_private;

  void a_m()
  {
    int a_m_;
    b b_ = new b()
    {
      int b_m()
      {
        return
          a_public+
          a_protected+
          a_+
          a_private+
//        a_m_+
          0;
      }
    };
  }
}
