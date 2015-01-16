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

/*
 * Program entry point and main loop of the uMIDI firmware.
 */

#include "main.h"
#include "adc.h"
#include "gpio.h"
#include "leds.h"
#include "midi.h"
#include "pwm.h"
#include "tests.h"
#include "timer.h"

#include <avr/interrupt.h>
#include <avr/wdt.h>


////////////////////////////////////////////////////////////////
//                     V A R I A B L E S                      //
////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////
//      F U N C T I O N S   A N D   P R O C E D U R E S       //
////////////////////////////////////////////////////////////////

static void configure_system_clock(void)
{
    // Enable internal 32 MHz oscillator
    OSC.CTRL |= OSC_RC32MEN_bm;
    while(!(OSC.STATUS & OSC_RC32MRDY_bm));

    // Select internal 32 MHz oscillator
    CCP = CCP_IOREG_gc;
    CLK.CTRL = CLK_SCLKSEL_RC32M_gc;
}

// initialization and endless loop
int main( void )
{
    configure_system_clock();
    configureTaskTimer();
    initializeLedsModule();

    // configure GPIO ports
    configureGPIO();

    initialize_midi_module();

    // configure the ADC
    configureADC();

    // configure the PWM
    configurePWM();

    // set watchdog for 128ms
    wdt_enable(WDT_PER_128CLK_gc);

    // enable interrupts
    PMIC.CTRL = PMIC_LOLVLEN_bm;
    sei();

    // run the test suite
    runTestSuite();

    // send initial program change
    sendProgramChange(INITIAL_PROGRAM);

    // Main loop
    while (true) {
        wdt_reset();
    }

    return 0;
}
