#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <assert.h>
#include "bintegers.h"
#define ABORT_NABN(x) if(!isvalidbignum((x))) {printf("The number is NaBN\n"); fprintf(stderr,"Bignumber Data Corrupted...") ; abort(); }
#define SHORT_ZEROS(x) while((strlen((x)->number)!=1) && ((x)->number[0]=='0')) shiftbignum(1,(x))

// BUNLARI POINTERLARLA VE MALLOCLA YAZ; POINTERLAR !!! // Fonksiyon bildirim isim düzeltmeleri ve kisitlar;

int bigCmp(const bignum *n1,const bignum *n2);
int shiftbignum(int t,bignum *n);
int bigclear(bignum *n);
bignum *getbignum   (bignum *n1);
bignum *putbignum   (const bignum *n1);
bignum *bignegative (bignum *n1);
bignum *bigincrement(bignum *n,size_t by_n);
bignum *bigdecrement(bignum *n,size_t by_n);
bignum *bigabsadd   (const bignum *n1,const bignum *n2,bignum *result);
bignum *bigabssub   (const bignum *n1,const bignum *n2,bignum *result);
bignum *bigadd      (const bignum *n1,const bignum *n2,bignum *result);
bignum *bigsub      (const bignum *n1,const bignum *n2,bignum *result);
int     bigabsCmp   (const bignum *n1,const bignum *n2);
int     isequalbig  (bignum *n1,bignum *n2);

int isvalidbignum(const bignum *n)
{
int i=0;
while (i<strlen(n->number)){
    if(!isdigit(n->number[i++]) || n->number[strlen(n->number)])
    return 0;
}
return 1;
}

int isequalbig  (bignum *n1,bignum *n2)
{
   if(!bigCmp(n1,n2))
   return 1;
   return 0;
}

int bigabsCmp(const bignum *n1,const bignum *n2)
{
    ABORT_NABN(n1);
    ABORT_NABN(n2);

    if(strlen(n1->number)>strlen(n2->number))
    return 1;

    if(strlen(n2->number)>strlen(n1->number))
    return -1;

    if(strlen(n1->number)==strlen(n2->number)){
        if(strcmp(n1->number,n2->number)==1)
        return 1;

        if(strcmp(n1->number,n2->number)==-1)
        return -1;

        if(!strcmp(n1->number,n2->number))
        return 0;
    }

   exit(EXIT_FAILURE);
}

int bigCmp(const bignum *n1,const bignum *n2)
{
    ABORT_NABN(n1);
    ABORT_NABN(n2);

    if(n1->sign=='p'&& n2->sign=='p')
    return bigabsCmp(n1,n2);

    if(n1->sign=='p'&& n2->sign=='n')
    return 1;

    if(n1->sign=='n' && n2->sign=='p')
    return -1;

    if(n1->sign=='n' && n2->sign=='n')
    return bigabsCmp(n1,n2)*-1;
    exit(EXIT_FAILURE);
}

bignum *getbignum(bignum *n1)
{
    char str[1000];

    n1->sign='p';
    gets(str);

    if(str[0]=='-'){
        n1->sign='n';
        strcpy(n1->number,&str[1]);
        return n1;
        }

    if(str[0]=='+'){
    strcpy(n1->number,&str[1]);
    return n1;
    }

    strcpy(n1->number,str);
    SHORT_ZEROS(n1);
    ABORT_NABN(n1);
    return n1;

}


bignum *putbignum(const bignum *n1)
{
    ABORT_NABN(n1);

    if(n1->sign=='n')
        putchar('-');

    puts(n1->number);
    return (bignum *)n1;
}

bignum *bignegative(bignum *n1)
{
ABORT_NABN(n1);
if (n1->sign=='p') n1->sign='n';
if (n1->sign=='n') n1->sign='p';
return n1;
}

int bigclear(bignum *n)
{
    *n=BIGZERO;
    return 0;
}

bignum *bigincrement(bignum *n,size_t by_n)
{
    ABORT_NABN(n);

    while(by_n--)
    bigadd(n,&BIGONE,n);
    ABORT_NABN(n);
    return n;
}

bignum *bigdecrement(bignum *n,size_t by_n)
{
    ABORT_NABN(n);

    while(by_n--)
    bigsub(n,&BIGONE,n);
    return n;
}

int shiftbignum(int t,bignum *n)
{
    ABORT_NABN(n);

    bignum temp;
    int len=strlen(n->number);
    temp.sign=n->sign;
    memcpy(temp.number,n->number,len);
    memcpy(temp.number+len,n->number,len);
    bigclear(n);
    memcpy(n->number,temp.number+len+t,len-t);
    n->sign=temp.sign;
    ABORT_NABN(n);
    return 0;
}

bignum *bigabsadd(const bignum *n1,const bignum *n2,bignum *result)
{
    ABORT_NABN(n1);
    ABORT_NABN(n2);

    int len,i=0,itp=0;
    int len1=strlen(n1->number);
    int len2=strlen(n2->number);
    bignum *temp1;
    bignum *temp2;
    len= len1>=len2 ? len1 : len2;
    temp1=(bignum *)malloc(sizeof(bignum));
    temp2=(bignum *)malloc(sizeof(bignum));
    strcpy(temp1->number,n1->number);
    strcpy(temp2->number,n2->number);
    strrev(temp1->number);
    strrev(temp2->number);
    for(i=0;i<len;++i){
        if(!isdigit(temp1->number[i]))temp1->number[i]='0';
        if(!isdigit(temp2->number[i]))temp2->number[i]='0';
        result->number[i]=(temp1->number[i]+temp2->number[i]+itp-2*'0')%10+'0';
        itp=(temp1->number[i]+temp2->number[i]+itp-2*'0')/10;
    }
    free(temp1);
    free(temp2);
    strrev(result->number);
    SHORT_ZEROS(result);
    ABORT_NABN(result);
    return result;

}


bignum *bigabssub(const bignum *n1,const bignum *n2,bignum *result)
{

    ABORT_NABN(n1);
    ABORT_NABN(n2);

    if(!bigabsCmp(n1,n2)){
    *result=BIGZERO;
    return result;
    }

    if (bigabsCmp(n1,n2)==-1){
        bigabssub(n2,n1,result);
        return NULL;
    }


    int len,i=0;
    int len1=strlen(n1->number);
    int len2=strlen(n2->number);
    char *temp1;
    char *temp2;
    len= len1>=len2 ? len1 : len2;
    temp1=(char *)malloc(len*sizeof(char));
    temp2=(char *)malloc(len*sizeof(char));
    memcpy(temp1,n1->number,len1+1);
    memcpy(temp2,n2->number,len2+1);
    strrev(temp1);
    strrev(temp2);
    while(i<len){
        if(i>=len1)temp1[i]='0';
        if(i>=len2)temp2[i]='0';
        if(temp1[i]<temp2[i]){
            temp1[i+1]-=1;
            temp1[i]+=10;
        }
        result->number[i]=temp1[i]-temp2[i]+'0';
    i++;
    }
    free(temp1);
    free(temp2);
    strrev(result->number);
    SHORT_ZEROS(result);
    ABORT_NABN(result);
    return result;
}

bignum *bigadd(const bignum *n1,const bignum *n2,bignum *result)
{

    if(n1->sign=='p' && n2->sign=='p'){
        bigabsadd(n1,n2,result);
        return result;
    }

    if(n1->sign=='n' && n2->sign=='n'){
        bigabsadd(n1,n2,result);
        result->sign='n';
        return result;
    }

    if(!bigabsCmp(n1,n2)) {
        *result=BIGZERO;
        return result;
    }

    if(n1->sign=='p' && n2->sign=='n')
    {
        bigabssub(n1,n2,result);
        if(bigabsCmp(n2,n1)==1)
        result->sign='n';
        return result;
    }

    if(n1->sign=='n' && n2->sign=='p'){
        bigabssub(n1,n2,result);
        if(bigabsCmp(n1,n2)==1)
        result->sign='n';
        return result;
    }


return result;
}


bignum *bigsub(const bignum *n1,const bignum *n2,bignum *result)
{

    if(n1->sign=='p' && n2->sign=='n'){
        bigabsadd(n1,n2,result);
        return result;
    }

    if(n1->sign=='n' && n2->sign=='p'){
        bigabsadd(n1,n2,result);
        result->sign='n';
        return result;

    }

    if(!bigabsCmp(n1,n2)) {
        *result=BIGZERO;
        return result;
    }

    if(n1->sign=='p' && n2->sign=='p'){
        bigabssub(n1,n2,result);
        if(bigabsCmp(n2,n1)==1)
        result->sign='n';
        return result;
    }

    if(n1->sign=='n' && n2->sign=='n'){
        bigabssub(n1,n2,result);
        if(bigabsCmp(n2,n1)==-1)
        result->sign='n';
        return result;
    }



return result;
    }

bignum *bigmul(const bignum *n1, const bignum *n2,bignum *result)
{
  ABORT_NABN(n1);
  ABORT_NABN(n2);

  int i=0,k=0,t=0,k2=0;
  bignum *buffer;
  bignum *buffer2;
  bignum *num1;
  bignum *num2;
  char *zeros;

  buffer =(bignum *)malloc(sizeof(bignum));
  num1   =(bignum *)malloc(sizeof(bignum));
  num2   =(bignum *)malloc(sizeof(bignum));
  buffer2=(bignum *)malloc(sizeof(bignum));
  zeros=(char *)malloc(1000*sizeof(char));

  for(i=0;i<1000;i++)
  *(zeros+i)='0';
  *(zeros+i)=0;

  *buffer=BIGZERO;
  *buffer2=BIGZERO;
  *num1=*n1;
  *num2=*n2;
  *result=BIGZERO;


  strrev(num1->number);
  strrev(num2->number);


    for(k=0;k<strlen(num2->number);++k){
        *buffer=BIGZERO;
        t=0;
        for(i=0;i<strlen(num1->number);++i){
            buffer->number[i]=((num2->number[k]-'0')*(num1->number[i]-'0')+t)%10+'0';
            t=((num2->number[k]-'0')*(num1->number[i]-'0')+t)/10;

        }
        buffer->number[i]=t+'0';
        buffer->number[i+1]=0;
        SHORT_ZEROS(buffer);
        strrev(buffer->number);
        strncat(buffer->number,(const char *)zeros,k);
        SHORT_ZEROS(buffer);
        bigabsadd(buffer,buffer2,buffer2);
        }


  *result=*buffer2;
  ABORT_NABN(result);

  free(num1);
  free(num2);
  free(buffer);
  free(buffer2);
  free(zeros);

  if(n1->sign!=n2->sign)
  result->sign='n';

return result;
}

bignum *bigdiv(const bignum *n1, const bignum *n2,bignum *result)
{
  ABORT_NABN(n1);
  ABORT_NABN(n2);

  int i=0,k=0,t=0,k2=0;
  bignum *divisor;
  bignum *divident;
  char *zeros;

  divisor =(bignum *)malloc(sizeof(bignum));
  divident=(bignum *)malloc(sizeof(bignum));
  zeros=(char *)malloc(1000*sizeof(char));

  for(i=0;i<1000;i++)
  *(zeros+i)='0';
  *(zeros+i)=0;

  *divident=*n1;
  *divisor=*n2;
  *result=BIGZERO;

  k=strlen(divident->number)-strlen(divisor->number);
  if(k<0)
  return result;

  i=0;

    while(k--){
        t=0;
        *divisor=*n2;
        strncat(divisor->number,zeros,k);

            while(bigCmp(divident,divisor)>=0){
                t++;
            bigabssub(divident,divisor,divident);
            }

            result->number[i++]=t%10+'0';
            putbignum(result);
            putbignum(divident);
            putbignum(divisor);
             ABORT_NABN(result);
              ABORT_NABN(divisor);
               ABORT_NABN(divident);
    }

    result->number[i]=0;



  ABORT_NABN(result);

  free(divisor);
  free(divident);
  free(zeros);

  if(n1->sign!=n2->sign)
  result->sign='n';

return result;
}

bignum *bigmod(const bignum *n1, const bignum *n2,bignum *result)
{
  ABORT_NABN(n1);
  ABORT_NABN(n2);

  int i=0,k=0,t=0,k2=0;
  bignum *divisor;
  bignum *divident;
  bignum *remainder;
  char *zeros;

  divisor =(bignum *)malloc(sizeof(bignum));
  divident   =(bignum *)malloc(sizeof(bignum));
  zeros=(char *)malloc(1000*sizeof(char));

  for(i=0;i<1000;i++)
  *(zeros+i)='0';
  *(zeros+i)=0;

  *divident=*n1;
  *result=BIGZERO;

  k=strlen(divident->number)-strlen(divisor->number);
  if(k<0)
  return result;

  i=0;

    while((k--)>=0){
        t=0;
        *divisor=*n2;
        strncat(divisor->number,zeros,k+1);

            while(bigCmp(divident,divisor)>0)
            bigabssub(divident,divisor,divident);
    }

  *result=*divident;

  ABORT_NABN(result);

  free(divisor);
  free(divident);
  free(zeros);

return result;
}

void testbigsum(void)
{
bignum *n1,*result,*n2;
result=(bignum *)malloc(sizeof(bignum));
n1    =(bignum *)malloc(sizeof(bignum));
n2    =(bignum *)malloc(sizeof(bignum));

    while(1)
    {

    *result=*n1=*n2=BIGZERO;
    printf("Enter The First Big Number:\n");
    getbignum(n1);
    printf("\n\nEnter The Second Big Number:\n");
    getbignum(n2);
//    bigadd(n1,n2,result);
//    printf("\nNumber1+Number2 =");
//    putbignum(result);
//    bigsub(n1,n2,result);
//    printf("\nNumber1-Number2 =");
//    putbignum(result);
//    *result=BIGZERO;
//    bigmul(n1,n2,result);
//    printf("\nNumber1*Number2 =");
//    putbignum(result);
//    *result=BIGZERO;
    printf("\nNumber1/Number2 =");
    bigdiv(n1,n2,result);
    putbignum(result);
    *result=BIGZERO;
//    printf("\nNumber1%%Number2 =");
//    bigmod(n1,n2,result);
//    putbignum(result);
//    *result=BIGZERO;

//    switch(bigCmp(n1,n2)+2){
//            case (3):printf("\n\nNumber1>Number2\n");break;
//            case (2):printf("\n\nNumber1=Number2\n");break;
//            case (1):printf("\n\nNumber1<Number2\n");break;
//        }

    printf("\n\n***************************\n\n");

    }
free(result);
free(n1);
free(n2);

}
