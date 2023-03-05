#include QMK_KEYBOARD_H

enum unicode_names {
    AA_LOWER,
    AA_UPPER,
    AE_LOWER,
    AE_UPPER,
    OE_LOWER,
    OE_UPPER
};

const uint32_t unicode_map[] PROGMEM = {
    [AA_LOWER] = 0x00E5,  // å
    [AA_UPPER] = 0x00C5,  // Å
    [AE_LOWER] = 0x00E6,  // æ
    [AE_UPPER] = 0x00C6,  // Æ
    [OE_LOWER] = 0x00F8,  // ø
    [OE_UPPER] = 0x00D8  // Ø
};

void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_E)) {
        // Leader, e => Types the below string
        SEND_STRING("christopher.maigaard@vippsmobilepay.com");
    } else if (leader_sequence_two_keys(KC_D, KC_K)) { 
        layer_on(3);
    } else if (leader_sequence_four_keys(KC_B, KC_O, KC_O, KC_T)) {
        reset_keyboard();
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {                                                   
        [0] = LAYOUT_split_3x6_3(
                C_S_T(KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T,                KC_Y, KC_U, KC_I, KC_O, KC_P, QK_LEAD,
                KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G,                       KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_DOUBLE_QUOTE,
                KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B,                      KC_N, KC_M, KC_COMMA, KC_DOT, KC_QUESTION, KC_LGUI,
                LALT_T(KC_DEL), LT(2,KC_BSPC), LT(1,KC_SPC),                LCTL_T(KC_ENT), RSFT_T(KC_SPC), LALT_T(KC_APP)),
        [1] = LAYOUT_split_3x6_3(
                KC_GRV, KC_AT, KC_HASH, KC_PERC, KC_AMPR, KC_PIPE,          KC_ASTR, KC_DLR, KC_EXLM, KC_CIRC, KC_PLUS, CW_TOGG, 
                KC_SLSH, KC_LT, KC_LPRN, KC_LCBR, KC_LBRC, KC_EQL,          KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_COLON, KC_QUOTE,
                KC_BSLS, KC_GT, KC_RPRN, KC_RCBR, KC_RBRC, KC_UNDS,         KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_MINUS, KC_TILDE, 
                LALT_T(KC_DEL), KC_SPC, KC_BSPC,                            LCTL_T(KC_ENT), RSFT_T(KC_SPC), LALT_T(KC_APP)),
        [2] = LAYOUT_split_3x6_3(
                KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                   KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
                KC_NO, KC_P1, KC_P2, KC_P3, KC_P4, KC_P5,                   KC_P6, KC_P7, KC_P8, KC_P9, KC_P0, KC_PSCR, 
                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
                KC_NO, KC_NO, KC_NO,                                        KC_NO, KC_NO, KC_NO),
        [3] = LAYOUT_split_3x6_3(
                _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, XP(AA_LOWER, AA_UPPER),
                _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, XP(AE_LOWER, AE_UPPER), XP(OE_LOWER, OE_UPPER),
                _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, TG(3),
                _______, _______, _______,                                  _______, _______, _______)
};

