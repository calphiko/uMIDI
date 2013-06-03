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
 * midi I/O procedures
 * @author Sebastian Neuser
*/

#include "midi.h"
#include "midiWah.h"

#include <util/setbaud.h>


////////////////////////////////////////////////////////////////
//                     V A R I A B L E S                      //
////////////////////////////////////////////////////////////////

extern exec_state_t state;



////////////////////////////////////////////////////////////////
//      F U N C T I O N S   A N D   P R O C E D U R E S       //
////////////////////////////////////////////////////////////////

void configureUSART( void )
{
    // enable RXEN and RXC interrupt
    UCSR0B = _BV(RXCIE0) | _BV(RXEN0);

    // apply UBRR value computed by setbaud.h
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
}



////////////////////////////////////////////////////////////////
//                    I N T E R R U P T S                     //
////////////////////////////////////////////////////////////////

ISR(USART_RX_vect)
{
    // fetch data
    uint8_t data = UDR0;

    switch (state.midi) {
        ////
        // MIDI status byte
        ////
        case IDLE:
            if ( (data & MIDI_COMMAND_MASK) == MIDI_NOTE_ON )
                state.midi = NOTE_ON;
            else if ( (data & MIDI_COMMAND_MASK) == MIDI_CONTROL_CHANGE )
                state.midi = CONTROL_CHANGE;
            else if ( (data & MIDI_COMMAND_MASK) == MIDI_PROGRAM_CHANGE )
                state.midi = PROGRAM_CHANGE;
            break;


        ////
        // MIDI data byte 0
        ////
        case NOTE_ON:
            switch(data) {
                case CMD_PEDAL_MODE:
                    state.receive = true;
                    state.waveform = WAVE_OFF;
                    break;

                case CMD_AUTO_MODE_SAW_UP:
                    state.receive = false;
                    state.waveform = WAVE_SAW_UP;
                    break;

                case CMD_AUTO_MODE_SAW_DOWN:
                    state.receive = false;
                    state.waveform = WAVE_SAW_DOWN;
                    break;

                case CMD_AUTO_MODE_SQUARE:
                    state.receive = false;
                    state.waveform = WAVE_SQUARE;
                    break;

                case CMD_AUTO_MODE_STAIRS:
                    state.receive = false;
                    state.waveform = WAVE_STAIRS;
                    break;

                case CMD_AUTO_MODE_TRIANGLE:
                    state.receive = false;
                    state.waveform = WAVE_TRIANGLE;
                    break;
            }
            state.midi = IDLE;
            break;


        case PROGRAM_CHANGE:
            state.midi = IDLE;
            break;


        case CONTROL_CHANGE:
            switch(data) {
                case CTRL_WAH:
                    if (state.receive)
                        state.midi = SET_WAH;
                    else
                        state.midi = IDLE;
                    break;

                case CTRL_SPEED:
                    state.midi = SET_SPEED;
                    break;

                default:
                    state.midi = IDLE;
            }
            break;


        ////
        // MIDI data byte 1
        ////
        case SET_WAH:
            applyWah(data);
            state.midi = IDLE;
            break;

        case SET_SPEED:
            // scale and set speed value
            state.speed = (MIDI_MAX_VALUE - data) / 4;
            state.midi = IDLE;
            break;


        ////
        // unimplemented
        ////
        default:
            state.midi = IDLE;
            break;
    }
}
