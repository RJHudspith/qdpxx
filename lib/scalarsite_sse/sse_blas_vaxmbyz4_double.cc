
/*! @file
 *  @brief Generic Scalar VAXPY routine
 *
 */

#include "scalarsite_sse/sse_blas_vaxmbyz4_double.h"
#include <xmmintrin.h>
#include "scalarsite_sse/sse_prefetch.h"

namespace QDP {


#ifndef L2BY2
#define L2BY2 1365          /* L2 / 2 in SPINORS */
#endif
  
  void vaxmbyz4(REAL64 *z,REAL64 *a,REAL64 *x, REAL64 *b, REAL64 *y, int n_4vec)
  {
  // Load the scalar into low bytes of scalar
  __m128d a_sse = _mm_load_sd(a);
  __m128d b_sse = _mm_load_sd(b);

  // cross components into tmp 
  // Zero tmp
  __m128d tmp1 = _mm_setzero_pd();
  
  tmp1 = _mm_shuffle_pd(a_sse, a_sse, 0x1);
  a_sse = _mm_add_pd(a_sse, tmp1);

  __m128d tmp2 = _mm_setzero_pd();
  tmp2 = _mm_shuffle_pd(b_sse, b_sse, 0x1);
  b_sse = _mm_add_pd(b_sse, tmp2);

  // Do n_3vec 3vectors.
  double *x_p=x;
  double *y_p=y;
  double *z_p=z;

  __m128d tmp3 ;
  __m128d x1 ,y1 ,z1 ;
  __m128d x2 ,y2 ,z2 ;
  __m128d x3 ,y3 ,z3 ;
  
  if( n_4vec < L2BY2 ) { 
    PREFETCHW(((const char *)z_p)+8);
    PREFETCHW(((const char *)z_p)+16);
    for(int i=0; i < 3*n_4vec; i++) { 

      y1 = _mm_load_pd(y_p);
      x1 = _mm_load_pd(x_p);
      z1 = _mm_mul_pd(a_sse,x1);
      tmp1 = _mm_mul_pd(b_sse,y1);
      z1 = _mm_sub_pd(z1,tmp1);
      _mm_store_pd(z_p, z1);
      
      y2 = _mm_load_pd(y_p+2);
      x2 = _mm_load_pd(x_p+2);
      z2 = _mm_mul_pd(a_sse,x2);
      tmp2 = _mm_mul_pd(b_sse,y2);
      z2 = _mm_sub_pd(z2,tmp2);
      _mm_store_pd(z_p+2, z2);
      
      y3 = _mm_load_pd(y_p+4);
      x3 = _mm_load_pd(x_p+4);
      z3 = _mm_mul_pd(a_sse,x3);
      tmp3 = _mm_mul_pd(b_sse,y3);
      z3 = _mm_sub_pd(z3,tmp3);
      _mm_store_pd(z_p+4, z3);
      
      y1 = _mm_load_pd(y_p+6);
      x1 = _mm_load_pd(x_p+6);
      z1 = _mm_mul_pd(a_sse,x1);
      tmp1 = _mm_mul_pd(b_sse,y1);
      z1 = _mm_sub_pd(z1,tmp1);
      _mm_store_pd(z_p+6, z1);

      x_p+=8; y_p+=8; z_p+=8;
    }
  }
  else {

    for(int i=0; i < 3*n_4vec; i++) { 

      PREFETCHNTA(((const char *)x_p)+56);
      PREFETCHNTA(((const char *)y_p)+56);

      y1 = _mm_load_pd(y_p);
      x1 = _mm_load_pd(x_p);
      z1 = _mm_mul_pd(a_sse,x1);
      tmp1 = _mm_mul_pd(b_sse,y1);
      z1 = _mm_sub_pd(z1,tmp1);
      _mm_stream_pd(z_p, z1);
      
      y2 = _mm_load_pd(y_p+2);
      x2 = _mm_load_pd(x_p+2);
      z2 = _mm_mul_pd(a_sse,x2);
      tmp2 = _mm_mul_pd(b_sse,y2);
      z2 = _mm_sub_pd(z2,tmp2);
      _mm_stream_pd(z_p+2, z2);
      
      
      y3 = _mm_load_pd(y_p+4);
      x3 = _mm_load_pd(x_p+4);
      z3 = _mm_mul_pd(a_sse,x3);
      tmp3 = _mm_mul_pd(b_sse,y3);
      z3 = _mm_sub_pd(z3,tmp3);
      _mm_stream_pd(z_p+4, z3);
      
      
      y1 = _mm_load_pd(y_p+6);
      x1 = _mm_load_pd(x_p+6);
      z1 = _mm_mul_pd(a_sse,x1);
      tmp1 = _mm_mul_pd(b_sse,y1);
      z1 = _mm_sub_pd(z1,tmp1);
      _mm_stream_pd(z_p+6, z1);

      x_p+=8; y_p+=8; z_p+=8;

    }


  }
}

  void vaxmby4(REAL64 *y,REAL64 *a,REAL64 *x, REAL64 *b, int n_4vec)
{
  __m128d a_sse;
  __m128d b_sse;
 
  __m128d tmp1;
  __m128d tmp2;
  __m128d tmp3;

  __m128d x1;
  __m128d y1;
  __m128d z1;

  __m128d x2;
  __m128d y2;
  __m128d z2;

  __m128d x3;
  __m128d y3;
  __m128d z3;

  // Load the scalar into low bytes of scalar
  a_sse = _mm_load_sd(a);
  b_sse = _mm_load_sd(b);

  // cross components into tmp 
  // Zero tmp
  tmp1 = _mm_setzero_pd();
  tmp1 = _mm_shuffle_pd(a_sse, a_sse, 0x1);
  a_sse = _mm_add_pd(a_sse, tmp1);

  tmp2 = _mm_setzero_pd();
  tmp2 = _mm_shuffle_pd(b_sse, b_sse, 0x1);
  b_sse = _mm_add_pd(b_sse, tmp2);


  // Do n_3vec 3vectors.
  double *x_p=x;
  double *y_p=y;


  if( n_4vec < L2BY2 ) { 
    for(int i=0; i < 3*n_4vec; i++) { 
      PREFETCHW(((const char *)y_p)+16);

      y1 = _mm_load_pd(y_p);
      x1 = _mm_load_pd(x_p);
      z1 = _mm_mul_pd(a_sse,x1);
      tmp1 = _mm_mul_pd(b_sse,y1);
      z1 = _mm_sub_pd(z1,tmp1);
      _mm_store_pd(y_p, z1);
      
      y2 = _mm_load_pd(y_p+2);
      x2 = _mm_load_pd(x_p+2);
      z2 = _mm_mul_pd(a_sse,x2);
      tmp2 = _mm_mul_pd(b_sse,y2);
      z2 = _mm_sub_pd(z2,tmp2);
      _mm_store_pd(y_p+2, z2);
      
      
      y3 = _mm_load_pd(y_p+4);
      x3 = _mm_load_pd(x_p+4);
      z3 = _mm_mul_pd(a_sse,x3);
      tmp3 = _mm_mul_pd(b_sse,y3);
      z3 = _mm_sub_pd(z3,tmp3);
      _mm_store_pd(y_p+4, z3);
      
      
      y1 = _mm_load_pd(y_p+6);
      x1 = _mm_load_pd(x_p+6);
      z1 = _mm_mul_pd(a_sse,x1);
      tmp1 = _mm_mul_pd(b_sse,y1);
      z1 = _mm_sub_pd(z1,tmp1);
      _mm_store_pd(y_p+6, z1);

      x_p +=8; y_p+=8;
    }

  }
  else { 
    for(int i=0; i < 3*n_4vec; i++) { 

      PREFETCHNTA(((const char *)y_p)+56);
      PREFETCHNTA(((const char *)x_p)+56);

      y1 = _mm_load_pd(y_p);
      x1 = _mm_load_pd(x_p);
      z1 = _mm_mul_pd(a_sse,x1);
      tmp1 = _mm_mul_pd(b_sse,y1);
      z1 = _mm_sub_pd(z1,tmp1);
      _mm_store_pd(y_p, z1);
      
      y2 = _mm_load_pd(y_p+2);
      x2 = _mm_load_pd(x_p+2);
      z2 = _mm_mul_pd(a_sse,x2);
      tmp2 = _mm_mul_pd(b_sse,y2);
      z2 = _mm_sub_pd(z2,tmp2);
      _mm_store_pd(y_p+2, z2);
      
      
      y3 = _mm_load_pd(y_p+4);
      x3 = _mm_load_pd(x_p+4);
      z3 = _mm_mul_pd(a_sse,x3);
      tmp3 = _mm_mul_pd(b_sse,y3);
      z3 = _mm_sub_pd(z3,tmp3);
      _mm_store_pd(y_p+4, z3);
      
      
      y1 = _mm_load_pd(y_p+6);
      x1 = _mm_load_pd(x_p+6);
      z1 = _mm_mul_pd(a_sse,x1);
      tmp1 = _mm_mul_pd(b_sse,y1);
      z1 = _mm_sub_pd(z1,tmp1);
      _mm_store_pd(y_p+6, z1);

      x_p +=8; y_p+=8;
    }

  }
  
}

}



