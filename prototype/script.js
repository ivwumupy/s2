"use strict";

function makeRect(x, y, w, h) {
  return { x, y, w, h };
}
function makePoint(x, y) {
  return { x, y };
}
function makeSize(w, h) {
  return { w, h };
}
function makeTrans(dx, dy) {
  return { dx, dy };
}

class PaintContext {
  constructor(ctx) {
    this.quads = [];
    this.lines = [];
    this.texts = [];
    this.trans = [makeTrans(0, 0)];
    this.ctx = ctx;
  }

  currentTransform() {
    return this.trans[this.trans.length - 1];
  }

  push(t) {
    const cur = this.currentTransform();
    this.trans.push(makeTrans(cur.dx + t.dx, cur.dy + t.dy));
  }

  pop() {
    this.trans.pop();
  }

  fill_quad(x, y, w, h, c) {
    const t = this.currentTransform();
    this.quads.push({ x: x + t.dx, y: y + t.dy, w, h, c });
  }
  stroke_quad(x, y, w, h, c) {
    const t = this.currentTransform();
    const x1 = x + t.dx;
    const y1 = y + t.dy;
    const a = makePoint(x1, y1);
    const b = makePoint(x1 + w, y1);
    const C = makePoint(x1 + w, y1 + h);
    const d = makePoint(x1, y1 + h);
    this.lines.push({ p: a, q: b, c });
    this.lines.push({ p: b, q: C, c });
    this.lines.push({ p: C, q: d, c });
    this.lines.push({ p: d, q: a, c });
  }

  add_text(x, y, text) {
    const t = this.currentTransform();
    this.texts.push({ x: x + t.dx, y: y + t.dy, text });
  }

  paintToCanvas() {
    for (const q of this.quads) {
      this.ctx.fillStyle = q.c;
      this.ctx.fillRect(q.x, q.y, q.w, q.h);
    }
    for (const l of this.lines) {
      this.ctx.lineWidth = 2.0;
      this.ctx.strokeStyle = l.c;
      this.ctx.moveTo(l.p.x, l.p.y);
      this.ctx.lineTo(l.q.x, l.q.y);
      this.ctx.stroke();
    }
    for (const t of this.texts) {
      this.ctx.font = "36px serif";
      this.ctx.fillStyle = "black";
      this.ctx.textBaseline = "top";
      this.ctx.fillText(t.text, t.x, t.y);
    }
  }

  measureText(text) {
    this.ctx.font = "36px serif";
    this.ctx.fillStyle = "black";
    this.ctx.textBaseline = "top";
    const m = this.ctx.measureText(text);
    console.log(m);
    return makeSize(m.width, m.actualBoundingBoxDescent);
  }
}

class View {
  constructor() {
    this.bounds = makeRect(0, 0, 0, 0);
    this.parent = null;
    this.repaint = false;
  }
  layout() {}
  prepaint() {
    this.repaint = false;
  }
  paint(ctx) {}
  preferredSize(proposal) {
    return makeSize(0, 0);
  }
  requestRepaint() {
    if (this.parent) {
      this.parent.requestRepaint();
    }
    this.repaint = true;
  }
}

class VStack extends View {
  constructor() {
    super();
    this.children = [];
  }
  add_child(view) {
    this.children.push(view);
    view.parent = this;
  }
  paint(ctx) {
    this.prepaint();
    ctx.push(makeTrans(this.bounds.x, this.bounds.y));
    for (const child of this.children) {
      child.paint(ctx);
    }
    ctx.pop();
  }
  preferredSize(proposal) {
    let w = 0;
    let h = 0;
    for (const child of this.children) {
      const size = child.preferredSize(proposal);
      h += size.h;
      w = Math.max(w, size.w);
    }
    return makeSize(w, h);
  }
  layout() {
    let x = 0;
    let y = 0;
    for (const child of this.children) {
      const size = child.preferredSize(this.bounds);
      child.bounds = makeRect(x, y, size.w, size.h);
      child.layout();
      y += size.h;
    }
  }
}

class QuadView extends View {
  constructor(w, h, c) {
    super();
    this.size = makeSize(w, h);
    this.c = c;
  }
  paint(ctx) {
    this.prepaint();
    const { x, y, w, h } = this.bounds;
    ctx.fill_quad(x, y, w, h, this.c);
  }
  preferredSize(proposal) {
    return this.size;
  }
}

class BorderView extends View {
  constructor(child) {
    super();
    this.child = child;
    child.parent = this;
  }

  paint(ctx) {
    this.prepaint();
    ctx.push(makeTrans(this.bounds.x, this.bounds.y));
    this.child.paint(ctx);
    ctx.pop();
    const { x, y, w, h } = this.bounds;
    ctx.stroke_quad(x, y, w, h, "red");
  }
  preferredSize(proposal) {
    return this.child.preferredSize(proposal);
  }
  layout() {
    this.child.bounds = makeRect(0, 0, this.bounds.w, this.bounds.h);
    this.child.layout();
  }
}

class VSpace extends View {
  constructor(h) {
    super();
    this.h = h;
  }
  preferredSize(proposal) {
    return makeSize(proposal.w, this.h);
  }
}

class Padding extends View {
  constructor(p, child) {
    super();
    this.p = p;
    this.child = child;
    child.parent = this;
  }
  preferredSize(proposal) {
    const { w, h } = this.child.preferredSize(
      makeSize(proposal.w - 2 * this.p, proposal.h - 2 * this.p),
    );
    return makeSize(w + 2 * this.p, h + 2 * this.p);
  }
  layout() {
    const { x, y, w, h } = this.bounds;
    this.child.bounds = makeRect(
      this.p,
      this.p,
      w - 2 * this.p,
      h - 2 * this.p,
    );
    this.child.layout();
  }
  paint(ctx) {
    this.prepaint();
    ctx.push(makeTrans(this.bounds.x, this.bounds.y));
    this.child.paint(ctx);
    ctx.pop();
  }
}

class TextView extends View {
  constructor(text) {
    super();
    this.text = text;
    this.size = null;
  }
  preferredSize(proposal) {
    if (this.size) {
      return this.size;
    }
    return makeSize(0, 0);
  }
  paint(ctx) {
    this.prepaint();
    if (this.size) {
      ctx.add_text(this.bounds.x, this.bounds.y, this.text);
      return;
    } else {
      this.size = ctx.measureText(this.text);
      this.requestRepaint();
    }
  }
}

document.addEventListener("DOMContentLoaded", function () {
  const canvas = document.getElementById("drawingCanvas");

  // hidpi
  const rect = canvas.getBoundingClientRect();
  const scaling = 2.0;
  canvas.width = rect.width * scaling;
  canvas.height = rect.height * scaling;

  let view = new VStack();

  view.add_child(
    new BorderView(new Padding(20, new QuadView(100, 100, "green"))),
  );
  view.add_child(new BorderView(new VSpace(20)));
  view.add_child(new QuadView(100, 200, "gray"));
  view.add_child(new BorderView(new QuadView(100, 100, "yellow")));
  view.add_child(
    new BorderView(
      new Padding(10, new BorderView(new TextView("hello, world! this is a TextView."))),
    ),
  );

  view = new Padding(10, new BorderView(view));

  function render() {
    console.log("rendering");

    const ctx = canvas.getContext("2d");
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    const pctx = new PaintContext(ctx);

    const size = view.preferredSize(makeSize(canvas.width, canvas.height));
    view.bounds = makeRect(0, 0, size.w, size.h);
    view.layout();

    view.paint(pctx);

    if (!view.repaint) {
      pctx.paintToCanvas();
    }

    console.log(pctx);

    if (view.repaint) {
      requestAnimationFrame(render);
    }
  }
  requestAnimationFrame(render);
});
