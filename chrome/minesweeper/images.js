function imagesClass()
{
  this.data =
  [
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    'close',
    'mark',
    'boom',
    'bomb',
    'not',
    'frame'
  ];
  this.image = new Array();
  for(var i = 0; i < this.data.length; i++)
  {
    this.image[i] = new Image()
    this.image[i].src = 'images/'+this.data[i]+'.png';
  }
  this.frameIndex = this.data.length-1;
  this.frameGrids = 5;

  this.getFieldSize = function()
  {
    return this.image[0].naturalWidth;
  };

  this.getFrameSize = function()
  {
    return this.image[this.frameIndex].naturalWidth/this.frameGrids;
  };

  this.getFrameGrids = function()
  {
    return this.frameGrids;
  };

  this.getImage = function(i)
  {
    return this.image[i];
  };

  this.getFrame = function()
  {
    return this.image[this.frameIndex];
  };

  this.isLoaded = function()
  {
    for(var i = 0; i < this.data.length; i++)
      if
      (
        this.image[i].complete == false ||
        (this.image[i].naturalWidth != undefined && this.image[i].naturalWidth == 0)
      )
        return false;
    return true;
  };

  this.whenLoadTimeout = undefined;
  this.whenLoadPass = false;
  this.whenLoad = function(finish)
  {
    if(this.whenLoadPass == true)
      return;
    if(this.isLoaded() == true)
    {
      if(this.whenLoadTimeout != undefined)
        clearTimeout(this.whenLoadTimeout);
      finish();
      this.whenLoadPass = true;
      return;
    }
    this.whenLoadTimeout = setTimeout(this.whenLoad.bind(this, finish), 100);
  };
}
