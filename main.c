#include <stdio.h>
#include <unistd.h>
#include <math.h>

#define R1 4
#define R2 10
#define SCREEN_WIDTH 100
#define COL 80
#define ROW 30

const char light_symb[13] = ".,-~:;=!*#$@";
const double theta_step = 0.02;
const double phi_step = 0.02;
const double rotate_speed = 0.02;
char output_buf[ROW * COL] = {0};

struct zbuf {
    double z;
    double L;
};

void clear_screen(void);
void hide_cursor(void);
void show_cursor(void);
void move_cursor(int x, int y);
void init_zbuf(struct zbuf zbuf[][SCREEN_WIDTH]);
void init_output(void);


int main(void) {
    hide_cursor();
    clear_screen();
    double A = 0, B = 0;
    struct zbuf zbuf[SCREEN_WIDTH][SCREEN_WIDTH] = {0};
    init_zbuf(zbuf);
    init_output();
    while (1) {
        clear_screen();
        A += rotate_speed;
        B += rotate_speed;
        double cosA = cos(A);
        double cosB = cos(B);
        double sinA = sin(A);
        double sinB = sin(B);
        for (double theta = 0; theta < M_PI * 2; theta += theta_step) {
            for (double phi = 0; phi < M_PI * 2; phi += phi_step) {
                double x = (R2 + R1 * cos(theta)) * (cosB * cos(phi) + sinA * sinB * sin(phi))
                    - R1 * cosA * sinB * sin(theta);
                double y = (R2 + R1 * cos(theta)) * (cos(phi) * sinB - cosB * sinA * sin(phi))
                    + R1 * cosA * cosB * sin(theta);
                double z = cosA * (R2 + R1 * cos(theta)) * sin(phi) + R1 * sinA * sin(theta);
                // double L = cos(phi) * cos(theta) * sinB - cosA * cos(theta) * sin(phi) 
                //     - sinA * sin(theta) + cos(theta) * 
                //     (cosA * sin(theta) - cos(theta) * sinA * sin(theta));
                double L = cosA * cos(theta) * sin(phi) + sinA * sin(theta) 
                    + cos(theta) * (cos(phi) * sinB - cosB * sinA * sin(phi))
                    + cosA * cosB * sin(theta);
                // L = L / sqrt(2);
// because the symbol's length and width are different, this is to center the circle
                int x1 = x + ROW / (double)2;
                int y1 = y + COL / (double)2;
                if (zbuf[x1][y1].L == -5) {
                    zbuf[x1][y1].L = L;
                    zbuf[x1][y1].z = z;
                } else if (z > zbuf[x1][y1].z) {
                    zbuf[x1][y1].L = L;
                    zbuf[x1][y1].z = z;
                }
            }
        }
        for (int i = 0; i < SCREEN_WIDTH; i++ ) {
            for (int j = 0; j < SCREEN_WIDTH; j++) {
                if (zbuf[i][j].L != -5) {
                    char ch;
                    if (zbuf[i][j].L < 0)
                        ch = '.';
                    else
                        ch = light_symb[(int)(zbuf[i][j].L * 8)];
                    output_buf[i * COL + j] = ch;
                }
            }
        }

        move_cursor(10, 0);
        printf("%s", output_buf);
        usleep(7000);
        init_zbuf(zbuf);
        init_output();
    }
    show_cursor();
    return 0;
}
void init_zbuf(struct zbuf zbuf[][SCREEN_WIDTH]) {
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            zbuf[i][j].L = -5;
        }
    }
}

void clear_screen(void) {
    printf("\033[2J");
}

void hide_cursor(void) {
    printf("\033[?25l");
}

void show_cursor(void) {
    printf("\033[?25h");
}

void move_cursor(int x, int y) {
    printf("\033[%d;%dH", x, y);
}

void init_output(void) {
    for (int i = 0; i < sizeof(output_buf); i++) {
        if (i > 0 && i % COL == 0) {
            output_buf[i] = '\n';
        } else {
            output_buf[i] = ' ';
        }
    }
}
