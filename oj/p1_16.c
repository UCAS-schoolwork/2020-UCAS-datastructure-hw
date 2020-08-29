#include <stdio.h>


void swp(int *a, int *b)
{
    int tmp=*a;
    *a=*b;
    *b=tmp;
}
//Compare * 3
int main()
{
    int a,b,c;
    scanf("%d%d%d",&a,&b,&c);
    if(a<b)
        swp(&a,&b);
    if(b<c)
        swp(&b,&c);
    else
        goto jump;
    if(a<b)
        swp(&a,&b);
    jump:
        ;
    printf("%d %d %d",a,b,c);
    return 0;
}