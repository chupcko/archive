var Images = undefined;
var Box = undefined;

function init()
{
  Images = new imagesClass();
  Images.whenLoad
  (
    function()
    {
      initFinish();
    }
  );
}

var MinDimX = 2;
var MaxDimX = 100;
var MinDimY = 2;
var MaxDimY = 40;
var MinMinesNumber = 1;
var MinDelay = 10;
var MaxDelay = 5000;

function initFinish()
{
  var dimX = parseInt(document.getElementById('dimX').value);
  var dimY = parseInt(document.getElementById('dimY').value);
  var minesNumber = parseInt(document.getElementById('minesNumber').value);
  if(isNaN(dimX))
    dimX = MinDimX;
  dimX = Math.max(dimX, MinDimX);
  dimX = Math.min(dimX, MaxDimX);
  if(isNaN(dimY))
    dimY = MinDimY;
  dimY = Math.max(dimY, MinDimY);
  dimY = Math.min(dimY, MaxDimY);
  if(isNaN(minesNumber))
    minesNumber = MinMinesNumber;
  minesNumber = Math.max(minesNumber, MinMinesNumber);
  minesNumber = Math.min(minesNumber, dimX*dimY-1);
  initNew(dimX, dimY, minesNumber);
}

function initNew(dimX, dimY, minesNumber)
{
  document.getElementById('dimX').value = dimX;
  document.getElementById('dimY').value = dimY;
  document.getElementById('minesNumber').value = minesNumber;
  if(Box != undefined)
    Box.destroy();
  Box = new boxClass('box', 'time', 'mines', Images, dimX, dimY, minesNumber);
}

function autoPlayStartStop()
{
  var delay = parseInt(document.getElementById('delay').value);
  if(isNaN(delay))
    delay = MinTime;
  delay = Math.max(delay, MinDelay);
  delay = Math.min(delay, MaxDelay);
  document.getElementById('delay').value = delay;
  Box.autoPlaySetDelay(delay);
  Box.autoPlayStartStop();
}
