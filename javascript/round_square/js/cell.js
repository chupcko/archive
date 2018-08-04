function CellClass(canvasContext, offsetX, offsetY)
{
  this.canvasContext = canvasContext;
  this.offsetX = offsetX;
  this.offsetY = offsetY;
  this.position = 0;
  this.step = 1;

  this.cellLineWidth = 1;

  this.cellLineColor = 'rgb(0%, 0%, 0%)';
  this.markerColor = 'rgb(100%, 100%, 100%)';
  this.cellSize = 16;
  this.borderWidth = 4;
  this.markerHalfWidth = 2;

  this.size = this.borderWidth+this.cellLineWidth+this.cellSize+this.cellLineWidth+this.borderWidth;
  this.maxPositionQuarter = this.cellLineWidth+this.cellSize;
  this.maxPosition = 4*this.maxPositionQuarter;
  this.markerWidth = this.markerHalfWidth+this.cellLineWidth+this.markerHalfWidth;

  this.setColors = function(cellLineColor, markerColor)
  {
    this.cellLineColor = cellLineColor;
    this.markerColor = markerColor;
  };

  this.normalize = function()
  {
    if(!isFinite(this.position))
    {
      this.position = 0;
      return;
    }
    if(this.position < 0)
      this.position += this.maxPosition*(Math.floor(-this.position/this.maxPosition)+1)
    this.position %= this.maxPosition;
  }

  this.set = function(position, step)
  {
    this.position = position;
    this.step = step;
    this.normalize();
  };

  this.next = function()
  {
    this.position += this.step;
    this.normalize();
  };

  this.markerX = function()
  {
    var x;
    switch(Math.floor(this.position/this.maxPositionQuarter))
    {
      case 0:
        x = this.position%this.maxPositionQuarter;
        break;
      case 1:
        x = this.maxPositionQuarter;
        break;
      case 2:
        x = this.maxPositionQuarter-this.position%this.maxPositionQuarter;
        break;
      case 3:
        x = 0;
        break;
    }
    return this.offsetX*this.size+this.borderWidth+x;
  };

  this.markerY = function()
  {
    var y;
    switch(Math.floor(this.position/this.maxPositionQuarter))
    {
      case 0:
        y = 0;
        break;
      case 1:
        y = this.position%this.maxPositionQuarter;
        break;
      case 2:
        y = this.maxPositionQuarter;
        break;
      case 3:
        y = this.maxPositionQuarter-this.position%this.maxPositionQuarter;
        break;
    }
    return this.offsetY*this.size+this.borderWidth+y;
  };

  this.drawCell = function()
  {
    this.canvasContext.beginPath();
    this.canvasContext.lineWidth = this.cellLineWidth;
    this.canvasContext.strokeStyle = this.cellLineColor;
    this.canvasContext.rect
    (
      this.offsetX*this.size+this.borderWidth+0.5,
      this.offsetY*this.size+this.borderWidth+0.5,
      this.cellSize+this.cellLineWidth,
      this.cellSize+this.cellLineWidth
    );
    this.canvasContext.stroke();
  };

  this.drawMarker = function()
  {
    this.canvasContext.fillStyle = this.markerColor;
    this.canvasContext.fillRect
    (
      this.markerX()-this.markerHalfWidth,
      this.markerY()-this.markerHalfWidth,
      this.markerWidth,
      this.markerWidth
    );
  };

  this.normalize();
}
