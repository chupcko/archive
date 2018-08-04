function boxClass(idName, images, dimX, dimY, minesNumber)
{
  this.idName = idName;
  this.images = images;
  this.dimX = dimX;
  this.dimY = dimY;
  this.minesNumber = minesNumber;

  this.fieldSize = this.images.getFieldSize();
  this.frameSize = this.images.getFrameSize();
  this.frameGrids = this.images.getFrameGrids();
  this.borderSize = this.frameSize*3;
  this.frame = this.images.getFrame();

  this.game = new gameClass(this.dimX, this.dimY, this.minesNumber);

  this.autoPlayTime = 500;
  this.autoPlayTimer = undefined;

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
      x >= this.borderSize+this.frameSize && x < this.borderSize+this.frameSize+this.dimX*this.fieldSize &&
      y >= this.borderSize+this.frameSize && y < this.borderSize+this.frameSize+this.dimY*this.fieldSize
    )
    {
      var returnValue =
      {
        x: ((x-this.borderSize-this.frameSize)/this.fieldSize)|0,
        y: ((y-this.borderSize-this.frameSize)/this.fieldSize)|0,
      };
      return returnValue;
    }
    return undefined;
  };

  this.canvas = document.getElementById(this.idName);
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
          {
            that.game.open(point.x, point.y);
            that.draw();
          }
          return false;
        }
      }
    )(this),
    false
  );
  this.canvas.addEventListener
  (
    'contextmenu',
    (
      function(that)
      {
        return function(event)
        {
          var point = that.point(event);
          if(point != undefined)
          {
            that.game.mark(point.x, point.y);
            that.draw();
          }
          event.preventDefault();
          return false;
        }
      }
    )(this),
    false
  );
  this.canvas.width = this.borderSize+this.frameSize+this.dimX*this.fieldSize+this.frameSize+this.borderSize;
  this.canvas.height = this.borderSize+this.frameSize+this.dimY*this.fieldSize+this.frameSize+this.borderSize;

  this.openRandom = function()
  {
    this.game.helpOpenRandom();
    this.draw();
  };

  this.markOne = function()
  {
    this.game.helpMarkAll(true);
    this.draw();
  };

  this.openOne = function()
  {
    this.game.helpOpenAll(true);
    this.draw();
  };

  this.markAll = function()
  {
    this.game.helpMarkAll(false);
    this.draw();
  };

  this.openAll = function()
  {
    this.game.helpOpenAll(false);
    this.draw();
  };

  this.play = function()
  {
    this.game.helpPlay();
    this.draw();
  };

  this.autoPlaySetTime = function(time)
  {
    this.autoPlayTime = time;
  };

  this.autoPlayStartStop = function()
  {
    if(this.autoPlayTimer == undefined)
      this.autoPlayTimer = setInterval
      (
        (
          function(self)
          {
            return function()
            {
              self.play();
            }
          }
        )(this),
        this.autoPlayTime
      );
    else
    {
      clearInterval(this.autoPlayTimer)
      this.autoPlayTimer = undefined;
    }
  };

  this.autoPlayStop = function()
  {
    if(this.autoPlayTimer != undefined)
    {
      clearInterval(this.autoPlayTimer)
      this.autoPlayTimer = undefined;
    }
  };

  this.draw = function()
  {
    if(this.game.getPlayable() == true)
      this.canvasContext.fillStyle = 'rgb(75%, 75%, 75%)';
    else if(this.game.getBoom() == true)
      this.canvasContext.fillStyle = 'rgb(100%, 0%, 0%)';
    else
      this.canvasContext.fillStyle = 'rgb(0%, 100%, 0%)';
    this.canvasContext.fillRect(0, 0, this.canvas.width, this.canvas.height);
    this.canvasContext.drawImage
    (
      this.frame,
      0,                                                       0,
      this.frameSize,                                          this.frameSize,
      this.borderSize,                                         this.borderSize,
      this.frameSize,                                          this.frameSize
    );
    this.canvasContext.drawImage
    (
      this.frame,
      0,                                                       (this.frameGrids-1)*this.frameSize,
      this.frameSize,                                          this.frameSize,
      this.borderSize,                                         this.borderSize+this.frameSize+this.dimY*this.fieldSize,
      this.frameSize,                                          this.frameSize
    );
    this.canvasContext.drawImage
    (
      this.frame,
      (this.frameGrids-1)*this.frameSize,                      0,
      this.frameSize,                                          this.frameSize,
      this.borderSize+this.frameSize+this.dimX*this.fieldSize, this.borderSize,
      this.frameSize,                                          this.frameSize
    );
    this.canvasContext.drawImage
    (
      this.frame,
      (this.frameGrids-1)*this.frameSize,                      (this.frameGrids-1)*this.frameSize,
      this.frameSize,                                          this.frameSize,
      this.borderSize+this.frameSize+this.dimX*this.fieldSize, this.borderSize+this.frameSize+this.dimY*this.fieldSize,
      this.frameSize,                                          this.frameSize
    );
    this.canvasContext.drawImage
    (
      this.frame,
      this.frameSize,                                          0,
      (this.frameGrids-3)*this.frameSize,                      this.frameSize,
      this.borderSize+this.frameSize,                          this.borderSize,
      this.dimX*this.fieldSize,                                this.frameSize
    );
    this.canvasContext.drawImage
    (
      this.frame,
      2*this.frameSize,                                        (this.frameGrids-1)*this.frameSize,
      (this.frameGrids-3)*this.frameSize,                      this.frameSize,
      this.borderSize+this.frameSize,                          this.borderSize+this.frameSize+this.dimY*this.fieldSize,
      this.dimX*this.fieldSize,                                this.frameSize
    );
    this.canvasContext.drawImage
    (
      this.frame,
      0,                                                       this.frameSize,
      this.frameSize,                                          (this.frameGrids-3)*this.frameSize,
      this.borderSize,                                         this.borderSize+this.frameSize,
      this.frameSize,                                          this.dimY*this.fieldSize
    );
    this.canvasContext.drawImage
    (
      this.frame,
      (this.frameGrids-1)*this.frameSize,                      2*this.frameSize,
      this.frameSize,                                          (this.frameGrids-3)*this.frameSize,
      this.borderSize+this.frameSize+this.dimX*this.fieldSize, this.borderSize+this.frameSize,
      this.frameSize,                                          this.dimY*this.fieldSize
    );
    for(var x = 0; x < this.dimX; x++)
      for(var y = 0; y < this.dimY; y++)
        this.canvasContext.drawImage
        (
          this.images.getImage(this.game.getCode(x, y)),
          this.borderSize+this.frameSize+x*this.fieldSize, this.borderSize+this.frameSize+y*this.fieldSize
        );
  };

  this.draw();
}
