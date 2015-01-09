/*
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "keycode.h"
#include "action.h"
#include "action_util.h"
#include "action_code.h"
#include "action_macro.h"
#include "action_layer.h"
#include "bootloader.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"
#include "ergodox.h"


/* ErgoDox keymap definition macro */
#define KEYMAP(                                                                          \
                                                                                         \
    /* spatial positions */                                                              \
    k00,k01,k02,k03,k04,k05,k06,                            k07,k08,k09,k0A,k0B,k0C,k0D, \
    k10,k11,k12,k13,k14,k15,k16,                            k17,k18,k19,k1A,k1B,k1C,k1D, \
    k20,k21,k22,k23,k24,k25,                                    k28,k29,k2A,k2B,k2C,k2D, \
    k30,k31,k32,k33,k34,k35,k36,    k55,k56,    k57,k58,    k37,k38,k39,k3A,k3B,k3C,k3D, \
    k40,k41,k42,k43,k44,        k53,k52,k54,    k59,k5B,k5A,        k49,k4A,k4B,k4C,k4D, \
                                        k51,    k5C                                      \
   )                                                                                     \
   /* matrix positions */                                                                \
   {                                                                                     \
    { KC_##k00,KC_##k10,KC_##k20,KC_##k30,KC_##k40,KC_NO   },                            \
    { KC_##k01,KC_##k11,KC_##k21,KC_##k31,KC_##k41,KC_##k51},                            \
    { KC_##k02,KC_##k12,KC_##k22,KC_##k32,KC_##k42,KC_##k52},                            \
    { KC_##k03,KC_##k13,KC_##k23,KC_##k33,KC_##k43,KC_##k53},                            \
    { KC_##k04,KC_##k14,KC_##k24,KC_##k34,KC_##k44,KC_##k54},                            \
    { KC_##k05,KC_##k15,KC_##k25,KC_##k35,KC_NO,   KC_##k55},                            \
    { KC_##k06,KC_##k16,KC_NO,   KC_##k36,KC_NO,   KC_##k56},                            \
                                                                                         \
    { KC_##k07,KC_##k17,KC_NO,   KC_##k37,KC_NO,   KC_##k57},                            \
    { KC_##k08,KC_##k18,KC_##k28,KC_##k38,KC_NO,   KC_##k58},                            \
    { KC_##k09,KC_##k19,KC_##k29,KC_##k39,KC_##k49,KC_##k59},                            \
    { KC_##k0A,KC_##k1A,KC_##k2A,KC_##k3A,KC_##k4A,KC_##k5A},                            \
    { KC_##k0B,KC_##k1B,KC_##k2B,KC_##k3B,KC_##k4B,KC_##k5B},                            \
    { KC_##k0C,KC_##k1C,KC_##k2C,KC_##k3C,KC_##k4C,KC_##k5C},                            \
    { KC_##k0D,KC_##k1D,KC_##k2D,KC_##k3D,KC_##k4D,KC_NO   }                             \
   }  

#if defined(KEYMAP_DVORAK)
#include "keymap_dvorak.h"
#elif defined(KEYMAP_COLEMAK)
#include "keymap_colemak.h"
#elif defined(KEYMAP_WORKMAN)
#include "keymap_workman.h"
#elif defined(KEYMAP_MICRO)
#include "keymap_micro.h"
#elif defined(KEYMAP_CUB)
#include "keymap_cub.h"
#else

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// Layer0
KEYMAP(
    NO  , NO  , NO  , NO  , NO  , NO  , NO  ,                                           NO  , NO  , NO  , NO  , NO  , NO  , NO  ,
    DEL , BSPC, D   , R   , W   , B   , NO  ,                                           NO  , J   , F   , U   , P   , LBRC, RBRC,
    Q   , A   , S   , FN3 , T   , G   ,                                                       Y   , N   , E   , O   , I   , QUOT,
    FN8 , Z   , X   , M   , C   , V   , INS ,       GRV , 2   ,       RALT, END ,       HOME, K   , L   , COMM, DOT , SLSH, FN9 ,
    NO  , LALT, FN20, TAB , FN24,             FN4 , FN2 , 1   ,       RGUI, FN22, FN1 ,            LEFT, UP  , DOWN, RGHT, NO  ,
                                                          FN7 ,       RCTL
),

// Layer1 - original Kinesis
KEYMAP(
    EQL , 0   , 1   , 2   , 3   , 4   , NO  ,                                           NO  , 5   , 6   , 7   , 8   , 9   , MINS,
    TAB , Q   , W   , E   , R   , T   , NO  ,                                           NO  , Y   , U   , I   , O   , P   , BSLS,
    CAPS, A   , S   , D   , F   , G   ,                                                       H   , J   , K   , L   , SCLN, QUOT,
    LSFT, Z   , X   , C   , V   , B   , NO  ,       LCTL, LALT,       RGUI, RCTL,       NO  , N   , M   , COMM, DOT , SLSH, RSFT,
    NO  , GRV , BSLS, LEFT, RGHT,             BSPC, DEL , HOME,       PGUP, ENT , FN1 ,             UP  , DOWN, LBRC, RBRC, NO  ,
                                                          END ,       PGDN
),

// Layer2
KEYMAP(
    NO  , NO  , NO  , NO  , NO  , NO  , NO  ,                                           NO  , NO  , NO  , NO  , NO  , NO  , NO  ,
    TRNS, TRNS, F7  , F12 , F11 , F1  , NO  ,                                           NO  , TRNS, TRNS, 4   , 5   , TRNS, TRNS,
    TRNS, F10 , F2  , TRNS, F4  , F3  ,                                                       3   , 1   , 0   , 2   , 7   , EQL ,
    TRNS, F9  , F8  , F6  , F5  , TRNS, PSCR,       TRNS, F18 ,       TRNS, PGDN,       PGUP, 6   , 9   , 8   , TRNS, TRNS, PPLS,
    NO  , TRNS, TRNS, SPC , TRNS,             FN21, TRNS, FN0 ,       TRNS, FN23, TRNS,             HOME, PGUP, PGDN, END , NO  ,
                                                          MINS,       TRNS
),
// Layer3
KEYMAP(
    NO  , NO  , NO  , NO  , NO  , NO  , NO  ,                                           NO  , NO  , NO  , NO  , NO  , NO  , NO  ,
    TRNS, TRNS, F7  , F12 , F11 , F1  , NO  ,                                           NO  , TRNS, TRNS, FN14, FN15, TRNS, TRNS,
    FN31, F10 , F2  , TRNS, F4  , F3  ,                                                       FN13, FN11, FN10, FN12, FN17, EQL ,
    TRNS, F9  , F8  , F6  , F5  , TRNS, PSCR,       TRNS, F18 ,       TRNS, PGDN,       PGUP, FN16, FN19, FN18, TRNS, TRNS, PPLS,
    NO  , TRNS, TRNS, SPC , TRNS,             FN21, TRNS, FN0 ,       TRNS, FN23, TRNS,             HOME, PGUP, PGDN, END , NO  ,
                                                          MINS,       TRNS
),

};

/* id for user defined functions */
enum function_id {
    TEENSY_KEY,
};

/*
 * Fn action definition
 */
static const uint16_t PROGMEM fn_actions[] = {
    [ 0] = ACTION_FUNCTION(TEENSY_KEY),                    // FN0  - Teensy key - reboot to programmator mode
    // [ 1] = ACTION_LAYER_MOMENTARY(1),
    [ 1] = ACTION_LAYER_TAP_KEY(3, KC_SPC),
    [ 2] = ACTION_LAYER_TAP_KEY(2, KC_ESC),
    [ 3] = ACTION_LAYER_TAP_KEY(2, KC_H),
    // [ 4] = ACTION_LAYER_TOGGLE(1),
    [ 4] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_ENT),
    // [ 5] = ACTION_MODS_KEY(MOD_LGUI | MOD_LSFT, KC_0),
    // [ 6] = ACTION_MODS_KEY(MOD_LALT | MOD_LSFT, KC_V),
    [ 7] = ACTION_MODS_KEY(MOD_LGUI, KC_Z), // UNDO shortcut
    // [ 8] = ACTION_MODS(MOD_LALT | MOD_LGUI | MOD_LCTL),
    [ 8] = ACTION_MODS_TAP_KEY(MOD_LALT | MOD_LGUI | MOD_LCTL, KC_SCLN), // META combo MOD_LALT | MOD_LGUI | MOD_LCTL
    [ 9] = ACTION_MODS_TAP_KEY(MOD_LALT | MOD_LGUI | MOD_LCTL, KC_MINS), // META combo MOD_LALT | MOD_LGUI | MOD_LCTL

    [10] = ACTION_MODS_KEY(MOD_LSFT, KC_0),
    [11] = ACTION_MODS_KEY(MOD_LSFT, KC_1),
    [12] = ACTION_MODS_KEY(MOD_LSFT, KC_2),
    [13] = ACTION_MODS_KEY(MOD_LSFT, KC_3),
    [14] = ACTION_MODS_KEY(MOD_LSFT, KC_4),
    [15] = ACTION_MODS_KEY(MOD_LSFT, KC_5),
    [16] = ACTION_MODS_KEY(MOD_LSFT, KC_6),
    [17] = ACTION_MODS_KEY(MOD_LSFT, KC_7),
    [18] = ACTION_MODS_KEY(MOD_LSFT, KC_8),
    [19] = ACTION_MODS_KEY(MOD_LSFT, KC_9),

    [20] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_GRV),
    [21] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_F16),
    [22] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_BSLS),
    [23] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_F17),
    [24] = ACTION_MODS_ONESHOT(MOD_LGUI),
    // [25] = ACTION_MODS_KEY(MOD_LGUI, KC_ENT),

    // [29] = ACTION_MACRO(C_COMMENT),
    // [30] = ACTION_MODS_KEY(MOD_LCTL|MOD_LALT|MOD_LGUI, KC_F), // ACTION_MACRO(JIRA_NOFORMAT),
    // [31] = ACTION_MODS_KEY(MOD_LCTL|MOD_LALT|MOD_LGUI, KC_Q), // ACTION_MACRO(JIRA_QUOTE),
    [31] = ACTION_LAYER_TOGGLE(1),
};

void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
    if (id == TEENSY_KEY) {
        clear_keyboard();
        print("\n\nJump to bootloader... ");
        _delay_ms(250);
        bootloader_jump(); // should not return
        print("not supported.\n");
    }
}

#endif


#define KEYMAPS_SIZE    (sizeof(keymaps) / sizeof(keymaps[0]))
#define FN_ACTIONS_SIZE (sizeof(fn_actions) / sizeof(fn_actions[0]))

/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, key_t key)
{
    if (layer < KEYMAPS_SIZE) {
        return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
    } else {
        // fall back to layer 0
        return pgm_read_byte(&keymaps[0][(key.row)][(key.col)]);
    }
}

#if defined(KEYMAP_CUB)

// function keymap_fn_to_action will be defined in keymap_cub.h

#else
/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
    action_t action;
    if (FN_INDEX(keycode) < FN_ACTIONS_SIZE) {
        action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
    } else {
        action.code = ACTION_NO;
    }
    return action;
}
#endif

