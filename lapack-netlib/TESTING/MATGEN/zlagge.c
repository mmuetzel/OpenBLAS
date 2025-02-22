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
#define mycycle_() continue;
#define myceiling_(w) ceil(w)
#define myhuge_(w) HUGE_VAL
//#define mymaxloc_(w,s,e,n) {if (sizeof(*(w)) == sizeof(double)) dmaxloc_((w),*(s),*(e),n); else dmaxloc_((w),*(s),*(e),n);}
#define mymaxloc_(w,s,e,n) dmaxloc_(w,*(s),*(e),n)

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

static doublecomplex c_b1 = {0.,0.};
static doublecomplex c_b2 = {1.,0.};
static integer c__3 = 3;
static integer c__1 = 1;

/* > \brief \b ZLAGGE */

/*  =========== DOCUMENTATION =========== */

/* Online html documentation available at */
/*            http://www.netlib.org/lapack/explore-html/ */

/*  Definition: */
/*  =========== */

/*       SUBROUTINE ZLAGGE( M, N, KL, KU, D, A, LDA, ISEED, WORK, INFO ) */

/*       INTEGER            INFO, KL, KU, LDA, M, N */
/*       INTEGER            ISEED( 4 ) */
/*       DOUBLE PRECISION   D( * ) */
/*       COMPLEX*16         A( LDA, * ), WORK( * ) */


/* > \par Purpose: */
/*  ============= */
/* > */
/* > \verbatim */
/* > */
/* > ZLAGGE generates a complex general m by n matrix A, by pre- and post- */
/* > multiplying a real diagonal matrix D with random unitary matrices: */
/* > A = U*D*V. The lower and upper bandwidths may then be reduced to */
/* > kl and ku by additional unitary transformations. */
/* > \endverbatim */

/*  Arguments: */
/*  ========== */

/* > \param[in] M */
/* > \verbatim */
/* >          M is INTEGER */
/* >          The number of rows of the matrix A.  M >= 0. */
/* > \endverbatim */
/* > */
/* > \param[in] N */
/* > \verbatim */
/* >          N is INTEGER */
/* >          The number of columns of the matrix A.  N >= 0. */
/* > \endverbatim */
/* > */
/* > \param[in] KL */
/* > \verbatim */
/* >          KL is INTEGER */
/* >          The number of nonzero subdiagonals within the band of A. */
/* >          0 <= KL <= M-1. */
/* > \endverbatim */
/* > */
/* > \param[in] KU */
/* > \verbatim */
/* >          KU is INTEGER */
/* >          The number of nonzero superdiagonals within the band of A. */
/* >          0 <= KU <= N-1. */
/* > \endverbatim */
/* > */
/* > \param[in] D */
/* > \verbatim */
/* >          D is DOUBLE PRECISION array, dimension (f2cmin(M,N)) */
/* >          The diagonal elements of the diagonal matrix D. */
/* > \endverbatim */
/* > */
/* > \param[out] A */
/* > \verbatim */
/* >          A is COMPLEX*16 array, dimension (LDA,N) */
/* >          The generated m by n matrix A. */
/* > \endverbatim */
/* > */
/* > \param[in] LDA */
/* > \verbatim */
/* >          LDA is INTEGER */
/* >          The leading dimension of the array A.  LDA >= M. */
/* > \endverbatim */
/* > */
/* > \param[in,out] ISEED */
/* > \verbatim */
/* >          ISEED is INTEGER array, dimension (4) */
/* >          On entry, the seed of the random number generator; the array */
/* >          elements must be between 0 and 4095, and ISEED(4) must be */
/* >          odd. */
/* >          On exit, the seed is updated. */
/* > \endverbatim */
/* > */
/* > \param[out] WORK */
/* > \verbatim */
/* >          WORK is COMPLEX*16 array, dimension (M+N) */
/* > \endverbatim */
/* > */
/* > \param[out] INFO */
/* > \verbatim */
/* >          INFO is INTEGER */
/* >          = 0: successful exit */
/* >          < 0: if INFO = -i, the i-th argument had an illegal value */
/* > \endverbatim */

/*  Authors: */
/*  ======== */

/* > \author Univ. of Tennessee */
/* > \author Univ. of California Berkeley */
/* > \author Univ. of Colorado Denver */
/* > \author NAG Ltd. */

/* > \date December 2016 */

/* > \ingroup complex16_matgen */

/*  ===================================================================== */
/* Subroutine */ int zlagge_(integer *m, integer *n, integer *kl, integer *ku,
	 doublereal *d__, doublecomplex *a, integer *lda, integer *iseed, 
	doublecomplex *work, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    doublereal d__1;
    doublecomplex z__1;

    /* Local variables */
    integer i__, j;
    extern /* Subroutine */ int zgerc_(integer *, integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *), zscal_(integer *, doublecomplex *, 
	    doublecomplex *, integer *), zgemv_(char *, integer *, integer *, 
	    doublecomplex *, doublecomplex *, integer *, doublecomplex *, 
	    integer *, doublecomplex *, doublecomplex *, integer *);
    extern doublereal dznrm2_(integer *, doublecomplex *, integer *);
    doublecomplex wa, wb;
    doublereal wn;
    extern /* Subroutine */ int xerbla_(char *, integer *), zlacgv_(
	    integer *, doublecomplex *, integer *), zlarnv_(integer *, 
	    integer *, integer *, doublecomplex *);
    doublecomplex tau;


/*  -- LAPACK auxiliary routine (version 3.7.0) -- */
/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
/*     December 2016 */


/*  ===================================================================== */


/*     Test the input arguments */

    /* Parameter adjustments */
    --d__;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --iseed;
    --work;

    /* Function Body */
    *info = 0;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*kl < 0 || *kl > *m - 1) {
	*info = -3;
    } else if (*ku < 0 || *ku > *n - 1) {
	*info = -4;
    } else if (*lda < f2cmax(1,*m)) {
	*info = -7;
    }
    if (*info < 0) {
	i__1 = -(*info);
	xerbla_("ZLAGGE", &i__1);
	return 0;
    }

/*     initialize A to diagonal matrix */

    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = i__ + j * a_dim1;
	    a[i__3].r = 0., a[i__3].i = 0.;
/* L10: */
	}
/* L20: */
    }
    i__1 = f2cmin(*m,*n);
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = i__ + i__ * a_dim1;
	i__3 = i__;
	a[i__2].r = d__[i__3], a[i__2].i = 0.;
/* L30: */
    }

/*     Quick exit if the user wants a diagonal matrix */

    if (*kl == 0 && *ku == 0) {
	return 0;
    }

/*     pre- and post-multiply A by random unitary matrices */

    for (i__ = f2cmin(*m,*n); i__ >= 1; --i__) {
	if (i__ < *m) {

/*           generate random reflection */

	    i__1 = *m - i__ + 1;
	    zlarnv_(&c__3, &iseed[1], &i__1, &work[1]);
	    i__1 = *m - i__ + 1;
	    wn = dznrm2_(&i__1, &work[1], &c__1);
	    d__1 = wn / z_abs(&work[1]);
	    z__1.r = d__1 * work[1].r, z__1.i = d__1 * work[1].i;
	    wa.r = z__1.r, wa.i = z__1.i;
	    if (wn == 0.) {
		tau.r = 0., tau.i = 0.;
	    } else {
		z__1.r = work[1].r + wa.r, z__1.i = work[1].i + wa.i;
		wb.r = z__1.r, wb.i = z__1.i;
		i__1 = *m - i__;
		z_div(&z__1, &c_b2, &wb);
		zscal_(&i__1, &z__1, &work[2], &c__1);
		work[1].r = 1., work[1].i = 0.;
		z_div(&z__1, &wb, &wa);
		d__1 = z__1.r;
		tau.r = d__1, tau.i = 0.;
	    }

/*           multiply A(i:m,i:n) by random reflection from the left */

	    i__1 = *m - i__ + 1;
	    i__2 = *n - i__ + 1;
	    zgemv_("Conjugate transpose", &i__1, &i__2, &c_b2, &a[i__ + i__ * 
		    a_dim1], lda, &work[1], &c__1, &c_b1, &work[*m + 1], &
		    c__1);
	    i__1 = *m - i__ + 1;
	    i__2 = *n - i__ + 1;
	    z__1.r = -tau.r, z__1.i = -tau.i;
	    zgerc_(&i__1, &i__2, &z__1, &work[1], &c__1, &work[*m + 1], &c__1,
		     &a[i__ + i__ * a_dim1], lda);
	}
	if (i__ < *n) {

/*           generate random reflection */

	    i__1 = *n - i__ + 1;
	    zlarnv_(&c__3, &iseed[1], &i__1, &work[1]);
	    i__1 = *n - i__ + 1;
	    wn = dznrm2_(&i__1, &work[1], &c__1);
	    d__1 = wn / z_abs(&work[1]);
	    z__1.r = d__1 * work[1].r, z__1.i = d__1 * work[1].i;
	    wa.r = z__1.r, wa.i = z__1.i;
	    if (wn == 0.) {
		tau.r = 0., tau.i = 0.;
	    } else {
		z__1.r = work[1].r + wa.r, z__1.i = work[1].i + wa.i;
		wb.r = z__1.r, wb.i = z__1.i;
		i__1 = *n - i__;
		z_div(&z__1, &c_b2, &wb);
		zscal_(&i__1, &z__1, &work[2], &c__1);
		work[1].r = 1., work[1].i = 0.;
		z_div(&z__1, &wb, &wa);
		d__1 = z__1.r;
		tau.r = d__1, tau.i = 0.;
	    }

/*           multiply A(i:m,i:n) by random reflection from the right */

	    i__1 = *m - i__ + 1;
	    i__2 = *n - i__ + 1;
	    zgemv_("No transpose", &i__1, &i__2, &c_b2, &a[i__ + i__ * a_dim1]
		    , lda, &work[1], &c__1, &c_b1, &work[*n + 1], &c__1);
	    i__1 = *m - i__ + 1;
	    i__2 = *n - i__ + 1;
	    z__1.r = -tau.r, z__1.i = -tau.i;
	    zgerc_(&i__1, &i__2, &z__1, &work[*n + 1], &c__1, &work[1], &c__1,
		     &a[i__ + i__ * a_dim1], lda);
	}
/* L40: */
    }

/*     Reduce number of subdiagonals to KL and number of superdiagonals */
/*     to KU */

/* Computing MAX */
    i__2 = *m - 1 - *kl, i__3 = *n - 1 - *ku;
    i__1 = f2cmax(i__2,i__3);
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (*kl <= *ku) {

/*           annihilate subdiagonal elements first (necessary if KL = 0) */

/* Computing MIN */
	    i__2 = *m - 1 - *kl;
	    if (i__ <= f2cmin(i__2,*n)) {

/*              generate reflection to annihilate A(kl+i+1:m,i) */

		i__2 = *m - *kl - i__ + 1;
		wn = dznrm2_(&i__2, &a[*kl + i__ + i__ * a_dim1], &c__1);
		d__1 = wn / z_abs(&a[*kl + i__ + i__ * a_dim1]);
		i__2 = *kl + i__ + i__ * a_dim1;
		z__1.r = d__1 * a[i__2].r, z__1.i = d__1 * a[i__2].i;
		wa.r = z__1.r, wa.i = z__1.i;
		if (wn == 0.) {
		    tau.r = 0., tau.i = 0.;
		} else {
		    i__2 = *kl + i__ + i__ * a_dim1;
		    z__1.r = a[i__2].r + wa.r, z__1.i = a[i__2].i + wa.i;
		    wb.r = z__1.r, wb.i = z__1.i;
		    i__2 = *m - *kl - i__;
		    z_div(&z__1, &c_b2, &wb);
		    zscal_(&i__2, &z__1, &a[*kl + i__ + 1 + i__ * a_dim1], &
			    c__1);
		    i__2 = *kl + i__ + i__ * a_dim1;
		    a[i__2].r = 1., a[i__2].i = 0.;
		    z_div(&z__1, &wb, &wa);
		    d__1 = z__1.r;
		    tau.r = d__1, tau.i = 0.;
		}

/*              apply reflection to A(kl+i:m,i+1:n) from the left */

		i__2 = *m - *kl - i__ + 1;
		i__3 = *n - i__;
		zgemv_("Conjugate transpose", &i__2, &i__3, &c_b2, &a[*kl + 
			i__ + (i__ + 1) * a_dim1], lda, &a[*kl + i__ + i__ * 
			a_dim1], &c__1, &c_b1, &work[1], &c__1);
		i__2 = *m - *kl - i__ + 1;
		i__3 = *n - i__;
		z__1.r = -tau.r, z__1.i = -tau.i;
		zgerc_(&i__2, &i__3, &z__1, &a[*kl + i__ + i__ * a_dim1], &
			c__1, &work[1], &c__1, &a[*kl + i__ + (i__ + 1) * 
			a_dim1], lda);
		i__2 = *kl + i__ + i__ * a_dim1;
		z__1.r = -wa.r, z__1.i = -wa.i;
		a[i__2].r = z__1.r, a[i__2].i = z__1.i;
	    }

/* Computing MIN */
	    i__2 = *n - 1 - *ku;
	    if (i__ <= f2cmin(i__2,*m)) {

/*              generate reflection to annihilate A(i,ku+i+1:n) */

		i__2 = *n - *ku - i__ + 1;
		wn = dznrm2_(&i__2, &a[i__ + (*ku + i__) * a_dim1], lda);
		d__1 = wn / z_abs(&a[i__ + (*ku + i__) * a_dim1]);
		i__2 = i__ + (*ku + i__) * a_dim1;
		z__1.r = d__1 * a[i__2].r, z__1.i = d__1 * a[i__2].i;
		wa.r = z__1.r, wa.i = z__1.i;
		if (wn == 0.) {
		    tau.r = 0., tau.i = 0.;
		} else {
		    i__2 = i__ + (*ku + i__) * a_dim1;
		    z__1.r = a[i__2].r + wa.r, z__1.i = a[i__2].i + wa.i;
		    wb.r = z__1.r, wb.i = z__1.i;
		    i__2 = *n - *ku - i__;
		    z_div(&z__1, &c_b2, &wb);
		    zscal_(&i__2, &z__1, &a[i__ + (*ku + i__ + 1) * a_dim1], 
			    lda);
		    i__2 = i__ + (*ku + i__) * a_dim1;
		    a[i__2].r = 1., a[i__2].i = 0.;
		    z_div(&z__1, &wb, &wa);
		    d__1 = z__1.r;
		    tau.r = d__1, tau.i = 0.;
		}

/*              apply reflection to A(i+1:m,ku+i:n) from the right */

		i__2 = *n - *ku - i__ + 1;
		zlacgv_(&i__2, &a[i__ + (*ku + i__) * a_dim1], lda);
		i__2 = *m - i__;
		i__3 = *n - *ku - i__ + 1;
		zgemv_("No transpose", &i__2, &i__3, &c_b2, &a[i__ + 1 + (*ku 
			+ i__) * a_dim1], lda, &a[i__ + (*ku + i__) * a_dim1],
			 lda, &c_b1, &work[1], &c__1);
		i__2 = *m - i__;
		i__3 = *n - *ku - i__ + 1;
		z__1.r = -tau.r, z__1.i = -tau.i;
		zgerc_(&i__2, &i__3, &z__1, &work[1], &c__1, &a[i__ + (*ku + 
			i__) * a_dim1], lda, &a[i__ + 1 + (*ku + i__) * 
			a_dim1], lda);
		i__2 = i__ + (*ku + i__) * a_dim1;
		z__1.r = -wa.r, z__1.i = -wa.i;
		a[i__2].r = z__1.r, a[i__2].i = z__1.i;
	    }
	} else {

/*           annihilate superdiagonal elements first (necessary if */
/*           KU = 0) */

/* Computing MIN */
	    i__2 = *n - 1 - *ku;
	    if (i__ <= f2cmin(i__2,*m)) {

/*              generate reflection to annihilate A(i,ku+i+1:n) */

		i__2 = *n - *ku - i__ + 1;
		wn = dznrm2_(&i__2, &a[i__ + (*ku + i__) * a_dim1], lda);
		d__1 = wn / z_abs(&a[i__ + (*ku + i__) * a_dim1]);
		i__2 = i__ + (*ku + i__) * a_dim1;
		z__1.r = d__1 * a[i__2].r, z__1.i = d__1 * a[i__2].i;
		wa.r = z__1.r, wa.i = z__1.i;
		if (wn == 0.) {
		    tau.r = 0., tau.i = 0.;
		} else {
		    i__2 = i__ + (*ku + i__) * a_dim1;
		    z__1.r = a[i__2].r + wa.r, z__1.i = a[i__2].i + wa.i;
		    wb.r = z__1.r, wb.i = z__1.i;
		    i__2 = *n - *ku - i__;
		    z_div(&z__1, &c_b2, &wb);
		    zscal_(&i__2, &z__1, &a[i__ + (*ku + i__ + 1) * a_dim1], 
			    lda);
		    i__2 = i__ + (*ku + i__) * a_dim1;
		    a[i__2].r = 1., a[i__2].i = 0.;
		    z_div(&z__1, &wb, &wa);
		    d__1 = z__1.r;
		    tau.r = d__1, tau.i = 0.;
		}

/*              apply reflection to A(i+1:m,ku+i:n) from the right */

		i__2 = *n - *ku - i__ + 1;
		zlacgv_(&i__2, &a[i__ + (*ku + i__) * a_dim1], lda);
		i__2 = *m - i__;
		i__3 = *n - *ku - i__ + 1;
		zgemv_("No transpose", &i__2, &i__3, &c_b2, &a[i__ + 1 + (*ku 
			+ i__) * a_dim1], lda, &a[i__ + (*ku + i__) * a_dim1],
			 lda, &c_b1, &work[1], &c__1);
		i__2 = *m - i__;
		i__3 = *n - *ku - i__ + 1;
		z__1.r = -tau.r, z__1.i = -tau.i;
		zgerc_(&i__2, &i__3, &z__1, &work[1], &c__1, &a[i__ + (*ku + 
			i__) * a_dim1], lda, &a[i__ + 1 + (*ku + i__) * 
			a_dim1], lda);
		i__2 = i__ + (*ku + i__) * a_dim1;
		z__1.r = -wa.r, z__1.i = -wa.i;
		a[i__2].r = z__1.r, a[i__2].i = z__1.i;
	    }

/* Computing MIN */
	    i__2 = *m - 1 - *kl;
	    if (i__ <= f2cmin(i__2,*n)) {

/*              generate reflection to annihilate A(kl+i+1:m,i) */

		i__2 = *m - *kl - i__ + 1;
		wn = dznrm2_(&i__2, &a[*kl + i__ + i__ * a_dim1], &c__1);
		d__1 = wn / z_abs(&a[*kl + i__ + i__ * a_dim1]);
		i__2 = *kl + i__ + i__ * a_dim1;
		z__1.r = d__1 * a[i__2].r, z__1.i = d__1 * a[i__2].i;
		wa.r = z__1.r, wa.i = z__1.i;
		if (wn == 0.) {
		    tau.r = 0., tau.i = 0.;
		} else {
		    i__2 = *kl + i__ + i__ * a_dim1;
		    z__1.r = a[i__2].r + wa.r, z__1.i = a[i__2].i + wa.i;
		    wb.r = z__1.r, wb.i = z__1.i;
		    i__2 = *m - *kl - i__;
		    z_div(&z__1, &c_b2, &wb);
		    zscal_(&i__2, &z__1, &a[*kl + i__ + 1 + i__ * a_dim1], &
			    c__1);
		    i__2 = *kl + i__ + i__ * a_dim1;
		    a[i__2].r = 1., a[i__2].i = 0.;
		    z_div(&z__1, &wb, &wa);
		    d__1 = z__1.r;
		    tau.r = d__1, tau.i = 0.;
		}

/*              apply reflection to A(kl+i:m,i+1:n) from the left */

		i__2 = *m - *kl - i__ + 1;
		i__3 = *n - i__;
		zgemv_("Conjugate transpose", &i__2, &i__3, &c_b2, &a[*kl + 
			i__ + (i__ + 1) * a_dim1], lda, &a[*kl + i__ + i__ * 
			a_dim1], &c__1, &c_b1, &work[1], &c__1);
		i__2 = *m - *kl - i__ + 1;
		i__3 = *n - i__;
		z__1.r = -tau.r, z__1.i = -tau.i;
		zgerc_(&i__2, &i__3, &z__1, &a[*kl + i__ + i__ * a_dim1], &
			c__1, &work[1], &c__1, &a[*kl + i__ + (i__ + 1) * 
			a_dim1], lda);
		i__2 = *kl + i__ + i__ * a_dim1;
		z__1.r = -wa.r, z__1.i = -wa.i;
		a[i__2].r = z__1.r, a[i__2].i = z__1.i;
	    }
	}

	if (i__ <= *n) {
	    i__2 = *m;
	    for (j = *kl + i__ + 1; j <= i__2; ++j) {
		i__3 = j + i__ * a_dim1;
		a[i__3].r = 0., a[i__3].i = 0.;
/* L50: */
	    }
	}

	if (i__ <= *m) {
	    i__2 = *n;
	    for (j = *ku + i__ + 1; j <= i__2; ++j) {
		i__3 = i__ + j * a_dim1;
		a[i__3].r = 0., a[i__3].i = 0.;
/* L60: */
	    }
	}
/* L70: */
    }
    return 0;

/*     End of ZLAGGE */

} /* zlagge_ */

