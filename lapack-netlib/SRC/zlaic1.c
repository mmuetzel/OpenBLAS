/* f2c.h  --  Standard Fortran to C header file */

/**  barf  [ba:rf]  2.  "He suggested using FORTRAN, and everybody barfed."

	- From The Shogakukan DICTIONARY OF NEW ENGLISH (Second edition) */

#ifndef F2C_INCLUDE
#define F2C_INCLUDE

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <complex.h>
#ifdef complex
#undef complex
#endif
#ifdef I
#undef I
#endif

#if defined(_WIN64)
typedef long long BLASLONG;
typedef unsigned long long BLASULONG;
#else
typedef long BLASLONG;
typedef unsigned long BLASULONG;
#endif

#ifdef LAPACK_ILP64
typedef BLASLONG blasint;
#if defined(_WIN64)
#define blasabs(x) llabs(x)
#else
#define blasabs(x) labs(x)
#endif
#else
typedef int blasint;
#define blasabs(x) abs(x)
#endif

typedef blasint integer;

typedef unsigned int uinteger;
typedef char *address;
typedef short int shortint;
typedef float real;
typedef double doublereal;
typedef struct { real r, i; } complex;
typedef struct { doublereal r, i; } doublecomplex;
static inline _Complex float Cf(complex *z) {return z->r + z->i*_Complex_I;}
static inline _Complex double Cd(doublecomplex *z) {return z->r + z->i*_Complex_I;}
static inline _Complex float * _pCf(complex *z) {return (_Complex float*)z;}
static inline _Complex double * _pCd(doublecomplex *z) {return (_Complex double*)z;}
#define pCf(z) (*_pCf(z))
#define pCd(z) (*_pCd(z))
typedef int logical;
typedef short int shortlogical;
typedef char logical1;
typedef char integer1;

#define TRUE_ (1)
#define FALSE_ (0)

/* Extern is for use with -E */
#ifndef Extern
#define Extern extern
#endif

/* I/O stuff */

typedef int flag;
typedef int ftnlen;
typedef int ftnint;

/*external read, write*/
typedef struct
{	flag cierr;
	ftnint ciunit;
	flag ciend;
	char *cifmt;
	ftnint cirec;
} cilist;

/*internal read, write*/
typedef struct
{	flag icierr;
	char *iciunit;
	flag iciend;
	char *icifmt;
	ftnint icirlen;
	ftnint icirnum;
} icilist;

/*open*/
typedef struct
{	flag oerr;
	ftnint ounit;
	char *ofnm;
	ftnlen ofnmlen;
	char *osta;
	char *oacc;
	char *ofm;
	ftnint orl;
	char *oblnk;
} olist;

/*close*/
typedef struct
{	flag cerr;
	ftnint cunit;
	char *csta;
} cllist;

/*rewind, backspace, endfile*/
typedef struct
{	flag aerr;
	ftnint aunit;
} alist;

/* inquire */
typedef struct
{	flag inerr;
	ftnint inunit;
	char *infile;
	ftnlen infilen;
	ftnint	*inex;	/*parameters in standard's order*/
	ftnint	*inopen;
	ftnint	*innum;
	ftnint	*innamed;
	char	*inname;
	ftnlen	innamlen;
	char	*inacc;
	ftnlen	inacclen;
	char	*inseq;
	ftnlen	inseqlen;
	char 	*indir;
	ftnlen	indirlen;
	char	*infmt;
	ftnlen	infmtlen;
	char	*inform;
	ftnint	informlen;
	char	*inunf;
	ftnlen	inunflen;
	ftnint	*inrecl;
	ftnint	*innrec;
	char	*inblank;
	ftnlen	inblanklen;
} inlist;

#define VOID void

union Multitype {	/* for multiple entry points */
	integer1 g;
	shortint h;
	integer i;
	/* longint j; */
	real r;
	doublereal d;
	complex c;
	doublecomplex z;
	};

typedef union Multitype Multitype;

struct Vardesc {	/* for Namelist */
	char *name;
	char *addr;
	ftnlen *dims;
	int  type;
	};
typedef struct Vardesc Vardesc;

struct Namelist {
	char *name;
	Vardesc **vars;
	int nvars;
	};
typedef struct Namelist Namelist;

#define abs(x) ((x) >= 0 ? (x) : -(x))
#define dabs(x) (fabs(x))
#define f2cmin(a,b) ((a) <= (b) ? (a) : (b))
#define f2cmax(a,b) ((a) >= (b) ? (a) : (b))
#define dmin(a,b) (f2cmin(a,b))
#define dmax(a,b) (f2cmax(a,b))
#define bit_test(a,b)	((a) >> (b) & 1)
#define bit_clear(a,b)	((a) & ~((uinteger)1 << (b)))
#define bit_set(a,b)	((a) |  ((uinteger)1 << (b)))

#define abort_() { sig_die("Fortran abort routine called", 1); }
#define c_abs(z) (cabsf(Cf(z)))
#define c_cos(R,Z) { pCf(R)=ccos(Cf(Z)); }
#define c_div(c, a, b) {pCf(c) = Cf(a)/Cf(b);}
#define z_div(c, a, b) {pCd(c) = Cd(a)/Cd(b);}
#define c_exp(R, Z) {pCf(R) = cexpf(Cf(Z));}
#define c_log(R, Z) {pCf(R) = clogf(Cf(Z));}
#define c_sin(R, Z) {pCf(R) = csinf(Cf(Z));}
//#define c_sqrt(R, Z) {*(R) = csqrtf(Cf(Z));}
#define c_sqrt(R, Z) {pCf(R) = csqrtf(Cf(Z));}
#define d_abs(x) (fabs(*(x)))
#define d_acos(x) (acos(*(x)))
#define d_asin(x) (asin(*(x)))
#define d_atan(x) (atan(*(x)))
#define d_atn2(x, y) (atan2(*(x),*(y)))
#define d_cnjg(R, Z) { pCd(R) = conj(Cd(Z)); }
#define r_cnjg(R, Z) { pCf(R) = conj(Cf(Z)); }
#define d_cos(x) (cos(*(x)))
#define d_cosh(x) (cosh(*(x)))
#define d_dim(__a, __b) ( *(__a) > *(__b) ? *(__a) - *(__b) : 0.0 )
#define d_exp(x) (exp(*(x)))
#define d_imag(z) (cimag(Cd(z)))
#define r_imag(z) (cimag(Cf(z)))
#define d_int(__x) (*(__x)>0 ? floor(*(__x)) : -floor(- *(__x)))
#define r_int(__x) (*(__x)>0 ? floor(*(__x)) : -floor(- *(__x)))
#define d_lg10(x) ( 0.43429448190325182765 * log(*(x)) )
#define r_lg10(x) ( 0.43429448190325182765 * log(*(x)) )
#define d_log(x) (log(*(x)))
#define d_mod(x, y) (fmod(*(x), *(y)))
#define u_nint(__x) ((__x)>=0 ? floor((__x) + .5) : -floor(.5 - (__x)))
#define d_nint(x) u_nint(*(x))
#define u_sign(__a,__b) ((__b) >= 0 ? ((__a) >= 0 ? (__a) : -(__a)) : -((__a) >= 0 ? (__a) : -(__a)))
#define d_sign(a,b) u_sign(*(a),*(b))
#define r_sign(a,b) u_sign(*(a),*(b))
#define d_sin(x) (sin(*(x)))
#define d_sinh(x) (sinh(*(x)))
#define d_sqrt(x) (sqrt(*(x)))
#define d_tan(x) (tan(*(x)))
#define d_tanh(x) (tanh(*(x)))
#define i_abs(x) abs(*(x))
#define i_dnnt(x) ((integer)u_nint(*(x)))
#define i_len(s, n) (n)
#define i_nint(x) ((integer)u_nint(*(x)))
#define i_sign(a,b) ((integer)u_sign((integer)*(a),(integer)*(b)))
#define pow_dd(ap, bp) ( pow(*(ap), *(bp)))
#define pow_si(B,E) spow_ui(*(B),*(E))
#define pow_ri(B,E) spow_ui(*(B),*(E))
#define pow_di(B,E) dpow_ui(*(B),*(E))
#define pow_zi(p, a, b) {pCd(p) = zpow_ui(Cd(a), *(b));}
#define pow_ci(p, a, b) {pCf(p) = cpow_ui(Cf(a), *(b));}
#define pow_zz(R,A,B) {pCd(R) = cpow(Cd(A),*(B));}
#define s_cat(lpp, rpp, rnp, np, llp) { 	ftnlen i, nc, ll; char *f__rp, *lp; 	ll = (llp); lp = (lpp); 	for(i=0; i < (int)*(np); ++i) {         	nc = ll; 	        if((rnp)[i] < nc) nc = (rnp)[i]; 	        ll -= nc;         	f__rp = (rpp)[i]; 	        while(--nc >= 0) *lp++ = *(f__rp)++;         } 	while(--ll >= 0) *lp++ = ' '; }
#define s_cmp(a,b,c,d) ((integer)strncmp((a),(b),f2cmin((c),(d))))
#define s_copy(A,B,C,D) { int __i,__m; for (__i=0, __m=f2cmin((C),(D)); __i<__m && (B)[__i] != 0; ++__i) (A)[__i] = (B)[__i]; }
#define sig_die(s, kill) { exit(1); }
#define s_stop(s, n) {exit(0);}
static char junk[] = "\n@(#)LIBF77 VERSION 19990503\n";
#define z_abs(z) (cabs(Cd(z)))
#define z_exp(R, Z) {pCd(R) = cexp(Cd(Z));}
#define z_sqrt(R, Z) {pCd(R) = csqrt(Cd(Z));}
#define myexit_() break;
#define mycycle() continue;
#define myceiling(w) {ceil(w)}
#define myhuge(w) {HUGE_VAL}
//#define mymaxloc_(w,s,e,n) {if (sizeof(*(w)) == sizeof(double)) dmaxloc_((w),*(s),*(e),n); else dmaxloc_((w),*(s),*(e),n);}
#define mymaxloc(w,s,e,n) {dmaxloc_(w,*(s),*(e),n)}

/* procedure parameter types for -A and -C++ */

#define F2C_proc_par_types 1
#ifdef __cplusplus
typedef logical (*L_fp)(...);
#else
typedef logical (*L_fp)();
#endif

static float spow_ui(float x, integer n) {
	float pow=1.0; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x = 1/x;
		for(u = n; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
static double dpow_ui(double x, integer n) {
	double pow=1.0; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x = 1/x;
		for(u = n; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
static _Complex float cpow_ui(_Complex float x, integer n) {
	_Complex float pow=1.0; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x = 1/x;
		for(u = n; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
static _Complex double zpow_ui(_Complex double x, integer n) {
	_Complex double pow=1.0; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x = 1/x;
		for(u = n; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
static integer pow_ii(integer x, integer n) {
	integer pow; unsigned long int u;
	if (n <= 0) {
		if (n == 0 || x == 1) pow = 1;
		else if (x != -1) pow = x == 0 ? 1/x : 0;
		else n = -n;
	}
	if ((n > 0) || !(n == 0 || x == 1 || x != -1)) {
		u = n;
		for(pow = 1; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
static integer dmaxloc_(double *w, integer s, integer e, integer *n)
{
	double m; integer i, mi;
	for(m=w[s-1], mi=s, i=s+1; i<=e; i++)
		if (w[i-1]>m) mi=i ,m=w[i-1];
	return mi-s+1;
}
static integer smaxloc_(float *w, integer s, integer e, integer *n)
{
	float m; integer i, mi;
	for(m=w[s-1], mi=s, i=s+1; i<=e; i++)
		if (w[i-1]>m) mi=i ,m=w[i-1];
	return mi-s+1;
}
static inline void cdotc_(complex *z, integer *n_, complex *x, integer *incx_, complex *y, integer *incy_) {
	integer n = *n_, incx = *incx_, incy = *incy_, i;
	_Complex float zdotc = 0.0;
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += conjf(Cf(&x[i])) * Cf(&y[i]);
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += conjf(Cf(&x[i*incx])) * Cf(&y[i*incy]);
		}
	}
	pCf(z) = zdotc;
}
static inline void zdotc_(doublecomplex *z, integer *n_, doublecomplex *x, integer *incx_, doublecomplex *y, integer *incy_) {
	integer n = *n_, incx = *incx_, incy = *incy_, i;
	_Complex double zdotc = 0.0;
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += conj(Cd(&x[i])) * Cd(&y[i]);
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += conj(Cd(&x[i*incx])) * Cd(&y[i*incy]);
		}
	}
	pCd(z) = zdotc;
}	
static inline void cdotu_(complex *z, integer *n_, complex *x, integer *incx_, complex *y, integer *incy_) {
	integer n = *n_, incx = *incx_, incy = *incy_, i;
	_Complex float zdotc = 0.0;
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += Cf(&x[i]) * Cf(&y[i]);
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += Cf(&x[i*incx]) * Cf(&y[i*incy]);
		}
	}
	pCf(z) = zdotc;
}
static inline void zdotu_(doublecomplex *z, integer *n_, doublecomplex *x, integer *incx_, doublecomplex *y, integer *incy_) {
	integer n = *n_, incx = *incx_, incy = *incy_, i;
	_Complex double zdotc = 0.0;
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += Cd(&x[i]) * Cd(&y[i]);
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += Cd(&x[i*incx]) * Cd(&y[i*incy]);
		}
	}
	pCd(z) = zdotc;
}
#endif
/*  -- translated by f2c (version 20000121).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/



/* Table of constant values */

static integer c__1 = 1;

/* > \brief \b ZLAIC1 applies one step of incremental condition estimation. */

/*  =========== DOCUMENTATION =========== */

/* Online html documentation available at */
/*            http://www.netlib.org/lapack/explore-html/ */

/* > \htmlonly */
/* > Download ZLAIC1 + dependencies */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/zlaic1.
f"> */
/* > [TGZ]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/zlaic1.
f"> */
/* > [ZIP]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/zlaic1.
f"> */
/* > [TXT]</a> */
/* > \endhtmlonly */

/*  Definition: */
/*  =========== */

/*       SUBROUTINE ZLAIC1( JOB, J, X, SEST, W, GAMMA, SESTPR, S, C ) */

/*       INTEGER            J, JOB */
/*       DOUBLE PRECISION   SEST, SESTPR */
/*       COMPLEX*16         C, GAMMA, S */
/*       COMPLEX*16         W( J ), X( J ) */


/* > \par Purpose: */
/*  ============= */
/* > */
/* > \verbatim */
/* > */
/* > ZLAIC1 applies one step of incremental condition estimation in */
/* > its simplest version: */
/* > */
/* > Let x, twonorm(x) = 1, be an approximate singular vector of an j-by-j */
/* > lower triangular matrix L, such that */
/* >          twonorm(L*x) = sest */
/* > Then ZLAIC1 computes sestpr, s, c such that */
/* > the vector */
/* >                 [ s*x ] */
/* >          xhat = [  c  ] */
/* > is an approximate singular vector of */
/* >                 [ L       0  ] */
/* >          Lhat = [ w**H gamma ] */
/* > in the sense that */
/* >          twonorm(Lhat*xhat) = sestpr. */
/* > */
/* > Depending on JOB, an estimate for the largest or smallest singular */
/* > value is computed. */
/* > */
/* > Note that [s c]**H and sestpr**2 is an eigenpair of the system */
/* > */
/* >     diag(sest*sest, 0) + [alpha  gamma] * [ conjg(alpha) ] */
/* >                                           [ conjg(gamma) ] */
/* > */
/* > where  alpha =  x**H * w. */
/* > \endverbatim */

/*  Arguments: */
/*  ========== */

/* > \param[in] JOB */
/* > \verbatim */
/* >          JOB is INTEGER */
/* >          = 1: an estimate for the largest singular value is computed. */
/* >          = 2: an estimate for the smallest singular value is computed. */
/* > \endverbatim */
/* > */
/* > \param[in] J */
/* > \verbatim */
/* >          J is INTEGER */
/* >          Length of X and W */
/* > \endverbatim */
/* > */
/* > \param[in] X */
/* > \verbatim */
/* >          X is COMPLEX*16 array, dimension (J) */
/* >          The j-vector x. */
/* > \endverbatim */
/* > */
/* > \param[in] SEST */
/* > \verbatim */
/* >          SEST is DOUBLE PRECISION */
/* >          Estimated singular value of j by j matrix L */
/* > \endverbatim */
/* > */
/* > \param[in] W */
/* > \verbatim */
/* >          W is COMPLEX*16 array, dimension (J) */
/* >          The j-vector w. */
/* > \endverbatim */
/* > */
/* > \param[in] GAMMA */
/* > \verbatim */
/* >          GAMMA is COMPLEX*16 */
/* >          The diagonal element gamma. */
/* > \endverbatim */
/* > */
/* > \param[out] SESTPR */
/* > \verbatim */
/* >          SESTPR is DOUBLE PRECISION */
/* >          Estimated singular value of (j+1) by (j+1) matrix Lhat. */
/* > \endverbatim */
/* > */
/* > \param[out] S */
/* > \verbatim */
/* >          S is COMPLEX*16 */
/* >          Sine needed in forming xhat. */
/* > \endverbatim */
/* > */
/* > \param[out] C */
/* > \verbatim */
/* >          C is COMPLEX*16 */
/* >          Cosine needed in forming xhat. */
/* > \endverbatim */

/*  Authors: */
/*  ======== */

/* > \author Univ. of Tennessee */
/* > \author Univ. of California Berkeley */
/* > \author Univ. of Colorado Denver */
/* > \author NAG Ltd. */

/* > \date December 2016 */

/* > \ingroup complex16OTHERauxiliary */

/*  ===================================================================== */
/* Subroutine */ int zlaic1_(integer *job, integer *j, doublecomplex *x, 
	doublereal *sest, doublecomplex *w, doublecomplex *gamma, doublereal *
	sestpr, doublecomplex *s, doublecomplex *c__)
{
    /* System generated locals */
    doublereal d__1, d__2;
    doublecomplex z__1, z__2, z__3, z__4, z__5, z__6;

    /* Local variables */
    doublecomplex sine;
    doublereal test, zeta1, zeta2, b, t;
    doublecomplex alpha;
    doublereal norma;
    extern /* Double Complex */ VOID zdotc_(doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    doublereal s1, s2;
    extern doublereal dlamch_(char *);
    doublereal absgam, absalp;
    doublecomplex cosine;
    doublereal absest, scl, eps, tmp;


/*  -- LAPACK auxiliary routine (version 3.7.0) -- */
/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
/*     December 2016 */


/*  ===================================================================== */


    /* Parameter adjustments */
    --w;
    --x;

    /* Function Body */
    eps = dlamch_("Epsilon");
    zdotc_(&z__1, j, &x[1], &c__1, &w[1], &c__1);
    alpha.r = z__1.r, alpha.i = z__1.i;

    absalp = z_abs(&alpha);
    absgam = z_abs(gamma);
    absest = abs(*sest);

    if (*job == 1) {

/*        Estimating largest singular value */

/*        special cases */

	if (*sest == 0.) {
	    s1 = f2cmax(absgam,absalp);
	    if (s1 == 0.) {
		s->r = 0., s->i = 0.;
		c__->r = 1., c__->i = 0.;
		*sestpr = 0.;
	    } else {
		z__1.r = alpha.r / s1, z__1.i = alpha.i / s1;
		s->r = z__1.r, s->i = z__1.i;
		z__1.r = gamma->r / s1, z__1.i = gamma->i / s1;
		c__->r = z__1.r, c__->i = z__1.i;
		d_cnjg(&z__4, s);
		z__3.r = s->r * z__4.r - s->i * z__4.i, z__3.i = s->r * 
			z__4.i + s->i * z__4.r;
		d_cnjg(&z__6, c__);
		z__5.r = c__->r * z__6.r - c__->i * z__6.i, z__5.i = c__->r * 
			z__6.i + c__->i * z__6.r;
		z__2.r = z__3.r + z__5.r, z__2.i = z__3.i + z__5.i;
		z_sqrt(&z__1, &z__2);
		tmp = z__1.r;
		z__1.r = s->r / tmp, z__1.i = s->i / tmp;
		s->r = z__1.r, s->i = z__1.i;
		z__1.r = c__->r / tmp, z__1.i = c__->i / tmp;
		c__->r = z__1.r, c__->i = z__1.i;
		*sestpr = s1 * tmp;
	    }
	    return 0;
	} else if (absgam <= eps * absest) {
	    s->r = 1., s->i = 0.;
	    c__->r = 0., c__->i = 0.;
	    tmp = f2cmax(absest,absalp);
	    s1 = absest / tmp;
	    s2 = absalp / tmp;
	    *sestpr = tmp * sqrt(s1 * s1 + s2 * s2);
	    return 0;
	} else if (absalp <= eps * absest) {
	    s1 = absgam;
	    s2 = absest;
	    if (s1 <= s2) {
		s->r = 1., s->i = 0.;
		c__->r = 0., c__->i = 0.;
		*sestpr = s2;
	    } else {
		s->r = 0., s->i = 0.;
		c__->r = 1., c__->i = 0.;
		*sestpr = s1;
	    }
	    return 0;
	} else if (absest <= eps * absalp || absest <= eps * absgam) {
	    s1 = absgam;
	    s2 = absalp;
	    if (s1 <= s2) {
		tmp = s1 / s2;
		scl = sqrt(tmp * tmp + 1.);
		*sestpr = s2 * scl;
		z__2.r = alpha.r / s2, z__2.i = alpha.i / s2;
		z__1.r = z__2.r / scl, z__1.i = z__2.i / scl;
		s->r = z__1.r, s->i = z__1.i;
		z__2.r = gamma->r / s2, z__2.i = gamma->i / s2;
		z__1.r = z__2.r / scl, z__1.i = z__2.i / scl;
		c__->r = z__1.r, c__->i = z__1.i;
	    } else {
		tmp = s2 / s1;
		scl = sqrt(tmp * tmp + 1.);
		*sestpr = s1 * scl;
		z__2.r = alpha.r / s1, z__2.i = alpha.i / s1;
		z__1.r = z__2.r / scl, z__1.i = z__2.i / scl;
		s->r = z__1.r, s->i = z__1.i;
		z__2.r = gamma->r / s1, z__2.i = gamma->i / s1;
		z__1.r = z__2.r / scl, z__1.i = z__2.i / scl;
		c__->r = z__1.r, c__->i = z__1.i;
	    }
	    return 0;
	} else {

/*           normal case */

	    zeta1 = absalp / absest;
	    zeta2 = absgam / absest;

	    b = (1. - zeta1 * zeta1 - zeta2 * zeta2) * .5;
	    d__1 = zeta1 * zeta1;
	    c__->r = d__1, c__->i = 0.;
	    if (b > 0.) {
		d__1 = b * b;
		z__4.r = d__1 + c__->r, z__4.i = c__->i;
		z_sqrt(&z__3, &z__4);
		z__2.r = b + z__3.r, z__2.i = z__3.i;
		z_div(&z__1, c__, &z__2);
		t = z__1.r;
	    } else {
		d__1 = b * b;
		z__3.r = d__1 + c__->r, z__3.i = c__->i;
		z_sqrt(&z__2, &z__3);
		z__1.r = z__2.r - b, z__1.i = z__2.i;
		t = z__1.r;
	    }

	    z__3.r = alpha.r / absest, z__3.i = alpha.i / absest;
	    z__2.r = -z__3.r, z__2.i = -z__3.i;
	    z__1.r = z__2.r / t, z__1.i = z__2.i / t;
	    sine.r = z__1.r, sine.i = z__1.i;
	    z__3.r = gamma->r / absest, z__3.i = gamma->i / absest;
	    z__2.r = -z__3.r, z__2.i = -z__3.i;
	    d__1 = t + 1.;
	    z__1.r = z__2.r / d__1, z__1.i = z__2.i / d__1;
	    cosine.r = z__1.r, cosine.i = z__1.i;
	    d_cnjg(&z__4, &sine);
	    z__3.r = sine.r * z__4.r - sine.i * z__4.i, z__3.i = sine.r * 
		    z__4.i + sine.i * z__4.r;
	    d_cnjg(&z__6, &cosine);
	    z__5.r = cosine.r * z__6.r - cosine.i * z__6.i, z__5.i = cosine.r 
		    * z__6.i + cosine.i * z__6.r;
	    z__2.r = z__3.r + z__5.r, z__2.i = z__3.i + z__5.i;
	    z_sqrt(&z__1, &z__2);
	    tmp = z__1.r;
	    z__1.r = sine.r / tmp, z__1.i = sine.i / tmp;
	    s->r = z__1.r, s->i = z__1.i;
	    z__1.r = cosine.r / tmp, z__1.i = cosine.i / tmp;
	    c__->r = z__1.r, c__->i = z__1.i;
	    *sestpr = sqrt(t + 1.) * absest;
	    return 0;
	}

    } else if (*job == 2) {

/*        Estimating smallest singular value */

/*        special cases */

	if (*sest == 0.) {
	    *sestpr = 0.;
	    if (f2cmax(absgam,absalp) == 0.) {
		sine.r = 1., sine.i = 0.;
		cosine.r = 0., cosine.i = 0.;
	    } else {
		d_cnjg(&z__2, gamma);
		z__1.r = -z__2.r, z__1.i = -z__2.i;
		sine.r = z__1.r, sine.i = z__1.i;
		d_cnjg(&z__1, &alpha);
		cosine.r = z__1.r, cosine.i = z__1.i;
	    }
/* Computing MAX */
	    d__1 = z_abs(&sine), d__2 = z_abs(&cosine);
	    s1 = f2cmax(d__1,d__2);
	    z__1.r = sine.r / s1, z__1.i = sine.i / s1;
	    s->r = z__1.r, s->i = z__1.i;
	    z__1.r = cosine.r / s1, z__1.i = cosine.i / s1;
	    c__->r = z__1.r, c__->i = z__1.i;
	    d_cnjg(&z__4, s);
	    z__3.r = s->r * z__4.r - s->i * z__4.i, z__3.i = s->r * z__4.i + 
		    s->i * z__4.r;
	    d_cnjg(&z__6, c__);
	    z__5.r = c__->r * z__6.r - c__->i * z__6.i, z__5.i = c__->r * 
		    z__6.i + c__->i * z__6.r;
	    z__2.r = z__3.r + z__5.r, z__2.i = z__3.i + z__5.i;
	    z_sqrt(&z__1, &z__2);
	    tmp = z__1.r;
	    z__1.r = s->r / tmp, z__1.i = s->i / tmp;
	    s->r = z__1.r, s->i = z__1.i;
	    z__1.r = c__->r / tmp, z__1.i = c__->i / tmp;
	    c__->r = z__1.r, c__->i = z__1.i;
	    return 0;
	} else if (absgam <= eps * absest) {
	    s->r = 0., s->i = 0.;
	    c__->r = 1., c__->i = 0.;
	    *sestpr = absgam;
	    return 0;
	} else if (absalp <= eps * absest) {
	    s1 = absgam;
	    s2 = absest;
	    if (s1 <= s2) {
		s->r = 0., s->i = 0.;
		c__->r = 1., c__->i = 0.;
		*sestpr = s1;
	    } else {
		s->r = 1., s->i = 0.;
		c__->r = 0., c__->i = 0.;
		*sestpr = s2;
	    }
	    return 0;
	} else if (absest <= eps * absalp || absest <= eps * absgam) {
	    s1 = absgam;
	    s2 = absalp;
	    if (s1 <= s2) {
		tmp = s1 / s2;
		scl = sqrt(tmp * tmp + 1.);
		*sestpr = absest * (tmp / scl);
		d_cnjg(&z__4, gamma);
		z__3.r = z__4.r / s2, z__3.i = z__4.i / s2;
		z__2.r = -z__3.r, z__2.i = -z__3.i;
		z__1.r = z__2.r / scl, z__1.i = z__2.i / scl;
		s->r = z__1.r, s->i = z__1.i;
		d_cnjg(&z__3, &alpha);
		z__2.r = z__3.r / s2, z__2.i = z__3.i / s2;
		z__1.r = z__2.r / scl, z__1.i = z__2.i / scl;
		c__->r = z__1.r, c__->i = z__1.i;
	    } else {
		tmp = s2 / s1;
		scl = sqrt(tmp * tmp + 1.);
		*sestpr = absest / scl;
		d_cnjg(&z__4, gamma);
		z__3.r = z__4.r / s1, z__3.i = z__4.i / s1;
		z__2.r = -z__3.r, z__2.i = -z__3.i;
		z__1.r = z__2.r / scl, z__1.i = z__2.i / scl;
		s->r = z__1.r, s->i = z__1.i;
		d_cnjg(&z__3, &alpha);
		z__2.r = z__3.r / s1, z__2.i = z__3.i / s1;
		z__1.r = z__2.r / scl, z__1.i = z__2.i / scl;
		c__->r = z__1.r, c__->i = z__1.i;
	    }
	    return 0;
	} else {

/*           normal case */

	    zeta1 = absalp / absest;
	    zeta2 = absgam / absest;

/* Computing MAX */
	    d__1 = zeta1 * zeta1 + 1. + zeta1 * zeta2, d__2 = zeta1 * zeta2 + 
		    zeta2 * zeta2;
	    norma = f2cmax(d__1,d__2);

/*           See if root is closer to zero or to ONE */

	    test = (zeta1 - zeta2) * 2. * (zeta1 + zeta2) + 1.;
	    if (test >= 0.) {

/*              root is close to zero, compute directly */

		b = (zeta1 * zeta1 + zeta2 * zeta2 + 1.) * .5;
		d__1 = zeta2 * zeta2;
		c__->r = d__1, c__->i = 0.;
		d__2 = b * b;
		z__2.r = d__2 - c__->r, z__2.i = -c__->i;
		d__1 = b + sqrt(z_abs(&z__2));
		z__1.r = c__->r / d__1, z__1.i = c__->i / d__1;
		t = z__1.r;
		z__2.r = alpha.r / absest, z__2.i = alpha.i / absest;
		d__1 = 1. - t;
		z__1.r = z__2.r / d__1, z__1.i = z__2.i / d__1;
		sine.r = z__1.r, sine.i = z__1.i;
		z__3.r = gamma->r / absest, z__3.i = gamma->i / absest;
		z__2.r = -z__3.r, z__2.i = -z__3.i;
		z__1.r = z__2.r / t, z__1.i = z__2.i / t;
		cosine.r = z__1.r, cosine.i = z__1.i;
		*sestpr = sqrt(t + eps * 4. * eps * norma) * absest;
	    } else {

/*              root is closer to ONE, shift by that amount */

		b = (zeta2 * zeta2 + zeta1 * zeta1 - 1.) * .5;
		d__1 = zeta1 * zeta1;
		c__->r = d__1, c__->i = 0.;
		if (b >= 0.) {
		    z__2.r = -c__->r, z__2.i = -c__->i;
		    d__1 = b * b;
		    z__5.r = d__1 + c__->r, z__5.i = c__->i;
		    z_sqrt(&z__4, &z__5);
		    z__3.r = b + z__4.r, z__3.i = z__4.i;
		    z_div(&z__1, &z__2, &z__3);
		    t = z__1.r;
		} else {
		    d__1 = b * b;
		    z__3.r = d__1 + c__->r, z__3.i = c__->i;
		    z_sqrt(&z__2, &z__3);
		    z__1.r = b - z__2.r, z__1.i = -z__2.i;
		    t = z__1.r;
		}
		z__3.r = alpha.r / absest, z__3.i = alpha.i / absest;
		z__2.r = -z__3.r, z__2.i = -z__3.i;
		z__1.r = z__2.r / t, z__1.i = z__2.i / t;
		sine.r = z__1.r, sine.i = z__1.i;
		z__3.r = gamma->r / absest, z__3.i = gamma->i / absest;
		z__2.r = -z__3.r, z__2.i = -z__3.i;
		d__1 = t + 1.;
		z__1.r = z__2.r / d__1, z__1.i = z__2.i / d__1;
		cosine.r = z__1.r, cosine.i = z__1.i;
		*sestpr = sqrt(t + 1. + eps * 4. * eps * norma) * absest;
	    }
	    d_cnjg(&z__4, &sine);
	    z__3.r = sine.r * z__4.r - sine.i * z__4.i, z__3.i = sine.r * 
		    z__4.i + sine.i * z__4.r;
	    d_cnjg(&z__6, &cosine);
	    z__5.r = cosine.r * z__6.r - cosine.i * z__6.i, z__5.i = cosine.r 
		    * z__6.i + cosine.i * z__6.r;
	    z__2.r = z__3.r + z__5.r, z__2.i = z__3.i + z__5.i;
	    z_sqrt(&z__1, &z__2);
	    tmp = z__1.r;
	    z__1.r = sine.r / tmp, z__1.i = sine.i / tmp;
	    s->r = z__1.r, s->i = z__1.i;
	    z__1.r = cosine.r / tmp, z__1.i = cosine.i / tmp;
	    c__->r = z__1.r, c__->i = z__1.i;
	    return 0;

	}
    }
    return 0;

/*     End of ZLAIC1 */

} /* zlaic1_ */

