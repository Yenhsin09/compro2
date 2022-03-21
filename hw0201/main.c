#include "mymatch.h"
#include "mysplit.h"

int main()
{
    char **pplist;
    const char str[100]=" kkel lessssss";
    const char pttern[100]="?e*";
    int ans = mymatch(&pplist,str,pttern);
    //printf("%s\n",*pplist);
    if(ans==-1)
    {
        printf("invalid value!\n");
    }
    else
    {
        printf("number of matching words: %d\n",ans);
    }
    
}
