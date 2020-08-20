// QMK key codes
// https://beta.docs.qmk.fm/using-qmk/simple-keycodes/keycodes
//
// _______ == KC_TRNS (transparent, i.e. pass-through to lower layer)
// XXXXXXX == KC_NO (noop)

// TODO: remove PG*/HOME/END form ADJUST layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [L_QWERTY] = LAYOUT(                                                                                  \
    KC_TAB,  KC_Q, KC_W, KC_E,    KC_R,  KC_T,   /**/ KC_Y,   KC_U,  KC_I,    KC_O,   KC_SCLN, KC_BSPC, \
    KC_LSFT, KC_A, KC_S, KC_D,    KC_F,  KC_G,   /**/ KC_H,   KC_J,  KC_K,    KC_L,   KC_P,    KC_QUOT, \
    KC_LCTL, KC_Z, KC_X, KC_C,    KC_V,  KC_B,   /**/ KC_N,   KC_M,  KC_COMM, KC_DOT, KC_SLSH, EXTRA,   \
                         KC_LALT, LOWER, KC_SPC, /**/ KC_ENT, RAISE, KC_LGUI                            \
  ),

  [L_COLEMAK] = LAYOUT(                                                                                 \
    KC_TAB,  KC_Q, KC_W, KC_F,    KC_P,  KC_G,   /**/ KC_J,   KC_L,  KC_U,    KC_Y,   KC_SCLN, KC_BSPC, \
    KC_LSFT, KC_A, KC_R, KC_S,    KC_T,  KC_D,   /**/ KC_H,   KC_N,  KC_E,    KC_I,   KC_O,    KC_QUOT, \
    KC_LCTL, KC_Z, KC_X, KC_C,    KC_V,  KC_B,   /**/ KC_K,   KC_M,  KC_COMM, KC_DOT, KC_SLSH, EXTRA,   \
                         KC_LALT, LOWER, KC_SPC, /**/ KC_ENT, RAISE, KC_LGUI                            \
  ),

  [L_LOWER] = LAYOUT(                                                                                                            \
    KC_ESC,  KC_EXLM,   KC_AT,   KC_HASH, KC_DLR,   KC_PERC, /**/ KC_CIRC,     KC_AMPR,     KC_ASTR,  KC_LPRN, KC_RPRN, _______, \
    _______, KC_LBRC,   KC_RBRC, KC_QUOT, KC_DQUO,  KC_COLN, /**/ KC_KP_MINUS, KC_UNDS,     KC_EQUAL, KC_LCBR, KC_RCBR, XXXXXXX, \
    _______, KC_BSLASH, KC_LT,   KC_GT,   KC_GRAVE, KC_TILD, /**/ KC_PIPE,     KC_KP_PLUS,  KC_DOT,   KC_SLSH, KC_SLSH, XXXXXXX, \
                                 _______, _______,  _______, /**/ _______,     _______,     _______                              \
  ),

  // NOTE: make sure to update keymap.c if you change this layer
  [L_LOWER_SHIFT] = LAYOUT(                                                                                          \
    _______, _______, _______, _______, _______, _______, /**/ _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, /**/ _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, /**/ _______, _______, _______, _______, _______, _______, \
                               _______, _______, _______, /**/ _______, _______, _______                             \
  ),

  [L_RAISE] = LAYOUT(                                                                                                      \
    _______, KC_F1,   KC_F2,  KC_F3,   KC_F4,   KC_F5,   /**/ KC_F6,     KC_F7,   KC_F8,   KC_F9,    KC_F10,    KC_DELETE, \
    _______, KC_F11,  KC_F12, XXXXXXX, XXXXXXX, XXXXXXX, /**/ KC_PGUP,   KC_HOME, KC_UP,   KC_END,   KC_PGUP,   XXXXXXX,   \
    _______, XXXXXXX, KC_X,   KC_C,    KC_V,    XXXXXXX, /**/ KC_PGDOWN, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDOWN, _______,   \
                              _______, _______, _______, /**/ _______,   _______, TG(L_MOUSE)                              \
  ),

  [L_ADJUST] = LAYOUT(                                                                                                     \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, /**/ XXXXXXX,   XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,   XXXXXXX, \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, /**/ KC_PGUP,   KC_HOME, KC_PGUP,   KC_END,  KC_PGUP,   _______, \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, /**/ KC_PGDOWN, KC_HOME, KC_PGDOWN, KC_END,  KC_PGDOWN, _______, \
                               _______, _______, _______, /**/ _______,   _______, _______                                 \
  ),

  [L_EXTRA] = LAYOUT(                                                                                                   \
    KC_COLN, KC_7, KC_8, KC_9,    KC_0,     KC_PLUS, /**/ KC_BRID, KC_BRIU, LSFT_T(KC_CAPS), KC_PSCR, KC_INS,  _______, \
    _______, KC_4, KC_5, KC_6,    KC_MINUS, KC_ASTR, /**/ XXXXXXX, XXXXXXX, KC_MUTE,         KC_VOLD, KC_VOLU, KC_APP,  \
    _______, KC_1, KC_2, KC_3,    KC_DOT,   KC_SLSH, /**/ XXXXXXX, XXXXXXX, KC_MPLY,         KC_MPRV, KC_MNXT, _______, \
                         _______, _______,  _______, /**/ _______, _______, _______                                     \
  ),

  [L_MOUSE] = LAYOUT(                                                                                                                   \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    /**/ XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX, XXXXXXX, \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    /**/ KC_MS_WH_UP,   KC_MS_BTN1, KC_MS_UP,   KC_MS_BTN2,  XXXXXXX, XXXXXXX, \
    _______, XXXXXXX, KC_X,    KC_C,    KC_V,    XXXXXXX,    /**/ KC_MS_WH_DOWN, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, XXXXXXX, XXXXXXX, \
                               _______, XXXXXXX, KC_MS_BTN1, /**/ KC_MS_BTN2,    XXXXXXX,    TG(L_MOUSE)                                \
  )
};
