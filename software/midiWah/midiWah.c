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

/* some useful vim commands
*:let @x='0xyyu@"j'
*j7@x
*:map <F9> :wa<CR>:!make backup<CR>
*:map <F10> :wa<CR>:!make eep<CR>
*:map <F12> :wa<CR>:!make clean build<CR>
*:map <F11> :wa<CR>:!make all<CR>
*:let @c="0i//\ej"
*:let @u='02xj'
*:let @d="oDEBUG1; //TODO\e"
*/

/*
 * main program of the display controller
 * @author haggl
*/

#include "midiWah.h"
#include "wah.h"

#include <avr/wdt.h>


////////////////////////////////////////////////////////////////
//                     V A R I A B L E S                      //
////////////////////////////////////////////////////////////////

// main state variable struct
exec_state_t    state;


////////////////////////////////////////////////////////////////
//      F U N C T I O N S   A N D   P R O C E D U R E S       //
////////////////////////////////////////////////////////////////

// initialization and endless loop
int main( void )
{
    // configure ports and USART
    configureUSART();
    configureWahTimer();

    // set watchdog for 30ms
    wdt_enable(WDTO_30MS);

    // enable interrupts
    sei();

    // main program
    while (1) {

        // handle watchdog
        if (MCUSR & _BV(WDRF)) {
        }
        wdt_reset();
    }

    return 0;
}
