var TDImage;

function main() {
  TDImage = new TDImageClass('tDImage', 1200, 800);
}

function change() {
  let f;
  switch(document.getElementById('shape').value) {
    case 'square':
      f = (x, y) => x > 400 && x < 800 && y > 200 && y < 600 ? 100 : 0;
      break;
    case 'ball':
      f = (x, y) => {
        let d = (x-600)*(x-600)+(y-400)*(y-400);
        return d <= 40000 ? 20+Math.sqrt(40000-d) : 0;
      };
      break;
    case 'stairs':
      f = (x, y) => (((x/100)|0)+((y/100)|0))*15;
      break;
    case 'hole':
      f = (x, y) => x > 400 && x < 800 && y > 200 && y < 600 ? -100 : 0;;
      break;
    case 'wave':
      f = (x, y) => (Math.sin((x-600)/40)+Math.cos((y-400)/40))*50+100;
      break;
  }
  if(f) {
    TDImage.draw(f);
  }
}
