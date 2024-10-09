#include QMK_KEYBOARD_H
#include "keymap_brazilian_abnt2.h"

enum {
    A_LGUI,
    S_LALT,
    D_LSFT,
    F_LCTL,
    J_RCTL,
    K_RSFT,
    L_RALT,
    CC_RGUI,
};

enum layers { _BASE, _LOWER, _UPPER, _ADJUST };

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;


void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
        #ifndef PERMISSIVE_HOLD
            && !state->interrupted
        #endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }


tap_dance_action_t tap_dance_actions[] = {
    [A_LGUI] = ACTION_TAP_DANCE_TAP_HOLD(KC_A, KC_LGUI),
    [S_LALT] = ACTION_TAP_DANCE_TAP_HOLD(KC_S, KC_LALT),
    [D_LSFT] = ACTION_TAP_DANCE_TAP_HOLD(KC_D, KC_LSFT),
    [F_LCTL] = ACTION_TAP_DANCE_TAP_HOLD(KC_F, KC_LCTL),
    [J_RCTL] = ACTION_TAP_DANCE_TAP_HOLD(KC_J, KC_LCTL),
    [K_RSFT] = ACTION_TAP_DANCE_TAP_HOLD(KC_K, KC_RSFT),
    [L_RALT] = ACTION_TAP_DANCE_TAP_HOLD(KC_L, KC_RALT),
    [CC_RGUI] = ACTION_TAP_DANCE_TAP_HOLD(BR_CCED, KC_RGUI),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        case TD(A_LGUI):  // list all tap dance keycodes with tap-hold configurations
        case TD(S_LALT):  // list all tap dance keycodes with tap-hold configurations
        case TD(D_LSFT):  // list all tap dance keycodes with tap-hold configurations
        case TD(F_LCTL):  // list all tap dance keycodes with tap-hold configurations
        case TD(J_RCTL):  // list all tap dance keycodes with tap-hold configurations
        case TD(K_RSFT):  // list all tap dance keycodes with tap-hold configurations
        case TD(L_RALT):  // list all tap dance keycodes with tap-hold configurations
        case TD(CC_RGUI):  // list all tap dance keycodes with tap-hold configurations
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base (qwerty)
     * +-----------------------------------------+                             +-----------------------------------------+
     * | ESC  |   q  |   w  |   e  |   r  |   t  |                             |   y  |   u  |   i  |   o  |   p  |      |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * | TAB  |   a  |   s  |   d  |   f  |   g  |                             |   h  |   j  |   k  |   l  |   ç  |      |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * | SHFT |   z  |   x  |   c  |   v  |   b  |                             |   n  |   m  |   ,  |   .  |   /  |      |
     * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
     *               |  [   |   ]  |                                                         |      |      |
     *               +-------------+-------------+                             +-------------+-------------+
     *                             |      | ENT  |                             |  SPC  |      |
     *                             |------+------|                             |------+------|
     *                             |      |      |                             |      |      |
     *                             +-------------+                             +-------------+
     *                                           +-------------+ +-------------+
     *                                           |      |      | |      |      |
     *                                           |------+------| |------+------|
     *                                           |      |      | |      |      |
     *                                           +-------------+ +-------------+
     */
    [_BASE] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  TD(A_LGUI),    TD(S_LALT),    TD(D_LSFT),    TD(F_LCTL),    KC_G,               KC_H,    TD(J_RCTL),    TD(K_RSFT),    TD(L_RALT),    TD(CC_RGUI), BR_TILD,
        BR_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,               KC_N,    KC_M,    KC_COMM, KC_DOT,  BR_SCLN, BR_SLSH,
                          _______, _______,                                                _______, _______,
                                            MO(_LOWER),   KC_ENT,             KC_SPC,  MO(_UPPER),
                                            KC_TAB,  KC_HOME,            KC_END,  KC_DEL,
                                            KC_BSPC, KC_GRV,             KC_LGUI, KC_LALT
    ),

    [_LOWER] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,                            BR_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX, XXXXXXX,
        KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          _______, _______,                                                 _______, _______,
                                            _______,  KC_ENT,             KC_SPC, MO(_ADJUST),
                                            _______, _______,             _______, _______,
                                            _______, _______,             _______, _______
    ),

    [_UPPER] = LAYOUT(
        KC_ESC, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                BR_DIAE, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
        KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             KC_MINS, KC_EQL, BR_ACUT, BR_LBRC, BR_RBRC, BR_QUOT,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            KC_UNDS, KC_PLUS, BR_GRV, BR_LCBR, BR_RCBR, BR_DQUO,
                          _______, _______,                                                 _______,  _______,
                                            MO(_ADJUST), KC_ENT,             KC_SPC, _______,
                                            _______, _______,             _______, _______,
                                            _______, _______,             _______, _______
    ),

    [_ADJUST] = LAYOUT(
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             KC_BTN1, KC_BTN2, KC_WH_U, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,             KC_MS_L, KC_MS_U, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX,
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,            XXXXXXX, XXXXXXX, KC_WH_D, XXXXXXX, XXXXXXX, XXXXXXX,
                          _______, _______,                                                 _______,  _______,
                                            _______, KC_SPC,             KC_ENT, _______,
                                            _______, _______,             _______, _______,
                                            _______, _______,             _______, _______
    )
};
