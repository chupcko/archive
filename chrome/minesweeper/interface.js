function interfaceClass(interfaceID, images, dimX, dimY, minesNumber)
{
  this.MinDimX = 2;
  this.MaxDimX = 100;
  this.MinDimY = 2;
  this.MaxDimY = 50;
  this.MinMinesNumber = 1;
  this.MinAutoPlaySleepTime = 1;
  this.MaxAutoPlaySleepTime = 5000;

  this.interfaceDOM = document.getElementById(interfaceID);
  this.images = images;
  this.dimX = dimX;
  this.dimY = dimY;
  this.minesNumber = minesNumber;

  this.fieldSize = this.images.getFieldSize();
  this.frameSize = this.images.getFrameSize();
  this.frameGrids = this.images.getFrameGrids();
  this.borderSize = this.frameSize*3;
  this.frame = this.images.getFrame();

  this.autoPlaySleepTime = 500;
  this.autoPlayTimer = undefined;

  this.timer = undefined;
  this.seconds = 0;

  this.init = function()
  {
    this.timerStop();
    this.autoPlayStop();

    this.inputDimXDOM.value = this.dimX;
    this.inputDimYDOM.value = this.dimY;
    this.inputMinesNumberDOM.value = this.minesNumber;

    this.game = new gameClass(this.dimX, this.dimY, this.minesNumber);
    this.canvasDOM.width = this.borderSize+this.frameSize+this.dimX*this.fieldSize+this.frameSize+this.borderSize;
    this.canvasDOM.height = this.borderSize+this.frameSize+this.dimY*this.fieldSize+this.frameSize+this.borderSize;
    this.seconds = 0;
    this.draw();
  };

  this.beginner = function()
  {
    this.dimX = 9;
    this.dimY = 9;
    this.minesNumber = 10;
    this.init();
  };

  this.intermediate = function()
  {
    this.dimX = 16;
    this.dimY = 16;
    this.minesNumber = 40;
    this.init();
  };

  this.expert = function()
  {
    this.dimX = 30;
    this.dimY = 16;
    this.minesNumber = 99;
    this.init();
  };

  this.custom = function()
  {
    this.dimX = parseInt(this.inputDimXDOM.value);
    if(isNaN(this.dimX))
      this.dimX = this.MinDimX;
    this.dimX = Math.max(this.dimX, this.MinDimX);
    this.dimX = Math.min(this.dimX, this.MaxDimX);

    this.dimY = parseInt(this.inputDimYDOM.value);
    if(isNaN(this.dimY))
      this.dimY = this.MinDimY;
    this.dimY = Math.max(this.dimY, this.MinDimY);
    this.dimY = Math.min(this.dimY, this.MaxDimY);

    this.minesNumber = parseInt(this.inputMinesNumberDOM.value);
    if(isNaN(this.minesNumber))
      this.minesNumber = this.MinMinesNumber;
    this.minesNumber = Math.max(this.minesNumber, this.MinMinesNumber);
    this.minesNumber = Math.min(this.minesNumber, this.dimX*this.dimY-1);

    this.init();
  };

  this.reset = function()
  {
    this.timerStop();
    this.autoPlayStop();
    this.game.reset();
    this.seconds = 0;
    this.draw();
  };

  this.undo = function()
  {
    this.timerStop();
    this.autoPlayStop();
    this.game.undo();
    this.timerStart();
    this.draw();
  };

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
    x -= this.canvasDOM.offsetLeft;
    y -= this.canvasDOM.offsetTop;
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

  this.canvasOpen = function(event)
  {
    var point = this.point(event);
    if(point != undefined)
    {
      this.timerStart();
      this.game.open(point.x, point.y);
      this.draw();
    }
    return false;
  };

  this.canvasMark = function(event)
  {
    var point = this.point(event);
    if(point != undefined)
    {
      this.timerStart();
      this.game.mark(point.x, point.y);
      this.draw();
    }
    event.preventDefault();
    return false;
  };

  this.keyPress = function(event)
  {
    switch(event.keyCode)
    {
      case 'a'.charCodeAt(0):
        this.autoPlay();
        break;
      case 'p'.charCodeAt(0):
        this.play();
        break;
      case 'r'.charCodeAt(0):
        this.reset();
        break;
      case 'u'.charCodeAt(0):
        this.undo();
        break;
    }
    return false;
  };

  this.openRandom = function()
  {
    this.timerStart();
    this.game.helpOpenRandom();
    this.draw();
  };

  this.markOne = function()
  {
    this.timerStart();
    this.game.helpMarkAll(true);
    this.draw();
  };

  this.openOne = function()
  {
    this.timerStart();
    this.game.helpOpenAll(true);
    this.draw();
  };

  this.markAll = function()
  {
    this.timerStart();
    this.game.helpMarkAll(false);
    this.draw();
  };

  this.openAll = function()
  {
    this.timerStart();
    this.game.helpOpenAll(false);
    this.draw();
  };

  this.play = function()
  {
    this.timerStart();
    if(this.game.helpPlay() != true)
    {
      this.timerStop();
      this.seconds = 0;
    }
    this.draw();
  };

  this.autoPlayStop = function()
  {
    if(this.autoPlayTimer != undefined)
    {
      clearInterval(this.autoPlayTimer)
      this.autoPlayTimer = undefined;
    }
  };

  this.autoPlay = function()
  {
    if(this.autoPlayTimer == undefined)
    {
      this.autoPlaySleepTime = parseInt(this.autoPlaySleepTimeDOM.value);
      if(isNaN(this.autoPlaySleepTime))
        this.autoPlaySleepTime = this.MinAutoPlaySleepTime;
      this.autoPlaySleepTime = Math.max(this.autoPlaySleepTime, this.MinAutoPlaySleepTime);
      this.autoPlaySleepTime = Math.min(this.autoPlaySleepTime, this.MaxAutoPlaySleepTime);
      this.autoPlaySleepTimeDOM.value = this.autoPlaySleepTime;
      this.autoPlayTimer = setInterval(this.play.bind(this), this.autoPlaySleepTime);
    }
    else
    {
      clearInterval(this.autoPlayTimer)
      this.autoPlayTimer = undefined;
    }
  };

  this.secondsIncrement = function()
  {
    this.seconds++;
    this.secondsDOM.value = this.seconds;
  };

  this.timerStop = function()
  {
    if(this.timer != undefined)
    {
      clearInterval(this.timer)
      this.timer = undefined;
    }
  };

  this.timerStart = function()
  {
    if(this.timer == undefined)
      this.timer = setInterval(this.secondsIncrement.bind(this), 1000);
  };

  this.draw = function()
  {
    this.minesRestNumberDOM.value = this.minesNumber-this.game.getMarkedNumber();
    this.secondsDOM.value = this.seconds;
    if(this.game.getPlayable() == true)
      this.canvasContext.fillStyle = 'rgb(75%, 75%, 75%)';
    else if(this.game.getBoom() == true)
    {
      this.timerStop();
      this.canvasContext.fillStyle = 'rgb(100%, 0%, 0%)';
    }
    else
    {
      this.timerStop();
      this.canvasContext.fillStyle = 'rgb(0%, 100%, 0%)';
    }
    this.canvasContext.fillRect(0, 0, this.canvasDOM.width, this.canvasDOM.height);
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

  var beginnerDOM = document.createElement('button');
  beginnerDOM.innerHTML = 'Beginner';
  beginnerDOM.addEventListener('click', this.beginner.bind(this));
  this.interfaceDOM.appendChild(beginnerDOM);

  this.interfaceDOM.appendChild(document.createTextNode(' '));
  var intermediateDOM = document.createElement('button');
  intermediateDOM.innerHTML = 'Intermediate';
  intermediateDOM.addEventListener('click', this.intermediate.bind(this));
  this.interfaceDOM.appendChild(intermediateDOM);

  this.interfaceDOM.appendChild(document.createTextNode(' '));
  var expertDOM = document.createElement('button');
  expertDOM.innerHTML = 'Expert';
  expertDOM.addEventListener('click', this.expert.bind(this));
  this.interfaceDOM.appendChild(expertDOM);

  this.interfaceDOM.appendChild(document.createTextNode(' DimX: '));
  this.inputDimXDOM = document.createElement('input');
  this.inputDimXDOM.value = this.dimX;
  this.inputDimXDOM.className = 'inputText';
  this.interfaceDOM.appendChild(this.inputDimXDOM);

  this.interfaceDOM.appendChild(document.createTextNode(' DimY: '));
  this.inputDimYDOM = document.createElement('input');
  this.inputDimYDOM.value = this.dimY;
  this.inputDimYDOM.className = 'inputText';
  this.interfaceDOM.appendChild(this.inputDimYDOM);

  this.interfaceDOM.appendChild(document.createTextNode(' Mines: '));
  this.inputMinesNumberDOM = document.createElement('input');
  this.inputMinesNumberDOM.value = this.minesNumber;
  this.inputMinesNumberDOM.className = 'inputText';
  this.interfaceDOM.appendChild(this.inputMinesNumberDOM);

  this.interfaceDOM.appendChild(document.createTextNode(' '));
  var customDOM = document.createElement('button');
  customDOM.innerHTML = 'Custom';
  customDOM.addEventListener('click', this.custom.bind(this));
  this.interfaceDOM.appendChild(customDOM);

  this.interfaceDOM.appendChild(document.createElement('p'));
  var openRandomDOM = document.createElement('button');
  openRandomDOM.innerHTML = 'Open Random';
  openRandomDOM.addEventListener('click', this.openRandom.bind(this));
  this.interfaceDOM.appendChild(openRandomDOM);

  this.interfaceDOM.appendChild(document.createTextNode(' '));
  var markOneDOM = document.createElement('button');
  markOneDOM.innerHTML = 'Mark One';
  markOneDOM.addEventListener('click', this.markOne.bind(this));
  this.interfaceDOM.appendChild(markOneDOM);

  this.interfaceDOM.appendChild(document.createTextNode(' '));
  var openOneDOM = document.createElement('button');
  openOneDOM.innerHTML = 'Open One';
  openOneDOM.addEventListener('click', this.openOne.bind(this));
  this.interfaceDOM.appendChild(openOneDOM);

  this.interfaceDOM.appendChild(document.createTextNode(' '));
  var markAllDOM = document.createElement('button');
  markAllDOM.innerHTML = 'Mark All';
  markAllDOM.addEventListener('click', this.markAll.bind(this));
  this.interfaceDOM.appendChild(markAllDOM);

  this.interfaceDOM.appendChild(document.createTextNode(' '));
  var openAllDOM = document.createElement('button');
  openAllDOM.innerHTML = 'Open All';
  openAllDOM.addEventListener('click', this.openAll.bind(this));
  this.interfaceDOM.appendChild(openAllDOM);

  this.interfaceDOM.appendChild(document.createTextNode(' '));
  var playDOM = document.createElement('button');
  playDOM.innerHTML = 'Play';
  playDOM.addEventListener('click', this.play.bind(this));
  this.interfaceDOM.appendChild(playDOM);

  this.interfaceDOM.appendChild(document.createTextNode(' Auto Play Sleep Time (ms): '));
  this.autoPlaySleepTimeDOM = document.createElement('input');
  this.autoPlaySleepTimeDOM.value = this.autoPlaySleepTime;
  this.autoPlaySleepTimeDOM.className = 'inputText';
  this.interfaceDOM.appendChild(this.autoPlaySleepTimeDOM);

  this.interfaceDOM.appendChild(document.createTextNode(' '));
  var autoPlayDOM = document.createElement('button');
  autoPlayDOM.innerHTML = 'Auto Play Start/Stop';
  autoPlayDOM.addEventListener('click', this.autoPlay.bind(this));
  this.interfaceDOM.appendChild(autoPlayDOM);

  this.interfaceDOM.appendChild(document.createElement('p'));
  this.minesRestNumberDOM = document.createElement('input');
  this.minesRestNumberDOM.value = this.minesNumber;
  this.minesRestNumberDOM.className = 'inputText';
  this.minesRestNumberDOM.disabled = 'disabled';
  this.interfaceDOM.appendChild(this.minesRestNumberDOM);

  this.interfaceDOM.appendChild(document.createTextNode(' '));
  var newDOM = document.createElement('button');
  newDOM.innerHTML = 'New';
  newDOM.addEventListener('click', this.reset.bind(this));
  this.interfaceDOM.appendChild(newDOM);

  this.interfaceDOM.appendChild(document.createTextNode(' '));
  this.secondsDOM = document.createElement('input');
  this.secondsDOM.value = this.seconds;
  this.secondsDOM.className = 'inputText';
  this.secondsDOM.disabled = 'disabled';
  this.interfaceDOM.appendChild(this.secondsDOM);

  this.interfaceDOM.appendChild(document.createElement('p'));
  this.canvasDOM = document.createElement('canvas');
  this.canvasDOM.addEventListener('click', this.canvasOpen.bind(this), false);
  this.canvasDOM.addEventListener('contextmenu', this.canvasMark.bind(this), false);
  this.canvasContext = this.canvasDOM.getContext('2d');
  this.interfaceDOM.appendChild(this.canvasDOM);

  this.init();
}
