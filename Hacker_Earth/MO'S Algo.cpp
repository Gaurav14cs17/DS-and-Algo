#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll rn,n;
 ll arr[100001];
ll block[1000][2];
ll find_right(ll index)
{
    
    ll block_id = index/rn;
    ll flag = 0;
    if(block[block_id][1]>=1)
    {
        for(ll i=index;i<block_id*rn;i++)
        {
            if(arr[i]==1){
             return i;
                flag = 1;
                break;}
        }            
    }
    if(flag==0)
    {
        block_id++;
        while(!block[block_id][1]&&block_id<=(rn+1))
            block_id+=1;
       
        if(block_id<=(rn+1))
        {
            ll index1 = block_id*rn;
            for(ll i =index1;i<=n;i++)
            {
                if(arr[i]==1){
                return i;
                break;}
            }
        }
    }   
    return -1;
}
ll find_left(ll index)
{
    ll block_id = index/rn;
    ll flag = 0;
    if(block[block_id][1]>=1)
    {
        for(ll i=index;i>=(block_id-1)*rn;i--)
        {
            if(arr[i]==1){
                flag = 1;
                return i;
                break;}
        }            
    }
    if(flag==0)
    {
        block_id--;
        while(!block[block_id][1]&&block_id>=0)
            block_id-=1;
        if(block_id>=0)
        {
            ll index1 = block_id*rn;
            for(ll i=index1;i<=n;i++)
            {
                if(arr[i]==1){
                return i;
                break;}
            }
        }
    }
    return -1;
}
void update(ll index)
{
    if(arr[index]==0)
    {
        arr[index] = 1;
        block[index/rn][1]++;
        block[index/rn][0]--;
    }
}
int main()
{
	 ios_base::sync_with_stdio(false);
	  cin.tie(NULL);
	   cout.tie(NULL);
	ll m,block_id,type,value,ans1,ans2,i,q;
    cin>>n>>q;
    rn = sqrt(n);
    for(i=0;i<=rn;i++)
       block[i][0] = block[i][1] = 0;
    for(i=0;i<n;i++)
    cin>>arr[i];
    block_id=-1;
    for(i=0;i<n;i++)
    {
        if(i%rn==0)
          block_id++;
        if(arr[i]==0)
           block[block_id][0]++;
        else
           block[block_id][1]++; 
    }
    while(q--)
    {
        cin>>type>>value;
        if(type==0)
        {
            ans1 = find_left(value);
            ans2 = find_right(value);
            cout<<ans1<<" "<<ans2<<endl;
        }
        else
        {
            update(value);
        }
    }
	return 0;
}
