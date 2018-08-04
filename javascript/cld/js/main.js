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
  new CLDClass('cld_1', 200);
  new CLDClass('cld_2', 150);
  new CLDClass('cld_3', 100);
}
