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

static complex c_b1 = {1.f,0.f};
static integer c__1 = 1;

/* > \brief \b CLARFB_GETT */

/*  =========== DOCUMENTATION =========== */

/* Online html documentation available at */
/*            http://www.netlib.org/lapack/explore-html/ */

/* > \htmlonly */
/* > Download CLARFB_GETT + dependencies */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/clarfb_
gett.f"> */
/* > [TGZ]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/clarfb_
gett.f"> */
/* > [ZIP]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/clarfb_
gett.f"> */
/* > [TXT]</a> */
/* > \endhtmlonly */
/* > */
/*  Definition: */
/*  =========== */

/*       SUBROUTINE CLARFB_GETT( IDENT, M, N, K, T, LDT, A, LDA, B, LDB, */
/*      $                        WORK, LDWORK ) */
/*       IMPLICIT NONE */

/*       CHARACTER          IDENT */
/*       INTEGER            K, LDA, LDB, LDT, LDWORK, M, N */
/*       COMPLEX            A( LDA, * ), B( LDB, * ), T( LDT, * ), */
/*      $                   WORK( LDWORK, * ) */

/* > \par Purpose: */
/*  ============= */
/* > */
/* > \verbatim */
/* > */
/* > CLARFB_GETT applies a complex Householder block reflector H from the */
/* > left to a complex (K+M)-by-N  "triangular-pentagonal" matrix */
/* > composed of two block matrices: an upper trapezoidal K-by-N matrix A */
/* > stored in the array A, and a rectangular M-by-(N-K) matrix B, stored */
/* > in the array B. The block reflector H is stored in a compact */
/* > WY-representation, where the elementary reflectors are in the */
/* > arrays A, B and T. See Further Details section. */
/* > \endverbatim */

/*  Arguments: */
/*  ========== */

/* > \param[in] IDENT */
/* > \verbatim */
/* >          IDENT is CHARACTER*1 */
/* >          If IDENT = not 'I', or not 'i', then V1 is unit */
/* >             lower-triangular and stored in the left K-by-K block of */
/* >             the input matrix A, */
/* >          If IDENT = 'I' or 'i', then  V1 is an identity matrix and */
/* >             not stored. */
/* >          See Further Details section. */
/* > \endverbatim */
/* > */
/* > \param[in] M */
/* > \verbatim */
/* >          M is INTEGER */
/* >          The number of rows of the matrix B. */
/* >          M >= 0. */
/* > \endverbatim */
/* > */
/* > \param[in] N */
/* > \verbatim */
/* >          N is INTEGER */
/* >          The number of columns of the matrices A and B. */
/* >          N >= 0. */
/* > \endverbatim */
/* > */
/* > \param[in] K */
/* > \verbatim */
/* >          K is INTEGER */
/* >          The number or rows of the matrix A. */
/* >          K is also order of the matrix T, i.e. the number of */
/* >          elementary reflectors whose product defines the block */
/* >          reflector. 0 <= K <= N. */
/* > \endverbatim */
/* > */
/* > \param[in] T */
/* > \verbatim */
/* >          T is COMPLEX array, dimension (LDT,K) */
/* >          The upper-triangular K-by-K matrix T in the representation */
/* >          of the block reflector. */
/* > \endverbatim */
/* > */
/* > \param[in] LDT */
/* > \verbatim */
/* >          LDT is INTEGER */
/* >          The leading dimension of the array T. LDT >= K. */
/* > \endverbatim */
/* > */
/* > \param[in,out] A */
/* > \verbatim */
/* >          A is COMPLEX array, dimension (LDA,N) */
/* > */
/* >          On entry: */
/* >           a) In the K-by-N upper-trapezoidal part A: input matrix A. */
/* >           b) In the columns below the diagonal: columns of V1 */
/* >              (ones are not stored on the diagonal). */
/* > */
/* >          On exit: */
/* >            A is overwritten by rectangular K-by-N product H*A. */
/* > */
/* >          See Further Details section. */
/* > \endverbatim */
/* > */
/* > \param[in] LDA */
/* > \verbatim */
/* >          LDB is INTEGER */
/* >          The leading dimension of the array A. LDA >= f2cmax(1,K). */
/* > \endverbatim */
/* > */
/* > \param[in,out] B */
/* > \verbatim */
/* >          B is COMPLEX array, dimension (LDB,N) */
/* > */
/* >          On entry: */
/* >            a) In the M-by-(N-K) right block: input matrix B. */
/* >            b) In the M-by-N left block: columns of V2. */
/* > */
/* >          On exit: */
/* >            B is overwritten by rectangular M-by-N product H*B. */
/* > */
/* >          See Further Details section. */
/* > \endverbatim */
/* > */
/* > \param[in] LDB */
/* > \verbatim */
/* >          LDB is INTEGER */
/* >          The leading dimension of the array B. LDB >= f2cmax(1,M). */
/* > \endverbatim */
/* > */
/* > \param[out] WORK */
/* > \verbatim */
/* >          WORK is COMPLEX array, */
/* >          dimension (LDWORK,f2cmax(K,N-K)) */
/* > \endverbatim */
/* > */
/* > \param[in] LDWORK */
/* > \verbatim */
/* >          LDWORK is INTEGER */
/* >          The leading dimension of the array WORK. LDWORK>=f2cmax(1,K). */
/* > */
/* > \endverbatim */

/*  Authors: */
/*  ======== */

/* > \author Univ. of Tennessee */
/* > \author Univ. of California Berkeley */
/* > \author Univ. of Colorado Denver */
/* > \author NAG Ltd. */

/* > \ingroup complexOTHERauxiliary */

/* > \par Contributors: */
/*  ================== */
/* > */
/* > \verbatim */
/* > */
/* > November 2020, Igor Kozachenko, */
/* >                Computer Science Division, */
/* >                University of California, Berkeley */
/* > */
/* > \endverbatim */

/* > \par Further Details: */
/*  ===================== */
/* > */
/* > \verbatim */
/* > */
/* >    (1) Description of the Algebraic Operation. */
/* > */
/* >    The matrix A is a K-by-N matrix composed of two column block */
/* >    matrices, A1, which is K-by-K, and A2, which is K-by-(N-K): */
/* >    A = ( A1, A2 ). */
/* >    The matrix B is an M-by-N matrix composed of two column block */
/* >    matrices, B1, which is M-by-K, and B2, which is M-by-(N-K): */
/* >    B = ( B1, B2 ). */
/* > */
/* >    Perform the operation: */
/* > */
/* >       ( A_out ) := H * ( A_in ) = ( I - V * T * V**H ) * ( A_in ) = */
/* >       ( B_out )        ( B_in )                          ( B_in ) */
/* >                  = ( I - ( V1 ) * T * ( V1**H, V2**H ) ) * ( A_in ) */
/* >                          ( V2 )                            ( B_in ) */
/* >     On input: */
/* > */
/* >    a) ( A_in )  consists of two block columns: */
/* >       ( B_in ) */
/* > */
/* >       ( A_in ) = (( A1_in ) ( A2_in )) = (( A1_in ) ( A2_in )) */
/* >       ( B_in )   (( B1_in ) ( B2_in ))   ((     0 ) ( B2_in )), */
/* > */
/* >       where the column blocks are: */
/* > */
/* >       (  A1_in )  is a K-by-K upper-triangular matrix stored in the */
/* >                   upper triangular part of the array A(1:K,1:K). */
/* >       (  B1_in )  is an M-by-K rectangular ZERO matrix and not stored. */
/* > */
/* >       ( A2_in )  is a K-by-(N-K) rectangular matrix stored */
/* >                  in the array A(1:K,K+1:N). */
/* >       ( B2_in )  is an M-by-(N-K) rectangular matrix stored */
/* >                  in the array B(1:M,K+1:N). */
/* > */
/* >    b) V = ( V1 ) */
/* >           ( V2 ) */
/* > */
/* >       where: */
/* >       1) if IDENT == 'I',V1 is a K-by-K identity matrix, not stored; */
/* >       2) if IDENT != 'I',V1 is a K-by-K unit lower-triangular matrix, */
/* >          stored in the lower-triangular part of the array */
/* >          A(1:K,1:K) (ones are not stored), */
/* >       and V2 is an M-by-K rectangular stored the array B(1:M,1:K), */
/* >                 (because on input B1_in is a rectangular zero */
/* >                  matrix that is not stored and the space is */
/* >                  used to store V2). */
/* > */
/* >    c) T is a K-by-K upper-triangular matrix stored */
/* >       in the array T(1:K,1:K). */
/* > */
/* >    On output: */
/* > */
/* >    a) ( A_out ) consists of two  block columns: */
/* >       ( B_out ) */
/* > */
/* >       ( A_out ) = (( A1_out ) ( A2_out )) */
/* >       ( B_out )   (( B1_out ) ( B2_out )), */
/* > */
/* >       where the column blocks are: */
/* > */
/* >       ( A1_out )  is a K-by-K square matrix, or a K-by-K */
/* >                   upper-triangular matrix, if V1 is an */
/* >                   identity matrix. AiOut is stored in */
/* >                   the array A(1:K,1:K). */
/* >       ( B1_out )  is an M-by-K rectangular matrix stored */
/* >                   in the array B(1:M,K:N). */
/* > */
/* >       ( A2_out )  is a K-by-(N-K) rectangular matrix stored */
/* >                   in the array A(1:K,K+1:N). */
/* >       ( B2_out )  is an M-by-(N-K) rectangular matrix stored */
/* >                   in the array B(1:M,K+1:N). */
/* > */
/* > */
/* >    The operation above can be represented as the same operation */
/* >    on each block column: */
/* > */
/* >       ( A1_out ) := H * ( A1_in ) = ( I - V * T * V**H ) * ( A1_in ) */
/* >       ( B1_out )        (     0 )                          (     0 ) */
/* > */
/* >       ( A2_out ) := H * ( A2_in ) = ( I - V * T * V**H ) * ( A2_in ) */
/* >       ( B2_out )        ( B2_in )                          ( B2_in ) */
/* > */
/* >    If IDENT != 'I': */
/* > */
/* >       The computation for column block 1: */
/* > */
/* >       A1_out: = A1_in - V1*T*(V1**H)*A1_in */
/* > */
/* >       B1_out: = - V2*T*(V1**H)*A1_in */
/* > */
/* >       The computation for column block 2, which exists if N > K: */
/* > */
/* >       A2_out: = A2_in - V1*T*( (V1**H)*A2_in + (V2**H)*B2_in ) */
/* > */
/* >       B2_out: = B2_in - V2*T*( (V1**H)*A2_in + (V2**H)*B2_in ) */
/* > */
/* >    If IDENT == 'I': */
/* > */
/* >       The operation for column block 1: */
/* > */
/* >       A1_out: = A1_in - V1*T*A1_in */
/* > */
/* >       B1_out: = - V2*T*A1_in */
/* > */
/* >       The computation for column block 2, which exists if N > K: */
/* > */
/* >       A2_out: = A2_in - T*( A2_in + (V2**H)*B2_in ) */
/* > */
/* >       B2_out: = B2_in - V2*T*( A2_in + (V2**H)*B2_in ) */
/* > */
/* >    (2) Description of the Algorithmic Computation. */
/* > */
/* >    In the first step, we compute column block 2, i.e. A2 and B2. */
/* >    Here, we need to use the K-by-(N-K) rectangular workspace */
/* >    matrix W2 that is of the same size as the matrix A2. */
/* >    W2 is stored in the array WORK(1:K,1:(N-K)). */
/* > */
/* >    In the second step, we compute column block 1, i.e. A1 and B1. */
/* >    Here, we need to use the K-by-K square workspace matrix W1 */
/* >    that is of the same size as the as the matrix A1. */
/* >    W1 is stored in the array WORK(1:K,1:K). */
/* > */
/* >    NOTE: Hence, in this routine, we need the workspace array WORK */
/* >    only of size WORK(1:K,1:f2cmax(K,N-K)) so it can hold both W2 from */
/* >    the first step and W1 from the second step. */
/* > */
/* >    Case (A), when V1 is unit lower-triangular, i.e. IDENT != 'I', */
/* >    more computations than in the Case (B). */
/* > */
/* >    if( IDENT != 'I' ) then */
/* >     if ( N > K ) then */
/* >       (First Step - column block 2) */
/* >       col2_(1) W2: = A2 */
/* >       col2_(2) W2: = (V1**H) * W2 = (unit_lower_tr_of_(A1)**H) * W2 */
/* >       col2_(3) W2: = W2 + (V2**H) * B2 = W2 + (B1**H) * B2 */
/* >       col2_(4) W2: = T * W2 */
/* >       col2_(5) B2: = B2 - V2 * W2 = B2 - B1 * W2 */
/* >       col2_(6) W2: = V1 * W2 = unit_lower_tr_of_(A1) * W2 */
/* >       col2_(7) A2: = A2 - W2 */
/* >     else */
/* >       (Second Step - column block 1) */
/* >       col1_(1) W1: = A1 */
/* >       col1_(2) W1: = (V1**H) * W1 = (unit_lower_tr_of_(A1)**H) * W1 */
/* >       col1_(3) W1: = T * W1 */
/* >       col1_(4) B1: = - V2 * W1 = - B1 * W1 */
/* >       col1_(5) square W1: = V1 * W1 = unit_lower_tr_of_(A1) * W1 */
/* >       col1_(6) square A1: = A1 - W1 */
/* >     end if */
/* >    end if */
/* > */
/* >    Case (B), when V1 is an identity matrix, i.e. IDENT == 'I', */
/* >    less computations than in the Case (A) */
/* > */
/* >    if( IDENT == 'I' ) then */
/* >     if ( N > K ) then */
/* >       (First Step - column block 2) */
/* >       col2_(1) W2: = A2 */
/* >       col2_(3) W2: = W2 + (V2**H) * B2 = W2 + (B1**H) * B2 */
/* >       col2_(4) W2: = T * W2 */
/* >       col2_(5) B2: = B2 - V2 * W2 = B2 - B1 * W2 */
/* >       col2_(7) A2: = A2 - W2 */
/* >     else */
/* >       (Second Step - column block 1) */
/* >       col1_(1) W1: = A1 */
/* >       col1_(3) W1: = T * W1 */
/* >       col1_(4) B1: = - V2 * W1 = - B1 * W1 */
/* >       col1_(6) upper-triangular_of_(A1): = A1 - W1 */
/* >     end if */
/* >    end if */
/* > */
/* >    Combine these cases (A) and (B) together, this is the resulting */
/* >    algorithm: */
/* > */
/* >    if ( N > K ) then */
/* > */
/* >      (First Step - column block 2) */
/* > */
/* >      col2_(1)  W2: = A2 */
/* >      if( IDENT != 'I' ) then */
/* >        col2_(2)  W2: = (V1**H) * W2 */
/* >                      = (unit_lower_tr_of_(A1)**H) * W2 */
/* >      end if */
/* >      col2_(3)  W2: = W2 + (V2**H) * B2 = W2 + (B1**H) * B2] */
/* >      col2_(4)  W2: = T * W2 */
/* >      col2_(5)  B2: = B2 - V2 * W2 = B2 - B1 * W2 */
/* >      if( IDENT != 'I' ) then */
/* >        col2_(6)    W2: = V1 * W2 = unit_lower_tr_of_(A1) * W2 */
/* >      end if */
/* >      col2_(7) A2: = A2 - W2 */
/* > */
/* >    else */
/* > */
/* >    (Second Step - column block 1) */
/* > */
/* >      col1_(1) W1: = A1 */
/* >      if( IDENT != 'I' ) then */
/* >        col1_(2) W1: = (V1**H) * W1 */
/* >                    = (unit_lower_tr_of_(A1)**H) * W1 */
/* >      end if */
/* >      col1_(3) W1: = T * W1 */
/* >      col1_(4) B1: = - V2 * W1 = - B1 * W1 */
/* >      if( IDENT != 'I' ) then */
/* >        col1_(5) square W1: = V1 * W1 = unit_lower_tr_of_(A1) * W1 */
/* >        col1_(6_a) below_diag_of_(A1): =  - below_diag_of_(W1) */
/* >      end if */
/* >      col1_(6_b) up_tr_of_(A1): = up_tr_of_(A1) - up_tr_of_(W1) */
/* > */
/* >    end if */
/* > */
/* > \endverbatim */
/* > */
/*  ===================================================================== */
/* Subroutine */ int clarfb_gett_(char *ident, integer *m, integer *n, 
	integer *k, complex *t, integer *ldt, complex *a, integer *lda, 
	complex *b, integer *ldb, complex *work, integer *ldwork)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, t_dim1, t_offset, work_dim1, 
	    work_offset, i__1, i__2, i__3, i__4, i__5;
    complex q__1;

    /* Local variables */
    integer i__, j;
    extern /* Subroutine */ int cgemm_(char *, char *, integer *, integer *, 
	    integer *, complex *, complex *, integer *, complex *, integer *, 
	    complex *, complex *, integer *);
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int ccopy_(integer *, complex *, integer *, 
	    complex *, integer *), ctrmm_(char *, char *, char *, char *, 
	    integer *, integer *, complex *, complex *, integer *, complex *, 
	    integer *);
    logical lnotident;


/*  -- LAPACK auxiliary routine -- */
/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */


/*  ===================================================================== */


/*     Quick return if possible */

    /* Parameter adjustments */
    t_dim1 = *ldt;
    t_offset = 1 + t_dim1 * 1;
    t -= t_offset;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1 * 1;
    b -= b_offset;
    work_dim1 = *ldwork;
    work_offset = 1 + work_dim1 * 1;
    work -= work_offset;

    /* Function Body */
    if (*m < 0 || *n <= 0 || *k == 0 || *k > *n) {
	return 0;
    }

    lnotident = ! lsame_(ident, "I");

/*     ------------------------------------------------------------------ */

/*     First Step. Computation of the Column Block 2: */

/*        ( A2 ) := H * ( A2 ) */
/*        ( B2 )        ( B2 ) */

/*     ------------------------------------------------------------------ */

    if (*n > *k) {

/*        col2_(1) Compute W2: = A2. Therefore, copy A2 = A(1:K, K+1:N) */
/*        into W2=WORK(1:K, 1:N-K) column-by-column. */

	i__1 = *n - *k;
	for (j = 1; j <= i__1; ++j) {
	    ccopy_(k, &a[(*k + j) * a_dim1 + 1], &c__1, &work[j * work_dim1 + 
		    1], &c__1);
	}
	if (lnotident) {

/*           col2_(2) Compute W2: = (V1**H) * W2 = (A1**H) * W2, */
/*           V1 is not an identy matrix, but unit lower-triangular */
/*           V1 stored in A1 (diagonal ones are not stored). */


	    i__1 = *n - *k;
	    ctrmm_("L", "L", "C", "U", k, &i__1, &c_b1, &a[a_offset], lda, &
		    work[work_offset], ldwork);
	}

/*        col2_(3) Compute W2: = W2 + (V2**H) * B2 = W2 + (B1**H) * B2 */
/*        V2 stored in B1. */

	if (*m > 0) {
	    i__1 = *n - *k;
	    cgemm_("C", "N", k, &i__1, m, &c_b1, &b[b_offset], ldb, &b[(*k + 
		    1) * b_dim1 + 1], ldb, &c_b1, &work[work_offset], ldwork);
	}

/*        col2_(4) Compute W2: = T * W2, */
/*        T is upper-triangular. */

	i__1 = *n - *k;
	ctrmm_("L", "U", "N", "N", k, &i__1, &c_b1, &t[t_offset], ldt, &work[
		work_offset], ldwork);

/*        col2_(5) Compute B2: = B2 - V2 * W2 = B2 - B1 * W2, */
/*        V2 stored in B1. */

	if (*m > 0) {
	    i__1 = *n - *k;
	    q__1.r = -1.f, q__1.i = 0.f;
	    cgemm_("N", "N", m, &i__1, k, &q__1, &b[b_offset], ldb, &work[
		    work_offset], ldwork, &c_b1, &b[(*k + 1) * b_dim1 + 1], 
		    ldb);
	}

	if (lnotident) {

/*           col2_(6) Compute W2: = V1 * W2 = A1 * W2, */
/*           V1 is not an identity matrix, but unit lower-triangular, */
/*           V1 stored in A1 (diagonal ones are not stored). */

	    i__1 = *n - *k;
	    ctrmm_("L", "L", "N", "U", k, &i__1, &c_b1, &a[a_offset], lda, &
		    work[work_offset], ldwork);
	}

/*        col2_(7) Compute A2: = A2 - W2 = */
/*                             = A(1:K, K+1:N-K) - WORK(1:K, 1:N-K), */
/*        column-by-column. */

	i__1 = *n - *k;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *k;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		i__3 = i__ + (*k + j) * a_dim1;
		i__4 = i__ + (*k + j) * a_dim1;
		i__5 = i__ + j * work_dim1;
		q__1.r = a[i__4].r - work[i__5].r, q__1.i = a[i__4].i - work[
			i__5].i;
		a[i__3].r = q__1.r, a[i__3].i = q__1.i;
	    }
	}

    }

/*     ------------------------------------------------------------------ */

/*     Second Step. Computation of the Column Block 1: */

/*        ( A1 ) := H * ( A1 ) */
/*        ( B1 )        (  0 ) */

/*     ------------------------------------------------------------------ */

/*     col1_(1) Compute W1: = A1. Copy the upper-triangular */
/*     A1 = A(1:K, 1:K) into the upper-triangular */
/*     W1 = WORK(1:K, 1:K) column-by-column. */

    i__1 = *k;
    for (j = 1; j <= i__1; ++j) {
	ccopy_(&j, &a[j * a_dim1 + 1], &c__1, &work[j * work_dim1 + 1], &c__1)
		;
    }

/*     Set the subdiagonal elements of W1 to zero column-by-column. */

    i__1 = *k - 1;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *k;
	for (i__ = j + 1; i__ <= i__2; ++i__) {
	    i__3 = i__ + j * work_dim1;
	    work[i__3].r = 0.f, work[i__3].i = 0.f;
	}
    }

    if (lnotident) {

/*        col1_(2) Compute W1: = (V1**H) * W1 = (A1**H) * W1, */
/*        V1 is not an identity matrix, but unit lower-triangular */
/*        V1 stored in A1 (diagonal ones are not stored), */
/*        W1 is upper-triangular with zeroes below the diagonal. */

	ctrmm_("L", "L", "C", "U", k, k, &c_b1, &a[a_offset], lda, &work[
		work_offset], ldwork);
    }

/*     col1_(3) Compute W1: = T * W1, */
/*     T is upper-triangular, */
/*     W1 is upper-triangular with zeroes below the diagonal. */

    ctrmm_("L", "U", "N", "N", k, k, &c_b1, &t[t_offset], ldt, &work[
	    work_offset], ldwork);

/*     col1_(4) Compute B1: = - V2 * W1 = - B1 * W1, */
/*     V2 = B1, W1 is upper-triangular with zeroes below the diagonal. */

    if (*m > 0) {
	q__1.r = -1.f, q__1.i = 0.f;
	ctrmm_("R", "U", "N", "N", m, k, &q__1, &work[work_offset], ldwork, &
		b[b_offset], ldb);
    }

    if (lnotident) {

/*        col1_(5) Compute W1: = V1 * W1 = A1 * W1, */
/*        V1 is not an identity matrix, but unit lower-triangular */
/*        V1 stored in A1 (diagonal ones are not stored), */
/*        W1 is upper-triangular on input with zeroes below the diagonal, */
/*        and square on output. */

	ctrmm_("L", "L", "N", "U", k, k, &c_b1, &a[a_offset], lda, &work[
		work_offset], ldwork);

/*        col1_(6) Compute A1: = A1 - W1 = A(1:K, 1:K) - WORK(1:K, 1:K) */
/*        column-by-column. A1 is upper-triangular on input. */
/*        If IDENT, A1 is square on output, and W1 is square, */
/*        if NOT IDENT, A1 is upper-triangular on output, */
/*        W1 is upper-triangular. */

/*        col1_(6)_a Compute elements of A1 below the diagonal. */

	i__1 = *k - 1;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *k;
	    for (i__ = j + 1; i__ <= i__2; ++i__) {
		i__3 = i__ + j * a_dim1;
		i__4 = i__ + j * work_dim1;
		q__1.r = -work[i__4].r, q__1.i = -work[i__4].i;
		a[i__3].r = q__1.r, a[i__3].i = q__1.i;
	    }
	}

    }

/*     col1_(6)_b Compute elements of A1 on and above the diagonal. */

    i__1 = *k;
    for (j = 1; j <= i__1; ++j) {
	i__2 = j;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = i__ + j * a_dim1;
	    i__4 = i__ + j * a_dim1;
	    i__5 = i__ + j * work_dim1;
	    q__1.r = a[i__4].r - work[i__5].r, q__1.i = a[i__4].i - work[i__5]
		    .i;
	    a[i__3].r = q__1.r, a[i__3].i = q__1.i;
	}
    }

    return 0;

/*     End of CLARFB_GETT */

} /* clarfb_gett__ */

