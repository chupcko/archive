import Point from './point.js';
import Box from './box.js';

class Julia extends Box {

  c = new Point();

  constructor(name) {
    super(name);
    this.init();
  }

  draw() {
    for(let x = 0; x < Box.SIZE; x++) {
      for(let y = 0; y < Box.SIZE; y++) {
        let z = this.real_from_point(x, y);
        let zz = new Point();
        let n;
        for(n = 0; n < this.count; n++) {
          zz.x = z.x*z.x;
          zz.y = z.y*z.y;
          if(zz.x+zz.y > Box.RADIUS) {
            break;
          }
          z.y = 2*z.x*z.y+this.c.y;
          z.x = zz.x-zz.y+this.c.x;
        }
        if(n == this.count) {
          this.box_context.fillStyle = 'rgb(0, 0, 0)';
        }
        else {
          if(this.trace) {
            let g = (255-n*255/this.count)|0;
            this.box_context.fillStyle = `rgb(255, ${ g }, ${ g })`;
          } else {
            this.box_context.fillStyle = 'rgb(255, 255, 255)';
          }
        }
        this.box_context.fillRect(x, y, 1, 1);
      }
    }
  }

}

export default Julia;
