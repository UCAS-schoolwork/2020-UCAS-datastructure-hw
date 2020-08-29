#include <stdio.h>
//Sequential Table(i.e.array) is enough.

char inp[1000];
int main()
{
    char c;
    int ix=0;
    while((c=getchar())!=EOF&&c!='@'){
        inp[ix++]=c;
    }
    for(int i=0;i<ix/2;i++){
        if(inp[i]!=inp[ix-1-i]){
            printf("0");
            return 0;
        }
    }
    printf("1");
    return 0;
}