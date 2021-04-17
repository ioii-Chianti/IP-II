#include <stdio.h>

int isLeap(int y) {
    if (y % 400 == 0 || y % 4 == 0 && y % 100)
        return 1;
    return 0;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {

        int year, leap, bias = 0;
        scanf("%d", &year);
        leap = isLeap(year);

        while (1) {
            if (isLeap(year))
                bias++;
            bias++;
            year++;
            bias %= 7;
            if (!bias && isLeap(year) == leap)
                break;
        }
        printf("%d\n", year);
    }
    
    return 0;
}