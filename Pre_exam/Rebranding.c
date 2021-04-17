#include <stdio.h>
#include <string.h>
#define MAX 200005

char name[MAX];

int main() {
    memset(name, '\0', sizeof(name));
    int n, T, ch[26];
    scanf("%d%d", &n, &T);
    scanf("%s", name);
    for (int i = 0; i < 26; i++)
        ch[i] = i;

    while (T--) {
        char x, y;
        scanf("\n%c %c", &x, &y);
        int pos_x = x - 'a', pos_y = y - 'a';

        for (int i = 0; i < 26; i++) {
            if (ch[i] == pos_x)
                ch[i] = pos_y;
            else if (ch[i] == pos_y)
                ch[i] = pos_x;
        }
    }
    for (int i = 0; name[i] != '\0'; i++)
        printf("%c", ch[name[i] - 'a'] + 'a');
    printf("\n");

    return 0;
}