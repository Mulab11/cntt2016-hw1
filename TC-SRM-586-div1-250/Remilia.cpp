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
#define VI vector<int>
using namespace std;
const int maxn=55;
int ls[maxn],n,m,cnt[maxn<<1];

/*

xjb扫描线即可………………
上下eps暴力求也行……

*/


class PiecewiseLinearFunction{
public:
	int maximumSolutions(vector<int>Y){
		n=Y.size();
		rep(i,0,n-1) ls[i]=Y[i];
		sort(ls,ls+n);
		m=unique(ls,ls+n)-ls;
		rep(i,0,n-1) Y[i]=(lower_bound(ls,ls+m,Y[i])-ls)*2;
		rep(i,1,n-1){
			if (Y[i-1]==Y[i]) return -1;
			if (Y[i-1]>Y[i]) drp(j,Y[i-1],Y[i]+1) cnt[j]++;
				else rep(j,Y[i-1],Y[i]-1) cnt[j]++; 
		}
		cnt[Y[n-1]]++;
		int ans=0;
		rep(i,0,(m-1)*2) ans=max(ans,cnt[i]);
		return ans;
	}
};
