#include <stdio.h>
#include <stdlib.h>
#define MAXROW 200
#define MAXCOL 200

int A[MAXROW][MAXCOL];
int Saddle[MAXROW];

int cmp (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

int main()
{
    char c;
    int dat;
    int m=0;
    int n=0;
    int nj=0;
    int num=0;
    while(scanf("%d%c",&dat,&c)==2){
        A[m][nj++] = dat;
        if(c==';'||c==EOF||c=='\n'){
            m++;
            n=nj;
            nj=0;
        }
    }
    int maxval;
    int rowloc=0;
 
    for(int i=0;i<m;i++){
        maxval = A[i][0];
        for(int j=0;j<n;j++){
            if(A[i][j]<maxval){
                maxval = A[i][j];
                rowloc = j;
            }
        }
      
        
        for(int j=0;j<n;j++){
            if(A[i][j]==maxval){
                rowloc = j;
                int yes=1;
                for(int k=0;k<m;k++){
                    if(A[k][rowloc]>maxval){
                        yes=0;
                        break;
                    }
                }
                if(yes)
                    Saddle[num++] = maxval;
            }
        }
        
    }
    if(num){
        qsort(Saddle,num,sizeof(int),cmp);
        for(int i=0;i<num;i++)
            printf("%d%c",Saddle[i],i==num-1?'\n':',');
    }
    else 
        printf("null");


    return 0;

}