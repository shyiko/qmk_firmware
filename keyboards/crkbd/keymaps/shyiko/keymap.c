#include QMK_KEYBOARD_H

// layers
// https://beta.docs.qmk.fm/using-qmk/software-features/feature_layers
#define L_QWERTY 0
#define L_LOWER 1
#define L_LOWER_SHIFT 2
#define L_RAISE 3
#define L_RAISE_J 4
#define L_ADJUST 5 // LOWER+RAISE
#define L_MOUSE 6

// custom key codes for layer switching
enum kc_custom {
  LOWER = SAFE_RANGE,
  RAISE,
  RAISE_J
};

#include "keymap_layers.h"

bool register_lshift_on_next_key = false;
bool unregister_lctrl_on_next_key = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (unregister_lctrl_on_next_key) {
    unregister_code(KC_LCTL);
    unregister_lctrl_on_next_key = false;
  }
  if (register_lshift_on_next_key) {
    register_code(KC_LSFT);
    register_lshift_on_next_key = false;
  }
  if (IS_LAYER_ON(L_LOWER_SHIFT) && !IS_LAYER_ON(L_RAISE)) {
    switch (keycode) {
      case KC_GRAVE: case KC_MINUS: case KC_EQUAL:
      case KC_LBRC: case KC_RBRC: case KC_BSLASH:
      case KC_SCLN: case KC_QUOT:
      case KC_COMM: case KC_DOT: case KC_SLSH:
      case KC_1: case KC_2: case KC_3: case KC_4: case KC_5:
      case KC_6: case KC_7: case KC_8: case KC_9: case KC_0:
      case KC_KP_MINUS: case KC_KP_PLUS:
      case KC_PGUP: case KC_PGDOWN:
        if (record->event.pressed) {
            unregister_code(KC_LSFT);
        } else {
            register_lshift_on_next_key = true;
        }
        break; // let qmk handle keycode as usual
      case KC_HOME: case KC_END:
        if (record->event.pressed) {
            unregister_code(KC_LSFT);
            register_code(KC_LCTL);
        } else {
            register_lshift_on_next_key = true;
            unregister_lctrl_on_next_key = true;
        }
        break; // let qmk handle keycode as usual
      case LOWER:
      case KC_LSFT:
        break;
      default:
        register_code(KC_LSFT);
        break; // let qmk handle keycode as usual
    }
  }
  switch (keycode) {
    case KC_BSLASH:
      if (get_mods() & MOD_BIT(KC_LSFT)) {
        unregister_code(KC_LSFT);
        register_lshift_on_next_key = true;
      }
      break; // let qmk handle keycode as usual
    case KC_LSFT:
      if (!IS_LAYER_ON(L_LOWER)) {
        break; // let qmk handle keycode as usual
      }
      if (record->event.pressed) {
        layer_on(L_LOWER_SHIFT);
      } else {
        layer_off(L_LOWER_SHIFT);
        register_lshift_on_next_key = false;
      }
      break; // let qmk handle keycode as usual
    case LOWER:
      if (record->event.pressed) {
        layer_on(L_LOWER);
        if (get_mods() & MOD_BIT(KC_LSFT)) {
          layer_on(L_LOWER_SHIFT);
        }
      } else {
        layer_off(L_LOWER_SHIFT);
        register_lshift_on_next_key = false;
        layer_off(L_LOWER);
      }
      update_tri_layer(L_LOWER, L_RAISE, L_ADJUST);
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(L_RAISE);
      } else {
        layer_off(L_RAISE);
      }
      update_tri_layer(L_LOWER, L_RAISE, L_ADJUST);
      return false;
    case RAISE_J:
      if (record->event.pressed) {
        layer_on(L_RAISE_J);
      } else {
        layer_off(L_RAISE_J);
      }
      return false;
  }
  return true;
}
