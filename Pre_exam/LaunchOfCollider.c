#include <stdio.h>
#include <limits.h>
#define MAX 200000
#define min(a, b) ((a) < (b) ? a : b)

int main() {
    int num, gap, minGap = INT_MAX, coordinate[MAX];
    char dic[MAX];
    scanf("%d%s", &num, dic);
    for (int i = 0; i < num; i++)
        scanf("%d", coordinate + i);

    for (int i = 0; i < num - 1; i++) {
        if (dic[i] == 'R' && dic[i + 1] == 'L') {
            gap = (coordinate[i + 1] - coordinate[i]) / 2;
            minGap = min(gap, minGap);
        }
    }
    if (minGap == INT_MAX)
        printf("-1\n");
    else
        printf("%d\n", minGap);
    return 0;
}