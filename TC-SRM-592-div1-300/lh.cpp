#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int pw[6]={1,3,9,27,81,243};

class LittleElephantAndBalls{
	static const int maxn=55,maxm=750;
	int dp[maxn][7][maxm];
	bool vis[maxn][7][maxm];
	int col[maxn],n;
	int use[maxn],fz[maxn];
	bool canuse[maxn];
	
	int make(int ss,int pos,int c,int len,int &nl,int &sta){
		for (int i=0;i<len;++i){
			use[i]=ss%3;
			ss/=3;
		}
		int ret=0;
		int tmp=0;
		for (int i=0;i<pos;++i){
			fz[i]=use[i];
			if (~tmp&(1<<fz[i])){
				tmp|=1<<fz[i];
				++ret;
			}
		}
		fz[pos]=c;
		tmp=0;
		for (int i=pos;i<len;++i){
			fz[i+1]=use[i];
			if (~tmp&(1<<fz[i+1])){
				tmp|=1<<fz[i+1];
				++ret;
			}
		}
		tmp=0;
		for (int i=0;i<=len;++i){
			canuse[i]=false;
			if (~tmp&(1<<fz[i])){
				tmp|=1<<fz[i];
				canuse[i]=true;
			}
		}
		tmp=0;
		for (int i=len;i>=0;--i){
			if (~tmp&(1<<fz[i])){
				tmp|=1<<fz[i];
				canuse[i]=true;
			}
		}
		nl=0;
		sta=0;
		for (int i=0;i<=len;++i) if (canuse[i]) sta=sta+fz[i]*pw[nl++];
		return ret;
	}
	
	int dfs(int now,int len,int sta){
		if (now==n) return 0;
		if (vis[now][len][sta]) return dp[now][len][sta];
		int a1,a2;
		for (int i=0;i<=len;++i){
			int tmp=make(sta,i,col[now],len,a1,a2);
//			if (now==0) printf("i=%d,col=%d,len=%d,a1=%d,a2=%d\n",i,col[now],len,a1,a2);
			dp[now][len][sta]=max(dp[now][len][sta],dfs(now+1,a1,a2)+tmp);
		}
//		printf("dp[%d][%d]:",now,len);
//		for (int i=0;i<len;++i) printf(" %d",use[i]);
//		printf ("  = %d\n",dp[now][len][sta]);
		vis[now][len][sta]=true;
		return dp[now][len][sta];
	}
	
	public:
		int getNumber(string S){
			n=S.length();
			for (int i=0;i<n;++i)
				col[i]=(S[i]=='R')?0:(S[i]=='G')?1:2;
			return dfs(0,0,0);
		}
};
