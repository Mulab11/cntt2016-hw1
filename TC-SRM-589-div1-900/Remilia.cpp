// by ξ
// program sky  :)

#include <vector>
#include <stdio.h>
#include <cassert>
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

int n,m,A[333],B[333],C[333],dp[333][2];

int Main(){
	int ans=1e9;
	if(m<=17){
		// 枚举前m位
		rep(mask,0,1<<m){
			// 求出新串
			For(i,1,n)B[i]=(mask>>((i-1)%m)&1)^A[i];
			// dp计算最少的变成新串的步数
			For(i,1,n){
				// 单位翻转
				dp[i][0]=dp[i-1][0]+B[i];
				dp[i][1]=dp[i-1][1]+!B[i];
				// 成段翻转
				if(i==n || i%m==0){
					dp[i][0]=min(dp[i][0],dp[i][1]+1);
					dp[i][1]=min(dp[i][1],dp[i][0]+1);
				}
			}
			ans=min(ans,dp[n][0]);
		}
	}else{
		int T=n/m;
		// 枚举每个前缀是否反转
		rep(mask,0,1<<T){
			int flag=0;
			// 求出反转之后的串
			dto(i,n,1){
				if(i%m==0)flag^=mask>>(i/m-1)&1;
				B[i]=A[i]^flag;
			}
			// 每个剩余类决定一个颜色
			flag=__builtin_popcount(mask);
			rep(i,0,m)C[i]=0;
			For(i,1,n)C[(i-1)%m]+=B[i];
			rep(i,0,m)flag+=min(C[i],n/m+(i<n%m)-C[i]);
			ans=min(ans,flag);
		}
	}
	return ans;
}

struct FlippingBitsDiv1{
	int getmin(vector <string> S, int M){
		for(auto ss:S)for(auto c:ss)A[++n]=c=='1';
		m=M;
		return Main();
	}
};