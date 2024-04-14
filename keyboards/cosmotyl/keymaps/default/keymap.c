// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#ifdef USE_ACCORDION
#    include "features/achordion.h"
#endif

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
#ifdef USE_ACHORDION
    if (!process_achordion(keycode, record)) {
        return false;
    }
#endif

    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("DEBUG: kc: 0x%04X, col: %u, row: %u, pressed: %d, time: %u, interrupt: %d, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

    return true;
}

#ifdef USE_ACHORDION
void matrix_scan_user(void) {
    achordion_task();
}

bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record, uint16_t other_keycode, keyrecord_t* other_record) {
    // Also allow same-hand holds when the other key is in the rows below the
    // alphas. I need the `% (MATRIX_ROWS / 2)` because my keyboard is split.
    if (other_record->event.key.row % (MATRIX_ROWS / 2) >= 3) {
        return true;
    }

    // Otherwise, follow the opposite hands rule.
    return achordion_opposite_hands(tap_hold_record, other_record);
}

uint16_t achordion_streak_timeout(uint16_t tap_hold_keycode) {
    if (IS_QK_LAYER_TAP(tap_hold_keycode)) {
        return 0; // Disable streak detection on layer-tap keys.
    }

    return 100; // A longer timeout otherwise.
}
#endif

#ifdef BILATERAL_COMBINATIONS
// See https://github.com/manna-harbour/qmk_firmware/pull/56
#    define BILATERAL_COMBINATIONS_LIMIT_CHORD_TO_N_KEYS 4 /* GUI, Alt, Ctrl, Shift */
#    define BILATERAL_COMBINATIONS_ALLOW_SAMESIDED_AFTER 500
#    define BILATERAL_COMBINATIONS_ALLOW_CROSSOVER_AFTER 80
#    define BILATERAL_COMBINATIONS_TYPING_STREAK_TIMEOUT 160
#    define BILATERAL_COMBINATIONS_TYPING_STREAK_MODMASK (~MOD_MASK_SHIFT)
#endif

enum layers {
    COLEMAK,
    GAMING,
    PROGRAMMING,
    NUMBERS,
    SYMBOLS,
};

const uint16_t PROGMEM grv_combo[] = {KC_Q, KC_SEMICOLON, COMBO_END};
const uint16_t PROGMEM esc_combo[] = {KC_A, KC_O, COMBO_END};
const uint16_t PROGMEM hyp_combo[] = {KC_P, KC_L, COMBO_END};
const uint16_t PROGMEM und_combo[] = {LSFT_T(KC_D), RSFT_T(KC_H), COMBO_END};
const uint16_t PROGMEM cap_combo[] = {LCTL_T(KC_Z), RCTL_T(KC_SLASH), COMBO_END};
// clang-format off
combo_t key_combos[] = {
    COMBO(grv_combo, KC_GRAVE),
    COMBO(esc_combo, KC_ESCAPE),
    COMBO(hyp_combo, KC_MINUS),
    COMBO(und_combo, LSFT(KC_MINUS)),
    COMBO(cap_combo, QK_CAPS_WORD_TOGGLE),
};
// clang-format on

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [COLEMAK] = LAYOUT_3x5_3(
// Left hand
          KC_Q,           KC_W,           KC_F,           KC_P,           KC_B,
          KC_A,           KC_R,           KC_S,           KC_T,           KC_G,
  LCTL_T(KC_Z),   LALT_T(KC_X),   LGUI_T(KC_C),   LSFT_T(KC_D),    ALL_T(KC_V),
                                        KC_TAB,          MO(3),          MO(2),
// Right hand
            KC_J,           KC_L,             KC_U,           KC_Y,          KC_SCLN,
            KC_M,           KC_N,             KC_E,           KC_I,             KC_O,
     ALL_T(KC_K),   RSFT_T(KC_H), RGUI_T(KC_COMMA), RALT_T(KC_DOT), RCTL_T(KC_SLASH),
  LT(4, KC_BSPC),       KC_SPACE,         KC_ENTER
    ),
    [GAMING] = LAYOUT_3x5_3(
// Left hand
          KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,
          KC_A,           KC_S,           KC_D,           KC_F,           KC_G,
          KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,
                                        KC_TAB,          MO(4),          MO(3),
// Right hand
            KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,
            KC_H,           KC_J,           KC_K,           KC_L,        KC_SCLN,
            KC_N,           KC_M,       KC_COMMA,         KC_DOT,       KC_SLASH,
  LT(4, KC_BSPC),       KC_SPACE,       KC_ENTER
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
        KC_COMMA,        KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_BSLS,
          KC_DOT,        KC_KP_4,        KC_KP_5,        KC_KP_6,       KC_QUOTE,
         KC_KP_0,        KC_KP_1,        KC_KP_2,        KC_KP_3,    KC_KP_EQUAL,
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
