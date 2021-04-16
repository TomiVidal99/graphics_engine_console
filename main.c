// MADE BY TOMAS VIDAL
// SIMPLE GRAPHIC ENGINE
// THE PURPOSE IT IS TO PROVIDE THE USER WITH BASIC 
// GRAPHICS UTILITY, SO THE USER CAN DESIGN SOFITICATED ANIMATIONS
// AN EXAMPLE: A SIMPLE PENDULUM

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>

// define constants
#define VERSION 1
#define PI 3.14

#define MIN_WIDTH 5 
#define MAX_WIDTH 300
#define MIN_HEIGHT 5
#define MAX_HEIGHT 300
#define WIDTH_DIFFERENCE 295 // MAX_WIDTH-MIN_WIDTH
#define HEIGTH_DIFFERENCE 295 // MAX_HEIGHT-MIN_HEIGHT

#define DEFAULT_WIDTH 40
#define DEFAULT_HEIGHT 12

#define BACKGROUND_CARACTER ' '
#define PAINTED_CARACTER '#'

#define GRAVITY 0.1
#define PENDULUM_MASS 5000
#define STARTING_ANGLE 1

#define SECONDS_BETWEEN_FRAMES 33 // FOR 30 FPS
//#define SECONDS_BETWEEN_FRAMES 200 // FOR 5 FPS
  

void delay(int number_of_seconds) {
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

void get_canvas_size(int *width, int *height) {
    // function that asks the user for width and height input
    char selection;
    
    // repeat input until user's choice is correct
    do {
        // get width
        do {
            system("clear");
            printf("Input a width (%d - %d): ", MIN_WIDTH, MAX_WIDTH);
            scanf("%d", width);
        } while (isdigit(*width) == 1 || *width < MIN_WIDTH || *width > MAX_WIDTH);
        // get height
        do {
            system("clear");
            printf("Input a height (%d - %d): ", MIN_HEIGHT, MAX_HEIGHT);
            scanf("%d", height);
        } while (isdigit(*height) == 1 || *height < MIN_WIDTH || *height > MAX_WIDTH);

        system("clear");
        printf("Canvas size: %dx%d \n", *width, *height);
        // repeat question until answer is valid
        do {
            printf("\nWould you like to change the sizes? [Y/N] ");
            scanf(" %c", &selection);
        } while ( selection != 'N' && selection != 'n' && selection != 'y' && selection != 'Y');

    } while (selection != 'N' && selection != 'n');

}

void draw(int width, int height, int pixels[WIDTH_DIFFERENCE][HEIGTH_DIFFERENCE]) {
    // function that draws all the "pixels" given a certain x width and a y height
    int i, j;

    for (j = 0; j < height; j++) {
        // loop through all the columns
        for (i = 0; i < width; i++) {
            // loop through all the rows
            // check if the current pixels is inside the parameters
            printf("%c", pixels[i][j]);
        }
        printf("\n");
    }
}

void rect(int x, int y, int a, int b, char paint, int width, int height, int pixels[WIDTH_DIFFERENCE][HEIGTH_DIFFERENCE]) {
    // (x,y) is the left top point and (x+a, y+b) is the bottom right point
    int i, j;
    
    for (j = 0; j < height; j++) {
        // loop through all the columns
        for (i = 0; i < width; i++) {
            // loop through all the rows
            // check if the current pixels is inside the parameters
            if (j >= y && j <= (y+b) && i == x) {
                // left line
                pixels[i][j] = paint;
            } else if (j >= y && j <= (y+b) && i == (x+a)) {
                // right line
                pixels[i][j] = paint;
            } else if (i > x && i < (x+a) && j == (y)) {
                // top line
                pixels[i][j] = paint;
            } else if (i > x && i < (x+a) && j == (y+b)) {
                // bottom line
                pixels[i][j] = paint;
            }
        }
    }
}

void circle(int x, int y, int r, int thickness, char paint, int width, int height, int pixels[WIDTH_DIFFERENCE][HEIGTH_DIFFERENCE]) {
    // (x,y) is the center point and r is the radius
    int i, j;
    int Rin = r - thickness;
    int Rout = r + thickness;
    int Rin2 = pow(Rin, 2);
    int Rout2 = pow(Rout, 2);
    
    for (j = 0; j < height; j++) {
        // loop through all the columns
        for (i = 0; i < width; i++) {
            // loop through all the rows
            // check if the current pixels is inside the parameters
            int val = pow(i-x, 2) + pow(j-y, 2);
            if ( i >= (x-r) && i <= (x+r) && val >= Rin2 && val <= Rout2) {
                pixels[i][j] = paint;
            }
        }
    }
}

void create_canvas(int width, int height, char paint, int pixels[WIDTH_DIFFERENCE][HEIGTH_DIFFERENCE]) {
    // initialize the pixels arrays with the BACKGROUND_CARACTER
    int i, j;
    for (j = 0; j < height; j++) {
        // loop through all the columns
        for (i = 0; i < width; i++) {
            // loop through all the rows
            pixels[i][j] = paint;
        }
    }
}

void point(int x, int y, char paint, int width, int height, int pixels[WIDTH_DIFFERENCE][HEIGTH_DIFFERENCE]) {
    // create a point in (x,y)
    int i, j;
    for (j = 0; j < height; j++) {
        // loop through all the columns
        for (i = 0; i < width; i++) {
            // loop through all the rows
            if (i == x && j == y) {
                pixels[i][j] = paint;
            }
        }
    }
}


void line(int a_, int b_, int c_, int d_, int thickness, char paint, int width, int height, int pixels[WIDTH_DIFFERENCE][HEIGTH_DIFFERENCE]) {
    // creates a line from point (x,y) to (a,b) with a thickness of thickness
    int x, y, a, b, c, d;
    float m, gamma;

    if ( 0 <= a_ && a_ <= width && 0 <= c_ && c_ <= width && 0 <= b_ && b_ <= height && 0 <= d_ && d_ <= height ) {
       
        // i need to reflect the Y axis
        b *= -1;
        d *= -1;

        // i reverse the points to set first the closest one
        if (a_ < c_) {
            a = a_;
            b = b_;
            c = c_;
            d = d_;
        } else {
            a = c_;
            b = d_;
            c = a_;
            d = b_;
        }

        if (a != c && b != d) {
            m = (float) (d-b)/ (float) (c-a);
            gamma = (float) b - (float) m*a;
            /*system("clear");*/
            /*printf("\"IN LINE:\" %d-%d / %d-%d = %lf, gamma=%lf\n", d,b,c,a,m, gamma);*/
            if (m > 0) { // diagonal '\\'
                for (y = 0; y < height; y++) {
                    for (x = 0; x < width; x++) {
                        int rect_y = abs( (float) m*x + gamma); // actual value of the rect
                        if (x >= a && x <= c && y == rect_y) { // the x is between a and b
                            /*pixels[x][y] = paint;*/
                            pixels[x][y] = '\\';
                        }
                    }
                }
            } else { // diagonal '/'
                for (y = 0; y < height; y++) {
                    for (x = 0; x < width; x++) {
                        int rect_y = abs( (float) m*x + gamma); // actual value of the rect
                        if (x >= a && x <= c && y == rect_y) { // the x is between a and b
                            /*pixels[x][y] = paint;*/
                            pixels[x][y] = '/';
                        }
                    }
                }
            }
        } else if (a == c && b != d) {
            if (d > b) {
                for (y = 0; y < height; y++) {
                    for (x = 0; x < width; x++) {
                            if ( y >= b && y <= d && x == a) {
                                /*pixels[x][y] = paint;*/
                                pixels[x][y] = '|';
                            }
                    }
                }
            } else if (b > d) {
                for (y = 0; y < height; y++) {
                    for (x = 0; x < width; x++) {
                            if ( y <= b && y >= d && x == a) {
                                /*pixels[x][y] = paint;*/
                                pixels[x][y] = '|';
                            }
                    }
                }
            }
        } else if ( a != c && b == d) {
            for (y = 0; y < height; y++) {
                for (x = 0; x < width; x++) {
                    if ( x >= a && x <= c && y == b ) {
                        /*pixels[x][y] = paint;*/
                        pixels[x][y] = '-';
                    }
                }
            }
        } else {
            printf("ERROR: in line function");
            /*exit(1);*/
        }

    }

}

void pendulum(int x, int y, int L, int ball_radius, int t, float starting_angle, char paint, float gravity, float mass, int width, int height, int pixels[WIDTH_DIFFERENCE][HEIGTH_DIFFERENCE]) {
    // creates a pendulum given a certain starting point (x,y) and a length L
    float deg_to_radiants = PI/180;
    float angular_frequency = sqrt((gravity/mass));
    /*float theta = starting_angle*sin(angular_frequency*t);*/

    int dx = x + sin(starting_angle - angular_frequency*deg_to_radiants*t)*L;
    int dy = y + cos(starting_angle - angular_frequency*deg_to_radiants*t)*L;

    line(x, y, dx, dy-ball_radius, 0, paint, width, height, pixels);
    point(x, y, 'o', width, height, pixels);
    circle(dx, dy, ball_radius, 0, '+', width, height, pixels);

}

void read_keyboard(int output) {
    // reads 5 characters of stdin and saves it in a buffer to return output depending
    // on user input
    int i;
    /*initscr();*/
    /*cbreak();        */
    /*delay(SECONDS_BETWEEN_FRAMES);*/
    sleep(1000);
    int c = 0;        
    while (c != 'q') {
        int c = getc(stdin);
        switch (c) {
            case 'q':
                exit(0);
            case 'a':
                output = -1;
                break;
            case 'd':
                output = 1;
                break;
            default:
                break;
        }
    }
}

void display_canvas_border(char corners_paint, char horizontal_paint, char vertical_paint, int width, int height, int pixels[WIDTH_DIFFERENCE][HEIGTH_DIFFERENCE]) {
    // shows the border of the canvas with custom characters
    line(0, 0, width-1, 0, 0, horizontal_paint, width, height, pixels);
    line(0, height-1, width-1, height-1, 0, horizontal_paint, width, height, pixels);
    line(0, 1, 0, height-1, 0, vertical_paint, width, height, pixels);
    line(width-1, 1, width-1, height-1, 0, vertical_paint, width, height, pixels);
    point(0, 0, corners_paint, width, height, pixels);
    point(width-1, 0, corners_paint, width, height, pixels);
    point(0, height-1, corners_paint, width, height, pixels);
    point(width-1, height-1, corners_paint, width, height, pixels);
}

void display_clock(int x, int y, int max_radius, int width, int height, int pixels[WIDTH_DIFFERENCE][HEIGTH_DIFFERENCE]) {
    // creates a clock with center point in (x,y) and maximum radius of max_radius
    int r = max_radius - 1;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    float PI4 = PI/4;
    float PI12 = PI/6;
    float PI60 = PI/30;
    int hours = tm.tm_hour;
    int minutes = tm.tm_min;
    int seconds = tm.tm_sec;

    // get the end point of the date arrows
    int Hx = r*cos( (float) PI12*hours - PI4);
    int Hy = r*sin( (float) PI12*hours - PI4);
    int Mx = r*cos( (float) PI60*minutes - PI4);
    int My = r*sin( (float) PI60*minutes - PI4);
    int Sx = r*cos( (float) PI60*seconds - PI4);
    int Sy = r*sin( (float) PI60*seconds - PI4);

    circle(x, y, max_radius, 1, '.', width, height, pixels);

    line(x, y, x+Hx, y+Hy, 0, '+', width, height, pixels);
    line(x, y, x+Mx, y+My, 0, '+', width, height, pixels);
    line(x, y, x+Sx, y+Sy, 0, '+', width, height, pixels);

    point(x+Hx, y+Hy, 'H', width, height, pixels);
    point(x+Mx, y+My, 'M', width, height, pixels);
    point(x+Sx, y+Sy, 'S', width, height, pixels);
    point(x, y, 'O', width, height, pixels);

    point(x, y-max_radius, '1', width, height, pixels);
    point(x+1, y-max_radius, '2', width, height, pixels);
    point(x-max_radius, y, '9', width, height, pixels);
    point(x, y+max_radius, '6', width, height, pixels);
    point(x+max_radius, y, '3', width, height, pixels);

    printf("Current time: %d:%d:%d \n\n", tm.tm_hour, tm.tm_min, tm.tm_sec);

}

int main(void) {

    // define variables
    int width = DEFAULT_WIDTH, height = DEFAULT_HEIGHT;
    int pixels[WIDTH_DIFFERENCE][HEIGTH_DIFFERENCE];
    char selection;

    // change default canvas size if the user wants it
    do {
        /*system("clear");*/
        printf("Default canvas size is %dx%d\n", width, height);
        printf("Would you like to change it? [Y/N] ");
        scanf(" %c", &selection);
    } while (isdigit(selection) == 1 && selection != 'Y' && selection != 'y' && selection != 'N' && selection != 'n');
    if (selection == 'Y' || selection == 'y') {
        get_canvas_size(&width, &height);
    }

    // creates the pixels array
    create_canvas(WIDTH_DIFFERENCE, HEIGTH_DIFFERENCE, BACKGROUND_CARACTER, pixels);

    // fill the pixels with a centered square that covers the borders
    /*rect(0, 0, width-1, height-1, PAINTED_CARACTER, pixels);*/
    /*rect(width/2, height/2, width/2+4, height/2+4, PAINTED_CARACTER, pixels);*/

    // draw 
    int current_frame = 0, t;
    while (current_frame < 10000) {

        // screen with system data
        printf("\nFRAME COUNT: %d\n", current_frame++);
        printf("FPS: %d\n", 1000/SECONDS_BETWEEN_FRAMES);
        printf("RESOLUTION: %dx%d\n", width, height);
        printf("VERSION: %d\n", VERSION);
        /*printf("dx: %d, dy: %d, theta: %lf, angular_frequency: %lf \n", dx, dy, theta, angular_frequency);*/

        delay(SECONDS_BETWEEN_FRAMES);
        system("clear");

        create_canvas(width, height, BACKGROUND_CARACTER, pixels);
        display_canvas_border('O', '-', '|', width, height, pixels);

        /*rect(width/2, 2, width-2, height-2, PAINTED_CARACTER, width, height, pixels);*/

        /*point(0, 0, 'X', width, height, pixels);*/
        /*point(width-1, 0, 'X', width, height, pixels);*/
        /*point(width-1, height-1, 'X', width, height, pixels);*/
        /*point(0, height-1, 'X', width, height, pixels);*/

        /*point(rect_off, height/2, 'o', width, height, pixels);*/
        /*circle(width/2, height/2, 5, 1, '+', width, height, pixels);*/
        /*line(15, 10, 0, 0, 0, '+', width, height, pixels);*/
        /*point(10, 2, 'A', width, height, pixels);*/
        /*point(10, 5, 'A', width, height, pixels);*/

        pendulum(width/3-3, 1, height/2+3, 3, t, STARTING_ANGLE, PAINTED_CARACTER, GRAVITY, PENDULUM_MASS, width, height, pixels);

        /*pendulum(width/3, 1, height/2, 1, t+125, STARTING_ANGLE, PAINTED_CARACTER, GRAVITY, PENDULUM_MASS, width, height, pixels);*/

        display_clock(2*width/3, height/2, height/3, width, height, pixels);

        draw(width, height, pixels);
    
        t++;
    }

    return 0;
}
