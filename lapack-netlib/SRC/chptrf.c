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

/* > \brief \b CHPTRF */

/*  =========== DOCUMENTATION =========== */

/* Online html documentation available at */
/*            http://www.netlib.org/lapack/explore-html/ */

/* > \htmlonly */
/* > Download CHPTRF + dependencies */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/chptrf.
f"> */
/* > [TGZ]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/chptrf.
f"> */
/* > [ZIP]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/chptrf.
f"> */
/* > [TXT]</a> */
/* > \endhtmlonly */

/*  Definition: */
/*  =========== */

/*       SUBROUTINE CHPTRF( UPLO, N, AP, IPIV, INFO ) */

/*       CHARACTER          UPLO */
/*       INTEGER            INFO, N */
/*       INTEGER            IPIV( * ) */
/*       COMPLEX            AP( * ) */


/* > \par Purpose: */
/*  ============= */
/* > */
/* > \verbatim */
/* > */
/* > CHPTRF computes the factorization of a complex Hermitian packed */
/* > matrix A using the Bunch-Kaufman diagonal pivoting method: */
/* > */
/* >    A = U*D*U**H  or  A = L*D*L**H */
/* > */
/* > where U (or L) is a product of permutation and unit upper (lower) */
/* > triangular matrices, and D is Hermitian and block diagonal with */
/* > 1-by-1 and 2-by-2 diagonal blocks. */
/* > \endverbatim */

/*  Arguments: */
/*  ========== */

/* > \param[in] UPLO */
/* > \verbatim */
/* >          UPLO is CHARACTER*1 */
/* >          = 'U':  Upper triangle of A is stored; */
/* >          = 'L':  Lower triangle of A is stored. */
/* > \endverbatim */
/* > */
/* > \param[in] N */
/* > \verbatim */
/* >          N is INTEGER */
/* >          The order of the matrix A.  N >= 0. */
/* > \endverbatim */
/* > */
/* > \param[in,out] AP */
/* > \verbatim */
/* >          AP is COMPLEX array, dimension (N*(N+1)/2) */
/* >          On entry, the upper or lower triangle of the Hermitian matrix */
/* >          A, packed columnwise in a linear array.  The j-th column of A */
/* >          is stored in the array AP as follows: */
/* >          if UPLO = 'U', AP(i + (j-1)*j/2) = A(i,j) for 1<=i<=j; */
/* >          if UPLO = 'L', AP(i + (j-1)*(2n-j)/2) = A(i,j) for j<=i<=n. */
/* > */
/* >          On exit, the block diagonal matrix D and the multipliers used */
/* >          to obtain the factor U or L, stored as a packed triangular */
/* >          matrix overwriting A (see below for further details). */
/* > \endverbatim */
/* > */
/* > \param[out] IPIV */
/* > \verbatim */
/* >          IPIV is INTEGER array, dimension (N) */
/* >          Details of the interchanges and the block structure of D. */
/* >          If IPIV(k) > 0, then rows and columns k and IPIV(k) were */
/* >          interchanged and D(k,k) is a 1-by-1 diagonal block. */
/* >          If UPLO = 'U' and IPIV(k) = IPIV(k-1) < 0, then rows and */
/* >          columns k-1 and -IPIV(k) were interchanged and D(k-1:k,k-1:k) */
/* >          is a 2-by-2 diagonal block.  If UPLO = 'L' and IPIV(k) = */
/* >          IPIV(k+1) < 0, then rows and columns k+1 and -IPIV(k) were */
/* >          interchanged and D(k:k+1,k:k+1) is a 2-by-2 diagonal block. */
/* > \endverbatim */
/* > */
/* > \param[out] INFO */
/* > \verbatim */
/* >          INFO is INTEGER */
/* >          = 0: successful exit */
/* >          < 0: if INFO = -i, the i-th argument had an illegal value */
/* >          > 0: if INFO = i, D(i,i) is exactly zero.  The factorization */
/* >               has been completed, but the block diagonal matrix D is */
/* >               exactly singular, and division by zero will occur if it */
/* >               is used to solve a system of equations. */
/* > \endverbatim */

/*  Authors: */
/*  ======== */

/* > \author Univ. of Tennessee */
/* > \author Univ. of California Berkeley */
/* > \author Univ. of Colorado Denver */
/* > \author NAG Ltd. */

/* > \date December 2016 */

/* > \ingroup complexOTHERcomputational */

/* > \par Further Details: */
/*  ===================== */
/* > */
/* > \verbatim */
/* > */
/* >  If UPLO = 'U', then A = U*D*U**H, where */
/* >     U = P(n)*U(n)* ... *P(k)U(k)* ..., */
/* >  i.e., U is a product of terms P(k)*U(k), where k decreases from n to */
/* >  1 in steps of 1 or 2, and D is a block diagonal matrix with 1-by-1 */
/* >  and 2-by-2 diagonal blocks D(k).  P(k) is a permutation matrix as */
/* >  defined by IPIV(k), and U(k) is a unit upper triangular matrix, such */
/* >  that if the diagonal block D(k) is of order s (s = 1 or 2), then */
/* > */
/* >             (   I    v    0   )   k-s */
/* >     U(k) =  (   0    I    0   )   s */
/* >             (   0    0    I   )   n-k */
/* >                k-s   s   n-k */
/* > */
/* >  If s = 1, D(k) overwrites A(k,k), and v overwrites A(1:k-1,k). */
/* >  If s = 2, the upper triangle of D(k) overwrites A(k-1,k-1), A(k-1,k), */
/* >  and A(k,k), and v overwrites A(1:k-2,k-1:k). */
/* > */
/* >  If UPLO = 'L', then A = L*D*L**H, where */
/* >     L = P(1)*L(1)* ... *P(k)*L(k)* ..., */
/* >  i.e., L is a product of terms P(k)*L(k), where k increases from 1 to */
/* >  n in steps of 1 or 2, and D is a block diagonal matrix with 1-by-1 */
/* >  and 2-by-2 diagonal blocks D(k).  P(k) is a permutation matrix as */
/* >  defined by IPIV(k), and L(k) is a unit lower triangular matrix, such */
/* >  that if the diagonal block D(k) is of order s (s = 1 or 2), then */
/* > */
/* >             (   I    0     0   )  k-1 */
/* >     L(k) =  (   0    I     0   )  s */
/* >             (   0    v     I   )  n-k-s+1 */
/* >                k-1   s  n-k-s+1 */
/* > */
/* >  If s = 1, D(k) overwrites A(k,k), and v overwrites A(k+1:n,k). */
/* >  If s = 2, the lower triangle of D(k) overwrites A(k,k), A(k+1,k), */
/* >  and A(k+1,k+1), and v overwrites A(k+2:n,k:k+1). */
/* > \endverbatim */

/* > \par Contributors: */
/*  ================== */
/* > */
/* >  J. Lewis, Boeing Computer Services Company */
/* > */
/*  ===================================================================== */
/* Subroutine */ int chptrf_(char *uplo, integer *n, complex *ap, integer *
	ipiv, integer *info)
{
    /* System generated locals */
    integer i__1, i__2, i__3, i__4, i__5, i__6;
    real r__1, r__2, r__3, r__4;
    complex q__1, q__2, q__3, q__4, q__5, q__6;

    /* Local variables */
    extern /* Subroutine */ int chpr_(char *, integer *, real *, complex *, 
	    integer *, complex *);
    integer imax, jmax;
    real d__;
    integer i__, j, k;
    complex t;
    real alpha;
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int cswap_(integer *, complex *, integer *, 
	    complex *, integer *);
    integer kstep;
    logical upper;
    real r1, d11;
    complex d12;
    real d22;
    complex d21;
    extern real slapy2_(real *, real *);
    integer kc, kk, kp;
    real absakk;
    complex wk;
    integer kx;
    extern integer icamax_(integer *, complex *, integer *);
    real tt;
    extern /* Subroutine */ int csscal_(integer *, real *, complex *, integer 
	    *), xerbla_(char *, integer *, ftnlen);
    real colmax, rowmax;
    integer knc, kpc, npp;
    complex wkm1, wkp1;


/*  -- LAPACK computational routine (version 3.7.0) -- */
/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
/*     December 2016 */


/*  ===================================================================== */


/*     Test the input parameters. */

    /* Parameter adjustments */
    --ipiv;
    --ap;

    /* Function Body */
    *info = 0;
    upper = lsame_(uplo, "U");
    if (! upper && ! lsame_(uplo, "L")) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("CHPTRF", &i__1, (ftnlen)6);
	return 0;
    }

/*     Initialize ALPHA for use in choosing pivot block size. */

    alpha = (sqrt(17.f) + 1.f) / 8.f;

    if (upper) {

/*        Factorize A as U*D*U**H using the upper triangle of A */

/*        K is the main loop index, decreasing from N to 1 in steps of */
/*        1 or 2 */

	k = *n;
	kc = (*n - 1) * *n / 2 + 1;
L10:
	knc = kc;

/*        If K < 1, exit from loop */

	if (k < 1) {
	    goto L110;
	}
	kstep = 1;

/*        Determine rows and columns to be interchanged and whether */
/*        a 1-by-1 or 2-by-2 pivot block will be used */

	i__1 = kc + k - 1;
	absakk = (r__1 = ap[i__1].r, abs(r__1));

/*        IMAX is the row-index of the largest off-diagonal element in */
/*        column K, and COLMAX is its absolute value */

	if (k > 1) {
	    i__1 = k - 1;
	    imax = icamax_(&i__1, &ap[kc], &c__1);
	    i__1 = kc + imax - 1;
	    colmax = (r__1 = ap[i__1].r, abs(r__1)) + (r__2 = r_imag(&ap[kc + 
		    imax - 1]), abs(r__2));
	} else {
	    colmax = 0.f;
	}

	if (f2cmax(absakk,colmax) == 0.f) {

/*           Column K is zero: set INFO and continue */

	    if (*info == 0) {
		*info = k;
	    }
	    kp = k;
	    i__1 = kc + k - 1;
	    i__2 = kc + k - 1;
	    r__1 = ap[i__2].r;
	    ap[i__1].r = r__1, ap[i__1].i = 0.f;
	} else {
	    if (absakk >= alpha * colmax) {

/*              no interchange, use 1-by-1 pivot block */

		kp = k;
	    } else {

/*              JMAX is the column-index of the largest off-diagonal */
/*              element in row IMAX, and ROWMAX is its absolute value */

		rowmax = 0.f;
		jmax = imax;
		kx = imax * (imax + 1) / 2 + imax;
		i__1 = k;
		for (j = imax + 1; j <= i__1; ++j) {
		    i__2 = kx;
		    if ((r__1 = ap[i__2].r, abs(r__1)) + (r__2 = r_imag(&ap[
			    kx]), abs(r__2)) > rowmax) {
			i__2 = kx;
			rowmax = (r__1 = ap[i__2].r, abs(r__1)) + (r__2 = 
				r_imag(&ap[kx]), abs(r__2));
			jmax = j;
		    }
		    kx += j;
/* L20: */
		}
		kpc = (imax - 1) * imax / 2 + 1;
		if (imax > 1) {
		    i__1 = imax - 1;
		    jmax = icamax_(&i__1, &ap[kpc], &c__1);
/* Computing MAX */
		    i__1 = kpc + jmax - 1;
		    r__3 = rowmax, r__4 = (r__1 = ap[i__1].r, abs(r__1)) + (
			    r__2 = r_imag(&ap[kpc + jmax - 1]), abs(r__2));
		    rowmax = f2cmax(r__3,r__4);
		}

		if (absakk >= alpha * colmax * (colmax / rowmax)) {

/*                 no interchange, use 1-by-1 pivot block */

		    kp = k;
		} else /* if(complicated condition) */ {
		    i__1 = kpc + imax - 1;
		    if ((r__1 = ap[i__1].r, abs(r__1)) >= alpha * rowmax) {

/*                 interchange rows and columns K and IMAX, use 1-by-1 */
/*                 pivot block */

			kp = imax;
		    } else {

/*                 interchange rows and columns K-1 and IMAX, use 2-by-2 */
/*                 pivot block */

			kp = imax;
			kstep = 2;
		    }
		}
	    }

	    kk = k - kstep + 1;
	    if (kstep == 2) {
		knc = knc - k + 1;
	    }
	    if (kp != kk) {

/*              Interchange rows and columns KK and KP in the leading */
/*              submatrix A(1:k,1:k) */

		i__1 = kp - 1;
		cswap_(&i__1, &ap[knc], &c__1, &ap[kpc], &c__1);
		kx = kpc + kp - 1;
		i__1 = kk - 1;
		for (j = kp + 1; j <= i__1; ++j) {
		    kx = kx + j - 1;
		    r_cnjg(&q__1, &ap[knc + j - 1]);
		    t.r = q__1.r, t.i = q__1.i;
		    i__2 = knc + j - 1;
		    r_cnjg(&q__1, &ap[kx]);
		    ap[i__2].r = q__1.r, ap[i__2].i = q__1.i;
		    i__2 = kx;
		    ap[i__2].r = t.r, ap[i__2].i = t.i;
/* L30: */
		}
		i__1 = kx + kk - 1;
		r_cnjg(&q__1, &ap[kx + kk - 1]);
		ap[i__1].r = q__1.r, ap[i__1].i = q__1.i;
		i__1 = knc + kk - 1;
		r1 = ap[i__1].r;
		i__1 = knc + kk - 1;
		i__2 = kpc + kp - 1;
		r__1 = ap[i__2].r;
		ap[i__1].r = r__1, ap[i__1].i = 0.f;
		i__1 = kpc + kp - 1;
		ap[i__1].r = r1, ap[i__1].i = 0.f;
		if (kstep == 2) {
		    i__1 = kc + k - 1;
		    i__2 = kc + k - 1;
		    r__1 = ap[i__2].r;
		    ap[i__1].r = r__1, ap[i__1].i = 0.f;
		    i__1 = kc + k - 2;
		    t.r = ap[i__1].r, t.i = ap[i__1].i;
		    i__1 = kc + k - 2;
		    i__2 = kc + kp - 1;
		    ap[i__1].r = ap[i__2].r, ap[i__1].i = ap[i__2].i;
		    i__1 = kc + kp - 1;
		    ap[i__1].r = t.r, ap[i__1].i = t.i;
		}
	    } else {
		i__1 = kc + k - 1;
		i__2 = kc + k - 1;
		r__1 = ap[i__2].r;
		ap[i__1].r = r__1, ap[i__1].i = 0.f;
		if (kstep == 2) {
		    i__1 = kc - 1;
		    i__2 = kc - 1;
		    r__1 = ap[i__2].r;
		    ap[i__1].r = r__1, ap[i__1].i = 0.f;
		}
	    }

/*           Update the leading submatrix */

	    if (kstep == 1) {

/*              1-by-1 pivot block D(k): column k now holds */

/*              W(k) = U(k)*D(k) */

/*              where U(k) is the k-th column of U */

/*              Perform a rank-1 update of A(1:k-1,1:k-1) as */

/*              A := A - U(k)*D(k)*U(k)**H = A - W(k)*1/D(k)*W(k)**H */

		i__1 = kc + k - 1;
		r1 = 1.f / ap[i__1].r;
		i__1 = k - 1;
		r__1 = -r1;
		chpr_(uplo, &i__1, &r__1, &ap[kc], &c__1, &ap[1]);

/*              Store U(k) in column k */

		i__1 = k - 1;
		csscal_(&i__1, &r1, &ap[kc], &c__1);
	    } else {

/*              2-by-2 pivot block D(k): columns k and k-1 now hold */

/*              ( W(k-1) W(k) ) = ( U(k-1) U(k) )*D(k) */

/*              where U(k) and U(k-1) are the k-th and (k-1)-th columns */
/*              of U */

/*              Perform a rank-2 update of A(1:k-2,1:k-2) as */

/*              A := A - ( U(k-1) U(k) )*D(k)*( U(k-1) U(k) )**H */
/*                 = A - ( W(k-1) W(k) )*inv(D(k))*( W(k-1) W(k) )**H */

		if (k > 2) {

		    i__1 = k - 1 + (k - 1) * k / 2;
		    r__1 = ap[i__1].r;
		    r__2 = r_imag(&ap[k - 1 + (k - 1) * k / 2]);
		    d__ = slapy2_(&r__1, &r__2);
		    i__1 = k - 1 + (k - 2) * (k - 1) / 2;
		    d22 = ap[i__1].r / d__;
		    i__1 = k + (k - 1) * k / 2;
		    d11 = ap[i__1].r / d__;
		    tt = 1.f / (d11 * d22 - 1.f);
		    i__1 = k - 1 + (k - 1) * k / 2;
		    q__1.r = ap[i__1].r / d__, q__1.i = ap[i__1].i / d__;
		    d12.r = q__1.r, d12.i = q__1.i;
		    d__ = tt / d__;

		    for (j = k - 2; j >= 1; --j) {
			i__1 = j + (k - 2) * (k - 1) / 2;
			q__3.r = d11 * ap[i__1].r, q__3.i = d11 * ap[i__1].i;
			r_cnjg(&q__5, &d12);
			i__2 = j + (k - 1) * k / 2;
			q__4.r = q__5.r * ap[i__2].r - q__5.i * ap[i__2].i, 
				q__4.i = q__5.r * ap[i__2].i + q__5.i * ap[
				i__2].r;
			q__2.r = q__3.r - q__4.r, q__2.i = q__3.i - q__4.i;
			q__1.r = d__ * q__2.r, q__1.i = d__ * q__2.i;
			wkm1.r = q__1.r, wkm1.i = q__1.i;
			i__1 = j + (k - 1) * k / 2;
			q__3.r = d22 * ap[i__1].r, q__3.i = d22 * ap[i__1].i;
			i__2 = j + (k - 2) * (k - 1) / 2;
			q__4.r = d12.r * ap[i__2].r - d12.i * ap[i__2].i, 
				q__4.i = d12.r * ap[i__2].i + d12.i * ap[i__2]
				.r;
			q__2.r = q__3.r - q__4.r, q__2.i = q__3.i - q__4.i;
			q__1.r = d__ * q__2.r, q__1.i = d__ * q__2.i;
			wk.r = q__1.r, wk.i = q__1.i;
			for (i__ = j; i__ >= 1; --i__) {
			    i__1 = i__ + (j - 1) * j / 2;
			    i__2 = i__ + (j - 1) * j / 2;
			    i__3 = i__ + (k - 1) * k / 2;
			    r_cnjg(&q__4, &wk);
			    q__3.r = ap[i__3].r * q__4.r - ap[i__3].i * 
				    q__4.i, q__3.i = ap[i__3].r * q__4.i + ap[
				    i__3].i * q__4.r;
			    q__2.r = ap[i__2].r - q__3.r, q__2.i = ap[i__2].i 
				    - q__3.i;
			    i__4 = i__ + (k - 2) * (k - 1) / 2;
			    r_cnjg(&q__6, &wkm1);
			    q__5.r = ap[i__4].r * q__6.r - ap[i__4].i * 
				    q__6.i, q__5.i = ap[i__4].r * q__6.i + ap[
				    i__4].i * q__6.r;
			    q__1.r = q__2.r - q__5.r, q__1.i = q__2.i - 
				    q__5.i;
			    ap[i__1].r = q__1.r, ap[i__1].i = q__1.i;
/* L40: */
			}
			i__1 = j + (k - 1) * k / 2;
			ap[i__1].r = wk.r, ap[i__1].i = wk.i;
			i__1 = j + (k - 2) * (k - 1) / 2;
			ap[i__1].r = wkm1.r, ap[i__1].i = wkm1.i;
			i__1 = j + (j - 1) * j / 2;
			i__2 = j + (j - 1) * j / 2;
			r__1 = ap[i__2].r;
			q__1.r = r__1, q__1.i = 0.f;
			ap[i__1].r = q__1.r, ap[i__1].i = q__1.i;
/* L50: */
		    }

		}

	    }
	}

/*        Store details of the interchanges in IPIV */

	if (kstep == 1) {
	    ipiv[k] = kp;
	} else {
	    ipiv[k] = -kp;
	    ipiv[k - 1] = -kp;
	}

/*        Decrease K and return to the start of the main loop */

	k -= kstep;
	kc = knc - k;
	goto L10;

    } else {

/*        Factorize A as L*D*L**H using the lower triangle of A */

/*        K is the main loop index, increasing from 1 to N in steps of */
/*        1 or 2 */

	k = 1;
	kc = 1;
	npp = *n * (*n + 1) / 2;
L60:
	knc = kc;

/*        If K > N, exit from loop */

	if (k > *n) {
	    goto L110;
	}
	kstep = 1;

/*        Determine rows and columns to be interchanged and whether */
/*        a 1-by-1 or 2-by-2 pivot block will be used */

	i__1 = kc;
	absakk = (r__1 = ap[i__1].r, abs(r__1));

/*        IMAX is the row-index of the largest off-diagonal element in */
/*        column K, and COLMAX is its absolute value */

	if (k < *n) {
	    i__1 = *n - k;
	    imax = k + icamax_(&i__1, &ap[kc + 1], &c__1);
	    i__1 = kc + imax - k;
	    colmax = (r__1 = ap[i__1].r, abs(r__1)) + (r__2 = r_imag(&ap[kc + 
		    imax - k]), abs(r__2));
	} else {
	    colmax = 0.f;
	}

	if (f2cmax(absakk,colmax) == 0.f) {

/*           Column K is zero: set INFO and continue */

	    if (*info == 0) {
		*info = k;
	    }
	    kp = k;
	    i__1 = kc;
	    i__2 = kc;
	    r__1 = ap[i__2].r;
	    ap[i__1].r = r__1, ap[i__1].i = 0.f;
	} else {
	    if (absakk >= alpha * colmax) {

/*              no interchange, use 1-by-1 pivot block */

		kp = k;
	    } else {

/*              JMAX is the column-index of the largest off-diagonal */
/*              element in row IMAX, and ROWMAX is its absolute value */

		rowmax = 0.f;
		kx = kc + imax - k;
		i__1 = imax - 1;
		for (j = k; j <= i__1; ++j) {
		    i__2 = kx;
		    if ((r__1 = ap[i__2].r, abs(r__1)) + (r__2 = r_imag(&ap[
			    kx]), abs(r__2)) > rowmax) {
			i__2 = kx;
			rowmax = (r__1 = ap[i__2].r, abs(r__1)) + (r__2 = 
				r_imag(&ap[kx]), abs(r__2));
			jmax = j;
		    }
		    kx = kx + *n - j;
/* L70: */
		}
		kpc = npp - (*n - imax + 1) * (*n - imax + 2) / 2 + 1;
		if (imax < *n) {
		    i__1 = *n - imax;
		    jmax = imax + icamax_(&i__1, &ap[kpc + 1], &c__1);
/* Computing MAX */
		    i__1 = kpc + jmax - imax;
		    r__3 = rowmax, r__4 = (r__1 = ap[i__1].r, abs(r__1)) + (
			    r__2 = r_imag(&ap[kpc + jmax - imax]), abs(r__2));
		    rowmax = f2cmax(r__3,r__4);
		}

		if (absakk >= alpha * colmax * (colmax / rowmax)) {

/*                 no interchange, use 1-by-1 pivot block */

		    kp = k;
		} else /* if(complicated condition) */ {
		    i__1 = kpc;
		    if ((r__1 = ap[i__1].r, abs(r__1)) >= alpha * rowmax) {

/*                 interchange rows and columns K and IMAX, use 1-by-1 */
/*                 pivot block */

			kp = imax;
		    } else {

/*                 interchange rows and columns K+1 and IMAX, use 2-by-2 */
/*                 pivot block */

			kp = imax;
			kstep = 2;
		    }
		}
	    }

	    kk = k + kstep - 1;
	    if (kstep == 2) {
		knc = knc + *n - k + 1;
	    }
	    if (kp != kk) {

/*              Interchange rows and columns KK and KP in the trailing */
/*              submatrix A(k:n,k:n) */

		if (kp < *n) {
		    i__1 = *n - kp;
		    cswap_(&i__1, &ap[knc + kp - kk + 1], &c__1, &ap[kpc + 1],
			     &c__1);
		}
		kx = knc + kp - kk;
		i__1 = kp - 1;
		for (j = kk + 1; j <= i__1; ++j) {
		    kx = kx + *n - j + 1;
		    r_cnjg(&q__1, &ap[knc + j - kk]);
		    t.r = q__1.r, t.i = q__1.i;
		    i__2 = knc + j - kk;
		    r_cnjg(&q__1, &ap[kx]);
		    ap[i__2].r = q__1.r, ap[i__2].i = q__1.i;
		    i__2 = kx;
		    ap[i__2].r = t.r, ap[i__2].i = t.i;
/* L80: */
		}
		i__1 = knc + kp - kk;
		r_cnjg(&q__1, &ap[knc + kp - kk]);
		ap[i__1].r = q__1.r, ap[i__1].i = q__1.i;
		i__1 = knc;
		r1 = ap[i__1].r;
		i__1 = knc;
		i__2 = kpc;
		r__1 = ap[i__2].r;
		ap[i__1].r = r__1, ap[i__1].i = 0.f;
		i__1 = kpc;
		ap[i__1].r = r1, ap[i__1].i = 0.f;
		if (kstep == 2) {
		    i__1 = kc;
		    i__2 = kc;
		    r__1 = ap[i__2].r;
		    ap[i__1].r = r__1, ap[i__1].i = 0.f;
		    i__1 = kc + 1;
		    t.r = ap[i__1].r, t.i = ap[i__1].i;
		    i__1 = kc + 1;
		    i__2 = kc + kp - k;
		    ap[i__1].r = ap[i__2].r, ap[i__1].i = ap[i__2].i;
		    i__1 = kc + kp - k;
		    ap[i__1].r = t.r, ap[i__1].i = t.i;
		}
	    } else {
		i__1 = kc;
		i__2 = kc;
		r__1 = ap[i__2].r;
		ap[i__1].r = r__1, ap[i__1].i = 0.f;
		if (kstep == 2) {
		    i__1 = knc;
		    i__2 = knc;
		    r__1 = ap[i__2].r;
		    ap[i__1].r = r__1, ap[i__1].i = 0.f;
		}
	    }

/*           Update the trailing submatrix */

	    if (kstep == 1) {

/*              1-by-1 pivot block D(k): column k now holds */

/*              W(k) = L(k)*D(k) */

/*              where L(k) is the k-th column of L */

		if (k < *n) {

/*                 Perform a rank-1 update of A(k+1:n,k+1:n) as */

/*                 A := A - L(k)*D(k)*L(k)**H = A - W(k)*(1/D(k))*W(k)**H */

		    i__1 = kc;
		    r1 = 1.f / ap[i__1].r;
		    i__1 = *n - k;
		    r__1 = -r1;
		    chpr_(uplo, &i__1, &r__1, &ap[kc + 1], &c__1, &ap[kc + *n 
			    - k + 1]);

/*                 Store L(k) in column K */

		    i__1 = *n - k;
		    csscal_(&i__1, &r1, &ap[kc + 1], &c__1);
		}
	    } else {

/*              2-by-2 pivot block D(k): columns K and K+1 now hold */

/*              ( W(k) W(k+1) ) = ( L(k) L(k+1) )*D(k) */

/*              where L(k) and L(k+1) are the k-th and (k+1)-th columns */
/*              of L */

		if (k < *n - 1) {

/*                 Perform a rank-2 update of A(k+2:n,k+2:n) as */

/*                 A := A - ( L(k) L(k+1) )*D(k)*( L(k) L(k+1) )**H */
/*                    = A - ( W(k) W(k+1) )*inv(D(k))*( W(k) W(k+1) )**H */

/*                 where L(k) and L(k+1) are the k-th and (k+1)-th */
/*                 columns of L */

		    i__1 = k + 1 + (k - 1) * ((*n << 1) - k) / 2;
		    r__1 = ap[i__1].r;
		    r__2 = r_imag(&ap[k + 1 + (k - 1) * ((*n << 1) - k) / 2]);
		    d__ = slapy2_(&r__1, &r__2);
		    i__1 = k + 1 + k * ((*n << 1) - k - 1) / 2;
		    d11 = ap[i__1].r / d__;
		    i__1 = k + (k - 1) * ((*n << 1) - k) / 2;
		    d22 = ap[i__1].r / d__;
		    tt = 1.f / (d11 * d22 - 1.f);
		    i__1 = k + 1 + (k - 1) * ((*n << 1) - k) / 2;
		    q__1.r = ap[i__1].r / d__, q__1.i = ap[i__1].i / d__;
		    d21.r = q__1.r, d21.i = q__1.i;
		    d__ = tt / d__;

		    i__1 = *n;
		    for (j = k + 2; j <= i__1; ++j) {
			i__2 = j + (k - 1) * ((*n << 1) - k) / 2;
			q__3.r = d11 * ap[i__2].r, q__3.i = d11 * ap[i__2].i;
			i__3 = j + k * ((*n << 1) - k - 1) / 2;
			q__4.r = d21.r * ap[i__3].r - d21.i * ap[i__3].i, 
				q__4.i = d21.r * ap[i__3].i + d21.i * ap[i__3]
				.r;
			q__2.r = q__3.r - q__4.r, q__2.i = q__3.i - q__4.i;
			q__1.r = d__ * q__2.r, q__1.i = d__ * q__2.i;
			wk.r = q__1.r, wk.i = q__1.i;
			i__2 = j + k * ((*n << 1) - k - 1) / 2;
			q__3.r = d22 * ap[i__2].r, q__3.i = d22 * ap[i__2].i;
			r_cnjg(&q__5, &d21);
			i__3 = j + (k - 1) * ((*n << 1) - k) / 2;
			q__4.r = q__5.r * ap[i__3].r - q__5.i * ap[i__3].i, 
				q__4.i = q__5.r * ap[i__3].i + q__5.i * ap[
				i__3].r;
			q__2.r = q__3.r - q__4.r, q__2.i = q__3.i - q__4.i;
			q__1.r = d__ * q__2.r, q__1.i = d__ * q__2.i;
			wkp1.r = q__1.r, wkp1.i = q__1.i;
			i__2 = *n;
			for (i__ = j; i__ <= i__2; ++i__) {
			    i__3 = i__ + (j - 1) * ((*n << 1) - j) / 2;
			    i__4 = i__ + (j - 1) * ((*n << 1) - j) / 2;
			    i__5 = i__ + (k - 1) * ((*n << 1) - k) / 2;
			    r_cnjg(&q__4, &wk);
			    q__3.r = ap[i__5].r * q__4.r - ap[i__5].i * 
				    q__4.i, q__3.i = ap[i__5].r * q__4.i + ap[
				    i__5].i * q__4.r;
			    q__2.r = ap[i__4].r - q__3.r, q__2.i = ap[i__4].i 
				    - q__3.i;
			    i__6 = i__ + k * ((*n << 1) - k - 1) / 2;
			    r_cnjg(&q__6, &wkp1);
			    q__5.r = ap[i__6].r * q__6.r - ap[i__6].i * 
				    q__6.i, q__5.i = ap[i__6].r * q__6.i + ap[
				    i__6].i * q__6.r;
			    q__1.r = q__2.r - q__5.r, q__1.i = q__2.i - 
				    q__5.i;
			    ap[i__3].r = q__1.r, ap[i__3].i = q__1.i;
/* L90: */
			}
			i__2 = j + (k - 1) * ((*n << 1) - k) / 2;
			ap[i__2].r = wk.r, ap[i__2].i = wk.i;
			i__2 = j + k * ((*n << 1) - k - 1) / 2;
			ap[i__2].r = wkp1.r, ap[i__2].i = wkp1.i;
			i__2 = j + (j - 1) * ((*n << 1) - j) / 2;
			i__3 = j + (j - 1) * ((*n << 1) - j) / 2;
			r__1 = ap[i__3].r;
			q__1.r = r__1, q__1.i = 0.f;
			ap[i__2].r = q__1.r, ap[i__2].i = q__1.i;
/* L100: */
		    }
		}
	    }
	}

/*        Store details of the interchanges in IPIV */

	if (kstep == 1) {
	    ipiv[k] = kp;
	} else {
	    ipiv[k] = -kp;
	    ipiv[k + 1] = -kp;
	}

/*        Increase K and return to the start of the main loop */

	k += kstep;
	kc = knc + *n - k + 2;
	goto L60;

    }

L110:
    return 0;

/*     End of CHPTRF */

} /* chptrf_ */

