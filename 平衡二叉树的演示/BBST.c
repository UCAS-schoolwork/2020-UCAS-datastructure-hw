#include <stdio.h>
#include <stdlib.h>

typedef enum{False, True} Status;
typedef int ElemType;

typedef struct BINNODE{
    int height; //树的高度
    int succ; //中序遍历下的下一个节点的编号
    ElemType data;
    struct BINNODE *parent, *lchild, *rchild;
} BinNode;//二叉树结点

typedef struct{
    int size;
    BinNode * root;
} BinTree;//二叉树


typedef BinNode LinkType;
typedef struct LNODE{
    LinkType data;
    struct LNODE * next, * front;
}LNode;
typedef struct{
    LNode * head, *tail;
}Quene;

Quene * Quene_Init()
{
    Quene * Q = (Quene *)malloc(sizeof(Quene));
    if(!Q)
        return NULL;
    Q->head = Q->tail = NULL;
    return Q;
}

Status Quene_In(Quene * Q, LinkType e)
{
    LNode * p = (LNode *)malloc(sizeof(LNode));
    p->data = e;
    p->front = NULL;
    if(Q->head)
        Q->head->front = p;
    else 
        Q->tail = p;
    p->next = Q->head;
    Q->head = p;
    return True;
}

Status Quene_isEmpty(Quene * Q)
{
    if(Q->head && Q->tail)
        return False;
    return True;
}
Status Quene_Out(Quene * Q, LinkType * e)
{
    LNode * q = Q->tail;
    if(!q)
        return False;
    LNode * p = q->front;
    *e = q->data;
    if(p)
        p->next = NULL;
    else 
        Q->head = NULL;
    Q->tail = p;
    free(q);
    return True;
}
Status Queue_Destroy(Quene * Q)
{
    LNode * p = Q->head;
    while(p&&p->next){
        p = p->next;
        free(p->front);
    }
    free(p);
    free(Q);
    return True;
}

int Max(int a, int b)
{
    return a>b?a:b;
}
BinNode * hot;//用于指示查找结点的父节点
BinNode * BST_SearchIn(BinNode * v, ElemType e)
{
    if(!v||e==v->data)
        return v;
    hot = v;
    return BST_SearchIn(e<v->data?v->lchild:v->rchild,e);
}
//在T中查找e，返回找到的结点，并更新hot。
BinNode * BST_Search(BinTree * T, ElemType e)
{
    hot = NULL;
    return BST_SearchIn(T->root, e);
}

#define GetHeight(v) ((v)?(v)->height:-1)
//更新结点v的高度
int UpdateHeight(BinNode * v)
{
    if(!v)
        return -1;
    v->height = 1 + Max(GetHeight(v->lchild),GetHeight(v->rchild));
    return v->height;
}
//更新结点v及其祖先的高度
void UpdateHeightAbove(BinNode * v)
{
    BinNode * w = v;
    while(v){
        int origin = v->height;
        UpdateHeight(v);
        if(w!=v && origin == UpdateHeight(v))
            break;
        v = v->parent;
    }
}
//在BST T中插入e，若成功返回True，若已存在则返回False
Status BST_Insert(BinTree * T, ElemType e)
{
    BinNode * v = BST_Search(T,e);
    if(v)
        return False;
    T->size++;
    v = (BinNode *)malloc(sizeof(BinNode));
    v->data = e;
    v->lchild = v->rchild = NULL;
    if(!hot){
        T->root = v;
        v->parent = NULL;
    }
    else {
        v->parent = hot;
        if(e<hot->data)
            hot->lchild = v;
        else 
            hot->rchild = v;
    }
    UpdateHeightAbove(v);
    return True;
}
//判断v是否为左孩子
#define islchild(v) ((v)->parent&&(v)->parent->lchild == (v))
//返回v在中序遍历的下一个节点
BinNode * BST_succ(BinNode * v)
{
    if(!v)
        return NULL;
    BinNode * w = v->rchild;
    if(w){
        while(w->lchild)
            w = w->lchild;
    }
    else if(islchild(v))
        w = v->parent;
    else 
        w = NULL;
    return w;
}
void Swap(ElemType * a, ElemType * b)
{
    ElemType t = *a;
    *a = *b;
    *b = t;
}
void BST_RemoveAt(BinTree * T, BinNode * v)
{
    BinNode * w = v;
    BinNode * succ = NULL;
    if(!v->lchild)
        succ = v->rchild;
    else if(!v->rchild)
        succ = v->lchild;
    else {
        w = BST_succ(v);
        Swap(&v->data,&w->data);
        succ = w->rchild;
    }
    hot = w->parent;
    if(succ)
        succ->parent = hot;
    if(hot){
        if(hot->lchild == w)
            hot->lchild = succ;
        else 
            hot->rchild = succ;
    }
    else 
        T->root = succ;
    free(w);
}
//在T中删除结点e。成功返回True，否则返回False
Status BST_Remove(BinTree * T, ElemType e)
{
    BinNode * v = BST_Search(T,e);
    if(!v)
        return False;
    BST_RemoveAt(T,v);
    T->size--;
    UpdateHeightAbove(hot);
    return True;
}

//创建新排序树并返回，失败返回NULL。
BinTree * BST_Init()
{
    BinTree * T = (BinTree *)malloc(sizeof(BinTree));
    if(!T)
        return NULL;
    T->size = 0;
    T->root = NULL;
    return T;
}
void BST_DestroyNode(BinNode * v)
{
    if(!v) return;
    if(v->lchild)
        BST_DestroyNode(v->lchild);
    if(v->rchild)
        BST_DestroyNode(v->rchild);
    free(v);
}
Status BST_Destroy(BinTree * T)
{
    if(!T) return False;
    BST_DestroyNode(T->root);
    free(T);
    return True;
}
void BST_PrintIn(BinNode * v)
{ //从节点v开始打印
    int succ = 0;
    int nexte = v->data;
    int renew = 0;
    Quene * Q = Quene_Init();
    Quene_In(Q,*v);
    BinNode w;
    while(!Quene_isEmpty(Q)){
        Quene_Out(Q,&w);
        if(w.data == nexte&&nexte!=v->data){//开启下一行
            printf("\n");
          
            succ = 0;
            renew = 0;
        }
        for(;succ<w.succ;succ++)
            printf("   ");
        printf("%3d",w.data);
        succ++;
        if(w.lchild){
            Quene_In(Q,*w.lchild);
            if(!renew) nexte = w.lchild->data;
            renew = 1;
        }
        if(w.rchild){
            Quene_In(Q,*w.rchild);
            if(!renew) nexte = w.rchild->data;
            renew = 1;
        }
    }
    Queue_Destroy(Q);
}
int _succ_inorder;
void BST_TravelInOrder(BinNode * v)
{
    if(!v) return;
    BST_TravelInOrder(v->lchild);
    v->succ = _succ_inorder++;
    BST_TravelInOrder(v->rchild);
}
void BST_Print(BinTree * T)
{
    if(!T||!T->root)
        printf("Empty Tree.\n");
    else {
        _succ_inorder = 0; //记录中序遍历次序
        BST_TravelInOrder(T->root);//计算打印前的空格
        BST_PrintIn(T->root);
        printf("\n");
    }
}

//BBST
//计算平衡因子
#define BalanceFac(v) (GetHeight((v)->lchild) - GetHeight((v)->rchild))
//判断是否平衡
#define isBalance(v) ((-2<BalanceFac(v))&&(BalanceFac(v))<2)

BinNode * BBST_Connect34(BinNode *a,BinNode *b,BinNode *c,
    BinNode *T0,BinNode *T1,BinNode *T2,BinNode *T3)
{//将待调整的3个结点、四颗子树拆开，按中间节点在最上的顺序重组即可。
    a->lchild = T0; if(T0) T0->parent = a;
    a->rchild = T1; if(T1) T1->parent = a; UpdateHeight(a);
    c->lchild = T2; if(T2) T2->parent = c;
    c->rchild = T3; if(T3) T3->parent = c; UpdateHeight(c);
    b->lchild = a; a->parent = b;
    b->rchild = c; c->parent = b; UpdateHeight(b);
    return b;
}

void BBST_RotateAt(BinTree * T,BinNode * v)
{   //将失衡结点旋转为平衡，其中失衡结点为孙子
    BinNode * p = v->parent;
    BinNode * g = p->parent;
    BinNode * r = g->parent;//需要考虑祖父结点为根节点的情况，可能要调整根节点指针
    if(islchild(p)){ //zig
        if(islchild(v)){ //zig-zig
            p->parent = r;
            if(r&&islchild(g)) r->lchild = p;
            else if(r) r->rchild = p;
            else T->root = p;
            BBST_Connect34(v,p,g,v->lchild,v->rchild,p->rchild,g->rchild);
        }
        else{ //zig-zag
            v->parent = r;
            if(r&&islchild(g)) r->lchild = v;
            else if(r) r->rchild = v;
            else T->root = v;
            BBST_Connect34(p,v,g,p->lchild,v->lchild,v->rchild,g->rchild);
        }
    }
    else{
        if(islchild(v)){ //zag-zig
            v->parent = r;
            if(r&&islchild(g)) r->lchild = v;
            else if(r) r->rchild = v;
            else T->root = v;
            BBST_Connect34(g,v,p,g->lchild,v->lchild,v->rchild,p->rchild);
        }
        else{ //zag-zag
            p->parent = r;
            if(r&&islchild(g)) r->lchild = p;
            else if(r) r->rchild = p;
            else T->root = p;
            BBST_Connect34(g,p,v,g->lchild,p->lchild,v->lchild,v->rchild);
        }
    }
}

Status BBST_Insert(BinTree * T, ElemType e)
{
    if(BST_Insert(T,e)==False) 
        return False;
    if(!hot) 
        return True;
    BinNode * v = hot->lchild && hot->lchild->data == e?hot->lchild:hot->rchild;
    BinNode * g = hot->parent;
    if(!g) 
        return True;
    for(;g;g=g->parent){
        if(!isBalance(g)){
            BBST_RotateAt(T,v);
            break; //插入只需调整一次
        }
        else
            v = v->parent;   
    }
    return True;
}
//计算高度较大的孩子
#define tallerchild(v) (GetHeight((v)->lchild)>GetHeight((v)->rchild)?(v)->lchild:(v)->rchild)
Status BBST_Remove(BinTree * T, ElemType e)
{//BBST的删除主函数
    BinNode * v = BST_Search(T,e);
    if(!v) return False;
    BST_RemoveAt(T,v);
    //BST_Print(T);
    T->size--;
    for(BinNode * g = hot;g;){
        if(!isBalance(g)){
            BinNode * r = g->parent;
            BBST_RotateAt(T,tallerchild(tallerchild(g)));
            g = r;//删除需要一直向上追溯。
        }
        else{
            UpdateHeight(g);
            g=g->parent;
        }
    }
    //BST_Print(T);
    return True;
}
//Merge T2 to T1
void BBST_MergeNode(BinTree * T, BinNode * v)
{
    if(!v) return;
    BBST_Insert(T,v->data);
    BBST_MergeNode(T,v->lchild);
    BBST_MergeNode(T,v->rchild);
}
Status BBST_Merge(BinTree * T1, BinTree * T2)
{
    if(!T2||!T1)
        return False;
    BBST_MergeNode(T1,T2->root);
    BST_Destroy(T2);
    return True;
}
//Separate T1 to T2 and T3
void BBST_SeparateIn(BinNode * v, BinTree *T2, BinTree * T3, ElemType e)
{
    if(!v) return;
    BBST_SeparateIn(v->lchild,T2,T3,e);
    if(v->data<=e)
        BBST_Insert(T2,v->data);
    else 
        BBST_Insert(T3,v->data);
    BBST_SeparateIn(v->rchild,T2,T3,e);
}
Status BBST_Separate(BinTree * T1, BinTree * T2, BinTree * T3,ElemType e)
{
    if(!T1||!T2||!T3)
        return False;
    BST_DestroyNode(T2->root);
    T2->root = NULL;
    BST_DestroyNode(T3->root);
    T3->root = NULL;
    BBST_SeparateIn(T1->root, T2, T3,e);
    BST_Destroy(T1);
    return True;
}

#define MAXTREE 1000
BinTree * TreeSet[MAXTREE];
int isOutRange(int i)
{
    return i<0||i>=MAXTREE;
}

int main()
{
    //交互界面
    printf("Welcome to BBST demo. Please create a BBST first(0-%d).\nRefer to manual if you are confused.\n",MAXTREE-1);
    char c;
    int dat;
    while((c=getchar())!=EOF&&c!='q'){
        if(c=='c'){
            while(scanf("%d",&dat)==1){
                if(isOutRange(dat)){
                    printf("Enter proper number(0-%d)\n",MAXTREE-1);
                    break;
                }
                else if(TreeSet[dat]){
                    printf("No.%d BBST has existed.\n",dat);
                    break;
                }
                BinTree * T = BST_Init();
                TreeSet[dat] = T;
                printf("No.%d BBST has been created successfully.\n",dat);
            }
        }
        else if(c=='i'){
            int num;
            scanf("%d",&num);
            if(isOutRange(num)||!TreeSet[num]){
                printf("No.%d BBST does not exist.\n",num);
                continue;
            }
            while(scanf("%d",&dat)==1){
                if(BBST_Insert(TreeSet[num],dat)==False)
                    printf("%d does exist in No.%d BBST.\n",dat,num);
                else{
                    BST_Print(TreeSet[num]);
                    printf("Insert %d to No.%d BBST successfully.\n",dat,num);
                }
            }
        }
        else if(c=='f'){
            int num;
            scanf("%d",&num);
            if(isOutRange(num)||!TreeSet[num]){
                printf("No.%d BBST does not exist.\n",num);
                continue;
            }
            while(scanf("%d",&dat)==1){
                BinNode * v = BST_Search(TreeSet[num],dat);
                if(!v)
                    printf("%d does not exist in No.%d BBST.\n",dat,num);
                else{
                    printf("%d is found in No.%d BBST.\n",dat,num);
                }
            }
        }
        else if(c=='r'){
            int num;
            scanf("%d",&num);
            if(isOutRange(num)||!TreeSet[num]){
                printf("No.%d BBST does not exist.\n",num);
                continue;
            }
            while(scanf("%d",&dat)==1){
                if(BBST_Remove(TreeSet[num],dat)==False)
                    printf("%d has not found in No.%d BBST.\n",dat,num);
                else {
                    BST_Print(TreeSet[num]);
                    printf("Remove %d in No.%d BBST successfully.\n",dat,num);
                }
            }
        }
        else if(c=='d'){
            while(scanf("%d",&dat)==1){
                if(isOutRange(dat)||!TreeSet[dat]){
                    printf("No.%d BBST does not exist.\n",dat);
                    break;
                }
                BST_Destroy(TreeSet[dat]);
                TreeSet[dat] = NULL;
                printf("No.%d BBST has been destroyed successfully.\n",dat);
            }
        }
        else if(c=='m'){
            int t1,t2;
            scanf("%d%d",&t1,&t2);
            if(isOutRange(t1)||isOutRange(t2)||!TreeSet[t1]||!TreeSet[t2]){
                printf("Target does not exist\n");
                continue;
            }
            else{
                BBST_Merge(TreeSet[t1],TreeSet[t2]);
                TreeSet[t2] = NULL;
                BST_Print(TreeSet[t1]);
                printf("No.%d BBST has merged to No.%d successfully.\n",t2,t1);
            }
        }
        else if(c=='s'){
            int t1,t2,t3,e;
            scanf("%d%d%d%d",&t1,&t2,&t3,&e);
            if(isOutRange(t1)||isOutRange(t2)||isOutRange(t3)||!TreeSet[t1]){
                printf("Target does not exist\n");
                continue;
            }
            if(!TreeSet[t3])
                TreeSet[t3] = BST_Init();
            if(!TreeSet[t2])
                TreeSet[t2] = BST_Init();
            BBST_Separate(TreeSet[t1],TreeSet[t2],TreeSet[t3],e);
            TreeSet[t1] = NULL;
            printf("Separate No.%d BBST to No.%d and No.%d by %d successfully.\n",t1,t2,t3,e);
        }
        else if(c=='p'){
            scanf("%d",&dat);
            if(isOutRange(dat)||!TreeSet[dat])
                printf("Target does not exist.\n");
            else{
                BST_Print(TreeSet[dat]);
                printf("No.%d BBST is printed successfully.\n",dat);
            }
        }
    }
    return 0;
}