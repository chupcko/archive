function boxClass(idBox, idTime, idMines, images, dimX, dimY, minesNumber)
{
  this.idBox = idBox;
  this.idTime = idTime;
  this.idMines = idMines;
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

  this.autoPlayDelay = 100;
  this.autoPlayTimer = undefined;

  this.timeTimer = undefined;

  this.point = function(event)
  {
    var rect = this.canvas.getBoundingClientRect();
    var x = Math.round(event.clientX-rect.left);
    var y = Math.round(event.clientY-rect.top);
    if
    (
      x >= this.borderSize+this.frameSize && x < this.borderSize+this.frameSize+this.dimX*this.fieldSize &&
      y >= this.borderSize+this.frameSize && y < this.borderSize+this.frameSize+this.dimY*this.fieldSize
    )
    {
      var returnValue =
      {
        x: Math.floor((x-this.borderSize-this.frameSize)/this.fieldSize),
        y: Math.floor((y-this.borderSize-this.frameSize)/this.fieldSize),
      };
      return returnValue;
    }
    return undefined;
  };

  this.clickCallback =
  (
    function(self)
    {
      return function(event)
      {
        var point = self.point(event);
        if(point != undefined)
        {
          self.game.open(point.x, point.y);
          self.draw();
        }
        return false;
      }
    }
  )(this);

  this.contextmenuCallback =
  (
    function(self)
    {
      return function(event)
      {
        var point = self.point(event);
        if(point != undefined)
        {
          self.game.mark(point.x, point.y);
          self.draw();
        }
        event.preventDefault();
        return false;
      }
    }
  )(this);

  this.canvas = document.getElementById(this.idBox);
  this.canvasContext = this.canvas.getContext('2d');
  this.canvas.addEventListener('click', this.clickCallback, false);
  this.canvas.addEventListener('contextmenu', this.contextmenuCallback, false);
  this.canvas.width = this.borderSize+this.frameSize+this.dimX*this.fieldSize+this.frameSize+this.borderSize;
  this.canvas.height = this.borderSize+this.frameSize+this.dimY*this.fieldSize+this.frameSize+this.borderSize;

  this.elementTime = document.getElementById(this.idTime);
  this.elementMines = document.getElementById(this.idMines);

  this.elementTime.innerHTML = '0.0';

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
    this.game.helpPlay(true);
    this.draw();
  };

  this.autoPlaySetDelay = function(delay)
  {
    this.autoPlayDelay = delay;
  };

  this.autoPlayStartStop = function()
  {
    if(this.autoPlayTimer == undefined)
    {
      this.game.helpPlay(true);
      this.draw();
      this.autoPlayTimer = setInterval
      (
        (
          function(self)
          {
            return function()
            {
              if(self.game.helpPlay(false) == false)
                self.autoPlayStop();
              self.draw()
            }
          }
        )(this),
        this.autoPlayDelay
      );
    }
    else
    {
      clearInterval(this.autoPlayTimer);
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

  this.timeShow = function(digits)
  {
    var time = this.game.getTime();
    var timeInt = Math.floor(time/1000);
    var timeDec = time%1000;
    this.elementTime.innerHTML = timeInt+'.'+('00'+timeDec.toString()).slice(-3).substring(0, digits);
  };

  this.timeStart = function()
  {
    if(this.timeTimer == undefined)
      this.timeTimer = setInterval
      (
        (
          function(self)
          {
            return function()
            {
              self.timeShow(1);
            }
          }
        )(this),
        50
      );
  };

  this.timeStop = function()
  {
    if(this.timeTimer != undefined)
    {
      clearInterval(this.timeTimer);
      this.timeTimer = undefined;
    }
  };

  this.draw = function()
  {
    if(this.game.getPlayable() == true)
    {
      if(this.game.isStarted())
      {
        this.timeStop();
        this.timeStart();
      }
      else
        this.timeShow(1);
      this.canvasContext.fillStyle = 'rgb(75%, 75%, 75%)';
    }
    else
    {
      this.timeStop();
      this.timeShow(3);
      if(this.game.getBoom() == true)
        this.canvasContext.fillStyle = 'rgb(100%, 0%, 0%)';
      else
        this.canvasContext.fillStyle = 'rgb(0%, 100%, 0%)';
    }
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
    this.elementMines.innerHTML = this.game.getMinesRemain();
  };

  this.destroy = function()
  {
    this.autoPlayStop()
    this.timeStop();
    this.canvas.removeEventListener('click', this.clickCallback, false);
    this.canvas.removeEventListener('contextmenu', this.contextmenuCallback, false);
  };

  this.draw();
}
