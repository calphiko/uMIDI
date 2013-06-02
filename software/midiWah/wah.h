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
 * header for volume computations and output
 * @author Sebastian Neuser
*/

#ifndef _WAH_H
#define _WAH_H


//---------------- includes ----------------//
#include <avr/io.h>
#include <avr/interrupt.h>


//---------------- AVR PORT mapping ----------------//
#define     WAH_LED_PORT    PORTB
#define     WAH_LED_DDR     DDRB
#define     WAH_LED_BIT     PB1


//---------------- code macros ----------------//
// the higher this value, the softer the wah effect
#define     WAH_LED_SCALER  16


//---------------- data types ----------------//
// wah modulation waveforms
typedef enum {
	WAVE_OFF,
	WAVE_SINE,
	WAVE_TRIANGLE,
	WAVE_SAW_UP,
	WAVE_SAW_DOWN,
	WAVE_SQUARE
} wave_t;


//---------------- functions and procedures ----------------//
void applyWah( uint8_t );
void configureWahLedTimer( void );
void configureWahModulationTimer( void );
void modulateSaw( void );


//---------------- EOF ----------------//
#endif // _WAH_H
