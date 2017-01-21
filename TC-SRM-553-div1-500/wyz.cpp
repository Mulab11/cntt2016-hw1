// BEGIN CUT HERE

// END CUT HERE
#line 5 "TwoConvexShapes.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;
#define P 1000000007
#define inc(x,y) if(((x)+=(y))>=P)(x)-=P
#define dec(x,y) if(((x)-=(y))<0)(x)+=P

const int maxn=55;

class TwoConvexShapes {
	int r,c;
	void trans(int *dp,bool *valid){
		int sum=0;
		for (int i=0;i<=c;++i){
			inc(sum,dp[i]);
			if (valid[i]) dp[i]=sum;
			else dp[i]=0;
		}
//		for (int i=0;i<=c;++i) printf("%d ",dp[i]);puts("");
	}
	bool v0[maxn][maxn],v1[maxn][maxn];
	int f[maxn];
	public:
	int countWays(vector <string> grid){
		r=grid.size();
		c=grid[0].size();
		memset(v0,0,sizeof(v0));
		memset(v1,0,sizeof(v1));
		for (int i=0;i<r;++i){
			int lb=c,rb=-1,lw=c,rw=-1;
			for (int j=0;j<c;++j)
				if (grid[i][j]=='B') lb=min(lb,j),rb=max(rb,j);
				else if (grid[i][j]=='W') lw=min(lw,j),rw=max(rw,j);
			for (int j=rb+1;j<=lw;++j) v0[i][j]=1;
			for (int j=rw+1;j<=lb;++j) v1[i][j]=1;
		}
//		for (int i=0;i<r;++i,puts(""))for (int j=0;j<=c;++j) printf("%d ",(int)v0[i][j]);
		int ret=0;
		memset(f,0,sizeof(f));f[0]=1;
		for (int i=0;i<r;++i)trans(f,v0[i]);
		for (int i=0;i<=c;++i)inc(ret,f[i]);
//		printf("%d\n",ret);
		memset(f,0,sizeof(f));f[0]=1;
		for (int i=r-1;i>=0;--i)trans(f,v0[i]);
		for (int i=0;i<=c;++i)inc(ret,f[i]);
//		printf("%d\n",ret);
		memset(f,0,sizeof(f));f[0]=1;
		for (int i=0;i<r;++i)trans(f,v1[i]);
		for (int i=0;i<=c;++i)inc(ret,f[i]);
//		printf("%d\n",ret);
		memset(f,0,sizeof(f));f[0]=1;
		for (int i=r-1;i>=0;--i)trans(f,v1[i]);
		for (int i=0;i<=c;++i)inc(ret,f[i]);
//		printf("%d\n",ret);
		
		for (int i=0;i<r;++i){
			bool _a=1,_b=1,_c=1,_d=1;
			for (int j=0;j<i;++j) _a=_a&&v0[j][0],_b=_b&&v1[j][0];
			for (int j=i;j<r;++j) _c=_c&&v0[j][0],_d=_d&&v1[j][0];
			if (_a&&_d) dec(ret,1);
			if (_b&&_c) dec(ret,1);
		}
		
		for (int i=0;i<=c;++i){
			bool found=0;
			for (int j=0;j<r&&!found;++j)
				if (!v0[j][i]) found=1;
			if (!found) dec(ret,1);
			found=0;
			for (int j=0;j<r&&!found;++j)
				if (!v1[j][i]) found=1;
			if (!found) dec(ret,1);
		}
		return ret;
	}
};
