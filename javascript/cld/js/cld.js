function CLDClass(containerID, dimension)
{
  this.container = document.getElementById(containerID);
  this.dimension = dimension;

  this.canvasBackground = undefined;
  this.canvasBackgroundContext = undefined;
  this.canvasDrawing = undefined;
  this.canvasDrawingContext = undefined;
  this.canvasPointer = undefined;
  this.canvasPointerContext = undefined;

  this.BackgroundColor = 'rgb(75%, 75%, 75%)';
  this.DrawingHalfSize = 3;
  this.DrawingSize = 2*this.DrawingHalfSize+1;
  this.DrawingColor = 'rgb(100%, 0%, 0%)'
  this.PointerHalfSize = 5;
  this.PointerSize = 2*this.PointerHalfSize+1;
  this.PointerColor = 'rgba(0%, 0%, 100%, 0.5)'

  this.init = function()
  {
    this.container.innerHTML =
      '<button onclick="'+this.$name()+'.clear();">Clear</button><p/>'+
      '<div id="'+this.$name()+'_div">'+
      '<canvas style="position: absolute; z-index: 0;" id="'+this.$name()+'_canvas_background"></canvas>'+
      '<canvas style="position: absolute; z-index: 1;" id="'+this.$name()+'_canvas_drawing"></canvas>'+
      '<canvas style="position: absolute; z-index: 2;" id="'+this.$name()+'_canvas_pointer" onmouseout="'+this.$name()+'.pointerClear();"></canvas>'+
      '</div>';

    var div = document.getElementById(this.$name()+'_div');
    div.style.width = this.dimension+'px';
    div.style.height = this.dimension+'px';

    this.canvasBackground = document.getElementById(this.$name()+'_canvas_background');
    this.canvasBackgroundContext = this.canvasBackground.getContext('2d');
    this.canvasBackground.width = this.dimension;
    this.canvasBackground.height = this.dimension;

    this.canvasDrawing = document.getElementById(this.$name()+'_canvas_drawing');
    this.canvasDrawingContext = this.canvasDrawing.getContext('2d');
    this.canvasDrawing.width = this.dimension;
    this.canvasDrawing.height = this.dimension;

    this.canvasPointer = document.getElementById(this.$name()+'_canvas_pointer');
    this.canvasPointerContext = this.canvasPointer.getContext('2d');
    this.canvasPointer.addEventListener
    (
      'mouseover',
      (
        function(that)
        {
          return function(event)
          {
            var point = that.eventPoint(event);
            that.handleMove(point.x, point.y);
            return false;
          };
        }
      )(this),
      false
    );
    this.canvasPointer.addEventListener
    (
      'mousemove',
      (
        function(that)
        {
          return function(event)
          {
            var point = that.eventPoint(event);
            that.handleMove(point.x, point.y);
            return false;
          };
        }
      )(this),
      false
    );
    this.canvasPointer.addEventListener
    (
      'click',
      (
        function(that)
        {
          return function(event)
          {
            var point = that.eventPoint(event);
            that.handleClick(point.x, point.y);
            return false;
          };
        }
      )(this),
      false
    );
    this.canvasPointer.width = this.dimension;
    this.canvasPointer.height = this.dimension;

    this.drawBackground();
  };

  this.clear = function()
  {
    this.canvasDrawingContext.clearRect
    (
      0,
      0,
      this.dimension,
      this.dimension
    );
  };

  this.pointerClear = function()
  {
    this.canvasPointerContext.clearRect
    (
      0,
      0,
      this.dimension,
      this.dimension
    );
  };

  this.eventPoint = function(event)
  {
    var x;
    var y;
    if
    (
      event.pageX !== undefined &&
      event.pageY !== undefined
    )
    {
      x = event.pageX;
      y = event.pageY;
    }
    else
    {
      x = event.clientX+document.body.scrollLeft+document.documentElement.scrollLeft;
      y = event.clientY+document.body.scrollTop+document.documentElement.scrollTop;
    }
    return { x: x-this.canvasPointer.offsetLeft, y: y-this.canvasPointer.offsetTop };
  };

  this.handleMove = function(x, y)
  {
    this.pointerClear();
    this.canvasPointerContext.fillStyle = this.PointerColor;
    this.canvasPointerContext.fillRect
    (
      x-this.PointerHalfSize,
      y-this.PointerHalfSize,
      this.PointerSize,
      this.PointerSize
    );
  };

  this.handleClick = function(x, y)
  {
    this.canvasDrawingContext.fillStyle = this.DrawingColor;
    this.canvasDrawingContext.fillRect
    (
      x-this.DrawingHalfSize,
      y-this.DrawingHalfSize,
      this.DrawingSize,
      this.DrawingSize
    );
  };

  this.drawBackground = function()
  {
    this.canvasBackgroundContext.fillStyle = this.BackgroundColor;
    this.canvasBackgroundContext.fillRect
    (
      0,
      0,
      this.dimension,
      this.dimension
    );
  };

  this.init();
}
