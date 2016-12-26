// by ξ
// program sky  :)

#include <vector>
#include <stdio.h>
#include <cassert>
#include <cstring>
#include <algorithm>

#define Rin register int
#define oo (c=getchar())
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)
#define ALL(V) V.begin(),V.end()
#define SZ(A) (int(A.size()))
#define pb push_back
#define mk make_pair
#define x first
#define y second

using namespace std;

typedef double db;
typedef long long LL;
typedef pair<int ,int> PII;
typedef pair<db ,db> cpx;
typedef vector<int> VI;
typedef vector<PII> VII;

int n,L[55],sl[55],dp[55][33][33];

void upd(int i,int j,int k,int xx){
	// 更新dp值
	if(j>=0 && j<=26 && k>=0 && k<=26 && xx<dp[i][j][k])dp[i][j][k]=xx;
}

int sum(int l,int r){
	// 等差数列
	return (l+r)*(r-l+1)/2;
}

int Main(){
	// 前缀和
	For(i,1,n)sl[i]=sl[i-1]+L[i];
	// 初始化
	memset(dp,0x3f,sizeof dp);
	dp[0][0][0]=0;
	For(i,1,n)For(j,0,26)For(k,0,26)if(dp[i-1][j][k]<1e9){
		int xx=dp[i-1][j][k];
		// 枚举一下有几个结束以及开始
		For(p,0,26)For(q,0,26){
			int col=min(L[i],26)-p-q;
			// 不合法
			if(col<0 || p>j)continue;
			// 合法
			int rem=L[i]-p-q;
			if(col<=j-p){
				// 贪心算贡献
				if(j-p==0)
					upd(i,j-p+q,k+p,xx+sum(sl[i-1]+1,sl[i-1]+p)-sum(sl[i]-q+1,sl[i])+rem);
				else
					upd(i,j-p+q,k+p,xx+sum(sl[i-1]+1,sl[i-1]+p)-sum(sl[i]-q+1,sl[i]));
			}else{
				// 贪心算贡献
				int tt=col-(j-p);
				if(j-p>0)
					upd(i,j-p+q,k+p+tt,xx+sum(sl[i-1]+1,sl[i-1]+p)-sum(sl[i]-q+1,sl[i]));
				else
					upd(i,j-p+q,k+p+tt,xx+sum(sl[i-1]+1,sl[i-1]+p)-sum(sl[i]-q+1,sl[i])+rem-tt);
			}
		}
	}
	// 取最小值
	int ans=1e9;
	For(k,0,26)ans=min(ans,dp[n][0][k]);
	return ans;
}

struct StringWeight{
	int getMinimum(vector<int> L){
		n=SZ(L);
		For(i,1,n)::L[i]=L[i-1];
		return Main();
	}
};