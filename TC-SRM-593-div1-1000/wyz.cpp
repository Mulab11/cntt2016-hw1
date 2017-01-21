// BEGIN CUT HERE

// END CUT HERE
#line 5 "WolfDelaymasterHard.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=(2e6)+6;
const int P=1000000007;

int a[maxn],n;
int pre0[maxn],nxt0[maxn],nxt1[maxn];
int dp[maxn];

class WolfDelaymasterHard{
	public:
	int countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd){
		if ((n=N)&1) return 0;
		memset(a,-1,sizeof(a));
		for(int i=0,x=w0;i<wlen;++i,x=((ll)x*wmul+wadd)%n) a[x+1]=0;
		for(int i=0,x=o0;i<olen;++i,x=((ll)x*omul+oadd)%n) a[x+1]=1;

		pre0[0]=0;nxt0[n+1]=nxt1[n+1]=n+1;
		for (int i=1;i<=n;++i) pre0[i]=a[i]==0?i:pre0[i-1];
		for (int i=n;i>=1;--i) nxt0[i]=a[i]==0?i:nxt0[i+1],nxt1[i]=a[i]==1?i:nxt1[i+1];

		memset(dp,0,sizeof(dp));
		dp[0]=1;dp[1]=P-1;
		for (int i=0;i<(n>>1);++i){
			int j=i<<1^1;
			if (a[j]==1){(dp[i+1]+=dp[i])%=P;continue;}
			for (int l=1;j+l*2-1<=n;){
				if (nxt1[j]<j+l) break;
				if (pre0[j+l*2-1]>=j+l){l=pre0[j+l*2-1]-j+1;continue;}
				(dp[i+l]+=dp[i])%=P;
				l=min(nxt1[j]-j,(nxt0[j+l]-j)>>1)+1;
				(dp[i+l]+=P-dp[i])%=P;
			}
			(dp[i+1]+=dp[i])%=P;
		}
		return dp[n>>1];
	}
};

//this is for test
/*
int main(){
	WolfDelaymasterHard test;
	printf("%d\n",test.countWords(2000000, 1940508, 1945440, 469448, 1465, 638965, 1876667, 1421470, 1365801));
//	test.run_test(-1);
	return 0;
}
*/
//test end
