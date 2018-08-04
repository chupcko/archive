function ChordsClass(name, divName)
{
  this.name = name;
  this.divName = divName;

  this.Notes = Array
  (
    'A',
    'A#/Bb',
    'B',
    'C',
    'C#/Db',
    'D',
    'D#/Eb',
    'E',
    'F',
    'F#/Gb',
    'G',
    'G#/Ab'
  );
  this.FretsNumber = this.Notes.length*2;
  this.FretsMark = Array
  (
    0,
    5,
    7
  );
  this.Class = Array
  (
    {
      name: 'sus2',
      offset: 2
    },
    {
      name: 'min',
      offset: 3
    },
    {
      name: 'maj',
      offset: 4
    },
    {
      name: 'sus4',
      offset: 5
    }
  );
  this.End = Array
  (
    {
      name: '-5',
      offset: 6
    },
    {
      name: '5',
      offset: 7
    },
    {
      name: '5+',
      offset: 8
    }
  );
  this.Suffix = Array
  (
    {
      name: '',
      offset: 0
    },
    {
      name: '6',
      offset: 9
    },
    {
      name: '7',
      offset: 10
    },
    {
      name: 'maj7',
      offset: 11
    },
    {
      name: '9',
      offset: 1
    },
    {
      name: '-9',
      offset: 2
    },
    {
      name: '11',
      offset: 5
    },
    {
      name: '13',
      offset: 9
    }
  );

  this.selectedKey = 3;
  this.selectedClass = 2;
  this.selectedEnd = 1;
  this.selectedSuffix1 = 0;
  this.selectedSuffix2 = 0;
  this.selectedSuffix3 = 0;

  this.strings = Array
  (
    7,
    2,
    10,
    5,
    0,
    7
  );

  this.fretsText = Array();

  this.normalizeSuffixes = function()
  {
    /* ako ima i 6 i 13 skini 13, ako je sus4 i ima 11 skini 11, ako je sus2 i ima 9 skini 9 */
    if(this.selectedSuffix1 == this.selectedSuffix2)
      this.selectedSuffix2 = 0;
    if
    (
      this.selectedSuffix1 == this.selectedSuffix3 ||
      this.selectedSuffix2 == this.selectedSuffix3
    )
      this.selectedSuffix3 = 0;
    if(this.selectedSuffix1 > this.selectedSuffix2)
    {
      var tmp = this.selectedSuffix1;
      this.selectedSuffix1 = this.selectedSuffix2;
      this.selectedSuffix2 = tmp;
    }
    if(this.selectedSuffix2 > this.selectedSuffix3)
    {
      var tmp = this.selectedSuffix2;
      this.selectedSuffix2 = this.selectedSuffix3;
      this.selectedSuffix3 = tmp;
      if(this.selectedSuffix1 > this.selectedSuffix2)
      {
        var tmp = this.selectedSuffix1;
        this.selectedSuffix1 = this.selectedSuffix2;
        this.selectedSuffix2 = tmp;
      }
    }
    if(this.selectedSuffix2 == 0)
    {
      this.selectedSuffix2 = this.selectedSuffix3;
      this.selectedSuffix3 = 0;
    }
    if(this.selectedSuffix1 == 0)
    {
      this.selectedSuffix1 = this.selectedSuffix2;
      this.selectedSuffix2 = this.selectedSuffix3;
      this.selectedSuffix3 = 0;
    }
  };

  this.fillFretsText = function()
  {
    for(var i = 0; i < this.Notes.length; i++)
      this.fretsText[i] = '&nbsp;';
    this.fretsText[this.selectedKey] = '<b>1</b>';
    this.fretsText[(this.selectedKey+this.Class[this.selectedClass].offset)%this.Notes.length] = '2';
    this.fretsText[(this.selectedKey+this.End[this.selectedEnd].offset)%this.Notes.length] = '3';
    if(this.selectedSuffix1 != 0)
      this.fretsText[(this.selectedKey+this.Suffix[this.selectedSuffix1].offset)%this.Notes.length] = '4';
    if(this.selectedSuffix2 != 0)
      this.fretsText[(this.selectedKey+this.Suffix[this.selectedSuffix2].offset)%this.Notes.length] = '5';
    if(this.selectedSuffix3 != 0)
      this.fretsText[(this.selectedKey+this.Suffix[this.selectedSuffix3].offset)%this.Notes.length] = '6';
  };

  this.drawControl = function()
  {
    var text = '';
    text += '<select id="'+this.name+'Key'+'" onchange="'+this.name+'.actionChord(); return false;">';
    for(var i = 0; i < this.Notes.length; i++)
    {
      var selected = '';
      if(i == this.selectedKey)
        selected = ' selected="selected"';
      text += '<option value="'+i+'"'+selected+'>'+this.Notes[i]+'</option>';
    }
    text +=
      '<select> '+
      '<select id="'+this.name+'Class'+'" onchange="'+this.name+'.actionChord(); return false;">';
    for(var i = 0; i < this.Class.length; i++)
    {
      var selected = '';
      if(i == this.selectedClass)
        selected = ' selected="selected"';
      text += '<option value="'+i+'"'+selected+'>'+this.Class[i].name+'</option>';
    }
    text +=
      '<select> '+
      '<select id="'+this.name+'End'+'" onchange="'+this.name+'.actionChord(); return false;">';
    for(var i = 0; i < this.End.length; i++)
    {
      var selected = '';
      if(i == this.selectedEnd)
        selected = ' selected="selected"';
      text += '<option value="'+i+'"'+selected+'>'+this.End[i].name+'</option>';
    }
    text +=
      '<select> '+
      '<select id="'+this.name+'Suffix1'+'" onchange="'+this.name+'.actionChord(); return false;">';
    for(var i = 0; i < this.Suffix.length; i++)
    {
      var selected = '';
      if(i == this.selectedSuffix1)
        selected = ' selected="selected"';
      text += '<option value="'+i+'"'+selected+'>'+this.Suffix[i].name+'</option>';
    }
    text +=
      '<select> '+
      '<select id="'+this.name+'Suffix2'+'" onchange="'+this.name+'.actionChord(); return false;">';
    for(var i = 0; i < this.Suffix.length; i++)
    {
      var selected = '';
      if(i == this.selectedSuffix2)
        selected = ' selected="selected"';
      text += '<option value="'+i+'"'+selected+'>'+this.Suffix[i].name+'</option>';
    }
    text +=
      '<select> '+
      '<select id="'+this.name+'Suffix3'+'" onchange="'+this.name+'.actionChord(); return false;">';
    for(var i = 0; i < this.Suffix.length; i++)
    {
      var selected = '';
      if(i == this.selectedSuffix3)
        selected = ' selected="selected"';
      text += '<option value="'+i+'"'+selected+'>'+this.Suffix[i].name+'</option>';
    }
    text += '<select>';
    return text;
  };

  this.drawChord = function()
  {
    var text = '';
    text +=
      '<table class="chordChord">'+
      '<tr>'+
      '<td class="chordsNote">1</td>'+
      '<td class="chordsNote">2</td>'+
      '<td class="chordsNote">3</td>';
    if(this.selectedSuffix1 != 0)
      text += '<td class="chordsNote">4</td>';
    if(this.selectedSuffix2 != 0)
      text += '<td class="chordsNote">5</td>';
    if(this.selectedSuffix3 != 0)
      text += '<td class="chordsNote">6</td>';
    text +=
      '</tr>'+
      '<tr>'+
      '<td class="chordsNote">'+this.Notes[this.selectedKey]+'</td>'+
      '<td class="chordsNote">'+this.Notes[(this.selectedKey+this.Class[this.selectedClass].offset)%this.Notes.length]+'</td>'+
      '<td class="chordsNote">'+this.Notes[(this.selectedKey+this.End[this.selectedEnd].offset)%this.Notes.length]+'</td>';
    if(this.selectedSuffix1 != 0)
      text += '<td class="chordsNote">'+this.Notes[(this.selectedKey+this.Suffix[this.selectedSuffix1].offset)%this.Notes.length]+'</td>';
    if(this.selectedSuffix2 != 0)
      text += '<td class="chordsNote">'+this.Notes[(this.selectedKey+this.Suffix[this.selectedSuffix2].offset)%this.Notes.length]+'</td>';
    if(this.selectedSuffix3 != 0)
      text += '<td class="chordsNote">'+this.Notes[(this.selectedKey+this.Suffix[this.selectedSuffix3].offset)%this.Notes.length]+'</td>';
    text +=
      '</tr>'+
      '</table>';
    return text;
  };

  this.drawFrets = function()
  {
    var text = '';
    text +=
      '<tr>'+
      '<td class="chordsCell">&nbsp</td>'+
      '<td class="chordsString">&nbsp</td>';
    for(var i = 0; i <= this.FretsNumber; i++)
    {
      var className = 'chordsCell';
      for(var j = 0; j < this.FretsMark.length; j++)
        if(i%this.Notes.length == this.FretsMark[j])
        {
          className = 'chordsCellMarked';
          break;
        }
      text += '<td class="'+className+'">'+i+'</td>';
    }
    text +=
      '<td class="chordsString">&nbsp</td>'+
      '<td>&nbsp;</td>'+
      '</tr>';
    return text;
  };

  this.drawString = function(index)
  {
    var text = '';
    text +=
      '<tr>'+
      '<td class="chordsCell">'+(this.strings.length-index)+'</td>'+
      '<td class="chordsString">'+this.Notes[this.strings[index]]+'</td>';
    for(var i = 0; i <= this.FretsNumber; i++)
      text += '<td class="chordsCell">'+this.fretsText[(this.strings[index]+i)%this.Notes.length]+'</td>';
    text +=
      '<td class="chordsString">'+this.Notes[this.strings[index]]+'</td>'+
      '<td>'+
      '<select id="'+this.name+'String'+index+'" onchange="'+this.name+'.actionString('+index+'); return false;">'+
      '<option value="" selected="selected">String '+(this.strings.length-index)+':</option>'+
      '<option value=""></option>';
    if(this.strings.length > 1)
      text += '<option value="delete">Delete</option>';
    text +=
      '<option value="duplicate">Duplicate</option>'+
      '<option value=""></option>';
    for(var i = 0; i < this.Notes.length; i++)
      text += '<option value="'+i+'">Change to '+this.Notes[i]+'</option>';
    text +=
      '</select>'+
      '</td>';
    text += '</tr>';
    return text;
  };

  this.drawFingerBoard = function()
  {
    var text = '';
    text +=
      '<table class="chordFingerBoard">'+
      this.drawFrets();
    this.fillFretsText();
    for(var i = 0; i < this.strings.length; i++)
      text += this.drawString(i);
    text +=
      this.drawFrets()+
      '</table>';
    return text;
  };

  this.drawShortcutChord = function()
  {
    var text = '';
    text +=
      '<select id="'+this.name+'ShortcutChord" onchange="'+this.name+'.actionShortcutChord(); return false;">'+
      '<option value="" selected="selected">Chord Shortcut:</option>'+
      '<option value=""></option>'+
      '<option value="dim">dim</option>'+
      '<option value="dim7">dim7</option>'+
      '<option value="-">-</option>'+
      '<option value="+">+</option>'+
      '</select>';
    return text;
  };

  this.drawShortcutTuning = function()
  {
    var text = '';
    text +=
      '<select id="'+this.name+'ShortcutTuning" onchange="'+this.name+'.actionShortcutTuning(); return false;">'+
      '<option value="" selected="selected">Tuning Shortcut:</option>'+
      '<option value=""></option>'+
      '<option value="standard">Standard</option>'+
      '<option value="7Strings">7 Strings</option>'+
      '<option value="Eb">Eb</option>'+
      '<option value="D">D</option>'+
      '<option value="dropD">Drop D</option>'+
      '<option value="openD">Open D</option>'+
      '<option value="openG">Open G</option>'+
      '<option value="bass">Bass</option>'+
      '<option value="bass5">Bass 5 Strings</option>'+
      '<option value="bass6">Bass 6 Strings</option>'+
      '</select>';
    return text;
  };

  this.drawShortcut = function()
  {
    var text = '';
    text += this.drawShortcutChord()+' '+this.drawShortcutTuning();
    return text;
  }

  this.draw = function()
  {
    this.normalizeSuffixes();
    document.getElementById(this.divName).innerHTML =
      this.drawControl()+
      '<p/>'+
      this.drawChord()+
      '<p/>'+
      this.drawFingerBoard()+
      '<p/>'+
      this.drawShortcut();
  };

  this.actionChord = function()
  {
    var newValue;
    newValue = parseInt(document.getElementById(this.name+'Key').value);
    if(!isNaN(newValue))
      this.selectedKey = newValue;
    newValue = parseInt(document.getElementById(this.name+'Class').value);
    if(!isNaN(newValue))
      this.selectedClass = newValue;
    newValue = parseInt(document.getElementById(this.name+'End').value);
    if(!isNaN(newValue))
      this.selectedEnd = newValue;
    newValue = parseInt(document.getElementById(this.name+'Suffix1').value);
    if(!isNaN(newValue))
      this.selectedSuffix1 = newValue;
    newValue = parseInt(document.getElementById(this.name+'Suffix2').value);
    if(!isNaN(newValue))
      this.selectedSuffix2 = newValue;
    newValue = parseInt(document.getElementById(this.name+'Suffix3').value);
    if(!isNaN(newValue))
      this.selectedSuffix3 = newValue;
    this.draw();
  };

  this.actionString = function(index)
  {
    var what = document.getElementById(this.name+'String'+index).value;
    switch(what)
    {
      case 'delete':
        this.strings.splice(index, 1);
        break;
      case 'duplicate':
        this.strings.splice(index, 0, this.strings[index]);
        break;
      default:
        if(what == '')
          return;
        var newValue = parseInt(what);
        if(isNaN(newValue))
          return;
        this.strings[index] = newValue;
    }
    this.draw();
  };

  this.actionShortcutChord = function()
  {
    switch(document.getElementById(this.name+'ShortcutChord').value)
    {
      case 'dim':
        this.selectedClass = 1;
        this.selectedEnd = 0;
        this.selectedSuffix1 = 0;
        this.selectedSuffix2 = 0;
        this.selectedSuffix3 = 0;
        break;
      case 'dim7':
        this.selectedClass = 1;
        this.selectedEnd = 0;
        this.selectedSuffix1 = 1;
        this.selectedSuffix2 = 0;
        this.selectedSuffix3 = 0;
        break;
      case '-':
        this.selectedClass = 2;
        this.selectedEnd = 0;
        this.selectedSuffix1 = 0;
        this.selectedSuffix2 = 0;
        this.selectedSuffix3 = 0;
        break;
      case '+':
        this.selectedClass = 2;
        this.selectedEnd = 2;
        this.selectedSuffix1 = 0;
        this.selectedSuffix2 = 0;
        this.selectedSuffix3 = 0;
        break;
      default:
        return;
    }
    this.draw();
  };

  this.actionShortcutTuning = function()
  {
    switch(document.getElementById(this.name+'ShortcutTuning').value)
    {
      case 'standard':
        this.strings = Array
        (
          7,
          2,
          10,
          5,
          0,
          7
        );
        break;
      case '7Strings':
        this.strings = Array
        (
          7,
          2,
          10,
          5,
          0,
          7,
          2
        );
        break;
      case 'Eb':
        this.strings = Array
        (
          6,
          1,
          9,
          4,
          11,
          6
        );
       break;
      case 'D':
        this.strings = Array
        (
          5,
          0,
          8,
          3,
          10,
          5
        );
        break;
      case 'dropD':
        this.strings = Array
        (
          7,
          2,
          10,
          5,
          0,
          5
        );
        break;
      case 'openD':
        this.strings = Array
        (
          5,
          0,
          9,
          5,
          0,
          5
        );
        break;
      case 'openG':
        this.strings = Array
        (
          5,
          2,
          10,
          5,
          10,
          5
        );
        break;
      case 'bass':
        this.strings = Array
        (
          10,
          5,
          0,
          7
        );
        break;
      case 'bass5':
        this.strings = Array
        (
          10,
          5,
          0,
          7,
          2
        );
        break;
      case 'bass6':
        this.strings = Array
        (
          3,
          10,
          5,
          0,
          7,
          2
        );
        break;
      default:
        return;
    }
    this.draw();
  };

  this.draw();
  window[this.name] = this;
}
