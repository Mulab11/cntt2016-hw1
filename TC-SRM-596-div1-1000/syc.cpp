#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <bitset>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <algorithm>
#define PR pair
#define fi first
#define se second
#define mk make_pair
#define pb push_back
#define For(i, x, y)   for(int i = (int)(x); i <= (int)(y); i++)
#define Rep(i, x, y)   for(int i = (int)(x); i <  (int)(y); i++)
#define Forn(i ,x, y)  for(int i = (int)(x); i >= (int)(y); i--)
#define CH	         ch = getchar()
#define Exit(...)    printf(__VA_ARGS__), exit(0)
#define dln()        fprintf(stderr,"\n")
#define dprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
typedef double	  db;
typedef long long ll;
typedef PR<int,int> PII;
const	int inf=2e9;
const	ll Inf=1e10;
const	int N=1000005;

inline int IN(){
	int x = 0, ch = 0, f = 0;
	for (CH; ch != -1 && (ch < 48 || ch > 57); CH) f = (ch == '-');
	for (; ch >= 48 && ch <= 57; CH) x = (x << 1) + (x << 3) + ch - '0';
	return f ? (-x) : x;
}

int Pow(int x, int y, int p){
	int a = 1;
	for (; y; y >>= 1, x = (ll)x * x %p) if(y & 1) a=(ll)a * x%p;
	return a;
}

int c[N];
ll f[N],g[N];

struct SparseFactorial{
	void work(ll p,ll s,ll q){
		memset(c,0,sizeof c);
		memset(g,0x3f,sizeof g);
		Rep(i,0,p*s){
			ll pp=(ll)i*i%p;
			for(ll j=pp;j<q;j+=p){
				if(c[j]>=s)continue;
				ll rem=(j-(ll)i*i%q+q)%q;
				if(!rem) c[j]+=s;else{
					while(rem%p==0&&c[j]<s){
						rem/=p;
						c[j]++;
					}
				}
				if(c[j]>=s) g[j]=(ll)i*i;
			}
		}
	}
	ll calc(ll n,ll p,ll rem){return n/p+(n%p>=rem);}
	ll getCount(ll L,ll R,ll P){
		ll gt=P;
		for(ll i=2;i<=P;i++)if(P%i==0){
			ll c=1;int s=0;
			while(P%i==0) P/=i,c*=i,s++;
			work(i,s,c);
			Rep(i,0,gt) f[i]=max(f[i],g[i%c]);
		}
		ll ans=0;
		Rep(i,0,gt){
			if(i == 67453)
				i = 67453;
			ll tmp=calc(R,gt,i)-calc(min(R,max(L-1,f[i])),gt,i);
			if(tmp) cerr << i << " " << tmp << endl;
			ans+=tmp;
		}
		return ans;
	}
}str;