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

static doublecomplex c_b1 = {0.,0.};
static doublecomplex c_b2 = {1.,0.};
static integer c__1 = 1;
static integer c__12 = 12;
static integer c__2 = 2;
static integer c__49 = 49;

/* > \brief \b ZHSEQR */

/*  =========== DOCUMENTATION =========== */

/* Online html documentation available at */
/*            http://www.netlib.org/lapack/explore-html/ */

/* > \htmlonly */
/* > Download ZHSEQR + dependencies */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/zhseqr.
f"> */
/* > [TGZ]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/zhseqr.
f"> */
/* > [ZIP]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/zhseqr.
f"> */
/* > [TXT]</a> */
/* > \endhtmlonly */

/*  Definition: */
/*  =========== */

/*       SUBROUTINE ZHSEQR( JOB, COMPZ, N, ILO, IHI, H, LDH, W, Z, LDZ, */
/*                          WORK, LWORK, INFO ) */

/*       INTEGER            IHI, ILO, INFO, LDH, LDZ, LWORK, N */
/*       CHARACTER          COMPZ, JOB */
/*       COMPLEX*16         H( LDH, * ), W( * ), WORK( * ), Z( LDZ, * ) */


/* > \par Purpose: */
/*  ============= */
/* > */
/* > \verbatim */
/* > */
/* >    ZHSEQR computes the eigenvalues of a Hessenberg matrix H */
/* >    and, optionally, the matrices T and Z from the Schur decomposition */
/* >    H = Z T Z**H, where T is an upper triangular matrix (the */
/* >    Schur form), and Z is the unitary matrix of Schur vectors. */
/* > */
/* >    Optionally Z may be postmultiplied into an input unitary */
/* >    matrix Q so that this routine can give the Schur factorization */
/* >    of a matrix A which has been reduced to the Hessenberg form H */
/* >    by the unitary matrix Q:  A = Q*H*Q**H = (QZ)*T*(QZ)**H. */
/* > \endverbatim */

/*  Arguments: */
/*  ========== */

/* > \param[in] JOB */
/* > \verbatim */
/* >          JOB is CHARACTER*1 */
/* >           = 'E':  compute eigenvalues only; */
/* >           = 'S':  compute eigenvalues and the Schur form T. */
/* > \endverbatim */
/* > */
/* > \param[in] COMPZ */
/* > \verbatim */
/* >          COMPZ is CHARACTER*1 */
/* >           = 'N':  no Schur vectors are computed; */
/* >           = 'I':  Z is initialized to the unit matrix and the matrix Z */
/* >                   of Schur vectors of H is returned; */
/* >           = 'V':  Z must contain an unitary matrix Q on entry, and */
/* >                   the product Q*Z is returned. */
/* > \endverbatim */
/* > */
/* > \param[in] N */
/* > \verbatim */
/* >          N is INTEGER */
/* >           The order of the matrix H.  N >= 0. */
/* > \endverbatim */
/* > */
/* > \param[in] ILO */
/* > \verbatim */
/* >          ILO is INTEGER */
/* > \endverbatim */
/* > */
/* > \param[in] IHI */
/* > \verbatim */
/* >          IHI is INTEGER */
/* > */
/* >           It is assumed that H is already upper triangular in rows */
/* >           and columns 1:ILO-1 and IHI+1:N. ILO and IHI are normally */
/* >           set by a previous call to ZGEBAL, and then passed to ZGEHRD */
/* >           when the matrix output by ZGEBAL is reduced to Hessenberg */
/* >           form. Otherwise ILO and IHI should be set to 1 and N */
/* >           respectively.  If N > 0, then 1 <= ILO <= IHI <= N. */
/* >           If N = 0, then ILO = 1 and IHI = 0. */
/* > \endverbatim */
/* > */
/* > \param[in,out] H */
/* > \verbatim */
/* >          H is COMPLEX*16 array, dimension (LDH,N) */
/* >           On entry, the upper Hessenberg matrix H. */
/* >           On exit, if INFO = 0 and JOB = 'S', H contains the upper */
/* >           triangular matrix T from the Schur decomposition (the */
/* >           Schur form). If INFO = 0 and JOB = 'E', the contents of */
/* >           H are unspecified on exit.  (The output value of H when */
/* >           INFO > 0 is given under the description of INFO below.) */
/* > */
/* >           Unlike earlier versions of ZHSEQR, this subroutine may */
/* >           explicitly H(i,j) = 0 for i > j and j = 1, 2, ... ILO-1 */
/* >           or j = IHI+1, IHI+2, ... N. */
/* > \endverbatim */
/* > */
/* > \param[in] LDH */
/* > \verbatim */
/* >          LDH is INTEGER */
/* >           The leading dimension of the array H. LDH >= f2cmax(1,N). */
/* > \endverbatim */
/* > */
/* > \param[out] W */
/* > \verbatim */
/* >          W is COMPLEX*16 array, dimension (N) */
/* >           The computed eigenvalues. If JOB = 'S', the eigenvalues are */
/* >           stored in the same order as on the diagonal of the Schur */
/* >           form returned in H, with W(i) = H(i,i). */
/* > \endverbatim */
/* > */
/* > \param[in,out] Z */
/* > \verbatim */
/* >          Z is COMPLEX*16 array, dimension (LDZ,N) */
/* >           If COMPZ = 'N', Z is not referenced. */
/* >           If COMPZ = 'I', on entry Z need not be set and on exit, */
/* >           if INFO = 0, Z contains the unitary matrix Z of the Schur */
/* >           vectors of H.  If COMPZ = 'V', on entry Z must contain an */
/* >           N-by-N matrix Q, which is assumed to be equal to the unit */
/* >           matrix except for the submatrix Z(ILO:IHI,ILO:IHI). On exit, */
/* >           if INFO = 0, Z contains Q*Z. */
/* >           Normally Q is the unitary matrix generated by ZUNGHR */
/* >           after the call to ZGEHRD which formed the Hessenberg matrix */
/* >           H. (The output value of Z when INFO > 0 is given under */
/* >           the description of INFO below.) */
/* > \endverbatim */
/* > */
/* > \param[in] LDZ */
/* > \verbatim */
/* >          LDZ is INTEGER */
/* >           The leading dimension of the array Z.  if COMPZ = 'I' or */
/* >           COMPZ = 'V', then LDZ >= MAX(1,N).  Otherwise, LDZ >= 1. */
/* > \endverbatim */
/* > */
/* > \param[out] WORK */
/* > \verbatim */
/* >          WORK is COMPLEX*16 array, dimension (LWORK) */
/* >           On exit, if INFO = 0, WORK(1) returns an estimate of */
/* >           the optimal value for LWORK. */
/* > \endverbatim */
/* > */
/* > \param[in] LWORK */
/* > \verbatim */
/* >          LWORK is INTEGER */
/* >           The dimension of the array WORK.  LWORK >= f2cmax(1,N) */
/* >           is sufficient and delivers very good and sometimes */
/* >           optimal performance.  However, LWORK as large as 11*N */
/* >           may be required for optimal performance.  A workspace */
/* >           query is recommended to determine the optimal workspace */
/* >           size. */
/* > */
/* >           If LWORK = -1, then ZHSEQR does a workspace query. */
/* >           In this case, ZHSEQR checks the input parameters and */
/* >           estimates the optimal workspace size for the given */
/* >           values of N, ILO and IHI.  The estimate is returned */
/* >           in WORK(1).  No error message related to LWORK is */
/* >           issued by XERBLA.  Neither H nor Z are accessed. */
/* > \endverbatim */
/* > */
/* > \param[out] INFO */
/* > \verbatim */
/* >          INFO is INTEGER */
/* >             = 0:  successful exit */
/* >             < 0:  if INFO = -i, the i-th argument had an illegal */
/* >                    value */
/* >             > 0:  if INFO = i, ZHSEQR failed to compute all of */
/* >                the eigenvalues.  Elements 1:ilo-1 and i+1:n of W */
/* >                contain those eigenvalues which have been */
/* >                successfully computed.  (Failures are rare.) */
/* > */
/* >                If INFO > 0 and JOB = 'E', then on exit, the */
/* >                remaining unconverged eigenvalues are the eigen- */
/* >                values of the upper Hessenberg matrix rows and */
/* >                columns ILO through INFO of the final, output */
/* >                value of H. */
/* > */
/* >                If INFO > 0 and JOB   = 'S', then on exit */
/* > */
/* >           (*)  (initial value of H)*U  = U*(final value of H) */
/* > */
/* >                where U is a unitary matrix.  The final */
/* >                value of  H is upper Hessenberg and triangular in */
/* >                rows and columns INFO+1 through IHI. */
/* > */
/* >                If INFO > 0 and COMPZ = 'V', then on exit */
/* > */
/* >                  (final value of Z)  =  (initial value of Z)*U */
/* > */
/* >                where U is the unitary matrix in (*) (regard- */
/* >                less of the value of JOB.) */
/* > */
/* >                If INFO > 0 and COMPZ = 'I', then on exit */
/* >                      (final value of Z)  = U */
/* >                where U is the unitary matrix in (*) (regard- */
/* >                less of the value of JOB.) */
/* > */
/* >                If INFO > 0 and COMPZ = 'N', then Z is not */
/* >                accessed. */
/* > \endverbatim */

/*  Authors: */
/*  ======== */

/* > \author Univ. of Tennessee */
/* > \author Univ. of California Berkeley */
/* > \author Univ. of Colorado Denver */
/* > \author NAG Ltd. */

/* > \date December 2016 */

/* > \ingroup complex16OTHERcomputational */

/* > \par Contributors: */
/*  ================== */
/* > */
/* >       Karen Braman and Ralph Byers, Department of Mathematics, */
/* >       University of Kansas, USA */

/* > \par Further Details: */
/*  ===================== */
/* > */
/* > \verbatim */
/* > */
/* >             Default values supplied by */
/* >             ILAENV(ISPEC,'ZHSEQR',JOB(:1)//COMPZ(:1),N,ILO,IHI,LWORK). */
/* >             It is suggested that these defaults be adjusted in order */
/* >             to attain best performance in each particular */
/* >             computational environment. */
/* > */
/* >            ISPEC=12: The ZLAHQR vs ZLAQR0 crossover point. */
/* >                      Default: 75. (Must be at least 11.) */
/* > */
/* >            ISPEC=13: Recommended deflation window size. */
/* >                      This depends on ILO, IHI and NS.  NS is the */
/* >                      number of simultaneous shifts returned */
/* >                      by ILAENV(ISPEC=15).  (See ISPEC=15 below.) */
/* >                      The default for (IHI-ILO+1) <= 500 is NS. */
/* >                      The default for (IHI-ILO+1) >  500 is 3*NS/2. */
/* > */
/* >            ISPEC=14: Nibble crossover point. (See IPARMQ for */
/* >                      details.)  Default: 14% of deflation window */
/* >                      size. */
/* > */
/* >            ISPEC=15: Number of simultaneous shifts in a multishift */
/* >                      QR iteration. */
/* > */
/* >                      If IHI-ILO+1 is ... */
/* > */
/* >                      greater than      ...but less    ... the */
/* >                      or equal to ...      than        default is */
/* > */
/* >                           1               30          NS =   2(+) */
/* >                          30               60          NS =   4(+) */
/* >                          60              150          NS =  10(+) */
/* >                         150              590          NS =  ** */
/* >                         590             3000          NS =  64 */
/* >                        3000             6000          NS = 128 */
/* >                        6000             infinity      NS = 256 */
/* > */
/* >                  (+)  By default some or all matrices of this order */
/* >                       are passed to the implicit double shift routine */
/* >                       ZLAHQR and this parameter is ignored.  See */
/* >                       ISPEC=12 above and comments in IPARMQ for */
/* >                       details. */
/* > */
/* >                 (**)  The asterisks (**) indicate an ad-hoc */
/* >                       function of N increasing from 10 to 64. */
/* > */
/* >            ISPEC=16: Select structured matrix multiply. */
/* >                      If the number of simultaneous shifts (specified */
/* >                      by ISPEC=15) is less than 14, then the default */
/* >                      for ISPEC=16 is 0.  Otherwise the default for */
/* >                      ISPEC=16 is 2. */
/* > \endverbatim */

/* > \par References: */
/*  ================ */
/* > */
/* >       K. Braman, R. Byers and R. Mathias, The Multi-Shift QR */
/* >       Algorithm Part I: Maintaining Well Focused Shifts, and Level 3 */
/* >       Performance, SIAM Journal of Matrix Analysis, volume 23, pages */
/* >       929--947, 2002. */
/* > \n */
/* >       K. Braman, R. Byers and R. Mathias, The Multi-Shift QR */
/* >       Algorithm Part II: Aggressive Early Deflation, SIAM Journal */
/* >       of Matrix Analysis, volume 23, pages 948--973, 2002. */

/*  ===================================================================== */
/* Subroutine */ int zhseqr_(char *job, char *compz, integer *n, integer *ilo,
	 integer *ihi, doublecomplex *h__, integer *ldh, doublecomplex *w, 
	doublecomplex *z__, integer *ldz, doublecomplex *work, integer *lwork,
	 integer *info)
{
    /* System generated locals */
    address a__1[2];
    integer h_dim1, h_offset, z_dim1, z_offset, i__1, i__2, i__3[2];
    doublereal d__1, d__2, d__3;
    doublecomplex z__1;
    char ch__1[2];

    /* Local variables */
    integer kbot, nmin;
    extern logical lsame_(char *, char *);
    logical initz;
    doublecomplex workl[49];
    logical wantt, wantz;
    extern /* Subroutine */ int zcopy_(integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *), zlaqr0_(logical *, logical *, 
	    integer *, integer *, integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, integer *, doublecomplex *, integer *,
	     doublecomplex *, integer *, integer *);
    doublecomplex hl[2401]	/* was [49][49] */;
    extern /* Subroutine */ int xerbla_(char *, integer *, ftnlen);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    extern /* Subroutine */ int zlahqr_(logical *, logical *, integer *, 
	    integer *, integer *, doublecomplex *, integer *, doublecomplex *,
	     integer *, integer *, doublecomplex *, integer *, integer *), 
	    zlacpy_(char *, integer *, integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *), zlaset_(char *, integer *, 
	    integer *, doublecomplex *, doublecomplex *, doublecomplex *, 
	    integer *);
    logical lquery;


/*  -- LAPACK computational routine (version 3.7.0) -- */
/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
/*     December 2016 */


/*  ===================================================================== */


/*     ==== Matrices of order NTINY or smaller must be processed by */
/*     .    ZLAHQR because of insufficient subdiagonal scratch space. */
/*     .    (This is a hard limit.) ==== */

/*     ==== NL allocates some local workspace to help small matrices */
/*     .    through a rare ZLAHQR failure.  NL > NTINY = 15 is */
/*     .    required and NL <= NMIN = ILAENV(ISPEC=12,...) is recom- */
/*     .    mended.  (The default value of NMIN is 75.)  Using NL = 49 */
/*     .    allows up to six simultaneous shifts and a 16-by-16 */
/*     .    deflation window.  ==== */

/*     ==== Decode and check the input parameters. ==== */

    /* Parameter adjustments */
    h_dim1 = *ldh;
    h_offset = 1 + h_dim1 * 1;
    h__ -= h_offset;
    --w;
    z_dim1 = *ldz;
    z_offset = 1 + z_dim1 * 1;
    z__ -= z_offset;
    --work;

    /* Function Body */
    wantt = lsame_(job, "S");
    initz = lsame_(compz, "I");
    wantz = initz || lsame_(compz, "V");
    d__1 = (doublereal) f2cmax(1,*n);
    z__1.r = d__1, z__1.i = 0.;
    work[1].r = z__1.r, work[1].i = z__1.i;
    lquery = *lwork == -1;

    *info = 0;
    if (! lsame_(job, "E") && ! wantt) {
	*info = -1;
    } else if (! lsame_(compz, "N") && ! wantz) {
	*info = -2;
    } else if (*n < 0) {
	*info = -3;
    } else if (*ilo < 1 || *ilo > f2cmax(1,*n)) {
	*info = -4;
    } else if (*ihi < f2cmin(*ilo,*n) || *ihi > *n) {
	*info = -5;
    } else if (*ldh < f2cmax(1,*n)) {
	*info = -7;
    } else if (*ldz < 1 || wantz && *ldz < f2cmax(1,*n)) {
	*info = -10;
    } else if (*lwork < f2cmax(1,*n) && ! lquery) {
	*info = -12;
    }

    if (*info != 0) {

/*        ==== Quick return in case of invalid argument. ==== */

	i__1 = -(*info);
	xerbla_("ZHSEQR", &i__1, (ftnlen)6);
	return 0;

    } else if (*n == 0) {

/*        ==== Quick return in case N = 0; nothing to do. ==== */

	return 0;

    } else if (lquery) {

/*        ==== Quick return in case of a workspace query ==== */

	zlaqr0_(&wantt, &wantz, n, ilo, ihi, &h__[h_offset], ldh, &w[1], ilo, 
		ihi, &z__[z_offset], ldz, &work[1], lwork, info);
/*        ==== Ensure reported workspace size is backward-compatible with */
/*        .    previous LAPACK versions. ==== */
/* Computing MAX */
	d__2 = work[1].r, d__3 = (doublereal) f2cmax(1,*n);
	d__1 = f2cmax(d__2,d__3);
	z__1.r = d__1, z__1.i = 0.;
	work[1].r = z__1.r, work[1].i = z__1.i;
	return 0;

    } else {

/*        ==== copy eigenvalues isolated by ZGEBAL ==== */

	if (*ilo > 1) {
	    i__1 = *ilo - 1;
	    i__2 = *ldh + 1;
	    zcopy_(&i__1, &h__[h_offset], &i__2, &w[1], &c__1);
	}
	if (*ihi < *n) {
	    i__1 = *n - *ihi;
	    i__2 = *ldh + 1;
	    zcopy_(&i__1, &h__[*ihi + 1 + (*ihi + 1) * h_dim1], &i__2, &w[*
		    ihi + 1], &c__1);
	}

/*        ==== Initialize Z, if requested ==== */

	if (initz) {
	    zlaset_("A", n, n, &c_b1, &c_b2, &z__[z_offset], ldz);
	}

/*        ==== Quick return if possible ==== */

	if (*ilo == *ihi) {
	    i__1 = *ilo;
	    i__2 = *ilo + *ilo * h_dim1;
	    w[i__1].r = h__[i__2].r, w[i__1].i = h__[i__2].i;
	    return 0;
	}

/*        ==== ZLAHQR/ZLAQR0 crossover point ==== */

/* Writing concatenation */
	i__3[0] = 1, a__1[0] = job;
	i__3[1] = 1, a__1[1] = compz;
	s_cat(ch__1, a__1, i__3, &c__2, (ftnlen)2);
	nmin = ilaenv_(&c__12, "ZHSEQR", ch__1, n, ilo, ihi, lwork, (ftnlen)6,
		 (ftnlen)2);
	nmin = f2cmax(15,nmin);

/*        ==== ZLAQR0 for big matrices; ZLAHQR for small ones ==== */

	if (*n > nmin) {
	    zlaqr0_(&wantt, &wantz, n, ilo, ihi, &h__[h_offset], ldh, &w[1], 
		    ilo, ihi, &z__[z_offset], ldz, &work[1], lwork, info);
	} else {

/*           ==== Small matrix ==== */

	    zlahqr_(&wantt, &wantz, n, ilo, ihi, &h__[h_offset], ldh, &w[1], 
		    ilo, ihi, &z__[z_offset], ldz, info);

	    if (*info > 0) {

/*              ==== A rare ZLAHQR failure!  ZLAQR0 sometimes succeeds */
/*              .    when ZLAHQR fails. ==== */

		kbot = *info;

		if (*n >= 49) {

/*                 ==== Larger matrices have enough subdiagonal scratch */
/*                 .    space to call ZLAQR0 directly. ==== */

		    zlaqr0_(&wantt, &wantz, n, ilo, &kbot, &h__[h_offset], 
			    ldh, &w[1], ilo, ihi, &z__[z_offset], ldz, &work[
			    1], lwork, info);

		} else {

/*                 ==== Tiny matrices don't have enough subdiagonal */
/*                 .    scratch space to benefit from ZLAQR0.  Hence, */
/*                 .    tiny matrices must be copied into a larger */
/*                 .    array before calling ZLAQR0. ==== */

		    zlacpy_("A", n, n, &h__[h_offset], ldh, hl, &c__49);
		    i__1 = *n + 1 + *n * 49 - 50;
		    hl[i__1].r = 0., hl[i__1].i = 0.;
		    i__1 = 49 - *n;
		    zlaset_("A", &c__49, &i__1, &c_b1, &c_b1, &hl[(*n + 1) * 
			    49 - 49], &c__49);
		    zlaqr0_(&wantt, &wantz, &c__49, ilo, &kbot, hl, &c__49, &
			    w[1], ilo, ihi, &z__[z_offset], ldz, workl, &
			    c__49, info);
		    if (wantt || *info != 0) {
			zlacpy_("A", n, n, hl, &c__49, &h__[h_offset], ldh);
		    }
		}
	    }
	}

/*        ==== Clear out the trash, if necessary. ==== */

	if ((wantt || *info != 0) && *n > 2) {
	    i__1 = *n - 2;
	    i__2 = *n - 2;
	    zlaset_("L", &i__1, &i__2, &c_b1, &c_b1, &h__[h_dim1 + 3], ldh);
	}

/*        ==== Ensure reported workspace size is backward-compatible with */
/*        .    previous LAPACK versions. ==== */

/* Computing MAX */
	d__2 = (doublereal) f2cmax(1,*n), d__3 = work[1].r;
	d__1 = f2cmax(d__2,d__3);
	z__1.r = d__1, z__1.i = 0.;
	work[1].r = z__1.r, work[1].i = z__1.i;
    }

/*     ==== End of ZHSEQR ==== */

    return 0;
} /* zhseqr_ */

