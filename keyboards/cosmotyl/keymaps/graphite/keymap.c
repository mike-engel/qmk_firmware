// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
    // If you quickly hold a tap-hold key after tapping it, the tap action is
    // repeated. Key repeating is useful e.g. for Vim navigation keys, but can
    // lead to missed triggers in fast typing. Here, returning 0 means we
    // instead want to "force hold" and disable key repeating.
    switch (keycode) {
        case KC_ENTER:
        case KC_SPACE:
        case LT(4, KC_BSPC):
            return QUICK_TAP_TERM; // Enable key repeating.
        default:
            return 0; // Otherwise, force hold and disable key repeating.
    }
}

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    // debug_enable   = true;
    // debug_matrix   = true;
    // debug_keyboard = true;
    // debug_mouse=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("DEBUG: kc: 0x%04X, col: %u, row: %u, pressed: %d, time: %u, interrupt: %d, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

    return true;
}

enum layers {
    BASE,
    PROGRAMMING,
    NUMBERS,
    SYMBOLS,
};

// Graphite combos
const uint16_t PROGMEM grv_combo[] = {KC_B, KC_J, COMBO_END};
const uint16_t PROGMEM esc_combo[] = {KC_N, KC_I, COMBO_END};
const uint16_t PROGMEM hyp_combo[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM und_combo[] = {LSFT_T(KC_C), RSFT_T(KC_P), COMBO_END};
const uint16_t PROGMEM cap_combo[] = {LCTL_T(KC_Q), RCTL_T(KC_SLASH), COMBO_END};
// clang-format off
combo_t key_combos[] = {
    COMBO(grv_combo, KC_GRAVE),
    COMBO(esc_combo, KC_ESCAPE),
    COMBO(hyp_combo, KC_MINUS),
    COMBO(und_combo, LSFT(KC_MINUS)),
    COMBO(cap_combo, QK_CAPS_WORD_TOGGLE),
};
// clang-format on

// clang format off
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_3x5_3(
        // Left hand
        'L', 'L', 'L', 'L', 'L',
        'L', 'L', 'L', 'L', 'L',
        'L', 'L', 'L', 'L', 'L',
                  '*', '*', '*',
        // Right hand
        'R', 'R', 'R', 'R', 'R',
        'R', 'R', 'R', 'R', 'R',
        'R', 'R', 'R', 'R', 'R',
        '*', '*', '*'
    );
// clang format on

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// Graphite
[BASE] = LAYOUT_3x5_3(
// Left hand
        KC_B,           KC_L,           KC_D,           KC_W,           KC_Z,
        KC_N,           KC_R,           KC_T,           KC_S,           KC_G,
LCTL_T(KC_Q),   LALT_T(KC_X),   LGUI_T(KC_M),   LSFT_T(KC_C),    ALL_T(KC_V),
                                      KC_TAB,          MO(3),          MO(2),
// Right hand
       KC_SCLN,           KC_F,             KC_O,           KC_U,             KC_J,
          KC_Y,           KC_H,             KC_A,           KC_E,             KC_I,
   ALL_T(KC_K),   RSFT_T(KC_P), RGUI_T(KC_COMMA), RALT_T(KC_DOT), RCTL_T(KC_SLASH),
LT(4, KC_BSPC),       KC_SPACE,         KC_ENTER
),
    [PROGRAMMING] = LAYOUT_3x5_3(
// Left hand
      KC_GRAVE,        KC_TRNS,        KC_TRNS,        KC_TRNS, LALT(KC_MINUS),
         TG(1),        KC_HOME,        KC_PGUP,        KC_PGDN,         KC_END,
       QK_BOOT,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
                                       KC_TRNS,        KC_TRNS,        KC_TRNS,
// Right hand
   LSA(KC_MINUS),  LSFT(KC_LBRC),  LSFT(KC_RBRC),     LSFT(KC_9),     LSFT(KC_0),
         KC_LEFT,        KC_DOWN,          KC_UP,       KC_RIGHT,        KC_TRNS,
         KC_TRNS,        KC_LBRC,        KC_RBRC, LSFT(KC_COMMA),   LSFT(KC_DOT),
         KC_BSPC,       KC_SPACE,       KC_ENTER
    ),
    [NUMBERS] = LAYOUT_3x5_3(
// Left hand
       KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
       KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
       KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
                                       KC_TRNS,        KC_TRNS,        KC_TRNS,
// Right hand
        KC_COMMA,        KC_7,        KC_8,        KC_9,        KC_BSLS,
          KC_DOT,        KC_4,        KC_5,        KC_6,       KC_QUOTE,
            KC_0,        KC_1,        KC_2,        KC_3,       KC_EQUAL,
         KC_BSPC,       KC_SPACE,       KC_ENTER
    ),
    [SYMBOLS] = LAYOUT_3x5_3(
// Left hand
       KC_TRNS,        KC_TRNS,     LSFT(KC_8),     LSFT(KC_7),        KC_TRNS,
   LSFT(KC_QUOTE),     LSFT(KC_6),     LSFT(KC_5),     LSFT(KC_4), LSFT(KC_EQUAL),
   LSFT(KC_GRAVE),     LSFT(KC_3),     LSFT(KC_2),     LSFT(KC_1),  LSFT(KC_BSLS),
                                        KC_TAB,        KC_TRNS,        KC_TRNS,
// Right hand
         KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
         KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
         KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
         KC_TRNS,        KC_TRNS,        KC_TRNS
    ),
    [5] = LAYOUT_3x5_3(
// Left hand
       KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
       KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
       KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
                                       KC_TRNS,        KC_TRNS,        KC_TRNS,
// Right hand
         KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
         KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
         KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
         KC_TRNS,        KC_TRNS,        KC_TRNS
    )
};
// clang-format on
