#include <stdio.h>

#define MAXINT 0x1ffff
#define MAX 0x20000

int s[300];

//residue class ring by mod MAXINT

int main()
{
    s[0]=1;
    int c;
  
    scanf("%d",&c);
   
    if(c>300 ||c<=0){
        printf("%d",-1);
        return 0;
    }

    else
        for(int i=1;i<c;i++){
            s[i]=s[i-1]*i*2;
            s[i]&=MAXINT;
            if(s[i]>>16==1)
                s[i] -= MAX;
        }
    int max=0;
    for(int i=0;i<c;i++)
        if(s[i]>max)
            max=s[i];
    
    printf("%d",max);
    return 0;
}