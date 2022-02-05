RGB_scale = 255.0;
HSV_scale = 100.0;

Math.fmod = function (a,b) {
  return Number((a - (Math.floor(a / b) * b)).toPrecision(8));
};

function gamma(val) {
  if(val <= 0.04045) {
    return val/12.92;
  } else {
    return Math.pow((val+ 0.055)/1.055, 2.4);
  }
}

function gamma_inv( val) {
  if(val > 0.0031308) {
    return 1.055 * Math.pow(val, 1/2.4) - 0.055;
  } else {
    return val * 12.92;
  }
}

function XYZ_2_RGB(x, y, z) {

  let r = x *  3.2406254773200531454   + y * -1.5372079722103185961  + z * -0.49862859869824785913;
  let g = x * -0.96893071472931930199  + y *  1.8757560608852411526  + z *  0.041517523842953942967;
  let b = x *  0.055710120445510610295 + y * -0.20402105059848668751 + z *  1.0569959422543882942;
  r = gamma_inv(r) * RGB_scale;
  g = gamma_inv(g) * RGB_scale;
  b = gamma_inv(b) * RGB_scale;
  return [r, g, b];
}

function RGB_2_XYZ(r, g, b) {
  let lR = gamma(r / RGB_scale);
  let lG = gamma(g / RGB_scale);
  let lB = gamma(b / RGB_scale);
  let x = lR * 0.4124 + lG * 0.3576 + lB * 0.1805;
  let y = lR * 0.2126 + lG * 0.7152 + lB * 0.0722;
  let z = lR * 0.0193 + lG * 0.1192 + lB * 0.9505;
  return [x, y, z];
}

function RGB_2_HSV(r, g, b) {
    let rp = r / RGB_scale;
    let gp = g / RGB_scale;
    let bp = b / RGB_scale;

    let min = Math.min(Math.min(rp, gp), bp);
    let max = Math.max(Math.max(rp, gp), bp);
    let diff = max - min;

    let v = max * 100.0;
    let s = 0.0;
    let h = 0.0;

    if(v == 0 || max == 0.0) {
      return [h, s, v];
    }
    s = (diff / max) * 100.0;

   if (max == min) {
     h = 0.0;
   } else if (max == rp) {
     h = Math.fmod((60.0 * ((gp - bp) / diff) + 360.0), 360.0);
   } else if (max == gp) {
     h = Math.fmod((60.0 * ((bp - rp) / diff) + 120.0), 360.0);
   } else if (max == bp) {
     h = Math.fmod((60.0 * ((rp - gp) / diff) + 240.0), 360.0);
   }
   return [h, s, v];
}

function XYZ_2_xyY(x, y, z) {
  let ox;
  let oy;
  let oY;
  if(x+y+z == 0.0) {
    ox = 0;
    oy = 0;
  } else {
    ox = x / (x+y+z);
    oy = y / (x+y+z);
  }
  oY = y;
  return [ox, oy, oY];
}


function HSV_2_RGB(h, s, v) {
  let sp = s / HSV_scale;
  let vp = v / HSV_scale;
  let C = sp * vp;
  let X = C * (1 - Math.abs(Math.fmod(h / 60.0, 2.0) -1.0));
  let m = vp - C;
  let rp;
  let gp;
  let bp;

  if(h >= 0 && h < 60) {
    rp = C;
    gp = X;
    bp = 0;
  } else if(h >= 60 && h < 120) {
    rp = X;
    gp = C;
    bp = 0;
  } else if(h >= 120 && h < 180) {
    rp = 0;
    gp = C;
    bp = X;
  } else if(h >= 180 && h < 240) {
    rp = 0;
    gp = X;
    bp = C;
  } else if(h >= 240 && h < 300) {
    rp = X;
    gp = 0;
    bp = C;
  } else {
    rp = C;
    gp = 0;
    bp = X;
  }
  let r;
  let g;
  let b;
  r = (rp + m) * RGB_scale;
  g = (gp + m) * RGB_scale;
  b = (bp + m) * RGB_scale;
  return [r, g, b];
}

function xyY_2_XYZ(x, y, I) {
  let X;
  let Y;
  let Z;
  if(y == 0) {
    X = 0;
    Z = 0;
  } else {
    X = (x * I) / y;
    Z = ((1 - x - y) * I) / y;
  }
  Y = I;
  return [X, Y, Z];
}

function RGB_normalize(r, g, b) {
  let Rn = RGB_scale;
  let Gn = RGB_scale;
  let Bn = RGB_scale;
  let max = Math.max(r, g, b);
  if(max > 0)
  {
    Rn = Math.floor(r*RGB_scale/max);
    Gn = Math.floor(g*RGB_scale/max);
    Bn = Math.floor(b*RGB_scale/max);
  }
  return [Rn, Gn, Bn];
}
