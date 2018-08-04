class a
{
  public    int a_public;
  protected int a_protected;
            int a_;
  private   int a_private;

  public    static int a_static_public;
  protected static int a_static_protected;
            static int a_static_;
  private   static int a_static_private;

  static class b
  {
    int b_ =
//    a_public+
//    a_protected+
//    a_+
//    a_private+
      a_static_public+
      a_static_protected+
      a_static_+
      a_static_private+
      0;
  }
}
