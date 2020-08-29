#include <stdio.h>
//Replace recursion with loop
int f(int n)
{
    int sum = 1;
    for(;n>0;n/=2){
        sum*=n;
    }
    return sum;
}

int main()
{
    int n;
    scanf("%d",&n);
    printf("%d",f(n));
    return 0;
}