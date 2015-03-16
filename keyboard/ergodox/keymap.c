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


/* id for user defined functions */
enum function_id {
    TEENSY_KEY,
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

////////////////////////////////////////////////////////////////////////////

// ERGODOX keymaps. Rendered automatically in https://docs.google.com/spreadsheets/d/1UNBirTlrECQJ08_CumkZXu8rqGTfGoYYeWQ7XA4az-4/edit
static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Layer0
KEYMAP(

    MINS, 1   , 2   , NO  , NO  , NO  , NO  ,                               NO  , NO  , NO  , NO  , VOLD, VOLU, MUTE,
    ESC , BSPC, D   , R   , W   , B   , NO  ,                               NO  , J   , F   , U   , P   , EQL , PAST,
    Q   , A   , S   , H   , T   , G   ,                                           Y   , N   , E   , O   , I   , QUOT,
    F19 , Z   , X   , M   , C   , V   , NO  , NO  , NO  ,       NO  , NO  , NO  , K   , L   , COMM, DOT , SLSH, MINS,
    NO  , GRV , FN22, FN21, FN20,       FN24, FN2 , NO  ,       NO  , FN31, FN1 ,       FN25, FN27, FN29, RGHT, NO  ,
                                                    PSCR,       F18 
),

// Layer1
KEYMAP(

    TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, NO  ,                               NO  , TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
    TRNS, DEL , 7   , 4   , F17 , F16 , NO  ,                               NO  , F14 , F15 , F4  , F8  , TRNS, TRNS,
    TRNS, 3   , 9   , 0   , SPC , LBRC,                                           F12 , F7  , F10 , F9  , F3  , TRNS,
    TRNS, 6   , 1   , 5   , 2   , RBRC, NO  , TRNS, TRNS,       TRNS, TRNS, NO  , SCLN, F2  , F5  , F11 , F6  , TRNS,
    NO  , TRNS, TRNS, TRNS, TRNS,       FN23, TRNS, TRNS,       FN0 , TRNS, TRNS,       FN26, FN28, FN30, END , NO  ,
                                                    TRNS,       TRNS
),

// Layer2
KEYMAP(

    TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, NO  ,                               NO  , TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
    TRNS, TRNS, F7  , F4  , F15 , F14 , NO  ,                               NO  , F16 , F17 , 4   , 7   , TRNS, TRNS,
    SPC , F3  , F9  , F10 , F7  , F12 ,                                           TRNS, 8   , 0   , 9   , 3   , TRNS,
    TRNS, F6  , F11 , F5  , F2  , PSCR, NO  , TRNS, TRNS,       TRNS, TRNS, NO  , TRNS, 2   , 5   , 1   , 6   , TRNS,
    NO  , TRNS, TRNS, TRNS, TRNS,       TRNS, TRNS, TRNS,       TRNS, TRNS, TRNS,       TRNS, TRNS, TRNS, TRNS, NO  ,
                                                    TRNS,       TRNS
),

// Layer3 - original Kinesis
KEYMAP(

    EQL , 1   , 2   , 3   , 4   , 5   , NO  ,                               NO  , 6   , 7   , 8   , 9   , 0   , MINS,
    TAB , Q   , W   , E   , R   , T   , NO  ,                               NO  , Y   , U   , I   , O   , P   , BSLS,
    FN3 , A   , S   , D   , F   , G   ,                                           H   , J   , K   , L   , SCLN, QUOT,
    LSFT, Z   , X   , C   , V   , B   , NO  , LCTL, LALT,       RGUI, RCTL, NO  , N   , M   , COMM, DOT , SLSH, RSFT,
    NO  , GRV , INS , LEFT, RGHT,       BSPC, DEL , HOME,       PGUP, ENT , SPC ,       UP  , DOWN, LBRC, RBRC, NO  ,
                                                    END ,       PGDN
),

};

/*
 * Fn action definition
 */
static const uint16_t PROGMEM fn_actions[] = {
    [ 0] = ACTION_FUNCTION(TEENSY_KEY),
    [ 1] = ACTION_LAYER_TAP_KEY(1, KC_SPC),
    [ 2] = ACTION_LAYER_TAP_KEY(2, KC_DEL),
    [ 3] = ACTION_LAYER_TOGGLE(3),
//  [ 4] = ,
//  [ 5] = ,
//  [ 6] = ,
//  [ 7] = ,
//  [ 8] = ,
//  [ 9] = ,
//  [10] = ,
//  [11] = ,
//  [12] = ,
//  [13] = ,
//  [14] = ,
//  [15] = ,
//  [16] = ,
//  [17] = ,
//  [18] = ,
//  [19] = ,
    [20] = ACTION_MODS_ONESHOT(MOD_LGUI),
    [21] = ACTION_MODS_TAP_KEY(MOD_LALT, KC_TAB),
    [22] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_INS),
    [23] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_8),
    [24] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_ENT),
    [25] = ACTION_MODS_TAP_KEY(MOD_RGUI, KC_LEFT),
    [26] = ACTION_MODS_TAP_KEY(MOD_RGUI, KC_HOME),
    [27] = ACTION_MODS_TAP_KEY(MOD_RALT, KC_UP),
    [28] = ACTION_MODS_TAP_KEY(MOD_RALT, KC_PGUP),
    [29] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_DOWN),
    [30] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_PGDN),
    [31] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_BSLS),
};


////////////////////////////////////////////////////////////////////////////

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
