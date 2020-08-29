#include <stdio.h>

int g(int m,int n)
{
    if(m>0&&n>=0)
        return g(m-1,2*n)+n;
    else
        return 0;
}



int main()
{
    char c;
    int m,n;
    scanf("%d%c%d",&m,&c,&n);
    printf("%d",g(m,n));
    return 0;
}