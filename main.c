/*MADE BY TOMAS VIDAL*/
/*SIMPLE GRAPHIC ENGINE*/
/*THE PURPOSE IT IS TO PROVIDE THE USER WITH BASIC */
/*GRAPHICS UTILITY, SO THE USER CAN DESIGN SOFITICATED ANIMATIONS*/
/*AN EXAMPLE: A SIMPLE PENDULUM*/

/*IMPORTACION DE LIBRERIAS*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <locale.h>

/*DEFINO CONSTANTES*/
#define VERSION 2
#define PI 3.14

#define MIN_WIDTH 5
#define MAX_WIDTH 300
#define MIN_HEIGHT 5
#define MAX_HEIGHT 300
#define WIDTH_DIFFERENCE 295
#define HEIGTH_DIFFERENCE 295

#define DEFAULT_WIDTH 148
#define DEFAULT_HEIGHT 36

#define BACKGROUND_CARACTER ' '
#define PAINTED_CARACTER '#'

#define GRAVITY 0.1
#define PENDULUM_MASS 5000
#define STARTING_ANGLE 1

 /*#define SECONDS_BETWEEN_FRAMES 1*/
/*PARA 30 FPS*/
 #define SECONDS_BETWEEN_FRAMES 33
/*PARA 5 FPS*/
/*#define SECONDS_BETWEEN_FRAMES 200*/

#define MAX_FIB 150

/*#define clc() system("clear")*/
#define clc() system("cls")


/*DEFINICION DE FUNCIONES*/
void fibonacci(int, int);
void display_clock(int, int, int);
void get_canvas_size(int *, int *);
void draw(void);
void rect(int, int, int, int, char);
void display_canvas_border(char, char, char);
void line(int, int, int, int, int, char, char, char, char);
void fill_canvas(char);
void pendulum(int, int, int, int, int, float, char, float, float);
void delay(int);
void display_debug_data(int);

/*DEFINICION DE VARIABLES GLOBALES*/
int width = DEFAULT_WIDTH, height = DEFAULT_HEIGHT;
char pixels[WIDTH_DIFFERENCE][HEIGTH_DIFFERENCE];

/*LOOP PRINCIPAL*/
int main(void) {
    /*defino variables*/
    char selection;

    clc();
    printf("Languaje: %s\n", setlocale(LC_ALL, "spanish"));

    /*cambio el valor por defecto del dibujo si se quiere*/
    do {
        /*clc();*/
        printf("El tamaño por defecto es %dx%d\n", width, height);
        printf("¿Querés cambiarlo? [S/N] ");
        scanf(" %c", &selection);
    } while (isdigit(selection) == 1 && selection != 'S' && selection != 's' && selection != 'N' && selection != 'n');
    if (selection == 'S' || selection == 's') {
        get_canvas_size(&width, &height);
    }

    /*lleno el arreglo con el fondo*/
    fill_canvas(BACKGROUND_CARACTER);

    /*llena el arreglo con un cuadrado que cubre los bordes*/
    /*rect(0, 0, width-1, height-1, PAINTED_CARACTER, pixels);*/
    /*rect(width/2, height/2, width/2+4, height/2+4, PAINTED_CARACTER, pixels);*/

    /*dibujo en pantalla el arreglo*/
    int current_frame = 0, t;
    while (current_frame < 10000) {

        /*dibujo en pantalla datos de debug*/
        display_debug_data(current_frame++);
        /*printf("dx: %d, dy: %d, theta: %lf, angular_frequency: %lf \n", dx, dy, theta, angular_frequency);*/

        delay(SECONDS_BETWEEN_FRAMES);
        clc();

        fill_canvas(BACKGROUND_CARACTER);
        display_canvas_border('O', '-', '|');

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

        /*pendulum(width/3-3, 1, height/2+3, 3, t, STARTING_ANGLE, PAINTED_CARACTER, GRAVITY, PENDULUM_MASS);*/

        /*pendulum(width/3, 1, height/2, 1, t+125, STARTING_ANGLE, PAINTED_CARACTER, GRAVITY, PENDULUM_MASS, width, height, pixels);*/

        display_clock(width/2, height/2, height/3);

        draw();

        t++;
    }

    return 0;
}

void delay(int milliseconds) {
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

void get_canvas_size(int *w, int *h) {
    /*seteo los valores del tamaño del arreglo*/
    char selection;

    do {
        /*ancho*/
        do {
            clc();
            printf("Ingrese el ancho (%d - %d): ", MIN_WIDTH, MAX_WIDTH);
            scanf("%d", w);
        } while (isdigit(*w) == 1 || *w < MIN_WIDTH || *w > MAX_WIDTH);
        /*alto*/
        do {
            clc();
            printf("Ingrese el alto (%d - %d): ", MIN_HEIGHT, MAX_HEIGHT);
            scanf("%d", h);
        } while (isdigit(*h) == 1 || *h < MIN_WIDTH || *h > MAX_WIDTH);

        clc();
        printf("El nuevo tamaño es %dx%d \n", *w, *h);
        /*repetir hasta que la respuesta sea correcta*/
        do {
            printf("\n¿Querés volver a cambiar el valor? [S/N] ");
            scanf(" %c", &selection);
        } while ( selection != 'N' && selection != 'n' && selection != 's' && selection != 'S');

    } while (selection != 'N' && selection != 'n');

}

void draw() {
    /*dibuja en pantalla todos los valores del arreglo*/
    int i, j;

    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            /*printf("%c", pixels[i][j]);*/
            putchar(pixels[i][j]);
        }
        printf("\n");
    }
}

void rect(int x, int y, int a, int b, char paint) {
    /*cuadrado desde esquina superior izquierda (x,y) hasta esquina inferior derecha (x+a, y+b)*/
    int i, j;

    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            /*compruebo que el "pixel" este entre los parametros correctos*/
            if (j >= y && j <= (y+b) && i == x) {
                /*linea izquierda*/
                pixels[i][j] = paint;
            } else if (j >= y && j <= (y+b) && i == (x+a)) {
                /*linea derecha*/
                pixels[i][j] = paint;
            } else if (i > x && i < (x+a) && j == (y)) {
                /*linea de arriba*/
                pixels[i][j] = paint;
            } else if (i > x && i < (x+a) && j == (y+b)) {
                /*linea de abajo*/
                pixels[i][j] = paint;
            }
        }
    }
}

void circle(int x, int y, int r, int thickness, char paint) {
    /*circunferencia de radio r y centro (x,y)*/
    int i, j;
    int diameter = 2*r;
    int Rin = r - thickness;
    int Rout = r + thickness;
    int Rin2 = pow(Rin, 2);
    int Rout2 = pow(Rout, 2);

    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            int val = pow(i-x, 2) + pow(j-y, 2);
            if ( i >= (x-diameter) && i <= (x+diameter) && val >= Rin2 && val <= Rout2) {
                pixels[i][j] = paint;
            }
        }
    }
}

void fill_canvas(char paint) {
    /*inicializo el arreglo con los caracteres de fondo*/
    int i, j;
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            pixels[i][j] = paint;
        }
    }
}

void point(int x, int y, char paint) {
    /*crea un punto en (x,y)*/
    int i, j;
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            if (i == x && j == y) {
                pixels[i][j] = paint;
            }
        }
    }
}


void line(int a_, int b_, int c_, int d_, int thickness, char paint_diag_left_right, char paint_diag_right_left, char paint_vertical, char paint_horizontal) {
    /*recta desde (a,b) hasta (c,d)*/
    int x, y, a, b, c, d;
    float m, gamma;

    if ( 0 <= a_ && a_ <= width && 0 <= c_ && c_ <= width && 0 <= b_ && b_ <= height && 0 <= d_ && d_ <= height ) {

        /*reflejo el eje x*/
        b *= -1;
        d *= -1;

        /*reverso los puntos si se dan que estan mal dados*/
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
            /*clc();*/
            /*printf("\"IN LINE:\" %d-%d / %d-%d = %lf, gamma=%lf\n", d,b,c,a,m, gamma);*/
            if (m > 0) { /*diagonal '\\'*/
                for (y = 0; y < height; y++) {
                    for (x = 0; x < width; x++) {
                        int rect_y = abs( (float) m*x + gamma);
                        if (x >= a && x <= c && y == rect_y) {
                            pixels[x][y] = paint_diag_left_right;
                            /*pixels[x][y] = '\\';*/
                        }
                    }
                }
            } else { /*diagonal '/'*/
                for (y = 0; y < height; y++) {
                    for (x = 0; x < width; x++) {
                        int rect_y = abs( (float) m*x + gamma);
                        if (x >= a && x <= c && y == rect_y) {
                            pixels[x][y] = paint_diag_right_left;
                            /*pixels[x][y] = '/';*/
                        }
                    }
                }
            }
        } else if (a == c && b != d) {
            if (d > b) {
                for (y = 0; y < height; y++) {
                    for (x = 0; x < width; x++) {
                            if ( y >= b && y <= d && x == a) {
                                pixels[x][y] = paint_vertical;
                                /*pixels[x][y] = '|';*/
                            }
                    }
                }
            } else if (b > d) {
                for (y = 0; y < height; y++) {
                    for (x = 0; x < width; x++) {
                            if ( y <= b && y >= d && x == a) {
                                pixels[x][y] = paint_vertical;
                                /*pixels[x][y] = '|';*/
                            }
                    }
                }
            }
        } else if ( a != c && b == d) {
            for (y = 0; y < height; y++) {
                for (x = 0; x < width; x++) {
                    if ( x >= a && x <= c && y == b ) {
                        pixels[x][y] = paint_horizontal;
                        /*pixels[x][y] = '-';*/
                    }
                }
            }
        } else {
            printf("ERROR: in line function");
            /*exit(1);*/
        }

    }

}

void pendulum(int x, int y, int L, int ball_radius, int t, float starting_angle, char paint, float gravity, float mass) {
    /*crea un pendulo agarrado en (x,y) y de longitud L*/
    float deg_to_radiants = PI/180;
    float angular_frequency = sqrt((gravity/mass));
    /*float theta = starting_angle*sin(angular_frequency*t);*/

    int dx = x + sin(starting_angle - angular_frequency*deg_to_radiants*t)*L;
    int dy = y + cos(starting_angle - angular_frequency*deg_to_radiants*t)*L;

    line(x, y, dx, dy-ball_radius, 0, '\\', '/', '|', '-');
    point(x, y, 'o');
    circle(dx, dy, ball_radius, 0, '+');

}

void display_canvas_border(char corners_paint, char horizontal_paint, char vertical_paint) {
    /*dibuja el borde del cuadro del arreglo*/
    line(0, 0, width-1, 0, 0, '\\', '/', '|', horizontal_paint);
    line(0, height-1, width-1, height-1, 0, '\\', '/', '|', horizontal_paint);
    line(0, 1, 0, height-1, 0, '\\', '/', vertical_paint, '-');
    line(width-1, 1, width-1, height-1, 0, '\\', '/', vertical_paint, '-');
    point(0, 0, corners_paint);
    point(width-1, 0, corners_paint);
    point(0, height-1, corners_paint);
    point(width-1, height-1, corners_paint);
}

void display_clock(int x, int y, int max_radius) {
    /*crea un reloj que muestra la hora actual con centro (x,y) y radio max_radius*/
    int r = max_radius - 1;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    float PI4 = PI/4;
    float PI12 = PI/6;
    float PI60 = PI/30;
    int hours = tm.tm_hour;
    int minutes = tm.tm_min;
    int seconds = tm.tm_sec;

    /*get the end point of the date arrows*/
    int Hx = r*cos( (float) PI12*hours - PI4);
    int Hy = r*sin( (float) PI12*hours - PI4);
    int Mx = r*cos( (float) PI60*minutes - PI4);
    int My = r*sin( (float) PI60*minutes - PI4);
    int Sx = r*cos( (float) PI60*seconds - PI4);
    int Sy = r*sin( (float) PI60*seconds - PI4);

    circle(x, y, max_radius, 1, '.');

    line(x, y, x+Hx, y+Hy, 0, '\\', '/', '|', '-');
    line(x, y, x+Mx, y+My, 0, '\\', '/', '|', '-');
    line(x, y, x+Sx, y+Sy, 0, '\\', '/', '|', '-');

    point(x+Hx, y+Hy, 'H');
    point(x+Mx, y+My, 'M');
    point(x+Sx, y+Sy, 'S');
    point(x, y, 'O');

    point(x, y-max_radius, '1');
    point(x+1, y-max_radius, '2');
    point(x-max_radius, y, '9');
    point(x, y+max_radius, '6');
    point(x+max_radius, y, '3');

    /*printf("Hora actual: %d:%d:%d \n", tm.tm_hour, tm.tm_min, tm.tm_sec);*/

}

void fibonacci(int f0, int f1) {
    int fib;

    fib = f0 + f1;
    printf("%d\n", fib);

    if (fib >= MAX_FIB) {
        printf("\n\nERROR: max number is %d and n is %d\n", MAX_FIB, fib);
        return;
    }

    f0 = f1;
    f1 = fib;

    fibonacci(f0, f1);

}

void display_debug_data(int current_frame) {
    /*muetro en pantalla datos utiles para el programador*/
    printf("\nFRAME COUNT: %d\n", current_frame++);
    printf("FPS: %d\n", 1000/SECONDS_BETWEEN_FRAMES);
    printf("RESOLUTION: %dx%d\n", width, height);
    printf("VERSION: %d\n", VERSION);
}
