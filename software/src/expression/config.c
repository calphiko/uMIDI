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
 * The uMIDI firmware is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the uMIDI firmware.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Device configuration.
 * @author Sebastian Neuser
*/

#include <stddef.h>

#include "lib/adc.h"
#include "lib/gpio.h"
#include "lib/leds.h"
#include "lib/midi.h"
#include "lib/state_machine.h"

#include "config.h"
#include "expression.h"


////////////////////////////////////////////////////////////////
//                     V A R I A B L E S                      //
////////////////////////////////////////////////////////////////

//---------------- ADC ----------------//
const struct adc_config adc_config = {
    .mode       = ADC_MODE_UNSIGNED,
    .prescaler  = ADC_PRESCALER_DIV512_gc,
};

//---------------- GPIO ----------------//
struct gpio_config gpio_config = {
    .header1 = {
        .pin2 = { &PORTA, 0, GPIO_UNUSED },
        .pin3 = { &PORTA, 1, GPIO_UNUSED },
        .pin4 = { &PORTA, 2, GPIO_UNUSED },
        .pin5 = { &PORTA, 3, GPIO_UNUSED },
        .pin6 = { &PORTA, 4, GPIO_INPUT },
        .pin7 = { &PORTA, 5, GPIO_UNUSED },
        .pin8 = { &PORTA, 6, GPIO_UNUSED },
        .pin9 = { &PORTA, 7, GPIO_UNUSED }
    },
    .header2 = {
        .pin2 = { &PORTB, 0, GPIO_UNUSED },
        .pin3 = { &PORTB, 1, GPIO_UNUSED },
        .pin4 = { &PORTB, 2, GPIO_UNUSED },
        .pin5 = { &PORTB, 3, GPIO_UNUSED },
        .pin6 = { &PORTC, 0, GPIO_UNUSED },
        .pin7 = { &PORTC, 1, GPIO_UNUSED },
        .pin8 = { &PORTC, 2, GPIO_UNUSED },
        .pin9 = { &PORTC, 3, GPIO_UNUSED }
    },
    .header3 = {
        .pin2 = { &PORTC, 4, GPIO_UNUSED },
        .pin3 = { &PORTC, 5, GPIO_UNUSED },
        .pin4 = { &PORTC, 6, GPIO_UNUSED },
        .pin5 = { &PORTC, 7, GPIO_UNUSED },
        .pin6 = { &PORTD, 0, GPIO_UNUSED },
        .pin7 = { &PORTD, 1, GPIO_UNUSED },
        .pin8 = { &PORTD, 2, GPIO_UNUSED },
        .pin9 = { &PORTD, 3, GPIO_UNUSED }
    }
};

//---------------- MIDI ----------------//
struct midi_event_handlers midi_event_handlers = {
    .control_change = NULL,
    .note_off       = NULL,
    .note_on        = NULL,
    .program_change = NULL
};

//---------------- State machine ----------------//
state_machine_task_t high_frequency_tasks[] = {};
uint8_t high_frequency_tasks_size = sizeof(high_frequency_tasks)/sizeof(state_machine_task_t);

state_machine_task_t mid_frequency_tasks[] = {
    &trigger_expression_conversion,
};
uint8_t mid_frequency_tasks_size = sizeof(mid_frequency_tasks)/sizeof(state_machine_task_t);

state_machine_task_t low_frequency_tasks[] = {
    &update_leds,
};
uint8_t low_frequency_tasks_size = sizeof(low_frequency_tasks)/sizeof(state_machine_task_t);
