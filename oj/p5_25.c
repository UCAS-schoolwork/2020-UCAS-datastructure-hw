#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    int row,col;
    int ax=0;
    int vx=0;
    char c;
    scanf("%d%c",&row,&c);
    scanf("%d%c",&col,&c);

    size_t tsize = sizeof(int)*row*col;
    int *A = (int *)malloc(tsize);
    char *V = (char *)malloc(tsize);
    
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
            if(sum){
                A[ax++] = sum;
                V[vx++] = 1;
            }
            else 
                V[vx++] = 0;
        }
    }
    //Output
    if(!ax)
        printf("[");
    for(int i=0;i<ax;i++)
        printf("%c%d",!i?'[':',',A[i]);
    printf("];[");
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%c%d",!j?'[':',',V[i*col+j]);
        }
        if(i!=row-1)
            printf("];");
        else 
            printf("]]");
    }
    return 0;

}