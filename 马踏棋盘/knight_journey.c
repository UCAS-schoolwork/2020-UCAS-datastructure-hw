#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define Initsize 10000 //栈容量，必须大于4096
#define SIZE 8 //棋盘宽度，可调节
#define True 1
#define False 0
typedef struct pos{
    char x;//坐标x
    char y;//坐标y
    char dir;//当前棋子到下一个棋子的方向
    char cnt;//当前棋子的最佳路径数
    char seq[8];//当前棋子最佳路径的顺序
}Pos; //棋子类型定义

typedef char Status;
typedef Pos ElemType;

typedef struct SqStack{
    int sp; //栈指针
    int stacksize;//栈当前的最大容量
    ElemType * base; //栈底指针
}Stack;

Stack * InitStack(void)
{
    Stack *S;
    S = (Stack *)malloc(sizeof(Stack));
    if(!S)  
        return NULL;
    S->base = (ElemType*)malloc(Initsize*sizeof(ElemType));
    if(!S->base)  
        return NULL;
    S->sp = 0;
    S->stacksize = Initsize;
    return S;
}

Status GetTop(Stack *S,ElemType *e)
{
    if(S->sp<=0)
        return False;
    *e = S->base[S->sp-1];
    return True;
}

Status Push(Stack *S,ElemType e)
{
    S->base[S->sp++] = e;
    return True;
}

Status Pop(Stack *S, ElemType *e)
{
    *e = S->base[--S->sp];
    return True;
}

typedef unsigned char Board[SIZE][SIZE];//棋盘类型定义
Board board;
Pos pos;
int backcnt; //当前路径回撤数
int totalback; //当前起始位置回撤总数
int step;
int maxstep = SIZE*SIZE;
#define MAXHISTORY 1000000 //存储的最多路径数
Board history[MAXHISTORY];
int backtrace[MAXHISTORY];
int history_cnt;
const char way_y[8] = {-1,-2,1,2,1,2,-1,-2};
const char way_x[8] = {2,1,2,1,-2,-1,-2,-1}; //回撤少
//const char way_y[8] = {-1,-2,1,2,2,1,-1,-2};
//const char way_x[8] = {2,1,2,1,-1,-2,-2,-1}; //书本上的

void display(void)
{//打印当前棋盘，用于演示回撤
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(!board[i][j])
                printf("__");
            else{ 
                if(SIZE<=9)
                    printf("%02d",board[i][j]);
                else 
                    printf("%03d",board[i][j]);
            }
            printf("%c",j==SIZE-1?'\n':' ');
        }
    }
    printf("\n");
}
void displayBoard(int cnt)
{//打印历史棋盘
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(cnt==-1||cnt>=history_cnt)
                if(SIZE<=9)
                    printf("__");
                else 
                    printf("___");
            else{
                if(SIZE<=9)
                    printf("%02d",history[cnt][i][j]);
                else {
                    if(SIZE==16&&history[cnt][i][j]==0)
                        printf("256");
                    else 
                        printf("%03d",history[cnt][i][j]);
                }
            }
            printf("%c",j==SIZE-1?'\n':' ');
        }
    }
    if(cnt>=0)
        printf("traceback_number:%d\n",backtrace[cnt]);
}

inline void Undo(Stack * S)
{   //  回撤一步
    board[pos.y][pos.x] = 0;
    Pop(S,&pos);
}

Status isnOut(int i)
{//判断跳跃是否越界
    return i>=0 && i<SIZE;
}

Status leap(Stack * S)
{   //马跳一步
    char dir = pos.seq[pos.dir];
    if(dir>7)
        return False;
    char nextx = pos.x + way_x[dir];
    char nexty = pos.y + way_y[dir];
    if(!isnOut(nextx)||!isnOut(nexty)||board[nexty][nextx]>0)
        return False;
    Push(S,pos);
    pos.x = nextx;
    pos.y = nexty;
    pos.dir = 0;
    board[nexty][nextx] = S->sp;
    //displayBoard();
    return True;
}

void SortSeq(Stack * S)
{//对下一步的方向进行排序
    int num[8] = {0};//初始化下一步可行动点数组。
    for(int i=0;i<8;i++){
        pos.seq[i] = i;
        pos.dir = i;
        if(leap(S)==False){//按自然顺序进行跳跃。若无法跳跃，可行动点设为9（越界值）
            num[i] = 9;
            continue;
        }
        for(int j=0;j<8;j++){
            char nextx = pos.x + way_x[j];
            char nexty = pos.y + way_y[j];
            if(isnOut(nextx)&&isnOut(nexty)&&board[nexty][nextx]==0)
                num[i]++; //计算下一步的可行动点数
        }
        if(!num[i] && S->sp<maxstep)
            num[i] = 9; //若下一步可行动点数为0，把他设为9，方便排序。
        Undo(S); //返回这一步。
    }
    pos.dir = 0;//初始化方向
    pos.cnt = 0;//初始化最佳步数个数
    int min0;
    for(int i=0;i<8;i++){
        int min = 9;
        int tar = 0;
        for(int j=0;j<8;j++){
            if(num[j]<min){
                min = num[j];
                tar = j;
            }
        }//采用稳定的选择排序
        num[tar] = 10;
        if(!i)
            min0=min;
        if(min==9)
            tar = 0xf;//此路不通
        pos.seq[i] = tar;
        if(min == min0 && min<9)
            pos.cnt++;//当前最佳路径加1
    }
}

int Search(Stack * S)
{
Again:
    while(S->sp>=step && S->sp<maxstep){
        if(!pos.dir) 
            SortSeq(S);//首次经过先排序
        else if(pos.cnt>=0 && pos.dir>=pos.cnt){   
            Undo(S);//方向走完就回撤
            backcnt++;
            if(totalback+backcnt>600000)//回撤过多就返回
                return history_cnt;
            pos.dir++;
            continue;
        }
        if(!leap(S)){//前有路径就跳跃
            pos.dir++;
            continue;
        }
    }
    if(S->sp<step)//回到原点就完成
        return history_cnt;
    else {
        if(history_cnt>=MAXHISTORY)
            return history_cnt;//超过容量也返回
        
        memcpy(history[history_cnt],board,sizeof(board));//复制成功的棋盘
        backtrace[history_cnt] = backcnt;
        if(backcnt!=0)
            totalback++;
        history_cnt++;
        totalback += backcnt;//更新总回撤数
        backcnt = 0;//初始化当前走法回撤数
        do{
            Undo(S);
            pos.dir++;
        }while(S->sp>=step&&pos.cnt<=pos.dir);//回撤到上一个分歧点
     
        goto Again;//搜索下一条路径
    }
}

void Init(Stack *S)
{//初始化栈
    S->sp=0;
    memset(board,0,sizeof(board));
    backcnt = totalback =  0;
    step = 1;
    history_cnt = 0;
}


int main()
{//用户界面
    int x,y,cnt;
    Stack * S = InitStack();
    clock_t clockstart, clockend;
	printf("Welcome to Knight's journey DEMO.\n");
    while(1){
        Init(S);
        displayBoard(-1);//打印空棋盘
        printf("Please enter the initial position(1-%d 1-%d):\n",SIZE,SIZE);
        printf("For example:\"1 1\"\n");
        scanf("%d%d",&x,&y);//读入初始位置
        if(isnOut(--x)&&isnOut(--y)){
            pos.y=y;
            pos.x=x;
            pos.dir=0;
            board[y][x]=1;
            Push(S,pos);//进行第一步落子
            clockstart = clock();//统计运行时间
            Search(S);
            clockend = clock();
            printf("%d paths found,enter a path number to view(0-%d)\nEnter -1 to rechoose initial position\n",history_cnt,history_cnt-1);
            printf("TIME:%.2fs\n", (double)(clockend - clockstart) / CLOCKS_PER_SEC);
            while(scanf("%d",&cnt)==1){
                if(cnt==-1)
                    break;
                else if(cnt>=0&&cnt<history_cnt)
                    displayBoard(cnt);//根据输入号数打印对应的路径
                printf("Printed successfully.\n%d paths found,enter a path number to view(0-%d)\nEnter -1 to rechoose initial position\n",history_cnt,history_cnt-1);
            }
        }
        else
            printf("Invalid input.Input again.\n");
    }
    return 0;
}
