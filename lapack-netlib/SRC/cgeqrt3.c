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

/* > \brief <b> CGEQRT3 recursively computes a QR factorization of a general real or complex matrix using the 
compact WY representation of Q. </b> */

/*  =========== DOCUMENTATION =========== */

/* Online html documentation available at */
/*            http://www.netlib.org/lapack/explore-html/ */

/* > \htmlonly */
/* > Download CGEQRT3 + dependencies */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/cgeqrt3
.f"> */
/* > [TGZ]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/cgeqrt3
.f"> */
/* > [ZIP]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/cgeqrt3
.f"> */
/* > [TXT]</a> */
/* > \endhtmlonly */

/*  Definition: */
/*  =========== */

/*        SUBROUTINE CGEQRT3( M, N, A, LDA, T, LDT, INFO ) */

/*       INTEGER   INFO, LDA, M, N, LDT */
/*       COMPLEX   A( LDA, * ), T( LDT, * ) */


/* > \par Purpose: */
/*  ============= */
/* > */
/* > \verbatim */
/* > */
/* > CGEQRT3 recursively computes a QR factorization of a complex M-by-N matrix A, */
/* > using the compact WY representation of Q. */
/* > */
/* > Based on the algorithm of Elmroth and Gustavson, */
/* > IBM J. Res. Develop. Vol 44 No. 4 July 2000. */
/* > \endverbatim */

/*  Arguments: */
/*  ========== */

/* > \param[in] M */
/* > \verbatim */
/* >          M is INTEGER */
/* >          The number of rows of the matrix A.  M >= N. */
/* > \endverbatim */
/* > */
/* > \param[in] N */
/* > \verbatim */
/* >          N is INTEGER */
/* >          The number of columns of the matrix A.  N >= 0. */
/* > \endverbatim */
/* > */
/* > \param[in,out] A */
/* > \verbatim */
/* >          A is COMPLEX array, dimension (LDA,N) */
/* >          On entry, the complex M-by-N matrix A.  On exit, the elements on and */
/* >          above the diagonal contain the N-by-N upper triangular matrix R; the */
/* >          elements below the diagonal are the columns of V.  See below for */
/* >          further details. */
/* > \endverbatim */
/* > */
/* > \param[in] LDA */
/* > \verbatim */
/* >          LDA is INTEGER */
/* >          The leading dimension of the array A.  LDA >= f2cmax(1,M). */
/* > \endverbatim */
/* > */
/* > \param[out] T */
/* > \verbatim */
/* >          T is COMPLEX array, dimension (LDT,N) */
/* >          The N-by-N upper triangular factor of the block reflector. */
/* >          The elements on and above the diagonal contain the block */
/* >          reflector T; the elements below the diagonal are not used. */
/* >          See below for further details. */
/* > \endverbatim */
/* > */
/* > \param[in] LDT */
/* > \verbatim */
/* >          LDT is INTEGER */
/* >          The leading dimension of the array T.  LDT >= f2cmax(1,N). */
/* > \endverbatim */
/* > */
/* > \param[out] INFO */
/* > \verbatim */
/* >          INFO is INTEGER */
/* >          = 0: successful exit */
/* >          < 0: if INFO = -i, the i-th argument had an illegal value */
/* > \endverbatim */

/*  Authors: */
/*  ======== */

/* > \author Univ. of Tennessee */
/* > \author Univ. of California Berkeley */
/* > \author Univ. of Colorado Denver */
/* > \author NAG Ltd. */

/* > \date June 2016 */

/* > \ingroup complexGEcomputational */

/* > \par Further Details: */
/*  ===================== */
/* > */
/* > \verbatim */
/* > */
/* >  The matrix V stores the elementary reflectors H(i) in the i-th column */
/* >  below the diagonal. For example, if M=5 and N=3, the matrix V is */
/* > */
/* >               V = (  1       ) */
/* >                   ( v1  1    ) */
/* >                   ( v1 v2  1 ) */
/* >                   ( v1 v2 v3 ) */
/* >                   ( v1 v2 v3 ) */
/* > */
/* >  where the vi's represent the vectors which define H(i), which are returned */
/* >  in the matrix A.  The 1's along the diagonal of V are not stored in A.  The */
/* >  block reflector H is then given by */
/* > */
/* >               H = I - V * T * V**H */
/* > */
/* >  where V**H is the conjugate transpose of V. */
/* > */
/* >  For details of the algorithm, see Elmroth and Gustavson (cited above). */
/* > \endverbatim */
/* > */
/*  ===================================================================== */
/* Subroutine */ int cgeqrt3_(integer *m, integer *n, complex *a, integer *
	lda, complex *t, integer *ldt, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, t_dim1, t_offset, i__1, i__2, i__3, i__4, i__5;
    complex q__1;

    /* Local variables */
    integer i__, j;
    extern /* Subroutine */ int cgemm_(char *, char *, integer *, integer *, 
	    integer *, complex *, complex *, integer *, complex *, integer *, 
	    complex *, complex *, integer *);
    integer iinfo;
    extern /* Subroutine */ int ctrmm_(char *, char *, char *, char *, 
	    integer *, integer *, complex *, complex *, integer *, complex *, 
	    integer *);
    integer i1, j1, n1, n2;
    extern /* Subroutine */ int clarfg_(integer *, complex *, complex *, 
	    integer *, complex *), xerbla_(char *, integer *, ftnlen);


/*  -- LAPACK computational routine (version 3.7.0) -- */
/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
/*     June 2016 */


/*  ===================================================================== */


    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    t_dim1 = *ldt;
    t_offset = 1 + t_dim1 * 1;
    t -= t_offset;

    /* Function Body */
    *info = 0;
    if (*n < 0) {
	*info = -2;
    } else if (*m < *n) {
	*info = -1;
    } else if (*lda < f2cmax(1,*m)) {
	*info = -4;
    } else if (*ldt < f2cmax(1,*n)) {
	*info = -6;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("CGEQRT3", &i__1, (ftnlen)7);
	return 0;
    }

    if (*n == 1) {

/*        Compute Householder transform when N=1 */

	clarfg_(m, &a[a_dim1 + 1], &a[f2cmin(2,*m) + a_dim1], &c__1, &t[t_dim1 + 
		1]);

    } else {

/*        Otherwise, split A into blocks... */

	n1 = *n / 2;
	n2 = *n - n1;
/* Computing MIN */
	i__1 = n1 + 1;
	j1 = f2cmin(i__1,*n);
/* Computing MIN */
	i__1 = *n + 1;
	i1 = f2cmin(i__1,*m);

/*        Compute A(1:M,1:N1) <- (Y1,R1,T1), where Q1 = I - Y1 T1 Y1**H */

	cgeqrt3_(m, &n1, &a[a_offset], lda, &t[t_offset], ldt, &iinfo);

/*        Compute A(1:M,J1:N) = Q1**H A(1:M,J1:N) [workspace: T(1:N1,J1:N)] */

	i__1 = n2;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = n1;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		i__3 = i__ + (j + n1) * t_dim1;
		i__4 = i__ + (j + n1) * a_dim1;
		t[i__3].r = a[i__4].r, t[i__3].i = a[i__4].i;
	    }
	}
	ctrmm_("L", "L", "C", "U", &n1, &n2, &c_b1, &a[a_offset], lda, &t[j1 *
		 t_dim1 + 1], ldt)
		;

	i__1 = *m - n1;
	cgemm_("C", "N", &n1, &n2, &i__1, &c_b1, &a[j1 + a_dim1], lda, &a[j1 
		+ j1 * a_dim1], lda, &c_b1, &t[j1 * t_dim1 + 1], ldt);

	ctrmm_("L", "U", "C", "N", &n1, &n2, &c_b1, &t[t_offset], ldt, &t[j1 *
		 t_dim1 + 1], ldt)
		;

	i__1 = *m - n1;
	q__1.r = -1.f, q__1.i = 0.f;
	cgemm_("N", "N", &i__1, &n2, &n1, &q__1, &a[j1 + a_dim1], lda, &t[j1 *
		 t_dim1 + 1], ldt, &c_b1, &a[j1 + j1 * a_dim1], lda);

	ctrmm_("L", "L", "N", "U", &n1, &n2, &c_b1, &a[a_offset], lda, &t[j1 *
		 t_dim1 + 1], ldt)
		;

	i__1 = n2;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = n1;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		i__3 = i__ + (j + n1) * a_dim1;
		i__4 = i__ + (j + n1) * a_dim1;
		i__5 = i__ + (j + n1) * t_dim1;
		q__1.r = a[i__4].r - t[i__5].r, q__1.i = a[i__4].i - t[i__5]
			.i;
		a[i__3].r = q__1.r, a[i__3].i = q__1.i;
	    }
	}

/*        Compute A(J1:M,J1:N) <- (Y2,R2,T2) where Q2 = I - Y2 T2 Y2**H */

	i__1 = *m - n1;
	cgeqrt3_(&i__1, &n2, &a[j1 + j1 * a_dim1], lda, &t[j1 + j1 * t_dim1], 
		ldt, &iinfo);

/*        Compute T3 = T(1:N1,J1:N) = -T1 Y1**H Y2 T2 */

	i__1 = n1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    i__2 = n2;
	    for (j = 1; j <= i__2; ++j) {
		i__3 = i__ + (j + n1) * t_dim1;
		r_cnjg(&q__1, &a[j + n1 + i__ * a_dim1]);
		t[i__3].r = q__1.r, t[i__3].i = q__1.i;
	    }
	}

	ctrmm_("R", "L", "N", "U", &n1, &n2, &c_b1, &a[j1 + j1 * a_dim1], lda,
		 &t[j1 * t_dim1 + 1], ldt);

	i__1 = *m - *n;
	cgemm_("C", "N", &n1, &n2, &i__1, &c_b1, &a[i1 + a_dim1], lda, &a[i1 
		+ j1 * a_dim1], lda, &c_b1, &t[j1 * t_dim1 + 1], ldt);

	q__1.r = -1.f, q__1.i = 0.f;
	ctrmm_("L", "U", "N", "N", &n1, &n2, &q__1, &t[t_offset], ldt, &t[j1 *
		 t_dim1 + 1], ldt)
		;

	ctrmm_("R", "U", "N", "N", &n1, &n2, &c_b1, &t[j1 + j1 * t_dim1], ldt,
		 &t[j1 * t_dim1 + 1], ldt);

/*        Y = (Y1,Y2); R = [ R1  A(1:N1,J1:N) ];  T = [T1 T3] */
/*                         [  0        R2     ]       [ 0 T2] */

    }

    return 0;

/*     End of CGEQRT3 */

} /* cgeqrt3_ */

