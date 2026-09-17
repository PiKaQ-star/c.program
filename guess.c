/*
程序随机生成4个不重复的数字，
玩家进行猜测
程序比较后输出结果：1A1B
A代表数字正确位置正确
B数字正确位置不对
直到4A0B游戏结束，并打印玩家猜了多少次
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
    srand((unsigned)time(NULL));
    int* num = (int*)malloc(4*sizeof(int));
    if (num == NULL)
    {
        printf("内存分配失败");
    }

    int i = 0;
    while (i < 4)
    {
        int temp = rand() % 10;
        int is_repeat = 0;
        for (int j = 0;j < i;j++)
        {
            if (num[j] == temp)
            {
                is_repeat = 1;
                break;
            }
        }
        if (is_repeat == 0)
        {
            num[i] = temp;
            i++;
        }
    }

    int* n = (int*)malloc(4 * sizeof(int));
    if (n == NULL)
    {
        printf("内存分配失败\n");
    }
    for (int time = 0;;time++)
    {
        printf("请输入4个数字");
        scanf("%d %d %d %d", &n[0], &n[1], &n[2], &n[3]);
        int a=0, b = 0;
        for (int i = 0;i < 4;i++)
        {
            if (n[i]==num[i])
            {
                a++;
            }
        }
        for (int i = 0;i < 4;i++)
        {
            for (int j = 0;j < 4;j++)
            {
                if (j != i && n[i] == num[j])
                {
                    b++;
                    break;
                }
            }
        }
        printf("%dA%dB", a, b);
        if (a == 4)
        {
            printf("恭喜，你总共用了%d次", (time + 1));
            break;
        }
    }
    free(n);
    free(num);
    return 0;
}