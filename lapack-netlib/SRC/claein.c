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

/* > \brief \b CLAEIN computes a specified right or left eigenvector of an upper Hessenberg matrix by inverse 
iteration. */

/*  =========== DOCUMENTATION =========== */

/* Online html documentation available at */
/*            http://www.netlib.org/lapack/explore-html/ */

/* > \htmlonly */
/* > Download CLAEIN + dependencies */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/claein.
f"> */
/* > [TGZ]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/claein.
f"> */
/* > [ZIP]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/claein.
f"> */
/* > [TXT]</a> */
/* > \endhtmlonly */

/*  Definition: */
/*  =========== */

/*       SUBROUTINE CLAEIN( RIGHTV, NOINIT, N, H, LDH, W, V, B, LDB, RWORK, */
/*                          EPS3, SMLNUM, INFO ) */

/*       LOGICAL            NOINIT, RIGHTV */
/*       INTEGER            INFO, LDB, LDH, N */
/*       REAL               EPS3, SMLNUM */
/*       COMPLEX            W */
/*       REAL               RWORK( * ) */
/*       COMPLEX            B( LDB, * ), H( LDH, * ), V( * ) */


/* > \par Purpose: */
/*  ============= */
/* > */
/* > \verbatim */
/* > */
/* > CLAEIN uses inverse iteration to find a right or left eigenvector */
/* > corresponding to the eigenvalue W of a complex upper Hessenberg */
/* > matrix H. */
/* > \endverbatim */

/*  Arguments: */
/*  ========== */

/* > \param[in] RIGHTV */
/* > \verbatim */
/* >          RIGHTV is LOGICAL */
/* >          = .TRUE. : compute right eigenvector; */
/* >          = .FALSE.: compute left eigenvector. */
/* > \endverbatim */
/* > */
/* > \param[in] NOINIT */
/* > \verbatim */
/* >          NOINIT is LOGICAL */
/* >          = .TRUE. : no initial vector supplied in V */
/* >          = .FALSE.: initial vector supplied in V. */
/* > \endverbatim */
/* > */
/* > \param[in] N */
/* > \verbatim */
/* >          N is INTEGER */
/* >          The order of the matrix H.  N >= 0. */
/* > \endverbatim */
/* > */
/* > \param[in] H */
/* > \verbatim */
/* >          H is COMPLEX array, dimension (LDH,N) */
/* >          The upper Hessenberg matrix H. */
/* > \endverbatim */
/* > */
/* > \param[in] LDH */
/* > \verbatim */
/* >          LDH is INTEGER */
/* >          The leading dimension of the array H.  LDH >= f2cmax(1,N). */
/* > \endverbatim */
/* > */
/* > \param[in] W */
/* > \verbatim */
/* >          W is COMPLEX */
/* >          The eigenvalue of H whose corresponding right or left */
/* >          eigenvector is to be computed. */
/* > \endverbatim */
/* > */
/* > \param[in,out] V */
/* > \verbatim */
/* >          V is COMPLEX array, dimension (N) */
/* >          On entry, if NOINIT = .FALSE., V must contain a starting */
/* >          vector for inverse iteration; otherwise V need not be set. */
/* >          On exit, V contains the computed eigenvector, normalized so */
/* >          that the component of largest magnitude has magnitude 1; here */
/* >          the magnitude of a complex number (x,y) is taken to be */
/* >          |x| + |y|. */
/* > \endverbatim */
/* > */
/* > \param[out] B */
/* > \verbatim */
/* >          B is COMPLEX array, dimension (LDB,N) */
/* > \endverbatim */
/* > */
/* > \param[in] LDB */
/* > \verbatim */
/* >          LDB is INTEGER */
/* >          The leading dimension of the array B.  LDB >= f2cmax(1,N). */
/* > \endverbatim */
/* > */
/* > \param[out] RWORK */
/* > \verbatim */
/* >          RWORK is REAL array, dimension (N) */
/* > \endverbatim */
/* > */
/* > \param[in] EPS3 */
/* > \verbatim */
/* >          EPS3 is REAL */
/* >          A small machine-dependent value which is used to perturb */
/* >          close eigenvalues, and to replace zero pivots. */
/* > \endverbatim */
/* > */
/* > \param[in] SMLNUM */
/* > \verbatim */
/* >          SMLNUM is REAL */
/* >          A machine-dependent value close to the underflow threshold. */
/* > \endverbatim */
/* > */
/* > \param[out] INFO */
/* > \verbatim */
/* >          INFO is INTEGER */
/* >          = 0:  successful exit */
/* >          = 1:  inverse iteration did not converge; V is set to the */
/* >                last iterate. */
/* > \endverbatim */

/*  Authors: */
/*  ======== */

/* > \author Univ. of Tennessee */
/* > \author Univ. of California Berkeley */
/* > \author Univ. of Colorado Denver */
/* > \author NAG Ltd. */

/* > \date December 2016 */

/* > \ingroup complexOTHERauxiliary */

/*  ===================================================================== */
/* Subroutine */ int claein_(logical *rightv, logical *noinit, integer *n, 
	complex *h__, integer *ldh, complex *w, complex *v, complex *b, 
	integer *ldb, real *rwork, real *eps3, real *smlnum, integer *info)
{
    /* System generated locals */
    integer b_dim1, b_offset, h_dim1, h_offset, i__1, i__2, i__3, i__4, i__5;
    real r__1, r__2, r__3, r__4;
    complex q__1, q__2;

    /* Local variables */
    integer ierr;
    complex temp;
    integer i__, j;
    real scale;
    complex x;
    char trans[1];
    real rtemp, rootn, vnorm;
    extern real scnrm2_(integer *, complex *, integer *);
    complex ei, ej;
    extern integer icamax_(integer *, complex *, integer *);
    extern /* Complex */ VOID cladiv_(complex *, complex *, complex *);
    extern /* Subroutine */ int csscal_(integer *, real *, complex *, integer 
	    *), clatrs_(char *, char *, char *, char *, integer *, complex *, 
	    integer *, complex *, real *, real *, integer *);
    extern real scasum_(integer *, complex *, integer *);
    char normin[1];
    real nrmsml, growto;
    integer its;


/*  -- LAPACK auxiliary routine (version 3.7.0) -- */
/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
/*     December 2016 */


/*  ===================================================================== */


    /* Parameter adjustments */
    h_dim1 = *ldh;
    h_offset = 1 + h_dim1 * 1;
    h__ -= h_offset;
    --v;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1 * 1;
    b -= b_offset;
    --rwork;

    /* Function Body */
    *info = 0;

/*     GROWTO is the threshold used in the acceptance test for an */
/*     eigenvector. */

    rootn = sqrt((real) (*n));
    growto = .1f / rootn;
/* Computing MAX */
    r__1 = 1.f, r__2 = *eps3 * rootn;
    nrmsml = f2cmax(r__1,r__2) * *smlnum;

/*     Form B = H - W*I (except that the subdiagonal elements are not */
/*     stored). */

    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = j - 1;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = i__ + j * b_dim1;
	    i__4 = i__ + j * h_dim1;
	    b[i__3].r = h__[i__4].r, b[i__3].i = h__[i__4].i;
/* L10: */
	}
	i__2 = j + j * b_dim1;
	i__3 = j + j * h_dim1;
	q__1.r = h__[i__3].r - w->r, q__1.i = h__[i__3].i - w->i;
	b[i__2].r = q__1.r, b[i__2].i = q__1.i;
/* L20: */
    }

    if (*noinit) {

/*        Initialize V. */

	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    i__2 = i__;
	    v[i__2].r = *eps3, v[i__2].i = 0.f;
/* L30: */
	}
    } else {

/*        Scale supplied initial vector. */

	vnorm = scnrm2_(n, &v[1], &c__1);
	r__1 = *eps3 * rootn / f2cmax(vnorm,nrmsml);
	csscal_(n, &r__1, &v[1], &c__1);
    }

    if (*rightv) {

/*        LU decomposition with partial pivoting of B, replacing zero */
/*        pivots by EPS3. */

	i__1 = *n - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    i__2 = i__ + 1 + i__ * h_dim1;
	    ei.r = h__[i__2].r, ei.i = h__[i__2].i;
	    i__2 = i__ + i__ * b_dim1;
	    if ((r__1 = b[i__2].r, abs(r__1)) + (r__2 = r_imag(&b[i__ + i__ * 
		    b_dim1]), abs(r__2)) < (r__3 = ei.r, abs(r__3)) + (r__4 = 
		    r_imag(&ei), abs(r__4))) {

/*              Interchange rows and eliminate. */

		cladiv_(&q__1, &b[i__ + i__ * b_dim1], &ei);
		x.r = q__1.r, x.i = q__1.i;
		i__2 = i__ + i__ * b_dim1;
		b[i__2].r = ei.r, b[i__2].i = ei.i;
		i__2 = *n;
		for (j = i__ + 1; j <= i__2; ++j) {
		    i__3 = i__ + 1 + j * b_dim1;
		    temp.r = b[i__3].r, temp.i = b[i__3].i;
		    i__3 = i__ + 1 + j * b_dim1;
		    i__4 = i__ + j * b_dim1;
		    q__2.r = x.r * temp.r - x.i * temp.i, q__2.i = x.r * 
			    temp.i + x.i * temp.r;
		    q__1.r = b[i__4].r - q__2.r, q__1.i = b[i__4].i - q__2.i;
		    b[i__3].r = q__1.r, b[i__3].i = q__1.i;
		    i__3 = i__ + j * b_dim1;
		    b[i__3].r = temp.r, b[i__3].i = temp.i;
/* L40: */
		}
	    } else {

/*              Eliminate without interchange. */

		i__2 = i__ + i__ * b_dim1;
		if (b[i__2].r == 0.f && b[i__2].i == 0.f) {
		    i__3 = i__ + i__ * b_dim1;
		    b[i__3].r = *eps3, b[i__3].i = 0.f;
		}
		cladiv_(&q__1, &ei, &b[i__ + i__ * b_dim1]);
		x.r = q__1.r, x.i = q__1.i;
		if (x.r != 0.f || x.i != 0.f) {
		    i__2 = *n;
		    for (j = i__ + 1; j <= i__2; ++j) {
			i__3 = i__ + 1 + j * b_dim1;
			i__4 = i__ + 1 + j * b_dim1;
			i__5 = i__ + j * b_dim1;
			q__2.r = x.r * b[i__5].r - x.i * b[i__5].i, q__2.i = 
				x.r * b[i__5].i + x.i * b[i__5].r;
			q__1.r = b[i__4].r - q__2.r, q__1.i = b[i__4].i - 
				q__2.i;
			b[i__3].r = q__1.r, b[i__3].i = q__1.i;
/* L50: */
		    }
		}
	    }
/* L60: */
	}
	i__1 = *n + *n * b_dim1;
	if (b[i__1].r == 0.f && b[i__1].i == 0.f) {
	    i__2 = *n + *n * b_dim1;
	    b[i__2].r = *eps3, b[i__2].i = 0.f;
	}

	*(unsigned char *)trans = 'N';

    } else {

/*        UL decomposition with partial pivoting of B, replacing zero */
/*        pivots by EPS3. */

	for (j = *n; j >= 2; --j) {
	    i__1 = j + (j - 1) * h_dim1;
	    ej.r = h__[i__1].r, ej.i = h__[i__1].i;
	    i__1 = j + j * b_dim1;
	    if ((r__1 = b[i__1].r, abs(r__1)) + (r__2 = r_imag(&b[j + j * 
		    b_dim1]), abs(r__2)) < (r__3 = ej.r, abs(r__3)) + (r__4 = 
		    r_imag(&ej), abs(r__4))) {

/*              Interchange columns and eliminate. */

		cladiv_(&q__1, &b[j + j * b_dim1], &ej);
		x.r = q__1.r, x.i = q__1.i;
		i__1 = j + j * b_dim1;
		b[i__1].r = ej.r, b[i__1].i = ej.i;
		i__1 = j - 1;
		for (i__ = 1; i__ <= i__1; ++i__) {
		    i__2 = i__ + (j - 1) * b_dim1;
		    temp.r = b[i__2].r, temp.i = b[i__2].i;
		    i__2 = i__ + (j - 1) * b_dim1;
		    i__3 = i__ + j * b_dim1;
		    q__2.r = x.r * temp.r - x.i * temp.i, q__2.i = x.r * 
			    temp.i + x.i * temp.r;
		    q__1.r = b[i__3].r - q__2.r, q__1.i = b[i__3].i - q__2.i;
		    b[i__2].r = q__1.r, b[i__2].i = q__1.i;
		    i__2 = i__ + j * b_dim1;
		    b[i__2].r = temp.r, b[i__2].i = temp.i;
/* L70: */
		}
	    } else {

/*              Eliminate without interchange. */

		i__1 = j + j * b_dim1;
		if (b[i__1].r == 0.f && b[i__1].i == 0.f) {
		    i__2 = j + j * b_dim1;
		    b[i__2].r = *eps3, b[i__2].i = 0.f;
		}
		cladiv_(&q__1, &ej, &b[j + j * b_dim1]);
		x.r = q__1.r, x.i = q__1.i;
		if (x.r != 0.f || x.i != 0.f) {
		    i__1 = j - 1;
		    for (i__ = 1; i__ <= i__1; ++i__) {
			i__2 = i__ + (j - 1) * b_dim1;
			i__3 = i__ + (j - 1) * b_dim1;
			i__4 = i__ + j * b_dim1;
			q__2.r = x.r * b[i__4].r - x.i * b[i__4].i, q__2.i = 
				x.r * b[i__4].i + x.i * b[i__4].r;
			q__1.r = b[i__3].r - q__2.r, q__1.i = b[i__3].i - 
				q__2.i;
			b[i__2].r = q__1.r, b[i__2].i = q__1.i;
/* L80: */
		    }
		}
	    }
/* L90: */
	}
	i__1 = b_dim1 + 1;
	if (b[i__1].r == 0.f && b[i__1].i == 0.f) {
	    i__2 = b_dim1 + 1;
	    b[i__2].r = *eps3, b[i__2].i = 0.f;
	}

	*(unsigned char *)trans = 'C';

    }

    *(unsigned char *)normin = 'N';
    i__1 = *n;
    for (its = 1; its <= i__1; ++its) {

/*        Solve U*x = scale*v for a right eigenvector */
/*          or U**H *x = scale*v for a left eigenvector, */
/*        overwriting x on v. */

	clatrs_("Upper", trans, "Nonunit", normin, n, &b[b_offset], ldb, &v[1]
		, &scale, &rwork[1], &ierr);
	*(unsigned char *)normin = 'Y';

/*        Test for sufficient growth in the norm of v. */

	vnorm = scasum_(n, &v[1], &c__1);
	if (vnorm >= growto * scale) {
	    goto L120;
	}

/*        Choose new orthogonal starting vector and try again. */

	rtemp = *eps3 / (rootn + 1.f);
	v[1].r = *eps3, v[1].i = 0.f;
	i__2 = *n;
	for (i__ = 2; i__ <= i__2; ++i__) {
	    i__3 = i__;
	    v[i__3].r = rtemp, v[i__3].i = 0.f;
/* L100: */
	}
	i__2 = *n - its + 1;
	i__3 = *n - its + 1;
	r__1 = *eps3 * rootn;
	q__1.r = v[i__3].r - r__1, q__1.i = v[i__3].i;
	v[i__2].r = q__1.r, v[i__2].i = q__1.i;
/* L110: */
    }

/*     Failure to find eigenvector in N iterations. */

    *info = 1;

L120:

/*     Normalize eigenvector. */

    i__ = icamax_(n, &v[1], &c__1);
    i__1 = i__;
    r__3 = 1.f / ((r__1 = v[i__1].r, abs(r__1)) + (r__2 = r_imag(&v[i__]), 
	    abs(r__2)));
    csscal_(n, &r__3, &v[1], &c__1);

    return 0;

/*     End of CLAEIN */

} /* claein_ */

