// BEGIN CUT HERE

// END CUT HERE
#line 5 "CuttingBitString.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn=55;

class CuttingBitString {
	int n;
	int dp[maxn][maxn];
	bool valid[maxn][maxn];
	set<string> s;
	public:
	int getmin(string S){
		n=S.size();
		string tmp="1";
		for (;tmp.size()<=n;){
			s.insert(tmp);
			string last=tmp;
			tmp="";
			int k=0;
			for (int j=last.size()-1;j>=0;--j){
				k=k+5*(last[j]-48);
				tmp=((char)(48+(k&1)))+tmp;
				k>>=1;
			}
			while (k){
				tmp=((char)(48+(k&1)))+tmp;
				k>>=1;
			}
//			cout<<tmp<<endl;
		}
		memset(valid,0,sizeof(valid));
		for (int i=1;i<=n;++i){
			string st="";
			for (int j=i;j<=n;++j){
				st=st+S[j-1];
				if (s.find(st)!=s.end()) valid[i][j]=1;
			}
		}
		memset(dp,1,sizeof(dp));
		for (int len=0;len<n;++len)
			for (int i=1,j;(j=i+len)<=n;++i)if (!valid[i][j])
				for (int k=i;k<j;++k)
					dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
			else dp[i][j]=1;
		return dp[1][n]>n?-1:dp[1][n];
	}
};
