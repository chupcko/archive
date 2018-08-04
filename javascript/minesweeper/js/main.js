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
var MinTime = 10;
var MaxTime = 5000;

function initFinish()
{
  if(Box != undefined)
    Box.autoPlayStop();
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
  document.getElementById('dimX').value = dimX;
  document.getElementById('dimY').value = dimY;
  document.getElementById('minesNumber').value = minesNumber;
  Box = new boxClass('box', Images, dimX, dimY, minesNumber);
}

function autoPlayStartStop()
{
  var time = parseInt(document.getElementById('time').value);
  if(isNaN(time))
    time = MinTime;
  time = Math.max(time, MinTime);
  time = Math.min(time, MaxTime);
  document.getElementById('time').value = time;
  Box.autoPlaySetTime(time);
  Box.autoPlayStartStop();
}
