#!/usr/bin/env python3
"""Add shifted legends to the punctuation keys on the base layer.

keymap-drawer draws what a key sends unshifted, so `,` `.` `/` `'` give no hint
that shift turns them into `<` `>` `?` `"`. This annotates them on one layer
only -- on the number layer `/` means divide and a `?` in the corner would just
be noise. Extend PAIRS to cover more keys.
"""
import sys, yaml

LAYER = "L0"
PAIRS = {",": "<", ".": ">", "/": "?", "'": '"'}

src, dst = sys.argv[1], sys.argv[2]
km = yaml.safe_load(open(src))

layer = km["layers"][LAYER]
for i, key in enumerate(layer):
    tap = key.get("t") if isinstance(key, dict) else key
    if tap in PAIRS:
        key = dict(key) if isinstance(key, dict) else {"t": tap}
        key["s"] = PAIRS[tap]
        layer[i] = key

yaml.safe_dump(km, open(dst, "w"), default_flow_style=None, sort_keys=False, width=200)
print(f"shifted legends on {LAYER}: " + " ".join(f"{k}{v}" for k, v in PAIRS.items()))
