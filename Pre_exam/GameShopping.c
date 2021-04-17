#include <stdio.h>
#define MAX 1000

int main() {
    int game[MAX], num_game, num_bill, money, pos = 0, cnt = 0;
    scanf("%d%d", &num_game, &num_bill);
    for (int i = 0; i < num_game; i++)
        scanf("%d", game + i);

    for (int i = 0; i < num_bill, pos < num_game; i++) {
        scanf("%d", &money);
        while (pos < num_game) {
            if (money >= game[pos]) {
                pos++;
                cnt++;
                break;
            } pos++;
        }
    }
    printf("%d\n", cnt);
    return 0;
}