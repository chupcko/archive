function GCAClass(name, maxX, maxY, canvasName)
{
  this.name = name;
  this.maxX = maxX;
  this.maxY = maxY;
  this.canvasName = canvasName;

  this.modulo = undefined;
  this.normalizeEval = undefined;
  this.leftEval = undefined;
  this.firstEval = undefined;
  this.rightEval = undefined;
  this.nextEval = undefined;

  this.canvas = document.getElementById(this.canvasName);
  this.canvasContext = this.canvas.getContext('2d');
  this.canvas.width = this.maxX;
  this.canvas.height = this.maxY;

  this.data = [new Array(), new Array()];
  this.dataIndex = undefined;

  this.normalize = function(v)
  {
    var N = this.modulo;
    return eval(this.normalizeEval);
  };

  this.fillFirstLine = function()
  {
    var N = this.modulo;
    var X = this.maxX;
    var Y = this.maxY;
    var y = 0;
    this.data[this.dataIndex][0] = this.normalize(eval(this.leftEval));
    for(var x = 0; x < this.maxX; x++)
      this.data[this.dataIndex][1+x] = this.normalize(eval(this.firstEval));
    this.data[this.dataIndex][1+this.maxX] = this.normalize(eval(this.rightEval));
  };

  this.fillNextLine = function(y)
  {
    var N = this.modulo;
    var X = this.maxX;
    var Y = this.maxY;
    this.dataIndex = 1-this.dataIndex;
    this.data[this.dataIndex][0] = this.normalize(eval(this.leftEval));
    for(var x = 0; x < this.maxX; x++)
    {
      var a = this.data[1-this.dataIndex][x];
      var b = this.data[1-this.dataIndex][x+1];
      var c = this.data[1-this.dataIndex][x+2];
      this.data[this.dataIndex][1+x] = this.normalize(eval(this.nextEval));
    }
    this.data[this.dataIndex][1+this.maxX] = this.normalize(eval(this.rightEval));
  };

  this.drawPoint = function(x, y, color)
  {
    this.canvasContext.beginPath();
    this.canvasContext.lineWidth = 1;
    this.canvasContext.strokeStyle = 'rgb('+color+'%, '+color+'%, '+color+'%)';
    this.canvasContext.moveTo(x+0.5, y);
    this.canvasContext.lineTo(x+0.5, y+1);
    this.canvasContext.stroke();
  };

  this.drawLine = function(y)
  {
    for(var x = 0; x < this.maxX; x++)
      this.drawPoint(x, y, 100-Math.floor(100*this.data[this.dataIndex][x+1]/this.modulo));
  };

  this.draw = function()
  {
    this.dataIndex = 0;
    this.fillFirstLine();
    this.drawLine(0);
    for(var y = 1; y < this.maxY; y++)
    {
      this.fillNextLine(y)
      this.drawLine(y);
    }
  };

  this.set = function(modulo, normalizeEval, leftEval, firstEval, rightEval, nextEval)
  {
    this.modulo = modulo;
    this.normalizeEval = normalizeEval;
    this.leftEval = leftEval;
    this.firstEval = firstEval;
    this.rightEval = rightEval;
    this.nextEval = nextEval;
    this.draw();
  };

  window[this.name] = this;
}
