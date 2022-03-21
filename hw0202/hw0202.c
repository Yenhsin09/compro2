#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

int sign(double input)
{
    if(input>=0) return 0;
    else return 1;
}

void detobi(int num,int arr[64],int i)
{
    int index = i-1;
    while(index >= 0)
    {
        arr[index] = num & 1;
        index--;
        num >>= 1;
    }
}

void point_bi(double pt,int arr[64],int i)
{
    int de=0;
    double p=0;
    double ans=0;
    for(int k=0;k<i;k++)
    {
        ans = pt*2;
        de = (int) ans;
        if(de==1)
        {
            p = ans - de;
        }
        else
        {
            p = ans;
        }
        
        arr[k] = de;
        pt = p;

        while(ans==1.0)
        {
            k++;
            arr[k]=0;
            if(k==63)
            {
                break;
            }
        }
    }
}
int findone(int arr[64],int i)
{
    int first=0;
    for(int k=0;k<i;k++)
    {
        if(arr[k]==1)
        {
            first = k+1;
            break;
        }
    }
    int num = i-first;
    return num;
}
int findpoint(int arr[64],int i)
{
    int first=0;
    for(int k=0;k<i;k++)
    {
        if(arr[k]==1)
        {
            first = (k+1)*(-1);
            break;
        }
    }

    return first;
}
void fraction(int to_bi1[64],int to_bi2[64],int ex,int fr[64],int num)
{
    int get=0;
    get=64-ex;
    int count=0;
    for(int k=get;k<64;k++)
    {
        fr[count++]=to_bi1[k];
    }
    int two=0;
    if(ex<0)
    {
        two = ex*(-1);
        for(int i=0;i<num;i++)
        {
        
            if(two<64)
            {
                fr[i]=to_bi2[two++];
            }
            else
            {
                fr[i]=0;
            }
        
        }
    }
    else
    {
        for(int i=ex;i<num;i++)
        {
        
            if(two<64)
            {
                fr[i]=to_bi2[two++];
            }
            else
            {
                fr[i]=0;
            }
        }
    }
    
}
void print_ans(double input,int frac[64],int exnum,int sign)
{
    int noprint=0;
    printf("%g = (-1)^%d * (",input,sign);
    if(input<1 && input>-1)
    {
        for(int i=0;i<52;i++)
        {
            if(frac[i]==1)
            {
                if(noprint==0)
                {
                    printf("2^-%d ",i+1);
                }
                else
                {
                    printf("+ 2^-%d ",i+1);
                }
                noprint++;
            }
        }
    }
    else
    {
        for(int i=0;i<52;i++)
        {
            if(frac[i]==1)
            {
                if(noprint==0)
                {
                    printf("1 + 2^-%d ",i+1);
                }
                else
                {
                    printf("+ 2^-%d ",i+1);
                }
                noprint++;
            }
        }
    }
    
    printf(") * 2^(%d-1023)\n",exnum);
}
int main()
{
    printf("Please enter a floating-point number (double precision): ");
    double input=0;
    int to_bi1[64];
    int to_bi2[64];
    int exarr[64];
    int frac[64];
    int exnum=0;
    int ex=0;

    scanf("%lf",&input);

    int Sign = sign(input);
    int integer = abs((int)input);
    double point = 0;
    if(Sign==0)
    {
        point = input-integer;
    }
    else
    {
        point = (input*(-1))-integer;
    }
    
    detobi(integer,to_bi1,64);

    point_bi(point,to_bi2,64);

    if(integer!=0)
    {
        ex = findone(to_bi1,64);
    }
    else if(integer==0 && point!=0)
    {
        ex = findpoint(to_bi2,64);
    }
    else if(integer==0)
    {
        ex = 0;
    }
    //printf("ex=%d\n",ex);
    exnum = ex+1023;
    detobi(exnum,exarr,64);

    fraction(to_bi1,to_bi2,ex,frac,64);
    printf("Sign: %d\n",Sign);
    printf("Exponent: ");
    for(int i=53;i<64;i++)  //64-11+1  exponent = 11 bit
    {
        printf("%d",exarr[i]);
    }
    printf("\n");
    printf("Fraction: ");
    for(int i=0;i<52;i++)
    {
        printf("%d",frac[i]);
    }
    printf("\n");
    print_ans(input,frac,exnum,Sign);
    
}

