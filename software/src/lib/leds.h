/*
 * Copyright 2015 Sebastian Neuser
 *
 * This file is part of the uMIDI firmware.
 *
 * the uMIDI firmware is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * the uMIDI firmware is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the uMIDI firmware.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Header for handling of LED GPIO ports
*/

#ifndef _LEDS_H
#define _LEDS_H


//---------------- includes ----------------//
#include <stdbool.h>
#include <avr/io.h>


//---------------- constants ----------------//
#define     LED_COUNT               2


//---------------- AVR PORT mapping ----------------//
#define     LED_PORT                PORTE


//---------------- AVR bit numbers ----------------//
#define     RED_LED_BIT             0
#define     GREEN_LED_BIT           1


//---------------- data types ----------------//
enum led
{
    LED_ALL     = -1,
    LED_GREEN   = GREEN_LED_BIT,
    LED_RED     = RED_LED_BIT,
};

enum led_mode
{
    LED_STATIC,
    LED_FLASH,
    LED_BLINK
};

struct led_state
{
    bool            active;
    enum led_mode   mode;
    uint8_t         prescaler;
    uint8_t         counter;
};


//---------------- functions and procedures ----------------//
void initialize_leds_module(void);
void blink_led(enum led, uint8_t);
void flash_led(enum led);
void set_led(enum led, bool);
void toggle_led(enum led);
void update_leds(void);


//---------------- EOF ----------------//
#endif // _LEDS_H