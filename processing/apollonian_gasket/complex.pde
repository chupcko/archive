static class complex
{
  public double real;
  public double imaginary;

  public complex()
  {
    real = 0.0d;
    imaginary = 0.0d;
  }

  public complex(double _real, double _imaginary)
  {
    real = _real;
    imaginary = _imaginary;
  }

  public complex(complex x)
  {
    real = x.real;
    imaginary = x.imaginary;
  }

  public void set(double _real, double _imaginary)
  {
    real = _real;
    imaginary = _imaginary;
  }

  public void set(complex x)
  {
    real = x.real;
    imaginary = x.imaginary;
  }

  public void neg()
  {
    real = -real;
    imaginary = -imaginary;
  }

  public void conj()
  {
    imaginary = -imaginary;
  }

  public double abs()
  {
    return Math.sqrt(real*real+imaginary*imaginary);
  }

  public double arg()
  {
    return Math.atan2(imaginary, real);
  }

  public void add(complex x)
  {
    real += x.real;
    imaginary += x.imaginary;
  }

  public void sub(complex x)
  {
    real -= x.real;
    imaginary -= x.imaginary;
  }

  public void mul(double x)
  {
    real *= x;
    imaginary *= x;
  }

  public void mul(complex x)
  {
    double _real = real*x.real-imaginary*x.imaginary;
    double _imaginary = imaginary*x.real+real*x.imaginary;
    real = _real;
    imaginary = _imaginary;
  }

  public void div(double x)
  {
    real /= x;
    imaginary /= x;
  }

  public void div(complex x)
  {
    double t = x.real*x.real+x.imaginary*x.imaginary;
    double _real = (real*x.real+imaginary*x.imaginary)/t;
    double _imaginary = (imaginary*x.real-real*x.imaginary)/t;
    real = _real;
    imaginary = _imaginary;
  }

  public void sqrt()
  {
    double _real = Math.sqrt(abs())*Math.cos(arg()/2.0d);
    double _imaginary = Math.sqrt(abs())*Math.sin(arg()/2.0d);
    real = _real;
    imaginary = _imaginary;
  }

  public void sqrt_alternative()
  {
    double _real = Math.sqrt((abs()+real)/2.0d);
    double _imaginary = Math.sqrt((abs()-real)/2.0d);
    if(imaginary < 0.0d)
      _imaginary = -_imaginary;

    real = _real;
    imaginary = _imaginary;
  }

  public String toString()
  {
    return "["+real+", "+imaginary+"]";
  }

  public static double distance(complex a, complex b)
  {
    complex x = new complex(a);
    x.sub(b);
    return x.abs();
  }
}
