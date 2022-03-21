#include "myvector.h"


int main()
{
    double inner;
    double area;
    sVector *p = myvector_init();
    sVector v=*p;
    v.type=1;
    v.data.c.x=3;
    v.data.c.y=4;
    //cartesiantopolar(&v);
    //printf("%lf , %lf\n",v.data.p.distance,v.data.p.angle);
    //polortocartesian(&v);
    //printf("%lf , %lf\n",v.data.c.x,v.data.c.y);
    sVector pv;
    myvector_set(&pv,v.type,v.data.c.x,v.data.c.y);
    //printf("pv=%lf , %lf\n",pv.data.c.x,pv.data.c.y);
    sVector pA;
    sVector *pB = myvector_init();
    pB->type=1;
    pB->data.c.x=3;
    pB->data.c.y=4;
    sVector *pC = myvector_init();
    pC->type=2;
    pC->data.p.distance=1.414;
    pC->data.p.angle=0.78539;
    polortocartesian(pC);
    myvector_print( pB, pB->type );
    myvector_print( pC, pC->type );
    myvector_add(&pA,&pv,pC);
    myvector_print( &pA, pA.type );
    myvector_inner_product(&inner,pB,pC);
    printf("inner=%lf\n",inner);
    myvector_area(&area, pB, pC);
    printf("%lf",area);
    double px;
    double py;
    double ptx=6;
    double pty=6;
    myvector_cvp(&px,&py,&ptx,&pty,pB,&pv);
    printf("px=%lf,py=%lf",px,py);
    
}
//(1.424214,0.004363-pi)
