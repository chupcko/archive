function GCAControlClass(name, gca, divName)
{
  this.name = name;
  this.gca = gca;
  this.divName = divName;


  this.parameter = function(name, label, values)
  {
    var text =
      '  <tr>\n'+
      '    <td><label for="'+this.name+name+'">'+label+':</label></td>\n'+
      '    <td><input type="text" value="'+values[0]+'" id="'+this.name+name+'"/></td>\n'+
      '    <td>\n'+
      '      <select id="'+this.name+'_select'+name+'" onchange="return '+this.name+'.put(\''+name+'\');">\n'+
      '';
   for(var i = 0; i < values.length; i++)
     text += '      <option value="'+values[i]+'">'+values[i]+'</option>\n';
   text +=
      '      </select>\n'+
      '    </td>\n'+
      '  </tr>\n'+
      '';
    return text;
  };

  this.div = document.getElementById(this.divName);
  this.div.innerHTML =
    '<form onsubmit="'+this.name+'.set(); return false;">\n'+
    '<table>\n'+
    this.parameter
    (
      '_modulo',
      'N',
      [
        64,
        2
      ]
    )+
    this.parameter
    (
      '_normalize',
      'Normalize(N, v)',
      [
        'v%N',
        'v < 0 ? 0 : v >= N ? N-1 : v'
      ]
    )+
    this.parameter
    (
      '_left',
      'Left(N, X, Y, y)',
      [
        '0',
        'N-1'
      ]
    )+
    this.parameter
    (
      '_first',
      'First(N, X, Y, x, y)',
      [
        'x == 1 ? N-1 : 0',
        'Math.floor(Math.random()*N)'
      ]
    )+
    this.parameter
    (
      '_right',
      'Right(N, X, Y, y)',
      [
        '0',
        'N-1'
      ]
    )+
    this.parameter
    (
      '_next',
      'Next(N, X, Y, x, y, a, b, c)',
      [
        'a+b+c',
        'b^c',
        '(a+b+c)/3'
      ]
    )+
    '  <tr>\n'+
    '    <td>&nbsp;</td>\n'+
    '    <td><input type="submit" value="Set"/></td>\n'+
    '    <td>&nbsp;</td>\n'+
    '  </tr>\n'+
    '</table>\n'+
    '</form>\n'+
    '';

  this.put = function(name)
  {
    document.getElementById(this.name+name).value = document.getElementById(this.name+'_select'+name).value;
    return false;
  };

  this.set = function()
  {
    this.gca.set
    (
      document.getElementById(this.name+'_modulo').value,
      document.getElementById(this.name+'_normalize').value,
      document.getElementById(this.name+'_left').value,
      document.getElementById(this.name+'_first').value,
      document.getElementById(this.name+'_right').value,
      document.getElementById(this.name+'_next').value
    );
  };

  window[this.name] = this;
}
