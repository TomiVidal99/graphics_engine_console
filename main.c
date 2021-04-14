#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// define constants
#define MIN_WIDTH 20
#define MAX_WIDTH 100
#define MIN_HEIGHT 20
#define MAX_HEIGHT 100

#define DEFAULT_WIDTH 50
#define DEFAULT_HEIGHT 20

#define BACKGROUND_CARACTER '#'
#define PAINTED_CARACTER '+'

#define SECONDS_BETWEEN_FRAMES 5


// C function showing how to do time delay
#include <stdio.h>
// To use time library of C
#include <time.h>
  
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
        // get heigth
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

void draw(int width, int height, int drawn_pixels_x[], drawn_pixels_y[]) {
    // function that draws all the "pixels" given a certain x width and a y height
    int cols, rows, i = 0, j = 0;

    // loop through the columns
    for (cols = 0; cols < height; cols++) {
        // loop through the rows
        for (rows = 0; rows < width; rows++) {
            if (drawn_pixels_x[i] == row
            printf("%c", BACKGROUND_CARACTER);
            i++;
        }
        printf("\n");
        j++;
    }
}

void rect(int x, int y, int a, int b, int *x_values, int *y_values) {
    int i, j, iterator_i = 0, iterator_j = 0;
    for (i = 0; i <= x; i++) {
        *x_values[iterator_i] = x+i;
        iterator_i++;
    }
    for (j = 0; j <= y; j++) {
        *y_values[iterator_j] = y+j;
        iterator_j++;
    }
}

void create_canvas(int width, int height, int pixels_x[], int pixels_y[]) {
    // initialize the pixels arrays with the BACKGROUND_CARACTER
    int i = 0, j = 0;
    for 
}

int main(void) {

    // define variables
    int width = DEFAULT_WIDTH, height = DEFAULT_HEIGHT;
    int drawn_pixels_x[MAX_WIDTH-MIN_WIDTH], drawn_pixels_y[MAX_HEIGHT-MIN_HEIGHT];
    char selection;

    // change default canvas size if the user wants it
    do {
        system("clear");
        printf("Default canvas size is %dx%d\n", width, height);
        printf("Would you like to change it? [Y/N] ");
        scanf(" %c", selection);
    } while (isdigit(selection) == 1 && selection != 'Y' && selection != 'y' && selection != 'N' && selection != 'n');
    if (selection == 'Y' || selection == 'y') {
        get_canvas_size(&width, &height);
    }

    // draw background
    while (1) {
        system("clear");
        delay(SECONDS_BETWEEN_FRAMES);
        draw(width, height, drawn_pixels_x, drawn_pixels_y);
    }

    return 0;
}
