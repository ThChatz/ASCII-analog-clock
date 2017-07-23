typedef struct {
    int x, y;
} vector2d;

typedef struct {
    char **data;
    vector2d dimensions;
} canvas;

/* initializes an empty canvas */
canvas *init_canvas(int width, int height);

/* accepts a function f and for every point in the canvas */
/* that f is true it puts the fill character in it */
void draw_function(int ( *f) (vector2d p), canvas *c, char fill);
/* prints the canvas to stdout */
void print_canvas(canvas *c);
