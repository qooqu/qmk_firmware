#!/bin/bash
# Rebuild the Corne keymap wallpaper from keymap.c.
# Needs: qmk, uv (for keymap-drawer), Google Chrome. No other setup.
set -euo pipefail

HERE=$(cd "$(dirname "$0")" && pwd)
QMK=$(cd "$HERE/.." && pwd)   # this script lives in viz/ at the repo root
OUT=~/Pictures/qooqu-keymap-wallpaper.png
TMP=$(mktemp -d)
BG='#00c0e8'          # macOS system color "cyan", baked in: wallpapers have no alpha
W=1920; H=1200        # HP E243i native resolution

cd "$QMK"
qmk c2json -kb crkbd/rev4_1/standard -km qooqu --no-cpp -o "$TMP/keymap.json"
KEYMAP="uvx --from keymap-drawer keymap"
$KEYMAP parse -q "$TMP/keymap.json" -o "$TMP/keymap.yaml"
uv run --quiet --with pyyaml python3 "$HERE/shifted-legends.py" "$TMP/keymap.yaml" "$TMP/annotated.yaml"
$KEYMAP -c "$HERE/keymap-wallpaper-config.yaml" draw "$TMP/annotated.yaml" -o "$TMP/wall.svg"
python3 "$HERE/gridify.py" "$TMP/wall.svg" "$TMP/wall-grid.svg"

{ printf '<!doctype html><meta charset=utf-8>\n<style>\n'
  printf '  html,body{margin:0;padding:0;width:%dpx;height:%dpx;overflow:hidden;background:%s}\n' "$W" "$H" "$BG"
  printf '  body{display:flex;align-items:center;justify-content:center}\n'
  printf '  svg.keymap{width:%dpx;height:auto;background:transparent!important}\n</style>\n' $((W - 60))
  cat "$TMP/wall-grid.svg"
} > "$TMP/wall.html"

"/Applications/Google Chrome.app/Contents/MacOS/Google Chrome" --headless --disable-gpu \
  --hide-scrollbars --window-size=$W,$H --screenshot="$OUT" "$TMP/wall.html" 2>/dev/null

rm -rf "$TMP"
echo "wrote $OUT"
