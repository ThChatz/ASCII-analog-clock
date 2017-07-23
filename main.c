#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "canvas.h"

#define CENTER (vector2d){15, 15}
#define RADIUS 15

#define HOUR_HAND_LENGTH 5
#define MIN_HAND_LENGTH 10

#define INF 1.0 / 0.0

#define SQUARE(x) (x)*(x)


float M;
int len, quadr, h, m;


int f_circle(vector2d p){
    return (SQUARE(RADIUS) == SQUARE(p.x - CENTER.x) + SQUARE(p.y - CENTER.y));
}

int f_line(vector2d p){

    if(M == INF)
	return p.x == CENTER.x;

    return (p.y == M * p.x - M * CENTER.x + CENTER.y);
}

int f_hour_hand(vector2d p){
    int quadrant = h / 3, q;

    switch(quadrant){
    case 0:
	q = p.x - CENTER.x >= 0 && p.y - CENTER.y <= 0;
	break;
    case 1:
	q = p.x - CENTER.x >= 0 && p.y - CENTER.y >= 0;
	break;
    case 2:
	q = p.x - CENTER.x <= 0 && p.y - CENTER.y >= 0;
	break;
    case 3:
	q = p.x - CENTER.x <= 0 && p.y - CENTER.y <= 0;
	break;
    }

    int in_range = (SQUARE(p.x - CENTER.x) + SQUARE(p.y - CENTER.y)) <= SQUARE(HOUR_HAND_LENGTH);
    int on_line = (p.y == M * (p.x - CENTER.x) + CENTER.y) || (M == INF && p.x == CENTER.x);
    return q && in_range && on_line;
}

int f_min_hand(vector2d p){
    printf("%d\n", m);
    int quadrant = m / 15, q;
    switch(quadrant){
    case 0:
	q = p.x - CENTER.x >= 0 && p.y - CENTER.y <= 0;
	break;
    case 1:
	q = p.x - CENTER.x >= 0 && p.y - CENTER.y >= 0;
	break;
    case 2:
	q = p.x - CENTER.x <= 0 && p.y - CENTER.y >= 0;
	break;
    case 3:
	q = p.x - CENTER.x <= 0 && p.y - CENTER.y <= 0;
	break;
    }

     int in_range = (SQUARE(p.x - CENTER.x) + SQUARE(p.y - CENTER.y)) <= SQUARE(MIN_HAND_LENGTH);
     int on_line = (p.y == M * (p.x - CENTER.x) + CENTER.y) || (M == INF && p.x == CENTER.x);
     return q && in_range && on_line;
}


float M_hours(int hour){
    int quadrant = hour / 3;

    if(hour % 6 == 3)
	return 0;
    else if(hour % 6 == 0)
	return INF;


    if(quadrant == 1 || quadrant == 3)
	return -M_hours(12 - hour);

    int x, y;
    float M;

    x = (hour % 3) * RADIUS / 3;
    y = RADIUS - (hour % 3) * RADIUS/ 3;

    M = (float)y / x;

    return -M;
}


float M_minutes(int minutes){
    minutes -= minutes % 5;

    int quadrant = minutes / 15;

    if(minutes % 30 == 15)
	return 0;
    else if(minutes % 30 == 0)
	return INF;


    if(quadrant == 1 || quadrant == 3)
	return -M_minutes(60 - minutes);

    int x, y;
    float M;

    x = (minutes % 15) * RADIUS / 15;
    y = RADIUS - (minutes % 15) * RADIUS/ 15;

    M = (float)y / x;

    return -M;
}

void draw_clock(canvas *c){
    draw_function(&f_circle, c, '*');
    int t;

    t = time(NULL);
    h = ((t / 3600) + 3) % 12;	/* +3 for timezone lmoa */
    m = (t / 60) % 60;

    M = M_hours(h);
    draw_function(&f_hour_hand, c, 'H');
    M = M_minutes(m);
    draw_function( &f_min_hand, c, 'M');


}


int main (int argc, char **argv){
    canvas *c = init_canvas(32, 32);
    draw_clock(c);
    print_canvas(c);
    return 0;
}
