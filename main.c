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

// define constants
#define VERSION 1

#define MIN_WIDTH 5 
#define MAX_WIDTH 300
#define MIN_HEIGHT 5
#define MAX_HEIGHT 300
#define WIDTH_DIFFERENCE 295 // MAX_WIDTH-MIN_WIDTH
#define HEIGTH_DIFFERENCE 295 // MAX_HEIGHT-MIN_HEIGHT

#define DEFAULT_WIDTH 50
#define DEFAULT_HEIGHT 16

#define BACKGROUND_CARACTER ' '
#define PAINTED_CARACTER '#'

#define SECONDS_BETWEEN_FRAMES 33 // FOR 30 FPS
// #define SECONDS_BETWEEN_FRAMES 200 // FOR 5 FPS
  

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

void rect(int x, int y, int a, int b, char paint, int pixels[WIDTH_DIFFERENCE][HEIGTH_DIFFERENCE]) {
    // (x,y) is the left top point and (x+a, y+b) is the bottom right point
    int i, j;
    
    for (j = 0; j < HEIGTH_DIFFERENCE; j++) {
        // loop through all the columns
        for (i = 0; i < WIDTH_DIFFERENCE; i++) {
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

void circle(int x, int y, int r, int thickness, char paint, int pixels[WIDTH_DIFFERENCE][HEIGTH_DIFFERENCE]) {
    // (x,y) is the center point and r is the radius
    int i, j;
    int Rin = r - thickness;
    int Rout = r + thickness;
    int Rin2 = pow(Rin, 2);
    int Rout2 = pow(Rout, 2);
    
    for (j = 0; j < HEIGTH_DIFFERENCE; j++) {
        // loop through all the columns
        for (i = 0; i < WIDTH_DIFFERENCE; i++) {
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

void point(int x, int y, char paint, int pixels[WIDTH_DIFFERENCE][HEIGTH_DIFFERENCE]) {
    // create a point in (x,y)
    int i, j;
    for (j = 0; j < HEIGTH_DIFFERENCE; j++) {
        // loop through all the columns
        for (i = 0; i < WIDTH_DIFFERENCE; i++) {
            // loop through all the rows
            if (i == x && j == y) {
                pixels[i][j] = paint;
            }
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
        system("clear");
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
    int off_x = 2, off_y = 2, current_frame = 0, direction = -1, rect_off = 0;
    while (current_frame < 400) {

        // screen with system data
        printf("\nFRAME COUNT: %d\n", current_frame++);
        printf("FPS: %d\n", 1000/SECONDS_BETWEEN_FRAMES);
        printf("RESOLUTION: %dx%d\n", width, height);
        printf("VERSION: %d\n", VERSION);

        delay(SECONDS_BETWEEN_FRAMES);
        system("clear");

        create_canvas(width, height, '-', pixels);
        rect(0, 0, width-1, height-1, PAINTED_CARACTER, pixels);
        point(0, 0, 'X', pixels);
        point(width-1, 0, 'X', pixels);
        point(width-1, height-1, 'X', pixels);
        point(0, height-1, 'X', pixels);

        point(width/2, height/2, 'o', pixels);
        circle(width/2, height/2, 5, 1, '+', pixels);
        draw(width, height, pixels);
    }

    return 0;
}
