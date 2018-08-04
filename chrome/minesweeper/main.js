var Images = undefined;
var Interface = undefined;

function init()
{
  Images = new imagesClass();
  Images.whenLoad(initFinish);
}

function initFinish()
{
  Interface = new interfaceClass('interface', Images, 9, 9, 10);
  document.getElementById('body').addEventListener('keypress', Interface.keyPress.bind(Interface));
}

document.addEventListener('DOMContentLoaded', init);
