#include <stdio.h>
#include <ctype.h>

int s[10000];
//UTF-8
//binary search
//手撸了一个atoi
//要求顺序表，只能一个一个移了
int main()
{
    char c;
    int ix=0;
    while((c=getchar())!=EOF)
    {
        int sum=0;
        int sign=0;
        if(c=='-'){
            sign = 1;
            goto MINUS;
        }
        if(isdigit(c)){
            sum = c-'0';
MINUS:
            while (isdigit(c=getchar())){
                sum*=10;
                sum+=c-'0';
            }
            if(sign)
                sum=-sum;
            s[ix++] = sum;
        }
        
    }
    int ins=s[--ix];
    int up = ix-1;
    int down = 0;
    int mi = ix/2;
    while(down<mi&&mi<up){
        if(s[mi]>ins)
            up = mi;
        else if(s[mi]<ins)
            down = mi;
        else
            break;
        mi = (down+(up-down)/2);
    }
    mi++;
    if(mi==ix-1)
        ;
    else{
        for(int j=ix-1;j>=mi;j--)
            s[j+1] = s[j];
        s[mi] = ins;
    }
    for(int j=0;j<=ix;j++)
        printf("%d%c",s[j],j==ix?'\n':' ');
    
    return 0;

}