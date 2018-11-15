#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define up upper_bound
#define vll vector<ll>
#define G vector<vll >
#define gg vector<int>
#define F first
#define S second
#define pll pair<ll,ll>
#define pii pair<int,int>
#define RFOR(i,a,b) for(int i=a;i>=b;i--)
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define endl '\n'
#define clr(a) memset(a,0,sizeof(a))
#define all(x) x.begin(),x.end()
#define rll read_ll();
#define gc getchar
#define pc putchar
typedef long long ll;
template<class T> inline T lcm(T a,T b){
        return a/gcd(a,b)*b;
}
template<typename T>
void debug(T first) {
    cout << first << "\n";
}
template<typename T, typename... Args>
void debug(T first, Args... args) {
    cout << first << " ";
    debug(args...);
}


ll read_ll(){char c=gc();while((c<'0'||c>'9')&&c!='-')c=gc();ll ret=0;int neg=0;if(c=='-')neg=1,c=gc();while(c>='0'&&c<='9'){ret=10*ret+c-48;c=gc();}return neg?-ret:ret;}

template<class T>int sz(T &x){return (int)x.size();}
const int MOD = 1e9+9;
const int ROOTN = 1e6+9;// 1e6+9
const int  N = 1e5+9;// 1e5+9
int strLen[N];
int Tree[4*N];
vector<string> str(N);

struct Node {
    Node* l, *r;
    int has,gind;
    bool end;
    Node():l(NULL), r(NULL), end(true), gind(MOD), has(0) {}
}*ZROOT[ROOTN];

struct Query {
    int l,r,i,ans;
    string x;
    Query(int ll,int rr, int ii, string xx):l(ll), r(rr), i(ii), x(xx), ans(MOD) {}
};


void trieInit(Node *root, string & str, int i, int LEN, int pos) {
    root->gind = min(pos,root->gind);
    root->has++;
    if(i == LEN-1)return;
    root->end = false;

    if(str[i+1]=='0') {
        if(root->l == NULL) root->l = new Node();
        trieInit(root->l, str, i+1, LEN, pos);
    } else {
        if(root->r == NULL) root->r = new Node();
        trieInit(root->r, str, i+1, LEN, pos);
    }
}
void trieInsert(string & str,int len,int ind) {
    Node* root = ZROOT[len];
    trieInit(root,str,0,len,ind);
}

int trieQuery(Node * root, string queryString, int i, int L, int l, int r) {

    if(root->end) return root->gind;
    if(root->has == 1) return root->gind;

    bool lacha = true,racha = true;
    if(!root->r) racha = false;
    else if(root->r->gind > r) racha = false;

    if(!root->l) lacha = false;
    else if(root->l->gind > r) lacha = false;

    if(L) {
        if(racha) return trieQuery(root->r, queryString, i, L-1, l, r);
        else return trieQuery(root->l, queryString, i, L-1, l, r);
    }

    if(queryString[i] =='0') {
        if(racha) return trieQuery(root->r, queryString, i+1, 0, l, r);
        else return trieQuery(root->l, queryString, i+1, 0, l, r);
    }
    else {
        if(lacha) return trieQuery(root->l, queryString, i+1, 0, l, r);
        else return trieQuery(root->r, queryString, i+1, 0, l, r);
    }
}

void init(int l, int r, int i) {
    if(l == r) {
        Tree[i] = strLen[l];
        return;
    }
    int mid = (l+r)/2;
    init(l, mid, 2*i);
    init(mid + 1, r, 2*i+1);
    Tree[i] = max(Tree[2*i], Tree[2*i+1]);
}

int query(int ql, int qr, int l, int r, int i) {
    if(ql == l and qr == r) return Tree[i];

    int mid = (l+r)/2;
    if(qr <= mid) return query(ql, qr, l, mid, 2*i);
    if(ql > mid) return query(ql, qr, mid+1, r, 2*i+1);

    return max(query(ql, mid, l, mid, 2*i), query(mid+1, qr, mid+1, r, 2*i+1));
}

int main() {
    FOR(i,0,ROOTN-1) 
        ZROOT[i] = new Node();
    int n,q;
    n = rll; q = rll;

    FOR(i,0,n-1) {
        string temp;
        cin >> temp;
        int len = sz(temp);
        str[i] = temp;
        strLen[i] = len;
    }

    init(0,n,1);

    vector<Query> QUERIES;
    FOR(i,0,q-1) {
        int l, r;
        string x;
        l = rll; r = rll; cin>>x;
        QUERIES.pb({l-1, r-1, i, x});
    }

    sort(all(QUERIES), [](Query &a,Query &b) { 
        return a.l > b.l; 
    });

    int li = n-1;
    FOR(i,0,q-1) {
        int &l = QUERIES[i].l, &r = QUERIES[i].r, &ANS = QUERIES[i].ans;
        string &x = QUERIES[i].x;

        for(;li>=l;li--) trieInsert(str[li], sz(str[li]), li);

        int maxlen = query(l, r, 0, n, 1);

        if(maxlen > sz(x)) {
            int lead = maxlen - sz(x);
            ANS = trieQuery(ZROOT[maxlen], x, 0, lead-1, l, r) + 1;
            continue;
        }
        FOR(i,0,sz(x)-1) if(x[i] == '0') {
            int j = sz(x) - i;
            if(ZROOT[j]->gind <= r) {
                ANS = trieQuery(ZROOT[j], x, i+1, 0, l, r) + 1;
                break;
            }
        }
        if(ANS != MOD) continue; 
        RFOR(i,sz(x)-1,0){
            int j = sz(x) - i;
            if(ZROOT[j]->gind <= r) {
                ANS = trieQuery(ZROOT[j], x, i+1, 0, l, r) + 1;
                break;
            }
        }
    }
    sort(all(QUERIES), [](Query &a,Query &b) { 
        return a.i < b.i; 
    });
    for(auto t: QUERIES) 
        printf("%d\n", t.ans);
}
