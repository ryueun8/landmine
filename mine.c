#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void MapOne();
void Boom();
int LandMine();
void Visual();
void MapTwo();
int LandMineAgain();
void VisualAgain();

int main(void)
{
    int a;
    srand(time(NULL));
    printf("1. 8 x 8, 지뢰 10개\n");
    printf("2. 16 x 16, 지뢰 40개\n");
    scanf("%d", &a);

    if (a == 1)
    {
        int p;
        int *k = &p;
        int x, y;
        int *X_count = &x;
        int *Y_count = &y;
        int p1;
        int *Mine_count = &p1;
        int map[8][8] = {};
        *Mine_count = 10;
        *X_count = 8;
        *Y_count = 8;
        *k = 8;
        MapOne(map, sizeof(map) / sizeof(map[0]), &p1, &x, &y);
    }
    else if (a == 2)
    {
        int x, y;
        int *X_count = &x;
        int *Y_count = &y;
        int p1;
        int *Mine_count = &p1;
        int map[16][16] = {};
        *Mine_count = 30;
        *X_count = 16;
        *Y_count = 16;
        MapTwo(map, sizeof(map) / sizeof(map[0]), &p1, &x, &y);
    }

    else
        printf("다시 입력해주세요.\n");

    return 0;
}
// 8x8 지뢰찾기
void MapOne(int (*map)[8], int len, int *Mine_count, int *X_count, int *Y_count)
{
    int map_x;
    int map_y;
    int temp;
    char a;
    int cnt = 0;
    int land_mine_x = 0, land_mine_y = 0;

    srand(time(NULL));

    for (int l = 0; l < *Mine_count; l++)
    {
        land_mine_x = rand() % *X_count;
        land_mine_y = rand() % *Y_count;
        if (map[land_mine_x][land_mine_y] == 0)
            map[land_mine_x][land_mine_y] = 6;
        else //중복제거
            l--;
    }
    system("clear");

    while (1)
    {
        int bom = 0;
        //출력확인용
        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < len; j++)
            {
                if (map[i][j] == 6)
                    printf("*");
                else
                    printf("%d", LandMine(map, j, i, 8));
            }
            printf("\n");
        }
        printf("\n");

        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < len; j++)
            {
                if (map[i][j] == 0 || map[i][j] == 6)
                    printf("⬜️ ");
                if (map[i][j] == 1)
                {
                    bom = LandMine(map, j, i, 8);
                    printf("%3d", bom);
                }
                if (map[i][j] == 2)
                    printf("🚩 ");
            }
            printf("\n");
        }

        printf("a. 깃발(지뢰 있는 곳을 표시할 수 있습니다.)\n");
        printf("b. 칸 제거\n");
        scanf(" %c", &a);
        if (a == 'a')
        {
            printf("깃발을 사용할 곳의 x, y 좌표를 입력해주세요.(0~7)\n");
            scanf("%d %d", &map_x, &map_y);
            getchar();

            map[map_x][map_y] == 2;
        }
        else if (a == 'b')
        {
            printf("x, y 좌표를 입력해주세요.(0~7)");
            scanf("%d %d", &map_x, &map_y);

            //지뢰발견
            if (map[map_x][map_y] == 6)
            {
                for (int y = 0; y < 3; y++)
                {
                    system("clear");
                    printf("지뢰발견\n");
                    usleep(500000);
                    system("clear");
                    usleep(500000);
                }
                Visual(map, X_count, Y_count); //폭탄 위치표시
                sleep(1);

                exit(1);
            }
            cnt=0;
            for (int i = 0; i < len; i++)
            {
                for (int j = 0; j < len; j++)
                {
                    if (map[i][j] != 1)
                    {
                        cnt++;
            
                    }
                }
            }
            if (cnt == 11)
            {
                system("clear");
                printf("승리하셨습니다.\n");
                usleep(500000);
                system("clear");
                usleep(500000);
                exit(1);
            }
            //입력한 숫자가 배열의 크기보다 클 때
            if (map_x < 0 || map_y < 0 || map_x > *X_count - 1 || map_y > *Y_count - 1)
            {
                printf("다시 입력해주세요.\n");
                usleep(500000);
                system("clear");
                continue;
            }
            //전에 없앤 블록을 다시 선택했을때
            if (map[map_x][map_y] == 1)
            {
                printf("이미 없어진 블록입니다.\n");
                printf("다시 입력해주세요\n");
                usleep(500000);
                system("clear");
                continue;
            }
            map[map_x][map_y] = 1;
            bom = LandMine(map, map_y, map_x, 8);
            if (bom == 0)
            {
                for (int k = map_x - 1; k <= map_x + 1; k++)
                {
                    for (int y = map_y - 1; y <= map_y + 1; y++)
                    {
                        if (map[k][y] == 0)
                        {
                            if (k >= 0 && k < 8 && y >= 0 && y < 8)
                            {
                                map[k][y] = 1;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            printf("다시 입력해주세요.\n");
            usleep(500000);
        }
        system("clear");
    }
}
//주변 지뢰갯수 표시
int LandMine(int (*map)[8], int xpos, int ypos, int Maxlen)
{
    int ret = 0;
    int ymax = (ypos + 1 >= Maxlen - 1) ? Maxlen - 1 : ypos + 1;
    int xmax = (xpos + 1 >= Maxlen - 1) ? Maxlen - 1 : xpos + 1;
    int xmin = (xpos - 1 < 0) ? 0 : xpos - 1;
    int ymin = (ypos - 1 < 0) ? 0 : ypos - 1;

    for (int i = ymin; i <= ymax; i++)
    {
        for (int j = xmin; j <= xmax; j++)
        {
            if (map[i][j] == 6)
            {
                ret++;
            }
        }
    }
    return ret;
}
//게임아웃, 지뢰 위치 표시
void Visual(int (*map)[8], int *X_count, int *Y_count)
{
    system("clear");
    for (int i = 0; i < *X_count; i++)
    {
        for (int j = 0; j < *Y_count; j++)
        {
            if (map[i][j] == 0)
                printf("⬜️ ");
            if (map[i][j] == 1)
                printf("⬛ ");
            if (map[i][j] == 6)
                printf("💥 ");
        }
        printf("\n");
    }
}
// 16x16배열
void MapTwo(int (*map)[16], int len, int *Mine_count, int *X_count, int *Y_count)
{
    int map_x;
    int map_y;
    int temp;
    char a;
    int cnt = 0;
    int land_mine_x = 0, land_mine_y = 0;

    for (int l = 0; l < *Mine_count; l++)
    {
        land_mine_x = rand() % *X_count;
        land_mine_y = rand() % *Y_count;
        if (map[land_mine_x][land_mine_y] == 0)
            map[land_mine_x][land_mine_y] = 6;
        else //중복제거
            l--;
    }
    system("clear");

    while (1)
    {
        int bom = 0;
        //출력확인용
        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < len; j++)
            {
                if (map[i][j] == 6)
                    printf("*");
                else
                    printf("%d", LandMineAgain(map, j, i, 16));
            }
            printf("\n");
        }
        printf("\n");

        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < len; j++)
            {
                if (map[i][j] == 0 || map[i][j] == 6)
                {
                    printf("⬜️ ");
                    cnt++;
                }
                if (map[i][j] == 1)
                {
                    bom = LandMineAgain(map, j, i, 16);
                    printf("%3d", bom);
                }
                if (map[i][j] == 2)
                    printf("🚩 ");
            }
            printf("\n");
        }

        printf("a. 깃발(지뢰 있는 곳을 표시할 수 있습니다.)\n");
        printf("b. 칸 제거\n");
        scanf(" %c", &a);
        if (a == 'a')
        {
            printf("깃발을 사용할 곳의 x, y 좌표를 입력해주세요.(0~7)\n");
            scanf("%d %d", &map_x, &map_y);
            getchar();

            map[map_x][map_y] == 2;
        }
        else if (a == 'b')
        {
            printf("x, y 좌표를 입력해주세요.(0~7)");
            scanf("%d %d", &map_x, &map_y);

            //지뢰발견
            if (map[map_x][map_y] == 6)
            {
                for (int y = 0; y < 3; y++)
                {
                    system("clear");
                    printf("지뢰발견\n");
                    usleep(500000);
                    system("clear");
                    usleep(500000);
                }
                VisualAgain(map, X_count, Y_count); //폭탄 위치표시
                sleep(1);

                exit(1);
            }
            cnt=0;
            for (int i = 0; i < len; i++)
            {
                for (int j = 0; j < len; j++)
                {
                    if (map[i][j] != 1)
                    {
                        cnt++;
            
                    }
                }
            }
            if (cnt == 40)
            {
                system("clear");
                printf("승리하셨습니다.\n");
                usleep(500000);
                system("clear");
                usleep(500000);
                exit(1);
            }
            
            //입력한 숫자가 배열의 크기보다 클 때
            if (map_x < 0 || map_y < 0 || map_x > *X_count - 1 || map_y > *Y_count - 1)
            {
                printf("다시 입력해주세요.\n");
                usleep(500000);
                system("clear");
                continue;
            }

            //전에 없앤 블록을 다시 선택했을때
            if (map[map_x][map_y] == 1)
            {
                printf("이미 없어진 블록입니다.\n");
                printf("다시 입력해주세요\n");
                usleep(500000);
                system("clear");
                continue;
            }
            map[map_x][map_y] = 1;
            bom = LandMineAgain(map, map_y, map_x, 16);
            if (bom == 0)
            {
                for (int k = map_x - 1; k <= map_x + 1; k++)
                {
                    for (int y = map_y - 1; y <= map_y + 1; y++)
                    {
                        if (map[k][y] == 0)
                        {
                            if (k >= 0 && k < 8 && y >= 0 && y < 8)
                            {
                                map[k][y] = 1;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            printf("다시 입력해주세요.\n");
            usleep(500000);
        }
        system("clear");
    }
}

// 16x16
void VisualAgain(int (*map)[16], int *X_count, int *Y_count)
{
    system("clear");
    for (int i = 0; i < *X_count; i++)
    {
        for (int j = 0; j < *Y_count; j++)
        {
            if (map[i][j] == 0)
                printf("⬜️ ");
            if (map[i][j] == 1)
                printf("⬛ ");
            if (map[i][j] == 6)
                printf("💥 ");
        }
        printf("\n");
    }
}
int LandMineAgain(int (*map)[16], int xpos, int ypos, int Maxlen)
{
    int ret = 0;
    int ymax = (ypos + 1 >= Maxlen - 1) ? Maxlen - 1 : ypos + 1;
    int xmax = (xpos + 1 >= Maxlen - 1) ? Maxlen - 1 : xpos + 1;

    for (int i = ypos - 1; i <= ymax; i++)
    {
        for (int j = xpos - 1; j <= xmax; j++)
        {
            if (map[i][j] == 6)
            {
                ret++;
            }
        }
    }
    return ret;
}
