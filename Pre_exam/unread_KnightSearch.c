#include <stdio.h>

/* TA's code */

char r[110][110];
char as[13] = "ICPCASIASG";    // 先建一個我要的陣列
int n, flag;                   // n是邊長，flag判斷是否有答案

void rec(int now, int prog){   // now是當前位置(以一維紀錄二維)。
                               // prog是進度，代表我已經到第幾個想要的字了。
    if(prog == 10) {flag=1; return;}

    for(int i=-2; i<=2 && !flag; i++)       // vertical
    for(int j=-2; j<=2 && !flag; j++){      // horizontal
        if( j*j + i*i != 5 || now/n + i < 0 || now/n + i >= n || now%n + j < 0 || now%n + j >= n ) continue;
            // 如果位移量不是合法的，或是跑出邊界，就continue。
        if( r[now/n+i][now%n+j] == as[prog] ) rec( now + i*n + j, prog+1 );
            // 如果這個字元正是我要的這個，那就進度加一，進下一層，找下一個。
    }
    return;
}

int main(){
    scanf("%d\n", &n);
    for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
        scanf("%c", &r[i][j]);

    flag=0;
    int cnt=-1;
    while(cnt < n*n && !flag){
        cnt++;
        if(r[cnt/n][cnt%n] == as[0]) rec(cnt, 1);
            // 從I開始遞迴，如果這個I沒有找到答案，就找下一個I
    }
    printf("%s\n", (flag?"YES":"NO") );
    return 0;
}