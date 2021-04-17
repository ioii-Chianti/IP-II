#include <stdio.h>
long long length[53],l , r;;
int k;
char s1[5] = "OuQ";
char askingchar(int linex, long long chdex){ // linex 是等同於k 
                                            // chdex 等同於k行的幾個字(0開始)
    if(linex == 1) // 遞迴到1
        return s1[chdex];
    if(chdex == 0) // 剛好要第一個字，一定是O
        return 'O';
    else if (chdex == length[linex]-1) // 剛好要最後一個字，一定是Q
        return 'Q';
    else if (chdex == length[linex-1]+1) // 剛好要中間字，一定是u
        return 'u';
    else
    {
        if(chdex < length[linex-1]+1)
            return askingchar(linex-1,chdex-1); // 將chdex 換算成上一行的第幾個字
        else 
             return askingchar(linex-1,chdex-length[linex-1]-2); // 同理，換算
    }
}

int main(){
    length[1] = 3;
    for(int i=2;i<=53;i++){
        length[i] = 2 * length[i-1] + 3;
    }
    
    while(~scanf("%d %lld %lld", &k, &l, &r)){
        for(int i=l;i<=r;i++){
            printf("%c",askingchar(k,i));
        }
        printf("\n");
    }
    return 0;
}