function GameClass(dimension)
{
  if(dimension < 2)
    dimension = 2;

  this.dimension = dimension;

  this.FlagEmpty = 0;
  this.FlagRed = 1;
  this.FlagBlue = 2;

  this.autoPlayAsRed = undefined;
  this.status = undefined;
  this.next = undefined;
  this.bigFlags = undefined;
  this.smallFlags = undefined;
  this.connectionsSize = undefined;
  this.connectionsRed = undefined;
  this.connectionsBlue = undefined;

  this.new = function()
  {
    this.autoPlayAsRed = false;
    this.status = this.FlagEmpty;
    this.next = this.FlagRed;
    this.bigFlags = [];
    for(var x = 0; x < this.dimension; x++)
    {
      this.bigFlags[x] = [];
      for(var y = 0; y < this.dimension; y++)
        this.bigFlags[x][y] = this.FlagEmpty;
    }
    this.smallFlags = [];
    for(var x = 0; x < this.dimension-1; x++)
    {
      this.smallFlags[x] = [];
      for(var y = 0; y < this.dimension-1; y++)
        this.smallFlags[x][y] = this.FlagEmpty;
    }
    this.connectionsSize = this.dimension*(this.dimension+1);
    this.connectionsRed = [];
    this.connectionsBlue = [];
    for(var x = 0; x < this.connectionsSize; x++)
    {
      this.connectionsRed[x] = [];
      this.connectionsBlue[x] = [];
      for(var y = 0; y < this.connectionsSize; y++)
      {
        this.connectionsRed[x][y] = false;
        this.connectionsBlue[x][y] = false;
      }
    }
    for(var i = 0; i < this.dimension-1; i++)
    {
      this.connectRed(i, i+1);
      this.connectRed(this.connectionsSize-i-1, this.connectionsSize-i-2);
      this.connectBlue(i, i+1);
      this.connectBlue(this.connectionsSize-i-1, this.connectionsSize-i-2);
    }
  };

  this.connectRed = function(x, y)
  {
    this.connectionsRed[x][y] = true;
    this.connectionsRed[y][x] = true;
  };

  this.connectBlue = function(x, y)
  {
    this.connectionsBlue[x][y] = true;
    this.connectionsBlue[y][x] = true;
  };

  this.beatMe = function()
  {
    this.new();
    this.autoPlayAsRed = true;
    var player = this.next;
    this.play(0, 0);
    return { player: player, x: 0, y: 0 };
  };

  this.play = function(x, y)
  {
    if
    (
      this.status != this.FlagEmpty ||
      x < 0 ||
      x >= this.dimension*2-1 ||
      y < 0 ||
      y >= this.dimension*2-1 ||
      x%2 != y%2
    )
      return undefined;
    var xr = (x/2)|0;
    var yr = (y/2)|0;
    if(x%2 == 0)
    {
      if(this.bigFlags[xr][yr] != this.FlagEmpty)
        return undefined;
      this.bigFlags[xr][yr] = this.next;
      switch(this.next)
      {
        case this.FlagRed:
          this.connectRed(yr*this.dimension+xr, (yr+1)*this.dimension+xr);
          break;
        case this.FlagBlue:
          this.connectBlue(xr*this.dimension+yr, (xr+1)*this.dimension+yr);
          break;
      }
    }
    else
    {
      if(this.smallFlags[xr][yr] != this.FlagEmpty)
        return undefined;
      this.smallFlags[xr][yr] = this.next;
      switch(this.next)
      {
        case this.FlagRed:
          this.connectRed((yr+1)*this.dimension+xr, (yr+1)*this.dimension+xr+1);
          break;
        case this.FlagBlue:
          this.connectBlue((xr+1)*this.dimension+yr, (xr+1)*this.dimension+yr+1);
          break;
      }
    }
    this.calculateStatus();
    this.calculateNext();
    if(this.autoPlayAsRed && this.next == this.FlagRed)
    {
      var autoMove = this.calculateAutoMove(x, y);
      autoMove.player = this.next;
      this.play(autoMove.x, autoMove.y);
      return autoMove;
    }
    return undefined;
  };

  this.calculateStatus = function()
  {
    var visited = [];
    for(var i = 0; i < this.connectionsSize; i++)
      visited[i] = false;
    switch(this.next)
    {
      case this.FlagRed:
        if(this.reachRed(0, visited))
          this.status = this.FlagRed;
        break;
      case this.FlagBlue:
        if(this.reachBlue(0, visited))
          this.status = this.FlagBlue;
        break;
    }
  };

  this.reachRed = function(node, visited)
  {
    if(node == this.connectionsSize-1)
      return true;
    visited[node] = true;
    for(var i = 0; i < this.connectionsSize; i++)
      if(!visited[i] && this.connectionsRed[node][i])
        if(this.reachRed(i, visited))
          return true;
    return false;
  };

  this.reachBlue = function(node, visited)
  {
    if(node == this.connectionsSize-1)
      return true;
    visited[node] = true;
    for(var i = 0; i < this.connectionsSize; i++)
      if(!visited[i] && this.connectionsBlue[node][i])
        if(this.reachBlue(i, visited))
          return true;
    return false;
  };

  this.calculateNext = function()
  {
    switch(this.next)
    {
      case this.FlagRed:
        this.next = this.FlagBlue;
        break;
      case this.FlagBlue:
        this.next = this.FlagRed;
        break;
    }
  };

  this.calculateAutoMove = function(x, y)
  {
    if(x%2 == 0)
    {
      if(x == y)
        return { x: x-2, y: y };
      if(x+2 == y)
        return { x: x+2, y: y };
      if(x >= y)
        return { x: x-1, y: y+1 };
      else
        return { x: x+1, y: y-1 };
    }
    else
      if(x >= y)
        return { x: x+1, y: y-1 };
      else
        return { x: x-1, y: y+1 };
  };

  this.isPlayable = function(x, y)
  {
    if
    (
      this.status != this.FlagEmpty ||
      x < 0 ||
      x >= this.dimension*2-1 ||
      y < 0 ||
      y >= this.dimension*2-1 ||
      x%2 != y%2
    )
      return false;
    if(x%2 == 0)
      return this.bigFlags[(x/2)|0][(y/2)|0] == this.FlagEmpty;
    else
      return this.smallFlags[(x/2)|0][(y/2)|0] == this.FlagEmpty;
  };

  this.getStatusString = function()
  {
    switch(this.status)
    {
      case this.FlagEmpty:
        switch(this.next)
        {
          case this.FlagRed:
            return 'Red play next';
            break;
          case this.FlagBlue:
            return 'Blue play next';
            break;
        }
        break;
      case this.FlagRed:
        return 'Red win';
        break;
      case this.FlagBlue:
        return 'Blue win';
        break;
    }
    return '';
  };

  this.haveRedVertical = function(x, y)
  {
    if
    (
      x < 0 ||
      x >= this.dimension ||
      y < 0 ||
      y >= this.dimension
    )
      return false;
    if(this.bigFlags[x][y] == this.FlagRed)
      return true;
    return false;
  };

  this.haveRedHorizontal = function(x, y)
  {
    if
    (
      x < 0 ||
      x >= this.dimension-1 ||
      y < 0 ||
      y >= this.dimension+1
    )
      return false;
    if
    (
      y == 0 ||
      y == this.dimension
    )
      return true;
    if(this.smallFlags[x][y-1] == this.FlagRed)
      return true;
    return false;
  };

  this.haveBlueHorizontal = function(x, y)
  {
    if
    (
      x < 0 ||
      x >= this.dimension ||
      y < 0 ||
      y >= this.dimension
    )
      return false;
    if(this.bigFlags[x][y] == this.FlagBlue)
      return true;
    return false;
  };

  this.haveBlueVertical = function(x, y)
  {
    if
    (
      x < 0 ||
      x >= this.dimension+1 ||
      y < 0 ||
      y >= this.dimension-1
    )
      return false;
    if
    (
      x == 0 ||
      x == this.dimension
    )
      return true;
    if(this.smallFlags[x-1][y] == this.FlagBlue)
      return true;
    return false;
  };

  this.new();
}
