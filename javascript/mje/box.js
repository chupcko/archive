import Point from './point.js';

class Box {

  static SIZE = 600;
  static RADIUS = 4;
  static ZOOM = 1.25;
  static COUNT_DEFAULT = 100;
  static TRACE_DEFAULT = true;

  mouse_is_down = false;
  mouse_down = new Point();
  min = new Point();
  max = new Point();
  delta = new Point();

  constructor(name) {
    this.name = name;
    this.count = Box.COUNT_DEFAULT;
    this.trace = Box.TRACE_DEFAULT;
    this.element = document.getElementById(this.name);
    this.element.style.border = '2px solid rgb(0, 0, 0)';
    this.element.style.width = `${ Box.SIZE }px`;
    this.element.style.height = `${ Box.SIZE }px`;
    this.element.style.display = 'inline-block';

    this.box = document.createElement('canvas');
    this.box.width = Box.SIZE;
    this.box.height = Box.SIZE;
    this.box.style.position = 'absolute';
    this.box.style.zIndex = '0';
    this.box_context = this.box.getContext('2d');

    this.control = document.createElement('canvas');
    this.control.width = Box.SIZE;
    this.control.height = Box.SIZE;
    this.control.style.position = 'absolute';
    this.control.style.zIndex = '1';
    this.control.style.outline = 'none';
    this.control_context = this.control.getContext('2d');

    this.element.appendChild(this.box);
    this.element.appendChild(this.control);

    this.control.addEventListener(
      'contextmenu',
      (event) => {
        event.preventDefault();
        this.init();
        return false;
      },
      false
    );

    this.control.addEventListener(
      'wheel',
      (event) => {
        event.preventDefault();
        this.zoom(this.mouse_point(event), Math.sign(event.deltaY), event.shiftKey, event.ctrlKey);
        return false;
      },
      false
    );

    this.control.addEventListener(
      'keydown',
      (event) => {
        event.preventDefault();
        this.key(event.key);
        return false;
      },
      false
    );

    this.control.addEventListener(
      'mousedown',
      (event) => {
        event.preventDefault();
        if(event.button == 0) {
          this.mouse_is_down = true;
          this.mouse_down = this.mouse_point(event);
        }
        return false;
      },
      false
    );

    this.control.addEventListener(
      'mouseup',
      (event) => {
        event.preventDefault();
        if(this.mouse_is_down) {
          this.mouse_do(this.mouse_point(event), event.shiftKey, event.ctrlKey);
          this.mouse_is_down = false;
        }
        return false;
      },
      false
    );

    this.control.addEventListener(
      'mouseenter',
      (event) => {
        event.preventDefault();
        this.focus();
        return false;
      },
      false
    );

    this.control.addEventListener(
      'mouseout',
      (event) => {
        event.preventDefault();
        if(this.mouse_is_down) {
          this.mouse_do(this.mouse_point(event), event.shiftKey, event.ctrlKey);
          this.mouse_is_down = false;
        }
        this.blur();
        return false;
      },
      false
    );
  }

  mouse_point(event) {
    let e = this.control;
    let left = 0;
    let top = 0;
    do {
      left += e.offsetLeft;
      top += e.offsetTop;
      e = e.offsetParent;
    } while(e);
    return new Point(event.clientX-left, event.clientY-top);
  }

  real_from_point(x, y) {
    let r = new Point(this.delta);
    r.smul(x, y);
    r.add(this.min);
    return r;
  }

  point_from_real(p) {
    let r = new Point(p);
    r.sub(this.min);
    r.sdiv(this.delta);
    r.x = Math.round(r.x)|0;
    r.y = Math.round(r.y)|0;
    return r;
  }

  init() {
    this.min.set(-2, -2);
    this.max.set(2, 2);
    this.calculate_delta_then_draw();
  }

  calculate_delta_then_draw() {
    this.delta.set(this.max);
    this.delta.sub(this.min);
    this.delta.sdiv(Box.SIZE-1);
    this.draw();
  }

  mouse_do(p, shift, ctrl) {
    if(p.eq(this.mouse_down)) {
      if(this.click_do !== undefined) {
        this.click_do(p, shift, ctrl);
      }
      return;
    }
    if(shift || ctrl) {
      if(this.line_do !== undefined) {
        this.line_do(this.mouse_down, p, shift, ctrl);
      }
      return;
    }
    let d = this.real_from_point(this.mouse_down);
    d.sub(this.real_from_point(p));
    this.min.add(d);
    this.max.add(d);
    this.calculate_delta_then_draw();
  }

  zoom(p, z, shift, ctrl) {
    if(shift || ctrl) {
      if(this.zoom_do !== undefined) {
        this.zoom_do(p, z, shift, ctrl);
      }
      return;
    }
    let c = Box.ZOOM;
    if(z < 0) {
      c = 1/c;
    }
    let m = this.real_from_point(p);
    this.min.sub(m);
    this.min.smul(c);
    this.min.add(m);
    this.max.sub(m);
    this.max.smul(c);
    this.max.add(m);
    this.calculate_delta_then_draw();
  }

  key(key) {
    switch(key) {
      case ' ': {
        this.init();
        break;
      }
      case 't': {
        this.trace = !this.trace;
        this.draw();
        break;
      }
      case '0': {
        this.count = 20;
        this.draw();
        break;
      }
      case '1': {
        this.count = 40;
        this.draw();
        break;
      }
      case '2': {
        this.count = 60;
        this.draw();
        break;
      }
      case '3': {
        this.count = 80;
        this.draw();
        break;
      }
      case '4': {
        this.count = 100;
        this.draw();
        break;
      }
      case '5': {
        this.count = 120;
        this.draw();
        break;
      }
      case '6': {
        this.count = 140;
        this.draw();
        break;
      }
      case '7': {
        this.count = 160;
        this.draw();
        break;
      }
      case '8': {
        this.count = 180;
        this.draw();
        break;
      }
      case '9': {
        this.count = 200;
        this.draw();
        break;
      }
    }
  }

  focus() {
    this.control.tabIndex = 0;
    this.control.focus();
  }

  blur() {
    this.control.tabIndex = -1;
    this.control.blur();
  }

}

export default Box;
