#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 20
#define MAX_LEN 400

int foodX, foodY;
int dir = 4; 
int len = 3;

typedef struct {
    int x;
    int y;
} Point;

Point snake[MAX_LEN];

void draw()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
            {
                printf("#");
            }
            else if (i == foodY && j == foodX)
            {
                printf("*");
            }
            else
            {
                int is_snake = 0;
                for (int k = 0; k < len; k++)
                {
                    if (i == snake[k].y && j == snake[k].x)
                    {
                        if (k == 0) printf("@");
                        else printf("o");
                        is_snake = 1;
                        break; 
                    }
                }
                if (!is_snake) printf(" ");
            }
        }
        printf("\n");
    }
}

void food()
{
    while (1)
    {
        foodX = rand() % (WIDTH - 2) + 1;
        foodY = rand() % (HEIGHT - 2) + 1;
        int is_collision = 0;
        for (int i = 0; i < len; i++)
        {
            if (foodX == snake[i].x && foodY == snake[i].y)
            {
                is_collision = 1;
                break;
            }
        }
        if (is_collision == 0)
        {
            break;
        }
    }
}

void init_snake()
{
    snake[0].x = WIDTH / 2;  
    snake[0].y = HEIGHT / 2; 
    dir = 4; 

    snake[1].x = snake[0].x - 1;
    snake[1].y = snake[0].y;
    snake[2].x = snake[1].x - 1;
    snake[2].y = snake[1].y;
}

void move_snake()
{
    for (int i = len - 1; i > 0; i--)
    {
        snake[i] = snake[i - 1];
    }
    if (dir == 1) snake[0].y--; // 上
    if (dir == 2) snake[0].y++; // 下
    if (dir == 3) snake[0].x--; // 左
    if (dir == 4) snake[0].x++; // 右
}

int main()
{
    srand((unsigned)time(NULL));
    init_snake();
    food();

    printf(" 开局坐标：x=%d, y=%d, dir=%d\n", snake[0].x, snake[0].y, dir);
    printf("按任意键继续...\n");
    _getch(); 

    while (1)
    {
        if (_kbhit())
        {
            int key = _getch();
            if ((key == 'w' || key == 'W') && dir != 2) dir = 1;
            if ((key == 's' || key == 'S') && dir != 1) dir = 2;
            if ((key == 'a' || key == 'A') && dir != 4) dir = 3;
            if ((key == 'd' || key == 'D') && dir != 3) dir = 4;
        }

        move_snake();

        if (snake[0].x == foodX && snake[0].y == foodY)
        {
            len++;
            if (len >= MAX_LEN)
            {
                printf("congruation!\n");
                break;
            }
            food();
        }

        int is_dead = 0;
        if (snake[0].x <= 0 || snake[0].x >= WIDTH - 1 || snake[0].y <= 0 || snake[0].y >= HEIGHT - 1)
        {
            is_dead = 1;
        }
        for (int i = 1; i < len; i++)
        {
            if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
            {
                is_dead = 1;
                break;
            }
        }

        system("cls"); // 清屏
        draw();        // 绘制

        if (is_dead == 1)
        {
            printf("\n oh, you ate %d food! Game over.\n", len - 3);
            printf("按任意键退出游戏...\n");
            _getch(); 
            break;
        }

        Sleep(200);
    }
    return 0;
}