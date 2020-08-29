#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

//为节约空间，以一维动态结构存储m维数组

int power[10];
int main()
{
    int m,n;
    int ix=0;
    char c;
    scanf("%d%c",&m,&c);
    scanf("%d%c",&n,&c);
    for(int i=0;i<m;i++)
        power[i] = n-1;
    int *s = (int *)malloc(sizeof(int)*pow(n,m));
    if(!s){
        printf("Wrong.");
        return 0;
    }
    //Input
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
    //Output by term
    int first=1;
    for(int i=ix-1;i>=0;i--){
        
        if(s[i]>0){
            if(!first)
                printf("+");   
        }
        else if(s[i]==0)
            goto JUMP;  
        else 
            printf("-");
        if(s[i]!=1 || i==0)
            printf("%d",s[i]);

        for(int j=0;j<m;j++){
            if(power[j]==0)
                continue;
            else if(power[j]==1)
                printf("x%d",j+1);
            else 
                printf("x%dE%d",j+1,power[j]);
        }
JUMP:
        for(int k=m-1;k>=0;k--){
            if(power[k]>0){
                power[k]--;
                for(int l=k+1;l<m;l++)
                    power[l]=n-1;
                break;
            }
        }
        first=0;
    }
 
    return 0;
}
