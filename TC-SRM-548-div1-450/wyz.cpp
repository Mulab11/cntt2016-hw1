// BEGIN CUT HERE

// END CUT HERE
#line 5 "KingdomAndDice.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn=55;

class KingdomAndDice{
	int cnt[maxn];
	int dp[maxn*maxn],f[maxn*maxn];
	int n,m;
	public:
	double newFairness(vector <int> firstDie, vector <int> secondDie, int X){
		sort(firstDie.begin(),firstDie.end());
		sort(secondDie.begin(),secondDie.end());
		n=firstDie.size();m=secondDie.size();
		int p=n,s=0;
		for (int i=m-1;i>=0;--i){
			while (p&&firstDie[p-1]>secondDie[i]) --p;
			cnt[i+1]=X-secondDie[i]-(n-p)-(m-i-1);
			s+=(n-p);
		}
		for (int i=1;i<m;++i) cnt[i]-=cnt[i+1];
		while (p&&firstDie[p-1]>0) --p;
//		for (int i=1;i<=m;++i) printf("%d ",cnt[i]);puts("");
//		printf("%d\n",s);
		int top=m*p;
		memset(dp,1,sizeof(dp));
		dp[0]=0;
		for (int i=1;i<=m;++i){
			memset(f,1,sizeof(f));
			for (int j=0;j<=top;++j)
				for (int k=0,to,val;k<=cnt[i]&&(to=i*k+j)<=top&&(val=dp[j]+k)<=p;++k)
					f[to]=min(f[to],val);
			memcpy(dp,f,sizeof(f));
//			for (int i=0;i<top;++i) printf("%d ",dp[i]);puts("");
		}
		int res=s;
		for (int i=s;i<=top+s;++i)if (dp[i-s]<=p)
			if (abs(i*2-n*m)<abs(res*2-n*m)) res=i;
		return 1.0*res/n/m;
	}
};
