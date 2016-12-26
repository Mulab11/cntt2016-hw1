#include <bits/stdc++.h>

#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
using namespace std;
const int maxn=65;
vector<ll>ans;
ll pw[maxn];
int out[maxn][maxn],inc[maxn][3],ava[maxn];
ll ex[maxn];

/*
逐位确定，每次贪心放最小的。
在能放的位里面每个挑一个最小的。
没动过的位里面挑出最小的几个。
*/

class BitwiseAnd{
public:
	vector<ll>lexSmallest(vector<ll>a,int N){
		int n=a.size();
		pw[1]=1;rep(i,2,60) pw[i]=pw[i-1]<<1;
		rep(i,0,n-1) rep(j,0,n-1) if (!(a[i]&a[j])) return ans;
		rep(i,0,n-1) rep(j,1,60) if (a[i]&pw[j]){
			if (*inc[j]==2) return ans;
			inc[j][++*inc[j]]=i;
		}
		rep(i,1,60){
			if (!*inc[i]) ava[++*ava]=i;
			else if (*inc[i]==1) out[inc[i][1]][++*out[inc[i][1]]]=i;
		}
		int need=N-n;
		rep(i,0,n-1) if (*out[i]<need) return ans;
		if (*ava<need*(need-1)/2) return ans;
		int zz=1;
		rep(i,0,n-1) ans.pb(a[i]);
		rep(i,1,need){
			rep(j,0,n-1) ex[i]+=pw[out[j][i]];
			rep(j,i+1,need) ex[i]+=pw[ava[zz]],ex[j]+=pw[ava[zz]],zz++;
			ans.pb(ex[i]);
		}
		sort(ans.begin(),ans.end());
		return ans;
	}
};
