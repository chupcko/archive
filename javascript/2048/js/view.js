function viewClass(name, divId)
{
  this.name = name;
  this.divId = divId;

  this.div = document.getElementById(this.divId);

  this.game = new gameClass();

  this.draw = function()
  {
    this.div.innerHTML =
      this.game.html()+
      'Dimension: <input type="text" id="'+this.name+'Dimension" value="'+this.game.dimension+'" onchange="'+this.name+'.setDimension(); return false;"/> '+
      'Fuzzy: <input type="text" id="'+this.name+'Fuzzy" value="'+this.game.fuzzy.toFixed(1)+'" onchange="'+this.name+'.setFuzzy(); return false;"/>'+
      '<br/>'+
      '<input type="submit" value="RESET" onclick="'+this.name+'.reset(); return false;"/> '+
      '<input type="submit" value="UP" onclick="'+this.name+'.moveUp(); return false;"/> '+
      '<input type="submit" value="DOWN" onclick="'+this.name+'.moveDown(); return false;"/> '+
      '<input type="submit" value="LEFT" onclick="'+this.name+'.moveLeft(); return false;"/> '+
      '<input type="submit" value="RIGHT" onclick="'+this.name+'.moveRight(); return false;"/>';
  };

  this.setDimension = function()
  {
    this.game.setDimension(parseInt(document.getElementById(this.name+'Dimension').value));
    this.draw();
  };

  this.setFuzzy = function()
  {
    this.game.setFuzzy(parseFloat(document.getElementById(this.name+'Fuzzy').value));
    this.draw();
  };

  this.reset = function()
  {
    this.game.reset();
    this.draw();
  };

  this.moveUp = function()
  {
    this.game.moveUp();
    this.draw();
  };

  this.moveDown = function()
  {
    this.game.moveDown();
    this.draw();
  };

  this.moveLeft = function()
  {
    this.game.moveLeft();
    this.draw();
  };

  this.moveRight = function()
  {
    this.game.moveRight();
    this.draw();
  };

  window[this.name] = this;
  this.draw();
}
