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
static logical c_false = FALSE_;
static integer c__2 = 2;
static doublereal c_b26 = 1.;
static doublereal c_b30 = 0.;
static logical c_true = TRUE_;

/* > \brief \b DTRSYL */

/*  =========== DOCUMENTATION =========== */

/* Online html documentation available at */
/*            http://www.netlib.org/lapack/explore-html/ */

/* > \htmlonly */
/* > Download DTRSYL + dependencies */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/dtrsyl.
f"> */
/* > [TGZ]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/dtrsyl.
f"> */
/* > [ZIP]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/dtrsyl.
f"> */
/* > [TXT]</a> */
/* > \endhtmlonly */

/*  Definition: */
/*  =========== */

/*       SUBROUTINE DTRSYL( TRANA, TRANB, ISGN, M, N, A, LDA, B, LDB, C, */
/*                          LDC, SCALE, INFO ) */

/*       CHARACTER          TRANA, TRANB */
/*       INTEGER            INFO, ISGN, LDA, LDB, LDC, M, N */
/*       DOUBLE PRECISION   SCALE */
/*       DOUBLE PRECISION   A( LDA, * ), B( LDB, * ), C( LDC, * ) */


/* > \par Purpose: */
/*  ============= */
/* > */
/* > \verbatim */
/* > */
/* > DTRSYL solves the real Sylvester matrix equation: */
/* > */
/* >    op(A)*X + X*op(B) = scale*C or */
/* >    op(A)*X - X*op(B) = scale*C, */
/* > */
/* > where op(A) = A or A**T, and  A and B are both upper quasi- */
/* > triangular. A is M-by-M and B is N-by-N; the right hand side C and */
/* > the solution X are M-by-N; and scale is an output scale factor, set */
/* > <= 1 to avoid overflow in X. */
/* > */
/* > A and B must be in Schur canonical form (as returned by DHSEQR), that */
/* > is, block upper triangular with 1-by-1 and 2-by-2 diagonal blocks; */
/* > each 2-by-2 diagonal block has its diagonal elements equal and its */
/* > off-diagonal elements of opposite sign. */
/* > \endverbatim */

/*  Arguments: */
/*  ========== */

/* > \param[in] TRANA */
/* > \verbatim */
/* >          TRANA is CHARACTER*1 */
/* >          Specifies the option op(A): */
/* >          = 'N': op(A) = A    (No transpose) */
/* >          = 'T': op(A) = A**T (Transpose) */
/* >          = 'C': op(A) = A**H (Conjugate transpose = Transpose) */
/* > \endverbatim */
/* > */
/* > \param[in] TRANB */
/* > \verbatim */
/* >          TRANB is CHARACTER*1 */
/* >          Specifies the option op(B): */
/* >          = 'N': op(B) = B    (No transpose) */
/* >          = 'T': op(B) = B**T (Transpose) */
/* >          = 'C': op(B) = B**H (Conjugate transpose = Transpose) */
/* > \endverbatim */
/* > */
/* > \param[in] ISGN */
/* > \verbatim */
/* >          ISGN is INTEGER */
/* >          Specifies the sign in the equation: */
/* >          = +1: solve op(A)*X + X*op(B) = scale*C */
/* >          = -1: solve op(A)*X - X*op(B) = scale*C */
/* > \endverbatim */
/* > */
/* > \param[in] M */
/* > \verbatim */
/* >          M is INTEGER */
/* >          The order of the matrix A, and the number of rows in the */
/* >          matrices X and C. M >= 0. */
/* > \endverbatim */
/* > */
/* > \param[in] N */
/* > \verbatim */
/* >          N is INTEGER */
/* >          The order of the matrix B, and the number of columns in the */
/* >          matrices X and C. N >= 0. */
/* > \endverbatim */
/* > */
/* > \param[in] A */
/* > \verbatim */
/* >          A is DOUBLE PRECISION array, dimension (LDA,M) */
/* >          The upper quasi-triangular matrix A, in Schur canonical form. */
/* > \endverbatim */
/* > */
/* > \param[in] LDA */
/* > \verbatim */
/* >          LDA is INTEGER */
/* >          The leading dimension of the array A. LDA >= f2cmax(1,M). */
/* > \endverbatim */
/* > */
/* > \param[in] B */
/* > \verbatim */
/* >          B is DOUBLE PRECISION array, dimension (LDB,N) */
/* >          The upper quasi-triangular matrix B, in Schur canonical form. */
/* > \endverbatim */
/* > */
/* > \param[in] LDB */
/* > \verbatim */
/* >          LDB is INTEGER */
/* >          The leading dimension of the array B. LDB >= f2cmax(1,N). */
/* > \endverbatim */
/* > */
/* > \param[in,out] C */
/* > \verbatim */
/* >          C is DOUBLE PRECISION array, dimension (LDC,N) */
/* >          On entry, the M-by-N right hand side matrix C. */
/* >          On exit, C is overwritten by the solution matrix X. */
/* > \endverbatim */
/* > */
/* > \param[in] LDC */
/* > \verbatim */
/* >          LDC is INTEGER */
/* >          The leading dimension of the array C. LDC >= f2cmax(1,M) */
/* > \endverbatim */
/* > */
/* > \param[out] SCALE */
/* > \verbatim */
/* >          SCALE is DOUBLE PRECISION */
/* >          The scale factor, scale, set <= 1 to avoid overflow in X. */
/* > \endverbatim */
/* > */
/* > \param[out] INFO */
/* > \verbatim */
/* >          INFO is INTEGER */
/* >          = 0: successful exit */
/* >          < 0: if INFO = -i, the i-th argument had an illegal value */
/* >          = 1: A and B have common or very close eigenvalues; perturbed */
/* >               values were used to solve the equation (but the matrices */
/* >               A and B are unchanged). */
/* > \endverbatim */

/*  Authors: */
/*  ======== */

/* > \author Univ. of Tennessee */
/* > \author Univ. of California Berkeley */
/* > \author Univ. of Colorado Denver */
/* > \author NAG Ltd. */

/* > \date December 2016 */

/* > \ingroup doubleSYcomputational */

/*  ===================================================================== */
/* Subroutine */ int dtrsyl_(char *trana, char *tranb, integer *isgn, integer 
	*m, integer *n, doublereal *a, integer *lda, doublereal *b, integer *
	ldb, doublereal *c__, integer *ldc, doublereal *scale, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, c_dim1, c_offset, i__1, i__2, 
	    i__3, i__4;
    doublereal d__1, d__2;

    /* Local variables */
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    integer ierr;
    doublereal smin, suml, sumr;
    integer j, k, l;
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *);
    doublereal x[4]	/* was [2][2] */;
    extern logical lsame_(char *, char *);
    integer knext, lnext, k1, k2, l1, l2;
    doublereal xnorm;
    extern /* Subroutine */ int dlaln2_(logical *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, integer *, doublereal *,
	     doublereal *, doublereal *, integer *, doublereal *, doublereal *
	    , doublereal *, integer *, doublereal *, doublereal *, integer *),
	     dlasy2_(logical *, logical *, integer *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, integer *, doublereal *, 
	    integer *, doublereal *, doublereal *, integer *, doublereal *, 
	    integer *);
    doublereal a11, db;
    extern /* Subroutine */ int dlabad_(doublereal *, doublereal *);
    extern doublereal dlamch_(char *), dlange_(char *, integer *, 
	    integer *, doublereal *, integer *, doublereal *);
    doublereal scaloc;
    extern /* Subroutine */ int xerbla_(char *, integer *, ftnlen);
    doublereal bignum;
    logical notrna, notrnb;
    doublereal smlnum, da11, vec[4]	/* was [2][2] */, dum[1], eps, sgn;


/*  -- LAPACK computational routine (version 3.7.0) -- */
/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
/*     December 2016 */


/*  ===================================================================== */


/*     Decode and Test input parameters */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1 * 1;
    b -= b_offset;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1 * 1;
    c__ -= c_offset;

    /* Function Body */
    notrna = lsame_(trana, "N");
    notrnb = lsame_(tranb, "N");

    *info = 0;
    if (! notrna && ! lsame_(trana, "T") && ! lsame_(
	    trana, "C")) {
	*info = -1;
    } else if (! notrnb && ! lsame_(tranb, "T") && ! 
	    lsame_(tranb, "C")) {
	*info = -2;
    } else if (*isgn != 1 && *isgn != -1) {
	*info = -3;
    } else if (*m < 0) {
	*info = -4;
    } else if (*n < 0) {
	*info = -5;
    } else if (*lda < f2cmax(1,*m)) {
	*info = -7;
    } else if (*ldb < f2cmax(1,*n)) {
	*info = -9;
    } else if (*ldc < f2cmax(1,*m)) {
	*info = -11;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DTRSYL", &i__1, (ftnlen)6);
	return 0;
    }

/*     Quick return if possible */

    *scale = 1.;
    if (*m == 0 || *n == 0) {
	return 0;
    }

/*     Set constants to control overflow */

    eps = dlamch_("P");
    smlnum = dlamch_("S");
    bignum = 1. / smlnum;
    dlabad_(&smlnum, &bignum);
    smlnum = smlnum * (doublereal) (*m * *n) / eps;
    bignum = 1. / smlnum;

/* Computing MAX */
    d__1 = smlnum, d__2 = eps * dlange_("M", m, m, &a[a_offset], lda, dum), d__1 = f2cmax(d__1,d__2), d__2 = eps * dlange_("M", n, n, 
	    &b[b_offset], ldb, dum);
    smin = f2cmax(d__1,d__2);

    sgn = (doublereal) (*isgn);

    if (notrna && notrnb) {

/*        Solve    A*X + ISGN*X*B = scale*C. */

/*        The (K,L)th block of X is determined starting from */
/*        bottom-left corner column by column by */

/*         A(K,K)*X(K,L) + ISGN*X(K,L)*B(L,L) = C(K,L) - R(K,L) */

/*        Where */
/*                  M                         L-1 */
/*        R(K,L) = SUM [A(K,I)*X(I,L)] + ISGN*SUM [X(K,J)*B(J,L)]. */
/*                I=K+1                       J=1 */

/*        Start column loop (index = L) */
/*        L1 (L2) : column index of the first (first) row of X(K,L). */

	lnext = 1;
	i__1 = *n;
	for (l = 1; l <= i__1; ++l) {
	    if (l < lnext) {
		goto L60;
	    }
	    if (l == *n) {
		l1 = l;
		l2 = l;
	    } else {
		if (b[l + 1 + l * b_dim1] != 0.) {
		    l1 = l;
		    l2 = l + 1;
		    lnext = l + 2;
		} else {
		    l1 = l;
		    l2 = l;
		    lnext = l + 1;
		}
	    }

/*           Start row loop (index = K) */
/*           K1 (K2): row index of the first (last) row of X(K,L). */

	    knext = *m;
	    for (k = *m; k >= 1; --k) {
		if (k > knext) {
		    goto L50;
		}
		if (k == 1) {
		    k1 = k;
		    k2 = k;
		} else {
		    if (a[k + (k - 1) * a_dim1] != 0.) {
			k1 = k - 1;
			k2 = k;
			knext = k - 2;
		    } else {
			k1 = k;
			k2 = k;
			knext = k - 1;
		    }
		}

		if (l1 == l2 && k1 == k2) {
		    i__2 = *m - k1;
/* Computing MIN */
		    i__3 = k1 + 1;
/* Computing MIN */
		    i__4 = k1 + 1;
		    suml = ddot_(&i__2, &a[k1 + f2cmin(i__3,*m) * a_dim1], lda, &
			    c__[f2cmin(i__4,*m) + l1 * c_dim1], &c__1);
		    i__2 = l1 - 1;
		    sumr = ddot_(&i__2, &c__[k1 + c_dim1], ldc, &b[l1 * 
			    b_dim1 + 1], &c__1);
		    vec[0] = c__[k1 + l1 * c_dim1] - (suml + sgn * sumr);
		    scaloc = 1.;

		    a11 = a[k1 + k1 * a_dim1] + sgn * b[l1 + l1 * b_dim1];
		    da11 = abs(a11);
		    if (da11 <= smin) {
			a11 = smin;
			da11 = smin;
			*info = 1;
		    }
		    db = abs(vec[0]);
		    if (da11 < 1. && db > 1.) {
			if (db > bignum * da11) {
			    scaloc = 1. / db;
			}
		    }
		    x[0] = vec[0] * scaloc / a11;

		    if (scaloc != 1.) {
			i__2 = *n;
			for (j = 1; j <= i__2; ++j) {
			    dscal_(m, &scaloc, &c__[j * c_dim1 + 1], &c__1);
/* L10: */
			}
			*scale *= scaloc;
		    }
		    c__[k1 + l1 * c_dim1] = x[0];

		} else if (l1 == l2 && k1 != k2) {

		    i__2 = *m - k2;
/* Computing MIN */
		    i__3 = k2 + 1;
/* Computing MIN */
		    i__4 = k2 + 1;
		    suml = ddot_(&i__2, &a[k1 + f2cmin(i__3,*m) * a_dim1], lda, &
			    c__[f2cmin(i__4,*m) + l1 * c_dim1], &c__1);
		    i__2 = l1 - 1;
		    sumr = ddot_(&i__2, &c__[k1 + c_dim1], ldc, &b[l1 * 
			    b_dim1 + 1], &c__1);
		    vec[0] = c__[k1 + l1 * c_dim1] - (suml + sgn * sumr);

		    i__2 = *m - k2;
/* Computing MIN */
		    i__3 = k2 + 1;
/* Computing MIN */
		    i__4 = k2 + 1;
		    suml = ddot_(&i__2, &a[k2 + f2cmin(i__3,*m) * a_dim1], lda, &
			    c__[f2cmin(i__4,*m) + l1 * c_dim1], &c__1);
		    i__2 = l1 - 1;
		    sumr = ddot_(&i__2, &c__[k2 + c_dim1], ldc, &b[l1 * 
			    b_dim1 + 1], &c__1);
		    vec[1] = c__[k2 + l1 * c_dim1] - (suml + sgn * sumr);

		    d__1 = -sgn * b[l1 + l1 * b_dim1];
		    dlaln2_(&c_false, &c__2, &c__1, &smin, &c_b26, &a[k1 + k1 
			    * a_dim1], lda, &c_b26, &c_b26, vec, &c__2, &d__1,
			     &c_b30, x, &c__2, &scaloc, &xnorm, &ierr);
		    if (ierr != 0) {
			*info = 1;
		    }

		    if (scaloc != 1.) {
			i__2 = *n;
			for (j = 1; j <= i__2; ++j) {
			    dscal_(m, &scaloc, &c__[j * c_dim1 + 1], &c__1);
/* L20: */
			}
			*scale *= scaloc;
		    }
		    c__[k1 + l1 * c_dim1] = x[0];
		    c__[k2 + l1 * c_dim1] = x[1];

		} else if (l1 != l2 && k1 == k2) {

		    i__2 = *m - k1;
/* Computing MIN */
		    i__3 = k1 + 1;
/* Computing MIN */
		    i__4 = k1 + 1;
		    suml = ddot_(&i__2, &a[k1 + f2cmin(i__3,*m) * a_dim1], lda, &
			    c__[f2cmin(i__4,*m) + l1 * c_dim1], &c__1);
		    i__2 = l1 - 1;
		    sumr = ddot_(&i__2, &c__[k1 + c_dim1], ldc, &b[l1 * 
			    b_dim1 + 1], &c__1);
		    vec[0] = sgn * (c__[k1 + l1 * c_dim1] - (suml + sgn * 
			    sumr));

		    i__2 = *m - k1;
/* Computing MIN */
		    i__3 = k1 + 1;
/* Computing MIN */
		    i__4 = k1 + 1;
		    suml = ddot_(&i__2, &a[k1 + f2cmin(i__3,*m) * a_dim1], lda, &
			    c__[f2cmin(i__4,*m) + l2 * c_dim1], &c__1);
		    i__2 = l1 - 1;
		    sumr = ddot_(&i__2, &c__[k1 + c_dim1], ldc, &b[l2 * 
			    b_dim1 + 1], &c__1);
		    vec[1] = sgn * (c__[k1 + l2 * c_dim1] - (suml + sgn * 
			    sumr));

		    d__1 = -sgn * a[k1 + k1 * a_dim1];
		    dlaln2_(&c_true, &c__2, &c__1, &smin, &c_b26, &b[l1 + l1 *
			     b_dim1], ldb, &c_b26, &c_b26, vec, &c__2, &d__1, 
			    &c_b30, x, &c__2, &scaloc, &xnorm, &ierr);
		    if (ierr != 0) {
			*info = 1;
		    }

		    if (scaloc != 1.) {
			i__2 = *n;
			for (j = 1; j <= i__2; ++j) {
			    dscal_(m, &scaloc, &c__[j * c_dim1 + 1], &c__1);
/* L30: */
			}
			*scale *= scaloc;
		    }
		    c__[k1 + l1 * c_dim1] = x[0];
		    c__[k1 + l2 * c_dim1] = x[1];

		} else if (l1 != l2 && k1 != k2) {

		    i__2 = *m - k2;
/* Computing MIN */
		    i__3 = k2 + 1;
/* Computing MIN */
		    i__4 = k2 + 1;
		    suml = ddot_(&i__2, &a[k1 + f2cmin(i__3,*m) * a_dim1], lda, &
			    c__[f2cmin(i__4,*m) + l1 * c_dim1], &c__1);
		    i__2 = l1 - 1;
		    sumr = ddot_(&i__2, &c__[k1 + c_dim1], ldc, &b[l1 * 
			    b_dim1 + 1], &c__1);
		    vec[0] = c__[k1 + l1 * c_dim1] - (suml + sgn * sumr);

		    i__2 = *m - k2;
/* Computing MIN */
		    i__3 = k2 + 1;
/* Computing MIN */
		    i__4 = k2 + 1;
		    suml = ddot_(&i__2, &a[k1 + f2cmin(i__3,*m) * a_dim1], lda, &
			    c__[f2cmin(i__4,*m) + l2 * c_dim1], &c__1);
		    i__2 = l1 - 1;
		    sumr = ddot_(&i__2, &c__[k1 + c_dim1], ldc, &b[l2 * 
			    b_dim1 + 1], &c__1);
		    vec[2] = c__[k1 + l2 * c_dim1] - (suml + sgn * sumr);

		    i__2 = *m - k2;
/* Computing MIN */
		    i__3 = k2 + 1;
/* Computing MIN */
		    i__4 = k2 + 1;
		    suml = ddot_(&i__2, &a[k2 + f2cmin(i__3,*m) * a_dim1], lda, &
			    c__[f2cmin(i__4,*m) + l1 * c_dim1], &c__1);
		    i__2 = l1 - 1;
		    sumr = ddot_(&i__2, &c__[k2 + c_dim1], ldc, &b[l1 * 
			    b_dim1 + 1], &c__1);
		    vec[1] = c__[k2 + l1 * c_dim1] - (suml + sgn * sumr);

		    i__2 = *m - k2;
/* Computing MIN */
		    i__3 = k2 + 1;
/* Computing MIN */
		    i__4 = k2 + 1;
		    suml = ddot_(&i__2, &a[k2 + f2cmin(i__3,*m) * a_dim1], lda, &
			    c__[f2cmin(i__4,*m) + l2 * c_dim1], &c__1);
		    i__2 = l1 - 1;
		    sumr = ddot_(&i__2, &c__[k2 + c_dim1], ldc, &b[l2 * 
			    b_dim1 + 1], &c__1);
		    vec[3] = c__[k2 + l2 * c_dim1] - (suml + sgn * sumr);

		    dlasy2_(&c_false, &c_false, isgn, &c__2, &c__2, &a[k1 + 
			    k1 * a_dim1], lda, &b[l1 + l1 * b_dim1], ldb, vec,
			     &c__2, &scaloc, x, &c__2, &xnorm, &ierr);
		    if (ierr != 0) {
			*info = 1;
		    }

		    if (scaloc != 1.) {
			i__2 = *n;
			for (j = 1; j <= i__2; ++j) {
			    dscal_(m, &scaloc, &c__[j * c_dim1 + 1], &c__1);
/* L40: */
			}
			*scale *= scaloc;
		    }
		    c__[k1 + l1 * c_dim1] = x[0];
		    c__[k1 + l2 * c_dim1] = x[2];
		    c__[k2 + l1 * c_dim1] = x[1];
		    c__[k2 + l2 * c_dim1] = x[3];
		}

L50:
		;
	    }

L60:
	    ;
	}

    } else if (! notrna && notrnb) {

/*        Solve    A**T *X + ISGN*X*B = scale*C. */

/*        The (K,L)th block of X is determined starting from */
/*        upper-left corner column by column by */

/*          A(K,K)**T*X(K,L) + ISGN*X(K,L)*B(L,L) = C(K,L) - R(K,L) */

/*        Where */
/*                   K-1        T                    L-1 */
/*          R(K,L) = SUM [A(I,K)**T*X(I,L)] +ISGN*SUM [X(K,J)*B(J,L)] */
/*                   I=1                          J=1 */

/*        Start column loop (index = L) */
/*        L1 (L2): column index of the first (last) row of X(K,L) */

	lnext = 1;
	i__1 = *n;
	for (l = 1; l <= i__1; ++l) {
	    if (l < lnext) {
		goto L120;
	    }
	    if (l == *n) {
		l1 = l;
		l2 = l;
	    } else {
		if (b[l + 1 + l * b_dim1] != 0.) {
		    l1 = l;
		    l2 = l + 1;
		    lnext = l + 2;
		} else {
		    l1 = l;
		    l2 = l;
		    lnext = l + 1;
		}
	    }

/*           Start row loop (index = K) */
/*           K1 (K2): row index of the first (last) row of X(K,L) */

	    knext = 1;
	    i__2 = *m;
	    for (k = 1; k <= i__2; ++k) {
		if (k < knext) {
		    goto L110;
		}
		if (k == *m) {
		    k1 = k;
		    k2 = k;
		} else {
		    if (a[k + 1 + k * a_dim1] != 0.) {
			k1 = k;
			k2 = k + 1;
			knext = k + 2;
		    } else {
			k1 = k;
			k2 = k;
			knext = k + 1;
		    }
		}

		if (l1 == l2 && k1 == k2) {
		    i__3 = k1 - 1;
		    suml = ddot_(&i__3, &a[k1 * a_dim1 + 1], &c__1, &c__[l1 * 
			    c_dim1 + 1], &c__1);
		    i__3 = l1 - 1;
		    sumr = ddot_(&i__3, &c__[k1 + c_dim1], ldc, &b[l1 * 
			    b_dim1 + 1], &c__1);
		    vec[0] = c__[k1 + l1 * c_dim1] - (suml + sgn * sumr);
		    scaloc = 1.;

		    a11 = a[k1 + k1 * a_dim1] + sgn * b[l1 + l1 * b_dim1];
		    da11 = abs(a11);
		    if (da11 <= smin) {
			a11 = smin;
			da11 = smin;
			*info = 1;
		    }
		    db = abs(vec[0]);
		    if (da11 < 1. && db > 1.) {
			if (db > bignum * da11) {
			    scaloc = 1. / db;
			}
		    }
		    x[0] = vec[0] * scaloc / a11;

		    if (scaloc != 1.) {
			i__3 = *n;
			for (j = 1; j <= i__3; ++j) {
			    dscal_(m, &scaloc, &c__[j * c_dim1 + 1], &c__1);
/* L70: */
			}
			*scale *= scaloc;
		    }
		    c__[k1 + l1 * c_dim1] = x[0];

		} else if (l1 == l2 && k1 != k2) {

		    i__3 = k1 - 1;
		    suml = ddot_(&i__3, &a[k1 * a_dim1 + 1], &c__1, &c__[l1 * 
			    c_dim1 + 1], &c__1);
		    i__3 = l1 - 1;
		    sumr = ddot_(&i__3, &c__[k1 + c_dim1], ldc, &b[l1 * 
			    b_dim1 + 1], &c__1);
		    vec[0] = c__[k1 + l1 * c_dim1] - (suml + sgn * sumr);

		    i__3 = k1 - 1;
		    suml = ddot_(&i__3, &a[k2 * a_dim1 + 1], &c__1, &c__[l1 * 
			    c_dim1 + 1], &c__1);
		    i__3 = l1 - 1;
		    sumr = ddot_(&i__3, &c__[k2 + c_dim1], ldc, &b[l1 * 
			    b_dim1 + 1], &c__1);
		    vec[1] = c__[k2 + l1 * c_dim1] - (suml + sgn * sumr);

		    d__1 = -sgn * b[l1 + l1 * b_dim1];
		    dlaln2_(&c_true, &c__2, &c__1, &smin, &c_b26, &a[k1 + k1 *
			     a_dim1], lda, &c_b26, &c_b26, vec, &c__2, &d__1, 
			    &c_b30, x, &c__2, &scaloc, &xnorm, &ierr);
		    if (ierr != 0) {
			*info = 1;
		    }

		    if (scaloc != 1.) {
			i__3 = *n;
			for (j = 1; j <= i__3; ++j) {
			    dscal_(m, &scaloc, &c__[j * c_dim1 + 1], &c__1);
/* L80: */
			}
			*scale *= scaloc;
		    }
		    c__[k1 + l1 * c_dim1] = x[0];
		    c__[k2 + l1 * c_dim1] = x[1];

		} else if (l1 != l2 && k1 == k2) {

		    i__3 = k1 - 1;
		    suml = ddot_(&i__3, &a[k1 * a_dim1 + 1], &c__1, &c__[l1 * 
			    c_dim1 + 1], &c__1);
		    i__3 = l1 - 1;
		    sumr = ddot_(&i__3, &c__[k1 + c_dim1], ldc, &b[l1 * 
			    b_dim1 + 1], &c__1);
		    vec[0] = sgn * (c__[k1 + l1 * c_dim1] - (suml + sgn * 
			    sumr));

		    i__3 = k1 - 1;
		    suml = ddot_(&i__3, &a[k1 * a_dim1 + 1], &c__1, &c__[l2 * 
			    c_dim1 + 1], &c__1);
		    i__3 = l1 - 1;
		    sumr = ddot_(&i__3, &c__[k1 + c_dim1], ldc, &b[l2 * 
			    b_dim1 + 1], &c__1);
		    vec[1] = sgn * (c__[k1 + l2 * c_dim1] - (suml + sgn * 
			    sumr));

		    d__1 = -sgn * a[k1 + k1 * a_dim1];
		    dlaln2_(&c_true, &c__2, &c__1, &smin, &c_b26, &b[l1 + l1 *
			     b_dim1], ldb, &c_b26, &c_b26, vec, &c__2, &d__1, 
			    &c_b30, x, &c__2, &scaloc, &xnorm, &ierr);
		    if (ierr != 0) {
			*info = 1;
		    }

		    if (scaloc != 1.) {
			i__3 = *n;
			for (j = 1; j <= i__3; ++j) {
			    dscal_(m, &scaloc, &c__[j * c_dim1 + 1], &c__1);
/* L90: */
			}
			*scale *= scaloc;
		    }
		    c__[k1 + l1 * c_dim1] = x[0];
		    c__[k1 + l2 * c_dim1] = x[1];

		} else if (l1 != l2 && k1 != k2) {

		    i__3 = k1 - 1;
		    suml = ddot_(&i__3, &a[k1 * a_dim1 + 1], &c__1, &c__[l1 * 
			    c_dim1 + 1], &c__1);
		    i__3 = l1 - 1;
		    sumr = ddot_(&i__3, &c__[k1 + c_dim1], ldc, &b[l1 * 
			    b_dim1 + 1], &c__1);
		    vec[0] = c__[k1 + l1 * c_dim1] - (suml + sgn * sumr);

		    i__3 = k1 - 1;
		    suml = ddot_(&i__3, &a[k1 * a_dim1 + 1], &c__1, &c__[l2 * 
			    c_dim1 + 1], &c__1);
		    i__3 = l1 - 1;
		    sumr = ddot_(&i__3, &c__[k1 + c_dim1], ldc, &b[l2 * 
			    b_dim1 + 1], &c__1);
		    vec[2] = c__[k1 + l2 * c_dim1] - (suml + sgn * sumr);

		    i__3 = k1 - 1;
		    suml = ddot_(&i__3, &a[k2 * a_dim1 + 1], &c__1, &c__[l1 * 
			    c_dim1 + 1], &c__1);
		    i__3 = l1 - 1;
		    sumr = ddot_(&i__3, &c__[k2 + c_dim1], ldc, &b[l1 * 
			    b_dim1 + 1], &c__1);
		    vec[1] = c__[k2 + l1 * c_dim1] - (suml + sgn * sumr);

		    i__3 = k1 - 1;
		    suml = ddot_(&i__3, &a[k2 * a_dim1 + 1], &c__1, &c__[l2 * 
			    c_dim1 + 1], &c__1);
		    i__3 = l1 - 1;
		    sumr = ddot_(&i__3, &c__[k2 + c_dim1], ldc, &b[l2 * 
			    b_dim1 + 1], &c__1);
		    vec[3] = c__[k2 + l2 * c_dim1] - (suml + sgn * sumr);

		    dlasy2_(&c_true, &c_false, isgn, &c__2, &c__2, &a[k1 + k1 
			    * a_dim1], lda, &b[l1 + l1 * b_dim1], ldb, vec, &
			    c__2, &scaloc, x, &c__2, &xnorm, &ierr);
		    if (ierr != 0) {
			*info = 1;
		    }

		    if (scaloc != 1.) {
			i__3 = *n;
			for (j = 1; j <= i__3; ++j) {
			    dscal_(m, &scaloc, &c__[j * c_dim1 + 1], &c__1);
/* L100: */
			}
			*scale *= scaloc;
		    }
		    c__[k1 + l1 * c_dim1] = x[0];
		    c__[k1 + l2 * c_dim1] = x[2];
		    c__[k2 + l1 * c_dim1] = x[1];
		    c__[k2 + l2 * c_dim1] = x[3];
		}

L110:
		;
	    }
L120:
	    ;
	}

    } else if (! notrna && ! notrnb) {

/*        Solve    A**T*X + ISGN*X*B**T = scale*C. */

/*        The (K,L)th block of X is determined starting from */
/*        top-right corner column by column by */

/*           A(K,K)**T*X(K,L) + ISGN*X(K,L)*B(L,L)**T = C(K,L) - R(K,L) */

/*        Where */
/*                     K-1                            N */
/*            R(K,L) = SUM [A(I,K)**T*X(I,L)] + ISGN*SUM [X(K,J)*B(L,J)**T]. */
/*                     I=1                          J=L+1 */

/*        Start column loop (index = L) */
/*        L1 (L2): column index of the first (last) row of X(K,L) */

	lnext = *n;
	for (l = *n; l >= 1; --l) {
	    if (l > lnext) {
		goto L180;
	    }
	    if (l == 1) {
		l1 = l;
		l2 = l;
	    } else {
		if (b[l + (l - 1) * b_dim1] != 0.) {
		    l1 = l - 1;
		    l2 = l;
		    lnext = l - 2;
		} else {
		    l1 = l;
		    l2 = l;
		    lnext = l - 1;
		}
	    }

/*           Start row loop (index = K) */
/*           K1 (K2): row index of the first (last) row of X(K,L) */

	    knext = 1;
	    i__1 = *m;
	    for (k = 1; k <= i__1; ++k) {
		if (k < knext) {
		    goto L170;
		}
		if (k == *m) {
		    k1 = k;
		    k2 = k;
		} else {
		    if (a[k + 1 + k * a_dim1] != 0.) {
			k1 = k;
			k2 = k + 1;
			knext = k + 2;
		    } else {
			k1 = k;
			k2 = k;
			knext = k + 1;
		    }
		}

		if (l1 == l2 && k1 == k2) {
		    i__2 = k1 - 1;
		    suml = ddot_(&i__2, &a[k1 * a_dim1 + 1], &c__1, &c__[l1 * 
			    c_dim1 + 1], &c__1);
		    i__2 = *n - l1;
/* Computing MIN */
		    i__3 = l1 + 1;
/* Computing MIN */
		    i__4 = l1 + 1;
		    sumr = ddot_(&i__2, &c__[k1 + f2cmin(i__3,*n) * c_dim1], ldc,
			     &b[l1 + f2cmin(i__4,*n) * b_dim1], ldb);
		    vec[0] = c__[k1 + l1 * c_dim1] - (suml + sgn * sumr);
		    scaloc = 1.;

		    a11 = a[k1 + k1 * a_dim1] + sgn * b[l1 + l1 * b_dim1];
		    da11 = abs(a11);
		    if (da11 <= smin) {
			a11 = smin;
			da11 = smin;
			*info = 1;
		    }
		    db = abs(vec[0]);
		    if (da11 < 1. && db > 1.) {
			if (db > bignum * da11) {
			    scaloc = 1. / db;
			}
		    }
		    x[0] = vec[0] * scaloc / a11;

		    if (scaloc != 1.) {
			i__2 = *n;
			for (j = 1; j <= i__2; ++j) {
			    dscal_(m, &scaloc, &c__[j * c_dim1 + 1], &c__1);
/* L130: */
			}
			*scale *= scaloc;
		    }
		    c__[k1 + l1 * c_dim1] = x[0];

		} else if (l1 == l2 && k1 != k2) {

		    i__2 = k1 - 1;
		    suml = ddot_(&i__2, &a[k1 * a_dim1 + 1], &c__1, &c__[l1 * 
			    c_dim1 + 1], &c__1);
		    i__2 = *n - l2;
/* Computing MIN */
		    i__3 = l2 + 1;
/* Computing MIN */
		    i__4 = l2 + 1;
		    sumr = ddot_(&i__2, &c__[k1 + f2cmin(i__3,*n) * c_dim1], ldc,
			     &b[l1 + f2cmin(i__4,*n) * b_dim1], ldb);
		    vec[0] = c__[k1 + l1 * c_dim1] - (suml + sgn * sumr);

		    i__2 = k1 - 1;
		    suml = ddot_(&i__2, &a[k2 * a_dim1 + 1], &c__1, &c__[l1 * 
			    c_dim1 + 1], &c__1);
		    i__2 = *n - l2;
/* Computing MIN */
		    i__3 = l2 + 1;
/* Computing MIN */
		    i__4 = l2 + 1;
		    sumr = ddot_(&i__2, &c__[k2 + f2cmin(i__3,*n) * c_dim1], ldc,
			     &b[l1 + f2cmin(i__4,*n) * b_dim1], ldb);
		    vec[1] = c__[k2 + l1 * c_dim1] - (suml + sgn * sumr);

		    d__1 = -sgn * b[l1 + l1 * b_dim1];
		    dlaln2_(&c_true, &c__2, &c__1, &smin, &c_b26, &a[k1 + k1 *
			     a_dim1], lda, &c_b26, &c_b26, vec, &c__2, &d__1, 
			    &c_b30, x, &c__2, &scaloc, &xnorm, &ierr);
		    if (ierr != 0) {
			*info = 1;
		    }

		    if (scaloc != 1.) {
			i__2 = *n;
			for (j = 1; j <= i__2; ++j) {
			    dscal_(m, &scaloc, &c__[j * c_dim1 + 1], &c__1);
/* L140: */
			}
			*scale *= scaloc;
		    }
		    c__[k1 + l1 * c_dim1] = x[0];
		    c__[k2 + l1 * c_dim1] = x[1];

		} else if (l1 != l2 && k1 == k2) {

		    i__2 = k1 - 1;
		    suml = ddot_(&i__2, &a[k1 * a_dim1 + 1], &c__1, &c__[l1 * 
			    c_dim1 + 1], &c__1);
		    i__2 = *n - l2;
/* Computing MIN */
		    i__3 = l2 + 1;
/* Computing MIN */
		    i__4 = l2 + 1;
		    sumr = ddot_(&i__2, &c__[k1 + f2cmin(i__3,*n) * c_dim1], ldc,
			     &b[l1 + f2cmin(i__4,*n) * b_dim1], ldb);
		    vec[0] = sgn * (c__[k1 + l1 * c_dim1] - (suml + sgn * 
			    sumr));

		    i__2 = k1 - 1;
		    suml = ddot_(&i__2, &a[k1 * a_dim1 + 1], &c__1, &c__[l2 * 
			    c_dim1 + 1], &c__1);
		    i__2 = *n - l2;
/* Computing MIN */
		    i__3 = l2 + 1;
/* Computing MIN */
		    i__4 = l2 + 1;
		    sumr = ddot_(&i__2, &c__[k1 + f2cmin(i__3,*n) * c_dim1], ldc,
			     &b[l2 + f2cmin(i__4,*n) * b_dim1], ldb);
		    vec[1] = sgn * (c__[k1 + l2 * c_dim1] - (suml + sgn * 
			    sumr));

		    d__1 = -sgn * a[k1 + k1 * a_dim1];
		    dlaln2_(&c_false, &c__2, &c__1, &smin, &c_b26, &b[l1 + l1 
			    * b_dim1], ldb, &c_b26, &c_b26, vec, &c__2, &d__1,
			     &c_b30, x, &c__2, &scaloc, &xnorm, &ierr);
		    if (ierr != 0) {
			*info = 1;
		    }

		    if (scaloc != 1.) {
			i__2 = *n;
			for (j = 1; j <= i__2; ++j) {
			    dscal_(m, &scaloc, &c__[j * c_dim1 + 1], &c__1);
/* L150: */
			}
			*scale *= scaloc;
		    }
		    c__[k1 + l1 * c_dim1] = x[0];
		    c__[k1 + l2 * c_dim1] = x[1];

		} else if (l1 != l2 && k1 != k2) {

		    i__2 = k1 - 1;
		    suml = ddot_(&i__2, &a[k1 * a_dim1 + 1], &c__1, &c__[l1 * 
			    c_dim1 + 1], &c__1);
		    i__2 = *n - l2;
/* Computing MIN */
		    i__3 = l2 + 1;
/* Computing MIN */
		    i__4 = l2 + 1;
		    sumr = ddot_(&i__2, &c__[k1 + f2cmin(i__3,*n) * c_dim1], ldc,
			     &b[l1 + f2cmin(i__4,*n) * b_dim1], ldb);
		    vec[0] = c__[k1 + l1 * c_dim1] - (suml + sgn * sumr);

		    i__2 = k1 - 1;
		    suml = ddot_(&i__2, &a[k1 * a_dim1 + 1], &c__1, &c__[l2 * 
			    c_dim1 + 1], &c__1);
		    i__2 = *n - l2;
/* Computing MIN */
		    i__3 = l2 + 1;
/* Computing MIN */
		    i__4 = l2 + 1;
		    sumr = ddot_(&i__2, &c__[k1 + f2cmin(i__3,*n) * c_dim1], ldc,
			     &b[l2 + f2cmin(i__4,*n) * b_dim1], ldb);
		    vec[2] = c__[k1 + l2 * c_dim1] - (suml + sgn * sumr);

		    i__2 = k1 - 1;
		    suml = ddot_(&i__2, &a[k2 * a_dim1 + 1], &c__1, &c__[l1 * 
			    c_dim1 + 1], &c__1);
		    i__2 = *n - l2;
/* Computing MIN */
		    i__3 = l2 + 1;
/* Computing MIN */
		    i__4 = l2 + 1;
		    sumr = ddot_(&i__2, &c__[k2 + f2cmin(i__3,*n) * c_dim1], ldc,
			     &b[l1 + f2cmin(i__4,*n) * b_dim1], ldb);
		    vec[1] = c__[k2 + l1 * c_dim1] - (suml + sgn * sumr);

		    i__2 = k1 - 1;
		    suml = ddot_(&i__2, &a[k2 * a_dim1 + 1], &c__1, &c__[l2 * 
			    c_dim1 + 1], &c__1);
		    i__2 = *n - l2;
/* Computing MIN */
		    i__3 = l2 + 1;
/* Computing MIN */
		    i__4 = l2 + 1;
		    sumr = ddot_(&i__2, &c__[k2 + f2cmin(i__3,*n) * c_dim1], ldc,
			     &b[l2 + f2cmin(i__4,*n) * b_dim1], ldb);
		    vec[3] = c__[k2 + l2 * c_dim1] - (suml + sgn * sumr);

		    dlasy2_(&c_true, &c_true, isgn, &c__2, &c__2, &a[k1 + k1 *
			     a_dim1], lda, &b[l1 + l1 * b_dim1], ldb, vec, &
			    c__2, &scaloc, x, &c__2, &xnorm, &ierr);
		    if (ierr != 0) {
			*info = 1;
		    }

		    if (scaloc != 1.) {
			i__2 = *n;
			for (j = 1; j <= i__2; ++j) {
			    dscal_(m, &scaloc, &c__[j * c_dim1 + 1], &c__1);
/* L160: */
			}
			*scale *= scaloc;
		    }
		    c__[k1 + l1 * c_dim1] = x[0];
		    c__[k1 + l2 * c_dim1] = x[2];
		    c__[k2 + l1 * c_dim1] = x[1];
		    c__[k2 + l2 * c_dim1] = x[3];
		}

L170:
		;
	    }
L180:
	    ;
	}

    } else if (notrna && ! notrnb) {

/*        Solve    A*X + ISGN*X*B**T = scale*C. */

/*        The (K,L)th block of X is determined starting from */
/*        bottom-right corner column by column by */

/*            A(K,K)*X(K,L) + ISGN*X(K,L)*B(L,L)**T = C(K,L) - R(K,L) */

/*        Where */
/*                      M                          N */
/*            R(K,L) = SUM [A(K,I)*X(I,L)] + ISGN*SUM [X(K,J)*B(L,J)**T]. */
/*                    I=K+1                      J=L+1 */

/*        Start column loop (index = L) */
/*        L1 (L2): column index of the first (last) row of X(K,L) */

	lnext = *n;
	for (l = *n; l >= 1; --l) {
	    if (l > lnext) {
		goto L240;
	    }
	    if (l == 1) {
		l1 = l;
		l2 = l;
	    } else {
		if (b[l + (l - 1) * b_dim1] != 0.) {
		    l1 = l - 1;
		    l2 = l;
		    lnext = l - 2;
		} else {
		    l1 = l;
		    l2 = l;
		    lnext = l - 1;
		}
	    }

/*           Start row loop (index = K) */
/*           K1 (K2): row index of the first (last) row of X(K,L) */

	    knext = *m;
	    for (k = *m; k >= 1; --k) {
		if (k > knext) {
		    goto L230;
		}
		if (k == 1) {
		    k1 = k;
		    k2 = k;
		} else {
		    if (a[k + (k - 1) * a_dim1] != 0.) {
			k1 = k - 1;
			k2 = k;
			knext = k - 2;
		    } else {
			k1 = k;
			k2 = k;
			knext = k - 1;
		    }
		}

		if (l1 == l2 && k1 == k2) {
		    i__1 = *m - k1;
/* Computing MIN */
		    i__2 = k1 + 1;
/* Computing MIN */
		    i__3 = k1 + 1;
		    suml = ddot_(&i__1, &a[k1 + f2cmin(i__2,*m) * a_dim1], lda, &
			    c__[f2cmin(i__3,*m) + l1 * c_dim1], &c__1);
		    i__1 = *n - l1;
/* Computing MIN */
		    i__2 = l1 + 1;
/* Computing MIN */
		    i__3 = l1 + 1;
		    sumr = ddot_(&i__1, &c__[k1 + f2cmin(i__2,*n) * c_dim1], ldc,
			     &b[l1 + f2cmin(i__3,*n) * b_dim1], ldb);
		    vec[0] = c__[k1 + l1 * c_dim1] - (suml + sgn * sumr);
		    scaloc = 1.;

		    a11 = a[k1 + k1 * a_dim1] + sgn * b[l1 + l1 * b_dim1];
		    da11 = abs(a11);
		    if (da11 <= smin) {
			a11 = smin;
			da11 = smin;
			*info = 1;
		    }
		    db = abs(vec[0]);
		    if (da11 < 1. && db > 1.) {
			if (db > bignum * da11) {
			    scaloc = 1. / db;
			}
		    }
		    x[0] = vec[0] * scaloc / a11;

		    if (scaloc != 1.) {
			i__1 = *n;
			for (j = 1; j <= i__1; ++j) {
			    dscal_(m, &scaloc, &c__[j * c_dim1 + 1], &c__1);
/* L190: */
			}
			*scale *= scaloc;
		    }
		    c__[k1 + l1 * c_dim1] = x[0];

		} else if (l1 == l2 && k1 != k2) {

		    i__1 = *m - k2;
/* Computing MIN */
		    i__2 = k2 + 1;
/* Computing MIN */
		    i__3 = k2 + 1;
		    suml = ddot_(&i__1, &a[k1 + f2cmin(i__2,*m) * a_dim1], lda, &
			    c__[f2cmin(i__3,*m) + l1 * c_dim1], &c__1);
		    i__1 = *n - l2;
/* Computing MIN */
		    i__2 = l2 + 1;
/* Computing MIN */
		    i__3 = l2 + 1;
		    sumr = ddot_(&i__1, &c__[k1 + f2cmin(i__2,*n) * c_dim1], ldc,
			     &b[l1 + f2cmin(i__3,*n) * b_dim1], ldb);
		    vec[0] = c__[k1 + l1 * c_dim1] - (suml + sgn * sumr);

		    i__1 = *m - k2;
/* Computing MIN */
		    i__2 = k2 + 1;
/* Computing MIN */
		    i__3 = k2 + 1;
		    suml = ddot_(&i__1, &a[k2 + f2cmin(i__2,*m) * a_dim1], lda, &
			    c__[f2cmin(i__3,*m) + l1 * c_dim1], &c__1);
		    i__1 = *n - l2;
/* Computing MIN */
		    i__2 = l2 + 1;
/* Computing MIN */
		    i__3 = l2 + 1;
		    sumr = ddot_(&i__1, &c__[k2 + f2cmin(i__2,*n) * c_dim1], ldc,
			     &b[l1 + f2cmin(i__3,*n) * b_dim1], ldb);
		    vec[1] = c__[k2 + l1 * c_dim1] - (suml + sgn * sumr);

		    d__1 = -sgn * b[l1 + l1 * b_dim1];
		    dlaln2_(&c_false, &c__2, &c__1, &smin, &c_b26, &a[k1 + k1 
			    * a_dim1], lda, &c_b26, &c_b26, vec, &c__2, &d__1,
			     &c_b30, x, &c__2, &scaloc, &xnorm, &ierr);
		    if (ierr != 0) {
			*info = 1;
		    }

		    if (scaloc != 1.) {
			i__1 = *n;
			for (j = 1; j <= i__1; ++j) {
			    dscal_(m, &scaloc, &c__[j * c_dim1 + 1], &c__1);
/* L200: */
			}
			*scale *= scaloc;
		    }
		    c__[k1 + l1 * c_dim1] = x[0];
		    c__[k2 + l1 * c_dim1] = x[1];

		} else if (l1 != l2 && k1 == k2) {

		    i__1 = *m - k1;
/* Computing MIN */
		    i__2 = k1 + 1;
/* Computing MIN */
		    i__3 = k1 + 1;
		    suml = ddot_(&i__1, &a[k1 + f2cmin(i__2,*m) * a_dim1], lda, &
			    c__[f2cmin(i__3,*m) + l1 * c_dim1], &c__1);
		    i__1 = *n - l2;
/* Computing MIN */
		    i__2 = l2 + 1;
/* Computing MIN */
		    i__3 = l2 + 1;
		    sumr = ddot_(&i__1, &c__[k1 + f2cmin(i__2,*n) * c_dim1], ldc,
			     &b[l1 + f2cmin(i__3,*n) * b_dim1], ldb);
		    vec[0] = sgn * (c__[k1 + l1 * c_dim1] - (suml + sgn * 
			    sumr));

		    i__1 = *m - k1;
/* Computing MIN */
		    i__2 = k1 + 1;
/* Computing MIN */
		    i__3 = k1 + 1;
		    suml = ddot_(&i__1, &a[k1 + f2cmin(i__2,*m) * a_dim1], lda, &
			    c__[f2cmin(i__3,*m) + l2 * c_dim1], &c__1);
		    i__1 = *n - l2;
/* Computing MIN */
		    i__2 = l2 + 1;
/* Computing MIN */
		    i__3 = l2 + 1;
		    sumr = ddot_(&i__1, &c__[k1 + f2cmin(i__2,*n) * c_dim1], ldc,
			     &b[l2 + f2cmin(i__3,*n) * b_dim1], ldb);
		    vec[1] = sgn * (c__[k1 + l2 * c_dim1] - (suml + sgn * 
			    sumr));

		    d__1 = -sgn * a[k1 + k1 * a_dim1];
		    dlaln2_(&c_false, &c__2, &c__1, &smin, &c_b26, &b[l1 + l1 
			    * b_dim1], ldb, &c_b26, &c_b26, vec, &c__2, &d__1,
			     &c_b30, x, &c__2, &scaloc, &xnorm, &ierr);
		    if (ierr != 0) {
			*info = 1;
		    }

		    if (scaloc != 1.) {
			i__1 = *n;
			for (j = 1; j <= i__1; ++j) {
			    dscal_(m, &scaloc, &c__[j * c_dim1 + 1], &c__1);
/* L210: */
			}
			*scale *= scaloc;
		    }
		    c__[k1 + l1 * c_dim1] = x[0];
		    c__[k1 + l2 * c_dim1] = x[1];

		} else if (l1 != l2 && k1 != k2) {

		    i__1 = *m - k2;
/* Computing MIN */
		    i__2 = k2 + 1;
/* Computing MIN */
		    i__3 = k2 + 1;
		    suml = ddot_(&i__1, &a[k1 + f2cmin(i__2,*m) * a_dim1], lda, &
			    c__[f2cmin(i__3,*m) + l1 * c_dim1], &c__1);
		    i__1 = *n - l2;
/* Computing MIN */
		    i__2 = l2 + 1;
/* Computing MIN */
		    i__3 = l2 + 1;
		    sumr = ddot_(&i__1, &c__[k1 + f2cmin(i__2,*n) * c_dim1], ldc,
			     &b[l1 + f2cmin(i__3,*n) * b_dim1], ldb);
		    vec[0] = c__[k1 + l1 * c_dim1] - (suml + sgn * sumr);

		    i__1 = *m - k2;
/* Computing MIN */
		    i__2 = k2 + 1;
/* Computing MIN */
		    i__3 = k2 + 1;
		    suml = ddot_(&i__1, &a[k1 + f2cmin(i__2,*m) * a_dim1], lda, &
			    c__[f2cmin(i__3,*m) + l2 * c_dim1], &c__1);
		    i__1 = *n - l2;
/* Computing MIN */
		    i__2 = l2 + 1;
/* Computing MIN */
		    i__3 = l2 + 1;
		    sumr = ddot_(&i__1, &c__[k1 + f2cmin(i__2,*n) * c_dim1], ldc,
			     &b[l2 + f2cmin(i__3,*n) * b_dim1], ldb);
		    vec[2] = c__[k1 + l2 * c_dim1] - (suml + sgn * sumr);

		    i__1 = *m - k2;
/* Computing MIN */
		    i__2 = k2 + 1;
/* Computing MIN */
		    i__3 = k2 + 1;
		    suml = ddot_(&i__1, &a[k2 + f2cmin(i__2,*m) * a_dim1], lda, &
			    c__[f2cmin(i__3,*m) + l1 * c_dim1], &c__1);
		    i__1 = *n - l2;
/* Computing MIN */
		    i__2 = l2 + 1;
/* Computing MIN */
		    i__3 = l2 + 1;
		    sumr = ddot_(&i__1, &c__[k2 + f2cmin(i__2,*n) * c_dim1], ldc,
			     &b[l1 + f2cmin(i__3,*n) * b_dim1], ldb);
		    vec[1] = c__[k2 + l1 * c_dim1] - (suml + sgn * sumr);

		    i__1 = *m - k2;
/* Computing MIN */
		    i__2 = k2 + 1;
/* Computing MIN */
		    i__3 = k2 + 1;
		    suml = ddot_(&i__1, &a[k2 + f2cmin(i__2,*m) * a_dim1], lda, &
			    c__[f2cmin(i__3,*m) + l2 * c_dim1], &c__1);
		    i__1 = *n - l2;
/* Computing MIN */
		    i__2 = l2 + 1;
/* Computing MIN */
		    i__3 = l2 + 1;
		    sumr = ddot_(&i__1, &c__[k2 + f2cmin(i__2,*n) * c_dim1], ldc,
			     &b[l2 + f2cmin(i__3,*n) * b_dim1], ldb);
		    vec[3] = c__[k2 + l2 * c_dim1] - (suml + sgn * sumr);

		    dlasy2_(&c_false, &c_true, isgn, &c__2, &c__2, &a[k1 + k1 
			    * a_dim1], lda, &b[l1 + l1 * b_dim1], ldb, vec, &
			    c__2, &scaloc, x, &c__2, &xnorm, &ierr);
		    if (ierr != 0) {
			*info = 1;
		    }

		    if (scaloc != 1.) {
			i__1 = *n;
			for (j = 1; j <= i__1; ++j) {
			    dscal_(m, &scaloc, &c__[j * c_dim1 + 1], &c__1);
/* L220: */
			}
			*scale *= scaloc;
		    }
		    c__[k1 + l1 * c_dim1] = x[0];
		    c__[k1 + l2 * c_dim1] = x[2];
		    c__[k2 + l1 * c_dim1] = x[1];
		    c__[k2 + l2 * c_dim1] = x[3];
		}

L230:
		;
	    }
L240:
	    ;
	}

    }

    return 0;

/*     End of DTRSYL */

} /* dtrsyl_ */

