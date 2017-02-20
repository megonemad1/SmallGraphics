/* Configure I/O Ports */

#include "unifiedLcd.h"

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



	init_lcd(0);


	drawCircle(160,120,100,YELLOW);
	drawCircle(115, 75, 15,YELLOW);
	drawCircle(205, 75, 15,YELLOW);

	uint16_t x[4] = {115, 135, 185, 205};
	uint16_t y[4] = {165, 195, 195,165};
	plotBezierBuffer(x,y, YELLOW, 0.1);

/*
        rectangle r = {50,188,150,300};
        fill_rectangle(r,BLACK);
        rectangle r2 = {90,110,72,100};
        fill_rectangle(r2,BLACK);
	uint16_t l1x[4] = {50, 25, 25, 50};
	uint16_t l1y[4] = {150, 175, 200, 225};
	plotBezierBuffer(l1x,l1y, YELLOW, 0.1);

	uint16_t l2x[4]  = {50, 75, 75, 80};
	uint16_t l2y[4]  = {150, 150, 150, 155};
	plotBezierBuffer(l2x,l2y, YELLOW, 0.1);

    drawLine(80,155,80,90,YELLOW);
    drawLine(110,155,110,90,YELLOW);
    drawLine(106,100,84,100,YELLOW);

    drawLine(84,90,84,100,YELLOW);
    drawLine(106,90,106,100,YELLOW);

	uint16_t l3x[4]  = {110, 120, 130, 140};
	uint16_t l3y[4]  = {155, 145, 145, 155};
	plotBezierBuffer(l3x,l3y,YELLOW, 0.1);

	uint16_t l4x[4]  = {140, 150, 160, 170};
	uint16_t l4y[4]  = {155, 145, 145, 155};
	plotBezierBuffer(l4x,l4y,YELLOW, 0.1);

	uint16_t l5x[4] = {170, 25+170, 25+170, 170};
	uint16_t l5y[4] = {155, 175, 200, 225};
	plotBezierBuffer(l5x,l5y, YELLOW, 0.1);

	uint16_t l6x[4] = {80, 90, 100, 110};
	uint16_t l6y[4] = {90, 60, 60, 90};
	plotBezierBuffer(l6x,l6y, YELLOW, 0.1);

	uint16_t l7x[4] = {84, 90, 100, 106};
	uint16_t l7y[4] = {90, 64, 64, 90};
	plotBezierBuffer(l7x,l7y, YELLOW, 0.1);

	uint16_t l8x[4] = {50, 10, 15, 20};
	uint16_t l8y[4] = {225, 200, 190, 175};
	plotBezierBuffer(l8x,l8y, YELLOW, 0.1);
    drawLine(20,175,34,171,YELLOW);
*/
display_curser_move(100,100);
drawLine(80,155,80,90,YELLOW);
drawAALine(100,80,90,155,YELLOW);

drawLine(80,155,80,90,RED);
drawLine(80,155,100,90,RED);
drawLine(100,155,100,90,RED);

display_string(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRS\nTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
}

int main() {
	init();
	return 0;
}
