#include <stdio.h>
#include <string.h>

//暴力法
//按长度从0到len/2遍历
char s[200];
char t[200];
int main()
{
    scanf("%s",s);
    int total = strlen(s);
    int len=0;
    int locate;
    char * p;
    for(int i=0;i<=total/2;i++){
        for(int head=0;head+i<total;head++){
            memcpy(t,s+head,i);
            if((p = strstr(s+head+i,t))!=NULL){
                len = i;
                locate = head;
                break;
            }
        }
    }
    if(len>0){
        for(int i=0;i<len;i++){
            printf("%c",*(s+locate+i));
        }
        printf(" %d",locate);
    }
    else 
        printf("-1");
    return 0;

}