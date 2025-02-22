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

static complex c_b1 = {0.f,0.f};
static integer c__1 = 1;
static integer c__5 = 5;
static logical c_true = TRUE_;
static logical c_false = FALSE_;

/* > \brief \b CLATMT */

/*  =========== DOCUMENTATION =========== */

/* Online html documentation available at */
/*            http://www.netlib.org/lapack/explore-html/ */

/*  Definition: */
/*  =========== */

/*       SUBROUTINE CLATMT( M, N, DIST, ISEED, SYM, D, MODE, COND, DMAX, */
/*                          RANK, KL, KU, PACK, A, LDA, WORK, INFO ) */

/*       REAL               COND, DMAX */
/*       INTEGER            INFO, KL, KU, LDA, M, MODE, N, RANK */
/*       CHARACTER          DIST, PACK, SYM */
/*       COMPLEX            A( LDA, * ), WORK( * ) */
/*       REAL               D( * ) */
/*       INTEGER            ISEED( 4 ) */


/* > \par Purpose: */
/*  ============= */
/* > */
/* > \verbatim */
/* > */
/* >    CLATMT generates random matrices with specified singular values */
/* >    (or hermitian with specified eigenvalues) */
/* >    for testing LAPACK programs. */
/* > */
/* >    CLATMT operates by applying the following sequence of */
/* >    operations: */
/* > */
/* >      Set the diagonal to D, where D may be input or */
/* >         computed according to MODE, COND, DMAX, and SYM */
/* >         as described below. */
/* > */
/* >      Generate a matrix with the appropriate band structure, by one */
/* >         of two methods: */
/* > */
/* >      Method A: */
/* >          Generate a dense M x N matrix by multiplying D on the left */
/* >              and the right by random unitary matrices, then: */
/* > */
/* >          Reduce the bandwidth according to KL and KU, using */
/* >              Householder transformations. */
/* > */
/* >      Method B: */
/* >          Convert the bandwidth-0 (i.e., diagonal) matrix to a */
/* >              bandwidth-1 matrix using Givens rotations, "chasing" */
/* >              out-of-band elements back, much as in QR; then convert */
/* >              the bandwidth-1 to a bandwidth-2 matrix, etc.  Note */
/* >              that for reasonably small bandwidths (relative to M and */
/* >              N) this requires less storage, as a dense matrix is not */
/* >              generated.  Also, for hermitian or symmetric matrices, */
/* >              only one triangle is generated. */
/* > */
/* >      Method A is chosen if the bandwidth is a large fraction of the */
/* >          order of the matrix, and LDA is at least M (so a dense */
/* >          matrix can be stored.)  Method B is chosen if the bandwidth */
/* >          is small (< 1/2 N for hermitian or symmetric, < .3 N+M for */
/* >          non-symmetric), or LDA is less than M and not less than the */
/* >          bandwidth. */
/* > */
/* >      Pack the matrix if desired. Options specified by PACK are: */
/* >         no packing */
/* >         zero out upper half (if hermitian) */
/* >         zero out lower half (if hermitian) */
/* >         store the upper half columnwise (if hermitian or upper */
/* >               triangular) */
/* >         store the lower half columnwise (if hermitian or lower */
/* >               triangular) */
/* >         store the lower triangle in banded format (if hermitian or */
/* >               lower triangular) */
/* >         store the upper triangle in banded format (if hermitian or */
/* >               upper triangular) */
/* >         store the entire matrix in banded format */
/* >      If Method B is chosen, and band format is specified, then the */
/* >         matrix will be generated in the band format, so no repacking */
/* >         will be necessary. */
/* > \endverbatim */

/*  Arguments: */
/*  ========== */

/* > \param[in] M */
/* > \verbatim */
/* >          M is INTEGER */
/* >           The number of rows of A. Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in] N */
/* > \verbatim */
/* >          N is INTEGER */
/* >           The number of columns of A. N must equal M if the matrix */
/* >           is symmetric or hermitian (i.e., if SYM is not 'N') */
/* >           Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in] DIST */
/* > \verbatim */
/* >          DIST is CHARACTER*1 */
/* >           On entry, DIST specifies the type of distribution to be used */
/* >           to generate the random eigen-/singular values. */
/* >           'U' => UNIFORM( 0, 1 )  ( 'U' for uniform ) */
/* >           'S' => UNIFORM( -1, 1 ) ( 'S' for symmetric ) */
/* >           'N' => NORMAL( 0, 1 )   ( 'N' for normal ) */
/* >           Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in,out] ISEED */
/* > \verbatim */
/* >          ISEED is INTEGER array, dimension ( 4 ) */
/* >           On entry ISEED specifies the seed of the random number */
/* >           generator. They should lie between 0 and 4095 inclusive, */
/* >           and ISEED(4) should be odd. The random number generator */
/* >           uses a linear congruential sequence limited to small */
/* >           integers, and so should produce machine independent */
/* >           random numbers. The values of ISEED are changed on */
/* >           exit, and can be used in the next call to CLATMT */
/* >           to continue the same random number sequence. */
/* >           Changed on exit. */
/* > \endverbatim */
/* > */
/* > \param[in] SYM */
/* > \verbatim */
/* >          SYM is CHARACTER*1 */
/* >           If SYM='H', the generated matrix is hermitian, with */
/* >             eigenvalues specified by D, COND, MODE, and DMAX; they */
/* >             may be positive, negative, or zero. */
/* >           If SYM='P', the generated matrix is hermitian, with */
/* >             eigenvalues (= singular values) specified by D, COND, */
/* >             MODE, and DMAX; they will not be negative. */
/* >           If SYM='N', the generated matrix is nonsymmetric, with */
/* >             singular values specified by D, COND, MODE, and DMAX; */
/* >             they will not be negative. */
/* >           If SYM='S', the generated matrix is (complex) symmetric, */
/* >             with singular values specified by D, COND, MODE, and */
/* >             DMAX; they will not be negative. */
/* >           Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in,out] D */
/* > \verbatim */
/* >          D is REAL array, dimension ( MIN( M, N ) ) */
/* >           This array is used to specify the singular values or */
/* >           eigenvalues of A (see SYM, above.)  If MODE=0, then D is */
/* >           assumed to contain the singular/eigenvalues, otherwise */
/* >           they will be computed according to MODE, COND, and DMAX, */
/* >           and placed in D. */
/* >           Modified if MODE is nonzero. */
/* > \endverbatim */
/* > */
/* > \param[in] MODE */
/* > \verbatim */
/* >          MODE is INTEGER */
/* >           On entry this describes how the singular/eigenvalues are to */
/* >           be specified: */
/* >           MODE = 0 means use D as input */
/* >           MODE = 1 sets D(1)=1 and D(2:RANK)=1.0/COND */
/* >           MODE = 2 sets D(1:RANK-1)=1 and D(RANK)=1.0/COND */
/* >           MODE = 3 sets D(I)=COND**(-(I-1)/(RANK-1)) */
/* >           MODE = 4 sets D(i)=1 - (i-1)/(N-1)*(1 - 1/COND) */
/* >           MODE = 5 sets D to random numbers in the range */
/* >                    ( 1/COND , 1 ) such that their logarithms */
/* >                    are uniformly distributed. */
/* >           MODE = 6 set D to random numbers from same distribution */
/* >                    as the rest of the matrix. */
/* >           MODE < 0 has the same meaning as ABS(MODE), except that */
/* >              the order of the elements of D is reversed. */
/* >           Thus if MODE is positive, D has entries ranging from */
/* >              1 to 1/COND, if negative, from 1/COND to 1, */
/* >           If SYM='H', and MODE is neither 0, 6, nor -6, then */
/* >              the elements of D will also be multiplied by a random */
/* >              sign (i.e., +1 or -1.) */
/* >           Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in] COND */
/* > \verbatim */
/* >          COND is REAL */
/* >           On entry, this is used as described under MODE above. */
/* >           If used, it must be >= 1. Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in] DMAX */
/* > \verbatim */
/* >          DMAX is REAL */
/* >           If MODE is neither -6, 0 nor 6, the contents of D, as */
/* >           computed according to MODE and COND, will be scaled by */
/* >           DMAX / f2cmax(abs(D(i))); thus, the maximum absolute eigen- or */
/* >           singular value (which is to say the norm) will be abs(DMAX). */
/* >           Note that DMAX need not be positive: if DMAX is negative */
/* >           (or zero), D will be scaled by a negative number (or zero). */
/* >           Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in] RANK */
/* > \verbatim */
/* >          RANK is INTEGER */
/* >           The rank of matrix to be generated for modes 1,2,3 only. */
/* >           D( RANK+1:N ) = 0. */
/* >           Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in] KL */
/* > \verbatim */
/* >          KL is INTEGER */
/* >           This specifies the lower bandwidth of the  matrix. For */
/* >           example, KL=0 implies upper triangular, KL=1 implies upper */
/* >           Hessenberg, and KL being at least M-1 means that the matrix */
/* >           has full lower bandwidth.  KL must equal KU if the matrix */
/* >           is symmetric or hermitian. */
/* >           Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in] KU */
/* > \verbatim */
/* >          KU is INTEGER */
/* >           This specifies the upper bandwidth of the  matrix. For */
/* >           example, KU=0 implies lower triangular, KU=1 implies lower */
/* >           Hessenberg, and KU being at least N-1 means that the matrix */
/* >           has full upper bandwidth.  KL must equal KU if the matrix */
/* >           is symmetric or hermitian. */
/* >           Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in] PACK */
/* > \verbatim */
/* >          PACK is CHARACTER*1 */
/* >           This specifies packing of matrix as follows: */
/* >           'N' => no packing */
/* >           'U' => zero out all subdiagonal entries (if symmetric */
/* >                  or hermitian) */
/* >           'L' => zero out all superdiagonal entries (if symmetric */
/* >                  or hermitian) */
/* >           'C' => store the upper triangle columnwise (only if the */
/* >                  matrix is symmetric, hermitian, or upper triangular) */
/* >           'R' => store the lower triangle columnwise (only if the */
/* >                  matrix is symmetric, hermitian, or lower triangular) */
/* >           'B' => store the lower triangle in band storage scheme */
/* >                  (only if the matrix is symmetric, hermitian, or */
/* >                  lower triangular) */
/* >           'Q' => store the upper triangle in band storage scheme */
/* >                  (only if the matrix is symmetric, hermitian, or */
/* >                  upper triangular) */
/* >           'Z' => store the entire matrix in band storage scheme */
/* >                      (pivoting can be provided for by using this */
/* >                      option to store A in the trailing rows of */
/* >                      the allocated storage) */
/* > */
/* >           Using these options, the various LAPACK packed and banded */
/* >           storage schemes can be obtained: */
/* >           GB                    - use 'Z' */
/* >           PB, SB, HB, or TB     - use 'B' or 'Q' */
/* >           PP, SP, HB, or TP     - use 'C' or 'R' */
/* > */
/* >           If two calls to CLATMT differ only in the PACK parameter, */
/* >           they will generate mathematically equivalent matrices. */
/* >           Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in,out] A */
/* > \verbatim */
/* >          A is COMPLEX array, dimension ( LDA, N ) */
/* >           On exit A is the desired test matrix.  A is first generated */
/* >           in full (unpacked) form, and then packed, if so specified */
/* >           by PACK.  Thus, the first M elements of the first N */
/* >           columns will always be modified.  If PACK specifies a */
/* >           packed or banded storage scheme, all LDA elements of the */
/* >           first N columns will be modified; the elements of the */
/* >           array which do not correspond to elements of the generated */
/* >           matrix are set to zero. */
/* >           Modified. */
/* > \endverbatim */
/* > */
/* > \param[in] LDA */
/* > \verbatim */
/* >          LDA is INTEGER */
/* >           LDA specifies the first dimension of A as declared in the */
/* >           calling program.  If PACK='N', 'U', 'L', 'C', or 'R', then */
/* >           LDA must be at least M.  If PACK='B' or 'Q', then LDA must */
/* >           be at least MIN( KL, M-1) (which is equal to MIN(KU,N-1)). */
/* >           If PACK='Z', LDA must be large enough to hold the packed */
/* >           array: MIN( KU, N-1) + MIN( KL, M-1) + 1. */
/* >           Not modified. */
/* > \endverbatim */
/* > */
/* > \param[out] WORK */
/* > \verbatim */
/* >          WORK is COMPLEX array, dimension ( 3*MAX( N, M ) ) */
/* >           Workspace. */
/* >           Modified. */
/* > \endverbatim */
/* > */
/* > \param[out] INFO */
/* > \verbatim */
/* >          INFO is INTEGER */
/* >           Error code.  On exit, INFO will be set to one of the */
/* >           following values: */
/* >             0 => normal return */
/* >            -1 => M negative or unequal to N and SYM='S', 'H', or 'P' */
/* >            -2 => N negative */
/* >            -3 => DIST illegal string */
/* >            -5 => SYM illegal string */
/* >            -7 => MODE not in range -6 to 6 */
/* >            -8 => COND less than 1.0, and MODE neither -6, 0 nor 6 */
/* >           -10 => KL negative */
/* >           -11 => KU negative, or SYM is not 'N' and KU is not equal to */
/* >                  KL */
/* >           -12 => PACK illegal string, or PACK='U' or 'L', and SYM='N'; */
/* >                  or PACK='C' or 'Q' and SYM='N' and KL is not zero; */
/* >                  or PACK='R' or 'B' and SYM='N' and KU is not zero; */
/* >                  or PACK='U', 'L', 'C', 'R', 'B', or 'Q', and M is not */
/* >                  N. */
/* >           -14 => LDA is less than M, or PACK='Z' and LDA is less than */
/* >                  MIN(KU,N-1) + MIN(KL,M-1) + 1. */
/* >            1  => Error return from SLATM7 */
/* >            2  => Cannot scale to DMAX (f2cmax. sing. value is 0) */
/* >            3  => Error return from CLAGGE, CLAGHE or CLAGSY */
/* > \endverbatim */

/*  Authors: */
/*  ======== */

/* > \author Univ. of Tennessee */
/* > \author Univ. of California Berkeley */
/* > \author Univ. of Colorado Denver */
/* > \author NAG Ltd. */

/* > \date December 2016 */

/* > \ingroup complex_matgen */

/*  ===================================================================== */
/* Subroutine */ int clatmt_(integer *m, integer *n, char *dist, integer *
	iseed, char *sym, real *d__, integer *mode, real *cond, real *dmax__, 
	integer *rank, integer *kl, integer *ku, char *pack, complex *a, 
	integer *lda, complex *work, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4, i__5, i__6;
    real r__1, r__2, r__3;
    complex q__1, q__2, q__3;
    logical L__1;

    /* Local variables */
    integer ilda, icol;
    real temp;
    logical csym;
    integer irow, isym;
    complex c__;
    integer i__, j, k;
    complex s;
    real alpha, angle, realc;
    integer ipack, ioffg;
    extern logical lsame_(char *, char *);
    integer iinfo;
    extern /* Subroutine */ int sscal_(integer *, real *, real *, integer *);
    complex ctemp;
    integer idist, mnmin;
    complex extra;
    integer iskew;
    complex dummy;
    extern /* Subroutine */ int slatm7_(integer *, real *, integer *, integer 
	    *, integer *, real *, integer *, integer *, integer *);
    integer ic, jc, nc;
    extern /* Subroutine */ int clagge_(integer *, integer *, integer *, 
	    integer *, real *, complex *, integer *, integer *, complex *, 
	    integer *), claghe_(integer *, integer *, real *, complex *, 
	    integer *, integer *, complex *, integer *);
    integer il;
    complex ct;
    integer iendch, ir, jr, ipackg, mr;
    //extern /* Complex */ VOID clarnd_(complex *, integer *, integer *);
    extern complex clarnd_(integer *, integer *);
    integer minlda;
    complex st;
    extern /* Subroutine */ int claset_(char *, integer *, integer *, complex 
	    *, complex *, complex *, integer *), clartg_(complex *, 
	    complex *, real *, complex *, complex *), xerbla_(char *, integer 
	    *), clagsy_(integer *, integer *, real *, complex *, 
	    integer *, integer *, complex *, integer *);
    extern real slarnd_(integer *, integer *);
    extern /* Subroutine */ int clarot_(logical *, logical *, logical *, 
	    integer *, complex *, complex *, complex *, integer *, complex *, 
	    complex *);
    integer ioffst, irsign;
    logical givens, iltemp, ilextr, topdwn;
    integer ir1, ir2, isympk, jch, llb, jkl, jku, uub;


/*  -- LAPACK computational routine (version 3.7.0) -- */
/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
/*     December 2016 */


/*  ===================================================================== */


/*     1)      Decode and Test the input parameters. */
/*             Initialize flags & seed. */

    /* Parameter adjustments */
    --iseed;
    --d__;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --work;

    /* Function Body */
    *info = 0;

/*     Quick return if possible */

    if (*m == 0 || *n == 0) {
	return 0;
    }

/*     Decode DIST */

    if (lsame_(dist, "U")) {
	idist = 1;
    } else if (lsame_(dist, "S")) {
	idist = 2;
    } else if (lsame_(dist, "N")) {
	idist = 3;
    } else {
	idist = -1;
    }

/*     Decode SYM */

    if (lsame_(sym, "N")) {
	isym = 1;
	irsign = 0;
	csym = FALSE_;
    } else if (lsame_(sym, "P")) {
	isym = 2;
	irsign = 0;
	csym = FALSE_;
    } else if (lsame_(sym, "S")) {
	isym = 2;
	irsign = 0;
	csym = TRUE_;
    } else if (lsame_(sym, "H")) {
	isym = 2;
	irsign = 1;
	csym = FALSE_;
    } else {
	isym = -1;
    }

/*     Decode PACK */

    isympk = 0;
    if (lsame_(pack, "N")) {
	ipack = 0;
    } else if (lsame_(pack, "U")) {
	ipack = 1;
	isympk = 1;
    } else if (lsame_(pack, "L")) {
	ipack = 2;
	isympk = 1;
    } else if (lsame_(pack, "C")) {
	ipack = 3;
	isympk = 2;
    } else if (lsame_(pack, "R")) {
	ipack = 4;
	isympk = 3;
    } else if (lsame_(pack, "B")) {
	ipack = 5;
	isympk = 3;
    } else if (lsame_(pack, "Q")) {
	ipack = 6;
	isympk = 2;
    } else if (lsame_(pack, "Z")) {
	ipack = 7;
    } else {
	ipack = -1;
    }

/*     Set certain internal parameters */

    mnmin = f2cmin(*m,*n);
/* Computing MIN */
    i__1 = *kl, i__2 = *m - 1;
    llb = f2cmin(i__1,i__2);
/* Computing MIN */
    i__1 = *ku, i__2 = *n - 1;
    uub = f2cmin(i__1,i__2);
/* Computing MIN */
    i__1 = *m, i__2 = *n + llb;
    mr = f2cmin(i__1,i__2);
/* Computing MIN */
    i__1 = *n, i__2 = *m + uub;
    nc = f2cmin(i__1,i__2);

    if (ipack == 5 || ipack == 6) {
	minlda = uub + 1;
    } else if (ipack == 7) {
	minlda = llb + uub + 1;
    } else {
	minlda = *m;
    }

/*     Use Givens rotation method if bandwidth small enough, */
/*     or if LDA is too small to store the matrix unpacked. */

    givens = FALSE_;
    if (isym == 1) {
/* Computing MAX */
	i__1 = 1, i__2 = mr + nc;
	if ((real) (llb + uub) < (real) f2cmax(i__1,i__2) * .3f) {
	    givens = TRUE_;
	}
    } else {
	if (llb << 1 < *m) {
	    givens = TRUE_;
	}
    }
    if (*lda < *m && *lda >= minlda) {
	givens = TRUE_;
    }

/*     Set INFO if an error */

    if (*m < 0) {
	*info = -1;
    } else if (*m != *n && isym != 1) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (idist == -1) {
	*info = -3;
    } else if (isym == -1) {
	*info = -5;
    } else if (abs(*mode) > 6) {
	*info = -7;
    } else if (*mode != 0 && abs(*mode) != 6 && *cond < 1.f) {
	*info = -8;
    } else if (*kl < 0) {
	*info = -10;
    } else if (*ku < 0 || isym != 1 && *kl != *ku) {
	*info = -11;
    } else if (ipack == -1 || isympk == 1 && isym == 1 || isympk == 2 && isym 
	    == 1 && *kl > 0 || isympk == 3 && isym == 1 && *ku > 0 || isympk 
	    != 0 && *m != *n) {
	*info = -12;
    } else if (*lda < f2cmax(1,minlda)) {
	*info = -14;
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("CLATMT", &i__1);
	return 0;
    }

/*     Initialize random number generator */

    for (i__ = 1; i__ <= 4; ++i__) {
	iseed[i__] = (i__1 = iseed[i__], abs(i__1)) % 4096;
/* L100: */
    }

    if (iseed[4] % 2 != 1) {
	++iseed[4];
    }

/*     2)      Set up D  if indicated. */

/*             Compute D according to COND and MODE */

    slatm7_(mode, cond, &irsign, &idist, &iseed[1], &d__[1], &mnmin, rank, &
	    iinfo);
    if (iinfo != 0) {
	*info = 1;
	return 0;
    }

/*     Choose Top-Down if D is (apparently) increasing, */
/*     Bottom-Up if D is (apparently) decreasing. */

    if (abs(d__[1]) <= (r__1 = d__[*rank], abs(r__1))) {
	topdwn = TRUE_;
    } else {
	topdwn = FALSE_;
    }

    if (*mode != 0 && abs(*mode) != 6) {

/*        Scale by DMAX */

	temp = abs(d__[1]);
	i__1 = *rank;
	for (i__ = 2; i__ <= i__1; ++i__) {
/* Computing MAX */
	    r__2 = temp, r__3 = (r__1 = d__[i__], abs(r__1));
	    temp = f2cmax(r__2,r__3);
/* L110: */
	}

	if (temp > 0.f) {
	    alpha = *dmax__ / temp;
	} else {
	    *info = 2;
	    return 0;
	}

	sscal_(rank, &alpha, &d__[1], &c__1);

    }

    claset_("Full", lda, n, &c_b1, &c_b1, &a[a_offset], lda);

/*     3)      Generate Banded Matrix using Givens rotations. */
/*             Also the special case of UUB=LLB=0 */

/*               Compute Addressing constants to cover all */
/*               storage formats.  Whether GE, HE, SY, GB, HB, or SB, */
/*               upper or lower triangle or both, */
/*               the (i,j)-th element is in */
/*               A( i - ISKEW*j + IOFFST, j ) */

    if (ipack > 4) {
	ilda = *lda - 1;
	iskew = 1;
	if (ipack > 5) {
	    ioffst = uub + 1;
	} else {
	    ioffst = 1;
	}
    } else {
	ilda = *lda;
	iskew = 0;
	ioffst = 0;
    }

/*     IPACKG is the format that the matrix is generated in. If this is */
/*     different from IPACK, then the matrix must be repacked at the */
/*     end.  It also signals how to compute the norm, for scaling. */

    ipackg = 0;

/*     Diagonal Matrix -- We are done, unless it */
/*     is to be stored HP/SP/PP/TP (PACK='R' or 'C') */

    if (llb == 0 && uub == 0) {
	i__1 = mnmin;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = (1 - iskew) * j + ioffst + j * a_dim1;
	    i__3 = j;
	    q__1.r = d__[i__3], q__1.i = 0.f;
	    a[i__2].r = q__1.r, a[i__2].i = q__1.i;
/* L120: */
	}

	if (ipack <= 2 || ipack >= 5) {
	    ipackg = ipack;
	}

    } else if (givens) {

/*        Check whether to use Givens rotations, */
/*        Householder transformations, or nothing. */

	if (isym == 1) {

/*           Non-symmetric -- A = U D V */

	    if (ipack > 4) {
		ipackg = ipack;
	    } else {
		ipackg = 0;
	    }

	    i__1 = mnmin;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = (1 - iskew) * j + ioffst + j * a_dim1;
		i__3 = j;
		q__1.r = d__[i__3], q__1.i = 0.f;
		a[i__2].r = q__1.r, a[i__2].i = q__1.i;
/* L130: */
	    }

	    if (topdwn) {
		jkl = 0;
		i__1 = uub;
		for (jku = 1; jku <= i__1; ++jku) {

/*                 Transform from bandwidth JKL, JKU-1 to JKL, JKU */

/*                 Last row actually rotated is M */
/*                 Last column actually rotated is MIN( M+JKU, N ) */

/* Computing MIN */
		    i__3 = *m + jku;
		    i__2 = f2cmin(i__3,*n) + jkl - 1;
		    for (jr = 1; jr <= i__2; ++jr) {
			extra.r = 0.f, extra.i = 0.f;
			angle = slarnd_(&c__1, &iseed[1]) * 
				6.2831853071795864769252867663f;
			r__1 = cos(angle);
			//clarnd_(&q__2, &c__5, &iseed[1]);
			q__2=clarnd_(&c__5, &iseed[1]);
			q__1.r = r__1 * q__2.r, q__1.i = r__1 * q__2.i;
			c__.r = q__1.r, c__.i = q__1.i;
			r__1 = sin(angle);
			//clarnd_(&q__2, &c__5, &iseed[1]);
			q__2=clarnd_(&c__5, &iseed[1]);
			q__1.r = r__1 * q__2.r, q__1.i = r__1 * q__2.i;
			s.r = q__1.r, s.i = q__1.i;
/* Computing MAX */
			i__3 = 1, i__4 = jr - jkl;
			icol = f2cmax(i__3,i__4);
			if (jr < *m) {
/* Computing MIN */
			    i__3 = *n, i__4 = jr + jku;
			    il = f2cmin(i__3,i__4) + 1 - icol;
			    L__1 = jr > jkl;
			    clarot_(&c_true, &L__1, &c_false, &il, &c__, &s, &
				    a[jr - iskew * icol + ioffst + icol * 
				    a_dim1], &ilda, &extra, &dummy);
			}

/*                    Chase "EXTRA" back up */

			ir = jr;
			ic = icol;
			i__3 = -jkl - jku;
			for (jch = jr - jkl; i__3 < 0 ? jch >= 1 : jch <= 1; 
				jch += i__3) {
			    if (ir < *m) {
				clartg_(&a[ir + 1 - iskew * (ic + 1) + ioffst 
					+ (ic + 1) * a_dim1], &extra, &realc, 
					&s, &dummy);
				//clarnd_(&q__1, &c__5, &iseed[1]);
				q__1=clarnd_(&c__5, &iseed[1]);
				dummy.r = q__1.r, dummy.i = q__1.i;
				q__2.r = realc * dummy.r, q__2.i = realc * 
					dummy.i;
				r_cnjg(&q__1, &q__2);
				c__.r = q__1.r, c__.i = q__1.i;
				q__3.r = -s.r, q__3.i = -s.i;
				q__2.r = q__3.r * dummy.r - q__3.i * dummy.i, 
					q__2.i = q__3.r * dummy.i + q__3.i * 
					dummy.r;
				r_cnjg(&q__1, &q__2);
				s.r = q__1.r, s.i = q__1.i;
			    }
/* Computing MAX */
			    i__4 = 1, i__5 = jch - jku;
			    irow = f2cmax(i__4,i__5);
			    il = ir + 2 - irow;
			    ctemp.r = 0.f, ctemp.i = 0.f;
			    iltemp = jch > jku;
			    clarot_(&c_false, &iltemp, &c_true, &il, &c__, &s,
				     &a[irow - iskew * ic + ioffst + ic * 
				    a_dim1], &ilda, &ctemp, &extra);
			    if (iltemp) {
				clartg_(&a[irow + 1 - iskew * (ic + 1) + 
					ioffst + (ic + 1) * a_dim1], &ctemp, &
					realc, &s, &dummy);
				//clarnd_(&q__1, &c__5, &iseed[1]);
				q__1=clarnd_(&c__5, &iseed[1]);
				dummy.r = q__1.r, dummy.i = q__1.i;
				q__2.r = realc * dummy.r, q__2.i = realc * 
					dummy.i;
				r_cnjg(&q__1, &q__2);
				c__.r = q__1.r, c__.i = q__1.i;
				q__3.r = -s.r, q__3.i = -s.i;
				q__2.r = q__3.r * dummy.r - q__3.i * dummy.i, 
					q__2.i = q__3.r * dummy.i + q__3.i * 
					dummy.r;
				r_cnjg(&q__1, &q__2);
				s.r = q__1.r, s.i = q__1.i;

/* Computing MAX */
				i__4 = 1, i__5 = jch - jku - jkl;
				icol = f2cmax(i__4,i__5);
				il = ic + 2 - icol;
				extra.r = 0.f, extra.i = 0.f;
				L__1 = jch > jku + jkl;
				clarot_(&c_true, &L__1, &c_true, &il, &c__, &
					s, &a[irow - iskew * icol + ioffst + 
					icol * a_dim1], &ilda, &extra, &ctemp)
					;
				ic = icol;
				ir = irow;
			    }
/* L140: */
			}
/* L150: */
		    }
/* L160: */
		}

		jku = uub;
		i__1 = llb;
		for (jkl = 1; jkl <= i__1; ++jkl) {

/*                 Transform from bandwidth JKL-1, JKU to JKL, JKU */

/* Computing MIN */
		    i__3 = *n + jkl;
		    i__2 = f2cmin(i__3,*m) + jku - 1;
		    for (jc = 1; jc <= i__2; ++jc) {
			extra.r = 0.f, extra.i = 0.f;
			angle = slarnd_(&c__1, &iseed[1]) * 
				6.2831853071795864769252867663f;
			r__1 = cos(angle);
			//clarnd_(&q__2, &c__5, &iseed[1]);
			q__2=clarnd_(&c__5, &iseed[1]);
			q__1.r = r__1 * q__2.r, q__1.i = r__1 * q__2.i;
			c__.r = q__1.r, c__.i = q__1.i;
			r__1 = sin(angle);
			//clarnd_(&q__2, &c__5, &iseed[1]);
			q__2=clarnd_(&c__5, &iseed[1]);
			q__1.r = r__1 * q__2.r, q__1.i = r__1 * q__2.i;
			s.r = q__1.r, s.i = q__1.i;
/* Computing MAX */
			i__3 = 1, i__4 = jc - jku;
			irow = f2cmax(i__3,i__4);
			if (jc < *n) {
/* Computing MIN */
			    i__3 = *m, i__4 = jc + jkl;
			    il = f2cmin(i__3,i__4) + 1 - irow;
			    L__1 = jc > jku;
			    clarot_(&c_false, &L__1, &c_false, &il, &c__, &s, 
				    &a[irow - iskew * jc + ioffst + jc * 
				    a_dim1], &ilda, &extra, &dummy);
			}

/*                    Chase "EXTRA" back up */

			ic = jc;
			ir = irow;
			i__3 = -jkl - jku;
			for (jch = jc - jku; i__3 < 0 ? jch >= 1 : jch <= 1; 
				jch += i__3) {
			    if (ic < *n) {
				clartg_(&a[ir + 1 - iskew * (ic + 1) + ioffst 
					+ (ic + 1) * a_dim1], &extra, &realc, 
					&s, &dummy);
				//clarnd_(&q__1, &c__5, &iseed[1]);
				q__1=clarnd_(&c__5, &iseed[1]);
				dummy.r = q__1.r, dummy.i = q__1.i;
				q__2.r = realc * dummy.r, q__2.i = realc * 
					dummy.i;
				r_cnjg(&q__1, &q__2);
				c__.r = q__1.r, c__.i = q__1.i;
				q__3.r = -s.r, q__3.i = -s.i;
				q__2.r = q__3.r * dummy.r - q__3.i * dummy.i, 
					q__2.i = q__3.r * dummy.i + q__3.i * 
					dummy.r;
				r_cnjg(&q__1, &q__2);
				s.r = q__1.r, s.i = q__1.i;
			    }
/* Computing MAX */
			    i__4 = 1, i__5 = jch - jkl;
			    icol = f2cmax(i__4,i__5);
			    il = ic + 2 - icol;
			    ctemp.r = 0.f, ctemp.i = 0.f;
			    iltemp = jch > jkl;
			    clarot_(&c_true, &iltemp, &c_true, &il, &c__, &s, 
				    &a[ir - iskew * icol + ioffst + icol * 
				    a_dim1], &ilda, &ctemp, &extra);
			    if (iltemp) {
				clartg_(&a[ir + 1 - iskew * (icol + 1) + 
					ioffst + (icol + 1) * a_dim1], &ctemp,
					 &realc, &s, &dummy);
				//clarnd_(&q__1, &c__5, &iseed[1]);
				q__1=clarnd_(&c__5, &iseed[1]);
				dummy.r = q__1.r, dummy.i = q__1.i;
				q__2.r = realc * dummy.r, q__2.i = realc * 
					dummy.i;
				r_cnjg(&q__1, &q__2);
				c__.r = q__1.r, c__.i = q__1.i;
				q__3.r = -s.r, q__3.i = -s.i;
				q__2.r = q__3.r * dummy.r - q__3.i * dummy.i, 
					q__2.i = q__3.r * dummy.i + q__3.i * 
					dummy.r;
				r_cnjg(&q__1, &q__2);
				s.r = q__1.r, s.i = q__1.i;
/* Computing MAX */
				i__4 = 1, i__5 = jch - jkl - jku;
				irow = f2cmax(i__4,i__5);
				il = ir + 2 - irow;
				extra.r = 0.f, extra.i = 0.f;
				L__1 = jch > jkl + jku;
				clarot_(&c_false, &L__1, &c_true, &il, &c__, &
					s, &a[irow - iskew * icol + ioffst + 
					icol * a_dim1], &ilda, &extra, &ctemp)
					;
				ic = icol;
				ir = irow;
			    }
/* L170: */
			}
/* L180: */
		    }
/* L190: */
		}

	    } else {

/*              Bottom-Up -- Start at the bottom right. */

		jkl = 0;
		i__1 = uub;
		for (jku = 1; jku <= i__1; ++jku) {

/*                 Transform from bandwidth JKL, JKU-1 to JKL, JKU */

/*                 First row actually rotated is M */
/*                 First column actually rotated is MIN( M+JKU, N ) */

/* Computing MIN */
		    i__2 = *m, i__3 = *n + jkl;
		    iendch = f2cmin(i__2,i__3) - 1;
/* Computing MIN */
		    i__2 = *m + jku;
		    i__3 = 1 - jkl;
		    for (jc = f2cmin(i__2,*n) - 1; jc >= i__3; --jc) {
			extra.r = 0.f, extra.i = 0.f;
			angle = slarnd_(&c__1, &iseed[1]) * 
				6.2831853071795864769252867663f;
			r__1 = cos(angle);
			//clarnd_(&q__2, &c__5, &iseed[1]);
			q__2=clarnd_(&c__5, &iseed[1]);
			q__1.r = r__1 * q__2.r, q__1.i = r__1 * q__2.i;
			c__.r = q__1.r, c__.i = q__1.i;
			r__1 = sin(angle);
			//clarnd_(&q__2, &c__5, &iseed[1]);
			q__2=clarnd_(&c__5, &iseed[1]);
			q__1.r = r__1 * q__2.r, q__1.i = r__1 * q__2.i;
			s.r = q__1.r, s.i = q__1.i;
/* Computing MAX */
			i__2 = 1, i__4 = jc - jku + 1;
			irow = f2cmax(i__2,i__4);
			if (jc > 0) {
/* Computing MIN */
			    i__2 = *m, i__4 = jc + jkl + 1;
			    il = f2cmin(i__2,i__4) + 1 - irow;
			    L__1 = jc + jkl < *m;
			    clarot_(&c_false, &c_false, &L__1, &il, &c__, &s, 
				    &a[irow - iskew * jc + ioffst + jc * 
				    a_dim1], &ilda, &dummy, &extra);
			}

/*                    Chase "EXTRA" back down */

			ic = jc;
			i__2 = iendch;
			i__4 = jkl + jku;
			for (jch = jc + jkl; i__4 < 0 ? jch >= i__2 : jch <= 
				i__2; jch += i__4) {
			    ilextr = ic > 0;
			    if (ilextr) {
				clartg_(&a[jch - iskew * ic + ioffst + ic * 
					a_dim1], &extra, &realc, &s, &dummy);
				//clarnd_(&q__1, &c__5, &iseed[1]);
				q__1=clarnd_(&c__5, &iseed[1]);
				dummy.r = q__1.r, dummy.i = q__1.i;
				q__1.r = realc * dummy.r, q__1.i = realc * 
					dummy.i;
				c__.r = q__1.r, c__.i = q__1.i;
				q__1.r = s.r * dummy.r - s.i * dummy.i, 
					q__1.i = s.r * dummy.i + s.i * 
					dummy.r;
				s.r = q__1.r, s.i = q__1.i;
			    }
			    ic = f2cmax(1,ic);
/* Computing MIN */
			    i__5 = *n - 1, i__6 = jch + jku;
			    icol = f2cmin(i__5,i__6);
			    iltemp = jch + jku < *n;
			    ctemp.r = 0.f, ctemp.i = 0.f;
			    i__5 = icol + 2 - ic;
			    clarot_(&c_true, &ilextr, &iltemp, &i__5, &c__, &
				    s, &a[jch - iskew * ic + ioffst + ic * 
				    a_dim1], &ilda, &extra, &ctemp);
			    if (iltemp) {
				clartg_(&a[jch - iskew * icol + ioffst + icol 
					* a_dim1], &ctemp, &realc, &s, &dummy)
					;
				//clarnd_(&q__1, &c__5, &iseed[1]);
				q__1=clarnd_(&c__5, &iseed[1]);
				dummy.r = q__1.r, dummy.i = q__1.i;
				q__1.r = realc * dummy.r, q__1.i = realc * 
					dummy.i;
				c__.r = q__1.r, c__.i = q__1.i;
				q__1.r = s.r * dummy.r - s.i * dummy.i, 
					q__1.i = s.r * dummy.i + s.i * 
					dummy.r;
				s.r = q__1.r, s.i = q__1.i;
/* Computing MIN */
				i__5 = iendch, i__6 = jch + jkl + jku;
				il = f2cmin(i__5,i__6) + 2 - jch;
				extra.r = 0.f, extra.i = 0.f;
				L__1 = jch + jkl + jku <= iendch;
				clarot_(&c_false, &c_true, &L__1, &il, &c__, &
					s, &a[jch - iskew * icol + ioffst + 
					icol * a_dim1], &ilda, &ctemp, &extra)
					;
				ic = icol;
			    }
/* L200: */
			}
/* L210: */
		    }
/* L220: */
		}

		jku = uub;
		i__1 = llb;
		for (jkl = 1; jkl <= i__1; ++jkl) {

/*                 Transform from bandwidth JKL-1, JKU to JKL, JKU */

/*                 First row actually rotated is MIN( N+JKL, M ) */
/*                 First column actually rotated is N */

/* Computing MIN */
		    i__3 = *n, i__4 = *m + jku;
		    iendch = f2cmin(i__3,i__4) - 1;
/* Computing MIN */
		    i__3 = *n + jkl;
		    i__4 = 1 - jku;
		    for (jr = f2cmin(i__3,*m) - 1; jr >= i__4; --jr) {
			extra.r = 0.f, extra.i = 0.f;
			angle = slarnd_(&c__1, &iseed[1]) * 
				6.2831853071795864769252867663f;
			r__1 = cos(angle);
			//clarnd_(&q__2, &c__5, &iseed[1]);
			q__2=clarnd_(&c__5, &iseed[1]);
			q__1.r = r__1 * q__2.r, q__1.i = r__1 * q__2.i;
			c__.r = q__1.r, c__.i = q__1.i;
			r__1 = sin(angle);
			//clarnd_(&q__2, &c__5, &iseed[1]);
			q__2=clarnd_(&c__5, &iseed[1]);
			q__1.r = r__1 * q__2.r, q__1.i = r__1 * q__2.i;
			s.r = q__1.r, s.i = q__1.i;
/* Computing MAX */
			i__3 = 1, i__2 = jr - jkl + 1;
			icol = f2cmax(i__3,i__2);
			if (jr > 0) {
/* Computing MIN */
			    i__3 = *n, i__2 = jr + jku + 1;
			    il = f2cmin(i__3,i__2) + 1 - icol;
			    L__1 = jr + jku < *n;
			    clarot_(&c_true, &c_false, &L__1, &il, &c__, &s, &
				    a[jr - iskew * icol + ioffst + icol * 
				    a_dim1], &ilda, &dummy, &extra);
			}

/*                    Chase "EXTRA" back down */

			ir = jr;
			i__3 = iendch;
			i__2 = jkl + jku;
			for (jch = jr + jku; i__2 < 0 ? jch >= i__3 : jch <= 
				i__3; jch += i__2) {
			    ilextr = ir > 0;
			    if (ilextr) {
				clartg_(&a[ir - iskew * jch + ioffst + jch * 
					a_dim1], &extra, &realc, &s, &dummy);
				//clarnd_(&q__1, &c__5, &iseed[1]);
				q__1=clarnd_(&c__5, &iseed[1]);
				dummy.r = q__1.r, dummy.i = q__1.i;
				q__1.r = realc * dummy.r, q__1.i = realc * 
					dummy.i;
				c__.r = q__1.r, c__.i = q__1.i;
				q__1.r = s.r * dummy.r - s.i * dummy.i, 
					q__1.i = s.r * dummy.i + s.i * 
					dummy.r;
				s.r = q__1.r, s.i = q__1.i;
			    }
			    ir = f2cmax(1,ir);
/* Computing MIN */
			    i__5 = *m - 1, i__6 = jch + jkl;
			    irow = f2cmin(i__5,i__6);
			    iltemp = jch + jkl < *m;
			    ctemp.r = 0.f, ctemp.i = 0.f;
			    i__5 = irow + 2 - ir;
			    clarot_(&c_false, &ilextr, &iltemp, &i__5, &c__, &
				    s, &a[ir - iskew * jch + ioffst + jch * 
				    a_dim1], &ilda, &extra, &ctemp);
			    if (iltemp) {
				clartg_(&a[irow - iskew * jch + ioffst + jch *
					 a_dim1], &ctemp, &realc, &s, &dummy);
				//clarnd_(&q__1, &c__5, &iseed[1]);
				q__1=clarnd_(&c__5, &iseed[1]);
				dummy.r = q__1.r, dummy.i = q__1.i;
				q__1.r = realc * dummy.r, q__1.i = realc * 
					dummy.i;
				c__.r = q__1.r, c__.i = q__1.i;
				q__1.r = s.r * dummy.r - s.i * dummy.i, 
					q__1.i = s.r * dummy.i + s.i * 
					dummy.r;
				s.r = q__1.r, s.i = q__1.i;
/* Computing MIN */
				i__5 = iendch, i__6 = jch + jkl + jku;
				il = f2cmin(i__5,i__6) + 2 - jch;
				extra.r = 0.f, extra.i = 0.f;
				L__1 = jch + jkl + jku <= iendch;
				clarot_(&c_true, &c_true, &L__1, &il, &c__, &
					s, &a[irow - iskew * jch + ioffst + 
					jch * a_dim1], &ilda, &ctemp, &extra);
				ir = irow;
			    }
/* L230: */
			}
/* L240: */
		    }
/* L250: */
		}

	    }

	} else {

/*           Symmetric -- A = U D U' */
/*           Hermitian -- A = U D U* */

	    ipackg = ipack;
	    ioffg = ioffst;

	    if (topdwn) {

/*              Top-Down -- Generate Upper triangle only */

		if (ipack >= 5) {
		    ipackg = 6;
		    ioffg = uub + 1;
		} else {
		    ipackg = 1;
		}

		i__1 = mnmin;
		for (j = 1; j <= i__1; ++j) {
		    i__4 = (1 - iskew) * j + ioffg + j * a_dim1;
		    i__2 = j;
		    q__1.r = d__[i__2], q__1.i = 0.f;
		    a[i__4].r = q__1.r, a[i__4].i = q__1.i;
/* L260: */
		}

		i__1 = uub;
		for (k = 1; k <= i__1; ++k) {
		    i__4 = *n - 1;
		    for (jc = 1; jc <= i__4; ++jc) {
/* Computing MAX */
			i__2 = 1, i__3 = jc - k;
			irow = f2cmax(i__2,i__3);
/* Computing MIN */
			i__2 = jc + 1, i__3 = k + 2;
			il = f2cmin(i__2,i__3);
			extra.r = 0.f, extra.i = 0.f;
			i__2 = jc - iskew * (jc + 1) + ioffg + (jc + 1) * 
				a_dim1;
			ctemp.r = a[i__2].r, ctemp.i = a[i__2].i;
			angle = slarnd_(&c__1, &iseed[1]) * 
				6.2831853071795864769252867663f;
			r__1 = cos(angle);
			//clarnd_(&q__2, &c__5, &iseed[1]);
			q__2=clarnd_(&c__5, &iseed[1]);
			q__1.r = r__1 * q__2.r, q__1.i = r__1 * q__2.i;
			c__.r = q__1.r, c__.i = q__1.i;
			r__1 = sin(angle);
			//clarnd_(&q__2, &c__5, &iseed[1]);
			q__2=clarnd_(&c__5, &iseed[1]);
			q__1.r = r__1 * q__2.r, q__1.i = r__1 * q__2.i;
			s.r = q__1.r, s.i = q__1.i;
			if (csym) {
			    ct.r = c__.r, ct.i = c__.i;
			    st.r = s.r, st.i = s.i;
			} else {
			    r_cnjg(&q__1, &ctemp);
			    ctemp.r = q__1.r, ctemp.i = q__1.i;
			    r_cnjg(&q__1, &c__);
			    ct.r = q__1.r, ct.i = q__1.i;
			    r_cnjg(&q__1, &s);
			    st.r = q__1.r, st.i = q__1.i;
			}
			L__1 = jc > k;
			clarot_(&c_false, &L__1, &c_true, &il, &c__, &s, &a[
				irow - iskew * jc + ioffg + jc * a_dim1], &
				ilda, &extra, &ctemp);
/* Computing MIN */
			i__3 = k, i__5 = *n - jc;
			i__2 = f2cmin(i__3,i__5) + 1;
			clarot_(&c_true, &c_true, &c_false, &i__2, &ct, &st, &
				a[(1 - iskew) * jc + ioffg + jc * a_dim1], &
				ilda, &ctemp, &dummy);

/*                    Chase EXTRA back up the matrix */

			icol = jc;
			i__2 = -k;
			for (jch = jc - k; i__2 < 0 ? jch >= 1 : jch <= 1; 
				jch += i__2) {
			    clartg_(&a[jch + 1 - iskew * (icol + 1) + ioffg + 
				    (icol + 1) * a_dim1], &extra, &realc, &s, 
				    &dummy);
			    //clarnd_(&q__1, &c__5, &iseed[1]);
			    q__1=clarnd_(&c__5, &iseed[1]);
			    dummy.r = q__1.r, dummy.i = q__1.i;
			    q__2.r = realc * dummy.r, q__2.i = realc * 
				    dummy.i;
			    r_cnjg(&q__1, &q__2);
			    c__.r = q__1.r, c__.i = q__1.i;
			    q__3.r = -s.r, q__3.i = -s.i;
			    q__2.r = q__3.r * dummy.r - q__3.i * dummy.i, 
				    q__2.i = q__3.r * dummy.i + q__3.i * 
				    dummy.r;
			    r_cnjg(&q__1, &q__2);
			    s.r = q__1.r, s.i = q__1.i;
			    i__3 = jch - iskew * (jch + 1) + ioffg + (jch + 1)
				     * a_dim1;
			    ctemp.r = a[i__3].r, ctemp.i = a[i__3].i;
			    if (csym) {
				ct.r = c__.r, ct.i = c__.i;
				st.r = s.r, st.i = s.i;
			    } else {
				r_cnjg(&q__1, &ctemp);
				ctemp.r = q__1.r, ctemp.i = q__1.i;
				r_cnjg(&q__1, &c__);
				ct.r = q__1.r, ct.i = q__1.i;
				r_cnjg(&q__1, &s);
				st.r = q__1.r, st.i = q__1.i;
			    }
			    i__3 = k + 2;
			    clarot_(&c_true, &c_true, &c_true, &i__3, &c__, &
				    s, &a[(1 - iskew) * jch + ioffg + jch * 
				    a_dim1], &ilda, &ctemp, &extra);
/* Computing MAX */
			    i__3 = 1, i__5 = jch - k;
			    irow = f2cmax(i__3,i__5);
/* Computing MIN */
			    i__3 = jch + 1, i__5 = k + 2;
			    il = f2cmin(i__3,i__5);
			    extra.r = 0.f, extra.i = 0.f;
			    L__1 = jch > k;
			    clarot_(&c_false, &L__1, &c_true, &il, &ct, &st, &
				    a[irow - iskew * jch + ioffg + jch * 
				    a_dim1], &ilda, &extra, &ctemp);
			    icol = jch;
/* L270: */
			}
/* L280: */
		    }
/* L290: */
		}

/*              If we need lower triangle, copy from upper. Note that */
/*              the order of copying is chosen to work for 'q' -> 'b' */

		if (ipack != ipackg && ipack != 3) {
		    i__1 = *n;
		    for (jc = 1; jc <= i__1; ++jc) {
			irow = ioffst - iskew * jc;
			if (csym) {
/* Computing MIN */
			    i__2 = *n, i__3 = jc + uub;
			    i__4 = f2cmin(i__2,i__3);
			    for (jr = jc; jr <= i__4; ++jr) {
				i__2 = jr + irow + jc * a_dim1;
				i__3 = jc - iskew * jr + ioffg + jr * a_dim1;
				a[i__2].r = a[i__3].r, a[i__2].i = a[i__3].i;
/* L300: */
			    }
			} else {
/* Computing MIN */
			    i__2 = *n, i__3 = jc + uub;
			    i__4 = f2cmin(i__2,i__3);
			    for (jr = jc; jr <= i__4; ++jr) {
				i__2 = jr + irow + jc * a_dim1;
				r_cnjg(&q__1, &a[jc - iskew * jr + ioffg + jr 
					* a_dim1]);
				a[i__2].r = q__1.r, a[i__2].i = q__1.i;
/* L310: */
			    }
			}
/* L320: */
		    }
		    if (ipack == 5) {
			i__1 = *n;
			for (jc = *n - uub + 1; jc <= i__1; ++jc) {
			    i__4 = uub + 1;
			    for (jr = *n + 2 - jc; jr <= i__4; ++jr) {
				i__2 = jr + jc * a_dim1;
				a[i__2].r = 0.f, a[i__2].i = 0.f;
/* L330: */
			    }
/* L340: */
			}
		    }
		    if (ipackg == 6) {
			ipackg = ipack;
		    } else {
			ipackg = 0;
		    }
		}
	    } else {

/*              Bottom-Up -- Generate Lower triangle only */

		if (ipack >= 5) {
		    ipackg = 5;
		    if (ipack == 6) {
			ioffg = 1;
		    }
		} else {
		    ipackg = 2;
		}

		i__1 = mnmin;
		for (j = 1; j <= i__1; ++j) {
		    i__4 = (1 - iskew) * j + ioffg + j * a_dim1;
		    i__2 = j;
		    q__1.r = d__[i__2], q__1.i = 0.f;
		    a[i__4].r = q__1.r, a[i__4].i = q__1.i;
/* L350: */
		}

		i__1 = uub;
		for (k = 1; k <= i__1; ++k) {
		    for (jc = *n - 1; jc >= 1; --jc) {
/* Computing MIN */
			i__4 = *n + 1 - jc, i__2 = k + 2;
			il = f2cmin(i__4,i__2);
			extra.r = 0.f, extra.i = 0.f;
			i__4 = (1 - iskew) * jc + 1 + ioffg + jc * a_dim1;
			ctemp.r = a[i__4].r, ctemp.i = a[i__4].i;
			angle = slarnd_(&c__1, &iseed[1]) * 
				6.2831853071795864769252867663f;
			r__1 = cos(angle);
			//clarnd_(&q__2, &c__5, &iseed[1]);
			q__2=clarnd_(&c__5, &iseed[1]);
			q__1.r = r__1 * q__2.r, q__1.i = r__1 * q__2.i;
			c__.r = q__1.r, c__.i = q__1.i;
			r__1 = sin(angle);
			//clarnd_(&q__2, &c__5, &iseed[1]);
			q__2=clarnd_(&c__5, &iseed[1]);
			q__1.r = r__1 * q__2.r, q__1.i = r__1 * q__2.i;
			s.r = q__1.r, s.i = q__1.i;
			if (csym) {
			    ct.r = c__.r, ct.i = c__.i;
			    st.r = s.r, st.i = s.i;
			} else {
			    r_cnjg(&q__1, &ctemp);
			    ctemp.r = q__1.r, ctemp.i = q__1.i;
			    r_cnjg(&q__1, &c__);
			    ct.r = q__1.r, ct.i = q__1.i;
			    r_cnjg(&q__1, &s);
			    st.r = q__1.r, st.i = q__1.i;
			}
			L__1 = *n - jc > k;
			clarot_(&c_false, &c_true, &L__1, &il, &c__, &s, &a[(
				1 - iskew) * jc + ioffg + jc * a_dim1], &ilda,
				 &ctemp, &extra);
/* Computing MAX */
			i__4 = 1, i__2 = jc - k + 1;
			icol = f2cmax(i__4,i__2);
			i__4 = jc + 2 - icol;
			clarot_(&c_true, &c_false, &c_true, &i__4, &ct, &st, &
				a[jc - iskew * icol + ioffg + icol * a_dim1], 
				&ilda, &dummy, &ctemp);

/*                    Chase EXTRA back down the matrix */

			icol = jc;
			i__4 = *n - 1;
			i__2 = k;
			for (jch = jc + k; i__2 < 0 ? jch >= i__4 : jch <= 
				i__4; jch += i__2) {
			    clartg_(&a[jch - iskew * icol + ioffg + icol * 
				    a_dim1], &extra, &realc, &s, &dummy);
			    //clarnd_(&q__1, &c__5, &iseed[1]);
			    q__1=clarnd_(&c__5, &iseed[1]);
			    dummy.r = q__1.r, dummy.i = q__1.i;
			    q__1.r = realc * dummy.r, q__1.i = realc * 
				    dummy.i;
			    c__.r = q__1.r, c__.i = q__1.i;
			    q__1.r = s.r * dummy.r - s.i * dummy.i, q__1.i = 
				    s.r * dummy.i + s.i * dummy.r;
			    s.r = q__1.r, s.i = q__1.i;
			    i__3 = (1 - iskew) * jch + 1 + ioffg + jch * 
				    a_dim1;
			    ctemp.r = a[i__3].r, ctemp.i = a[i__3].i;
			    if (csym) {
				ct.r = c__.r, ct.i = c__.i;
				st.r = s.r, st.i = s.i;
			    } else {
				r_cnjg(&q__1, &ctemp);
				ctemp.r = q__1.r, ctemp.i = q__1.i;
				r_cnjg(&q__1, &c__);
				ct.r = q__1.r, ct.i = q__1.i;
				r_cnjg(&q__1, &s);
				st.r = q__1.r, st.i = q__1.i;
			    }
			    i__3 = k + 2;
			    clarot_(&c_true, &c_true, &c_true, &i__3, &c__, &
				    s, &a[jch - iskew * icol + ioffg + icol * 
				    a_dim1], &ilda, &extra, &ctemp);
/* Computing MIN */
			    i__3 = *n + 1 - jch, i__5 = k + 2;
			    il = f2cmin(i__3,i__5);
			    extra.r = 0.f, extra.i = 0.f;
			    L__1 = *n - jch > k;
			    clarot_(&c_false, &c_true, &L__1, &il, &ct, &st, &
				    a[(1 - iskew) * jch + ioffg + jch * 
				    a_dim1], &ilda, &ctemp, &extra);
			    icol = jch;
/* L360: */
			}
/* L370: */
		    }
/* L380: */
		}

/*              If we need upper triangle, copy from lower. Note that */
/*              the order of copying is chosen to work for 'b' -> 'q' */

		if (ipack != ipackg && ipack != 4) {
		    for (jc = *n; jc >= 1; --jc) {
			irow = ioffst - iskew * jc;
			if (csym) {
/* Computing MAX */
			    i__2 = 1, i__4 = jc - uub;
			    i__1 = f2cmax(i__2,i__4);
			    for (jr = jc; jr >= i__1; --jr) {
				i__2 = jr + irow + jc * a_dim1;
				i__4 = jc - iskew * jr + ioffg + jr * a_dim1;
				a[i__2].r = a[i__4].r, a[i__2].i = a[i__4].i;
/* L390: */
			    }
			} else {
/* Computing MAX */
			    i__2 = 1, i__4 = jc - uub;
			    i__1 = f2cmax(i__2,i__4);
			    for (jr = jc; jr >= i__1; --jr) {
				i__2 = jr + irow + jc * a_dim1;
				r_cnjg(&q__1, &a[jc - iskew * jr + ioffg + jr 
					* a_dim1]);
				a[i__2].r = q__1.r, a[i__2].i = q__1.i;
/* L400: */
			    }
			}
/* L410: */
		    }
		    if (ipack == 6) {
			i__1 = uub;
			for (jc = 1; jc <= i__1; ++jc) {
			    i__2 = uub + 1 - jc;
			    for (jr = 1; jr <= i__2; ++jr) {
				i__4 = jr + jc * a_dim1;
				a[i__4].r = 0.f, a[i__4].i = 0.f;
/* L420: */
			    }
/* L430: */
			}
		    }
		    if (ipackg == 5) {
			ipackg = ipack;
		    } else {
			ipackg = 0;
		    }
		}
	    }

/*           Ensure that the diagonal is real if Hermitian */

	    if (! csym) {
		i__1 = *n;
		for (jc = 1; jc <= i__1; ++jc) {
		    irow = ioffst + (1 - iskew) * jc;
		    i__2 = irow + jc * a_dim1;
		    i__4 = irow + jc * a_dim1;
		    r__1 = a[i__4].r;
		    q__1.r = r__1, q__1.i = 0.f;
		    a[i__2].r = q__1.r, a[i__2].i = q__1.i;
/* L440: */
		}
	    }

	}

    } else {

/*        4)      Generate Banded Matrix by first */
/*                Rotating by random Unitary matrices, */
/*                then reducing the bandwidth using Householder */
/*                transformations. */

/*                Note: we should get here only if LDA .ge. N */

	if (isym == 1) {

/*           Non-symmetric -- A = U D V */

	    clagge_(&mr, &nc, &llb, &uub, &d__[1], &a[a_offset], lda, &iseed[
		    1], &work[1], &iinfo);
	} else {

/*           Symmetric -- A = U D U' or */
/*           Hermitian -- A = U D U* */

	    if (csym) {
		clagsy_(m, &llb, &d__[1], &a[a_offset], lda, &iseed[1], &work[
			1], &iinfo);
	    } else {
		claghe_(m, &llb, &d__[1], &a[a_offset], lda, &iseed[1], &work[
			1], &iinfo);
	    }
	}

	if (iinfo != 0) {
	    *info = 3;
	    return 0;
	}
    }

/*     5)      Pack the matrix */

    if (ipack != ipackg) {
	if (ipack == 1) {

/*           'U' -- Upper triangular, not packed */

	    i__1 = *m;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = *m;
		for (i__ = j + 1; i__ <= i__2; ++i__) {
		    i__4 = i__ + j * a_dim1;
		    a[i__4].r = 0.f, a[i__4].i = 0.f;
/* L450: */
		}
/* L460: */
	    }

	} else if (ipack == 2) {

/*           'L' -- Lower triangular, not packed */

	    i__1 = *m;
	    for (j = 2; j <= i__1; ++j) {
		i__2 = j - 1;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    i__4 = i__ + j * a_dim1;
		    a[i__4].r = 0.f, a[i__4].i = 0.f;
/* L470: */
		}
/* L480: */
	    }

	} else if (ipack == 3) {

/*           'C' -- Upper triangle packed Columnwise. */

	    icol = 1;
	    irow = 0;
	    i__1 = *m;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = j;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    ++irow;
		    if (irow > *lda) {
			irow = 1;
			++icol;
		    }
		    i__4 = irow + icol * a_dim1;
		    i__3 = i__ + j * a_dim1;
		    a[i__4].r = a[i__3].r, a[i__4].i = a[i__3].i;
/* L490: */
		}
/* L500: */
	    }

	} else if (ipack == 4) {

/*           'R' -- Lower triangle packed Columnwise. */

	    icol = 1;
	    irow = 0;
	    i__1 = *m;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = *m;
		for (i__ = j; i__ <= i__2; ++i__) {
		    ++irow;
		    if (irow > *lda) {
			irow = 1;
			++icol;
		    }
		    i__4 = irow + icol * a_dim1;
		    i__3 = i__ + j * a_dim1;
		    a[i__4].r = a[i__3].r, a[i__4].i = a[i__3].i;
/* L510: */
		}
/* L520: */
	    }

	} else if (ipack >= 5) {

/*           'B' -- The lower triangle is packed as a band matrix. */
/*           'Q' -- The upper triangle is packed as a band matrix. */
/*           'Z' -- The whole matrix is packed as a band matrix. */

	    if (ipack == 5) {
		uub = 0;
	    }
	    if (ipack == 6) {
		llb = 0;
	    }

	    i__1 = uub;
	    for (j = 1; j <= i__1; ++j) {
/* Computing MIN */
		i__2 = j + llb;
		for (i__ = f2cmin(i__2,*m); i__ >= 1; --i__) {
		    i__2 = i__ - j + uub + 1 + j * a_dim1;
		    i__4 = i__ + j * a_dim1;
		    a[i__2].r = a[i__4].r, a[i__2].i = a[i__4].i;
/* L530: */
		}
/* L540: */
	    }

	    i__1 = *n;
	    for (j = uub + 2; j <= i__1; ++j) {
/* Computing MIN */
		i__4 = j + llb;
		i__2 = f2cmin(i__4,*m);
		for (i__ = j - uub; i__ <= i__2; ++i__) {
		    i__4 = i__ - j + uub + 1 + j * a_dim1;
		    i__3 = i__ + j * a_dim1;
		    a[i__4].r = a[i__3].r, a[i__4].i = a[i__3].i;
/* L550: */
		}
/* L560: */
	    }
	}

/*        If packed, zero out extraneous elements. */

/*        Symmetric/Triangular Packed -- */
/*        zero out everything after A(IROW,ICOL) */

	if (ipack == 3 || ipack == 4) {
	    i__1 = *m;
	    for (jc = icol; jc <= i__1; ++jc) {
		i__2 = *lda;
		for (jr = irow + 1; jr <= i__2; ++jr) {
		    i__4 = jr + jc * a_dim1;
		    a[i__4].r = 0.f, a[i__4].i = 0.f;
/* L570: */
		}
		irow = 0;
/* L580: */
	    }

	} else if (ipack >= 5) {

/*           Packed Band -- */
/*              1st row is now in A( UUB+2-j, j), zero above it */
/*              m-th row is now in A( M+UUB-j,j), zero below it */
/*              last non-zero diagonal is now in A( UUB+LLB+1,j ), */
/*                 zero below it, too. */

	    ir1 = uub + llb + 2;
	    ir2 = uub + *m + 2;
	    i__1 = *n;
	    for (jc = 1; jc <= i__1; ++jc) {
		i__2 = uub + 1 - jc;
		for (jr = 1; jr <= i__2; ++jr) {
		    i__4 = jr + jc * a_dim1;
		    a[i__4].r = 0.f, a[i__4].i = 0.f;
/* L590: */
		}
/* Computing MAX */
/* Computing MIN */
		i__3 = ir1, i__5 = ir2 - jc;
		i__2 = 1, i__4 = f2cmin(i__3,i__5);
		i__6 = *lda;
		for (jr = f2cmax(i__2,i__4); jr <= i__6; ++jr) {
		    i__2 = jr + jc * a_dim1;
		    a[i__2].r = 0.f, a[i__2].i = 0.f;
/* L600: */
		}
/* L610: */
	    }
	}
    }

    return 0;

/*     End of CLATMT */

} /* clatmt_ */

