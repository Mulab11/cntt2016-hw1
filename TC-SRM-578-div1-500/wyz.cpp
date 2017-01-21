// BEGIN CUT HERE

// END CUT HERE
#line 5 "WolfInZooDivOne.cpp"
#include <bits/stdc++.h>
#define ll long long
#define P 1000000007

using namespace std;
string st;int stamp;
inline int get_char(){
	if (stamp==st.size()) return -1;
	return st[stamp++];
}
inline int read(){
	int ret=0;char ch=get_char();
	while (ch<'0'||ch>'9') ch=get_char();
	while ('0'<=ch&&ch<='9'){
		ret=ret*10-48+ch;
		ch=get_char();
	}
	return ret;
}
void Max(int &x,int y){if (y>x) x=y;}

const int maxn=305;

class WolfInZooDivOne{
	int l[maxn],m,to[maxn];
	int dp[maxn][maxn],n;
	public:
	int count(int N, vector <string> L, vector <string> R){
		n=N;
		st="";stamp=0;
		for (int i=0;i<L.size();++i) st+=L[i];
		m=0;
		while (stamp<st.size()) l[++m]=read()+1;
		st="";stamp=0;
		for (int i=0;i<R.size();++i) st+=R[i];
		for (int i=1;i<=n;++i) to[i]=i;
		for (int i=1;i<=m;++i) Max(to[l[i]],read()+1);
		memset(dp,0,sizeof(dp));dp[0][0]=1;
		int nowmx=0;
		for (int i=1;i<=n;++i){
			int tmp=nowmx;
			Max(nowmx,to[i]);
			for (int j=tmp;j>=i;--j) (dp[nowmx][j]+=dp[j][0])%=P;
			(dp[nowmx][0]+=dp[0][0])%=P;
			for (int j=i;j<=nowmx;++j) (dp[j][0]+=dp[j][i])%=P;
			(dp[0][0]+=dp[i][0])%=P;
//			printf("%d %d %d\n",dp[0][0],dp[5][0],dp[5][5]);
		}
		return dp[0][0];
	}
};
