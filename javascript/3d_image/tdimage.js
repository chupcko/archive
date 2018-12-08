class TDImageClass {

  constructor(id, width, height) {
    this.shift = 100;
    this.zoom = -8;

    this.id = id;
    this.width = width;
    this.height = height;
    this.canvas = document.getElementById(this.id);
    this.canvasContext = this.canvas.getContext('2d');
    this.canvas.width = this.width;
    this.canvas.height = this.height;
  }

  random(n) {
    return (Math.random()*n)|0;
  }

  setColor(r, g, b) {
    this.canvasContext.fillStyle = `rgb(${r}, ${g}, ${b})`;
  }

  point(x, y) {
    this.canvasContext.fillRect(x, y, 1, 1);
  }

  draw(f) {
    for(let  y = 0; y < this.height; y++) {
      let used = [];
      for(let x = 0; x < this.width; x++) {
        if(used[x] === undefined) {
          let t = x;
          this.setColor(this.random(256), this.random(256), this.random(256));
          while(t < this.width) {
            this.point(t, y);
            used[t] = true;
            t += this.shift+(f(t, y)/this.zoom)|0;
          }
        }
      }
    }
  }

}
