/* Configure I/O Ports */

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "unifiedColor.h"
#include "bezier.h"

 /*{Small Graphics library for the LaFortuna}
    Copyright (C) {2016}  {Nicholas Bishop}

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. */

void init(void) {

    /* 8MHz clock, no prescaling (DS, p. 48) */
    CLKPR = (1 << CLKPCE);
    CLKPR = 0;

	init_lcd();
	
	
	display_string("hello world");
	
	drawCircle(160,120,100,YELLOW);
	drawCircle(115, 75, 15,YELLOW);
	drawCircle(205, 75, 15,YELLOW);
	
	uint16_t x[4] = {115, 135, 185, 205};
	uint16_t y[4] = {165, 195, 195,165};
	plotBezierBuffer(x,y, YELLOW, 0.1);
	
	
	
}

int main() {
	init();
	return 0;
}


