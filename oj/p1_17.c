#include <stdio.h>
#define MAX 100000
int s[MAX];
int main()
{
    //Avoid recursion
    int k, m;
    scanf("%d%d", &k, &m);
    int i;
    s[k - 1] = 1;
    for (i = k; i <= m; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            s[i] += s[i - j];
        }
    }
    printf("%d",s[m]);
    return 0;
}