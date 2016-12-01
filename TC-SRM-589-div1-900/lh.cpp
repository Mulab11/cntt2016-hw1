#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class FlippingBitsDiv1{
	static const int maxn=320;
	int dp[maxn][2],n,m,T;
	string s;
	
	int check1(int sta){
//		printf("sta=%d:\n",sta);
		int ret=0;
		for (int i=0;i<T;++i) if (sta&(1<<i)){
			if (i==0) ++ret;
			else if (~sta&(1<<(i-1))) ret+=2;
		}
		for (int i=0;i<m;++i){
			int cnt0=0,cnt1=0;
			for (int j=i,tr=1;j<n;j+=m,tr<<=1) if (sta&tr){
				if (s[j]=='0') ++cnt1;
				else ++cnt0;
			}
			else{
				if (s[j]=='0') ++cnt0;
				else ++cnt1;
			}
			ret+=min(cnt0,cnt1);
		}
//		printf("ans=%d\n",ret);
		return ret;
	}
	
	int check2(int sta){
		memset(dp,0x3f,sizeof(dp));
		dp[0][0]=0;
		dp[0][1]=1;
		int st=0;
		for (int i=1;i<=T;++i,st+=m){
			int tmp=0;
			for (int j=0;j<m;++j) if ((s[j+st]-'0')!=((sta>>j)&1)) ++tmp;
			dp[i][0]=min(dp[i-1][0],dp[i-1][1])+tmp;
			dp[i][1]=min(dp[i-1][0]+2,dp[i-1][1])+(m-tmp);
		}
		int tmp=0;
		for (int j=0;j+st<n;++j) if ((s[j+st]-'0')!=((sta>>j)&1)) ++tmp;
		return tmp+min(dp[T][0],dp[T][1]);
	}
	
	public:
		int getmin(vector<string> S, int M){
			for (auto &x:S) s+=x;
			n=s.length();
			m=M;
			T=n/M;
			int ans=1000000;
			if (T<M){ 
				for (int i=0;i<(1<<T);++i) ans=min(ans,check1(i));
			}
			else{
				for (int i=0;i<(1<<M);++i) ans=min(ans,check2(i));
			}
			return ans;
		}
};
