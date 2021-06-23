class Point {

  constructor(x, y) {
    if(x instanceof Point) {
      this.x = x.x;
      this.y = x.y;
      return;
    }
    if(x === undefined) {
      x = 0;
    }
    if(y === undefined) {
      y = x;
    }
    this.x = x;
    this.y = y;
  }

  set(x, y) {
    if(x instanceof Point) {
      this.x = x.x;
      this.y = x.y;
      return;
    }
    this.x = x;
    this.y = y;
  }

  eq(x, y) {
    if(x instanceof Point) {
      return (
        this.x == x.x &&
        this.y == x.y
      );
    }
    return (
      this.x == x &&
      this.y == y
    );
  }

  neg() {
    this.x = -this.x;
    this.y = -this.y;
  }

  add(x, y) {
    if(x instanceof Point) {
      this.x += x.x;
      this.y += x.y;
      return;
    }
    this.x += x;
    this.y += y;
  }

  sub(x, y) {
    if(x instanceof Point) {
      this.x -= x.x;
      this.y -= x.y;
      return;
    }
    this.x -= x;
    this.y -= y;
  }

  smul(x, y) {
    if(x instanceof Point) {
      this.x *= x.x;
      this.y *= x.y;
      return;
    }
    if(y === undefined) {
      y = x;
    }
    this.x *= x;
    this.y *= y;
  }

  sdiv(x, y) {
    if(x instanceof Point) {
      this.x /= x.x;
      this.y /= x.y;
      return;
    }
    if(y === undefined) {
      y = x;
    }
    this.x /= x;
    this.y /= y;
  }

}

export default Point;
