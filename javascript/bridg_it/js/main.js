(
  function()
  {
    var _id = 0;
    Object.prototype.$id = function()
    {
      if(typeof this.$_id === 'undefined')
      {
        this.$_id = _id;
        _id++;
      }
      return this.$_id;
    };
    Object.prototype.$name = function()
    {
      if(typeof this.$_name === 'undefined')
      {
        this.$_name = '$$_'+this.$id();
        window[this.$_name] = this;
      }
      return this.$_name;
    };
  }
)();

function init()
{
  new GameViewClass('game_view_7', 7);
  new GameViewClass('game_view_6', 6);
  new GameViewClass('game_view_5', 5);
  new GameViewClass('game_view_4', 4);
  new GameViewClass('game_view_3', 3);
  new GameViewClass('game_view_2', 2);
}
