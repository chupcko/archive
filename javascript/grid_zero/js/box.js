function boxClass(name, canvasName, N)
{
  this.name = name;
  this.canvasName = canvasName;
  this.N = N;

  this.fieldSize = 20;
  this.frameSize = 5;
  this.inputSize = 2;
  this.framePlayColor = 'rgb(50%, 50%, 50%)';
  this.frameEditColor = 'rgb(100%, 25%, 25%)';
  this.fieldOnColor = 'rgb(100%, 100%, 0%)';
  this.fieldOffColor = 'rgb(0%, 0%, 0%)';
  this.inputColor = 'rgb(100%, 0%, 0%)';

  this.modeEdit = false;
  this.showInput = false;

  this.point = function(event)
  {
    var x = new Number();
    var y = new Number();
    if(event.x != undefined && event.y != undefined)
    {
      x = event.x;
      y = event.y;
    }
    else
    {
      x = event.clientX+document.body.scrollLeft+document.documentElement.scrollLeft;
      y = event.clientY+document.body.scrollTop+document.documentElement.scrollTop;
    }
    x -= this.canvas.offsetLeft;
    y -= this.canvas.offsetTop;

    if
    (
      x%(this.frameSize+this.fieldSize) < this.frameSize ||
      y%(this.frameSize+this.fieldSize) < this.frameSize
    )
      return undefined;
    var returnValue =
    {
      x: (x/(this.frameSize+this.fieldSize))|0,
      y: (y/(this.frameSize+this.fieldSize))|0
    };
    return returnValue;
  };

  this.canvas = document.getElementById(this.canvasName);
  this.canvasContext = this.canvas.getContext('2d');
  this.canvas.addEventListener
  (
    'click',
    (
      function(that)
      {
        return function(event)
        {
          var point = that.point(event);
          if(point != undefined)
            that.click(point.x, point.y);
          return false;
        }
      }
    )(this),
    false
  );
  this.canvas.width = N*(this.frameSize+this.fieldSize)+this.frameSize;
  this.canvas.height = this.canvas.width;

  this.toggleMode = function()
  {
    this.modeEdit = !this.modeEdit;
    this.draw();
  };

  this.toggleInput = function()
  {
    this.showInput = !this.showInput;
    this.draw();
  };

  this.init = function()
  {
    this.fields = new Array();
    this.input = new Array();
    this.fieldsSave = new Array();
    this.inputSave = new Array();
    for(var x = 0; x < this.N; x++)
    {
      this.fields[x] = new Array();
      this.input[x] = new Array();
      this.fieldsSave[x] = new Array();
      this.inputSave[x] = new Array();
      for(var y = 0; y < this.N; y++)
      {
        this.fields[x][y] = 0;
        this.input[x][y] = 0;
        this.fieldsSave[x][y] = 0;
        this.inputSave[x][y] = 0;
      }
    }
    this.draw();
  };

  this.reset = function()
  {
    for(var x = 0; x < this.N; x++)
      for(var y = 0; y < this.N; y++)
        this.fields[x][y] = 0;
    this.draw();
  };

  this.clearInput = function()
  {
    for(var x = 0; x < this.N; x++)
      for(var y = 0; y < this.N; y++)
        this.input[x][y] = 0;
    this.draw();
  };

  this.fillRandom = function()
  {
    for(var x = 0; x < this.N; x++)
      for(var y = 0; y < this.N; y++)
        this.fields[x][y] = (Math.random()*2)|0;
    this.draw();
  };

  this.shuffle = function()
  {
    for(i = 0; i < this.N*this.N; i++)
    {
      var x = (Math.random()*N)|0;
      var y = (Math.random()*N)|0;
      this.fields[x][y] = !this.fields[x][y];
      this.clickHelper(x, y);
    }
    this.draw();
  };

  this.save = function()
  {
    for(var x = 0; x < this.N; x++)
      for(var y = 0; y < this.N; y++)
      {
        this.fieldsSave[x][y] = this.fields[x][y];
        this.inputSave[x][y] = this.input[x][y];
      }
  };

  this.load = function()
  {
    for(var x = 0; x < this.N; x++)
      for(var y = 0; y < this.N; y++)
      {
        this.fields[x][y] = this.fieldsSave[x][y];
        this.input[x][y] = this.inputSave[x][y];
      }
    this.draw();
  };

  this.countInput = function()
  {
    var count = 0;
    for(var x = 0; x < this.N; x++)
      for(var y = 0; y < this.N; y++)
        if(this.input[x][y]%2 == 1)
          count++;
    return count;
  };

  this.clickHelper = function(x, y)
  {
    this.input[x][y]++;
    for(var i = 0; i < N; i++)
    {
      if(i != x)
        this.fields[i][y] = !this.fields[i][y];
      if(i != y)
        this.fields[x][i] = !this.fields[x][i];
    }
  };

  this.click = function(x, y)
  {
    if(x < 0 || x >= N || y < 0 || y >= N)
      return;
    this.fields[x][y] = !this.fields[x][y];
    if(!this.modeEdit)
      this.clickHelper(x, y);
    this.draw();
  };

  this.draw = function()
  {
    for(var x = 0; x < this.N; x++)
      for(var y = 0; y < this.N; y++)
      {
        if(this.modeEdit)
          this.canvasContext.fillStyle = this.frameEditColor;
        else
          this.canvasContext.fillStyle = this.framePlayColor;
        this.canvasContext.fillRect
        (
          x*(this.frameSize+this.fieldSize),
          y*(this.frameSize+this.fieldSize),
          this.frameSize+this.fieldSize+this.frameSize,
          this.frameSize+this.fieldSize+this.frameSize
        )
        if(this.fields[x][y] != 0)
          this.canvasContext.fillStyle = this.fieldOnColor;
        else
          this.canvasContext.fillStyle = this.fieldOffColor;
        this.canvasContext.fillRect
        (
          x*(this.frameSize+this.fieldSize)+this.frameSize,
          y*(this.frameSize+this.fieldSize)+this.frameSize,
          this.fieldSize,
          this.fieldSize
        )
        if(this.showInput)
          if(this.input[x][y]%2 == 1)
          {
            this.canvasContext.beginPath();
            this.canvasContext.moveTo
            (
              x*(this.frameSize+this.fieldSize)+this.frameSize,
              y*(this.frameSize+this.fieldSize)+this.frameSize
            );
            this.canvasContext.lineTo
            (
              (x+1)*(this.frameSize+this.fieldSize),
              (y+1)*(this.frameSize+this.fieldSize)
            );
            this.canvasContext.moveTo
            (
              x*(this.frameSize+this.fieldSize)+this.frameSize,
              (y+1)*(this.frameSize+this.fieldSize)
            );
            this.canvasContext.lineTo
            (
              (x+1)*(this.frameSize+this.fieldSize),
              y*(this.frameSize+this.fieldSize)+this.frameSize
            );
            this.canvasContext.lineWidth = this.inputSize;
            this.canvasContext.strokeStyle = this.inputColor;
            this.canvasContext.stroke();
          }
      }
  };

  window[this.name] = this;
  this.init();
}
