const FloatB32 = {
  FB32_SIGN_INDEX: 0,
  FB32_EXPONENT_BEGIN: 1,
  FB32_EXPONENT_END: 8,
  FB32_MANTISA_BEGIN: 9,
  FB32_MANTISA_END: 31,
  FB32_SIZE: 32,
};

FloatB32.FB32_EXPONENT_MAX = 1<<(FloatB32.FB32_EXPONENT_END-FloatB32.FB32_EXPONENT_BEGIN);
FloatB32.FB32_EXPONENT_MIN = 1-FloatB32.FB32_EXPONENT_MAX;
FloatB32.FB32_EXPONENT_BIAS = FloatB32.FB32_EXPONENT_MAX-1;

FloatB32.isFloat = function(x) {
  return typeof x === 'number';
}

FloatB32.isBits32 = function(x) {
  if(!Array.isArray(x)) {
    return false;
  }
  if(x.length !== FloatB32.FB32_SIZE) {
    return false;
  }
  return x.every(
    (e) => e === 0 || e === 1
  );
}

FloatB32.infinityToBits32 = function(x) {
  let b = [];
  if(x < 0.0) {
    b[FloatB32.FB32_SIGN_INDEX] = 1;
  } else {
    b[FloatB32.FB32_SIGN_INDEX] = 0;
  }
  for(let i = FloatB32.FB32_EXPONENT_BEGIN; i <= FloatB32.FB32_EXPONENT_END; i++) {
    b[i] = 1;
  }
  for(let i = FloatB32.FB32_MANTISA_BEGIN; i <= FloatB32.FB32_MANTISA_END; i++) {
    b[i] = 0;
  }
  return b;
}

FloatB32.floatToBits32 = function(x) {
  if(!FloatB32.isFloat(x)) {
    return false;
  }

  let b = [];
  if(isNaN(x)) {
    b[FloatB32.FB32_SIGN_INDEX] = 0;
    b[FloatB32.FB32_EXPONENT_BEGIN] = 1;
    for(let i = FloatB32.FB32_EXPONENT_BEGIN; i <= FloatB32.FB32_EXPONENT_END; i++) {
      b[i] = 1;
    }
    b[FloatB32.FB32_MANTISA_BEGIN] = 1;
    for(let i = FloatB32.FB32_MANTISA_BEGIN+1; i <= FloatB32.FB32_MANTISA_END; i++) {
      b[i] = 0;
    }
    return b;
  }
  if(!isFinite(x)) {
    return FloatB32.infinityToBits32(x);
  }
  if(x === 0.0) {
    b[FloatB32.FB32_SIGN_INDEX] = 0;
    for(let i = FloatB32.FB32_EXPONENT_BEGIN; i <= FloatB32.FB32_EXPONENT_END; i++) {
      b[i] = 0;
    }
    for(let i = FloatB32.FB32_MANTISA_BEGIN; i <= FloatB32.FB32_MANTISA_END; i++) {
      b[i] = 0;
    }
    return b;
  }
  let exponent = Math.floor(Math.log(Math.abs(x))/Math.log(2.0));
  if(exponent >= FloatB32.FB32_EXPONENT_MAX) {
    if(x < 0.0) {
      return FloatB32.infinityToBits32(-Infinity);
    }
    return FloatB32.infinityToBits32(Infinity);
  }
  let mantisa;
  if(exponent <= FloatB32.FB32_EXPONENT_MIN) {
    exponent = FloatB32.FB32_EXPONENT_MIN;
    mantisa = Math.abs(x)/Math.pow(2.0, FloatB32.FB32_EXPONENT_MIN+1);
  } else {
    mantisa = Math.abs(x)/Math.pow(2.0, exponent)-1.0;
  }
  if(x < 0.0) {
    b[FloatB32.FB32_SIGN_INDEX] = 1;
  } else {
    b[FloatB32.FB32_SIGN_INDEX] = 0;
  }
  exponent += FloatB32.FB32_EXPONENT_BIAS;
  for(let i = FloatB32.FB32_EXPONENT_END; i >= FloatB32.FB32_EXPONENT_BEGIN; i--) {
    b[i] = exponent%2;
    exponent >>= 1;
  }
  for(let i = FloatB32.FB32_MANTISA_BEGIN; i <= FloatB32.FB32_MANTISA_END; i++) {
    mantisa *= 2.0;
    if(mantisa >= 1.0) {
      b[i] = 1;
      mantisa -= 1.0;
    } else {
      b[i] = 0;
    }
  }
  if(mantisa*2.0 >= 1.0) {
    for(let i = FloatB32.FB32_MANTISA_END; i >= FloatB32.FB32_MANTISA_BEGIN; i--) {
      if(b[i] == 0)
      {
        b[i] = 1;
        break;
      } else {
        b[i] = 0;
      }
    }
  }
  return b;
}

FloatB32.bits32ToFloat = function(x) {
  if(!FloatB32.isBits32(x)) {
    return false;
  }

  let sign = 1.0;
  if(x[FloatB32.FB32_SIGN_INDEX] === 1) {
    sign = -1.0;
  }
  let exponent = 0;
  for(let i = FloatB32.FB32_EXPONENT_BEGIN; i <= FloatB32.FB32_EXPONENT_END; i++) {
    exponent <<= 1;
    exponent |= x[i];
  }
  exponent -= FloatB32.FB32_EXPONENT_BIAS;
  let q = 0.5;
  let mantisa = 0.0;
  let mantissa_have_all_zero = true;
  for(let i = FloatB32.FB32_MANTISA_BEGIN; i <= FloatB32.FB32_MANTISA_END; i++)
  {
    if(x[i] === 1)
    {
      mantisa += q;
      mantissa_have_all_zero = false;
    }
    q /= 2.0;
  }
  if(exponent === FloatB32.FB32_EXPONENT_MIN) {
    if(mantissa_have_all_zero) {
      return 0;
    } else {
      return sign*mantisa*Math.pow(2, FloatB32.FB32_EXPONENT_MIN+1);
    }
  }
  if(exponent === FloatB32.FB32_EXPONENT_MAX) {
    if(mantissa_have_all_zero) {
      return sign*Infinity;
    } else {
      return NaN;
    }
  }
  return sign*(1+mantisa)*Math.pow(2, exponent);
}

/*

console.log(bits32ToFloat([0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]));
console.log(bits32ToFloat([0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]));
console.log(bits32ToFloat([0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]));
console.log(bits32ToFloat([0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]));
console.log(bits32ToFloat([0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]));


console.log(floatToBits32(0));
console.log(floatToBits32(12.375));
console.log(floatToBits32(1));
console.log(floatToBits32(Infinity));
console.log(floatToBits32(NaN));

console.log(floatToBits32(3.14));

*/

export {
  FloatB32
};
