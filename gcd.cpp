#include<bits/stdc++.h>
using namespace std;
vector<vector<int>>  division(vector<int> numerator, vector<int> denominator){
    vector<vector<int>> result;
    int dq = (numerator.size()-1) - (denominator.size()-1);
    int dN = numerator.size()-1;
    int dD = denominator.size() -1;
    int dd = 0;
    int dr = dN;
    vector<int> d(dN + 1,0);
    vector<int> q(dq+1,0);
    vector<int> r(dr+1,0);
	if( dN >= dD ) {
		while(dN >= dD) {
			q[dN-dD] = numerator[dN]/denominator[dD];
 
			for(int  i = 0 ; i < dD + 1 ; i++ )
				d[i+dN-dD] = denominator[i] * q[dN-dD];
 
			for(int  i = 0 ; i < dN + 1 ; i++ )
				numerator[i] = (numerator[i] ^ d[i]);
			dN--;
		}
	} 
	for( int i = 0 ; i <= dN ; i++ )
		r[i] = numerator[i];

    result.push_back(q);
    result.push_back(r);
    return result;
}

vector<int> moduluss(vector<int> a, vector<int> b){
    vector<int> remainder = division(a,b)[1];
    while(remainder.size()!=0 && remainder[remainder.size()-1]==0){
        remainder.pop_back();
    }
    return remainder;
}

vector<int> gcd(vector<int> a, vector<int> b){
    if(b.size()==0)
    return a;
    else{
        return gcd(b,moduluss(a,b));
    }
}

int main()
{
    int d1,d2;
    cout<<"Enter the degree of Polynomial 1 :";
    cin>>d1;
    cout<<"Enter the coefficients of polynomial 1\n";
    vector<int> P1(d1+1);

    for(int i=0;i<d1+1;i++)
    {
        cin>>P1[i];
    }
    cout<<"Enter the degree of Polynomial 2:";
    cin>>d2;
    vector<int> P2(d2+1);
    cout<<"Enter the coefficients of polynomial 2\n";
    for(int i=0;i<d2+1;i++)
    {
        cin>>P2[i];
    }
    vector<int> d= gcd(P1,P2);

    cout<<"gcd of poly 1 and poly 2 is \n";
    for(int i= d.size()-1;i>0;i--)
    {
        cout<<d[i]<<"x^"<<i<<" +";
    }
    cout<<d[0];
}
