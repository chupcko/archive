export enum WorldDirection { UP, LEFT, DOWN, RIGHT };

export interface WorldAnt {
  x : number;
  y : number;
  d : WorldDirection;
}

export class World {

  public fields : any;
  public ant : WorldAnt;
  public in : boolean;
  public count : number;

  public constructor(
    public width : number = 10,
    public height : number = 10
  ) {
    this.reset();
  }

  public reset() : void {
    this.fields = [];
    for(let x = 0; x < this.width; x++) {
      this.fields[x] = [];
      for(let y = 0; y < this.height; y++) {
        this.fields[x][y] = { visited: false, number: 0 }
      }
    }
    this.ant = { x: Math.floor(this.width/2), y: Math.floor(this.height/2), d: WorldDirection.UP };
    this.fields[this.ant.x][this.ant.y].visited = true;
    this.in = true;
    this.count = 0;
  }

  public step() : boolean {
    if(this.in) {
      if(this.fields[this.ant.x][this.ant.y].number%2 == 0){
        this.turnRight();
      } else {
        this.turnLeft();
      }
      this.fields[this.ant.x][this.ant.y].number++;
      this.move();
      this.count++;
    }
    return this.in;
  }

  private turnLeft() : void {
    this.ant.d = (this.ant.d+1)%4;
  }

  private turnRight() : void {
    this.ant.d = (this.ant.d+3)%4;
  }

  private move() : void {
    switch(this.ant.d) {
      case WorldDirection.UP:
        if(this.ant.y > 0) {
          this.ant.y--;
        } else {
          this.in = false;
        }
        break;
      case WorldDirection.LEFT:
        if(this.ant.x > 0) {
          this.ant.x--;
        } else {
          this.in = false;
        }
        break;
      case WorldDirection.DOWN:
        if(this.ant.y < this.height-1) {
          this.ant.y++;
        } else {
          this.in = false;
        }
        break;
      case WorldDirection.RIGHT:
        if(this.ant.x < this.width-1) {
          this.ant.x++;
        } else {
          this.in = false;
        }
        break;
    }
    this.fields[this.ant.x][this.ant.y].visited = true;
  }

}
