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
int yp;
int a[maxn],use[maxn],n;
/*
贪心，枚举最大值，然后挑一个可以卡住的最小值，然后挑一个比这个最小值大的最小值。
*/
struct TeamContest{
	int worstRank(vector<int>sth){
		n=sth.size();
		yp=max(max(sth[0],sth[1]),sth[2])+min(min(sth[0],sth[1]),sth[2]);
		rep(i,3,n-1) a[i-2]=sth[i];
		n-=3;
		sort(a+1,a+n+1);
		int ans=1;
		drp(i,n,1){
			if (use[i]) continue;
			int j=1;
			while (j<i&&(use[j]||a[j]+a[i]<=yp)) j++;
			if (j==i) return ans;
			int k=j+1;
			while (k<i&&use[k]) k++;
			if (k==i) return ans;
			ans++,use[i]=use[j]=use[k]=1;
		}
		return ans;
	}
};
