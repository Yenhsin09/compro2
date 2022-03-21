#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct _sMixedNumber {
    int denominator;
    int numertor;
    char operator;
}sMixedNumber;

int ck1(char *input)
{
    int num=0;
    if(*input=='c'&&*(input+1)=='{')
    {
        num = atoi(input+2);
 //       printf("ck1:%d\n",num);
        return num;
    }
    else
    {
        return -1;
    }
}
int ck2(char *input)
{
    int num=0;
    if(*input=='}'&&*(input+1)=='{')
    {
        num = atoi(input+2);
//        printf("ck2:%d\n",num);
        return num;
    }
    else
    {
        return -1;
    }
}

int store(char input[4096],sMixedNumber num[4096])
{
    int i=0;
    int arr=0;
    int k=0;
    int nu =0;
    int save_nu=0;
    int de = 0;
    num[arr].operator='+';
    while(input[i]!='\0')
    {
        if(i==0 && isdigit(input[i]))
        {
            k=atoi(&input[i]);
            i++;
            continue;
        }
        if(input[i]=='+'||input[i]=='-'||input[i]=='*'||input[i]=='/')
        {
            if(isdigit(input[i-1])&&i!=0)
            {
                num[arr].denominator=1;
                num[arr].numertor=k;
            }
            if(i!=0 && input[i-1]!='(')
            {
                arr++;
            }
            num[arr].operator=input[i];
            if(input[i+1]=='(')
            {
                if(input[i+2]!='-')
                {
                    return -1;
                }
            }
            if(isdigit(input[i+1]))
            {
                k=atoi(&input[i+1]);
            }
            else
            {
                k=0;
            }
        }
        
        nu = ck1(&input[i]);
        if(nu!=-1)
        {
            num[arr].numertor= nu;
            save_nu=nu;
        }
        
        de= ck2(&input[i]);
        
        if(de!=-1)
        {
            num[arr].denominator= de;
            if(de==0)
            {
                return -1;
            }
            num[arr].numertor=de*k+save_nu;
            //printf("de=%d k=%d nu=%d\n",de,k,save_nu);
        }
        i++;
    }
    
    if(num[arr].denominator==0&&num[arr].numertor==0)
    {
        num[arr].denominator=1;
        num[arr].numertor=k;
    }
    return arr+1;
}

int GCD(int A,int B)
{
    int R;
    if (B==0)
    return -1;
    while ( (R = A % B) != 0 )
    {
        A = B;
        B = R;
     }
    return B;
}
void mixed_add( sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2)
{
    int one_de=r1.denominator;
    int one_nu=r1.numertor;
    int two_de=r2.denominator;
    int two_nu=r2.numertor;
    if(one_de!=two_de)
    {
        (*pNumber).denominator=one_de*two_de;
        (*pNumber).numertor=one_nu*two_de+two_nu*one_de;
    }
    else
    {
        (*pNumber).denominator=one_de;
        (*pNumber).numertor=one_nu+two_nu;
    }
    (*pNumber).operator='+';
}

void mixed_sub( sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2)
{
    int one_de=r1.denominator;
    int one_nu=r1.numertor;
    int two_de=r2.denominator;
    int two_nu=r2.numertor;
    two_nu=two_nu*(-1);
    
    if(one_de!=two_de)
    {
        (*pNumber).denominator=one_de*two_de;
        (*pNumber).numertor=one_nu*two_de+two_nu*one_de;
    }
    else
    {
        (*pNumber).denominator=one_de;
        (*pNumber).numertor=one_nu+two_nu;
    }
    (*pNumber).operator='+';
}

void mixed_mul( sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2)
{
    int de=r1.denominator*r2.denominator;
    (*pNumber).denominator =de;
    int nu=r1.numertor*r2.numertor;
    (*pNumber).numertor =nu;
    (*pNumber).operator=r1.operator;
}

void mixed_div( sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2)
{
    int de=r1.denominator*r2.numertor;
    (*pNumber).denominator =de;
    int nu=r1.numertor*r2.denominator;
    (*pNumber).numertor =nu;
    (*pNumber).operator=r1.operator;
}
int search(sMixedNumber num[4096],int k)
{
    
    if(num[k].operator=='*' ||num[k].operator=='/')
    {
        return 0;
    }
    return -1;
}
void locate(sMixedNumber num[4096],int *p,int a,sMixedNumber new)
{
    num[a-1]=new;
    for(int i=a;i<(*p);i++)
    {
        if(i==(*p)-1)
        {
            num[i].operator=0;
            num[i].numertor=0;
            num[i].denominator=0;
            break;
        }
        num[i]=num[i+1];
    }
    
    (*p)--;
}

int main()
{
    char input[4096]={0};
    sMixedNumber num[4096]={0};
    int integer=0;
    printf("Q: ");
    scanf("%s",input);
    int arr = store(input,num); //how many number
   
    if(arr==-1)
    {
        printf("invalid input\n");
        exit(0);
    }
    if(arr==1)
    {
        printf("%s\n",input);
        exit(0);
    }
   
    if(num[0].operator=='-')
    {
        num[0].numertor=num[0].numertor*(-1);
        num[0].operator='+';
    }
    
    sMixedNumber t;
    for(int i=0;i<arr;i++)
    {
        if(arr==1)
        {
            break;
        }
        int a=search(num,i);
        if(a==0)
        {
            if(num[i].operator=='*')
            {
                mixed_mul(&t,num[i-1],num[i]);
                locate(num,&arr,i,t);
                i--;
            }
            else
            {
                mixed_div(&t,num[i-1],num[i]);
                locate(num,&arr,i,t);
                i--;
            }
        }

    }

    for(int i=0;i<arr;i++)
    {
        if(arr==1)
        {
            break;
        }
        if(i==0)
        {
            continue;
        }
        
        if(num[i].operator=='+')
        {
            mixed_add(&t,num[i-1],num[i]);
            locate(num,&arr,i,t);  //arr=有幾個數
            i--;
        }
        else
        {
            mixed_sub(&t,num[i-1],num[i]);
            locate(num,&arr,i,t);
            i--;
        }
        
    }
    
    int ans_de=num[0].denominator;
    int ans_nu=abs(num[0].numertor);
    int tmp =  GCD(ans_de,ans_nu);
    num[0].denominator=ans_de/tmp;
    num[0].numertor=num[0].numertor/tmp;
    
    if(num[0].numertor%num[0].denominator==0)
    {
        integer =num[0].numertor/num[0].denominator;
        printf("%d\n",integer);
        exit(0);
    }
    
    int a= num[0].numertor/num[0].denominator;
    int b1=num[0].numertor-(a*num[0].denominator);
    int b2=(-1)*num[0].numertor-((-1)*a*num[0].denominator);
    if(a==0)
    {
        if(b1>0)
        {
            printf("\\frac{%d}{%d}\n",b1,num[0].denominator);
        }
        else
        {
            printf("-\\frac{%d}{%d}\n",-b1,num[0].denominator);
        }
    }
    else if(a>0)
    {
        printf("%d\\frac{%d}{%d}\n",a,b1,num[0].denominator);
    }
    else
    {
        printf("%d\\frac{%d}{%d}\n",a,b2,num[0].denominator);
    }
}



//  \frac{2}{1}-\frac{2}{1}
