/*
 * Copyright QMK Community
 * Copyright 2021 Tyler Thrailkill (@snowe/@snowe2010) <tyler.b.thrailkill@gmail.com>
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

#ifdef OLED_ENABLE

#    include QMK_KEYBOARD_H
#    include "quantum.h"
#    include "snowe.h"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
    #ifdef EZPLIT_ENABLE
        return OLED_ROTATION_0;
    #endif /* ifdef ARASAKA_ENABLE */
        return OLED_ROTATION_270;
    }
    #ifdef BONGO_ENABLE
        return OLED_ROTATION_180;
    #endif /* ifdef BONGO_ENABLE */
    #ifdef ARASAKA_ENABLE
        return OLED_ROTATION_270;
    #endif /* ifdef ARASAKA_ENABLE */
    #ifdef OCEAN_DREAM_ENABLE
        return OLED_ROTATION_270;
    #endif /* ifdef ARASAKA_ENABLE */
    #ifdef EZPLIT_ENABLE
        return OLED_ROTATION_180;
    #endif /* ifdef ARASAKA_ENABLE */
    return OLED_ROTATION_0;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_ln_P(PSTR("Main"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("Low"), false);
            break;
        case _UPPER:
            oled_write_ln_P(PSTR("Up"), false);
            break;
    }
}

char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }
    if (keycode < 60) {
        name = code_to_name[keycode];
    }

    // update keylog
    snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c", record->event.key.row, record->event.key.col, keycode, name);
}

void oled_render_keylog(void) { oled_write(keylog_str, false); }

#ifdef WPM_ENABLE

void render_bootmagic_status(void) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    oled_write_P(PSTR(""), false);
    if (!keymap_config.swap_lctl_lgui) {
        oled_write_P(logo[1][0], false);
        oled_write_P(PSTR("   "), false);
        oled_write_P(logo[1][1], false);
    } else {
        oled_write_P(logo[0][0], false);
        oled_write_P(PSTR("   "), false);
        oled_write_P(logo[0][1], false);
    }
#    ifndef BONGO_ENABLE
    oled_write_P(PSTR("   "), false);
    oled_write_P(PSTR("WPM: "), false);

    char wpm[6];
    itoa(get_current_wpm(), wpm, 10);
    oled_write_ln(wpm, false);
#    endif
}
#endif /* ifndef WPM_ENABLE */

bool oled_task_user(void) {
    if (is_keyboard_master()) {
#    ifdef ARASAKA_ENABLE
        arasaka_draw();
#    endif
#    ifdef EZPLIT_ENABLE
        ezplit_draw();
#    endif
#    ifdef WPM_ENABLE
        oled_render_layer_state();
        oled_render_keylog();
        render_bootmagic_status();
#    endif

#    ifdef LUNA_ENABLE
        led_usb_state = host_keyboard_led_state();
        render_luna(0, 13);
#    endif
    } else {
#    ifdef OCEAN_DREAM_ENABLE
        render_stars();
#    endif
#    ifdef ARASAKA_ENABLE
        arasaka_draw();
#    endif
#    ifdef BONGO_ENABLE
        draw_bongo(false);
#    endif
#    ifdef EZPLIT_ENABLE
        ezplit_draw();
#    endif
    }
    return false;
}

#endif // OLED_ENABLE
