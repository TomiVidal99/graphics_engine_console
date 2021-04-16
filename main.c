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

// define constants
#define VERSION 1

#define MIN_WIDTH 5 
#define MAX_WIDTH 300
#define MIN_HEIGHT 5
#define MAX_HEIGHT 300
#define WIDTH_DIFFERENCE 295 // MAX_WIDTH-MIN_WIDTH
#define HEIGTH_DIFFERENCE 295 // MAX_HEIGHT-MIN_HEIGHT

#define DEFAULT_WIDTH 80
#define DEFAULT_HEIGHT 16

#define BACKGROUND_CARACTER ' '
#define PAINTED_CARACTER '#'

#define GRAVITY 0.1
#define PENDULUM_MASS 5000
#define STARTING_ANGLE 15

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


void line(int a, int b, int c, int d, int thickness, char paint, int width, int height, int pixels[WIDTH_DIFFERENCE][HEIGTH_DIFFERENCE]) {
    // creates a line from point (x,y) to (a,b) with a thickness of thickness
    int x, y;
    float m, gamma;

    /*system("clear");*/
    /*printf("(%d, %d) y (%d, %d) \t pendiente: %d y gamma: %.3lf \n", a,b,c,d,m, gamma);*/

    if (a != c && b != d) {
        m = (d-b)/(c-a);
        gamma = b - m*a;
        /*printf("%d-%d / %d-%d = %.2lf, gamma=%.2lf\n", d,b,c,a,m, gamma);*/
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                int rect_y = m*x + gamma; // actual value of the rect
                /*printf("rect_y: %d\n", rect_y);*/
                if (x >= a && x <= c && y == rect_y) { // the x is between a and b
                    pixels[x][y] = paint;
                }
            }
        }
    } else if (a == c && b != d) {
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                if ( y >= b && y <= d && x == a) {
                    pixels[x][y] = paint;
                }
            }
        }
    } else if ( a != c && b == d) {
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                if ( x >= a && x <= c && y == b ) {
                    pixels[x][y] = paint;
                }
            }
        }
    } else {
        printf("ERROR");
        exit(1);
    }

}

void pendulum(int x, int y, int L, int t, float starting_angle, char paint, float gravity, float mass, int width, int height, int pixels[WIDTH_DIFFERENCE][HEIGTH_DIFFERENCE], int *dx, int *dy, float *theta, float *angular_frequency) {
    // creates a pendulum given a certain starting point (x,y) and a length L
    int ball_radius = 3;
    *angular_frequency = sqrt((gravity/mass));
    *theta = starting_angle*sin(*angular_frequency*t);

    *dx = x + cos(*theta)*L;
    *dy = y + sin(*theta)*L;

    line(x, y, *dx, *dy-ball_radius, 0, paint, width, height, pixels);
    point(x, y, 'o', width, height, pixels);
    circle(*dx, *dy, ball_radius, 0, '+', width, height, pixels);

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
    int off_x = 2, off_y = 2, current_frame = 0, direction = -1, rect_off = 2, t, dx, dy;
    float theta, angular_frequency;
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
        rect(0, 0, width-1, height-1, PAINTED_CARACTER, width, height, pixels);
        point(0, 0, 'X', width, height, pixels);
        point(width-1, 0, 'X', width, height, pixels);
        point(width-1, height-1, 'X', width, height, pixels);
        point(0, height-1, 'X', width, height, pixels);

        /*point(rect_off, height/2, 'o', width, height, pixels);*/
        /*circle(width/2, height/2, 5, 1, '+', width, height, pixels);*/
        /*line(5, 5, 7, 10, 0, '+', width, height, pixels);*/
        /*point(5, 5, 'o', width, height, pixels);*/
        /*point(7, 10, 'o', width, height, pixels);*/

        pendulum(width/2, 1, 40, t, STARTING_ANGLE, PAINTED_CARACTER, GRAVITY, PENDULUM_MASS, width, height, pixels, &dx, &dy, &theta, &angular_frequency);

        draw(width, height, pixels);
    
        t++;
    }

    return 0;
}
