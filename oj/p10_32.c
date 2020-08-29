#include <stdio.h>

//计数即可

int main()
{
    int cnt[3] = {0};
    char c;
    while((c=getchar())!=EOF){
        if(c>='0' && c<='2')
            cnt[c-'0']++;
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<cnt[i];j++)
            printf("%c%c",i+'0',i==2&&j==cnt[i]-1?'\n':',');
    }
    return 0;
}