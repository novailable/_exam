#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int ac, char **av)
{
    if (ac != 4)
        return 1;

    int w = atoi(av[1]);
    int h = atoi(av[2]);
    int it = atoi(av[3]);

    char *board = calloc(w * h, 1);
    if (!board)
        return 1;

    /* --------------------------- DRAW --------------------------- */

    int x = 0, y = 0;
    int pen = 0;
    char c;

    while (read(0, &c, 1) == 1)
    {
        switch (c)
        {
            case 'x':
                pen = !pen;
                break;

            case 'w': y--; break;
            case 's': y++; break;
            case 'a': x--; break;
            case 'd': x++; break;
        }

        if (pen && x >= 0 && y >= 0 && x < w && y < h)
            board[y * w + x] = 1;
    }

    /* --------------------- GAME OF LIFE LOOP --------------------- */

    while (it--)
    {
        char *nb = calloc(w * h, 1);
        if (!nb)
            return 1;

        for (int yy = 0; yy < h; yy++)
        {
            for (int xx = 0; xx < w; xx++)
            {
                int	count = 0;
				for (int dx = -1; dx <= 1; dx++)
				{
					for (int dy = -1; dy <= 1; dy++)
					{
						if (dx != 0 || dy != 0)
						{
							int nx = xx + dx;
							int ny = yy + dy;
							if (nx >= 0 && ny >= 0 && nx < w && ny < h)
								count += board[ny * w + nx];
						}
					}
				}
				char alive = board[yy * w + xx];
				if ((alive && (count == 2 || count == 3)) || (!alive && count == 3))
					nb[yy * w + xx] = 1;
            }
        }
        free(board);
        board = nb;
    }

    /* ---------------------------- PRINT ---------------------------- */

    for (int yy = 0; yy < h; yy++)
    {
        for (int xx = 0; xx < w; xx++)
            putchar(board[yy * w + xx] ? 'O' : ' ');
        putchar('\n');
    }

    free(board);
    return 0;
}
