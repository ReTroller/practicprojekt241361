#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define WIDTH 10
#define HEIGHT 20

int field[HEIGHT][WIDTH] = {0};
int tetromino[4][2];
int x = WIDTH / 2, y = 0;
int shape = 0;

int shapes[7][4][2] = {
    {{0,0},{1,0},{2,0},{3,0}},   // I
    {{0,0},{0,1},{1,0},{1,1}},   // O
    {{0,0},{-1,1},{0,1},{1,1}},  // T
    {{0,0},{1,0},{0,1},{0,2}},   // L
    {{0,0},{-1,0},{0,1},{0,2}},  // J
    {{0,0},{-1,1},{0,1},{1,0}},  // S
    {{0,0},{-1,0},{0,1},{1,1}}   // Z
};

void spawn() {
    shape = rand() % 7;
    for (int i = 0; i < 4; i++) {
        tetromino[i][0] = shapes[shape][i][0];
        tetromino[i][1] = shapes[shape][i][1];
    }
    x = WIDTH / 2;
    y = 0;
}

int checkCollision(int dx, int dy) {
    for (int i = 0; i < 4; i++) {
        int nx = x + tetromino[i][0] + dx;
        int ny = y + tetromino[i][1] + dy;
        if (nx < 0 || nx >= WIDTH || ny >= HEIGHT) return 1;
        if (ny >= 0 && field[ny][nx]) return 1;
    }
    return 0;
}

void place() {
    for (int i = 0; i < 4; i++) {
        int nx = x + tetromino[i][0];
        int ny = y + tetromino[i][1];
        if (ny >= 0) field[ny][nx] = 1;
    }
}

void clearLines() {
    for (int i = HEIGHT - 1; i >= 0; i--) {
        int full = 1;
        for (int j = 0; j < WIDTH; j++) {
            if (!field[i][j]) {
                full = 0;
                break;
            }
        }
        if (full) {
            for (int k = i; k > 0; k--)
                for (int j = 0; j < WIDTH; j++)
                    field[k][j] = field[k-1][j];
            for (int j = 0; j < WIDTH; j++)
                field[0][j] = 0;
            i++; // ????????? ???????? ??????? ??????
        }
    }
}

void draw() {
    system("cls");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int occupied = field[i][j];
            for (int k = 0; k < 4; k++) {
                int tx = x + tetromino[k][0];
                int ty = y + tetromino[k][1];
                if (i == ty && j == tx) occupied = 1;
            }
            printf(occupied ? "[]" : " .");
        }
        printf("\n");
    }
}

void input() {
    if (_kbhit()) {
        char key = _getch();
        if (key == 'a' && !checkCollision(-1, 0)) x--;
        if (key == 'd' && !checkCollision(1, 0)) x++;
        if (key == 's' && !checkCollision(0, 1)) y++;
    }
}

int main() {
    srand(time(NULL));
    spawn();
    while (1) {
        draw();
        input();
        if (!checkCollision(0, 1)) y++;
        else {
            place();
            clearLines();
            spawn();
            if (checkCollision(0, 0)) break; // ????????
        }
        _sleep(300);
    }
    printf("\nGame Over!\n");
    return 0;
}

