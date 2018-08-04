class landscape_c
{
  private final float BORDER_LEFT = 10.0;
  private final float BORDER_RIGHT = 10.0;
  private final float BORDER_UP = 10.0;
  private final float BORDER_DOWN = 100.0;
  private final float RATIO_INIT = 20.0;
  private final float RATIO_MIN = 8.0;
  private final float RATIO_MAX = 32.0;

  private int steps;
  private int width;
  private int height;
  private float ratio;
  private boolean fill_triangle;
  private point_c[] points;
  private int point_number;
  private line_c[] lines;
  private int line_number;
  private int[] end_lines_index;
  private triangle_c[] triangles;
  private int triangle_number;
  private int[] end_triangles_index;

  public landscape_c(int _steps, int _width, int _height)
  {
    int i;

    steps = _steps;
    width = _width;
    height = _height;
    ratio = RATIO_INIT;
    fill_triangle = false;
    calculate_c calculate = new calculate_c(steps);
    points = new point_c[calculate.points()];
    for(i = 0; i < calculate.points(); i++)
      points[i] = new point_c();
    lines = new line_c[calculate.lines()];
    for(i = 0; i < calculate.lines(); i++)
      lines[i] = new line_c();
    end_lines_index = new int[steps];
    triangles = new triangle_c[calculate.triangles()];
    for(i = 0; i < calculate.triangles(); i++)
      triangles[i] = new triangle_c();
    end_triangles_index = new int[steps+1];
    calculate();
  }

  public void calculate()
  {
    int i;

    points[0].x = BORDER_LEFT;
    points[0].y = (float)height-BORDER_DOWN;
    points[1].x = (float)width-BORDER_RIGHT;
    points[1].y = (float)height-BORDER_DOWN;
    points[2].x = (float)width/2.0;
    points[2].y = BORDER_UP;
    point_number = 3;
    lines[0].begin_point_index = 0;
    lines[0].end_point_index = 1;
    lines[1].begin_point_index = 1;
    lines[1].end_point_index = 2;
    lines[2].begin_point_index = 2;
    lines[2].end_point_index = 0;
    line_number = 3;
    end_lines_index[0] = 0;
    triangles[0].orientation = true;
    triangles[0].line_0_index = 0;
    triangles[0].line_1_index = 1;
    triangles[0].line_2_index = 2;
    triangle_number = 1;
    end_triangles_index[0] = 0;
    for(i = 1; i < steps; i++)
    {
      end_lines_index[i] = line_number;
      end_triangles_index[i] = triangle_number;
      make_new_lines(i);
      make_new_triangles(i);
    }
    end_triangles_index[steps] = triangle_number;
  }

  private void make_new_lines(int step)
  {
    int i;

    for(i = end_lines_index[step-1]; i < end_lines_index[step]; i++)
    {
      int middle_point_index;

      middle_point_index = make_middle_point(lines[i].begin_point_index, lines[i].end_point_index);
      lines[i].new_line_index = line_number;
      lines[line_number].begin_point_index = lines[i].begin_point_index;
      lines[line_number].end_point_index = middle_point_index;
      line_number++;
      lines[line_number].begin_point_index = middle_point_index;
      lines[line_number].end_point_index = lines[i].end_point_index;
      line_number++;
    }
  }

  private int make_middle_point(int begin_point_index, int end_point_index)
  {
    float offset;
    int new_point_index;

    offset = sqrt(sq(points[end_point_index].x-points[begin_point_index].x)+sq(points[end_point_index].y-points[begin_point_index].y))/ratio;
    new_point_index = point_number;
    points[point_number].x = (points[begin_point_index].x+points[end_point_index].x)/2.0+random(-offset, offset);
    points[point_number].y = (points[begin_point_index].y+points[end_point_index].y)/2.0+random(-offset, offset);
    point_number++;
    return new_point_index;
  }

  private void make_new_triangles(int step)
  {
    int i;

    for(i = end_triangles_index[step-1]; i < end_triangles_index[step]; i++)
      if(triangles[i].orientation == true)
        make_new_four_triangles_positive(i);
      else
        make_new_four_triangles_negative(i);
  }

  private void make_new_four_triangles_positive(int index)
  {
    int middle_point_0_index;
    int middle_point_1_index;
    int middle_point_2_index;
    int line_0_2_index;
    int line_2_1_index;
    int line_1_0_index;

    middle_point_0_index = lines[lines[triangles[index].line_0_index].new_line_index].end_point_index;
    middle_point_1_index = lines[lines[triangles[index].line_1_index].new_line_index].end_point_index;
    middle_point_2_index = lines[lines[triangles[index].line_2_index].new_line_index].end_point_index;
    line_0_2_index = line_number;
    lines[line_number].begin_point_index = middle_point_0_index;
    lines[line_number].end_point_index = middle_point_2_index;
    line_number++;
    line_2_1_index = line_number;
    lines[line_number].begin_point_index = middle_point_2_index;
    lines[line_number].end_point_index = middle_point_1_index;
    line_number++;
    line_1_0_index = line_number;
    lines[line_number].begin_point_index = middle_point_1_index;
    lines[line_number].end_point_index = middle_point_0_index;
    line_number++;
    triangles[triangle_number].orientation = true;
    triangles[triangle_number].line_0_index = lines[triangles[index].line_0_index].new_line_index;
    triangles[triangle_number].line_1_index = line_0_2_index;
    triangles[triangle_number].line_2_index = lines[triangles[index].line_2_index].new_line_index+1;
    triangle_number++;
    triangles[triangle_number].orientation = true;
    triangles[triangle_number].line_0_index = lines[triangles[index].line_0_index].new_line_index+1;
    triangles[triangle_number].line_1_index = lines[triangles[index].line_1_index].new_line_index;
    triangles[triangle_number].line_2_index = line_1_0_index;
    triangle_number++;
    triangles[triangle_number].orientation = true;
    triangles[triangle_number].line_0_index = line_2_1_index;
    triangles[triangle_number].line_1_index = lines[triangles[index].line_1_index].new_line_index+1;
    triangles[triangle_number].line_2_index = lines[triangles[index].line_2_index].new_line_index;
    triangle_number++;
    triangles[triangle_number].orientation = false;
    triangles[triangle_number].line_0_index = line_2_1_index;
    triangles[triangle_number].line_1_index = line_0_2_index;
    triangles[triangle_number].line_2_index = line_1_0_index;
    triangle_number++;
  }

  private void make_new_four_triangles_negative(int index)
  {
    int middle_point_0_index;
    int middle_point_1_index;
    int middle_point_2_index;
    int line_0_1_index;
    int line_1_2_index;
    int line_2_0_index;

    middle_point_0_index = lines[lines[triangles[index].line_0_index].new_line_index].end_point_index;
    middle_point_1_index = lines[lines[triangles[index].line_1_index].new_line_index].end_point_index;
    middle_point_2_index = lines[lines[triangles[index].line_2_index].new_line_index].end_point_index;
    line_0_1_index = line_number;
    lines[line_number].begin_point_index = middle_point_0_index;
    lines[line_number].end_point_index = middle_point_1_index;
    line_number++;
    line_1_2_index = line_number;
    lines[line_number].begin_point_index = middle_point_1_index;
    lines[line_number].end_point_index = middle_point_2_index;
    line_number++;
    line_2_0_index = line_number;
    lines[line_number].begin_point_index = middle_point_2_index;
    lines[line_number].end_point_index = middle_point_0_index;
    line_number++;
    triangles[triangle_number].orientation = false;
    triangles[triangle_number].line_0_index = lines[triangles[index].line_0_index].new_line_index+1;
    triangles[triangle_number].line_1_index = line_2_0_index;
    triangles[triangle_number].line_2_index = lines[triangles[index].line_2_index].new_line_index;
    triangle_number++;
    triangles[triangle_number].orientation = false;
    triangles[triangle_number].line_0_index = lines[triangles[index].line_0_index].new_line_index;
    triangles[triangle_number].line_1_index = lines[triangles[index].line_1_index].new_line_index+1;
    triangles[triangle_number].line_2_index = line_0_1_index;
    triangle_number++;
    triangles[triangle_number].orientation = false;
    triangles[triangle_number].line_0_index = line_1_2_index;
    triangles[triangle_number].line_1_index = lines[triangles[index].line_1_index].new_line_index;
    triangles[triangle_number].line_2_index = lines[triangles[index].line_2_index].new_line_index+1;
    triangle_number++;
    triangles[triangle_number].orientation = true;
    triangles[triangle_number].line_0_index = line_1_2_index;
    triangles[triangle_number].line_1_index = line_2_0_index;
    triangles[triangle_number].line_2_index = line_0_1_index;
    triangle_number++;
  }

  public void ratio_down()
  {
    ratio -= 1.0;
    if(ratio < RATIO_MIN)
      ratio = RATIO_MIN;
    else
      calculate();
  }

  public void ratio_init()
  {
    if(ratio != RATIO_INIT)
    {
      ratio = RATIO_INIT;
      calculate();
    }
  }

  public void ratio_up()
  {
    ratio += 1.0;
    if(ratio < RATIO_MAX)
      ratio = RATIO_MAX;
    else
      calculate();
  }

  public void toggle_fill()
  {
    if(fill_triangle == true)
      fill_triangle = false;
    else
      fill_triangle = true;
  }

  public void draw(int level)
  {
    int i;

    background(255);
    for(i = end_triangles_index[level]; i < end_triangles_index[level+1]; i++)
    {
      if(fill_triangle == true)
        if(triangles[i].orientation == true)
          fill(255, 0, 0);
        else
          fill(0, 0, 255);
      else
        noFill();
      beginShape();
      vertex
      (
        points[lines[triangles[i].line_0_index].begin_point_index].x,
        points[lines[triangles[i].line_0_index].begin_point_index].y
      );
      vertex
      (
        points[lines[triangles[i].line_1_index].begin_point_index].x,
        points[lines[triangles[i].line_1_index].begin_point_index].y
      );
      vertex
      (
        points[lines[triangles[i].line_2_index].begin_point_index].x,
        points[lines[triangles[i].line_2_index].begin_point_index].y
      );
      endShape(CLOSE);
    }
  }
}
