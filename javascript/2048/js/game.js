function gameClass()
{
  this.MinDimension = 2;
  this.MaxDimension = 10;
  this.DefaultDimension = 4;
  this.dimension = this.DefaultDimension;

  this.MinFuzzy = 0.0;
  this.MaxFuzzy = 1.0;
  this.DefaultFuzzy = 0.1;
  this.fuzzy = this.DefaultFuzzy;

  this.playable = undefined;
  this.count = undefined;
  this.fields = undefined;

  this.DirectionUp = 0;
  this.DirectionDown = 1;
  this.DirectionLeft = 2;
  this.DirectionRight = 3;

  this.setDimension = function(value)
  {
    if(isNaN(value))
      value = this.MinDimension;
    if(value < this.MinDimension)
      value = this.MinDimension;
    if(value > this.MaxDimension)
      value = this.MaxDimension;
    this.dimension = value;
    this.reset();
  };

  this.setFuzzy = function(value)
  {
    if(isNaN(value))
      value = this.DefaultFuzzy;
    if(value < this.MinFuzzy)
      value = this.MinFuzzy;
    if(value > this.MaxFuzzy)
      value = this.MaxFuzzy;
    this.fuzzy = value;
  };

  this.checkPlayable = function()
  {
    if(this.count == 0)
    {
      for(var x = 0; x < this.dimension-1; x++)
        for(var y = 0; y < this.dimension-1; y++)
          if
          (
            this.fields[x][y] == this.fields[x][y+1] ||
            this.fields[x][y] == this.fields[x+1][y]
          )
            return;
      for(var n = 0; n < this.dimension-1; n++)
        if
        (
          this.fields[this.dimension-1][n] == this.fields[this.dimension-1][n+1] ||
          this.fields[n][this.dimension-1] == this.fields[n+1][this.dimension-1]
        )
          return;
      this.playable = false;
    }
  };

  this.add = function()
  {
    var index = Math.floor(Math.random()*(this.count));
    for(var x = 0; x < this.dimension; x++)
      for(var y = 0; y < this.dimension; y++)
        if(this.fields[x][y] == 0)
        {
          if(index == 0)
          {
            this.fields[x][y] = 2;
            if(Math.random() < this.fuzzy)
              this.fields[x][y] += 2;
            this.count--;
            this.checkPlayable();
            return;
          }
          index--;
        }
  };

  this.reset = function()
  {
    this.playable = true;
    this.count = 0;
    this.fields = Array();
    for(var x = 0; x < this.dimension; x++)
    {
      this.fields[x] = Array();
      for(var y = 0; y < this.dimension; y++)
      {
        this.fields[x][y] = 0;
        this.count++;
      }
    }
    this.add();
    this.add();
  };

  this.directionX = function(direction, x, y)
  {
    switch(direction)
    {
      case this.DirectionUp:
        return x;
        break;
      case this.DirectionDown:
        return this.dimension-1-x;
        break;
      case this.DirectionLeft:
        return y;
        break;
      case this.DirectionRight:
        return this.dimension-1-y;
        break;
    }
  };

  this.directionY = function(direction, x, y)
  {
    switch(direction)
    {
      case this.DirectionUp:
        return y;
        break;
      case this.DirectionDown:
        return this.dimension-1-y;
        break;
      case this.DirectionLeft:
        return x;
        break;
      case this.DirectionRight:
        return this.dimension-1-x;
        break;
    }
  };

  this.getField = function(direction, x, y)
  {
    return this.fields[this.directionX(direction, x, y)][this.directionY(direction, x, y)];
  };

  this.setField = function(direction, x, y, value)
  {
    this.fields[this.directionX(direction, x, y)][this.directionY(direction, x, y)] = value;
  };

  this.gravity = function(direction)
  {
    var changes = 0;
    for(var x = 0; x < this.dimension; x++)
      for(var n = this.dimension-1; n > 0; n--)
        for(var y = 0; y < n; y++)
          if
          (
            this.getField(direction, x, y) == 0 &&
            this.getField(direction, x, y+1) > 0
          )
          {
            changes++;
            this.setField(direction, x, y, this.getField(direction, x, y+1));
            this.setField(direction, x, y+1, 0);
          }
    return changes;
  };

  this.summarize = function(direction)
  {
    var changes = 0;
    for(var x = 0; x < this.dimension; x++)
      for(var y = 0; y < this.dimension-1; y++)
        if
        (
          this.getField(direction, x, y) > 0 &&
          this.getField(direction, x, y) == this.getField(direction, x, y+1)
        )
        {
          changes++;
          this.setField(direction, x, y, this.getField(direction, x, y)+this.getField(direction, x, y+1));
          this.setField(direction, x, y+1, 0);
          this.count++;
        }
    return changes;
  };

  this.move = function(direction)
  {
    if(this.playable == true)
    {
      if(this.gravity(direction)+this.summarize(direction)+this.gravity(direction) > 0)
        this.add();
    }
  };

  this.moveUp = function()
  {
    this.move(this.DirectionUp);
  };

  this.moveDown = function()
  {
    this.move(this.DirectionDown);
  };

  this.moveLeft = function()
  {
    this.move(this.DirectionLeft);
  };

  this.moveRight = function()
  {
    this.move(this.DirectionRight);
  };

  this.html = function()
  {
    var html = '';
    if(this.playable != true)
      html +=
        'Game Over'+
        '<br/>';
    html += '<table border="1">';
    for(var y = 0; y < this.dimension; y++)
    {
      html += '<tr>';
      for(var x = 0; x < this.dimension; x++)
        html += '<td>'+this.fields[x][y]+'</td>'
      html += '</tr>';
    }
    html += '</table>';
    return html;
  };

  this.reset();
}
