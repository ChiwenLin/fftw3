#include <math.h>
#include <stdio.h>
#include <string.h>
#include <spu_intrinsics.h>
#include "fftw-spu.h"
#include "../fftw-cell.h"

#undef DEBUG

const double twopi = 6.2831853071795864769252867665590057683943388;

R *fill_twiddle(R *W, int r, int m)
{
     int i, j, v, n = r * m;

     for (j = 0; j < m; j += VL) {
	  for (i = 1; i < r; ++i) {
	       for (v = 0; v < VL; ++v) 
		    *W++ = cos(twopi * i * (j+v) / n);
	       for (v = 0; v < VL; ++v) 
		    *W++ = sin(twopi * i * (j+v) / n);
	  }
     }
     return W;
}

R A[2*MAX_N] __attribute__ ((aligned (16)));
R B[2*MAX_N] __attribute__ ((aligned (16)));
R W[5*MAX_N] __attribute__ ((aligned (16)));

void fill_plan(struct spu_plan *p)
{
     p->W = W;     
     while (p->r > 0) {
	  p[1].W = fill_twiddle(p->W, p->r, p->m);
	  ++p;
     }
}

void print_plan(struct spu_plan *p)
{
     while (p->r > 0) {
	  printf("[r:%d m:%d] ", p->r, p->m);
	  ++p;
     }
     printf("\n");
}

unsigned decrementer(void)
{
     return spu_readch(SPU_RdDec);
}

void check(int n)
{
     double maxerr = 0;
     int i, j;

     for (i = 0; i < n; ++i) {
	  double xr = 0, xi = 0;
	  for (j = 0; j < n; ++j) {
	       double c = cos(twopi * i * j / n);
	       double s = -sin(twopi * i * j / n);
	       xr += A[2*j] * c - A[2*j+1] * s;
	       xi += A[2*j] * s + A[2*j+1] * c;
	  }

	  xr -= B[2*i]; if (xr < 0) xr = -xr;
	  xi -= B[2*i+1]; if (xi < 0) xi = -xi;
	  if (xr > maxerr) maxerr = xr;
	  if (xi > maxerr) maxerr = xi;
     }
     printf("%4d %16.10g\n", n, maxerr);
}

struct spu_plan the_plan[15];
struct spu_plan best_plan[15];
int best_time = 10000000;

void doit(void)
{
     int i;
     int b, e;

     fill_plan(the_plan);

     b = decrementer();
     for (i = 0; i < 100; ++i)
	  X(spu_execute_plan)(the_plan, A, B);
     e = decrementer();

     b -= e;

     if (b <= best_time) {

	  memcpy(best_plan, the_plan, sizeof(the_plan));
	  best_time = b;
     }
}

void genall(struct spu_plan *p, int n, int v)
{
     int r;

     if (n < sizeof(X(n2fvtab))  / sizeof(X(n2fvtab)[0])
	 && X(n2fvtab)[n] && (v % VL) == 0) {
	  p->r = -n;
	  doit();
     }

     for (r = 2; r < sizeof(X(t1fvtab))  / sizeof(X(t1fvtab)[0]); ++r)
	  if (n % r == 0 && X(t1fvtab)[r] && ((n / r) % VL) == 0) {
	       p->r = r;
	       p->m = n / r;
	       genall(p+1, p->m, v > 1 ? v : p->r);
	  }
}

#ifdef DEBUG
int main( int argc, char *argv[])
{  
     int n;
     int i;

     spu_writech(SPU_WrDec, -1);

     for (n = 1; n <= MAX_N; ++n) {
	  best_time = 1000000000;
	  best_plan[0].r = 0; /* invalid plan */

	  genall(the_plan, n, 1);

	  if (best_plan[0].r) {
	       printf("%5d: %8d   ", n, best_time);
	       print_plan(best_plan);

	       for (i = 0; i < 2 * n; ++i)
		    A[i] = ((i*i)%n+1) / (double)n;

	       fill_plan(best_plan);
	       X(spu_execute_plan)(best_plan, A, B);	  
	  
	       check(n);
	  }
     }
}

#else
/* output a C file containing a compact representation of all plans
   from 1 to MAX_N */
int main( int argc, char *argv[])
{  
     int n;
     struct spu_plan *p;

     spu_writech(SPU_WrDec, -1);
     printf("/* automatically generated by spu/planner; DO NOT EDIT */\n\n");
     printf("#include \"fftw-cell.h\"\n\n");
     printf("const struct spu_radices X(spu_radices)[%d] = {\n", 
	    (MAX_N/REQUIRE_N_MULTIPLE_OF) + 1);
     for (n = 0; n <= MAX_N; n += REQUIRE_N_MULTIPLE_OF) {
	  best_time = 1000000000;
	  best_plan[0].r = 0; /* invalid plan */

	  if (n > 0)
	       genall(the_plan, n, 1);

	  printf("  /* [%4d] */ {{", n);

	  if (best_plan[0].r) {
	       p = best_plan;
	       for (p = best_plan; ; ++p) {
		    printf(" %d", p->r);
		    if (p->r < 0) break;
		    printf(",");
	       } 
	  } else {
	       printf(" 0");
	  }
	  printf(" }},\n");
     }
     printf("};\n\n");
     return 0;
}
#endif


