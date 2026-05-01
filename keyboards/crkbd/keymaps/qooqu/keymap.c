/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
        KC_ESC,  KC_Q, KC_W, LT(1, KC_E), LT(4, KC_R), KC_T,      KC_Y,       KC_U,  KC_I,    KC_O,   KC_P,    KC_BSPC,
        KC_TAB,  KC_A, KC_S, LT(2, KC_D), LT(3, KC_F), KC_G,      KC_H, LT(3, KC_J), KC_K,    KC_L,   KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X,       KC_C,        KC_V,  KC_B,      KC_N,       KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                                  KC_LCTL, KC_LALT, KC_LGUI,      RGUI_T(KC_SPC), KC_BSPC, KC_ENT
    ),

    [1] = LAYOUT_split_3x6_3(
        TO(0),   XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, XXXXXXX,      XXXXXXX, KC_PGUP, KC_UP,   KC_PGDN, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      KC_F1,   KC_F2,   KC_F11,  KC_F12,  XXXXXXX, XXXXXXX,
                                   _______, _______, _______,      _______, _______, _______
    ),

    [2] = LAYOUT_split_3x6_3(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, KC_7, KC_8, KC_9, LSFT(KC_EQL), LSFT(KC_8),
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, KC_4, KC_5, KC_6,      KC_MINS,      KC_SLSH,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, KC_1, KC_2, KC_3,      XXXXXXX,      XXXXXXX,
                                   _______, _______, _______,      _______, KC_DOT,  KC_0
    ),

    [3] = LAYOUT_split_3x6_3(
        LSFT(KC_GRV), LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5),      LSFT(KC_6),   LSFT(KC_7),   LSFT(KC_8),    LSFT(KC_9),    LSFT(KC_0),   LSFT(KC_SCLN),
             KC_GRV,  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,         LSFT(KC_EQL),      KC_MINS, LSFT(KC_MINS),      KC_LBRC,       KC_RBRC,      KC_SCLN,
             XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,              KC_BSLS,      KC_EQL,  LSFT(KC_BSLS), LSFT(KC_LBRC), LSFT(KC_RBRC), XXXXXXX,
                                                       _______, _______, _______,      _______, _______, _______
    ),

    [4] = LAYOUT_split_3x6_3(
        XXXXXXX, XXXXXXX, MS_BTN1, KC_LSFT, XXXXXXX, XXXXXXX,      MS_WHLL, MS_WHLU, MS_UP,   MS_WHLD, MS_WHLR, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, MS_LEFT, MS_DOWN, MS_RGHT, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, MS_BTN1, XXXXXXX, MS_BTN2, XXXXXXX, XXXXXXX,
                                   _______, _______, _______,      MS_BTN1, _______, _______
    ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
    [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
    [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
    [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
    [4] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif
