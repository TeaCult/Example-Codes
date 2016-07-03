#ifndef _BIGINTEGERS_H_
#define _BIGINTEGERS_H_
#endif
#define PRIVATE static
#define PUBLIC
#define BIGZERO bigNumbersLibrary_ZERO_Positive
#define BIGONE  bigNumbersLibrary_ONE_Positive

typedef struct bignum
{
    char sign; //'p' for positive 'n' for negative;
    char number[1000];

}bignum;

bignum BIGZERO={'p',"0"};
bignum BIGONE ={'p',"1"};

PUBLIC  int bigCmp(const bignum *n1,const bignum *n2);
PRIVATE int shiftbignum(int t,bignum *n);
PUBLIC  int bigclear(bignum *n);
PUBLIC  bignum *getbignum   (bignum *n1);
PUBLIC  bignum *putbignum   (const bignum *n1);
PRIVATE bignum *bignegative (bignum *n1);
PUBLIC  bignum *bigincrement(bignum *n,size_t by_n);
PUBLIC  bignum *bigdecrement(bignum *n,size_t by_n);
PRIVATE bignum *bigabsadd   (const bignum *n1,const bignum *n2,bignum *result);
PRIVATE bignum *bigabssub   (const bignum *n1,const bignum *n2,bignum *result);
PUBLIC  bignum *bigadd      (const bignum *n1,const bignum *n2,bignum *result);
PUBLIC  bignum *bigsub      (const bignum *n1,const bignum *n2,bignum *result);
PRIVATE int bigabsCmp   (const bignum *n1,const bignum *n2);
PRIVATE int isequalbig  (bignum *n1,bignum *n2);




