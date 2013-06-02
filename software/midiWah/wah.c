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
 * wah computations and output
 * @author Sebastian Neuser
*/

#include "midiWah.h"


////////////////////////////////////////////////////////////////
//                     V A R I A B L E S                      //
////////////////////////////////////////////////////////////////

extern exec_state_t state;



////////////////////////////////////////////////////////////////
//      F U N C T I O N S   A N D   P R O C E D U R E S       //
////////////////////////////////////////////////////////////////

void applyWah( uint8_t wah )
{
    // apply value
    OCR1A = WAH_LED_SCALER * MIDI_MAX_VALUE - wah;
}


void configureWahLedTimer( void ) {
    // configure AVR ports
    WAH_LED_DDR = _BV(WAH_LED_BIT);

    // 8 bit / 125 kHz / clear on compare match
    TCCR1A = _BV(WGM11) | _BV(COM1A1) | _BV(COM1A0);
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);

    // set TOP
    ICR1 = WAH_LED_SCALER * MIDI_MAX_VALUE;
    OCR1A = WAH_LED_SCALER * MIDI_MAX_VALUE;
}

void configureWahModulationTimer( void ) {
    // 8bit / 4 kHz
    TCCR0A = _BV(CS00);
    TIMSK0 |= _BV(TOIE0);
}



////////////////////////////////////////////////////////////////
//                    I N T E R R U P T S                     //
////////////////////////////////////////////////////////////////

ISR(TIMER0_OVF_vect) {
    static uint8_t prescaler = 0;
    static uint8_t wah = 0;
    static direction_t direction = DIRECTION_UP;
    if (++prescaler > state.speed) {
        switch (state.waveform) {
            case WAVE_SAW_DOWN:
                // increment, rotate and apply wah value
                wah++;
                wah %= MIDI_MAX_VALUE + 1;
                applyWah(MIDI_MAX_VALUE - wah);
                break;

            case WAVE_SAW_UP:
                // increment, rotate and apply wah value
                wah++;
                wah %= MIDI_MAX_VALUE + 1;
                applyWah(wah);
                break;

            case WAVE_TRIANGLE:
                switch (direction) {
                    case DIRECTION_DOWN:
                        if (--wah <= 0)
                            direction = DIRECTION_UP;
                        break;

                    case DIRECTION_UP:
                        if (++wah >= MIDI_MAX_VALUE)
                            direction = DIRECTION_DOWN;
                        break;

                    default:
                        break;
                }
                applyWah(wah);
                break;

            default:
                break;
        }
    }
}
