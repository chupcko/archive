const C_S2     = Math.sqrt(2); /* 1.414213562373095                  */
const C_S3     = Math.sqrt(3); /* 1.732050807568877                  */
const C_S3P3D2 = (C_S3+3)/2;   /* 2.366025403784438 invert(C_S3)     */
const C_S3P1D2 = (C_S3+1)/2;   /* 1.366025403784439 C_S3P3D2-1       */
const C_S3P2   = C_S3+2;       /* 3.732050807568877 invert(C_S3P1D2) */

function S(a, n) {
  let s = 0;
  for(let i = 1; i <= n; i++) {
    s += Math.floor(a*i);
  }
  return s;
}

function invert(a) {
  return 1/(1-(1/a));
}

function T(n) {
  return (n+1n)*n/2n;
}

function sqrt(n) {
  if(n === 0) {
    return 0;
  }
  let x0 = n/2n;
  let x1 = (x0+n/x0)/2n;
  while(x1 < x0) {
    x0 = x1;
    x1 = (x0+n/x0)/2n;
  }
  return x0;
}

/*

S(a+1, n) = S(a, n) + T(n)

S(a, b) = T(n+m) - S(invert(a), m) where m = floor((a-1)*n)

*/

function S_C_S3(n) {
  if(n === 0n) {
    return 0n;
  }
  let m = sqrt(3n*n*n)-n;
  return T(n+m)-S_C_S3P3D2(m);
}

function S_C_S3P3D2(n) {
  if(n === 0n) {
    return 0n;
  }
  return T(n)+S_C_S3P1D2(n);
}

function S_C_S3P1D2(n) {
  if(n === 0n) {
    return 0n;
  }
  let m = (sqrt(3n*n*n)-n)/2n;
  return T(n+m)-S_C_S3P2(m);
}

function S_C_S3P2(n) {
  if(n === 0n) {
    return 0n;
  }
  return 2n*T(n)+S_C_S3(n);
}

//console.log(S(C_S3, 1030040).toString());
//console.log(S_C_S3(1030040n).toString());
//console.log();
//console.log(S(C_S3, 38946743).toString());
//console.log(S_C_S3(38946743n).toString());
//console.log();
//console.log(S(C_S3, 8178329).toString());
//console.log(S_C_S3(8178329n).toString());
//console.log();
//console.log(S_C_S3(2n**100n).toString());
//console.log();
console.log(S_C_S3(10n**100n).toString());
//console.log();
//console.log(S_C_S3(1391649168635968194620974987869244360915499123827859905656803n).toString());
//console.log();
