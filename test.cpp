#include <stdio.h>
#include <stdlib.h>

void CreateMap(int map[20][10])
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            map[i][j] = 0;
        }
    }
}

void Add_block_to_map(int map[20][10], int block[2][2], int pos[2])
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            map[i + pos[1]][j + pos[0]] = block[i][j];
        }
    }
}

void fall(int pos[2])
{
    pos[1]++;
}

void Clear_block_from_map(int map[20][10], int block[2][2], int pos[2])
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            map[i + pos[1]][j + pos[0]] = 0;
        }
    }
}

void Draw(int map[20][10])
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int pos[2] = {4, 0}; // 0 -> pos.x, 1 -> pos.y
    int block[2][2] = {{1, 1}, {1, 1}};
    int map[20][10];

    for (int k = 0; k < 40; k++)
    {
        CreateMap(map);
        Add_block_to_map(map, block, pos);
        Draw(map);
        for (int l = 0; l < 10; l++)
            printf("\n");
        Clear_block_from_map(map, block, pos);
        if (pos[1] < 20)
            fall(pos);
    }

    return EXIT_SUCCESS;
}
