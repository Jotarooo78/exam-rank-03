#include "nqueens.h"

void    print_board(char *board, int n)
{
    int i = 0;

    while (i < n)
    {
        printf("%d", board[i]);
        if (i < n - 1)
            printf(" ");
        i++;
    }
    printf("\n");
}

int is_valid(char *board, int col, int row)
{
    int i = 0;

    while (i < row)
    {
        if (board[i] == col || board[i] - i == col - row || board[i] + i == col + row)
            return (0);
        i++;
    }
    return (1);
}

void    nqueens(char *board, int n, int row)
{
    int col = 0;

    if (row == n)
    {
        print_board(board, n);
        return ;
    }
    while (col < n)
    {
        if (is_valid(board, col, row) == 1)
        {
            board[row] = col;
            nqueens(board, n, row + 1);
        }
        col++;
    }
}

int main(int argc, char **argv)
{
    int n;
    if (argc == 2)
        n = atoi(argv[1]);
    else
        return (1);
    int i;
    char board[10000];
    i = 0;
    while (i < n)
    {
        board[i] = 0;
        i++;
    }
    nqueens(board, n, 0);
    return (0);
}