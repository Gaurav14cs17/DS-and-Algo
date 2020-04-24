// Problems link :  https://www.codechef.com/APRIL20A/problems/FCTRE

#include"bits/stdc++.h"
using namespace std;
const int N = 2e6 + 5;
#define mod 1000000007
vector<pair<int , int >>factor_array[N];
int Inv_array[N];


void __factor__(){
 factor_array[1].push_back({1 , 0 });
 for( int i = 2 ; i<N ; ++i ){
    if(factor_array[i].size()== 0){
        factor_array[i].push_back({i , 1});
        for( int j = 1LL*2*i ; j < N ; j+= i  ){
            int cnt = 0 ;
            int x  = 1LL*j;
            while(x%i == 0 )
                ++cnt , x = x/i;  
            factor_array[j].push_back({i , cnt });
        }
    }
 }
 Inv_array[0] = Inv_array[1] = 1;
 for( int i = 2 ; i<2000000 ; ++i )
    Inv_array[i] = (mod - (((mod/i)*1LL*Inv_array[mod%i])%mod))%mod;

}



 vector<int>adj_list[N];
 int started_time[N] , ending_time[N] ,  flatten_array[N] , tree_lvl[N];
 const int lca_size = 20;
 int lca_array[N][lca_size];
 int timer = 1;


 void dfs( int node , int par = -1  , int lvl = 0 ){
     tree_lvl[node] = lvl;
     started_time[node] = timer;
     lca_array[node][0] = par;
     flatten_array[timer] = node;
     ++timer;

     for( auto child : adj_list[node]){
        if( child != par )
            dfs( child , node , lvl + 1);
     }

     flatten_array[timer] = node;
     ending_time[node] = timer;
     ++timer;
 }

 void __init__lca(int n ){
     for(int bits = 1 ; bits<lca_size ; ++bits ){
        for( int node = 1 ; node <=n ; ++node ){
            if(lca_array[node][bits-1] != -1 ){
                lca_array[node][bits] = lca_array[lca_array[node][bits-1]][bits-1];
            }
        }
     }
 }


 int get_lca( int a , int  b ){

 if(tree_lvl[a] > tree_lvl[b])
    swap(a , b );

 int d = tree_lvl[b] - tree_lvl[a];
 int bits = 0 ;
 while(d){
    if(d&1)
        b = lca_array[b][bits];
    d >>= 1;
    bits += 1;
 }
 if(a == b )
    return a;

 for( int bits = lca_size-1 ; bits>=0 ; --bits ){
    if(lca_array[a][bits] != -1 && (lca_array[a][bits] != lca_array[b][bits]))
        a = lca_array[a][bits] , b = lca_array[b][bits];

 }
 return lca_array[a][0];
 }


const int Block_size = 1200;
struct Query_node{
int l, r , idx , lca ;
bool flag;
 };

Query_node Q[N];

bool comp( Query_node a, Query_node b ){

	int x = a.l/Block_size;
	int y = b.l/Block_size;

	if(x != y)
	return x < y;

	return x % 2 ? a.r < b.r : a.r > b.r;

}


int feq_node[N];
int feq_element[N];
int node_val[N];
long long int res = 1;


void add(int node)
{
	node = flatten_array[node];
	feq_node[node]++;
	if(feq_node[node] == 1)
	{
		int ele = node_val[node];
		for(auto d  : factor_array[ele])
		{
			int pre = feq_element[d.first];
			feq_element[d.first] += d.second;
			int curr = feq_element[d.first];

			res = (res * 1LL * (Inv_array[pre + 1])) % mod;
			res = (res * 1LL * (curr + 1)) % mod;
		}
	}
	else
	{
		int ele = node_val[node];
		for(auto d : factor_array[ele])
		{
			int pre = feq_element[d.first];
			feq_element[d.first] -= d.second;
			int curr = feq_element[d.first];

			res = (res * 1LL * (Inv_array[pre + 1])) % mod;
			res = (res * 1LL * (curr + 1)) % mod;
		}
	}
}

void remove(int node)
{
	node = flatten_array[node];
	feq_node[node]--;

	if(feq_node[node] == 1)
	{
		int ele = node_val[node];
		for(auto d : factor_array[ele])
		{
			int pre = feq_element[d.first];
			feq_element[d.first] += d.second;
			int curr = feq_element[d.first];

			res = (res * 1LL * (Inv_array[pre + 1])) % mod;
			res = (res * 1LL * (curr + 1)) % mod;
		}
	}
	else{
		int ele = node_val[node];
		for(auto d : factor_array[ele])
		{
			int pre = feq_element[d.first];
			feq_element[d.first] -= d.second;
			int curr = feq_element[d.first];

			res = (res * 1LL * (Inv_array[pre + 1])) % mod;
			res = (res * 1LL * (curr + 1)) % mod;
		}
	}
}



int addLCA(int lca){
	int newRes = res;
	int ele = node_val[lca];

	for(auto d : factor_array[ele]){
		int pre = feq_element[d.first];
		int curr = pre + d.second;

		newRes = (newRes * 1LL * (Inv_array[pre + 1])) % mod;
		newRes = (newRes * 1LL * (curr + 1)) % mod;
	}

	int x = newRes - res;
	if(x < 0) x +=mod;
	return x;
}


void __reset__(int n ){

    for( int i = 0  ; i<n+1 ; ++i ){
       adj_list[i].clear();
        started_time[i] = 0;
        ending_time[i] = 0;
        for(int j = 0  ; j<lca_size ; ++j )
            lca_array[i][j] = -1;

        feq_node[i] = 0;
        feq_element[i] = 0;
    }


}



int main( void ){

__factor__();

int n, q, a, b , t;
scanf("%d",&t);
while(t--){
    scanf("%d",&n);
    __reset__(n);
    timer = 1;
    res = 1;
    for(int i = 1 ; i<n ; ++i ){
        scanf("%d%d",&a,&b);
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }
    for(int i =1 ; i<=n ; ++i )
        scanf("%d",node_val + i );
    dfs(1 , -1 , 0 );
    __init__lca(n);

    scanf("%d",&q);
    for( int i =1 ; i<=q; ++i ){
        scanf("%d%d",&a,&b);
        if(started_time[a] > started_time[b])
            swap(a , b );

        int lca_node = get_lca(a , b );
        if(lca_node ==  a ){
            Q[i].l = started_time[a];
            Q[i].r = started_time[b];
            Q[i].idx = i ;
            Q[i].lca = lca_node;
            Q[i].flag = 0 ;
        }else{

            Q[i].l = ending_time[a];
            Q[i].r = started_time[b];
            Q[i].idx = i ;
            Q[i].lca = lca_node;
            Q[i].flag = 1 ;

        }
    }

    sort(Q+1 , Q+1 + n , comp);
    int ans[n+1];
    int ML = 1;
    int MR = 0 ;
    for( int i =1 ; i<=q; ++i ){
        int L = Q[i].l;
        int R = Q[i].r;
        int idx = Q[i].idx;
        int lca_ndoe = Q[i].lca;
        bool flag = Q[i].flag;

        	while(MR < R)
			MR++ , add(MR);

			while(ML > L)
			ML-- , add(ML );

			while(MR > R)
			remove(MR) , MR--;

			while(ML < L)
			remove(ML) , ML++;

			ans[idx] = res;
			if(flag){
				ans[idx] += addLCA(lca_ndoe);
				if(ans[idx] >= mod)
				ans[idx] -= mod;
			}
    }

    for(int i =1 ; i<=q ; ++i )
        cout<<ans[i]<<endl;
}
return 0;
}

