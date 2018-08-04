/* http://en.wikibooks.org/wiki/Fractals/Apollonian_fractals */

final int SIZE = 1000;
final float RANDOM_LIMIT = 0.25;
final double ERROR_GATE = 0.0000001;

final double OFFSET_SIZE = (double)SIZE/2.0d;
final double SCALE_SIZE = (double)SIZE/5.0d;
final double COLOR_SCALE = (double)SIZE/4.0d;

final color COLOR_BLACK = color(0,   0,   0);
final color COLOR_RED   = color(255, 0,   0);
final color COLOR_GREEN = color(0,   255, 0);
final color COLOR_BLUE  = color(0,   0,   255);
final color COLOR_WHITE = color(255, 255, 255);

void setup()
{
  size(SIZE, SIZE);
  smooth();
  noLoop();
}

circle soddy(circle circle_a, circle circle_b, circle circle_c, boolean out, boolean do_error, boolean negative)
{
  double k_a = 1.0d/circle_a.radius;
  double k_b = 1.0d/circle_b.radius;
  double k_c = 1.0d/circle_c.radius;
  double k_result;

  if(out == true)
    k_result = k_a+k_b+k_c-2.0d*Math.sqrt(k_a*k_b+k_b*k_c+k_c*k_a);
  else
    k_result = k_a+k_b+k_c+2.0d*Math.sqrt(k_a*k_b+k_b*k_c+k_c*k_a);

  complex z_a = new complex(circle_a.center);
  z_a.mul(k_a);
  complex z_b = new complex(circle_b.center);
  z_b.mul(k_b);
  complex z_c = new complex(circle_c.center);
  z_c.mul(k_c);

  complex z_ab = new complex(z_a);
  z_ab.mul(z_b);
  complex z_bc = new complex(z_b);
  z_bc.mul(z_c);
  complex z_ca = new complex(z_c);
  z_ca.mul(z_a);

  complex z_2_sqrt_ab_bc_ca = new complex(z_ab);
  z_2_sqrt_ab_bc_ca.add(z_bc);
  z_2_sqrt_ab_bc_ca.add(z_ca);
  z_2_sqrt_ab_bc_ca.sqrt();
  z_2_sqrt_ab_bc_ca.mul(2.0d);

  complex z_a_b_c = new complex(z_a);
  z_a_b_c.add(z_b);
  z_a_b_c.add(z_c);
  double radius_result = 1.0d/k_result;
  complex center_result;

  if(do_error == true)
  {
    center_result = new complex(z_a_b_c);
    center_result.add(z_2_sqrt_ab_bc_ca);
    center_result.div(k_result);
    double error;

    if(out == true)
      error =
        Math.abs(complex.distance(center_result, circle_a.center)-Math.abs(radius_result)+Math.abs(circle_a.radius))+
        Math.abs(complex.distance(center_result, circle_b.center)-Math.abs(radius_result)+Math.abs(circle_b.radius))+
        Math.abs(complex.distance(center_result, circle_c.center)-Math.abs(radius_result)+Math.abs(circle_c.radius));
    else
    {
      if(circle_a.radius < 0.0d)
        error = Math.abs(complex.distance(center_result, circle_a.center)+Math.abs(radius_result)-Math.abs(circle_a.radius));
      else
        error = Math.abs(complex.distance(center_result, circle_a.center)-Math.abs(radius_result)-Math.abs(circle_a.radius));
      if(circle_b.radius < 0.0d)
        error += Math.abs(complex.distance(center_result, circle_b.center)+Math.abs(radius_result)-Math.abs(circle_b.radius));
      else
        error += Math.abs(complex.distance(center_result, circle_b.center)-Math.abs(radius_result)-Math.abs(circle_b.radius));
      if(circle_c.radius < 0.0d)
        error += Math.abs(complex.distance(center_result, circle_c.center)+Math.abs(radius_result)-Math.abs(circle_c.radius));
      else
        error += Math.abs(complex.distance(center_result, circle_c.center)-Math.abs(radius_result)-Math.abs(circle_c.radius));
    }
    if(error > ERROR_GATE)
    {
      center_result.set(z_a_b_c);
      center_result.sub(z_2_sqrt_ab_bc_ca);
      center_result.div(k_result);
    }
  }
  else
    if(negative == true)
    {
      center_result = new complex(z_a_b_c);
      center_result.sub(z_2_sqrt_ab_bc_ca);
      center_result.div(k_result);
    }
    else
    {
      center_result = new complex(z_a_b_c);
      center_result.add(z_2_sqrt_ab_bc_ca);
      center_result.div(k_result);
    }

  return new circle(center_result, radius_result);
}

void helper(circle circle_a, circle circle_b, circle circle_c)
{
  circle circle_in = soddy(circle_a, circle_b, circle_c, false, true, false);

  if(Math.abs(circle_in.radius) < 1.0d/SCALE_SIZE)
    return;

  circle_in.draw(true);
  helper(circle_in, circle_b, circle_c);
  helper(circle_a, circle_in, circle_c);
  helper(circle_a, circle_b, circle_in);
}

void draw()
{
  background(COLOR_WHITE);

  complex corner_a = new complex(0.0d, -1.0d);
  complex corner_b = new complex(Math.cos(30.0d*2.0d*Math.PI/360.0d), Math.sin(30.0d*2.0d*Math.PI/360)+0.1d);
  complex corner_c = new complex(-Math.cos(30.0d*2.0d*Math.PI/360.0d), Math.sin(30.0d*2.0d*Math.PI/360.0d));
  corner_a.real += (double)random(-RANDOM_LIMIT, RANDOM_LIMIT);
  corner_a.imaginary += (double)random(-RANDOM_LIMIT, RANDOM_LIMIT);
  corner_b.real += (double)random(-RANDOM_LIMIT, RANDOM_LIMIT);
  corner_b.imaginary += (double)random(-RANDOM_LIMIT, RANDOM_LIMIT);
  corner_c.real += (double)random(-RANDOM_LIMIT, RANDOM_LIMIT);
  corner_c.imaginary += (double)random(-RANDOM_LIMIT, RANDOM_LIMIT);

  double length_a = complex.distance(corner_b, corner_c);
  double length_b = complex.distance(corner_c, corner_a);
  double length_c = complex.distance(corner_a, corner_b);

  double radius_a = (length_b+length_c-length_a)/2.0d;
  double radius_b = (length_c+length_a-length_b)/2.0d;
  double radius_c = (length_a+length_b-length_c)/2.0d;

  circle circle_a = new circle(corner_a, radius_a);
  circle circle_b = new circle(corner_b, radius_b);
  circle circle_c = new circle(corner_c, radius_c);

  if(circle_b.radius > circle_a.radius)
  {
    circle temporally = circle_a;
    circle_a = circle_b;
    circle_b = temporally;
  }
  if(circle_c.radius > circle_a.radius)
  {
    circle temporally = circle_a;
    circle_a = circle_c;
    circle_c = temporally;
  }
  if(circle_c.radius > circle_b.radius)
  {
    circle temporally = circle_b;
    circle_b = circle_c;
    circle_c = temporally;
  }

  circle circle_out = soddy(circle_a, circle_b, circle_c, true, true, false);
  circle_c = soddy(circle_a, circle_b, circle_out, false, true, false);
  circle circle_d = soddy(circle_a, circle_b, circle_out, true, false, false);
  circle circle_d_alternative = soddy(circle_a, circle_b, circle_out, true, false, true);

  if
  (
    Math.abs(complex.distance(circle_d.center, circle_a.center)-Math.abs(circle_d.radius)-Math.abs(circle_a.radius))+
    Math.abs(complex.distance(circle_d.center, circle_b.center)-Math.abs(circle_d.radius)-Math.abs(circle_b.radius))+
    Math.abs(complex.distance(circle_d.center, circle_out.center)+Math.abs(circle_d.radius)-Math.abs(circle_out.radius)) >
    Math.abs(complex.distance(circle_d_alternative.center, circle_a.center)-Math.abs(circle_d_alternative.radius)-Math.abs(circle_a.radius))+
    Math.abs(complex.distance(circle_d_alternative.center, circle_b.center)-Math.abs(circle_d_alternative.radius)-Math.abs(circle_b.radius))+
    Math.abs(complex.distance(circle_d_alternative.center, circle_out.center)+Math.abs(circle_d_alternative.radius)-Math.abs(circle_out.radius))
  )
    circle_d = circle_d_alternative;

  circle_a.draw(true);
  circle_b.draw(true);
  circle_c.draw(true);
  circle_d.draw(true);
  circle_out.draw(false);
  helper(circle_a, circle_b, circle_c);
  helper(circle_a, circle_b, circle_d);
  helper(circle_a, circle_c, circle_out);
  helper(circle_b, circle_c, circle_out);
  helper(circle_a, circle_d, circle_out);
  helper(circle_b, circle_d, circle_out);
}

void keyTyped()
{
  switch(key)
  {
    case ' ':
      redraw();
      break;
  }
}
