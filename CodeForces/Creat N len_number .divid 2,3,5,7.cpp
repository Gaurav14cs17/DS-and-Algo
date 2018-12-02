///https://codeforces.com/problemset/problem/248/B

#include"bits/stdc++.h"
using namespace std;
const int N = 5e5 + 5;


int n ;
using ll  = long long ;

ll pow( ll a , ll b , ll m ){

ll  ans = 1;
while( b >0){

    if(b&1) ans = ( ans*a)%m;

    a = ( a* a)%m;
    b =  b>> 1;
}
return ans ;
}

 int main( void ){

 scanf("%lld",&n);
 if( n <=2 ) return printf("-1\n") , 0 ;

 ll st = pow( 10 , n-1 , 210 );
 ///cout<<210- st<<endl;


 st = 210 - st;

 vector<ll> v( n , 0 );
 v[0] = 1;
 ll tmp = 10;
 ll carry = 0;


 for( ll  i = n-1 ; i+1 ; --i ){
    v[i] = v[i] + st%tmp + carry;
    if( v[i] >=10) carry =  1;
    else carry  = 0;

    v[i] = v[i]%10;
    st = st/10;
 }


 for(auto it : v)
     cout<<it;




 }
