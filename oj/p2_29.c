#include<stdio.h>
#include<stdlib.h>

char a[1000];
char b[1000];
char c[1000];

int main()
{
    //用顺序表即数组比较快
    //找到先占位，最后一起删除，只要删一次，总复杂度O(n)
    int len1,len2,len3;
    len1=len2=len3=0;
    char ch;
    while(scanf("%c%c",a+len1++,&ch)==2)
        if(ch==';')
            break;
    while(scanf("%c%c",b+len2++,&ch)==2)
        if(ch==';')
            break;
            
    while(scanf("%c%c",c+len3++,&ch)==2)
        ;
    int del=0;
    int i1,i2,i3;
    int find;
    for(i1=0;i1<len1;i1++){
        find=0;
        for(i2=0;i2<len2&&!find;i2++){
            if(b[i2]==a[i1]){
                for(i3=0;i3<len3&&!find;i3++){
                    if(c[i3]==a[i1])
                        find=1;
                    else if(c[i3]>a[i1])
                        break;
                }
            }
            else if(b[i2]>a[i1])
                break;
        }
        if(find){
            a[i1]=0;
            del++;
        }
    }

    for(i1=0,i2=0;i1<len1;i1++){
        if(!a[i1]){
            if(i2<i1)
                i2=i1;
            for(;!a[i2]&&i2<len1;i2++)
                ;
            if(i2<len1){
                a[i1]=a[i2];
                a[i2]=0;
            }
        }
    }
    len1-=del;
    //删除后a表长即为len1
    for(i1=0;i1<len1;i1++)
        printf("%c%c",a[i1],i1==len1-1?'\n':',');

    return 0;
}