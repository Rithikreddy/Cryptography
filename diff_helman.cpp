//Alice and bob both are defined in a single file only
#define ll long long
#include<bits/stdc++.h>
using namespace std;

int m=3,n=17;   //2 random nos as public key of alice and bob respectively
int a = 12;  //private key of alice
int b = 15;  //private key of bob

ll modpow(ll a,ll b,ll mod){
    if(b == 0)
        return 1;
    ll ans = modpow(a,b/2,mod);
    ans = (ans*ans)%mod;
    if(b & 1)
        ans = (ans*a)%mod;
    return ans;
}

int bob(int x){
    //received a number from alice decrypting it
    return int(modpow(x,b,m));
}

int alice(int y){
    //received a number from bob decrypting it
    return int(modpow(y,a,m));
}

int main(){
    int x = int(modpow(n,a,m));
    //sending the message to alice
    int y = int(modpow(n,b,m));
    int c = bob(x);
    int d = alice(y);
    if(c == d){
        cout<<"The original number is "<<c<<endl;
    }
    else
        cout<<c<<" "<<d<<endl;
}
