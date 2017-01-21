// BEGIN CUT HERE

// END CUT HERE
#line 5 "StringWeight.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=103;

class StringWeight{
	int a[maxn],n;
	int dp[maxn][maxn][maxn];
	void doit(){
		dp[0][0][0]=0;
		int s=0;
		for (int i=1;i<=n;s+=a[i++])
			for (int j=1;j<=26;++j)for (int k=0;k<=j;++k){
//				printf("%d %d\n",j,k);
				for (int x=0;x<=j;++x)for (int y=max(k+x-j,0);y<=k;++y){
					if (j-k+y<min(a[i],26)) continue;
					if (max(x,y)>a[i]) continue;
					int z=max(max(x+y-a[i],k-j+x),0);
					int X=x-z,Y=y-z;
					if (i==2&&j==26&&k==24&&x==0&&y==0) printf("%d %d %d %d",dp[i-1][j-x][k-y],X,Y,z);
//					printf("%d %d %d %d %d\n",i,j,k,x,y);
					dp[i][j][k]=min(dp[i][j][k],dp[i-1][j-x][k-y]+s*Y+(1+Y)*Y/2-(s+a[i])*X+(X-1)*X/2+(a[i]-X-Y-z)*(min(a[i],26)==X+Y+z));
				}
//				printf("%d %d\n",j,k);
			}
//		puts("ok");
	}
	public:
	int getMinimum(vector <int> L){
		n=L.size();
		for (int i=1;i<=n;++i) a[i]=L[i-1];
		memset(dp,63,sizeof(dp));
		doit();
		int ret=1e9;
		for (int i=1;i<=26;++i) ret=min(ret,dp[n][i][i]);
//		printf("%d\n",dp[2][26][24]);
//		for (int i=1;i<=26;++i) printf("%d ",dp[n][i][i]);puts("");
		return ret;
	}
};
