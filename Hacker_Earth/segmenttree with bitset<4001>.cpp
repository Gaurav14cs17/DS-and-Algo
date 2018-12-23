//https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/practice-problems/algorithm/distinct-integers-in-range-66eca44b/



#include"bits/stdc++.h"
using namespace std;
const int N = 5e5 + 5;

int a[N];
int b[N];
int n ;
bitset<5001>tree[N] , tree_1[N];


void build( int node , int l , int r ){
if( l == r  ){
    tree[node].set(a[l]);
    tree_1[node].set(b[l]);
    return ;
}
int mid = ( l + r )/2;
build( node + node , l , mid );
build( node + node +1 , mid +1 , r );
tree[node]   =  tree[node + node ] | tree[node + node +1 ];
tree_1[node]  = tree_1[node + node] | tree_1[node+node+1 ];
}


bitset<5001> query_1( int node , int l , int r , int ql , int qr ){

if( l > r || l > qr || r < ql ) return 0;
if( ql <=l && r <=qr ) return tree[node];


int mid = ( l + r )/2;
return query_1( node + node , l , mid , ql , qr ) | query_1( node + node +1 , mid +1 , r , ql , qr );

}



bitset<5001>query_2( int node , int l , int r , int ql , int qr ){

if( l> r || l > qr || r < ql ) return 0;
if( ql <=l && r <= qr ) return tree_1[node];

int mid =  ( l + r )/2;
return query_2( node + node , l , mid , ql , qr )| query_2( node + node +1 , mid +1 , r , ql , qr );

}

int main( void ){


scanf("%d",&n);
for( int i =1 ; i<=n ; ++i ) scanf("%d",a+i);
for( int i =1 ; i<=n ; ++i )scanf("%d",b + i );


build( 1 , 1 , n  );

int q;
scanf("%d",&q);
while(q--){


    int a1 , b1 , c , d;
    scanf("%d%d%d%d",&a1,&b1,&c,&d);
    cout<<  ( query_1( 1 , 1 , n , a1 , b1 ) | query_2( 1 , 1 , n , c ,d ) ).count();
    printf("\n");


}

}
