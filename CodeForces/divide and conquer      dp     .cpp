
/// http://codeforces.com/problemset/problem/448/C



#include"bits/stdc++.h"
using namespace std;

const int N = 5e5 + 5;
int arr[N];
int n ;


int solve( int l , int r , int h ){
    
    if( l >  r) return 0;
    if( l == r )   return arr[l] <= h ? 0 : 1;
    
    
    int mn = INT_MAX;
    int idx;
    
    for(int i = l ; i<=r ; ++i ){
        if( mn > arr[i]){
            mn = arr[i];
            idx = i;
        }
    }
    
    return min({ r - l + 1 , mn - h  + solve( l , idx-1 , mn ) + solve( idx+1 , r , mn)  });
}



int main( void ){
    
    scanf("%d",&n);
    
    for( int i = 1 ; i<=n ; ++i )scanf("%d",arr+i);
    
    int ans =  solve( 1 , n , 0 );
    
    printf("%d\n",ans);
}
