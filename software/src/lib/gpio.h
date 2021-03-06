/// \file
/// \brief  GPIO configuration and service functions

/*
 * Copyright 2012-2015 Sebastian Neuser
 *
 * This file is part of the uMIDI firmware.
 *
 * The uMIDI firmware is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The uMIDI firmware is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the uMIDI firmware.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _GPIO_H
#define _GPIO_H


//---------------- includes ----------------//
#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>


//---------------- data types ----------------//

/// \brief      Function / type of a GPIO pin
enum gpio_type
{
    GPIO_INPUT,                     ///< The GPIO pin acts as an input
    GPIO_INPUT_PULLDOWN,            ///< The GPIO pin acts as an input and is pulled down
    GPIO_INPUT_PULLUP,              ///< The GPIO pin acts as an input and is pulled up
    GPIO_OUTPUT,                    ///< The GPIO pin acts as an output
    GPIO_UNUSED                     ///< The GPIO pin is not used
                                    ///  Unused pins are configured as outputs and connected to GND
};

/// \brief      Configuration of a single GPIO pin
/// \see        iox128a4u.h
struct gpio_pin
{
    PORT_t*             port;       ///< The corresponding AVR I/O port registers as defined in the
                                    ///  AVR gcc headers
    uint8_t             bit;        ///< The corresponding bit index in the configuration registers
    enum gpio_type      type;       ///< Function / type of the pin
};

/// \brief      Configurations of the GPIO pins contained in one 10-pin header
/// \details    The pins 1 and 10 are reserved for \f$V_{cc}\f$ and GND respectively.
struct gpio_header
{
    struct gpio_pin     pin2;       ///< Pin 2 in the pin header on the PCB
    struct gpio_pin     pin3;       ///< Pin 3 in the pin header on the PCB
    struct gpio_pin     pin4;       ///< Pin 4 in the pin header on the PCB
    struct gpio_pin     pin5;       ///< Pin 5 in the pin header on the PCB
    struct gpio_pin     pin6;       ///< Pin 6 in the pin header on the PCB
    struct gpio_pin     pin7;       ///< Pin 7 in the pin header on the PCB
    struct gpio_pin     pin8;       ///< Pin 8 in the pin header on the PCB
    struct gpio_pin     pin9;       ///< Pin 9 in the pin header on the PCB
};

/// \brief      Configurations for all available GPIO pins
struct gpio_config
{
    struct gpio_header  header1;    ///< Pin header GPIO1 on the PCB
    struct gpio_header  header2;    ///< Pin header GPIO2 on the PCB
    struct gpio_header  header3;    ///< Pin header GPIO3 on the PCB
};


//---------------- functions and procedures ----------------//

/// \brief      Enables a GPIO output pin
/// \param      pin
///                 the GPIO pin
static inline void gpio_drive_high(struct gpio_pin pin) {
    pin.port->OUT |= _BV(pin.bit);
}

/// \brief      Disables a GPIO output pin
/// \param      pin
///                 the GPIO pin
static inline void gpio_drive_low(struct gpio_pin pin) {
    pin.port->OUT &=~ _BV(pin.bit);
}

/// \brief      Reads the state of a GPIO input pin
/// \param      pin
///                 the GPIO pin
/// \return     `true` if the input pin is driven high; `false` otherwise
static inline bool gpio_get(struct gpio_pin pin) {
    return pin.port->IN & _BV(pin.bit);
}

/// \brief      Sets a GPIO output pin to the specified state
/// \param      pin
///                 the GPIO pin
/// \param      value
///                 `true` enables the output; `false` disables it
static inline void gpio_set(struct gpio_pin pin, bool value) {
    value ? gpio_drive_high(pin) : gpio_drive_low(pin);
}

/// \brief      Toggles a GPIO output pin
/// \param      pin
static inline void gpio_toggle(struct gpio_pin pin) {
    pin.port->OUT ^= _BV(pin.bit);
}

/// \brief      Initializes the GPIO module
/// \details    Configures all available GPIO pins according to the provided configuration.
/// \param      gpio
///                 the GPIO configuration
void init_gpio_module(struct gpio_config* gpio);


//---------------- EOF ----------------//
#endif // _GPIO_H

