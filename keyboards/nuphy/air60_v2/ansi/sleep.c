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

#include "ansi.h"
#include "hal_usb.h"
#include "usb_main.h"

extern void m_break_all_key(void);
extern user_config_t    user_config;
extern DEV_INFO_STRUCT  dev_info;
extern uint16_t         no_act_time;

extern bool             f_wakeup_prepare;
extern bool             f_goto_sleep;


/**
 * @brief  Sleep Handle.
 */
void Sleep_Handle(void) {
    static uint32_t delay_step_timer = 0;
    static uint8_t  usb_suspend_debounce = 0;

    /* 50ms interval */
    if (timer_elapsed32(delay_step_timer) < 50) return;
    delay_step_timer = timer_read32();

    if (f_goto_sleep) {
        f_goto_sleep = 0;

        if(user_config.sleep_enable) {
            writePinLow(DC_BOOST_PIN);
            writePinLow(RGB_DRIVER_SDB1);
            writePinLow(RGB_DRIVER_SDB2);
        }

        f_wakeup_prepare = 1;
    }

    if (f_wakeup_prepare && (no_act_time < 10)) {
        f_wakeup_prepare = 0;

        writePinHigh(DC_BOOST_PIN);
        writePinHigh(RGB_DRIVER_SDB1);
        writePinHigh(RGB_DRIVER_SDB2);

        if (dev_info.link_mode == LINK_USB) {
            #define USB_GETSTATUS_REMOTE_WAKEUP_ENABLED (2U)
            if ((USB_DRIVER.status & USB_GETSTATUS_REMOTE_WAKEUP_ENABLED) ) {
                usb_lld_wakeup_host(&USB_DRIVER);
                wait_ms(50);
                uint8_t timeout = 10;
                while ((USB_DRIVER.state == USB_SUSPENDED) && (timeout--)) {
                    usbWakeupHost(&USB_DRIVER);
                    restart_usb_driver(&USB_DRIVER);
                    wait_ms(50);
                }
                m_break_all_key();
            }
        }
    }

    if (f_goto_sleep || f_wakeup_prepare)
        return;

    if (dev_info.link_mode == LINK_USB) {
        if (USB_DRIVER.state == USB_SUSPENDED) {
            usb_suspend_debounce++;
            if (usb_suspend_debounce >= 20) {
                f_goto_sleep = 1;
            }
        } else {
            usb_suspend_debounce = 0;
        }
    }
}
