#include <stdio.h>
#include "LBsystem.h"
//9 이상부터 주사위 이미지가 같은 오류 발생 gpt ㅈㄴ 닦달해서 고쳐

#define SIZE 29
#define GAP 15
#define DOT 1

// 점을 3x3 블록으로 찍기
void draw_dot(int canvas[SIZE][SIZE], int x, int y) {
    for (int dy = -DOT; dy <= DOT; dy++) {
        for (int dx = -DOT; dx <= DOT; dx++) {
            int nx = x + dx;
            int ny = y + dy;

            if (nx > 0 && nx < SIZE - 1 && ny > 0 && ny < SIZE - 1)
                canvas[ny][nx] = 1;
        }
    }
}

// 주사위 생성 (완전 대칭)
void make_dice(int canvas[SIZE][SIZE], int value) {

    int mid = SIZE / 2;
    int offset = SIZE / 4;

    int left = mid - offset;
    int right = mid + offset;
    int top = left;
    int bottom = right;

    // 초기화
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            canvas[i][j] = 0;

    switch (value) {

    case 1:
        draw_dot(canvas, mid, mid);
        break;

    case 2:
        draw_dot(canvas, left, top);
        draw_dot(canvas, right, bottom);
        break;

    case 3:
        draw_dot(canvas, left, top);
        draw_dot(canvas, mid, mid);
        draw_dot(canvas, right, bottom);
        break;

    case 4:
        draw_dot(canvas, left, top);
        draw_dot(canvas, right, top);
        draw_dot(canvas, left, bottom);
        draw_dot(canvas, right, bottom);
        break;

    case 5:
        draw_dot(canvas, left, top);
        draw_dot(canvas, right, top);
        draw_dot(canvas, mid, mid);
        draw_dot(canvas, left, bottom);
        draw_dot(canvas, right, bottom);
        break;

    case 6:
        draw_dot(canvas, left, top);
        draw_dot(canvas, right, top);
        draw_dot(canvas, left, mid);
        draw_dot(canvas, right, mid);
        draw_dot(canvas, left, bottom);
        draw_dot(canvas, right, bottom);
        break;

    case 7:
        draw_dot(canvas, left, top);
        draw_dot(canvas, right, top);
        draw_dot(canvas, mid, mid);
        draw_dot(canvas, left, mid);
        draw_dot(canvas, right, mid);
        draw_dot(canvas, left, bottom);
        draw_dot(canvas, right, bottom);
        break;

    case 8:
        draw_dot(canvas, left, top);
        draw_dot(canvas, mid, top);
        draw_dot(canvas, right, top);

        draw_dot(canvas, left, mid);
        draw_dot(canvas, right, mid);

        draw_dot(canvas, left, bottom);
        draw_dot(canvas, mid, bottom);
        draw_dot(canvas, right, bottom);
        break;

    case 9:
        draw_dot(canvas, left, top);
        draw_dot(canvas, mid, top);
        draw_dot(canvas, right, top);

        draw_dot(canvas, left, mid);
        draw_dot(canvas, mid, mid);
        draw_dot(canvas, right, mid);

        draw_dot(canvas, left, bottom);
        draw_dot(canvas, mid, bottom);
        draw_dot(canvas, right, bottom);
        break;

    case 10:
        draw_dot(canvas, left, top);
        draw_dot(canvas, right, top);
        draw_dot(canvas, left, mid);
        draw_dot(canvas, right, mid);
        draw_dot(canvas, left, bottom);
        draw_dot(canvas, right, bottom);

        draw_dot(canvas, mid, top);
        draw_dot(canvas, mid, bottom);
        break;

    case 11:
        draw_dot(canvas, left, top);
        draw_dot(canvas, right, top);
        draw_dot(canvas, left, mid);
        draw_dot(canvas, right, mid);
        draw_dot(canvas, left, bottom);
        draw_dot(canvas, right, bottom);

        draw_dot(canvas, mid, top);
        draw_dot(canvas, mid, mid);
        draw_dot(canvas, mid, bottom);
        break;

    case 12:
        draw_dot(canvas, left, top);
        draw_dot(canvas, mid, top);
        draw_dot(canvas, right, top);

        draw_dot(canvas, left, mid);
        draw_dot(canvas, mid, mid);
        draw_dot(canvas, right, mid);

        draw_dot(canvas, left, bottom);
        draw_dot(canvas, mid, bottom);
        draw_dot(canvas, right, bottom);
        break;
    }
}

// 🎲 출력 함수
void print_dice_pair() {
    int dice1[SIZE][SIZE];
    int dice2[SIZE][SIZE];
    Diceroll();

    make_dice(dice1, Dice1);
    make_dice(dice2, Dice2);

    for (int i = 0; i < SIZE; i++) {

        // 첫 번째 주사위
        for (int j = 0; j < SIZE; j++) {

            if (i == 0 || i == SIZE - 1 || j == 0 || j == SIZE - 1)
                printf("□");
            else if (dice1[i][j])
                printf("■");
            else
                printf(" ");
        }

        // 간격
        for (int g = 0; g < GAP; g++)
            printf(" ");

        // 두 번째 주사위
        for (int j = 0; j < SIZE; j++) {

            if (i == 0 || i == SIZE - 1 || j == 0 || j == SIZE - 1)
                printf("□");
            else if (dice2[i][j])
                printf("■");
            else
                printf(" ");
        }

        printf("\n");
    }

    printf("\n결과: %d , %d (D%d)\n", Dice1, Dice2, Dn);
    system("pause");
    Clearscreen();
}