#include <stdio.h>
#include <stdlib.h>
//字符最多有128个，使用全哈希记录是否有出现过。
//因此直接遍历串t，复杂度<128*n，是O(n)的，比先排序的nlogn快

char s[1000];
char t[1000];
int hash[256];
int locate[256];
char r[1000];
int main()
{
    int num=0;
    scanf("%s%s",s,t);
    for(int i=0;s[i]!=0;i++){
        if(hash[s[i]])
            continue;
        for(int j=0;t[j]!=0;j++){
            if(t[j]==s[i]){
                goto Found;
            }
        }
        r[num]=s[i];
        locate[num++]=i;
Found:
        hash[s[i]] = 1;
    }
    if(!num)
        printf("-1");
    else{
        printf("%s ",r);
        for(int i=0;i<num;i++){
            printf("%d",locate[i]);
        }
    }
    return 0;
}