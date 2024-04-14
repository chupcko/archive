import { FloatB32 } from 'float_b32';

class FloatB32View_class {

  constructor(element) {
    this.element = document.getElementById(element);
    this.float = 0.0;
    this.bits = FloatB32.floatToBits32(this.float);
    this.bits_element = [];
    this.init();
  }

  toggle_bit(i) {
    this.bits[i] = 1-this.bits[i];
    this.bits_element[i].innerHTML = this.bits[i];
    this.float = FloatB32.bits32ToFloat(this.bits);
    this.float_element.value = this.float;
  }

  change_float() {
    this.float = parseFloat(this.float_element.value);
    this.bits = FloatB32.floatToBits32(this.float);
    for(let i = FloatB32.FB32_SIGN_INDEX; i <= FloatB32.FB32_MANTISA_END; i++) {
      this.bits_element[i].innerHTML = this.bits[i];
    }
  }

  add_bit(where, i, css_class) {
    let bit_element = document.createElement('div');
    bit_element.classList.add('bit');
    bit_element.classList.add(css_class);
    bit_element.addEventListener(
      'click',
      () => {
        this.toggle_bit(i);
      }
    );
    this.bits_element[i] = document.createElement('div');
    this.bits_element[i].classList.add('bit_content');
    this.bits_element[i].innerHTML = this.bits[i];
    bit_element.appendChild(this.bits_element[i]);
    where.appendChild(bit_element);
  }

  add_space(where) {
    let space_element = document.createElement('div');
    space_element.classList.add('space');
    where.appendChild(space_element);
  }

  add_number(x) {
    let a_element = document.createElement('a');
    a_element.classList.add('number');
    a_element.addEventListener(
      'click',
      (event) => {
        event.preventDefault();
        this.float_element.value = x;
        this.change_float();
      }
    );
    a_element.innerHTML = x;
    this.element.appendChild(a_element);
    this.element.appendChild(document.createElement('br'));
  }

  init() {
    let bits_element = document.createElement('div');
    bits_element.classList.add('bits');

    this.add_bit(bits_element, FloatB32.FB32_SIGN_INDEX, 'sign');

    for(let i = FloatB32.FB32_EXPONENT_BEGIN; i <= FloatB32.FB32_EXPONENT_END; i++) {
      if((i-FloatB32.FB32_EXPONENT_BEGIN)%4 == 0) {
        this.add_space(bits_element);
      }
      this.add_bit(bits_element, i, 'exponent');
    }

    for(let i = FloatB32.FB32_MANTISA_BEGIN; i <= FloatB32.FB32_MANTISA_END; i++) {
      if((i-FloatB32.FB32_MANTISA_BEGIN)%4 == 0) {
        this.add_space(bits_element);
      }
      this.add_bit(bits_element, i, 'mantisa');
    }

    this.element.appendChild(bits_element);
    this.element.appendChild(document.createElement('p'));

    this.float_element = document.createElement('input');
    this.float_element.classList.add('float');
    this.float_element.value = this.float;
    this.float_element.addEventListener(
      'change',
      () => {
        this.change_float();
      }
    );
    this.element.appendChild(this.float_element);
    this.element.appendChild(document.createElement('p'));

    this.add_number(NaN);
    this.add_number(Infinity);
    this.add_number(0);
    this.add_number(1.401298464324817e-45);
    this.add_number(0.1);
    this.add_number(0.2);
    this.add_number(0.5);
    this.add_number(1);
    this.add_number(2);
    this.add_number(Math.E);
    this.add_number(Math.PI);
    this.add_number(5);
    this.add_number(10);
    this.add_number(3.4028234663852886e+38);
  }

}

export {
  FloatB32View_class
};
