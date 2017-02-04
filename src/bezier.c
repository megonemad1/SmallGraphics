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

int16_t findBezier(double t, uint16_t x[4]) {
	double omt = 1-t;
	
	double xt = omt*omt*omt*x[0] + 3*omt*omt*t*x[1] +
				3*omt*t*t*x[2] +  t*t*t*x[3];
				
	return (int16_t) xt+0.5;
}

void plotBezier(uint16_t x[4], uint16_t y[4], uint16_t col, double segSize) {
	int16_t px0 = findBezier(0.0, x);
	int16_t py0 = findBezier(0.0, y);
	double t;
	for (t = segSize; t < 1.0+segSize; t+=segSize) {
		int16_t px1 = findBezier(t,x);
		int16_t py1 = findBezier(t,y);
		
		drawLine(px0,py0,px1, py1, col);
		px0 = px1;
		py0 = py1;
	}
	
}

void plotBezierBuffer(uint16_t x[4], uint16_t y[4], uint16_t col, double segSize) {
	int16_t px0 = findBezier(0.0, x);
	int16_t py0 = findBezier(0.0, y);
	double t = segSize;
	uint16_t pointNo = (uint16_t) ((1/segSize) + 1.5); //+1 for n+1 points for n lines  and +0.5 for round up
	int16_t* xbuff = (int16_t*) malloc(sizeof(int16_t) * pointNo); 
	int16_t* ybuff = (int16_t*) malloc(sizeof(int16_t) * pointNo); 
	ybuff[0] = py0;
	xbuff[0] = px0;
	uint16_t i;
	for (i = 1; i < pointNo; i++) {
		int16_t px1 = findBezier(t,x);
		int16_t py1 = findBezier(t,y);
		
		ybuff[i] = py1;
		xbuff[i] = px1;
		px0 = px1;
		py0 = py1;
		t+= segSize;
	}
	
	for (i = 0; i < pointNo-1; i++ ) {
		drawLine(xbuff[i],ybuff[i],xbuff[i+1], ybuff[i+1],col);
	}
	
	free(ybuff);
	free(xbuff);
}

double fraction(double val) {
	if (val<0) {
		return 1 - (val - floor(val));
	}
	
	return val - floor(val);
	
}

double remainingFraction(double val) {
	return 1 - fraction(val);
}

void drawAALine(double x0, double y0, double x1, double y1, uint16_t col) {
	double steep = fabs(y1 - y0) - fabs (x1 - x0);
	
	if (steep > 0) {
		swapDouble(&y0, &x0);
		swapDouble(&y1, &x1);
	}
	
	if (x0 > x1) {
		swapDouble(&x0, &x1);
		swapDouble(&y1, &y0);
	}
	
	double dx = x1 - x0;
	double dy = y1 - y0;
	
	double gradient = dy / dx;
	
	int16_t xend = (int16_t) (x0 +0.5);
	double yend = y0 + gradient * (xend-x0);
	double xgap = remainingFraction(x0 + 0.5);
	uint16_t xpxl1 = (uint16_t) xend;
	uint16_t ypxl1 = (uint16_t) yend;
	
	if(steep > 0) {
		plotPixel(ypxl1, xpxl1, shade(col,1+remainingFraction(yend)*xgap));
		plotPixel(ypxl1+1,xpxl1, shade(col,1+fraction(yend)*xgap));
	}
	else {
		plotPixel(xpxl1, ypxl1, shade(col,1+remainingFraction(yend)*xgap));
		plotPixel(xpxl1,ypxl1+1, shade(col,1+fraction(yend)*xgap));
	}
	
	double intery = yend + gradient;
	
	xend = (int16_t) (x1 +0.5);
    yend = y1 + gradient * (xend - x1);
    xgap = remainingFraction(x1 + 0.5);
    uint16_t xpxl2 = (uint16_t) xend; 
    uint16_t ypxl2 = (uint16_t) yend;
    if (steep > 0) {
        plotPixel(ypxl2  , xpxl2, shade(col,remainingFraction(yend) * xgap));
        plotPixel(ypxl2+1, xpxl2, shade(col,fraction(yend) * xgap));
	}
    else {
        plotPixel(xpxl2, ypxl2,  shade(col,remainingFraction(yend) * xgap));
        plotPixel(xpxl2, ypxl2+1, shade(col,fraction(yend) * xgap));
	}
	
	uint16_t i;
	
	for(i = xpxl1+1; i<xpxl2;i++) {
		if(steep >0) {
			plotPixel((uint16_t) intery  , i, shade(col,remainingFraction(intery)));
            plotPixel((uint16_t) intery+1, i, shade(col,fraction(intery)));
		}
		else {
			plotPixel(i,(uint16_t) intery  , shade(col,remainingFraction(intery)));
            plotPixel(i,(uint16_t) intery+1, shade(col,fraction(intery)));
		}
		intery = intery + gradient;
	}
	
}

void swapDouble(double *x, double *y) {
	double z;
	z = *x;
	*x = *y;
	*y  = z;
}


void drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t col) {
	
	plotPixel((uint16_t) x1, (uint16_t) y1, col);
	
	uint16_t oct = findOctant(x1,y1,x2,y2);
	
	toOctant0(&x1, &y1, oct);
	toOctant0(&x2, &y2, oct);
	
	int16_t posx;
	int16_t posy = y1;
	int16_t diffx =  x2 -  x1;
	int16_t diffy =   y2 -  y1;
	int16_t twoDiffy = 2 *diffy;
	int32_t p = (int32_t) twoDiffy -  (int32_t) diffx;
	int16_t tempx;
	int16_t tempy;
	
	
	for (posx = x1+1; posx <= x2; posx++) {
		if (p < 0) {
			p = p + twoDiffy;
		}
			
	
		
		else {
			posy++;
			p = p + twoDiffy - 2*diffx;	
		}
		
		tempx = posx;
		tempy = posy;
		
		switchFromOctant0(&tempx, &tempy, oct);
		
		plotPixel((uint16_t)tempx , (uint16_t) tempy, col);
		
	}
}

void switchFromOctant0(int16_t *x, int16_t *y, uint16_t octant) {
	switch(octant)  {
     case 0: break;
     case 1: 
		swap(x,y);
		break;
     case 2: 
		*y = -*y;
		swap(x,y);
		break;
     case 3: 
		*x = -*x;
		break;
     case 4: 
		*x = -*x;
		*y = -*y;
		break;
     case 5: 
		*x = -*x;
		*y = -*y;
		swap(x,y);
		break;
     case 6: 
		*x = -*x;
		swap(x,y);
		break;
     case 7: 
		*y = -*y;
		break;
	}
}

void toOctant0(int16_t *x, int16_t *y, uint16_t octant) {
	switch(octant)  {
     case 0: break;
     case 1: 
		swap(x,y);
		break;
     case 6: 
		*y = -*y;
		swap(x,y);
		break;
     case 3: 
		*x = -*x;
		break;
     case 4: 
		*x = -*x;
		*y = -*y;
		break;
     case 5: 
		*x = -*x;
		*y = -*y;
		swap(x,y);
		break;
     case 2: 
		*x = -*x;
		swap(x,y);
		break;
     case 7: 
		*y = -*y;
		break;
	}
}

void swap(int16_t *x, int16_t *y) {
	uint16_t z;
	z = *x;
	*x = *y;
	*y  = z;
}

uint16_t findOctant(int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
	int16_t dy = y2 - y1;
	int16_t dx = x2 - x1;
	
	if (fabs(dy) > fabs(dx)) {
		if (dy < 0) {
			
			if (dx < 0) {
				return 5;
			}
			
			else {
				return 6;
			}
		}
		
		else {
			if (dx < 0) {
				return 2;
			}
			
			else {
				return 1;
			}
		}
	}
	
	else {
		if (dy < 0) {
			
			if (dx < 0) {
				return 4;
			} 
			
			else {
				return 7;
			}
		}
		
		else {
			if (dx < 0) {
				return 3;
			}
			
			else {
				return 0;
			}
		}
	}
}



void plotPixel(uint16_t x, uint16_t y, uint16_t col) {
	
	write_cmd(COLUMN_ADDRESS_SET);
	write_data16(x);
	write_data16(x);
	write_cmd(PAGE_ADDRESS_SET);
	write_data16(y);
	write_data16(y);
	write_cmd(MEMORY_WRITE);
	write_data16(col);
	
}

void drawCircle(uint16_t xc, uint16_t yc, int32_t r, uint16_t col) {
	int32_t x = 0;
	int32_t y = r;
	int32_t diff = 3 - 2*r;
	
	while (x< y) {
		auxCircle(xc,yc, (uint16_t) x, (uint16_t) y,col);
		x++;
		
		if (diff < 0) {
			diff = diff + 4*x + 6;
		}
		
		else {
			y--;
			diff = diff + 4*(x-y) + 10; 
		}
		
		auxCircle(xc,yc, (uint16_t) x, (uint16_t) y,col);
	}
}

void auxCircle(uint16_t xc, uint16_t yc, uint16_t x, uint16_t y, uint16_t col) {
	plotPixel(xc+x, yc+y, col);
	plotPixel(xc-x, yc+y, col);
	plotPixel(xc+x, yc-y, col);
	plotPixel(xc-x, yc-y, col);
	plotPixel(xc+y, yc+x, col);
	plotPixel(xc-y, yc+x, col);
	plotPixel(xc+y, yc-x, col);
	plotPixel(xc-y, yc-x, col);
}

	
	

