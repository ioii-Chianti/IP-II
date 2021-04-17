#include <stdio.h>
#include <limits.h>

int main() {
    int n, cur, max = 0, min = INT_MAX;
    scanf("%d", &n);
    for (int i = 0; i < n + 1; i++) {
        scanf("%d", &cur);
        if (cur < min)
            min = cur;
        if (cur > max)
            max = cur;
    }
    printf("%d\n", (max - min) * 2);
    return 0;
}