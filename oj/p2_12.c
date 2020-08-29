#include <stdio.h>
#include<ctype.h>
char s[2][10000];

int main()
{
    char c;
    int ix=0;
    int iy=0;
    while((c=getchar())!=EOF&&c!=';')
    {
        if(isalnum(c))
            s[0][ix++] = c;
    }
    while((c=getchar())!=EOF)
    {
        if(isalnum(c))
            s[1][iy++] = c;
    }

    for(int i=0;i<10000;i++)
    {
        if(s[0][i]<s[1][i]){
            printf("%d",1);
            break;
        }
       if(s[0][i]>s[1][i]){
            printf("%d",2);
            break;
        }
        else if(!s[0][i]){
            printf("%d",0);
            break;
        }
    }
    
    return 0;

}