//边界标志+首次适配

#include <stdio.h>
#include <stdlib.h>
typedef struct WORD{
    int tag; //1:allocated; 0:vice versa
    int size;
    union{
        struct WORD *llink;
        struct WORD *uplink;
    };
    struct WORD *rlink;
}Word,Space;

#define FootLoc(p) (p+p->size-1)
Space *pav;
const int minsize = 16;
Space * AllocBound(int n)
{
    Space *p;
    for(p=pav;p&&p->size<n&&p->rlink!=pav;p->rlink)
        ;
    if(!p||p->size<n)
        return NULL;
    else{
        Space * f = FootLoc(p);
        pav = p->rlink;
        if(p->size-n<=minsize){
            if(pav==p)
                pav = NULL;
            else{ // release p
                pav->llink = p->llink;
                p->llink -> rlink = pav;
            }
            p->tag = f->tag = 1;
        }
        else{
            f->tag = 1;
            p->size -= n;
            f = FootLoc(p);
            f->tag = 0;
            f->uplink = p;
            p = f+1;
            p->tag = 1;
            p->size = n;
        }
    }
    return p;
}

int FreeBound(Space *p)
{
    if((p-1)->tag == 1){
        if((p+p->size)->tag == 1){
            p->tag = 0;
            FootLoc(p)->uplink = p;
            FootLoc(p)->tag = 0;
            if(!pav)
                pav = p->llink = p->rlink = p;
            else{
                Space *q = pav->llink;
                p->rlink = pav;
                p->llink = q;
                q->rlink = pav->llink = p;
                pav = p;
            }
        }
        else{
            Space *t = FootLoc(p)+1;
            p->tag = 0;
            Space *q = t->llink;
            p->llink = q;
            q->rlink = p;
            Space *q1 = t->rlink;
            p->rlink = q1;
            q1->llink = p;
            p->size +=t->size;
            FootLoc(t)->uplink = p;
        }
    }
    else{
        if((p+p->size)->tag==1){
            Space *f = FootLoc(p);
            f->uplink = (p-1)->uplink;
            f->tag = 0;
            (p-1)->uplink->size+=p->size;
        }
        else{
            int n = p->size;
            Space *s = (p-1)->uplink;
            Space *t = FootLoc(p)+1;
            s->size += n+t->size;
            Space *q = t->llink; 
            Space *q1 = t->rlink;
            q->rlink = q1;
            q1->llink = q;
            FootLoc(t)->uplink = s;
        }
    }
    return 1;
}

Space * InitBound(int n)
{
    Space *p = (Space *)malloc(n);
    return p;
}

int main()
{
    
    return 0;
}