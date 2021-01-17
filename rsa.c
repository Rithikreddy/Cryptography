#include<gmp.h>
#include<stdio.h>
void main(){
    mpz_t a,b,m,e,d,n,pr,c,a1,b1,a2,b2,s0,s1,s2,t0,t1,t2,p,q,t,de;
    mpz_inits(a,b,m,e,d,n,pr,c,a1,b1,a2,b2,s0,s1,s2,t0,t1,t2,p,q,t,de,NULL);
    gmp_printf("Enter the value of a\n");
    gmp_scanf("%Zd",a);
    gmp_printf("Enter the value of b\n");
    gmp_scanf("%Zd",b);
    printf("Enter the number(M) which need to be encrypted\n");
    gmp_scanf("%Zd",m);
    mpz_init_set_ui(a2,1);
    mpz_sub(a1,a,a2);;
    mpz_init_set_ui(b2,1);
    mpz_sub(b1,b,b2);

    mpz_mul(n,a1,b1);

    gmp_printf("Enter the number(e) which makes gcd 1 with %Zd\n",n);
    gmp_scanf("%Zd",e);
    printf("Now d is the additive inverse of e with respect to n\n");
    //now required to the additive inverse of e with respect to n
    //now setting p as a*b
    mpz_mul(pr,a,b);
    mpz_set(a,n);
    mpz_set(b,e);

    mpz_init_set_ui(s0,1);
    mpz_init_set_ui(s1,0);
    mpz_init_set_ui(t0,0);
    mpz_init_set_ui(t1,1);
    mpz_set(p,a);
    mpz_set(q,b);
    while(mpz_cmp_ui(b,0)!=0){
        //for setting s
        mpz_fdiv_q(t,a,b);
        //gmp_printf("Quotient is %Zd\n",t);
        //gmp_printf("values of s0,s1,s2 before is \n%Zd\n%Zd\n%Zd\n",s0,s1,s2);
        mpz_mul(t,t,s1);
        mpz_sub(t,s0,t);
        mpz_set(s2,t);
        mpz_set(s0,s1);
        mpz_set(s1,s2);
        //gmp_printf("values of s0,s1,s2 after is \n%Zd\n%Zd\n%Zd\n",s0,s1,s2);
        //for setting t
        //gmp_printf("values of t0,t1,t2 before is \n%Zd\n%Zd\n%Zd\n",t0,t1,t2);
        mpz_fdiv_q(t,a,b);
        mpz_mul(t,t,t1);
        mpz_sub(t,t0,t);
        mpz_set(t2,t);
        mpz_set(t0,t1);
        mpz_set(t1,t2);
        //gmp_printf("values of t0,t1,t2 after is \n%Zd\n%Zd\n%Zd\n",t0,t1,t2);
        //now calculating gcd
        mpz_set(t,b);
        mpz_mod(b,a,b);
        mpz_set(a,t);
    }
    //gcd is a a
    //if gcd is 1 finding multiplicative inverse
    gmp_printf("The gcd is %Zd\n",a);
    if(mpz_cmp_ui(a,1)!=0){
        printf("They are not coprime to each other so multiplicative inverse doesn't exists\n");
    }
    else{
        if(mpz_cmp(p,q)>0){
            printf("a is greater than b so t1 is the multiplicative inverse\n");
            mpz_set(d,t0);
            //gmp_printf("%Zd\n%Zd\n%Zd\n",t1,t2,t0);
        }
        else{
            printf("a is lesser than b so s1 is the multiplicative inverse\n");
            //gmp_printf("%Zd\n %Zd\n %Zd\n",s2,s1,s0);
            mpz_set(d,s1);
        }
    }
    gmp_printf("The multiplicative inverse is %Zd\n",d);
    //now the additive inverse is found
    //computing RSA
    mpz_powm(c,m,e,pr);      //sets c as m^e mod pr(a*b)
    gmp_printf("The encrypted number is %Zd \n",c);
    //Decryption
    mpz_powm(de,c,d,pr);      //sets c as m^e mod pr(a*b)
    gmp_printf("The decrypted number is %Zd which is same as our input\n",de);
}
