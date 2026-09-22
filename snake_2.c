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
int is_paused = 0;

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
            // 纯半角字符，绝对不允许出现全角！
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                printf("#"); // 墙
            else if (i == foodY && j == foodX)
                printf("*"); // 食物
            else
            {
                int is_snake = 0;
                for (int k = 0; k < len; k++)
                {
                    if (i == snake[k].y && j == snake[k].x)
                    {
                        if (k == 0) printf("@"); // 蛇头
                        else printf("o");       // 蛇身
                        is_snake = 1;
                        break; 
                    }
                }
                if (!is_snake) printf(" "); // 纯半角空格
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
    if (dir == 1) snake[0].y--;
    if (dir == 2) snake[0].y++;
    if (dir == 3) snake[0].x--;
    if (dir == 4) snake[0].x++;
}


int main()
{
    system("chcp 65001 > nul"); // 开启UTF-8编码，支持特殊符号
    srand((unsigned)time(NULL));

    printf("game will be start\n");
    printf("p/P is pause,r/R is restart,q/Q is quit\n");
    printf("w/a/s/d can control your directions\n");
    printf("now enjoy your game\nhave a good luck!\n");
    printf("按任意键开始游戏\n");
    _getch();


    init_snake();
    food();

    while (1)
    {
        if (_kbhit())
        {
            int key = _getch();
            if ((key == 'w' || key == 'W') && dir != 2) dir = 1;
            if ((key == 's' || key == 'S') && dir != 1) dir = 2;
            if ((key == 'a' || key == 'A') && dir != 4) dir = 3;
            if ((key == 'd' || key == 'D') && dir != 3) dir = 4;
            if ((key == 'p' || key == 'P'))
            {
                is_paused = 1;
            }
            if (is_paused)
            {
                system("cls");
                printf("pause the game\n");
                printf("press any key to continue\n");
                printf("Press R to restartgame,Q to quit\n");
                int choice = _getch();
                if ((choice == 'q' || choice == 'Q'))
                {
                    break;
                }
                if ((choice == 'r' || choice == 'R'))
                {
                    init_snake();
                    food();
                    len = 3;
                    is_paused = 0;
                    continue;
                }
                else
                {
                    is_paused = 0;
                    continue;
                }
            }
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

        system("cls");
        draw();

        if (is_dead == 1)
        {
            printf("\n💥 oh, you ate %d food! Game over.\n", len - 3);
            printf("play game again?\n");
            printf("r:restart\nq:quit\n");
            while(1)
           {
            int choice_2 = _getch();
            if ((choice_2 == 'q' || choice_2 == 'Q'))
            {
                return 0;
            }
            else if(choice_2 == 'r' || choice_2 == 'R')
            {
                init_snake();
                food();
                len = 3;
                is_dead = 0;
                is_paused = 0;
                break;
            }
            }
            continue;
        }

        Sleep(200);

    }
    return 0;
}