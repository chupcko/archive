import Point from './point.js';
import Box from './box.js';

class Mandelbrot extends Box {

  line_1 = new Point();
  line_2 = new Point();
  line_delta = new Point();
  timer = undefined;

  constructor(name, julia) {
    super(name);
    this.julia = julia;
    this.init();
  }

  draw() {
    for(let x = 0; x < Box.SIZE; x++) {
      for(let y = 0; y < Box.SIZE; y++) {
        let p = this.real_from_point(x, y);
        let z = new Point(p);
        let zz = new Point();
        let n;
        for(n = 0; n < this.count; n++) {
          zz.x = z.x*z.x;
          zz.y = z.y*z.y;
          if(zz.x+zz.y > Box.RADIUS) {
            break;
          }
          z.y = 2*z.x*z.y+p.y;
          z.x = zz.x-zz.y+p.x;
        }
        if(n == this.count) {
          this.box_context.fillStyle = 'rgb(0, 0, 0)';
        }
        else {
          if(this.trace) {
            let g = (255-n*255/this.count)|0;
            this.box_context.fillStyle = `rgb(${ g }, ${ g }, 255)`;
          } else {
            this.box_context.fillStyle = 'rgb(255, 255, 255)';
          }
        }
        this.box_context.fillRect(x, y, 1, 1);
      }
    }
    this.draw_julia_dot();
  }

  draw_julia_dot() {
    this.control_context.clearRect(0, 0, Box.SIZE, Box.SIZE);
    let p = this.point_from_real(this.julia.c);
    this.control_context.fillStyle = 'rgb(255, 0, 255)';
    this.control_context.fillRect(p.x, p.y, 3, 3);
  }

  click_do(p, shift, ctrl) {
    this.stop_timer();
    this.julia.c.set(this.real_from_point(p));
    this.draw_julia_dot();
    this.julia.draw();
  }

  line_do(p1, p2, shift, ctrl) {
    this.stop_timer();

    let m = new Point(p2);
    m.sub(p1);
    this.line_n = Math.max(Math.abs(m.x), Math.abs(m.y))|0
    this.line_i = 0;
    this.line_d = 1;

    this.line_1.set(this.real_from_point(p1));
    this.line_2.set(this.real_from_point(p2));

    this.line_delta.set(this.line_2);
    this.line_delta.sub(this.line_1);
    this.line_delta.sdiv(this.line_n-1);

    this.start_timer();
  }

  zoom_do(p, z, shift, ctrl) {
  }

  line_next_i() {
    this.line_i += this.line_d;
    if(this.line_i >= this.line_n) {
      this.line_d = -1;
      this.line_i = this.line_n-2;
    } else if(this.line_i < 0) {
      this.line_d = 1;
      this.line_i = 1;
    }
  }

  stop_timer() {
    if(this.timer !== undefined) {
      clearTimeout(this.timer);
      this.timer = undefined;
    }
  }

  start_timer() {
    this.timer = setInterval(
      () => {
        this.julia.c.set(this.line_delta);
        this.julia.c.smul(this.line_i);
        this.julia.c.add(this.line_1);
        this.draw_julia_dot();
        this.julia.draw();
        this.line_next_i();
      },
      100
    )
  }

}

export default Mandelbrot;
