// BEGIN CUT HERE

// END CUT HERE
#line 5 "YetAnotherBoardGame.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=15;

class YetAnotherBoardGame{
	int n,m;
	int cnt,ans;
	bool a[maxn][maxn],b[maxn][2][maxn];
	bool c[maxn];
	void dfs(int u){
		if (u==n){
			for (int j=0;j<m;++j)if (b[u-1][0][j])return;
			if (ans<0||cnt<ans) ans=cnt;
			return;
		}
		int bakc[maxn],bakcnt=cnt;
		memcpy(bakc,c,sizeof(c));
		for (int k=0;k<2;++k){
			memcpy(c,bakc,sizeof(c));
			cnt=bakcnt;
			memcpy(b[u][0],b[u-1][1],sizeof(b[u][0]));
			memcpy(b[u][1],a[u+1],sizeof(a[u+1]));
			bool valid=1;
			for (int j=0;j<m;++j)if (b[u-1][0][j]){
				if (c[j]==(k^1)){valid=0;break;}
				if (j>0) b[u][0][j-1]^=1;
				if (j<m-1) b[u][0][j+1]^=1;
				b[u][1][j]^=1;
				b[u][0][j]^=k;
				c[j]=k;
				++cnt;
			}
			if (valid) dfs(u+1);
		}
	}
	public:
	int minimumMoves(vector <string> board){
		n=board.size();m=board[0].size();
		for (int i=0;i<n;++i)for (int j=0;j<m;++j) a[i][j]=board[i][j]=='W';
		ans=-1;
		for (int i=(1<<m)-1;i>=0;--i)
			for (int k=0;k<2;++k){
				memcpy(b[0][0],a[0],sizeof(a[0]));
				memcpy(b[0][1],a[1],sizeof(a[1]));
				memset(c,-1,sizeof(c));
				cnt=0;
				for (int j=0;j<m;++j)if ((i>>j)&1){
					if (j>0) b[0][0][j-1]^=1;
					if (j<m-1) b[0][0][j+1]^=1;
					b[0][1][j]^=1;
					b[0][0][j]^=k;
					c[j]=k;
					++cnt;
				}
				dfs(1);
			}
		return ans;
	}
};
