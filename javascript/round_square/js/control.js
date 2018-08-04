function ControlClass(name, square, divName)
{
  this.name = name;
  this.square = square;
  this.divName = divName;

  this.div = document.getElementById(this.divName);
  this.div.innerHTML =
    '<form onsubmit="'+this.name+'.set(); return false;">\n'+
    '<table>\n'+
    '  <tr>\n'+
    '    <td><label for="'+this.name+'_expression">Expression:</label></td>\n'+
    '    <td><input type="text" value="0" id="'+this.name+'_expression"/></td>\n'+
    '  </tr>\n'+
    '  <tr>\n'+
    '    <td><label for="'+this.name+'_step">Step:</label></td>\n'+
    '    <td><input type="text" value="1" id="'+this.name+'_step"/></td>\n'+
    '  </tr>\n'+
    '  <tr>\n'+
    '    <td>&nbsp;</td>\n'+
    '    <td><input type="submit" value="Set"/></td>\n'+
    '  </tr>\n'+
    '  <tr>\n'+
    '    <td><label for="'+this.name+'_run">Run:</label></td>\n'+
    '    <td><input type="checkbox" id="'+this.name+'_run" onchange="'+this.name+'.run(); return false;"/></td>\n'+
    '  </tr>\n'+
    '  <tr>\n'+
    '    <td><label for="'+this.name+'_lines">Lines:</label></td>\n'+
    '    <td><input type="checkbox" id="'+this.name+'_lines" onchange="'+this.name+'.linesToggle(); return false;"/></td>\n'+
    '  </tr>\n'+
    '</table>\n'+
    '</form>\n'+
    '<p/>\n'+
    'Examples:<br/>\n'+
    '<span class="link" onclick="'+this.name+'.fill(\'x+y\', \'1\'); return false;">x+y, 1</span><br/>\n'+
    '<span class="link" onclick="'+this.name+'.fill(\'x+y\', \'Math.abs(x+y)%2*2-1\'); return false;">x+y, Math.abs(x+y)%2*2-1</span><br/>\n'+
    '<span class="link" onclick="'+this.name+'.fill(\'x*y\', \'1\'); return false;">x*y, 1</span><br/>\n'+
    '<span class="link" onclick="'+this.name+'.fill(\'x*x+y*y\', \'1\'); return false;">x*x+y*y, 1</span><br/>\n'+
    '<span class="link" onclick="'+this.name+'.fill(\'x*x-y*y\', \'1\'); return false;">x*x-y*y, 1</span><br/>\n'+
    '<span class="link" onclick="'+this.name+'.fill(\'x^y\', \'1\'); return false;">x^y, 1</span><br/>\n'+
    '<span class="link" onclick="'+this.name+'.fill(\'0\', \'(x*x+y*y)>102 ?1:-1\'); return false;">0, (x*x+y*y)>102 ?1:-1</span><br/>\n'+
    '';

  this.set = function()
  {
    this.square.set
    (
      document.getElementById(this.name+'_expression').value,
      document.getElementById(this.name+'_step').value
    );
  };

  this.run = function()
  {
    this.square.run();
  };

  this.linesToggle = function()
  {
    this.square.linesToggle();
  };

  this.fill = function(expression, step)
  {
    document.getElementById(this.name+'_expression').value = expression;
    document.getElementById(this.name+'_step').value = step;
    this.square.set(expression, step);
  }

  window[this.name] = this;
}
