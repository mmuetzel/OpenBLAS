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
static integer c__0 = 0;
static real c_b27 = 1.f;

/* > \brief \b CGSVJ0 pre-processor for the routine cgesvj. */

/*  =========== DOCUMENTATION =========== */

/* Online html documentation available at */
/*            http://www.netlib.org/lapack/explore-html/ */

/* > \htmlonly */
/* > Download CGSVJ0 + dependencies */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/cgsvj0.
f"> */
/* > [TGZ]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/cgsvj0.
f"> */
/* > [ZIP]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/cgsvj0.
f"> */
/* > [TXT]</a> */
/* > \endhtmlonly */

/*  Definition: */
/*  =========== */

/*       SUBROUTINE CGSVJ0( JOBV, M, N, A, LDA, D, SVA, MV, V, LDV, EPS, */
/*                          SFMIN, TOL, NSWEEP, WORK, LWORK, INFO ) */

/*       INTEGER            INFO, LDA, LDV, LWORK, M, MV, N, NSWEEP */
/*       REAL               EPS, SFMIN, TOL */
/*       CHARACTER*1        JOBV */
/*       COMPLEX            A( LDA, * ), D( N ), V( LDV, * ), WORK( LWORK ) */
/*       REAL               SVA( N ) */


/* > \par Purpose: */
/*  ============= */
/* > */
/* > \verbatim */
/* > */
/* > CGSVJ0 is called from CGESVJ as a pre-processor and that is its main */
/* > purpose. It applies Jacobi rotations in the same way as CGESVJ does, but */
/* > it does not check convergence (stopping criterion). Few tuning */
/* > parameters (marked by [TP]) are available for the implementer. */
/* > \endverbatim */

/*  Arguments: */
/*  ========== */

/* > \param[in] JOBV */
/* > \verbatim */
/* >          JOBV is CHARACTER*1 */
/* >          Specifies whether the output from this procedure is used */
/* >          to compute the matrix V: */
/* >          = 'V': the product of the Jacobi rotations is accumulated */
/* >                 by postmulyiplying the N-by-N array V. */
/* >                (See the description of V.) */
/* >          = 'A': the product of the Jacobi rotations is accumulated */
/* >                 by postmulyiplying the MV-by-N array V. */
/* >                (See the descriptions of MV and V.) */
/* >          = 'N': the Jacobi rotations are not accumulated. */
/* > \endverbatim */
/* > */
/* > \param[in] M */
/* > \verbatim */
/* >          M is INTEGER */
/* >          The number of rows of the input matrix A.  M >= 0. */
/* > \endverbatim */
/* > */
/* > \param[in] N */
/* > \verbatim */
/* >          N is INTEGER */
/* >          The number of columns of the input matrix A. */
/* >          M >= N >= 0. */
/* > \endverbatim */
/* > */
/* > \param[in,out] A */
/* > \verbatim */
/* >          A is COMPLEX array, dimension (LDA,N) */
/* >          On entry, M-by-N matrix A, such that A*diag(D) represents */
/* >          the input matrix. */
/* >          On exit, */
/* >          A_onexit * diag(D_onexit) represents the input matrix A*diag(D) */
/* >          post-multiplied by a sequence of Jacobi rotations, where the */
/* >          rotation threshold and the total number of sweeps are given in */
/* >          TOL and NSWEEP, respectively. */
/* >          (See the descriptions of D, TOL and NSWEEP.) */
/* > \endverbatim */
/* > */
/* > \param[in] LDA */
/* > \verbatim */
/* >          LDA is INTEGER */
/* >          The leading dimension of the array A.  LDA >= f2cmax(1,M). */
/* > \endverbatim */
/* > */
/* > \param[in,out] D */
/* > \verbatim */
/* >          D is COMPLEX array, dimension (N) */
/* >          The array D accumulates the scaling factors from the complex scaled */
/* >          Jacobi rotations. */
/* >          On entry, A*diag(D) represents the input matrix. */
/* >          On exit, A_onexit*diag(D_onexit) represents the input matrix */
/* >          post-multiplied by a sequence of Jacobi rotations, where the */
/* >          rotation threshold and the total number of sweeps are given in */
/* >          TOL and NSWEEP, respectively. */
/* >          (See the descriptions of A, TOL and NSWEEP.) */
/* > \endverbatim */
/* > */
/* > \param[in,out] SVA */
/* > \verbatim */
/* >          SVA is REAL array, dimension (N) */
/* >          On entry, SVA contains the Euclidean norms of the columns of */
/* >          the matrix A*diag(D). */
/* >          On exit, SVA contains the Euclidean norms of the columns of */
/* >          the matrix A_onexit*diag(D_onexit). */
/* > \endverbatim */
/* > */
/* > \param[in] MV */
/* > \verbatim */
/* >          MV is INTEGER */
/* >          If JOBV = 'A', then MV rows of V are post-multipled by a */
/* >                           sequence of Jacobi rotations. */
/* >          If JOBV = 'N',   then MV is not referenced. */
/* > \endverbatim */
/* > */
/* > \param[in,out] V */
/* > \verbatim */
/* >          V is COMPLEX array, dimension (LDV,N) */
/* >          If JOBV = 'V' then N rows of V are post-multipled by a */
/* >                           sequence of Jacobi rotations. */
/* >          If JOBV = 'A' then MV rows of V are post-multipled by a */
/* >                           sequence of Jacobi rotations. */
/* >          If JOBV = 'N',   then V is not referenced. */
/* > \endverbatim */
/* > */
/* > \param[in] LDV */
/* > \verbatim */
/* >          LDV is INTEGER */
/* >          The leading dimension of the array V,  LDV >= 1. */
/* >          If JOBV = 'V', LDV >= N. */
/* >          If JOBV = 'A', LDV >= MV. */
/* > \endverbatim */
/* > */
/* > \param[in] EPS */
/* > \verbatim */
/* >          EPS is REAL */
/* >          EPS = SLAMCH('Epsilon') */
/* > \endverbatim */
/* > */
/* > \param[in] SFMIN */
/* > \verbatim */
/* >          SFMIN is REAL */
/* >          SFMIN = SLAMCH('Safe Minimum') */
/* > \endverbatim */
/* > */
/* > \param[in] TOL */
/* > \verbatim */
/* >          TOL is REAL */
/* >          TOL is the threshold for Jacobi rotations. For a pair */
/* >          A(:,p), A(:,q) of pivot columns, the Jacobi rotation is */
/* >          applied only if ABS(COS(angle(A(:,p),A(:,q)))) > TOL. */
/* > \endverbatim */
/* > */
/* > \param[in] NSWEEP */
/* > \verbatim */
/* >          NSWEEP is INTEGER */
/* >          NSWEEP is the number of sweeps of Jacobi rotations to be */
/* >          performed. */
/* > \endverbatim */
/* > */
/* > \param[out] WORK */
/* > \verbatim */
/* >          WORK is COMPLEX array, dimension (LWORK) */
/* > \endverbatim */
/* > */
/* > \param[in] LWORK */
/* > \verbatim */
/* >          LWORK is INTEGER */
/* >          LWORK is the dimension of WORK. LWORK >= M. */
/* > \endverbatim */
/* > */
/* > \param[out] INFO */
/* > \verbatim */
/* >          INFO is INTEGER */
/* >          = 0:  successful exit. */
/* >          < 0:  if INFO = -i, then the i-th argument had an illegal value */
/* > \endverbatim */

/*  Authors: */
/*  ======== */

/* > \author Univ. of Tennessee */
/* > \author Univ. of California Berkeley */
/* > \author Univ. of Colorado Denver */
/* > \author NAG Ltd. */

/* > \date June 2016 */

/* > \ingroup complexOTHERcomputational */

/* > \par Further Details: */
/*  ===================== */
/* > */
/* > CGSVJ0 is used just to enable CGESVJ to call a simplified version of */
/* > itself to work on a submatrix of the original matrix. */
/* > */
/* > \par Contributor: */
/*  ================== */
/* > */
/* > Zlatko Drmac (Zagreb, Croatia) */
/* > */
/* > \par Bugs, Examples and Comments: */
/*  ================================= */
/* > */
/* > Please report all bugs and send interesting test examples and comments to */
/* > drmac@math.hr. Thank you. */

/*  ===================================================================== */
/* Subroutine */ int cgsvj0_(char *jobv, integer *m, integer *n, complex *a, 
	integer *lda, complex *d__, real *sva, integer *mv, complex *v, 
	integer *ldv, real *eps, real *sfmin, real *tol, integer *nsweep, 
	complex *work, integer *lwork, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, v_dim1, v_offset, i__1, i__2, i__3, i__4, i__5, 
	    i__6, i__7;
    real r__1, r__2;
    complex q__1, q__2, q__3;

    /* Local variables */
    real aapp;
    complex aapq;
    real aaqq;
    integer ierr;
    real bigtheta;
    extern /* Subroutine */ int crot_(integer *, complex *, integer *, 
	    complex *, integer *, real *, complex *);
    complex ompq;
    integer pskipped;
    real aapp0, aapq1, temp1;
    integer i__, p, q;
    real t;
    extern /* Complex */ VOID cdotc_(complex *, integer *, complex *, integer 
	    *, complex *, integer *);
    real apoaq, aqoap;
    extern logical lsame_(char *, char *);
    real theta, small;
    extern /* Subroutine */ int ccopy_(integer *, complex *, integer *, 
	    complex *, integer *), cswap_(integer *, complex *, integer *, 
	    complex *, integer *);
    logical applv, rsvec;
    extern /* Subroutine */ int caxpy_(integer *, complex *, complex *, 
	    integer *, complex *, integer *);
    logical rotok;
    real rootsfmin;
    extern real scnrm2_(integer *, complex *, integer *);
    real cs, sn;
    extern /* Subroutine */ int clascl_(char *, integer *, integer *, real *, 
	    real *, integer *, integer *, complex *, integer *, integer *), xerbla_(char *, integer *, ftnlen);
    integer ijblsk, swband;
    extern integer isamax_(integer *, real *, integer *);
    integer blskip;
    extern /* Subroutine */ int classq_(integer *, complex *, integer *, real 
	    *, real *);
    real mxaapq, thsign, mxsinj;
    integer ir1, emptsw, notrot, iswrot, jbc;
    real big;
    integer kbl, lkahead, igl, ibr, jgl, nbl, mvl;
    real rootbig, rooteps;
    integer rowskip;
    real roottol;


/*  -- LAPACK computational routine (version 3.8.0) -- */
/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
/*     June 2016 */


/*  ===================================================================== */

/*     from BLAS */
/*     from LAPACK */

/*     Test the input parameters. */

    /* Parameter adjustments */
    --sva;
    --d__;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    v_dim1 = *ldv;
    v_offset = 1 + v_dim1 * 1;
    v -= v_offset;
    --work;

    /* Function Body */
    applv = lsame_(jobv, "A");
    rsvec = lsame_(jobv, "V");
    if (! (rsvec || applv || lsame_(jobv, "N"))) {
	*info = -1;
    } else if (*m < 0) {
	*info = -2;
    } else if (*n < 0 || *n > *m) {
	*info = -3;
    } else if (*lda < *m) {
	*info = -5;
    } else if ((rsvec || applv) && *mv < 0) {
	*info = -8;
    } else if (rsvec && *ldv < *n || applv && *ldv < *mv) {
	*info = -10;
    } else if (*tol <= *eps) {
	*info = -13;
    } else if (*nsweep < 0) {
	*info = -14;
    } else if (*lwork < *m) {
	*info = -16;
    } else {
	*info = 0;
    }

/*     #:( */
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("CGSVJ0", &i__1, (ftnlen)6);
	return 0;
    }

    if (rsvec) {
	mvl = *n;
    } else if (applv) {
	mvl = *mv;
    }
    rsvec = rsvec || applv;
    rooteps = sqrt(*eps);
    rootsfmin = sqrt(*sfmin);
    small = *sfmin / *eps;
    big = 1.f / *sfmin;
    rootbig = 1.f / rootsfmin;
    bigtheta = 1.f / rooteps;
    roottol = sqrt(*tol);


    emptsw = *n * (*n - 1) / 2;
    notrot = 0;


    swband = 0;
/* [TP] SWBAND is a tuning parameter [TP]. It is meaningful and effective */
/*     if CGESVJ is used as a computational routine in the preconditioned */
/*     Jacobi SVD algorithm CGEJSV. For sweeps i=1:SWBAND the procedure */
/*     works on pivots inside a band-like region around the diagonal. */
/*     The boundaries are determined dynamically, based on the number of */
/*     pivots above a threshold. */

    kbl = f2cmin(8,*n);
/* [TP] KBL is a tuning parameter that defines the tile size in the */
/*     tiling of the p-q loops of pivot pairs. In general, an optimal */
/*     value of KBL depends on the matrix dimensions and on the */
/*     parameters of the computer's memory. */

    nbl = *n / kbl;
    if (nbl * kbl != *n) {
	++nbl;
    }

/* Computing 2nd power */
    i__1 = kbl;
    blskip = i__1 * i__1;
/* [TP] BLKSKIP is a tuning parameter that depends on SWBAND and KBL. */

    rowskip = f2cmin(5,kbl);
/* [TP] ROWSKIP is a tuning parameter. */

    lkahead = 1;
/* [TP] LKAHEAD is a tuning parameter. */

/*     Quasi block transformations, using the lower (upper) triangular */
/*     structure of the input matrix. The quasi-block-cycling usually */
/*     invokes cubic convergence. Big part of this cycle is done inside */
/*     canonical subspaces of dimensions less than M. */



    i__1 = *nsweep;
    for (i__ = 1; i__ <= i__1; ++i__) {


	mxaapq = 0.f;
	mxsinj = 0.f;
	iswrot = 0;

	notrot = 0;
	pskipped = 0;

/*     Each sweep is unrolled using KBL-by-KBL tiles over the pivot pairs */
/*     1 <= p < q <= N. This is the first step toward a blocked implementation */
/*     of the rotations. New implementation, based on block transformations, */
/*     is under development. */

	i__2 = nbl;
	for (ibr = 1; ibr <= i__2; ++ibr) {

	    igl = (ibr - 1) * kbl + 1;

/* Computing MIN */
	    i__4 = lkahead, i__5 = nbl - ibr;
	    i__3 = f2cmin(i__4,i__5);
	    for (ir1 = 0; ir1 <= i__3; ++ir1) {

		igl += ir1 * kbl;

/* Computing MIN */
		i__5 = igl + kbl - 1, i__6 = *n - 1;
		i__4 = f2cmin(i__5,i__6);
		for (p = igl; p <= i__4; ++p) {


		    i__5 = *n - p + 1;
		    q = isamax_(&i__5, &sva[p], &c__1) + p - 1;
		    if (p != q) {
			cswap_(m, &a[p * a_dim1 + 1], &c__1, &a[q * a_dim1 + 
				1], &c__1);
			if (rsvec) {
			    cswap_(&mvl, &v[p * v_dim1 + 1], &c__1, &v[q * 
				    v_dim1 + 1], &c__1);
			}
			temp1 = sva[p];
			sva[p] = sva[q];
			sva[q] = temp1;
			i__5 = p;
			aapq.r = d__[i__5].r, aapq.i = d__[i__5].i;
			i__5 = p;
			i__6 = q;
			d__[i__5].r = d__[i__6].r, d__[i__5].i = d__[i__6].i;
			i__5 = q;
			d__[i__5].r = aapq.r, d__[i__5].i = aapq.i;
		    }

		    if (ir1 == 0) {

/*        Column norms are periodically updated by explicit */
/*        norm computation. */
/*        Caveat: */
/*        Unfortunately, some BLAS implementations compute SNCRM2(M,A(1,p),1) */
/*        as SQRT(S=CDOTC(M,A(1,p),1,A(1,p),1)), which may cause the result to */
/*        overflow for ||A(:,p)||_2 > SQRT(overflow_threshold), and to */
/*        underflow for ||A(:,p)||_2 < SQRT(underflow_threshold). */
/*        Hence, SCNRM2 cannot be trusted, not even in the case when */
/*        the true norm is far from the under(over)flow boundaries. */
/*        If properly implemented SCNRM2 is available, the IF-THEN-ELSE-END IF */
/*        below should be replaced with "AAPP = SCNRM2( M, A(1,p), 1 )". */

			if (sva[p] < rootbig && sva[p] > rootsfmin) {
			    sva[p] = scnrm2_(m, &a[p * a_dim1 + 1], &c__1);
			} else {
			    temp1 = 0.f;
			    aapp = 1.f;
			    classq_(m, &a[p * a_dim1 + 1], &c__1, &temp1, &
				    aapp);
			    sva[p] = temp1 * sqrt(aapp);
			}
			aapp = sva[p];
		    } else {
			aapp = sva[p];
		    }

		    if (aapp > 0.f) {

			pskipped = 0;

/* Computing MIN */
			i__6 = igl + kbl - 1;
			i__5 = f2cmin(i__6,*n);
			for (q = p + 1; q <= i__5; ++q) {

			    aaqq = sva[q];

			    if (aaqq > 0.f) {

				aapp0 = aapp;
				if (aaqq >= 1.f) {
				    rotok = small * aapp <= aaqq;
				    if (aapp < big / aaqq) {
					cdotc_(&q__3, m, &a[p * a_dim1 + 1], &
						c__1, &a[q * a_dim1 + 1], &
						c__1);
					q__2.r = q__3.r / aaqq, q__2.i = 
						q__3.i / aaqq;
					q__1.r = q__2.r / aapp, q__1.i = 
						q__2.i / aapp;
					aapq.r = q__1.r, aapq.i = q__1.i;
				    } else {
					ccopy_(m, &a[p * a_dim1 + 1], &c__1, &
						work[1], &c__1);
					clascl_("G", &c__0, &c__0, &aapp, &
						c_b27, m, &c__1, &work[1], 
						lda, &ierr);
					cdotc_(&q__2, m, &work[1], &c__1, &a[
						q * a_dim1 + 1], &c__1);
					q__1.r = q__2.r / aaqq, q__1.i = 
						q__2.i / aaqq;
					aapq.r = q__1.r, aapq.i = q__1.i;
				    }
				} else {
				    rotok = aapp <= aaqq / small;
				    if (aapp > small / aaqq) {
					cdotc_(&q__3, m, &a[p * a_dim1 + 1], &
						c__1, &a[q * a_dim1 + 1], &
						c__1);
					q__2.r = q__3.r / aapp, q__2.i = 
						q__3.i / aapp;
					q__1.r = q__2.r / aaqq, q__1.i = 
						q__2.i / aaqq;
					aapq.r = q__1.r, aapq.i = q__1.i;
				    } else {
					ccopy_(m, &a[q * a_dim1 + 1], &c__1, &
						work[1], &c__1);
					clascl_("G", &c__0, &c__0, &aaqq, &
						c_b27, m, &c__1, &work[1], 
						lda, &ierr);
					cdotc_(&q__2, m, &a[p * a_dim1 + 1], &
						c__1, &work[1], &c__1);
					q__1.r = q__2.r / aapp, q__1.i = 
						q__2.i / aapp;
					aapq.r = q__1.r, aapq.i = q__1.i;
				    }
				}

/*                           AAPQ = AAPQ * CONJG( CWORK(p) ) * CWORK(q) */
				aapq1 = -c_abs(&aapq);
/* Computing MAX */
				r__1 = mxaapq, r__2 = -aapq1;
				mxaapq = f2cmax(r__1,r__2);

/*        TO rotate or NOT to rotate, THAT is the question ... */

				if (abs(aapq1) > *tol) {
				    r__1 = c_abs(&aapq);
				    q__1.r = aapq.r / r__1, q__1.i = aapq.i / 
					    r__1;
				    ompq.r = q__1.r, ompq.i = q__1.i;

/* [RTD]      ROTATED = ROTATED + ONE */

				    if (ir1 == 0) {
					notrot = 0;
					pskipped = 0;
					++iswrot;
				    }

				    if (rotok) {

					aqoap = aaqq / aapp;
					apoaq = aapp / aaqq;
					theta = (r__1 = aqoap - apoaq, abs(
						r__1)) * -.5f / aapq1;

					if (abs(theta) > bigtheta) {

					    t = .5f / theta;
					    cs = 1.f;
					    r_cnjg(&q__2, &ompq);
					    q__1.r = t * q__2.r, q__1.i = t * 
						    q__2.i;
					    crot_(m, &a[p * a_dim1 + 1], &
						    c__1, &a[q * a_dim1 + 1], 
						    &c__1, &cs, &q__1);
					    if (rsvec) {
			  r_cnjg(&q__2, &ompq);
			  q__1.r = t * q__2.r, q__1.i = t * q__2.i;
			  crot_(&mvl, &v[p * v_dim1 + 1], &c__1, &v[q * 
				  v_dim1 + 1], &c__1, &cs, &q__1);
					    }
/* Computing MAX */
					    r__1 = 0.f, r__2 = t * apoaq * 
						    aapq1 + 1.f;
					    sva[q] = aaqq * sqrt((f2cmax(r__1,
						    r__2)));
/* Computing MAX */
					    r__1 = 0.f, r__2 = 1.f - t * 
						    aqoap * aapq1;
					    aapp *= sqrt((f2cmax(r__1,r__2)));
/* Computing MAX */
					    r__1 = mxsinj, r__2 = abs(t);
					    mxsinj = f2cmax(r__1,r__2);

					} else {


					    thsign = -r_sign(&c_b27, &aapq1);
					    t = 1.f / (theta + thsign * sqrt(
						    theta * theta + 1.f));
					    cs = sqrt(1.f / (t * t + 1.f));
					    sn = t * cs;

/* Computing MAX */
					    r__1 = mxsinj, r__2 = abs(sn);
					    mxsinj = f2cmax(r__1,r__2);
/* Computing MAX */
					    r__1 = 0.f, r__2 = t * apoaq * 
						    aapq1 + 1.f;
					    sva[q] = aaqq * sqrt((f2cmax(r__1,
						    r__2)));
/* Computing MAX */
					    r__1 = 0.f, r__2 = 1.f - t * 
						    aqoap * aapq1;
					    aapp *= sqrt((f2cmax(r__1,r__2)));

					    r_cnjg(&q__2, &ompq);
					    q__1.r = sn * q__2.r, q__1.i = sn 
						    * q__2.i;
					    crot_(m, &a[p * a_dim1 + 1], &
						    c__1, &a[q * a_dim1 + 1], 
						    &c__1, &cs, &q__1);
					    if (rsvec) {
			  r_cnjg(&q__2, &ompq);
			  q__1.r = sn * q__2.r, q__1.i = sn * q__2.i;
			  crot_(&mvl, &v[p * v_dim1 + 1], &c__1, &v[q * 
				  v_dim1 + 1], &c__1, &cs, &q__1);
					    }
					}
					i__6 = p;
					i__7 = q;
					q__2.r = -d__[i__7].r, q__2.i = -d__[
						i__7].i;
					q__1.r = q__2.r * ompq.r - q__2.i * 
						ompq.i, q__1.i = q__2.r * 
						ompq.i + q__2.i * ompq.r;
					d__[i__6].r = q__1.r, d__[i__6].i = 
						q__1.i;

				    } else {
					ccopy_(m, &a[p * a_dim1 + 1], &c__1, &
						work[1], &c__1);
					clascl_("G", &c__0, &c__0, &aapp, &
						c_b27, m, &c__1, &work[1], 
						lda, &ierr);
					clascl_("G", &c__0, &c__0, &aaqq, &
						c_b27, m, &c__1, &a[q * 
						a_dim1 + 1], lda, &ierr);
					q__1.r = -aapq.r, q__1.i = -aapq.i;
					caxpy_(m, &q__1, &work[1], &c__1, &a[
						q * a_dim1 + 1], &c__1);
					clascl_("G", &c__0, &c__0, &c_b27, &
						aaqq, m, &c__1, &a[q * a_dim1 
						+ 1], lda, &ierr);
/* Computing MAX */
					r__1 = 0.f, r__2 = 1.f - aapq1 * 
						aapq1;
					sva[q] = aaqq * sqrt((f2cmax(r__1,r__2)))
						;
					mxsinj = f2cmax(mxsinj,*sfmin);
				    }
/*           END IF ROTOK THEN ... ELSE */

/*           In the case of cancellation in updating SVA(q), SVA(p) */
/*           recompute SVA(q), SVA(p). */

/* Computing 2nd power */
				    r__1 = sva[q] / aaqq;
				    if (r__1 * r__1 <= rooteps) {
					if (aaqq < rootbig && aaqq > 
						rootsfmin) {
					    sva[q] = scnrm2_(m, &a[q * a_dim1 
						    + 1], &c__1);
					} else {
					    t = 0.f;
					    aaqq = 1.f;
					    classq_(m, &a[q * a_dim1 + 1], &
						    c__1, &t, &aaqq);
					    sva[q] = t * sqrt(aaqq);
					}
				    }
				    if (aapp / aapp0 <= rooteps) {
					if (aapp < rootbig && aapp > 
						rootsfmin) {
					    aapp = scnrm2_(m, &a[p * a_dim1 + 
						    1], &c__1);
					} else {
					    t = 0.f;
					    aapp = 1.f;
					    classq_(m, &a[p * a_dim1 + 1], &
						    c__1, &t, &aapp);
					    aapp = t * sqrt(aapp);
					}
					sva[p] = aapp;
				    }

				} else {
/*        A(:,p) and A(:,q) already numerically orthogonal */
				    if (ir1 == 0) {
					++notrot;
				    }
/* [RTD]      SKIPPED  = SKIPPED  + 1 */
				    ++pskipped;
				}
			    } else {
/*        A(:,q) is zero column */
				if (ir1 == 0) {
				    ++notrot;
				}
				++pskipped;
			    }

			    if (i__ <= swband && pskipped > rowskip) {
				if (ir1 == 0) {
				    aapp = -aapp;
				}
				notrot = 0;
				goto L2103;
			    }

/* L2002: */
			}
/*     END q-LOOP */

L2103:
/*     bailed out of q-loop */

			sva[p] = aapp;

		    } else {
			sva[p] = aapp;
			if (ir1 == 0 && aapp == 0.f) {
/* Computing MIN */
			    i__5 = igl + kbl - 1;
			    notrot = notrot + f2cmin(i__5,*n) - p;
			}
		    }

/* L2001: */
		}
/*     end of the p-loop */
/*     end of doing the block ( ibr, ibr ) */
/* L1002: */
	    }
/*     end of ir1-loop */

/* ... go to the off diagonal blocks */

	    igl = (ibr - 1) * kbl + 1;

	    i__3 = nbl;
	    for (jbc = ibr + 1; jbc <= i__3; ++jbc) {

		jgl = (jbc - 1) * kbl + 1;

/*        doing the block at ( ibr, jbc ) */

		ijblsk = 0;
/* Computing MIN */
		i__5 = igl + kbl - 1;
		i__4 = f2cmin(i__5,*n);
		for (p = igl; p <= i__4; ++p) {

		    aapp = sva[p];
		    if (aapp > 0.f) {

			pskipped = 0;

/* Computing MIN */
			i__6 = jgl + kbl - 1;
			i__5 = f2cmin(i__6,*n);
			for (q = jgl; q <= i__5; ++q) {

			    aaqq = sva[q];
			    if (aaqq > 0.f) {
				aapp0 = aapp;


/*        Safe Gram matrix computation */

				if (aaqq >= 1.f) {
				    if (aapp >= aaqq) {
					rotok = small * aapp <= aaqq;
				    } else {
					rotok = small * aaqq <= aapp;
				    }
				    if (aapp < big / aaqq) {
					cdotc_(&q__3, m, &a[p * a_dim1 + 1], &
						c__1, &a[q * a_dim1 + 1], &
						c__1);
					q__2.r = q__3.r / aaqq, q__2.i = 
						q__3.i / aaqq;
					q__1.r = q__2.r / aapp, q__1.i = 
						q__2.i / aapp;
					aapq.r = q__1.r, aapq.i = q__1.i;
				    } else {
					ccopy_(m, &a[p * a_dim1 + 1], &c__1, &
						work[1], &c__1);
					clascl_("G", &c__0, &c__0, &aapp, &
						c_b27, m, &c__1, &work[1], 
						lda, &ierr);
					cdotc_(&q__2, m, &work[1], &c__1, &a[
						q * a_dim1 + 1], &c__1);
					q__1.r = q__2.r / aaqq, q__1.i = 
						q__2.i / aaqq;
					aapq.r = q__1.r, aapq.i = q__1.i;
				    }
				} else {
				    if (aapp >= aaqq) {
					rotok = aapp <= aaqq / small;
				    } else {
					rotok = aaqq <= aapp / small;
				    }
				    if (aapp > small / aaqq) {
					cdotc_(&q__3, m, &a[p * a_dim1 + 1], &
						c__1, &a[q * a_dim1 + 1], &
						c__1);
					r__1 = f2cmax(aaqq,aapp);
					q__2.r = q__3.r / r__1, q__2.i = 
						q__3.i / r__1;
					r__2 = f2cmin(aaqq,aapp);
					q__1.r = q__2.r / r__2, q__1.i = 
						q__2.i / r__2;
					aapq.r = q__1.r, aapq.i = q__1.i;
				    } else {
					ccopy_(m, &a[q * a_dim1 + 1], &c__1, &
						work[1], &c__1);
					clascl_("G", &c__0, &c__0, &aaqq, &
						c_b27, m, &c__1, &work[1], 
						lda, &ierr);
					cdotc_(&q__2, m, &a[p * a_dim1 + 1], &
						c__1, &work[1], &c__1);
					q__1.r = q__2.r / aapp, q__1.i = 
						q__2.i / aapp;
					aapq.r = q__1.r, aapq.i = q__1.i;
				    }
				}

/*                           AAPQ = AAPQ * CONJG(CWORK(p))*CWORK(q) */
				aapq1 = -c_abs(&aapq);
/* Computing MAX */
				r__1 = mxaapq, r__2 = -aapq1;
				mxaapq = f2cmax(r__1,r__2);

/*        TO rotate or NOT to rotate, THAT is the question ... */

				if (abs(aapq1) > *tol) {
				    r__1 = c_abs(&aapq);
				    q__1.r = aapq.r / r__1, q__1.i = aapq.i / 
					    r__1;
				    ompq.r = q__1.r, ompq.i = q__1.i;
				    notrot = 0;
/* [RTD]      ROTATED  = ROTATED + 1 */
				    pskipped = 0;
				    ++iswrot;

				    if (rotok) {

					aqoap = aaqq / aapp;
					apoaq = aapp / aaqq;
					theta = (r__1 = aqoap - apoaq, abs(
						r__1)) * -.5f / aapq1;
					if (aaqq > aapp0) {
					    theta = -theta;
					}

					if (abs(theta) > bigtheta) {
					    t = .5f / theta;
					    cs = 1.f;
					    r_cnjg(&q__2, &ompq);
					    q__1.r = t * q__2.r, q__1.i = t * 
						    q__2.i;
					    crot_(m, &a[p * a_dim1 + 1], &
						    c__1, &a[q * a_dim1 + 1], 
						    &c__1, &cs, &q__1);
					    if (rsvec) {
			  r_cnjg(&q__2, &ompq);
			  q__1.r = t * q__2.r, q__1.i = t * q__2.i;
			  crot_(&mvl, &v[p * v_dim1 + 1], &c__1, &v[q * 
				  v_dim1 + 1], &c__1, &cs, &q__1);
					    }
/* Computing MAX */
					    r__1 = 0.f, r__2 = t * apoaq * 
						    aapq1 + 1.f;
					    sva[q] = aaqq * sqrt((f2cmax(r__1,
						    r__2)));
/* Computing MAX */
					    r__1 = 0.f, r__2 = 1.f - t * 
						    aqoap * aapq1;
					    aapp *= sqrt((f2cmax(r__1,r__2)));
/* Computing MAX */
					    r__1 = mxsinj, r__2 = abs(t);
					    mxsinj = f2cmax(r__1,r__2);
					} else {


					    thsign = -r_sign(&c_b27, &aapq1);
					    if (aaqq > aapp0) {
			  thsign = -thsign;
					    }
					    t = 1.f / (theta + thsign * sqrt(
						    theta * theta + 1.f));
					    cs = sqrt(1.f / (t * t + 1.f));
					    sn = t * cs;
/* Computing MAX */
					    r__1 = mxsinj, r__2 = abs(sn);
					    mxsinj = f2cmax(r__1,r__2);
/* Computing MAX */
					    r__1 = 0.f, r__2 = t * apoaq * 
						    aapq1 + 1.f;
					    sva[q] = aaqq * sqrt((f2cmax(r__1,
						    r__2)));
/* Computing MAX */
					    r__1 = 0.f, r__2 = 1.f - t * 
						    aqoap * aapq1;
					    aapp *= sqrt((f2cmax(r__1,r__2)));

					    r_cnjg(&q__2, &ompq);
					    q__1.r = sn * q__2.r, q__1.i = sn 
						    * q__2.i;
					    crot_(m, &a[p * a_dim1 + 1], &
						    c__1, &a[q * a_dim1 + 1], 
						    &c__1, &cs, &q__1);
					    if (rsvec) {
			  r_cnjg(&q__2, &ompq);
			  q__1.r = sn * q__2.r, q__1.i = sn * q__2.i;
			  crot_(&mvl, &v[p * v_dim1 + 1], &c__1, &v[q * 
				  v_dim1 + 1], &c__1, &cs, &q__1);
					    }
					}
					i__6 = p;
					i__7 = q;
					q__2.r = -d__[i__7].r, q__2.i = -d__[
						i__7].i;
					q__1.r = q__2.r * ompq.r - q__2.i * 
						ompq.i, q__1.i = q__2.r * 
						ompq.i + q__2.i * ompq.r;
					d__[i__6].r = q__1.r, d__[i__6].i = 
						q__1.i;

				    } else {
					if (aapp > aaqq) {
					    ccopy_(m, &a[p * a_dim1 + 1], &
						    c__1, &work[1], &c__1);
					    clascl_("G", &c__0, &c__0, &aapp, 
						    &c_b27, m, &c__1, &work[1]
						    , lda, &ierr);
					    clascl_("G", &c__0, &c__0, &aaqq, 
						    &c_b27, m, &c__1, &a[q * 
						    a_dim1 + 1], lda, &ierr);
					    q__1.r = -aapq.r, q__1.i = 
						    -aapq.i;
					    caxpy_(m, &q__1, &work[1], &c__1, 
						    &a[q * a_dim1 + 1], &c__1)
						    ;
					    clascl_("G", &c__0, &c__0, &c_b27,
						     &aaqq, m, &c__1, &a[q * 
						    a_dim1 + 1], lda, &ierr);
/* Computing MAX */
					    r__1 = 0.f, r__2 = 1.f - aapq1 * 
						    aapq1;
					    sva[q] = aaqq * sqrt((f2cmax(r__1,
						    r__2)));
					    mxsinj = f2cmax(mxsinj,*sfmin);
					} else {
					    ccopy_(m, &a[q * a_dim1 + 1], &
						    c__1, &work[1], &c__1);
					    clascl_("G", &c__0, &c__0, &aaqq, 
						    &c_b27, m, &c__1, &work[1]
						    , lda, &ierr);
					    clascl_("G", &c__0, &c__0, &aapp, 
						    &c_b27, m, &c__1, &a[p * 
						    a_dim1 + 1], lda, &ierr);
					    r_cnjg(&q__2, &aapq);
					    q__1.r = -q__2.r, q__1.i = 
						    -q__2.i;
					    caxpy_(m, &q__1, &work[1], &c__1, 
						    &a[p * a_dim1 + 1], &c__1)
						    ;
					    clascl_("G", &c__0, &c__0, &c_b27,
						     &aapp, m, &c__1, &a[p * 
						    a_dim1 + 1], lda, &ierr);
/* Computing MAX */
					    r__1 = 0.f, r__2 = 1.f - aapq1 * 
						    aapq1;
					    sva[p] = aapp * sqrt((f2cmax(r__1,
						    r__2)));
					    mxsinj = f2cmax(mxsinj,*sfmin);
					}
				    }
/*           END IF ROTOK THEN ... ELSE */

/*           In the case of cancellation in updating SVA(q), SVA(p) */
/* Computing 2nd power */
				    r__1 = sva[q] / aaqq;
				    if (r__1 * r__1 <= rooteps) {
					if (aaqq < rootbig && aaqq > 
						rootsfmin) {
					    sva[q] = scnrm2_(m, &a[q * a_dim1 
						    + 1], &c__1);
					} else {
					    t = 0.f;
					    aaqq = 1.f;
					    classq_(m, &a[q * a_dim1 + 1], &
						    c__1, &t, &aaqq);
					    sva[q] = t * sqrt(aaqq);
					}
				    }
/* Computing 2nd power */
				    r__1 = aapp / aapp0;
				    if (r__1 * r__1 <= rooteps) {
					if (aapp < rootbig && aapp > 
						rootsfmin) {
					    aapp = scnrm2_(m, &a[p * a_dim1 + 
						    1], &c__1);
					} else {
					    t = 0.f;
					    aapp = 1.f;
					    classq_(m, &a[p * a_dim1 + 1], &
						    c__1, &t, &aapp);
					    aapp = t * sqrt(aapp);
					}
					sva[p] = aapp;
				    }
/*              end of OK rotation */
				} else {
				    ++notrot;
/* [RTD]      SKIPPED  = SKIPPED  + 1 */
				    ++pskipped;
				    ++ijblsk;
				}
			    } else {
				++notrot;
				++pskipped;
				++ijblsk;
			    }

			    if (i__ <= swband && ijblsk >= blskip) {
				sva[p] = aapp;
				notrot = 0;
				goto L2011;
			    }
			    if (i__ <= swband && pskipped > rowskip) {
				aapp = -aapp;
				notrot = 0;
				goto L2203;
			    }

/* L2200: */
			}
/*        end of the q-loop */
L2203:

			sva[p] = aapp;

		    } else {

			if (aapp == 0.f) {
/* Computing MIN */
			    i__5 = jgl + kbl - 1;
			    notrot = notrot + f2cmin(i__5,*n) - jgl + 1;
			}
			if (aapp < 0.f) {
			    notrot = 0;
			}

		    }

/* L2100: */
		}
/*     end of the p-loop */
/* L2010: */
	    }
/*     end of the jbc-loop */
L2011:
/* 2011 bailed out of the jbc-loop */
/* Computing MIN */
	    i__4 = igl + kbl - 1;
	    i__3 = f2cmin(i__4,*n);
	    for (p = igl; p <= i__3; ++p) {
		sva[p] = (r__1 = sva[p], abs(r__1));
/* L2012: */
	    }
/* ** */
/* L2000: */
	}
/* 2000 :: end of the ibr-loop */

	if (sva[*n] < rootbig && sva[*n] > rootsfmin) {
	    sva[*n] = scnrm2_(m, &a[*n * a_dim1 + 1], &c__1);
	} else {
	    t = 0.f;
	    aapp = 1.f;
	    classq_(m, &a[*n * a_dim1 + 1], &c__1, &t, &aapp);
	    sva[*n] = t * sqrt(aapp);
	}

/*     Additional steering devices */

	if (i__ < swband && (mxaapq <= roottol || iswrot <= *n)) {
	    swband = i__;
	}

	if (i__ > swband + 1 && mxaapq < sqrt((real) (*n)) * *tol && (real) (*
		n) * mxaapq * mxsinj < *tol) {
	    goto L1994;
	}

	if (notrot >= emptsw) {
	    goto L1994;
	}

/* L1993: */
    }
/*     end i=1:NSWEEP loop */

/* #:( Reaching this point means that the procedure has not converged. */
    *info = *nsweep - 1;
    goto L1995;

L1994:
/* #:) Reaching this point means numerical convergence after the i-th */
/*     sweep. */

    *info = 0;
/* #:) INFO = 0 confirms successful iterations. */
L1995:

/*     Sort the vector SVA() of column norms. */
    i__1 = *n - 1;
    for (p = 1; p <= i__1; ++p) {
	i__2 = *n - p + 1;
	q = isamax_(&i__2, &sva[p], &c__1) + p - 1;
	if (p != q) {
	    temp1 = sva[p];
	    sva[p] = sva[q];
	    sva[q] = temp1;
	    i__2 = p;
	    aapq.r = d__[i__2].r, aapq.i = d__[i__2].i;
	    i__2 = p;
	    i__3 = q;
	    d__[i__2].r = d__[i__3].r, d__[i__2].i = d__[i__3].i;
	    i__2 = q;
	    d__[i__2].r = aapq.r, d__[i__2].i = aapq.i;
	    cswap_(m, &a[p * a_dim1 + 1], &c__1, &a[q * a_dim1 + 1], &c__1);
	    if (rsvec) {
		cswap_(&mvl, &v[p * v_dim1 + 1], &c__1, &v[q * v_dim1 + 1], &
			c__1);
	    }
	}
/* L5991: */
    }

    return 0;
} /* cgsvj0_ */

