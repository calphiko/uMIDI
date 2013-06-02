/*
 * Copyright 2012, 2013 Sebastian Neuser
 *
 * This file is part of the MIDI wah controller firmware.
 *
 * The MIDI wah controller firmware is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The MIDI wah controller firmware is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the MIDI wah controller firmware.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * midi I/O header
 * @author Sebastian Neuser
*/

#ifndef _MIDI_H
#define _MIDI_H


//---------------- includes ----------------//
#include <avr/io.h>
#include <avr/interrupt.h>


//---------------- constants ----------------//
// MIDI baudrate
#define     BAUD                        31250

// maximum MIDI value
#define     MIDI_MAX_VALUE              127

// MIDI status byte
#define     MIDI_COMMAND_MASK           0xf0
#define     MIDI_PROGRAM_CHANGE         0xc0
#define     MIDI_CONTROL_CHANGE         0xb0
#define     MIDI_NOTE_ON                0x90

// MIDI data byte 0 for NOTE ON commands
#define     CMD_PEDAL_MODE              0x00
#define     CMD_AUTO_MODE_SAW_UP        0x01
#define     CMD_AUTO_MODE_SAW_DOWN      0x02
#define     CMD_AUTO_MODE_SQUARE        0x04
#define     CMD_AUTO_MODE_STAIRS        0x05
#define     CMD_AUTO_MODE_TRIANGLE      0x03
#define     CMD_TAP_TEMPO               0x10

// MIDI data byte 0 for CONTROL CHANGE commands
#define     CTRL_WAH                    0x01
#define     CTRL_SPEED                  0x07


//---------------- data types ----------------//
// codes for MIDI state machine
typedef enum {
    IDLE,
    NOTE_ON,
    CONTROL_CHANGE,
    PROGRAM_CHANGE,
    SET_WAH,
    SET_SPEED
} midi_state_t;


//---------------- functions and procedures ----------------//
void configureUSART( void );


//---------------- EOF ----------------//
#endif // _MIDI_H
