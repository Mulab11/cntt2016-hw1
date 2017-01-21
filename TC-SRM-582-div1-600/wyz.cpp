// BEGIN CUT HERE

// END CUT HERE
#line 5 "ColorfulBuilding.cpp"
#include <bits/stdc++.h>
#define ll long long
#define N 1505
#define P 1000000009

using namespace std;


class ColorfulBuilding{
	pair<int,int> tmp[N];
	int col[N],n,m;
	int dp[N][N],sdp[N];
	int last[N];
	public:
	int count(vector <string> color1, vector <string> color2, int L){
		n=0;
		for (int i=0;i<color1.size();++i)for (int j=0;j<color1[i].size();++j)col[++n]=color1[i][j]<<10;
		n=0;
		for (int i=0;i<color2.size();++i)for (int j=0;j<color2[i].size();++j)col[++n]^=color2[i][j];
		for (int i=1;i<=n;++i) tmp[i]=make_pair(col[i],i);
		sort(tmp+1,tmp+n+1);
		m=0;
		for (int i=1;i<=n;++i){
			if (i==1||tmp[i].first!=tmp[i-1].first) ++m;
			col[tmp[i].second]=m;
		}
		memset(sdp,0,sizeof(sdp));
		memset(dp,0,sizeof(dp));
		dp[0][0]=1;
		sdp[0]=1;
		memset(last,0,sizeof(last));
		for (int i=n;i;--i){
			int k=1;
			for (;last[col[i]]<n-i;++last[col[i]]) k=1LL*k*last[col[i]]%P;
//			printf("%d\n",k);
			for (int j=1;j<=L;++j) dp[j][col[i]]=1LL*dp[j][col[i]]*k%P;
			for (int j=L;j;--j){
//				printf("%d %d %d %d %d %d\n",i,j,sdp[j],sdp[j-1],dp[j-1][col[i]],dp[j][col[i]]);
				sdp[j]=(1LL*(n-i)*sdp[j]+sdp[j-1]-dp[j-1][col[i]]+dp[j][col[i]])%P;
				dp[j][col[i]]=(1LL*dp[j][col[i]]*(n-i+1)+sdp[j-1]-dp[j-1][col[i]])%P;
				
			}
			++last[col[i]];
			sdp[0]=dp[0][0]=0;
//			puts("");
		}
		return (sdp[L]+P)%P;
	}
};
/*
ColorfulBuilding test;
int main(){
	vector<string> a,b;
	a.push_back("abaaa");
	b.push_back("abaaa");
	printf("%d\n",test.count(a,b,2));
	return 0;
}*/
