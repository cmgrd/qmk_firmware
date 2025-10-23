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

enum unicode_names {
    AA_LOWER,
    AA_UPPER,
    AE_LOWER,
    AE_UPPER,
    OE_LOWER,
    OE_UPPER
};

enum custom_keycodes {
    LIT_GRV = SAFE_RANGE,  // start of custom codes
};

const uint32_t unicode_map[] PROGMEM = {
    [AA_LOWER] = 0x00E5,  // å
    [AA_UPPER] = 0x00C5,  // Å
    [AE_LOWER] = 0x00E6,  // æ
    [AE_UPPER] = 0x00C6,  // Æ
    [OE_LOWER] = 0x00F8,  // ø
    [OE_UPPER] = 0x00D8  // Ø
};

enum combos {
    COMBO_ALTTAB,
    COMBO_ALTENTER,
};

const uint16_t PROGMEM combo_alttab[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_altenter[] = {KC_COMM, KC_DOT, COMBO_END};

combo_t key_combos[] = {
    [COMBO_ALTTAB] = COMBO_ACTION(combo_alttab),
    [COMBO_ALTENTER] = COMBO_ACTION(combo_altenter),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case COMBO_ALTENTER:
            if (pressed) {
                tap_code16(A(KC_ENTER));
            }
            break;
        case COMBO_ALTTAB:
            if (pressed) {
                tap_code16(A(KC_TAB));
            }
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LIT_GRV:
            if (record->event.pressed) {
                send_unicode_string("`"); // sends literal backtick character
            }
            return false; // skip further processing
    }
    return true;
}

void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_SPC)) {
        layer_on(1);
    } else if (leader_sequence_one_key(KC_BSPC)) {
        layer_on(2);
    } else if (leader_sequence_one_key(KC_DEL)) {
        layer_on(4);
    } else if (leader_sequence_one_key(KC_ENT)) {
        layer_on(3);
    } else if (leader_sequence_two_keys(KC_W, KC_E)) {
        SEND_STRING("christopher.maigaard@vippsmobilepay.com");
	} else if (leader_sequence_one_key(KC_G)) {
        SEND_STRING(" =>");
	}
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3_ex2(
    //,----------------------------------------------------------------------.  ,--------------------------------------------------------------.
         HYPR_T(KC_TAB),   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_NO,      KC_NO,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  RGUI_T(KC_APP),
    //|----------------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     CTL_T(KC_ESC), ALT_T(KC_A),CTL_T(KC_S),RGUI_T(KC_D), KC_F, KC_G, KC_NO,      KC_NO,    KC_H,     KC_J, RGUI_T(KC_K),CTL_T(KC_L), ALT_T(KC_SCLN), HYPR_T(KC_DOUBLE_QUOTE),
    //|----------------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
       RGUI_T(KC_MINUS),   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_QUESTION, C_S_T(KC_INSERT),
    //|----------------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                       LT(4, KC_DEL),  LT(2, KC_BSPC),  LT(1, KC_SPC),   LT(3, KC_ENT), OSM(MOD_RSFT), QK_LEAD
                                        //`--------------------------'  `--------------------------'
    ),
    [1] = LAYOUT_split_3x6_3_ex2(
    //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
        LIT_GRV,   KC_AT, KC_HASH, KC_PERC, KC_AMPR, KC_PIPE,   KC_NO,      KC_NO, KC_ASTR, KC_CIRC, KC_EXLM, KC_DLR, KC_PLUS, CW_TOGG, 
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        KC_SLSH,   KC_LT, KC_LPRN, KC_LCBR, KC_LBRC,  KC_EQL,   KC_NO,      KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_COLON, KC_QUOTE,
    //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
        KC_BSLS,   KC_GT, KC_RPRN, KC_RCBR, KC_RBRC, KC_UNDS,                      KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_MINUS, KC_TILDE, 
    //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                            _______, _______, _______,    _______,   TO(0), _______
                                        //`--------------------------'  `--------------------------'
    ),
    [2] = LAYOUT_split_3x6_3_ex2(
    //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_NO,      KC_NO,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
          KC_NO,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_NO,      KC_NO,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_PSCR, 
    //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
         KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,                      KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24, 
    //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                            _______, _______, _______,    _______,   TO(0), _______
                                        //`--------------------------'  `--------------------------'
    ),
    [3] = LAYOUT_split_3x6_3_ex2(
    //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
        _______, KC_BRIU, _______, _______, _______, KC_VOLU, _______,    _______, KC_PSLS,   KC_P7,   KC_P8,   KC_P9,KC_MINUS, _______,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        _______, KC_BRID, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_MUTE,    _______, KC_PAST,   KC_P4,   KC_P5,   KC_P6, KC_PLUS, _______, 
    //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______,                      KC_PCMM,   KC_P1,   KC_P2,   KC_P3,  KC_ENT, _______, 
    //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                            _______, _______, _______,    _______,   TO(0),   KC_P0
                                        //`--------------------------'  `--------------------------'
    ),
    [4] = LAYOUT_split_3x6_3_ex2(
        //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
            _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, UP(AA_LOWER, AA_UPPER),
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
            _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, UP(AE_LOWER, AE_UPPER), UP(OE_LOWER, OE_UPPER),
        //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
            _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, 
        //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                                _______, _______, _______,    _______,   TO(0), _______
                                            //`--------------------------'  `--------------------------'
        )
};


/*

    [3] = LAYOUT_split_3x6_3_ex2(
    //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
        _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, 
    //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, 
    //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                            _______, _______, _______,    _______, _______, _______
                                        //`--------------------------'  `--------------------------'
    )

*/