#include "mymatch.h"

int match(char *tmp,const char *pattern)
{
    int strnum=strlen(tmp);
    int patnum=strlen(pattern);
    //printf("strnum=%d\n",strnum);
    //printf("patnum=%d\n",patnum);
    if(patnum==0) return 0;
    
    int i=0,j=0,strptr = -1, patptr = -1;  //i:str   j:pat
    while(i<strnum)
    {
        if(tmp[i]==pattern[j])
        {
            i++;
            j++;
        }
        else if(j<patnum&&pattern[j]=='?')
        {
            i++;
            j++;
        }
        else if(j<patnum&&pattern[j]=='*')
        {
            strptr = i;
            patptr = j;
            j++;
        }
        else if(patptr!=-1)
        {
            j = patptr+1;
            i = strptr+1;
            strptr++;
        }
        else
        {
            return -1;
        }
    }
    
    while(j<patnum && pattern[j] =='*')
    {
        j++;
    }
    
    if(j==patnum)
    {
        return 0;
    }
    return -1;
}
void ck(char ***st,int *num,int storenum,int mark[storenum])
{
    int mk=0;
    for(int r=0;r<storenum;r++)
    {
        int k=0;
        mark[mk]=1;
        int len=strlen(*((*st)+r));
        if(len==0)
        {
            (*num)--;
            mark[mk++]=0;
            continue;
        }
        
        while( *(*((*st)+r)+k)!='\0' )
        {
            if( *(*((*st)+r)+k)<97 ||  *(*((*st)+r)+k)>122 )
            {
                (*num)--;
                mark[mk]=0;
                break;
            }
            else
            {
                k++;
            }
        }
        mk++;
    }
}
int mymatch(char ***pppList , const char *pStr, const char *pPattern)
{
    char **store;
    int store_num=0;
    int new_num=0;
    int mark[10000];
    
    if(strlen(pStr)==0 && strlen(pPattern)==0)
    {
        return -1;
    }
    int re = mystrsplit(&store,&store_num,pStr," ");
    if(re==-1) return -1;

    new_num=store_num;
    char *tmp;
    ck(&store,&new_num,store_num,mark);
    //printf("newnum=%d,storenum=%d\n",new_num,store_num);
    for(int i=0;i<store_num;i++)
    {
        printf("%d ",mark[i]);
    }
    for(int i=0;i<store_num;i++)
    {
        tmp=*(store+i);
        
        if(mark[i]==0)
        {
            continue;
        }
    
        int ret= match(tmp,pPattern);
        //printf("ret = %d\n",ret);
        if(ret==-1)
        {
            mark[i]=0;
            new_num--;
        }
    }
   
    int num=0;
    *pppList = malloc(sizeof(char(*)) * new_num);
    for(int i=0;i<store_num;i++)
    {
        tmp=*(store+i);
        if(mark[i]==1)
        {
            *((*pppList)+num) = tmp;
            num++;
        }
    }
    
    return new_num;
}
