function SquareClass(name, maxX, maxY, canvasName)
{
  this.name = name;
  this.maxX = maxX;
  this.maxY = maxY;
  this.canvasName = canvasName;

  this.backGroundColor = 'rgb(0%, 0%, 0%)';
  this.lineColor = 'rgb(50%, 50%, 50%)';
  this.cellLineColor = 'rgb(10%, 10%, 10%)';
  this.centerCellLineColor = 'rgb(50%, 10%, 10%)';
  this.markerColor = 'rgb(100%, 100%, 100%)';

  this.lineWidth = 1;
  this.doDrawLines = false;
  this.speed = 20;
  this.speedAddForLines = 40;

  this.centerX = Math.floor(this.maxX/2);
  this.centerY = Math.floor(this.maxY/2);

  this.drawLines = function()
  {
    for(var x = 0; x < this.maxX-1; x++)
      for(var y = 0; y < this.maxY; y++)
      {
        this.canvasContext.beginPath();
        this.canvasContext.lineWidth = this.lineWidth;
        this.canvasContext.strokeStyle = this.lineColor;
        this.canvasContext.moveTo(this.cells[x][y].markerX()+0.5, this.cells[x][y].markerY()+0.5);
        this.canvasContext.lineTo(this.cells[x+1][y].markerX()+0.5, this.cells[x+1][y].markerY()+0.5);
        this.canvasContext.stroke();
      }
    for(var x = 0; x < this.maxX; x++)
      for(var y = 0; y < this.maxY-1; y++)
      {
        this.canvasContext.beginPath();
        this.canvasContext.lineWidth = this.lineWidth;
        this.canvasContext.strokeStyle = this.lineColor;
        this.canvasContext.moveTo(this.cells[x][y].markerX()+0.5, this.cells[x][y].markerY()+0.5);
        this.canvasContext.lineTo(this.cells[x][y+1].markerX()+0.5, this.cells[x][y+1].markerY()+0.5);
        this.canvasContext.stroke();
      }
  };

  this.draw = function()
  {
    this.canvasContext.setTransform(1, 0, 0, -1, 0, this.canvas.height);
    this.canvasContext.fillStyle = this.backGroundColor;
    this.canvasContext.fillRect(0, 0, this.canvas.width, this.canvas.height);
    for(var x = 0; x < this.maxX; x++)
      for(var y = 0; y < this.maxY; y++)
        this.cells[x][y].drawCell();
    if(this.doDrawLines)
      this.drawLines();
    for(var x = 0; x < this.maxX; x++)
      for(var y = 0; y < this.maxY; y++)
        this.cells[x][y].drawMarker();
  };

  this.linesOn = function()
  {
    this.doDrawLines = true;
    this.speed += this.speedAddForLines;
    if(this.job != undefined)
    {
      this.stop();
      this.start();
    }
  };

  this.linesOff = function()
  {
    this.doDrawLines = false;
    this.speed -= this.speedAddForLines;
    if(this.speed < 1)
      this.speed = 1;
    if(this.job != undefined)
    {
      this.stop();
      this.start();
    }
  };

  this.linesToggle = function()
  {
    if(this.doDrawLines)
      this.linesOff();
    else
      this.linesOn();
    this.draw();
  };

  this.next = function()
  {
    for(var x = 0; x < this.maxX; x++)
      for(var y = 0; y < this.maxY; y++)
        this.cells[x][y].next();
  };

  this.job = undefined;

  this.start = function()
  {
    if(this.job == undefined)
      this.job = setInterval
      (
        (
          function(that)
          {
            return function()
            {
              that.next();
              that.draw();
            };
          }
        )(this),
        this.speed
      );
  };

  this.stop = function()
  {
    if(this.job != undefined)
    {
      clearInterval(this.job);
      this.job = undefined;
    }
  };

  this.run = function()
  {
    if(this.job == undefined)
      this.start();
    else
      this.stop();
  };

  this.speedUp = function()
  {
    this.speed--;
    if(this.speed < 1)
      this.speed = 1;
  };

  this.speedDown = function()
  {
    this.speed++;
  };

  this.exampleCell = new CellClass(undefined, 0, 0, 0);
  this.canvas = document.getElementById(this.canvasName);
  this.canvasContext = this.canvas.getContext('2d');
  this.canvas.width = this.maxX*this.exampleCell.size;
  this.canvas.height = this.maxY*this.exampleCell.size;

  this.set = function(expression, step)
  {
    for(var xi = 0; xi < this.maxX; xi++)
      for(var yi = 0; yi < this.maxY; yi++)
      {
        var x = xi-this.centerX;
        var y = yi-this.centerY;
        var N = this.exampleCell.maxPosition;
        var maxX = this.maxX;
        var maxY = this.maxY;
        this.cells[xi][yi].set
        (
          Math.floor(eval(expression)),
          Math.floor(eval(step))
        );
      }
    this.draw();
  };

  this.cells = new Array();
  for(var x = 0; x < this.maxX; x++)
  {
    this.cells[x] = new Array();
    for(var y = 0; y < this.maxY; y++)
    {
      this.cells[x][y] = new CellClass
      (
        this.canvasContext,
        x,
        y
      );
      this.cells[x][y].setColors(this.cellLineColor, this.markerColor);
    }
  }
  this.cells[this.centerX][this.centerY].setColors(this.centerCellLineColor, this.markerColor);

  this.draw();
  window[this.name] = this;
}
