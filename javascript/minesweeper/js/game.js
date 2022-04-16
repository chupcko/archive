function gameClass(dimX, dimY, minesNumber)
{
  this.dimX = dimX;
  this.dimY = dimY;
  this.minesNumber = minesNumber;

  this.fields = undefined;
  this.playable = undefined;
  this.shuffled = undefined;
  this.boom = undefined;
  this.openedNumber = undefined;
  this.minesRemain = undefined;
  this.haveAction = undefined;
  this.startTime = undefined;
  this.stopTime = undefined;

  this.ValueBomb = -1;
  this.FlagOpen  = 0;
  this.FlagClose = 1;
  this.FlagMark  = 2;
  this.FlagBoom  = 3;

  this.CodeClose   = 9;
  this.CodeMark    = 10;
  this.CodeBoom    = 11;
  this.CodeBomb    = 12;
  this.CodeNotBomb = 13;

  this.reset = function()
  {
    this.fields = new Array();
    for(var x = 0; x < this.dimX; x++)
    {
      this.fields[x] = new Array();
      for(var y = 0; y < this.dimY; y++)
        this.fields[x][y] =
        {
          value: 0,
          flag: this.FlagClose,
        };
    }
    this.playable = true;
    this.shuffled = false;
    this.boom = false;
    this.openedNumber = 0;
    this.minesRemain = this.minesNumber;
    this.haveAction = false;
    this.startTime = undefined;
    this.stopTime = undefined;
  };

  this.start = function()
  {
    if(this.startTime == undefined)
      this.startTime = (new Date()).getTime();
  };

  this.stop = function()
  {
    this.stopTime = (new Date()).getTime();
  };

  this.getCode = function(x, y)
  {
    if(this.playable == true)
      switch(this.fields[x][y].flag)
      {
        case this.FlagOpen:
          return this.fields[x][y].value;
          break;
        case this.FlagMark:
          return this.CodeMark;
          break;
        default:
          return this.CodeClose;
      }
    else if(this.boom == true)
      switch(this.fields[x][y].flag)
      {
        case this.FlagMark:
          if(this.fields[x][y].value != this.ValueBomb)
            return this.CodeNotBomb;
          return this.CodeMark;
          break;
        case this.FlagBoom:
          return this.CodeBoom;
          break;
        default:
          if(this.fields[x][y].value == this.ValueBomb)
            return this.CodeBomb;
          return this.fields[x][y].value;
      }
    else
    {
      if(this.fields[x][y].value == this.ValueBomb)
        return this.CodeMark;
      return this.fields[x][y].value;
    }
    return this.CodeClose;
  };

  this.countAroundWithValueHelper = function(x, y, value)
  {
    if
    (
      x >= 0 &&
      x < this.dimX &&
      y >= 0 &&
      y < this.dimY &&
      this.fields[x][y].value == value
    )
      return 1;
    return 0;
  };

  this.countAroundWithValue = function(x, y, value)
  {
    var returnValue =
      this.countAroundWithValueHelper(x-1, y-1, value)+
      this.countAroundWithValueHelper(x-1, y  , value)+
      this.countAroundWithValueHelper(x-1, y+1, value)+
      this.countAroundWithValueHelper(x,   y-1, value)+
      this.countAroundWithValueHelper(x,   y+1, value)+
      this.countAroundWithValueHelper(x+1, y-1, value)+
      this.countAroundWithValueHelper(x+1, y  , value)+
      this.countAroundWithValueHelper(x+1, y+1, value);
    return returnValue;
  };

  this.countAroundWithFlagHelper = function(x, y, flag)
  {
    if
    (
      x >= 0 &&
      x < this.dimX &&
      y >= 0 &&
      y < this.dimY &&
      this.fields[x][y].flag == flag
    )
      return 1;
    return 0;
  };

  this.countAroundWithFlag = function(x, y, flag)
  {
    var returnValue =
      this.countAroundWithFlagHelper(x-1, y-1, flag)+
      this.countAroundWithFlagHelper(x-1, y  , flag)+
      this.countAroundWithFlagHelper(x-1, y+1, flag)+
      this.countAroundWithFlagHelper(x,   y-1, flag)+
      this.countAroundWithFlagHelper(x,   y+1, flag)+
      this.countAroundWithFlagHelper(x+1, y-1, flag)+
      this.countAroundWithFlagHelper(x+1, y  , flag)+
      this.countAroundWithFlagHelper(x+1, y+1, flag);
    return returnValue;
  };

  this.shuffle = function(initX, initY)
  {
    for(var n = 0; n < this.minesNumber; n++)
    {
      var x = undefined;
      var y = undefined;
      do
      {
        x = Math.floor(Math.random()*this.dimX);
        y = Math.floor(Math.random()*this.dimY);
      }
      while
      (
        (x == initX && y == initY) ||
        this.fields[x][y].value == this.ValueBomb
      );
      this.fields[x][y].value = this.ValueBomb;
    }
    for(var x = 0; x < this.dimX; x++)
      for(var y = 0; y < this.dimY; y++)
        if(this.fields[x][y].value != this.ValueBomb)
          this.fields[x][y].value = this.countAroundWithValue(x, y, this.ValueBomb);
    this.shuffled = true;
  };

  this.openHintDo = function(x, y)
  {
    if
    (
      x >= 0 &&
      x < this.dimX &&
      y >= 0 &&
      y < this.dimY &&
      this.fields[x][y].flag == this.FlagClose
    )
      this.open(x, y);
  };

  this.openHint = function(x, y)
  {
    if
    (
      this.fields[x][y].value == this.countAroundWithFlag(x, y, this.FlagMark) &&
      this.countAroundWithFlag(x, y, this.FlagClose) > 0
    )
    {
      this.openHintDo(x-1, y-1);
      this.openHintDo(x-1, y  );
      this.openHintDo(x-1, y+1);
      this.openHintDo(x,   y-1);
      this.openHintDo(x,   y+1);
      this.openHintDo(x+1, y-1);
      this.openHintDo(x+1, y  );
      this.openHintDo(x+1, y+1);
    }
  };

  this.openAllHelper = function(x, y)
  {
    if
    (
      x >= 0 &&
      x < this.dimX &&
      y >= 0 &&
      y < this.dimY &&
      this.fields[x][y].flag == this.FlagClose
    )
      this.openAll(x, y);
  };

  this.openAll = function(x, y)
  {
    this.fields[x][y].flag = this.FlagOpen;
    this.openedNumber++;
    this.haveAction = true;
    if(this.fields[x][y].value == 0)
    {
      this.openAllHelper(x-1, y-1);
      this.openAllHelper(x-1, y  );
      this.openAllHelper(x-1, y+1);
      this.openAllHelper(x,   y-1);
      this.openAllHelper(x,   y+1);
      this.openAllHelper(x+1, y-1);
      this.openAllHelper(x+1, y  );
      this.openAllHelper(x+1, y+1);
    }
  };

  this.open = function(x, y)
  {
    if(this.playable == true)
    {
      this.start();
      if(this.shuffled != true)
        this.shuffle(x, y);
      if(this.fields[x][y].flag == this.FlagOpen)
        this.openHint(x, y);
      else
      {
        if(this.fields[x][y].value == this.ValueBomb)
        {
          this.stop();
          this.fields[x][y].flag = this.FlagBoom;
          this.playable = false;
          this.boom = true;
        }
        else
        {
          this.openAll(x, y);
          if(this.openedNumber == this.dimX*this.dimY-this.minesNumber)
          {
            this.stop();
            this.playable = false;
          }
        }
      }
    }
  };

  this.markHintDo = function(x, y)
  {
    if
    (
      x >= 0 &&
      x < this.dimX &&
      y >= 0 &&
      y < this.dimY &&
      this.fields[x][y].flag == this.FlagClose
    )
      this.mark(x, y);
  };

  this.markHint = function(x, y)
  {
    if(this.countAroundWithFlag(x, y, this.FlagClose) == this.fields[x][y].value-this.countAroundWithFlag(x, y, this.FlagMark))
    {
      this.markHintDo(x-1, y-1);
      this.markHintDo(x-1, y  );
      this.markHintDo(x-1, y+1);
      this.markHintDo(x,   y-1);
      this.markHintDo(x,   y+1);
      this.markHintDo(x+1, y-1);
      this.markHintDo(x+1, y  );
      this.markHintDo(x+1, y+1);
    }
  };

  this.mark = function(x, y)
  {
    if(this.playable == true)
    {
      this.start();
      if(this.fields[x][y].flag == this.FlagOpen)
        this.markHint(x, y);
      else if(this.fields[x][y].flag != this.FlagClose)
      {
        this.fields[x][y].flag = this.FlagClose;
        this.minesRemain++;
      }
      else
      {
        this.fields[x][y].flag = this.FlagMark;
        this.minesRemain--;
        this.haveAction = true;
      }
    }
  };

  this.helpOpenRandom = function()
  {
    if(this.playable == true)
    {
      var x = undefined;
      var y = undefined;
      do
      {
        x = Math.floor(Math.random()*this.dimX);
        y = Math.floor(Math.random()*this.dimY);
      }
      while(this.fields[x][y].flag != this.FlagClose);
      this.open(x, y);
    }
  };

  this.helpMarkAll = function(onlyOne)
  {
    if(this.playable == true)
    {
      this.haveAction = false;
      for(var x = 0; x < this.dimX; x++)
        for(var y = 0; y < this.dimY; y++)
          if(this.fields[x][y].flag == this.FlagOpen)
          {
            this.markHint(x, y);
            if(onlyOne == true && this.haveAction == true)
              return;
          }
    }
  };

  this.helpOpenAll = function(onlyOne)
  {
    if(this.playable == true)
      do
      {
        this.haveAction = false;
        for(var x = 0; x < this.dimX; x++)
          for(var y = 0; y < this.dimY; y++)
            if(this.fields[x][y].flag == this.FlagOpen)
            {
              this.openHint(x, y);
              if(onlyOne == true && this.haveAction == true)
                return;
            }
      }
      while(this.haveAction == true)
  };

  this.helpPlay = function(doReset)
  {
    if(this.playable == true)
    {
      this.helpOpenAll();
      if(this.haveAction == true)
        return;
      this.helpMarkAll();
      if(this.haveAction == true)
        return;
      this.helpOpenRandom();
      return true;
    }
    if(doReset)
      this.reset();
    return false;
  };

  this.getPlayable = function()
  {
    return this.playable;
  };

  this.getBoom = function()
  {
    return this.boom;
  };

  this.getMinesRemain = function()
  {
    return this.minesRemain;
  };

  this.isStarted = function()
  {
    return this.startTime != undefined;
  };

  this.getTime = function()
  {
    if(this.startTime == undefined)
      return 0;
    var lastTime = this.stopTime;
    if(lastTime == undefined)
      lastTime = (new Date()).getTime();
    return lastTime-this.startTime;
  };

  this.reset();
}
