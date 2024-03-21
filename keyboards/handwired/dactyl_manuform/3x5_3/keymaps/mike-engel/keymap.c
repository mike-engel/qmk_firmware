#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
// #define _FN     1
// #define _NUMPAD 2

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable   = true;
    debug_matrix   = true;
    debug_keyboard = true;
    // debug_mouse=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
    return true;
}

tap_dance_action_t tap_dance_actions[] = {};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
    // left hand
        KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,
        KC_A,    KC_S,    KC_D,   KC_F,   KC_G,
        KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,
                        KC_SPC, KC_END, KC_HOME,
            // right hand
                        KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,
                        KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,
                        KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,
            KC_BSPC, KC_ENT, KC_PGUP
    )
};
