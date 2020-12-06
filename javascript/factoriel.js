class bigUnsigned {

  constructor(n) {
    this.load(n);
  }

  zero(n) {
    this.digits = [0];
  }

  load(n) {
    if(n === undefined) {
      this.zero();
      return;
    }
    if(typeof n === 'number') {
      if(n <= 0) {
        this.zero();
        return;
      }
      this.digits = [];
      let i = 0;
      while(n > 0) {
        this.digits[i] = n%10;
        i++;
        n = (n/10)|0;
      }
    }
    if(n instanceof bigUnsigned) {
      this.digits = n.digits.slice();
    }
  }

  toString() {
    let s = '';
    for(let i = this.digits.length-1; i >= 0; i--) {
      s += this.digits[i];
    }
    return s;
  }

  toNumber() {
    let x = 0;
    for(let i = this.digits.length-1; i >= 0; i--) {
      x *= 10;
      x += this.digits[i];
    }
    return x;
  }

  add(x) {
    if(!(x instanceof bigUnsigned)) {
      x = new bigUnsigned(x);
    }
    let p = 0;
    for(let i = 0; i < x.digits.length; i++) {
      if(this.digits[i] === undefined) {
        this.digits[i] = 0;
      }
      this.digits[i] += x.digits[i]+p;
      p = (this.digits[i]/10)|0;
      this.digits[i] %= 10;
    }
    for(let i = x.digits.length; p > 0 && i < this.digits.length; i++) {
      this.digits[i] += p;
      p = (this.digits[i]/10)|0;
      this.digits[i] %= 10;
    }
    if(p > 0) {
      this.digits[this.digits.length] = p;
    }
  }

  dup() {
    let p = 0;
    for(let i = 0; i < this.digits.length; i++) {
      this.digits[i] *= 2;
      this.digits[i] += p;
      p = (this.digits[i]/10)|0;
      this.digits[i] %= 10;
    }
    if(p > 0) {
      this.digits[this.digits.length] = p;
    }
  }

  scale(x) {
    if(typeof x !== 'number') {
      x = x.toNumber();
    }
    if(x < 0) {
      x = 0;
    }
    let f = new bigUnsigned(this);
    this.zero();
    while(x > 0) {
      if(x%2 == 1) {
        this.add(f);
      }
      f.dup();
      x = (x/2)|0;
    }
  }

  factoriel(n) {
    this.load(1);
    for(let i = 1; i <= n; i++) {
      this.scale(i);
    }
  }
}

a = new bigUnsigned();
a.factoriel(1000);
console.log(a.toString());
