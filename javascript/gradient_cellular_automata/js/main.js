var SIZEX = 600;
var SIZEY = 600;

function main()
{
  new GCAClass('GCA', SIZEX, SIZEY, 'gca');
  new GCAControlClass('GCAControl', GCA, 'gca_control');
}
