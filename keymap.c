#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define QWERTY 0
#define SYMB 1
#define NMPD 2

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE,
  SZ,
  UUML,
  AUML,
  OUML
};

static bool SHIFTED = false;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// QWERTY
  [QWERTY] = LAYOUT_ortho_5x14(
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4    , KC_5   , MO(NMPD),    TG(NMPD),KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_PSCR,
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R    , KC_T   , KC_CAPS,     KC_INS , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS,
    KC_ESC , MT(MOD_LSFT, KC_A)   , MT(MOD_LCTL, KC_S)   , MT(MOD_LGUI, KC_D)   , MT(MOD_LALT, KC_F)    , KC_G   , KC_END ,     KC_PGUP, KC_H   , MT(MOD_RALT, KC_J)   , MT(MOD_RGUI, KC_K)   , MT(MOD_RCTL, KC_L)   , MT(MOD_RSFT, KC_SCLN), KC_QUOT,
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V    , KC_B   , KC_HOME,     KC_PGDN, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LGUI, KC_LALT, KC_RALT, MO(SYMB), KC_SPC , KC_ENT,      KC_DEL,  KC_BSPC, KC_LBRC, KC_RBRC, KC_MINS, KC_EQL , KC_RCTL
  ),

// umlauts and things
  [SYMB] = LAYOUT_ortho_5x14(
    _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F11,      KC_F12,  KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , _______,
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, UUML   , _______, OUML   , _______, _______,
    _______, AUML   , SZ     , _______, _______, _______, _______,     _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RIGHT,_______, _______,
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______
  ),
  [NMPD] = LAYOUT_ortho_5x14(
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, KC_7   , KC_8   , KC_9   , KC_BSLS, _______,
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, KC_4   , KC_5   , KC_6   , KC_ASTR, _______,
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, KC_1   , KC_2   , KC_3   , KC_MINS, _______,
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, KC_0   , KC_0   , KC_DOT , KC_PLUS, _______
  ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_LSFT || keycode == KC_RSFT)
    {
        SHIFTED = record->event.pressed;
    }

    if (record->event.pressed)
    {
        switch (keycode)
        {
            case AUML:
                if (SHIFTED)
                    SEND_STRING (SS_TAP(X_RALT) "\"A");
                else
                    SEND_STRING (SS_TAP(X_RALT) "\"a");
                return false;
            case UUML:
                if (SHIFTED)
                    SEND_STRING (SS_TAP(X_RALT) "\"U");
                else
                    SEND_STRING (SS_TAP(X_RALT) "\"u");
                return false;
            case OUML:
                if (SHIFTED)
                    SEND_STRING (SS_TAP(X_RALT) "\"O");
                else
                    SEND_STRING (SS_TAP(X_RALT) "\"o");
                return false;
            case SZ:
                SEND_STRING (SS_TAP(X_RALT) "ss");
                return false;
        }
    }
  return true;
}
