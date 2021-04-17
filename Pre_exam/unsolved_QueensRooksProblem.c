#include <stdio.h>
#define MAX 9

int N, M, side;
char board[MAX][MAX];
int queen[MAX], rook[MAX];

void place(int row, int n, int m) {
    // for (int i = 0; i < side; i++)
}

int main() {
    int N, M, side;
    scanf("%d%d", &N, &M);
    side = N + M;
    place(0, 0, 0);
    return 0;
}