//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<bitset>
#include<string>
#include<cstdio>
#include<cctype>
#include<cassert>
#include<cstdlib>
#include<cstring>
#include<sstream>
#include<iostream>
#include<algorithm>

#define For(i,x,y) for (int i=x;i<y;i++)
#define pb push_back
#define mp make_pair
#define fi first
#define se second

#define dprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;

typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> Vi;
typedef vector<string> Vs;

const int N=50+19;

struct item{
	int x;
	ll c;
	bool operator < (const item &B) const {return x<B.x;}
} S[N],__S[N];
Vi V;
int n,m;
ll l,r,res=-1;

bool check(ll num){
	int c=0;
	memcpy(S,__S,sizeof(__S));
	For(i,0,n){	//贪心验证
		ll now=num,tmp;
		while (c<m&&now&&V[i]>=S[c].x){
			tmp=min(now,S[c].c);
			now-=tmp;
			S[c].c-=tmp;
			if (S[c].c==0) c++;
		}
	}
	return c==m;
}

class SpaceWarDiv1{
public:
	ll minimalFatigue(Vi A,Vi B,vector<ll> C){
		V=A;
		n=V.size();
		m=B.size();
		For(i,0,m) S[i]=(item){B[i],C[i]};
		sort(S,S+m);
		sort(V.begin(),V.end());
		memcpy(__S,S,sizeof(S));
		l=0,r=m*ll(1e14);
		while (l<=r){	//二分答案
			ll mid=(l+r>>1);
			if (check(mid)) res=mid,r=mid-1;else l=mid+1;
		}
		return res;
	}
} T;