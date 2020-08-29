#include <stdio.h>
//Just compare one by one 
int mystrcmp(char *s,char *t)
{
    while(*s++==*t++&&*s!=0)
        ;
    if(*--s>*--t)
        return 1;
    else if(*s<*t)
        return -1;
    return 0;
}

char s[1000];
char t[1000];
int main()
{
    scanf("%s%s",s,t);
    printf("%d",mystrcmp(s,t));
    return 0;
}