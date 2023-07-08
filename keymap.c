#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define QWERTY 0
#define NAV 1
#define SYMB 2
#define NUM 3
#define GERM 4

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
    _______, _______, _______, _______, _______ , _______, _______,     _______, _______, _______, _______, _______, _______ , _______,
    _______, KC_Q   , KC_W   , KC_E   , KC_R    , KC_T   , _______,     _______, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P    , _______,
    _______, MT(MOD_LSFT,KC_A)   , MT(MOD_LCTL, KC_S)   , MT(MOD_LGUI, KC_D)   , MT(MOD_LALT, KC_F)    , KC_G   , _______,     _______, KC_H   , MT(MOD_RALT, KC_J)   , MT(MOD_RGUI, KC_K)   , MT(MOD_RCTL, KC_L)   , MT(MOD_RSFT, KC_SCLN), _______,
    _______, KC_Z   , KC_X   , KC_C   , KC_V    , KC_B   , _______,     _______, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, _______,
    _______, _______, _______, _______, MT(MOD_LSFT, KC_ESC)  , LT(SYMB, KC_SPC) , LT(NAV, KC_ENT),      LT(GERM, KC_TAB),  LT(NUM, KC_BSPC), _______, _______, _______, _______, _______
  ),


  [NAV] = LAYOUT_ortho_5x14(
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, KC_BRIU, KC_VOLU, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, KC_BRID, KC_VOLD, _______, _______,     _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RIGHT,_______, _______,
    _______, _______, _______, KC_MPLY, KC_MUTE, _______, _______,     _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END , _______, _______,
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______
  ),
  [SYMB] = LAYOUT_ortho_5x14(
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    _______, KC_PLUS, KC_EQL , KC_MINS, KC_UNDS, _______, _______,     _______, _______, KC_QUOTE,KC_DQUO, KC_PIPE, KC_BSLS, _______,
    _______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, _______,     _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______, KC_GRV , KC_TILD, _______, _______, KC_PSCR, _______,     _______, _______, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, _______,
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______
  ),
  [NUM] = LAYOUT_ortho_5x14(
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______,     _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , _______,
    _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , _______,     _______, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,
    _______, KC_F11 , KC_F12 , _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______
  ),
  [GERM] = LAYOUT_ortho_5x14(
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, UUML   , _______, OUML   , _______, _______,
    _______, AUML   , SZ     , _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______
  ),
};


enum combo_events {
    THUMB_DEL,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM thumb_del[] = {LT(GERM, KC_TAB),  LT(NUM, KC_BSPC), COMBO_END};
combo_t key_combos[] = {
    [THUMB_DEL] = COMBO(thumb_del, KC_DEL),
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
