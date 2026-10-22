# dave notes

make changes in
```
keyboards/crkbd/keymaps/qooqu
```

then run
```
qmk compile
```

open folder with the uf2 firmware
```
cd ~/Repos/qmk_firmware
f.
```

open the right half of the keyboard in boot mode
1. unplug the usb power from the keyboard
1. unplug the trs cable? not sure this is necessary
1. update the right half
  1. open the right half in bootmode
    1. hold down "p" (one in from top right) and plug in usb
    1. it should show up in finder as a new drive called RPI-PR2
  1. upload the firmware
    1. drag the uf2 into the new drive
    1. the new drive will close itself and mac will complain. this is annoying, but normal
  1. unplug the usb
1. repeat for the left half. "q" (one in from top left) is the bootmode key
1. make sure you unplugged the usb
1. connect the two halves with the trs
1. plug in the usb


# mac / linux toggle

the key under caps lock (`CG_TOGG`) switches between mac and linux modifiers
```
mac:    lctrl  lalt  lcmd     |  rcmd/space   ralt  rctrl
linux:  lsuper lalt  lctrl    |  rctrl/space  ralt  rsuper
```

1. it swaps ctrl and gui on both sides, including what space does when held
1. the setting is saved on the keyboard, so it boots in whichever mode it was last in
1. there's no indicator. to check, press the thumb key next to space: on linux it should act as ctrl


# visualize the keymap

quick look. needs `uv`, nothing else to install
```
qmk c2json -kb crkbd/rev4_1/standard -km qooqu --no-cpp -o /tmp/qooqu.json
uvx --from keymap-drawer keymap parse -q /tmp/qooqu.json -o /tmp/qooqu.yaml
uvx --from keymap-drawer keymap draw /tmp/qooqu.yaml > /tmp/qooqu.svg
open /tmp/qooqu.svg
```

or drop `/tmp/qooqu.json` into a browser
1. https://keymap-drawer.streamlit.app for the same picture
1. https://config.qmk.fm for the interactive configurator view. it flags `SEMI_ZERO` as unknown

gotchas
1. `-kb crkbd/rev4_1` is rejected, it needs the `/standard` (or `/mini`) leaf
1. `--no-cpp` is what gets it past the `SEMI_ZERO` custom keycode
1. shifted symbols draw as `!` `@` `#` because the keymap uses the `KC_EXLM` aliases from `keymap_us.h`. plain `LSFT(KC_1)` would draw as "Sft+1" instead
1. the encoder map is not drawn, keymap-drawer has no notion of encoders
1. don't use `magick` to turn the svg into a png, the local imagemagick is not librsvg-backed and mangles keymap-drawer's css

# keymap as the desktop picture

```
viz/make-keymap-wallpaper.sh
```

writes `~/Pictures/qooqu-keymap-wallpaper.png`, 1920x1200, layers in two columns with hairline dividers between them. then finder right-click > set desktop picture. it can't be set from the terminal, that needs automation permission

1. macos desktop pictures have no alpha, a transparent png goes black. so the background color is painted into the image
1. `BG` in the script is `#00c0e8`, the system color "cyan" my desktop was set to. change it there if the desktop color changes
1. it works from any cwd, it finds the repo relative to itself
1. supporting files sit next to it in `viz/`. `keymap-wallpaper-config.yaml` is the keymap-drawer draw config, `gridify.py` adds the divider lines and the spacing between layer rows
1. `shifted-legends.py` draws the shift value above `, . / '` on L0. add to `PAIRS` in it for more keys. it is L0 only on purpose, on the number layer a `?` over `/` is just noise




# Quantum Mechanical Keyboard Firmware

[![Current Version](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/qmk)
[![Docs Status](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub contributors](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

This is a keyboard firmware based on the [tmk\_keyboard firmware](https://github.com/tmk/tmk_keyboard) with some useful features for Atmel AVR and ARM controllers, and more specifically, the [OLKB product line](https://olkb.com), the [ErgoDox EZ](https://ergodox-ez.com) keyboard, and the Clueboard product line.

## Documentation

* [See the official documentation on docs.qmk.fm](https://docs.qmk.fm)

The docs are powered by [VitePress](https://vitepress.dev/). They are also viewable offline; see [Previewing the Documentation](https://docs.qmk.fm/#/contributing?id=previewing-the-documentation) for more details.

You can request changes by making a fork and opening a [pull request](https://github.com/qmk/qmk_firmware/pulls).

## Supported Keyboards

* [Planck](/keyboards/planck/)
* [Preonic](/keyboards/preonic/)
* [ErgoDox EZ](/keyboards/ergodox_ez/)
* [Clueboard](/keyboards/clueboard/)
* [Cluepad](/keyboards/clueboard/17/)
* [Atreus](/keyboards/atreus/)

The project also includes community support for [lots of other keyboards](/keyboards/).

## Maintainers

QMK is developed and maintained by Jack Humbert of OLKB with contributions from the community, and of course, [Hasu](https://github.com/tmk). The OLKB product firmwares are maintained by [Jack Humbert](https://github.com/jackhumbert), the Ergodox EZ by [ZSA Technology Labs](https://github.com/zsa), the Clueboard by [Zach White](https://github.com/skullydazed), and the Atreus by [Phil Hagelberg](https://github.com/technomancy).

## Official Website

[qmk.fm](https://qmk.fm) is the official website of QMK, where you can find links to this page, the documentation, and the keyboards supported by QMK.
