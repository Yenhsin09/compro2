#include "mysplit.h"

int find(const char *pStr, const char * pSeparator)
{
    int i=0;
    int j=0;
    int found=0;
    int cut_num=0;
    const char *p = pStr;
    const char *cut = pSeparator;
    while(*(p+i)!='\0')
    {
        if(*(p+i)==*cut)
        {
            found = 1;
            for(j=0;*(cut+j)!='\0';j++)
            {
                if(*(p+i+j)!=*(cut+j))
                {
                    found=-1;
                    p=p+j;
                    break;
                }
            }
            if(found==1)
            {
                p=p+j;
                cut_num++;
            }
        }
        i++;
    }
    return cut_num+1;
}

char *cut(const char *pStr, const char * pSeparator,char *store)
{
    int j=0;
    int found=0;
    char *p = (char*) pStr;
    const char *cut = pSeparator;
    for(int i=0;*(p+i)!='\0';i++)
    {
        if(*(p+i)==*cut)
        {
            found = 1;
            for(j=0;*(cut+j)!='\0';j++)
            {
                if(*(p+i+j)!=*(cut+j))
                {
                    found=-1;
                    break;
                }
            }

            if(found==1)
            {
                store=malloc(sizeof(char)*i+1);
                strncpy(store,pStr,i);
                *(store+i+1)='\0';
                return store;
            }
        }
    }
    return NULL;
}

int mystrsplit(char ***ppList, int *pCounter, const char *pStr, const char * pSeparator)
{

    if(strlen(pStr)==0||pSeparator==NULL||strlen(pSeparator)==0)
    {
        return -1;
    }
    int pcounter = find(pStr,pSeparator);
    char **tmp;
    char *pstr= (char *) pStr;
    char *store = NULL;
    char *cutstr;

    *pCounter = pcounter;
    *ppList = malloc(sizeof(char*)*pcounter);
    for(int i=0;i<pcounter;i++)
    {
        if(pcounter==1) //沒東西可以切
        {
            *(*ppList)= (char*)pStr;
            return 0;
        }
        if(i==0)
        {
            cutstr = cut(pstr,pSeparator,store);
            *(*ppList+i)=cutstr;
            pstr=pstr+strlen(cutstr)+strlen(pSeparator);
        }
        else if(i==pcounter-1)
        {
            *(*ppList+i)=pstr;
            break;
        }
        else
        {
            cutstr=cut(pstr,pSeparator,store);
            *(*ppList+i)=cutstr;
            pstr=pstr+strlen(cutstr)+strlen(pSeparator);
        }
        
    }
    return 0;
}
