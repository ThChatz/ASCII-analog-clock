#include <stdlib.h>
#include <stdio.h>

#include "canvas.h"

canvas *init_canvas(int width, int height){
    /* initializes an empty canvas */
    canvas *c = malloc(sizeof(canvas));
    c->data = malloc(height * sizeof(char *));
    int i, j;
    for(i = 0;i < height;i++ ){
	c->data[i] = malloc(width * sizeof(char));
	for(j = 0;j < width;j++ )
	    c->data[i][j] = ' ';
    }

    c->dimensions.x = width;
    c->dimensions.y = height;

    return c;
}

void draw_function(int ( *f) (vector2d p), canvas *c, char fill){
    vector2d point;
    for(point.y = 0;point.y < c->dimensions.y;point.y++ ){
	for(point.x = 0;point.x < c->dimensions.x;point.x++ ){
	    if(f(point))
		c->data[point.y][point.x] = fill;
	}
    }
}

void print_canvas(canvas *c){
    int i, j;
    for(i = 0;i < c->dimensions.y;i++ ){
	for(j = 0;j < c->dimensions.x;j++ ){
	    putchar(c->data[i][j]);
	    putchar(' ');
	}
	putchar('\n');
    }

}
