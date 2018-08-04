function Counter(drawID, initial)
{
  if(initial == undefined)
    initial = 0;
  this.count = initial;

  this.redraw = function()
  {
    this.counterDOM.innerHTML = this.count;
  };

  this.reset = function()
  {
    this.count = 0;
    this.redraw();
  };

  this.increment = function()
  {
    this.count++;
    this.redraw();
  };

  var drawDOM = document.getElementById(drawID);

  var resetDOM = document.createElement('button');
  resetDOM.innerHTML = 'Reset';
  resetDOM.addEventListener('click', this.reset.bind(this));
  drawDOM.appendChild(resetDOM);

  drawDOM.appendChild(document.createTextNode(' '));

  var incrementDOM = document.createElement('button');
  incrementDOM.innerHTML = 'Increment';
  incrementDOM.addEventListener('click', this.increment.bind(this));
  drawDOM.appendChild(incrementDOM);

  drawDOM.appendChild(document.createTextNode(' Value: '));

  this.counterDOM = document.createElement('span');
  this.redraw();
  drawDOM.appendChild(this.counterDOM);
}

function init()
{
  var c1 = new Counter('d1');
  c1.increment();

  var c2 = new Counter('d2', 1);
  c2.increment();
  c2.increment();

  var c3 = new Counter('d3', 2);
  c3.increment();
  c3.increment();
  c3.increment();
}

document.addEventListener('DOMContentLoaded', init);
