import { Component, OnInit, AfterViewInit, Input, ElementRef, ViewChild } from '@angular/core';

import { WorldDirection, WorldAnt, World } from './world';

const ColorWall = 'rgb(40%, 40%, 100%)';
const ColorNone = 'rgb(80%, 80%, 100%)';
const ColorAnt = 'rgb(20%, 20%, 100%)';
const ColorEvenTemplate = 'rgb(100%, {}%, {}%)';
const ColorOddTemplate = 'rgb({}%, 100%, {}%)';
const SizeWall = 1;
const SizeField = 7;
const SizeFieldHalf = Math.floor((SizeField+1)/2);
const SizePeriodic = SizeWall+SizeField;
const SizeAntHalfWidth = 2;
const SizeAntHalfHeight = 3;
const TimeInterval = 5;

@Component({
  selector: 'lant',
  template: `
<button (click)="step()">Step</button>
<button (click)="runStop()">Run/Stop</button>
<button (click)="reset()">Reset</button>
{{ world.count }}
<a href="https://en.wikipedia.org/wiki/Langton's_ant">Info</a>
<br/>
<canvas #canvasBackground style="position: absolute; z-index: 0;"></canvas>
<canvas #canvasFields style="position: absolute; z-index: 1;"></canvas>
<canvas #canvasAnt style="position: absolute; z-index: 2;"></canvas>
`,
  styles: []
})
export class LantComponent implements OnInit, AfterViewInit {

  @Input() private width : number = 100;
  @Input() private height : number = 100;

  @ViewChild('canvasBackground') private canvasBackground : ElementRef;
  @ViewChild('canvasFields') private canvasFields : ElementRef;
  @ViewChild('canvasAnt') private canvasAnt : ElementRef;

  private canvasBackgroundContext : CanvasRenderingContext2D;
  private canvasFieldsContext : CanvasRenderingContext2D;
  private canvasAntContext : CanvasRenderingContext2D;

  private canvasWidth : number;
  private canvasHeight : number;

  public world : World;

  private interval : any;

  public constructor(
  ) { }

  public ngOnInit() {
    this.world = new World(this.width, this.height);
  }

  public ngAfterViewInit() {
    const elementBackground : HTMLCanvasElement = this.canvasBackground.nativeElement;
    const elementFields : HTMLCanvasElement = this.canvasFields.nativeElement;
    const elementAnt : HTMLCanvasElement = this.canvasAnt.nativeElement;

    this.canvasWidth = this.width*SizePeriodic+SizeWall;
    this.canvasHeight = this.height*SizePeriodic+SizeWall;

    elementBackground.width = this.canvasWidth;
    elementBackground.height = this.canvasHeight;
    elementFields.width = this.canvasWidth;
    elementFields.height = this.canvasHeight;
    elementAnt.width = this.canvasWidth;
    elementAnt.height = this.canvasHeight;

    this.canvasBackgroundContext = elementBackground.getContext('2d');
    this.canvasFieldsContext = elementFields.getContext('2d');
    this.canvasAntContext = elementAnt.getContext('2d');

    this.drawBackground();
    this.drawFields();
    this.drawAnt();
  }

  private drawBackground() : void {
    this.canvasBackgroundContext.fillStyle = ColorWall;
    for(let x = 0; x <= this.width; x++) {
      this.canvasBackgroundContext.fillRect(x*SizePeriodic, 0, SizeWall, this.canvasHeight);
    }
    for(let y = 0; y <= this.height; y++) {
      this.canvasBackgroundContext.fillRect(0, y*SizePeriodic, this.canvasWidth, SizeWall);
    }
  }

  private drawFields() : void {
    for(let x = 0; x < this.width; x++) {
      for(let y = 0; y < this.height; y++) {
        this.drawField(x, y);
      }
    }
  }

  private drawField(x : number, y : number) {
    if(this.world.fields[x][y].visited) {
      let template : string;
      if(this.world.fields[x][y].number%2 == 0) {
        template = ColorEvenTemplate;
      } else {
        template = ColorOddTemplate;
      }
      this.canvasFieldsContext.fillStyle = template.replace(/{}/g, (90-(this.world.fields[x][y].number*2)%80).toString());
    } else {
      this.canvasFieldsContext.fillStyle = ColorNone;
    }
    this.canvasFieldsContext.fillRect(x*SizePeriodic+SizeWall, y*SizePeriodic+SizeWall, SizeField, SizeField);
  }

  private drawAnt() : void {
    this.canvasAntContext.clearRect(0, 0, this.canvasWidth, this.canvasHeight);
    let centerX = this.world.ant.x*SizePeriodic+SizeFieldHalf+0.5;
    let centerY = this.world.ant.y*SizePeriodic+SizeFieldHalf+0.5;
    this.canvasAntContext.beginPath();
    switch(this.world.ant.d) {
      case WorldDirection.UP:
        this.canvasAntContext.moveTo(centerX, centerY-SizeAntHalfHeight);
        this.canvasAntContext.lineTo(centerX-SizeAntHalfWidth, centerY+SizeAntHalfHeight);
        this.canvasAntContext.lineTo(centerX+SizeAntHalfWidth, centerY+SizeAntHalfHeight);
        break;
      case WorldDirection.LEFT:
        this.canvasAntContext.moveTo(centerX-SizeAntHalfHeight, centerY);
        this.canvasAntContext.lineTo(centerX+SizeAntHalfHeight, centerY-SizeAntHalfWidth);
        this.canvasAntContext.lineTo(centerX+SizeAntHalfHeight, centerY+SizeAntHalfWidth);
        break;
      case WorldDirection.DOWN:
        this.canvasAntContext.moveTo(centerX, centerY+SizeAntHalfHeight);
        this.canvasAntContext.lineTo(centerX+SizeAntHalfWidth, centerY-SizeAntHalfHeight);
        this.canvasAntContext.lineTo(centerX-SizeAntHalfWidth, centerY-SizeAntHalfHeight);
        break;
      case WorldDirection.RIGHT:
        this.canvasAntContext.moveTo(centerX+SizeAntHalfHeight, centerY);
        this.canvasAntContext.lineTo(centerX-SizeAntHalfHeight, centerY+SizeAntHalfWidth);
        this.canvasAntContext.lineTo(centerX-SizeAntHalfHeight, centerY-SizeAntHalfWidth);
        break;
    }
    this.canvasAntContext.closePath();
    this.canvasAntContext.fillStyle = ColorAnt;
    this.canvasAntContext.fill();
    this.canvasAntContext.strokeStyle = ColorAnt;
    this.canvasAntContext.lineWidth = 1;
    this.canvasAntContext.lineJoin = 'bevel';
    this.canvasAntContext.stroke();
  }

  public step() : void {
    let ant = this.world.ant;
    this.world.step();
    this.drawField(ant.x, ant.y);
    this.drawField(this.world.ant.x, this.world.ant.y);
    this.drawAnt();
  }

  private stop() : void {
    clearInterval(this.interval);
    this.interval = undefined;
  }

  public runStop() : void {
    if(this.interval) {
      this.stop();
    } else {
      this.interval = setInterval(
        () => this.step(),
        TimeInterval
      );
    }
  }

  public reset() : void {
    this.stop();
    this.world.reset();
    this.drawFields();
    this.drawAnt();
  }

}
