#ifndef myvector_h
#define myvector_h

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.141592

typedef struct _sVector {
    uint8_t type;
    union Component
    {
        struct _sCartesian
        {
            double x;
            double y;
        } c;
        
        struct _sPolar
        {
            double distance;
            double angle;
        } p;
    } data;
}sVector;

sVector *myvector_init(void);
void changeagl(double *agl);
void cartesiantopolar ( sVector *v);
void polortocartesian(sVector *v);
void totypeone(sVector *tmp1,sVector *tmp2,const sVector *pB, const sVector *pC );
int myvector_set( sVector *pVector, uint8_t type, double a, double b );
int myvector_print( const sVector *pVector, uint8_t type );
int myvector_add( sVector *pA, const sVector *pB, const sVector *pC );
int myvector_inner_product( double *inner, const sVector *pB, const sVector *pC );
int myvector_area( double *pArea, const sVector *pB, const sVector *pC );
int u(double U[2][2],double new[2][2]);
void array(double new[2][2],double *ptx,double *pty);
void shot(double ptx,double pty,const sVector *pA,double *x,double *y);
int myvector_cvp( double *pX, double *pY, const double *pTx, const double *pTy, const sVector *pA, const sVector *pB );

#endif /* myvector_h */
