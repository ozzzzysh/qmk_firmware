#include QMK_KEYBOARD_H
#include "ozzzzysh.h"

extern keymap_config_t keymap_config;

__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
    return true;
}

// define a type containing as many tapdance states as you need
typedef enum {
    SINGLE_TAP,
    SINGLE_HOLD,
    DOUBLE_SINGLE_TAP
} td_state_t;

// create a global instance of the tapdance state type
static td_state_t td_state_sft;
static bool caps_lock = false;

// determine the tapdance state to return
int cur_dance (qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) { return SINGLE_TAP; }
        else { return SINGLE_HOLD; }
    }
    if (state->count == 2) { return DOUBLE_SINGLE_TAP; }
    else { return 3; } // any number higher than the maximum state value you return above
}

#define DEBOUNCE_CAPS_DELAY 100

void sft_finished (qk_tap_dance_state_t *state, void *user_data) {
    td_state_sft = cur_dance(state);
    if (td_state_sft == DOUBLE_SINGLE_TAP) {
        if (!caps_lock) {
            register_code(KC_CAPSLOCK);
            return;
        }
    }

    if (caps_lock) {
        register_code(KC_CAPSLOCK);
    } else {
        register_code(KC_LSFT);
    }
}

void sft_reset (qk_tap_dance_state_t *state, void *user_data) {
    if (td_state_sft == DOUBLE_SINGLE_TAP) {
        if (!caps_lock) {
            caps_lock = true;
            wait_ms(DEBOUNCE_CAPS_DELAY);
            unregister_code(KC_CAPSLOCK);
            return;
        }
    }

    if (caps_lock) {
        caps_lock = false;
        wait_ms(DEBOUNCE_CAPS_DELAY);
        unregister_code(KC_CAPSLOCK);
    } else {
        unregister_code(KC_LSFT);
    }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_QUOT_PIPE] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_BSLS),
    [TD_TAB_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_ESC),
    [TD_DOT_SLSH] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_SLSH),
    //Tap once for Shift, twice for Caps Lock
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft_finished, sft_reset)
};

#ifdef AUDIO_ENABLE
    float plover_song[][2]     = SONG(PLOVER_SOUND);
    float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

static float song1[][2] = SONG(MEGALOVANIA);
static float song2[][2] = SONG(RICK_ROLL);
static float song3[][2] = SONG(ALL_STAR);
static float song4[][2] = SONG(OVERWATCH_THEME);

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SONG1:
            if (record->event.pressed) {
                PLAY_SONG(song1);
            }
            return false;
            break;
        case SONG2:
            if (record->event.pressed) {
                PLAY_SONG(song2);
            }
            return false;
            break;
        case SONG3:
            if (record->event.pressed) {
                PLAY_SONG(song3);
            }
            return false;
            break;
        case SONG4:
            if (record->event.pressed) {
                PLAY_SONG(song4);
            }
            return false;
            break;
    }
    return process_record_secrets(keycode, record);
}

// Generated by QMK Configurator
// Copied from the generated configurator_keymap.c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_5x12(KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, TD(TD_QUOT_PIPE), TD(TD_LSFT_CAPS), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, TD(TD_DOT_SLSH), KC_UP, KC_ENT, KC_LCTL, KC_LGUI, KC_LALT, KC_LALT, MO(3), LCTL_T(KC_SPC), KC_SPC, MO(4), LT(6,KC_APP), KC_LEFT, KC_DOWN, KC_RGHT),
	[1] = LAYOUT_ortho_5x12(KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSPC, KC_ESC, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, TD(TD_QUOT_PIPE), TD(TD_LSFT_CAPS), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, TD(TD_DOT_SLSH), KC_UP, KC_ENT, KC_LCTL, KC_LGUI, KC_LALT, KC_LALT, MO(3), LCTL_T(KC_SPC), KC_SPC, MO(4), LT(6,KC_APP), KC_LEFT, KC_DOWN, KC_RGHT),
	[2] = LAYOUT_ortho_5x12(KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, TD(TD_TAB_ESC), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_GRV, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, TD(TD_QUOT_PIPE), TD(TD_LSFT_CAPS), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, TD(TD_DOT_SLSH), KC_UP, KC_ENT, KC_LCTL, KC_LGUI, KC_LALT, MO(3), KC_SPC, KC_SPC, KC_SPC, MO(4), DF(1), KC_LEFT, KC_DOWN, KC_RGHT),
	[3] = LAYOUT_ortho_5x12(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_4, KC_5, KC_6, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_1, KC_2, KC_3, KC_TRNS, KC_VOLU, KC_MPLY, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_0, MO(5), KC_DOT, KC_MPRV, KC_VOLD, KC_MNXT),
	[4] = LAYOUT_ortho_5x12(KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_TRNS, KC_TRNS, KC_LCBR, KC_QUOT, KC_RCBR, KC_TRNS, KC_TRNS, KC_BSPC, KC_UP, KC_BSPC, KC_DEL, KC_BSPC, KC_DEL, KC_TRNS, KC_LPRN, KC_DQUO, KC_RPRN, KC_TRNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, KC_TRNS, KC_TRNS, KC_LT, KC_LBRC, KC_GRV, KC_RBRC, KC_GT, KC_TRNS, KC_ASTG, CK_TOGG, KC_TRNS, CK_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(5), KC_UNDS, KC_UNDS, KC_TRNS, KC_TRNS, KC_TRNS, CK_DOWN, CK_RST),
	[5] = LAYOUT_ortho_5x12(RGB_TOG, RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, RGB_SPI, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD, RGB_M_R, KC_NO, RESET, DF(0), DF(1), DF(2), KC_NO, KC_NO, KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN3, KC_TRNS, KC_NO, KC_BTN1, KC_ACL0, KC_ACL1, KC_ACL2, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, SONG1, SONG2, SONG3, SONG4, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_SECRET_4, KC_SECRET_3, KC_SECRET_2, KC_SECRET_1),
	[6] = LAYOUT_ortho_5x12(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_CALC, LGUI(LSFT(KC_S)), KC_PSCR, KC_NO, KC_NO, LCTL(LSFT(KC_LBRC)), LCTL(KC_QUOT), KC_NO, KC_NO, KC_NO, LCTL(LSFT(KC_TAB)), KC_NO, LCTL(KC_TAB), LGUI(LSFT(KC_S)), KC_PSCR, KC_NO, KC_NO, LCTL(LSFT(KC_9)), LCTL(LSFT(KC_QUOT)), KC_NO, KC_NO, KC_NO, LCTL(LGUI(KC_LEFT)), LGUI(KC_TAB), LCTL(LGUI(KC_RGHT)), KC_NO, KC_NO, KC_NO, LCTL(LSFT(KC_COMM)), LCTL(KC_LBRC), KC_NO, KC_NO, KC_NO, KC_NO, LCTL(KC_Z), KC_NO, LCTL(KC_Y), KC_VOLU, KC_MPLY, KC_NO, AG_TOGG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MPRV, KC_VOLD, KC_MNXT)
};
