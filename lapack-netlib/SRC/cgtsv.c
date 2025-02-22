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



/* > \brief <b> CGTSV computes the solution to system of linear equations A * X = B for GT matrices </b> */

/*  =========== DOCUMENTATION =========== */

/* Online html documentation available at */
/*            http://www.netlib.org/lapack/explore-html/ */

/* > \htmlonly */
/* > Download CGTSV + dependencies */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/cgtsv.f
"> */
/* > [TGZ]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/cgtsv.f
"> */
/* > [ZIP]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/cgtsv.f
"> */
/* > [TXT]</a> */
/* > \endhtmlonly */

/*  Definition: */
/*  =========== */

/*       SUBROUTINE CGTSV( N, NRHS, DL, D, DU, B, LDB, INFO ) */

/*       INTEGER            INFO, LDB, N, NRHS */
/*       COMPLEX            B( LDB, * ), D( * ), DL( * ), DU( * ) */


/* > \par Purpose: */
/*  ============= */
/* > */
/* > \verbatim */
/* > */
/* > CGTSV  solves the equation */
/* > */
/* >    A*X = B, */
/* > */
/* > where A is an N-by-N tridiagonal matrix, by Gaussian elimination with */
/* > partial pivoting. */
/* > */
/* > Note that the equation  A**T *X = B  may be solved by interchanging the */
/* > order of the arguments DU and DL. */
/* > \endverbatim */

/*  Arguments: */
/*  ========== */

/* > \param[in] N */
/* > \verbatim */
/* >          N is INTEGER */
/* >          The order of the matrix A.  N >= 0. */
/* > \endverbatim */
/* > */
/* > \param[in] NRHS */
/* > \verbatim */
/* >          NRHS is INTEGER */
/* >          The number of right hand sides, i.e., the number of columns */
/* >          of the matrix B.  NRHS >= 0. */
/* > \endverbatim */
/* > */
/* > \param[in,out] DL */
/* > \verbatim */
/* >          DL is COMPLEX array, dimension (N-1) */
/* >          On entry, DL must contain the (n-1) subdiagonal elements of */
/* >          A. */
/* >          On exit, DL is overwritten by the (n-2) elements of the */
/* >          second superdiagonal of the upper triangular matrix U from */
/* >          the LU factorization of A, in DL(1), ..., DL(n-2). */
/* > \endverbatim */
/* > */
/* > \param[in,out] D */
/* > \verbatim */
/* >          D is COMPLEX array, dimension (N) */
/* >          On entry, D must contain the diagonal elements of A. */
/* >          On exit, D is overwritten by the n diagonal elements of U. */
/* > \endverbatim */
/* > */
/* > \param[in,out] DU */
/* > \verbatim */
/* >          DU is COMPLEX array, dimension (N-1) */
/* >          On entry, DU must contain the (n-1) superdiagonal elements */
/* >          of A. */
/* >          On exit, DU is overwritten by the (n-1) elements of the first */
/* >          superdiagonal of U. */
/* > \endverbatim */
/* > */
/* > \param[in,out] B */
/* > \verbatim */
/* >          B is COMPLEX array, dimension (LDB,NRHS) */
/* >          On entry, the N-by-NRHS right hand side matrix B. */
/* >          On exit, if INFO = 0, the N-by-NRHS solution matrix X. */
/* > \endverbatim */
/* > */
/* > \param[in] LDB */
/* > \verbatim */
/* >          LDB is INTEGER */
/* >          The leading dimension of the array B.  LDB >= f2cmax(1,N). */
/* > \endverbatim */
/* > */
/* > \param[out] INFO */
/* > \verbatim */
/* >          INFO is INTEGER */
/* >          = 0:  successful exit */
/* >          < 0:  if INFO = -i, the i-th argument had an illegal value */
/* >          > 0:  if INFO = i, U(i,i) is exactly zero, and the solution */
/* >                has not been computed.  The factorization has not been */
/* >                completed unless i = N. */
/* > \endverbatim */

/*  Authors: */
/*  ======== */

/* > \author Univ. of Tennessee */
/* > \author Univ. of California Berkeley */
/* > \author Univ. of Colorado Denver */
/* > \author NAG Ltd. */

/* > \date December 2016 */

/* > \ingroup complexGTsolve */

/*  ===================================================================== */
/* Subroutine */ int cgtsv_(integer *n, integer *nrhs, complex *dl, complex *
	d__, complex *du, complex *b, integer *ldb, integer *info)
{
    /* System generated locals */
    integer b_dim1, b_offset, i__1, i__2, i__3, i__4, i__5, i__6, i__7;
    real r__1, r__2, r__3, r__4;
    complex q__1, q__2, q__3, q__4, q__5;

    /* Local variables */
    complex temp, mult;
    integer j, k;
    extern /* Subroutine */ int xerbla_(char *, integer *, ftnlen);


/*  -- LAPACK driver routine (version 3.7.0) -- */
/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
/*     December 2016 */


/*  ===================================================================== */


    /* Parameter adjustments */
    --dl;
    --d__;
    --du;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1 * 1;
    b -= b_offset;

    /* Function Body */
    *info = 0;
    if (*n < 0) {
	*info = -1;
    } else if (*nrhs < 0) {
	*info = -2;
    } else if (*ldb < f2cmax(1,*n)) {
	*info = -7;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("CGTSV ", &i__1, (ftnlen)6);
	return 0;
    }

    if (*n == 0) {
	return 0;
    }

    i__1 = *n - 1;
    for (k = 1; k <= i__1; ++k) {
	i__2 = k;
	if (dl[i__2].r == 0.f && dl[i__2].i == 0.f) {

/*           Subdiagonal is zero, no elimination is required. */

	    i__2 = k;
	    if (d__[i__2].r == 0.f && d__[i__2].i == 0.f) {

/*              Diagonal is zero: set INFO = K and return; a unique */
/*              solution can not be found. */

		*info = k;
		return 0;
	    }
	} else /* if(complicated condition) */ {
	    i__2 = k;
	    i__3 = k;
	    if ((r__1 = d__[i__2].r, abs(r__1)) + (r__2 = r_imag(&d__[k]), 
		    abs(r__2)) >= (r__3 = dl[i__3].r, abs(r__3)) + (r__4 = 
		    r_imag(&dl[k]), abs(r__4))) {

/*           No row interchange required */

		c_div(&q__1, &dl[k], &d__[k]);
		mult.r = q__1.r, mult.i = q__1.i;
		i__2 = k + 1;
		i__3 = k + 1;
		i__4 = k;
		q__2.r = mult.r * du[i__4].r - mult.i * du[i__4].i, q__2.i = 
			mult.r * du[i__4].i + mult.i * du[i__4].r;
		q__1.r = d__[i__3].r - q__2.r, q__1.i = d__[i__3].i - q__2.i;
		d__[i__2].r = q__1.r, d__[i__2].i = q__1.i;
		i__2 = *nrhs;
		for (j = 1; j <= i__2; ++j) {
		    i__3 = k + 1 + j * b_dim1;
		    i__4 = k + 1 + j * b_dim1;
		    i__5 = k + j * b_dim1;
		    q__2.r = mult.r * b[i__5].r - mult.i * b[i__5].i, q__2.i =
			     mult.r * b[i__5].i + mult.i * b[i__5].r;
		    q__1.r = b[i__4].r - q__2.r, q__1.i = b[i__4].i - q__2.i;
		    b[i__3].r = q__1.r, b[i__3].i = q__1.i;
/* L10: */
		}
		if (k < *n - 1) {
		    i__2 = k;
		    dl[i__2].r = 0.f, dl[i__2].i = 0.f;
		}
	    } else {

/*           Interchange rows K and K+1 */

		c_div(&q__1, &d__[k], &dl[k]);
		mult.r = q__1.r, mult.i = q__1.i;
		i__2 = k;
		i__3 = k;
		d__[i__2].r = dl[i__3].r, d__[i__2].i = dl[i__3].i;
		i__2 = k + 1;
		temp.r = d__[i__2].r, temp.i = d__[i__2].i;
		i__2 = k + 1;
		i__3 = k;
		q__2.r = mult.r * temp.r - mult.i * temp.i, q__2.i = mult.r * 
			temp.i + mult.i * temp.r;
		q__1.r = du[i__3].r - q__2.r, q__1.i = du[i__3].i - q__2.i;
		d__[i__2].r = q__1.r, d__[i__2].i = q__1.i;
		if (k < *n - 1) {
		    i__2 = k;
		    i__3 = k + 1;
		    dl[i__2].r = du[i__3].r, dl[i__2].i = du[i__3].i;
		    i__2 = k + 1;
		    q__2.r = -mult.r, q__2.i = -mult.i;
		    i__3 = k;
		    q__1.r = q__2.r * dl[i__3].r - q__2.i * dl[i__3].i, 
			    q__1.i = q__2.r * dl[i__3].i + q__2.i * dl[i__3]
			    .r;
		    du[i__2].r = q__1.r, du[i__2].i = q__1.i;
		}
		i__2 = k;
		du[i__2].r = temp.r, du[i__2].i = temp.i;
		i__2 = *nrhs;
		for (j = 1; j <= i__2; ++j) {
		    i__3 = k + j * b_dim1;
		    temp.r = b[i__3].r, temp.i = b[i__3].i;
		    i__3 = k + j * b_dim1;
		    i__4 = k + 1 + j * b_dim1;
		    b[i__3].r = b[i__4].r, b[i__3].i = b[i__4].i;
		    i__3 = k + 1 + j * b_dim1;
		    i__4 = k + 1 + j * b_dim1;
		    q__2.r = mult.r * b[i__4].r - mult.i * b[i__4].i, q__2.i =
			     mult.r * b[i__4].i + mult.i * b[i__4].r;
		    q__1.r = temp.r - q__2.r, q__1.i = temp.i - q__2.i;
		    b[i__3].r = q__1.r, b[i__3].i = q__1.i;
/* L20: */
		}
	    }
	}
/* L30: */
    }
    i__1 = *n;
    if (d__[i__1].r == 0.f && d__[i__1].i == 0.f) {
	*info = *n;
	return 0;
    }

/*     Back solve with the matrix U from the factorization. */

    i__1 = *nrhs;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *n + j * b_dim1;
	c_div(&q__1, &b[*n + j * b_dim1], &d__[*n]);
	b[i__2].r = q__1.r, b[i__2].i = q__1.i;
	if (*n > 1) {
	    i__2 = *n - 1 + j * b_dim1;
	    i__3 = *n - 1 + j * b_dim1;
	    i__4 = *n - 1;
	    i__5 = *n + j * b_dim1;
	    q__3.r = du[i__4].r * b[i__5].r - du[i__4].i * b[i__5].i, q__3.i =
		     du[i__4].r * b[i__5].i + du[i__4].i * b[i__5].r;
	    q__2.r = b[i__3].r - q__3.r, q__2.i = b[i__3].i - q__3.i;
	    c_div(&q__1, &q__2, &d__[*n - 1]);
	    b[i__2].r = q__1.r, b[i__2].i = q__1.i;
	}
	for (k = *n - 2; k >= 1; --k) {
	    i__2 = k + j * b_dim1;
	    i__3 = k + j * b_dim1;
	    i__4 = k;
	    i__5 = k + 1 + j * b_dim1;
	    q__4.r = du[i__4].r * b[i__5].r - du[i__4].i * b[i__5].i, q__4.i =
		     du[i__4].r * b[i__5].i + du[i__4].i * b[i__5].r;
	    q__3.r = b[i__3].r - q__4.r, q__3.i = b[i__3].i - q__4.i;
	    i__6 = k;
	    i__7 = k + 2 + j * b_dim1;
	    q__5.r = dl[i__6].r * b[i__7].r - dl[i__6].i * b[i__7].i, q__5.i =
		     dl[i__6].r * b[i__7].i + dl[i__6].i * b[i__7].r;
	    q__2.r = q__3.r - q__5.r, q__2.i = q__3.i - q__5.i;
	    c_div(&q__1, &q__2, &d__[k]);
	    b[i__2].r = q__1.r, b[i__2].i = q__1.i;
/* L40: */
	}
/* L50: */
    }

    return 0;

/*     End of CGTSV */

} /* cgtsv_ */

