// by ξ
// program sky  :)

#include <bits/stdc++.h>

#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)

using namespace std;

int ans,n,m,A[55][55],sum[55][55],dp[55][55][55][2];
bool done[55][55][55][2];

int calc(int i,int j,int p,int op){
	// A在(i,j),l,r如下描述
	if(i==n)return 0;
	// 记忆化
	if(done[i][j][p][op])return dp[i][j][p][op];
	done[i][j][p][op]=1;
	int &res=dp[i][j][p][op]=0,l,r;
	if(op==0)l=j+1,r=p;else l=p,r=j;
	// 不卡
	res=calc(i+1,j,j,1)+A[i+1][j];
	// 卡
	if(r-l<m-1){
		int tmp=1e9;
		// 向右走一步
		if(j==r && j<m)tmp=min(tmp,calc(i,j+1,l,1)+A[i][j+1]);
		// 向左走一段
		if(j==r && l>1)tmp=min(tmp,calc(i,l-1,r+1,0)+sum[i][r-1]-sum[i][l-2]);
		// 向右走一段
		if(j==l-1 && j>1)tmp=min(tmp,calc(i,j-1,r,0)+A[i][j-1]);
		// 向左走一步
		if(j==l-1 && r<=m)tmp=min(tmp,calc(i,r,l-1,1)+sum[i][r]-sum[i][l-1]);
		res=max(tmp,res);
	}
	return res;
}

struct WallGameDiv1{
	int play(vector<string> costs){
		n=costs.size();
		m=costs[0].size();
		For(i,1,n)For(j,1,m){
			A[i][j]=costs[i-1][j-1]-48;
			sum[i][j]=sum[i][j-1]+A[i][j];
		}
		int ans=1e9;
		For(i,1,m)
			ans=min(ans,A[1][i]+calc(1,i,i,1));
		return ans;
	}
};