#include <stdio.h>
#include<stdlib.h>
#include <string.h>
int s[5][3];
char line[100];

int getline(void)
{
    char c;
    int i = 0;
    while((c=getchar())!='\n'&&c!=EOF){
        line[i++] = c;
    }
    if(c==EOF)
        return 1;
    return 0;
}
//Pay attention to the format
int main()
{
    int gender;
    int score;
    int c;
    while(1){
        memset(line,0,sizeof(line));
        c = getline();
        score = atoi(line+6);
        gender = line[2]=='M'?0:1;
        if(line[4]>='A')
            s[line[4]-'A'][gender] += score;
        if(c==1)
            break;
    }
    for(int i=0;i<5;i++)
        s[i][2] = s[i][0]+s[i][1];
    
    for(int i=0;i<5;i++){
        if(s[i][0]!=0)
            printf("%c %c %d\n",i+'A','M',s[i][0]);
        if(s[i][1]!=0)
            printf("%c %c %d\n",i+'A','F',s[i][1]);
        if(s[i][2]!=0)
            printf("%c %d\n",i+'A',s[i][2]);
    }
    return 0;

}