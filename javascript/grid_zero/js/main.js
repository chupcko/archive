function init()
{
  document.getElementById("edit").checked = false;
  document.getElementById("show_input").checked = false;
  document.getElementById("clear_input").disabled = true;
  document.getElementById("count_input").disabled = true;
  var N = parseInt(document.getElementById('N').value);
  new boxClass('Box', 'box', N);
}

function toggleInput()
{
  Box.toggleInput();
  if(document.getElementById("show_input").checked)
  {
    document.getElementById("clear_input").disabled = false;
    document.getElementById("count_input").disabled = false;
  }
  else
  {
    document.getElementById("clear_input").disabled = true;
    document.getElementById("count_input").disabled = true;
  }
}
