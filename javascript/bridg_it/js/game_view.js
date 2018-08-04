function GameViewClass(containerID, dimension)
{
  if(dimension < 2)
    dimension = 2;

  this.container = document.getElementById(containerID);
  this.dimension = dimension;

  this.canvasBackground = undefined;
  this.canvasBackgroundContext = undefined;
  this.canvasDots = undefined;
  this.canvasDots = undefined;
  this.canvasLines = undefined;
  this.canvasLines = undefined;
  this.canvasProposal = undefined;
  this.canvasProposalContext = undefined;

  this.game = new GameClass(this.dimension);
  this.boxProposal = undefined;

  this.colorBackgroud = 'rgb(100%, 100%, 100%)';
  this.colorBackgroudRed = 'rgb(100%, 90%, 90%)';
  this.colorBackgroudBlue = 'rgb(90%, 90%, 100%)';
  this.colorDotRed = 'rgb(100%, 0%, 0%)';
  this.colorDotBlue = 'rgb(0%, 0%, 100%)';
  this.colorLineRed = 'rgb(100%, 40%, 40%)';
  this.colorLineBlue = 'rgb(40%, 40%, 100%)';
  this.colorProposalRed = 'rgb(100%, 80%, 80%)';
  this.colorProposalBlue = 'rgb(80%, 80%, 100%)';

  this.lineWidth = 3;
  this.dotMargin = 2;
  this.dotWidth = this.dotMargin+this.lineWidth+this.dotMargin;
  this.offset = this.dotWidth;
  this.lineLength = 5*this.dotWidth;
  this.dotOffset = this.offset+3*this.dotWidth;
  this.clickWidth = 3*this.dotWidth;
  this.clickOffset = this.offset+2*this.dotWidth;
  this.periodic = this.dotWidth+this.lineLength;

  this.init = function()
  {
    var dimension = this.dotOffset+(this.dimension-1)*this.periodic+this.dotWidth+this.dotOffset;

    this.container.innerHTML =
      '<button onclick="'+this.$name()+'.new();">New</button><p/>'+
      '<span id="'+this.$name()+'_status"></span><p/>'+
      '<div id="'+this.$name()+'_div">'+
      '<canvas style="position: absolute; z-index:0" id="'+this.$name()+'_canvas_background"></canvas>'+
      '<canvas style="position: absolute; z-index:1" id="'+this.$name()+'_canvas_dots"></canvas>'+
      '<canvas style="position: absolute; z-index:2" id="'+this.$name()+'_canvas_lines"></canvas>'+
      '<canvas style="position: absolute; z-index:3" id="'+this.$name()+'_canvas_proposal" onmouseout="'+this.$name()+'.outProposal();"></canvas>'+
      '</div>'+
      '<button onclick="'+this.$name()+'.beatMe();">Beat me</button>';

    var div = document.getElementById(this.$name()+'_div');
    div.style.width = dimension+'px';
    div.style.height = dimension+'px';

    this.canvasBackground = document.getElementById(this.$name()+'_canvas_background');
    this.canvasBackgroundContext = this.canvasBackground.getContext('2d');
    this.canvasBackground.width = dimension;
    this.canvasBackground.height = dimension;

    this.canvasDots = document.getElementById(this.$name()+'_canvas_dots');
    this.canvasDotsContext = this.canvasDots.getContext('2d');
    this.canvasDots.width = dimension;
    this.canvasDots.height = dimension;

    this.canvasLines = document.getElementById(this.$name()+'_canvas_lines');
    this.canvasLinesContext = this.canvasLines.getContext('2d');
    this.canvasLines.width = dimension;
    this.canvasLines.height = dimension;

    this.canvasProposal = document.getElementById(this.$name()+'_canvas_proposal');
    this.canvasProposalContext = this.canvasProposal.getContext('2d');
    this.canvasProposal.addEventListener
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
    this.canvasProposal.addEventListener
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
    this.canvasProposal.addEventListener
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
    this.canvasProposal.width = dimension;
    this.canvasProposal.height = dimension;

    this.drawStatusBackground();
    this.drawDots();
  };

  this.new = function()
  {
    this.game.new();
    this.drawStatusBackground();
    this.clearLines();
    this.outProposal();
  };

  this.drawStatusBackground = function()
  {
    document.getElementById(this.$name()+'_status').innerHTML = this.game.getStatusString();
    switch(this.game.status)
    {
      case this.game.FlagEmpty:
        this.canvasBackgroundContext.fillStyle = this.colorBackgroud;
        break;
      case this.game.FlagRed:
        this.canvasBackgroundContext.fillStyle = this.colorBackgroudRed;
        break;
      case this.game.FlagBlue:
        this.canvasBackgroundContext.fillStyle = this.colorBackgroudBlue;
        break;
    }
    this.canvasBackgroundContext.fillRect
    (
      0,
      0,
      this.canvasBackground.width,
      this.canvasBackground.height
    );
  };

  this.clearLines = function()
  {
    this.canvasLinesContext.clearRect
    (
      0,
      0,
      this.canvasLines.width,
      this.canvasLines.height
    );
  };

  this.outProposal = function()
  {
    this.boxProposal = undefined;
    this.clearProposal();
  };

  this.clearProposal = function()
  {
    this.canvasProposalContext.clearRect
    (
      0,
      0,
      this.canvasProposal.width,
      this.canvasProposal.height
    );
  };

  this.beatMe = function()
  {
    var result = this.game.beatMe();
    this.drawStatusBackground();
    this.clearLines();
    this.outProposal();
    this.drawLine(result.player, result.x, result.y, false);
  };

  this.drawLine = function(player, x, y, proposal)
  {
    var canvasContext;
    if(proposal)
      canvasContext = this.canvasProposalContext;
    else
      canvasContext = this.canvasLinesContext;
    var xr = (x/2)|0;
    var yr = (y/2)|0;
    switch(player)
    {
      case this.game.FlagRed:
        if(proposal)
          canvasContext.fillStyle = this.colorProposalRed;
        else
          canvasContext.fillStyle = this.colorLineRed;
        if(x%2 == 0)
          this.drawLineRedVertical(xr, yr, canvasContext);
        else
          this.drawLineRedHorizontal(xr, yr+1, canvasContext);
        break;
      case this.game.FlagBlue:
        if(proposal)
          canvasContext.fillStyle = this.colorProposalBlue;
        else
          canvasContext.fillStyle = this.colorLineBlue;
        if(x%2 == 0)
          this.drawLineBlueHorizontal(xr, yr, canvasContext);
        else
          this.drawLineBlueVertical(xr+1, yr, canvasContext);
        break;
    }
  };

  this.drawLineRedVertical = function(x, y, canvasContext)
  {
    canvasContext.fillRect
    (
      this.dotOffset+x*this.periodic+this.dotMargin,
      this.offset+y*this.periodic+this.dotWidth,
      this.lineWidth,
      this.lineLength
    );
  };

  this.drawLineRedHorizontal = function(x, y, canvasContext)
  {
    canvasContext.fillRect
    (
      this.dotOffset+x*this.periodic+this.dotWidth,
      this.offset+y*this.periodic+this.dotMargin,
      this.lineLength,
      this.lineWidth
    );
  };

  this.drawLineBlueHorizontal = function(x, y, canvasContext)
  {
    canvasContext.fillRect
    (
      this.offset+x*this.periodic+this.dotWidth,
      this.dotOffset+y*this.periodic+this.dotMargin,
      this.lineLength,
      this.lineWidth
    );
  };

  this.drawLineBlueVertical = function(x, y, canvasContext)
  {
    canvasContext.fillRect
    (
      this.offset+x*this.periodic+this.dotMargin,
      this.dotOffset+y*this.periodic+this.dotWidth,
      this.lineWidth,
      this.lineLength
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
    return { x: x-this.canvasProposal.offsetLeft, y: y-this.canvasProposal.offsetTop };
  };

  this.handleMove = function(x, y)
  {
    var box = this.findBox(x, y);
    if
    (
      box !== undefined &&
      this.game.isPlayable(box.x, box.y)
    )
    {
      if
      (
        this.boxProposal === undefined ||
        this.boxProposal.x != box.x ||
        this.boxProposal.y != box.y
      )
      {
        this.clearProposal();
        this.boxProposal = box;
        this.drawLine(this.game.next, box.x, box.y, true);
      }
    }
    else
      if(this.boxProposal !== undefined)
        this.outProposal();
  };

  this.findBox = function(x, y)
  {
    var box;
    switch(this.game.next)
    {
      case this.game.FlagRed:
        box = this.findPeriodicBox
        (
          x,
          y,
          this.dotOffset,
          this.offset+this.dotWidth,
          this.dotWidth,
          this.lineLength,
          this.periodic,
          this.periodic
        );
        if(box !== undefined)
          return { x: 2*box.x, y: 2*box.y };
        box = this.findPeriodicBox
        (
          x,
          y,
          this.dotOffset+this.dotWidth,
          this.offset+this.periodic,
          this.lineLength,
          this.dotWidth,
          this.periodic,
          this.periodic
        );
        if(box !== undefined)
          return { x: 2*box.x+1, y: 2*box.y+1 };
        break;
      case this.game.FlagBlue:
        box = this.findPeriodicBox
        (
          x,
          y,
          this.offset+this.dotWidth,
          this.dotOffset,
          this.lineLength,
          this.dotWidth,
          this.periodic,
          this.periodic
        );
        if(box !== undefined)
          return { x: 2*box.x, y: 2*box.y };
        box = this.findPeriodicBox
        (
          x,
          y,
          this.offset+this.periodic,
          this.dotOffset+this.dotWidth,
          this.dotWidth,
          this.lineLength,
          this.periodic,
          this.periodic
        );
        if(box !== undefined)
          return { x: 2*box.x+1, y: 2*box.y+1 };
        break;
    }
    return this.findPeriodicBox
    (
      x,
      y,
      this.clickOffset,
      this.clickOffset,
      this.clickWidth,
      this.clickWidth,
      this.clickWidth,
      this.clickWidth
    );
  };

  this.findPeriodicBox = function(x, y, offsetX, offsetY, sizeX, sizeY, periodicX, periodicY)
  {
    if
    (
      x-offsetX >= 0 &&
      y-offsetY >= 0 &&
      (x-offsetX)%periodicX < sizeX &&
      (y-offsetY)%periodicY < sizeY
    )
      return { x: ((x-offsetX)/periodicX)|0, y: ((y-offsetY)/periodicY)|0 };
    return undefined;
  };

  this.handleClick = function(x, y)
  {
    var box = this.findBox(x, y);
    if
    (
      box !== undefined &&
      this.game.isPlayable(box.x, box.y)
    )
    {
      var player = this.game.next;
      var result = this.game.play(box.x, box.y);
      this.drawLine(player, box.x, box.y, false);
      if(result !== undefined)
        this.drawLine(result.player, result.x, result.y, false);
      this.drawStatusBackground();
      this.outProposal();
    }
  };

  this.drawDots = function()
  {
    for(var x = 0; x < this.dimension; x++)
      for(var y = 0; y < this.dimension+1; y++)
      {
        this.canvasDotsContext.fillStyle = this.colorDotRed;
        this.canvasDotsContext.fillRect
        (
          this.dotOffset+x*this.periodic,
          this.offset+y*this.periodic,
          this.dotWidth,
          this.dotWidth
        );
        this.canvasDotsContext.fillStyle = this.colorDotBlue;
        this.canvasDotsContext.fillRect
        (
          this.offset+y*this.periodic,
          this.dotOffset+x*this.periodic,
          this.dotWidth,
          this.dotWidth
        );
      }
    for(var i = 0; i < this.dimension-1; i++)
    {
      this.canvasDotsContext.fillStyle = this.colorLineRed;
      this.drawLineRedHorizontal(i, 0, this.canvasDotsContext);
      this.drawLineRedHorizontal(i, this.dimension, this.canvasDotsContext);
      this.canvasDotsContext.fillStyle = this.colorLineBlue;
      this.drawLineBlueVertical(0, i, this.canvasDotsContext);
      this.drawLineBlueVertical(this.dimension, i, this.canvasDotsContext);
    }
  };

  this.init();
}
