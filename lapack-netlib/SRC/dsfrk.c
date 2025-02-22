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



/* > \brief \b DSFRK performs a symmetric rank-k operation for matrix in RFP format. */

/*  =========== DOCUMENTATION =========== */

/* Online html documentation available at */
/*            http://www.netlib.org/lapack/explore-html/ */

/* > \htmlonly */
/* > Download DSFRK + dependencies */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/dsfrk.f
"> */
/* > [TGZ]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/dsfrk.f
"> */
/* > [ZIP]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/dsfrk.f
"> */
/* > [TXT]</a> */
/* > \endhtmlonly */

/*  Definition: */
/*  =========== */

/*       SUBROUTINE DSFRK( TRANSR, UPLO, TRANS, N, K, ALPHA, A, LDA, BETA, */
/*                         C ) */

/*       DOUBLE PRECISION   ALPHA, BETA */
/*       INTEGER            K, LDA, N */
/*       CHARACTER          TRANS, TRANSR, UPLO */
/*       DOUBLE PRECISION   A( LDA, * ), C( * ) */


/* > \par Purpose: */
/*  ============= */
/* > */
/* > \verbatim */
/* > */
/* > Level 3 BLAS like routine for C in RFP Format. */
/* > */
/* > DSFRK performs one of the symmetric rank--k operations */
/* > */
/* >    C := alpha*A*A**T + beta*C, */
/* > */
/* > or */
/* > */
/* >    C := alpha*A**T*A + beta*C, */
/* > */
/* > where alpha and beta are real scalars, C is an n--by--n symmetric */
/* > matrix and A is an n--by--k matrix in the first case and a k--by--n */
/* > matrix in the second case. */
/* > \endverbatim */

/*  Arguments: */
/*  ========== */

/* > \param[in] TRANSR */
/* > \verbatim */
/* >          TRANSR is CHARACTER*1 */
/* >          = 'N':  The Normal Form of RFP A is stored; */
/* >          = 'T':  The Transpose Form of RFP A is stored. */
/* > \endverbatim */
/* > */
/* > \param[in] UPLO */
/* > \verbatim */
/* >          UPLO is CHARACTER*1 */
/* >           On  entry, UPLO specifies whether the upper or lower */
/* >           triangular part of the array C is to be referenced as */
/* >           follows: */
/* > */
/* >              UPLO = 'U' or 'u'   Only the upper triangular part of C */
/* >                                  is to be referenced. */
/* > */
/* >              UPLO = 'L' or 'l'   Only the lower triangular part of C */
/* >                                  is to be referenced. */
/* > */
/* >           Unchanged on exit. */
/* > \endverbatim */
/* > */
/* > \param[in] TRANS */
/* > \verbatim */
/* >          TRANS is CHARACTER*1 */
/* >           On entry, TRANS specifies the operation to be performed as */
/* >           follows: */
/* > */
/* >              TRANS = 'N' or 'n'   C := alpha*A*A**T + beta*C. */
/* > */
/* >              TRANS = 'T' or 't'   C := alpha*A**T*A + beta*C. */
/* > */
/* >           Unchanged on exit. */
/* > \endverbatim */
/* > */
/* > \param[in] N */
/* > \verbatim */
/* >          N is INTEGER */
/* >           On entry, N specifies the order of the matrix C. N must be */
/* >           at least zero. */
/* >           Unchanged on exit. */
/* > \endverbatim */
/* > */
/* > \param[in] K */
/* > \verbatim */
/* >          K is INTEGER */
/* >           On entry with TRANS = 'N' or 'n', K specifies the number */
/* >           of  columns of the matrix A, and on entry with TRANS = 'T' */
/* >           or 't', K specifies the number of rows of the matrix A. K */
/* >           must be at least zero. */
/* >           Unchanged on exit. */
/* > \endverbatim */
/* > */
/* > \param[in] ALPHA */
/* > \verbatim */
/* >          ALPHA is DOUBLE PRECISION */
/* >           On entry, ALPHA specifies the scalar alpha. */
/* >           Unchanged on exit. */
/* > \endverbatim */
/* > */
/* > \param[in] A */
/* > \verbatim */
/* >          A is DOUBLE PRECISION array, dimension (LDA,ka) */
/* >           where KA */
/* >           is K  when TRANS = 'N' or 'n', and is N otherwise. Before */
/* >           entry with TRANS = 'N' or 'n', the leading N--by--K part of */
/* >           the array A must contain the matrix A, otherwise the leading */
/* >           K--by--N part of the array A must contain the matrix A. */
/* >           Unchanged on exit. */
/* > \endverbatim */
/* > */
/* > \param[in] LDA */
/* > \verbatim */
/* >          LDA is INTEGER */
/* >           On entry, LDA specifies the first dimension of A as declared */
/* >           in  the  calling  (sub)  program.   When  TRANS = 'N' or 'n' */
/* >           then  LDA must be at least  f2cmax( 1, n ), otherwise  LDA must */
/* >           be at least  f2cmax( 1, k ). */
/* >           Unchanged on exit. */
/* > \endverbatim */
/* > */
/* > \param[in] BETA */
/* > \verbatim */
/* >          BETA is DOUBLE PRECISION */
/* >           On entry, BETA specifies the scalar beta. */
/* >           Unchanged on exit. */
/* > \endverbatim */
/* > */
/* > \param[in,out] C */
/* > \verbatim */
/* >          C is DOUBLE PRECISION array, dimension (NT) */
/* >           NT = N*(N+1)/2. On entry, the symmetric matrix C in RFP */
/* >           Format. RFP Format is described by TRANSR, UPLO and N. */
/* > \endverbatim */

/*  Authors: */
/*  ======== */

/* > \author Univ. of Tennessee */
/* > \author Univ. of California Berkeley */
/* > \author Univ. of Colorado Denver */
/* > \author NAG Ltd. */

/* > \date December 2016 */

/* > \ingroup doubleOTHERcomputational */

/*  ===================================================================== */
/* Subroutine */ int dsfrk_(char *transr, char *uplo, char *trans, integer *n,
	 integer *k, doublereal *alpha, doublereal *a, integer *lda, 
	doublereal *beta, doublereal *c__)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1;

    /* Local variables */
    integer info, j;
    logical normaltransr;
    extern /* Subroutine */ int dgemm_(char *, char *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, integer *, doublereal *, 
	    integer *, doublereal *, doublereal *, integer *);
    extern logical lsame_(char *, char *);
    integer nrowa;
    logical lower;
    extern /* Subroutine */ int dsyrk_(char *, char *, integer *, integer *, 
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *,
	     integer *);
    integer n1, n2, nk;
    extern /* Subroutine */ int xerbla_(char *, integer *, ftnlen);
    logical nisodd, notrans;


/*  -- LAPACK computational routine (version 3.7.0) -- */
/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
/*     December 2016 */


/*  ===================================================================== */


/*     Test the input parameters. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --c__;

    /* Function Body */
    info = 0;
    normaltransr = lsame_(transr, "N");
    lower = lsame_(uplo, "L");
    notrans = lsame_(trans, "N");

    if (notrans) {
	nrowa = *n;
    } else {
	nrowa = *k;
    }

    if (! normaltransr && ! lsame_(transr, "T")) {
	info = -1;
    } else if (! lower && ! lsame_(uplo, "U")) {
	info = -2;
    } else if (! notrans && ! lsame_(trans, "T")) {
	info = -3;
    } else if (*n < 0) {
	info = -4;
    } else if (*k < 0) {
	info = -5;
    } else if (*lda < f2cmax(1,nrowa)) {
	info = -8;
    }
    if (info != 0) {
	i__1 = -info;
	xerbla_("DSFRK ", &i__1, (ftnlen)6);
	return 0;
    }

/*     Quick return if possible. */

/*     The quick return case: ((ALPHA.EQ.0).AND.(BETA.NE.ZERO)) is not */
/*     done (it is in DSYRK for example) and left in the general case. */

    if (*n == 0 || (*alpha == 0. || *k == 0) && *beta == 1.) {
	return 0;
    }

    if (*alpha == 0. && *beta == 0.) {
	i__1 = *n * (*n + 1) / 2;
	for (j = 1; j <= i__1; ++j) {
	    c__[j] = 0.;
	}
	return 0;
    }

/*     C is N-by-N. */
/*     If N is odd, set NISODD = .TRUE., and N1 and N2. */
/*     If N is even, NISODD = .FALSE., and NK. */

    if (*n % 2 == 0) {
	nisodd = FALSE_;
	nk = *n / 2;
    } else {
	nisodd = TRUE_;
	if (lower) {
	    n2 = *n / 2;
	    n1 = *n - n2;
	} else {
	    n1 = *n / 2;
	    n2 = *n - n1;
	}
    }

    if (nisodd) {

/*        N is odd */

	if (normaltransr) {

/*           N is odd and TRANSR = 'N' */

	    if (lower) {

/*              N is odd, TRANSR = 'N', and UPLO = 'L' */

		if (notrans) {

/*                 N is odd, TRANSR = 'N', UPLO = 'L', and TRANS = 'N' */

		    dsyrk_("L", "N", &n1, k, alpha, &a[a_dim1 + 1], lda, beta,
			     &c__[1], n);
		    dsyrk_("U", "N", &n2, k, alpha, &a[n1 + 1 + a_dim1], lda, 
			    beta, &c__[*n + 1], n);
		    dgemm_("N", "T", &n2, &n1, k, alpha, &a[n1 + 1 + a_dim1], 
			    lda, &a[a_dim1 + 1], lda, beta, &c__[n1 + 1], n);

		} else {

/*                 N is odd, TRANSR = 'N', UPLO = 'L', and TRANS = 'T' */

		    dsyrk_("L", "T", &n1, k, alpha, &a[a_dim1 + 1], lda, beta,
			     &c__[1], n);
		    dsyrk_("U", "T", &n2, k, alpha, &a[(n1 + 1) * a_dim1 + 1],
			     lda, beta, &c__[*n + 1], n)
			    ;
		    dgemm_("T", "N", &n2, &n1, k, alpha, &a[(n1 + 1) * a_dim1 
			    + 1], lda, &a[a_dim1 + 1], lda, beta, &c__[n1 + 1]
			    , n);

		}

	    } else {

/*              N is odd, TRANSR = 'N', and UPLO = 'U' */

		if (notrans) {

/*                 N is odd, TRANSR = 'N', UPLO = 'U', and TRANS = 'N' */

		    dsyrk_("L", "N", &n1, k, alpha, &a[a_dim1 + 1], lda, beta,
			     &c__[n2 + 1], n);
		    dsyrk_("U", "N", &n2, k, alpha, &a[n2 + a_dim1], lda, 
			    beta, &c__[n1 + 1], n);
		    dgemm_("N", "T", &n1, &n2, k, alpha, &a[a_dim1 + 1], lda, 
			    &a[n2 + a_dim1], lda, beta, &c__[1], n);

		} else {

/*                 N is odd, TRANSR = 'N', UPLO = 'U', and TRANS = 'T' */

		    dsyrk_("L", "T", &n1, k, alpha, &a[a_dim1 + 1], lda, beta,
			     &c__[n2 + 1], n);
		    dsyrk_("U", "T", &n2, k, alpha, &a[n2 * a_dim1 + 1], lda, 
			    beta, &c__[n1 + 1], n);
		    dgemm_("T", "N", &n1, &n2, k, alpha, &a[a_dim1 + 1], lda, 
			    &a[n2 * a_dim1 + 1], lda, beta, &c__[1], n);

		}

	    }

	} else {

/*           N is odd, and TRANSR = 'T' */

	    if (lower) {

/*              N is odd, TRANSR = 'T', and UPLO = 'L' */

		if (notrans) {

/*                 N is odd, TRANSR = 'T', UPLO = 'L', and TRANS = 'N' */

		    dsyrk_("U", "N", &n1, k, alpha, &a[a_dim1 + 1], lda, beta,
			     &c__[1], &n1);
		    dsyrk_("L", "N", &n2, k, alpha, &a[n1 + 1 + a_dim1], lda, 
			    beta, &c__[2], &n1);
		    dgemm_("N", "T", &n1, &n2, k, alpha, &a[a_dim1 + 1], lda, 
			    &a[n1 + 1 + a_dim1], lda, beta, &c__[n1 * n1 + 1],
			     &n1);

		} else {

/*                 N is odd, TRANSR = 'T', UPLO = 'L', and TRANS = 'T' */

		    dsyrk_("U", "T", &n1, k, alpha, &a[a_dim1 + 1], lda, beta,
			     &c__[1], &n1);
		    dsyrk_("L", "T", &n2, k, alpha, &a[(n1 + 1) * a_dim1 + 1],
			     lda, beta, &c__[2], &n1);
		    dgemm_("T", "N", &n1, &n2, k, alpha, &a[a_dim1 + 1], lda, 
			    &a[(n1 + 1) * a_dim1 + 1], lda, beta, &c__[n1 * 
			    n1 + 1], &n1);

		}

	    } else {

/*              N is odd, TRANSR = 'T', and UPLO = 'U' */

		if (notrans) {

/*                 N is odd, TRANSR = 'T', UPLO = 'U', and TRANS = 'N' */

		    dsyrk_("U", "N", &n1, k, alpha, &a[a_dim1 + 1], lda, beta,
			     &c__[n2 * n2 + 1], &n2);
		    dsyrk_("L", "N", &n2, k, alpha, &a[n1 + 1 + a_dim1], lda, 
			    beta, &c__[n1 * n2 + 1], &n2);
		    dgemm_("N", "T", &n2, &n1, k, alpha, &a[n1 + 1 + a_dim1], 
			    lda, &a[a_dim1 + 1], lda, beta, &c__[1], &n2);

		} else {

/*                 N is odd, TRANSR = 'T', UPLO = 'U', and TRANS = 'T' */

		    dsyrk_("U", "T", &n1, k, alpha, &a[a_dim1 + 1], lda, beta,
			     &c__[n2 * n2 + 1], &n2);
		    dsyrk_("L", "T", &n2, k, alpha, &a[(n1 + 1) * a_dim1 + 1],
			     lda, beta, &c__[n1 * n2 + 1], &n2);
		    dgemm_("T", "N", &n2, &n1, k, alpha, &a[(n1 + 1) * a_dim1 
			    + 1], lda, &a[a_dim1 + 1], lda, beta, &c__[1], &
			    n2);

		}

	    }

	}

    } else {

/*        N is even */

	if (normaltransr) {

/*           N is even and TRANSR = 'N' */

	    if (lower) {

/*              N is even, TRANSR = 'N', and UPLO = 'L' */

		if (notrans) {

/*                 N is even, TRANSR = 'N', UPLO = 'L', and TRANS = 'N' */

		    i__1 = *n + 1;
		    dsyrk_("L", "N", &nk, k, alpha, &a[a_dim1 + 1], lda, beta,
			     &c__[2], &i__1);
		    i__1 = *n + 1;
		    dsyrk_("U", "N", &nk, k, alpha, &a[nk + 1 + a_dim1], lda, 
			    beta, &c__[1], &i__1);
		    i__1 = *n + 1;
		    dgemm_("N", "T", &nk, &nk, k, alpha, &a[nk + 1 + a_dim1], 
			    lda, &a[a_dim1 + 1], lda, beta, &c__[nk + 2], &
			    i__1);

		} else {

/*                 N is even, TRANSR = 'N', UPLO = 'L', and TRANS = 'T' */

		    i__1 = *n + 1;
		    dsyrk_("L", "T", &nk, k, alpha, &a[a_dim1 + 1], lda, beta,
			     &c__[2], &i__1);
		    i__1 = *n + 1;
		    dsyrk_("U", "T", &nk, k, alpha, &a[(nk + 1) * a_dim1 + 1],
			     lda, beta, &c__[1], &i__1);
		    i__1 = *n + 1;
		    dgemm_("T", "N", &nk, &nk, k, alpha, &a[(nk + 1) * a_dim1 
			    + 1], lda, &a[a_dim1 + 1], lda, beta, &c__[nk + 2]
			    , &i__1);

		}

	    } else {

/*              N is even, TRANSR = 'N', and UPLO = 'U' */

		if (notrans) {

/*                 N is even, TRANSR = 'N', UPLO = 'U', and TRANS = 'N' */

		    i__1 = *n + 1;
		    dsyrk_("L", "N", &nk, k, alpha, &a[a_dim1 + 1], lda, beta,
			     &c__[nk + 2], &i__1);
		    i__1 = *n + 1;
		    dsyrk_("U", "N", &nk, k, alpha, &a[nk + 1 + a_dim1], lda, 
			    beta, &c__[nk + 1], &i__1);
		    i__1 = *n + 1;
		    dgemm_("N", "T", &nk, &nk, k, alpha, &a[a_dim1 + 1], lda, 
			    &a[nk + 1 + a_dim1], lda, beta, &c__[1], &i__1);

		} else {

/*                 N is even, TRANSR = 'N', UPLO = 'U', and TRANS = 'T' */

		    i__1 = *n + 1;
		    dsyrk_("L", "T", &nk, k, alpha, &a[a_dim1 + 1], lda, beta,
			     &c__[nk + 2], &i__1);
		    i__1 = *n + 1;
		    dsyrk_("U", "T", &nk, k, alpha, &a[(nk + 1) * a_dim1 + 1],
			     lda, beta, &c__[nk + 1], &i__1);
		    i__1 = *n + 1;
		    dgemm_("T", "N", &nk, &nk, k, alpha, &a[a_dim1 + 1], lda, 
			    &a[(nk + 1) * a_dim1 + 1], lda, beta, &c__[1], &
			    i__1);

		}

	    }

	} else {

/*           N is even, and TRANSR = 'T' */

	    if (lower) {

/*              N is even, TRANSR = 'T', and UPLO = 'L' */

		if (notrans) {

/*                 N is even, TRANSR = 'T', UPLO = 'L', and TRANS = 'N' */

		    dsyrk_("U", "N", &nk, k, alpha, &a[a_dim1 + 1], lda, beta,
			     &c__[nk + 1], &nk);
		    dsyrk_("L", "N", &nk, k, alpha, &a[nk + 1 + a_dim1], lda, 
			    beta, &c__[1], &nk);
		    dgemm_("N", "T", &nk, &nk, k, alpha, &a[a_dim1 + 1], lda, 
			    &a[nk + 1 + a_dim1], lda, beta, &c__[(nk + 1) * 
			    nk + 1], &nk);

		} else {

/*                 N is even, TRANSR = 'T', UPLO = 'L', and TRANS = 'T' */

		    dsyrk_("U", "T", &nk, k, alpha, &a[a_dim1 + 1], lda, beta,
			     &c__[nk + 1], &nk);
		    dsyrk_("L", "T", &nk, k, alpha, &a[(nk + 1) * a_dim1 + 1],
			     lda, beta, &c__[1], &nk);
		    dgemm_("T", "N", &nk, &nk, k, alpha, &a[a_dim1 + 1], lda, 
			    &a[(nk + 1) * a_dim1 + 1], lda, beta, &c__[(nk + 
			    1) * nk + 1], &nk);

		}

	    } else {

/*              N is even, TRANSR = 'T', and UPLO = 'U' */

		if (notrans) {

/*                 N is even, TRANSR = 'T', UPLO = 'U', and TRANS = 'N' */

		    dsyrk_("U", "N", &nk, k, alpha, &a[a_dim1 + 1], lda, beta,
			     &c__[nk * (nk + 1) + 1], &nk);
		    dsyrk_("L", "N", &nk, k, alpha, &a[nk + 1 + a_dim1], lda, 
			    beta, &c__[nk * nk + 1], &nk);
		    dgemm_("N", "T", &nk, &nk, k, alpha, &a[nk + 1 + a_dim1], 
			    lda, &a[a_dim1 + 1], lda, beta, &c__[1], &nk);

		} else {

/*                 N is even, TRANSR = 'T', UPLO = 'U', and TRANS = 'T' */

		    dsyrk_("U", "T", &nk, k, alpha, &a[a_dim1 + 1], lda, beta,
			     &c__[nk * (nk + 1) + 1], &nk);
		    dsyrk_("L", "T", &nk, k, alpha, &a[(nk + 1) * a_dim1 + 1],
			     lda, beta, &c__[nk * nk + 1], &nk);
		    dgemm_("T", "N", &nk, &nk, k, alpha, &a[(nk + 1) * a_dim1 
			    + 1], lda, &a[a_dim1 + 1], lda, beta, &c__[1], &
			    nk);

		}

	    }

	}

    }

    return 0;

/*     End of DSFRK */

} /* dsfrk_ */

