#!/usr/bin/env python3
"""Add subtle divider lines between the layer blocks of a keymap-drawer SVG.

keymap-drawer leaves only ~15px between one layer's lowest key and the next
layer's "Lx:" label, which is not enough room for a divider that clears the
rotated thumb keys. So this first opens up ROW_GAP extra pixels between rows,
then centers a hairline in each gutter. Block extents are measured from the
real geometry of every key -- its own rect size and any rotation -- so nothing
is ever clipped and the grid follows changes to the keymap.
"""
import math, re, sys

ROW_GAP = 24     # extra breathing room inserted between layer rows
LABEL_TOP = 10   # cap height of the "Lx:" label, measured from its group origin
EDGE = 8         # how far the lines stop short of the canvas edge

src, dst = sys.argv[1], sys.argv[2]
svg = open(src).read()

LAYER_RE = re.compile(r'<g transform="translate\((-?[\d.]+), (-?[\d.]+)\)" class="layer-(\S+?)">')
KEYAREA_RE = re.compile(r'<g transform="translate\((-?[\d.]+), (-?[\d.]+)\)">')
KEY_RE = re.compile(
    r'<g transform="translate\((-?[\d.]+), (-?[\d.]+)\)(?: rotate\((-?[\d.]+)\))?" class="key [^"]*">\s*'
    r'<rect[^>]*?x="(-?[\d.]+)" y="(-?[\d.]+)" width="([\d.]+)" height="([\d.]+)"')

# ---- push the rows apart, and grow the canvas to match --------------------
rows = sorted({float(m.group(2)) for m in LAYER_RE.finditer(svg)})
shift = {row: i * ROW_GAP for i, row in enumerate(rows)}

def move_layer(m):
    ox, oy, name = float(m.group(1)), float(m.group(2)), m.group(3)
    return f'<g transform="translate({ox:g}, {oy + shift[oy]:g})" class="layer-{name}">'

svg = LAYER_RE.sub(move_layer, svg)

W = int(re.search(r'<svg width="(\d+)"', svg).group(1))
H = int(re.search(r'<svg width="\d+" height="(\d+)"', svg).group(1)) + shift[rows[-1]]
svg = re.sub(r'<svg width="\d+" height="\d+" viewBox="0 0 \d+ \d+"',
             f'<svg width="{W}" height="{H}" viewBox="0 0 {W} {H}"', svg, count=1)

# ---- measure each layer block --------------------------------------------
def key_bounds(kx, ky, deg, rx, ry, rw, rh):
    """Bounds of one key rect, honouring rotation about its center."""
    a = math.radians(deg)
    cos, sin = math.cos(a), math.sin(a)
    xs, ys = [], []
    for cx in (rx, rx + rw):
        for cy in (ry, ry + rh):
            xs.append(kx + cx * cos - cy * sin)
            ys.append(ky + cx * sin + cy * cos)
    return min(xs), min(ys), max(xs), max(ys)

marks = [(m.start(), float(m.group(1)), float(m.group(2))) for m in LAYER_RE.finditer(svg)]
blocks = []
for i, (pos, ox, oy) in enumerate(marks):
    chunk = svg[pos:marks[i + 1][0] if i + 1 < len(marks) else len(svg)]
    hdr = KEYAREA_RE.search(chunk)            # keys are offset by the layer header
    hx, hy = (float(hdr.group(1)), float(hdr.group(2))) if hdr else (0.0, 0.0)
    keys = [key_bounds(float(kx), float(ky), float(deg or 0), *map(float, rect))
            for kx, ky, deg, *rect in KEY_RE.findall(chunk)]
    if keys:
        blocks.append({"x": ox, "y": oy,
                       "right": ox + hx + max(b[2] for b in keys),
                       "bottom": oy + hy + max(b[3] for b in keys)})

# ---- draw the dividers, centered in each gutter --------------------------
cols = sorted({b["x"] for b in blocks})
new_rows = sorted({b["y"] for b in blocks})
lines = []
for col in cols[1:]:
    left = max(b["right"] for b in blocks if b["x"] < col)
    x = (left + col) / 2
    lines.append(f'<line x1="{x:.1f}" y1="{EDGE}" x2="{x:.1f}" y2="{H - EDGE}"/>')
for row in new_rows[1:]:
    above = max(b["bottom"] for b in blocks if b["y"] < row)
    y = (above + row + LABEL_TOP) / 2
    lines.append(f'<line x1="{EDGE}" y1="{y:.1f}" x2="{W - EDGE}" y2="{y:.1f}"/>')
    print(f"  row gutter {above:.1f}..{row + LABEL_TOP:.1f} -> line {y:.1f} "
          f"({y - above:.1f}px below the keys above)")

grid = ('<g class="layer-grid" fill="none" stroke="#ffffff" stroke-opacity="0.4" '
        'stroke-width="1.5" stroke-linecap="round">\n' + "\n".join(lines) + "\n</g>\n")
svg = svg.replace("</style>\n", "</style>\n" + grid, 1)  # behind the layers
open(dst, "w").write(svg)
print(f"canvas {W}x{H} (aspect {W / H:.3f})")
