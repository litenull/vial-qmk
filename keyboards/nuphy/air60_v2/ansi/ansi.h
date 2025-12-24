/*
Copyright 2023 @ Nuphy <https://nuphy.com/>

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

#pragma once

#include "quantum.h"

enum custom_keycodes {
    LNK_USB,
    LNK_RF,
    LNK_BLE1,
    LNK_BLE2,
    LNK_BLE3,
    MAC_TASK,
    MAC_SEARCH,
    MAC_VOICE,
    MAC_CONSOLE,
    MAC_DND,
    MAC_PRT,
    MAC_PRTA,

    SIDE_VAI,
    SIDE_VAD,
    SIDE_MOD,
    SIDE_HUI,
    SIDE_SPI,
    SIDE_SPD,

    DEV_RESET,
    SLEEP_MODE,
    BAT_SHOW,
    RGB_TEST,
    SHIFT_GRV,
    BAT_NUM
};


#define DEV_RESET_PRESS_DELAY 30
#define RGB_TEST_PRESS_DELAY  30

#define RF_IDLE             0
#define RF_CONNECT          3
#define RF_DISCONNECT       4

#define LINK_USB         4

#define SYS_SW_WIN        0xa1
#define SYS_SW_MAC        0xa2

#define SLEEP_TIME_DELAY (uint16_t)(100 * 360)

typedef struct
{
    uint8_t link_mode;
    uint8_t rf_channel;
    uint8_t ble_channel;
    uint8_t rf_state;
    uint8_t rf_charge;
    uint8_t rf_led;
    uint8_t rf_baterry;
    uint8_t sys_sw_state;
} DEV_INFO_STRUCT;


typedef struct
{
    uint8_t default_brightness_flag;
    uint8_t ee_side_mode;
    uint8_t ee_side_light;
    uint8_t ee_side_speed;
    uint8_t ee_side_rgb;
    uint8_t ee_side_colour;
    uint8_t sleep_enable;
    uint8_t retain2;
} user_config_t;
