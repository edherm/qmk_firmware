/* Copyright 2023 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layers{
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
};

enum custom_keycodes {
    CTL_LEFT = SAFE_RANGE,
    CTL_RGHT,
    FLOW_SHRTCT,
    TMR_NXT,
    TMR_STRT,
    MUT_ZM,
};

enum {
    TD_RTSHFT_CAPS,
    TD_CAPS_CUSTOM,
};

// Function prototypes for tap dance actions
void caps_tap_hold_finished(tap_dance_state_t *state, void *user_data);
void caps_tap_hold_reset(tap_dance_state_t *state, void *user_data);

tap_dance_action_t tap_dance_actions[] = {
    [TD_RTSHFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS),
    [TD_CAPS_CUSTOM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, caps_tap_hold_finished, caps_tap_hold_reset),
};

// Start cmd+k | ctrl+shift
void caps_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        // Single tap: Send Cmd+K
        register_code(KC_LGUI); // Cmd (Mac)
        tap_code(KC_K);         // K
        unregister_code(KC_LGUI);
    } else if (state->pressed) {
        // Hold: Send Ctrl+Shift
        register_code(KC_LCTL); // Ctrl
        register_code(KC_LSFT); // Shift
    }
}

void caps_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        // Release Ctrl+Shift when the key is released
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    }
}
// End cmd+k | ctrl+shift

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case CTL_LEFT:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_LEFT);
                unregister_code(KC_LCTL);
            }
            return false;
        case CTL_RGHT:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_RGHT);
                unregister_code(KC_LCTL);
            }
            return false;
        case FLOW_SHRTCT:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LALT);
                register_code(KC_LSFT);
                register_code(KC_LGUI);
                tap_code(KC_F);
                unregister_code(KC_LGUI);
                unregister_code(KC_LSFT);
                unregister_code(KC_LALT);
                unregister_code(KC_LCTL);
            }
            return false;
        case TMR_NXT:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LOPT);
                register_code(KC_LCMD);
                tap_code(KC_S);
                unregister_code(KC_LCMD);
                unregister_code(KC_LOPT);
                unregister_code(KC_LCTL);
            }
            return false;
        case TMR_STRT:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LOPT);
                register_code(KC_LCMD);
                tap_code(KC_F);
                unregister_code(KC_LCMD);
                unregister_code(KC_LOPT);
                unregister_code(KC_LCTL);
            }
            return false;
        case MUT_ZM:
            if (record->event.pressed) {
                register_code(KC_LSFT);
                register_code(KC_LCMD);
                tap_code(KC_A);
                unregister_code(KC_LCMD);
                unregister_code(KC_LSFT);
            }
            return false;
    }
    return true;
}

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_91_ansi(
        KC_MUTE,  KC_ESC,              KC_BRID,  KC_BRIU,  KC_MCTL,     KC_LPAD,  RM_VALD,   RM_VALU,  KC_MPRV,   KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  FLOW_SHRTCT,  KC_DEL,   KC_MUTE,
        _______,  KC_GRV,              KC_1,     KC_2,     KC_3,        KC_4,     KC_5,      KC_6,     KC_7,      KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,             KC_PGUP,
        _______,  KC_TAB,              KC_Q,     KC_W,     KC_E,        KC_R,     KC_T,      KC_Y,     KC_U,      KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,             KC_PGDN,
        _______,  TD(TD_CAPS_CUSTOM),  KC_A,     KC_S,     KC_D,        KC_F,     KC_G,      KC_H,     KC_J,      KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,              KC_HOME,
        _______,  KC_LSFT,             KC_Z,     KC_X,     KC_C,        KC_V,     KC_B,      KC_N,     KC_M,      KC_COMM,  KC_DOT,   KC_SLSH,              TD(TD_RTSHFT_CAPS),  KC_UP,
        MUT_ZM,   KC_LCTL,             KC_LOPT,  KC_LCMD,  MO(MAC_FN),           KC_SPC,                        KC_SPC,              KC_RCMD,  MO(MAC_FN), KC_RCTL,  KC_LEFT,   KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_91_ansi(
        RM_TOGG,   _______,            KC_F1,    KC_F2,    KC_F3,       KC_F4,     KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   TMR_NXT,                _______,  RM_TOGG,
        _______,   _______,            _______,  _______,  _______,     _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,                          DT_UP,
        _______,   RM_TOGG,            RM_NEXT,  RM_VALU,  RM_HUEU,     RM_SATU,   RM_SPDU,   _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,                          DT_DOWN,
        _______,   _______,            RM_PREV,  RM_VALD,  RM_HUED,     RM_SATD,   RM_SPDD,   _______,  _______,  _______,  _______,  _______,  _______,              _______,                          DT_PRNT,
        _______,   _______,            _______,  _______,  _______,     _______,   _______,   NK_TOGG,  _______,  _______,  _______,  _______,              _______,                _______,
        _______,   _______,            _______,  _______,  _______,               _______,                       _______,            _______,  _______,    _______,  _______,                _______,  _______),

    [WIN_BASE] = LAYOUT_91_ansi(
        KC_MUTE,  KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_INS,                 KC_DEL,   KC_MUTE,
        _______,  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,                          KC_PGUP,
        _______,  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,                          KC_PGDN,
        _______,  KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,                           KC_HOME,
        _______,  KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,                KC_UP,
        _______,  KC_LCTL,  KC_LWIN,  KC_LALT,  MO(WIN_FN),         KC_SPC,                        KC_SPC,             KC_RALT,  MO(WIN_FN), KC_RCTL,  KC_LEFT,                KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_91_ansi(
        RM_TOGG,  _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RM_VALD,   RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,                _______,  RM_TOGG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,                          _______,
        _______,  RM_TOGG,  RM_NEXT,  RM_VALU,  RM_HUEU,  RM_SATU,  RM_SPDU,   _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,                          _______,
        _______,  _______,  RM_PREV,  RM_VALD,  RM_HUED,  RM_SATD,  RM_SPDD,   _______,  _______,  _______,  _______,  _______,  _______,              _______,                          _______,
        _______,  _______,            _______,  _______,  _______,  _______,   _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,                _______,
        _______,  _______,  _______,  _______,  _______,            _______,                       _______,            _______,  _______,    _______,  _______,                _______,  _______),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [MAC_BASE] = { ENCODER_CCW_CW(CTL_LEFT, CTL_RGHT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_FN]   = { ENCODER_CCW_CW(RM_PREV, RM_NEXT), ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_FN]   = { ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(RM_VALD, RM_VALU) }
};
#endif // ENCODER_MAP_ENABLE
