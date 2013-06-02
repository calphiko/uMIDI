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

#include <util/atomic.h>


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

void modulateSaw() {
    int value = 0;
    value++;
    value %= 128;
    applyWah(value);
}



////////////////////////////////////////////////////////////////
//                    I N T E R R U P T S                     //
////////////////////////////////////////////////////////////////

ISR(TIMER0_OVF_vect) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        static uint8_t prescaler = 0;
        if (++prescaler > 8) {
            switch (state.waveform) {
                case WAVE_SAW_UP:
                    modulateSaw();
                    break;

                default:
                    break;
            }
            prescaler = 0;
        }
    }
}
