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



/* > \brief \b ZLATM3 */

/*  =========== DOCUMENTATION =========== */

/* Online html documentation available at */
/*            http://www.netlib.org/lapack/explore-html/ */

/*  Definition: */
/*  =========== */

/*       COMPLEX*16   FUNCTION ZLATM3( M, N, I, J, ISUB, JSUB, KL, KU, */
/*                        IDIST, ISEED, D, IGRADE, DL, DR, IPVTNG, IWORK, */
/*                        SPARSE ) */


/*       INTEGER            I, IDIST, IGRADE, IPVTNG, ISUB, J, JSUB, KL, */
/*      $                   KU, M, N */
/*       DOUBLE PRECISION   SPARSE */


/*       INTEGER            ISEED( 4 ), IWORK( * ) */
/*       COMPLEX*16         D( * ), DL( * ), DR( * ) */


/* > \par Purpose: */
/*  ============= */
/* > */
/* > \verbatim */
/* > */
/* >    ZLATM3 returns the (ISUB,JSUB) entry of a random matrix of */
/* >    dimension (M, N) described by the other parameters. (ISUB,JSUB) */
/* >    is the final position of the (I,J) entry after pivoting */
/* >    according to IPVTNG and IWORK. ZLATM3 is called by the */
/* >    ZLATMR routine in order to build random test matrices. No error */
/* >    checking on parameters is done, because this routine is called in */
/* >    a tight loop by ZLATMR which has already checked the parameters. */
/* > */
/* >    Use of ZLATM3 differs from CLATM2 in the order in which the random */
/* >    number generator is called to fill in random matrix entries. */
/* >    With ZLATM2, the generator is called to fill in the pivoted matrix */
/* >    columnwise. With ZLATM3, the generator is called to fill in the */
/* >    matrix columnwise, after which it is pivoted. Thus, ZLATM3 can */
/* >    be used to construct random matrices which differ only in their */
/* >    order of rows and/or columns. ZLATM2 is used to construct band */
/* >    matrices while avoiding calling the random number generator for */
/* >    entries outside the band (and therefore generating random numbers */
/* >    in different orders for different pivot orders). */
/* > */
/* >    The matrix whose (ISUB,JSUB) entry is returned is constructed as */
/* >    follows (this routine only computes one entry): */
/* > */
/* >      If ISUB is outside (1..M) or JSUB is outside (1..N), return zero */
/* >         (this is convenient for generating matrices in band format). */
/* > */
/* >      Generate a matrix A with random entries of distribution IDIST. */
/* > */
/* >      Set the diagonal to D. */
/* > */
/* >      Grade the matrix, if desired, from the left (by DL) and/or */
/* >         from the right (by DR or DL) as specified by IGRADE. */
/* > */
/* >      Permute, if desired, the rows and/or columns as specified by */
/* >         IPVTNG and IWORK. */
/* > */
/* >      Band the matrix to have lower bandwidth KL and upper */
/* >         bandwidth KU. */
/* > */
/* >      Set random entries to zero as specified by SPARSE. */
/* > \endverbatim */

/*  Arguments: */
/*  ========== */

/* > \param[in] M */
/* > \verbatim */
/* >          M is INTEGER */
/* >           Number of rows of matrix. Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in] N */
/* > \verbatim */
/* >          N is INTEGER */
/* >           Number of columns of matrix. Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in] I */
/* > \verbatim */
/* >          I is INTEGER */
/* >           Row of unpivoted entry to be returned. Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in] J */
/* > \verbatim */
/* >          J is INTEGER */
/* >           Column of unpivoted entry to be returned. Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in,out] ISUB */
/* > \verbatim */
/* >          ISUB is INTEGER */
/* >           Row of pivoted entry to be returned. Changed on exit. */
/* > \endverbatim */
/* > */
/* > \param[in,out] JSUB */
/* > \verbatim */
/* >          JSUB is INTEGER */
/* >           Column of pivoted entry to be returned. Changed on exit. */
/* > \endverbatim */
/* > */
/* > \param[in] KL */
/* > \verbatim */
/* >          KL is INTEGER */
/* >           Lower bandwidth. Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in] KU */
/* > \verbatim */
/* >          KU is INTEGER */
/* >           Upper bandwidth. Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in] IDIST */
/* > \verbatim */
/* >          IDIST is INTEGER */
/* >           On entry, IDIST specifies the type of distribution to be */
/* >           used to generate a random matrix . */
/* >           1 => real and imaginary parts each UNIFORM( 0, 1 ) */
/* >           2 => real and imaginary parts each UNIFORM( -1, 1 ) */
/* >           3 => real and imaginary parts each NORMAL( 0, 1 ) */
/* >           4 => complex number uniform in DISK( 0 , 1 ) */
/* >           Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in,out] ISEED */
/* > \verbatim */
/* >          ISEED is INTEGER array of dimension ( 4 ) */
/* >           Seed for random number generator. */
/* >           Changed on exit. */
/* > \endverbatim */
/* > */
/* > \param[in] D */
/* > \verbatim */
/* >          D is COMPLEX*16 array of dimension ( MIN( I , J ) ) */
/* >           Diagonal entries of matrix. Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in] IGRADE */
/* > \verbatim */
/* >          IGRADE is INTEGER */
/* >           Specifies grading of matrix as follows: */
/* >           0  => no grading */
/* >           1  => matrix premultiplied by diag( DL ) */
/* >           2  => matrix postmultiplied by diag( DR ) */
/* >           3  => matrix premultiplied by diag( DL ) and */
/* >                         postmultiplied by diag( DR ) */
/* >           4  => matrix premultiplied by diag( DL ) and */
/* >                         postmultiplied by inv( diag( DL ) ) */
/* >           5  => matrix premultiplied by diag( DL ) and */
/* >                         postmultiplied by diag( CONJG(DL) ) */
/* >           6  => matrix premultiplied by diag( DL ) and */
/* >                         postmultiplied by diag( DL ) */
/* >           Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in] DL */
/* > \verbatim */
/* >          DL is COMPLEX*16 array ( I or J, as appropriate ) */
/* >           Left scale factors for grading matrix.  Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in] DR */
/* > \verbatim */
/* >          DR is COMPLEX*16 array ( I or J, as appropriate ) */
/* >           Right scale factors for grading matrix.  Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in] IPVTNG */
/* > \verbatim */
/* >          IPVTNG is INTEGER */
/* >           On entry specifies pivoting permutations as follows: */
/* >           0 => none. */
/* >           1 => row pivoting. */
/* >           2 => column pivoting. */
/* >           3 => full pivoting, i.e., on both sides. */
/* >           Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in] IWORK */
/* > \verbatim */
/* >          IWORK is INTEGER array ( I or J, as appropriate ) */
/* >           This array specifies the permutation used. The */
/* >           row (or column) originally in position K is in */
/* >           position IWORK( K ) after pivoting. */
/* >           This differs from IWORK for ZLATM2. Not modified. */
/* > \endverbatim */
/* > */
/* > \param[in] SPARSE */
/* > \verbatim */
/* >          SPARSE is DOUBLE PRECISION between 0. and 1. */
/* >           On entry specifies the sparsity of the matrix */
/* >           if sparse matrix is to be generated. */
/* >           SPARSE should lie between 0 and 1. */
/* >           A uniform ( 0, 1 ) random number x is generated and */
/* >           compared to SPARSE; if x is larger the matrix entry */
/* >           is unchanged and if x is smaller the entry is set */
/* >           to zero. Thus on the average a fraction SPARSE of the */
/* >           entries will be set to zero. */
/* >           Not modified. */
/* > \endverbatim */

/*  Authors: */
/*  ======== */

/* > \author Univ. of Tennessee */
/* > \author Univ. of California Berkeley */
/* > \author Univ. of Colorado Denver */
/* > \author NAG Ltd. */

/* > \date June 2016 */

/* > \ingroup complex16_matgen */

/*  ===================================================================== */
/* Double Complex */ VOID zlatm3_(doublecomplex * ret_val, integer *m, 
	integer *n, integer *i__, integer *j, integer *isub, integer *jsub, 
	integer *kl, integer *ku, integer *idist, integer *iseed, 
	doublecomplex *d__, integer *igrade, doublecomplex *dl, doublecomplex 
	*dr, integer *ipvtng, integer *iwork, doublereal *sparse)
{
    /* System generated locals */
    integer i__1, i__2;
    doublecomplex z__1, z__2, z__3;

    /* Local variables */
    doublecomplex ctemp;
    extern doublereal dlaran_(integer *);
    //extern /* Double Complex */ VOID zlarnd_(doublecomplex *, integer *, 
    extern doublecomplex zlarnd_(integer *, 
	    integer *);


/*  -- LAPACK auxiliary routine (version 3.7.0) -- */
/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
/*     June 2016 */





/*  ===================================================================== */









/* ----------------------------------------------------------------------- */



/*     Check for I and J in range */

    /* Parameter adjustments */
    --iwork;
    --dr;
    --dl;
    --d__;
    --iseed;

    /* Function Body */
    if (*i__ < 1 || *i__ > *m || *j < 1 || *j > *n) {
	*isub = *i__;
	*jsub = *j;
	 ret_val->r = 0.,  ret_val->i = 0.;
	return ;
    }

/*     Compute subscripts depending on IPVTNG */

    if (*ipvtng == 0) {
	*isub = *i__;
	*jsub = *j;
    } else if (*ipvtng == 1) {
	*isub = iwork[*i__];
	*jsub = *j;
    } else if (*ipvtng == 2) {
	*isub = *i__;
	*jsub = iwork[*j];
    } else if (*ipvtng == 3) {
	*isub = iwork[*i__];
	*jsub = iwork[*j];
    }

/*     Check for banding */

    if (*jsub > *isub + *ku || *jsub < *isub - *kl) {
	 ret_val->r = 0.,  ret_val->i = 0.;
	return ;
    }

/*     Check for sparsity */

    if (*sparse > 0.) {
	if (dlaran_(&iseed[1]) < *sparse) {
	     ret_val->r = 0.,  ret_val->i = 0.;
	    return ;
	}
    }

/*     Compute entry and grade it according to IGRADE */

    if (*i__ == *j) {
	i__1 = *i__;
	ctemp.r = d__[i__1].r, ctemp.i = d__[i__1].i;
    } else {
	//zlarnd_(&z__1, idist, &iseed[1]);
	z__1=zlarnd_(idist, &iseed[1]);
	ctemp.r = z__1.r, ctemp.i = z__1.i;
    }
    if (*igrade == 1) {
	i__1 = *i__;
	z__1.r = ctemp.r * dl[i__1].r - ctemp.i * dl[i__1].i, z__1.i = 
		ctemp.r * dl[i__1].i + ctemp.i * dl[i__1].r;
	ctemp.r = z__1.r, ctemp.i = z__1.i;
    } else if (*igrade == 2) {
	i__1 = *j;
	z__1.r = ctemp.r * dr[i__1].r - ctemp.i * dr[i__1].i, z__1.i = 
		ctemp.r * dr[i__1].i + ctemp.i * dr[i__1].r;
	ctemp.r = z__1.r, ctemp.i = z__1.i;
    } else if (*igrade == 3) {
	i__1 = *i__;
	z__2.r = ctemp.r * dl[i__1].r - ctemp.i * dl[i__1].i, z__2.i = 
		ctemp.r * dl[i__1].i + ctemp.i * dl[i__1].r;
	i__2 = *j;
	z__1.r = z__2.r * dr[i__2].r - z__2.i * dr[i__2].i, z__1.i = z__2.r * 
		dr[i__2].i + z__2.i * dr[i__2].r;
	ctemp.r = z__1.r, ctemp.i = z__1.i;
    } else if (*igrade == 4 && *i__ != *j) {
	i__1 = *i__;
	z__2.r = ctemp.r * dl[i__1].r - ctemp.i * dl[i__1].i, z__2.i = 
		ctemp.r * dl[i__1].i + ctemp.i * dl[i__1].r;
	z_div(&z__1, &z__2, &dl[*j]);
	ctemp.r = z__1.r, ctemp.i = z__1.i;
    } else if (*igrade == 5) {
	i__1 = *i__;
	z__2.r = ctemp.r * dl[i__1].r - ctemp.i * dl[i__1].i, z__2.i = 
		ctemp.r * dl[i__1].i + ctemp.i * dl[i__1].r;
	d_cnjg(&z__3, &dl[*j]);
	z__1.r = z__2.r * z__3.r - z__2.i * z__3.i, z__1.i = z__2.r * z__3.i 
		+ z__2.i * z__3.r;
	ctemp.r = z__1.r, ctemp.i = z__1.i;
    } else if (*igrade == 6) {
	i__1 = *i__;
	z__2.r = ctemp.r * dl[i__1].r - ctemp.i * dl[i__1].i, z__2.i = 
		ctemp.r * dl[i__1].i + ctemp.i * dl[i__1].r;
	i__2 = *j;
	z__1.r = z__2.r * dl[i__2].r - z__2.i * dl[i__2].i, z__1.i = z__2.r * 
		dl[i__2].i + z__2.i * dl[i__2].r;
	ctemp.r = z__1.r, ctemp.i = z__1.i;
    }
     ret_val->r = ctemp.r,  ret_val->i = ctemp.i;
    return ;

/*     End of ZLATM3 */

} /* zlatm3_ */

