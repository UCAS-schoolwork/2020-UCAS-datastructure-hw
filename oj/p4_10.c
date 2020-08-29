#include <stdio.h>
#include <string.h>
void Reverse(char *s,int len)
{
    char tmp;
    for(int i=0;i<len/2;i++){
        tmp = s[i];
        s[i] = s[len-1-i];
        s[len-1-i]=tmp;
    }
}

char s[1000];
int main()
{
    int len=0;
    char c;
    while((c=getchar())!=EOF&&c!='\n')
        s[len++]=c;
    Reverse(s,len);
    for(int i=0;i<len;i++)
        printf("%c",s[i]);
    return 0;
}