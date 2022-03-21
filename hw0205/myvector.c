#include "myvector.h"

sVector *myvector_init(void)
{
    sVector *v=calloc(1,sizeof(sVector));
    return v;
}


void changeagl(double *agl)
{
    double angle=( (*agl)*180 )/PI;
    if(angle>360)
    {
        while(angle>360)
        {
            angle=angle-360;
        }
    }
    else if(angle<0)
    {
        while(angle<0)
        {
            angle=angle+360;
        }
    }
     
    *agl=(angle)/180;
}
void cartesiantopolar ( sVector *v)
{
    double x= (*v).data.c.x;
    double y= (*v).data.c.y;
    double r = sqrt(x*x + y*y);
    double theta = atan(y/x);
    (*v).type=2;
    (*v).data.p.distance=r;
    (*v).data.p.angle=theta;
}
void polortocartesian(sVector *v)
{
    double r=(*v).data.p.distance;
    double angle=(*v).data.p.angle;
    
    (*v).type=1;
    (*v).data.c.x=r*cos(angle);
    (*v).data.c.y=r*sin(angle);
}
void totypeone(sVector *tmp1,sVector *tmp2,const sVector *pB, const sVector *pC )
{
    if(pB->type!=1)
    {
        *tmp1=*pB;
        polortocartesian(tmp1);
    }
    else
    {
        *tmp1=*pB;
    }
    if(pC->type!=1)
    {
        *tmp2=*pC;
        polortocartesian(tmp2);
        //printf("tmp2=%lf , %lf\n",tmp2->data.c.x,tmp2->data.c.y);
    }
    else
    {
        *tmp2=*pC;
    }
}
int myvector_set( sVector *pVector, uint8_t type, double a, double b )
{
    if(pVector==NULL) return -1;
    (*pVector).type=type;
    if(type==1)
    {
        (*pVector).data.c.x=a;
        (*pVector).data.c.y=b;
    }
    else if(type==2)
    {
        if(a<0) return -1;
        (*pVector).data.p.distance=a;
        (*pVector).data.p.angle=b;
    }
    else
    {
        return -1;
    }
    return 0;
}
int myvector_print( const sVector *pVector, uint8_t type )
{
    if(pVector==NULL) return -1;
    if(type==1)
    {
        printf("(%lf,%lf)",(*pVector).data.c.x,(*pVector).data.c.y);
    }
    else if(type==2)
    {
        double agl=(*pVector).data.p.angle;
        changeagl(&agl);
        double tmp =agl;
        printf("(%lf,%lf-pi)",(*pVector).data.p.distance,tmp);
    }
    
    return 0;
}
int myvector_add( sVector *pA, const sVector *pB, const sVector *pC )
{
    sVector tmp1;
    sVector tmp2;
    if(pA==NULL||pB==NULL||pC==NULL) return -1;
    (*pA).type=pB->type;
    totypeone(&tmp1, &tmp2, pB, pC);

    double x=tmp1.data.c.x+tmp2.data.c.x;
    double y=tmp1.data.c.y+tmp2.data.c.y;
    if((*pA).type==1)
    {
        (*pA).data.c.x=x;
        (*pA).data.c.y=y;
    }
    else if((*pA).type==2)
    {
        sVector tmp;
        tmp.type=1;
        tmp.data.c.x=x;
        tmp.data.c.y=y;
        cartesiantopolar(&tmp);
        *pA=tmp;
    }
    return 0;
}

int myvector_inner_product( double *inner, const sVector *pB, const sVector *pC )
{
    sVector tmp1;
    sVector tmp2;
    totypeone(&tmp1,&tmp2,pB,pC);
    
    *inner=(tmp1.data.c.x)*(tmp2.data.c.x)+(tmp1.data.c.y)*(tmp2.data.c.y);
    return 0;
}
int myvector_area( double *pArea, const sVector *pB, const sVector *pC )
{
    sVector tmp1;
    sVector tmp2;
    double inner;
    totypeone(&tmp1, &tmp2, pB, pC);
    double r1=sqrt( (tmp1.data.c.x * tmp1.data.c.x)+(tmp1.data.c.y * tmp1.data.c.y) );
    double r2=sqrt( (tmp2.data.c.x * tmp2.data.c.x)+(tmp2.data.c.y * tmp2.data.c.y) );
    printf("r1=%lf r2=%lf\n",r1,r2);
    myvector_inner_product(&inner,&tmp1,&tmp2);
    double area=sqrt( r1*r1*r2*r2-pow(inner,2) );
    *pArea = area;
    return 0;
}
int u(double U[2][2],double new[2][2])
{
    double tmp=0;
    tmp = 1/( (U[0][0]*U[1][1])-(U[0][1]*U[1][0]) );
    if( (U[0][0]*U[1][1])-(U[0][1]*U[1][0]) ==0) return -1;
    new[0][0]=U[1][1]*tmp;
    new[0][1]=(-1)*U[0][1]*tmp;
    new[1][0]=(-1)*U[1][0]*tmp;
    new[1][1]=U[0][0]*tmp;
    return 0;
}
void array(double new[2][2],double *ptx,double *pty)
{
    *ptx=new[0][0]*(*ptx)+new[0][1]*(*pty);
    *pty=new[1][0]*(*ptx)+new[1][1]*(*pty);
    double point1=*ptx-(int)*ptx;
    double point2=*pty-(int)*pty;
    int px=(int)*ptx;
    int py=(int)*pty;
    if(point1>=0.5)
    {
        *ptx=px+1.0;
    }
    else if(point1<=-0.5)
    {
        *ptx=px-1.0;
    }
    if(point2>=0.5)
    {
        *pty=py+1.0;
    }
    else if(point2<=-0.5)
    {
        *pty=py-1.0;
    }

}
void shot(double ptx,double pty,const sVector *pA,double *x,double *y)
{
    double inner=0;
    sVector pt;
    myvector_set(&pt,1,ptx,pty);
    myvector_inner_product(&inner, &pt, pA);
    double pow_b= pow(pA->data.c.x,2)+pow(pA->data.c.y,2);
    double k=inner/pow_b;
    *x=(pA->data.c.x)*k;
    *y=(pA->data.c.y)*k;
}
int myvector_cvp( double *pX, double *pY, const double *pTx, const double *pTy, const sVector *pA, const sVector *pB )
{
    double U[2][2]={0};
    double new_u[2][2]={0};
    sVector tmp1;
    sVector tmp2;
    double ptx=*pTx;
    double pty=*pTy;
    totypeone(&tmp1, &tmp2, pA, pB);
    U[0][0]=tmp1.data.c.x;
    U[0][1]=tmp2.data.c.x;
    U[1][0]=tmp1.data.c.y;
    U[1][1]=tmp2.data.c.y;
    int re=u(U,new_u);
    if(re==-1)
    {
        double x;
        double y;
        shot(ptx,pty,&tmp1,&x,&y);
        *pX=x;
        *pY=y;
    }
    else
    {
        array(new_u,&ptx,&pty);
        *pX=ptx;
        *pY=pty;
    }
    return 0;
}
