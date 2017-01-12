#include <bits/stdc++.h>

using namespace std;

const int mo=1e9+7;
int n,m,f[55][55],g[55][55],p1[55],p2[55];
char mp[55][55];
int dp(){//DP
	memset(f,0,sizeof f);memset(g,0,sizeof g);
	//f:从大到小,g:从小到大 
	for(int i=1;i<=n;++i){
		p1[i]=0;p2[i]=m+1;
		for(int j=1;j<=m;++j)if(mp[i][j]=='B')p1[i]=j;
		for(int j=m;j>=1;--j)if(mp[i][j]=='W')p2[i]=j;
		if(p1[i]>p2[i])return 0;
	}
	for(int i=0;i<=m;++i)f[0][i]=1;
	for(int i=1;i<=n;++i)
		for(int j=m;j>=0;--j){
			f[i][j]=f[i][j+1];
			if(p1[i]<=j&&p2[i]>=j+1)//是否可行 
				if((f[i][j]+=f[i-1][j])>=mo)f[i][j]-=mo;
		}
	for(int i=0;i<=m;++i)g[0][i]=1;
	for(int i=1;i<=n;++i)
		for(int j=0;j<=m;++j){
			if(j)g[i][j]=g[i][j-1];
			if(p1[i]<=j&&p2[i]>=j+1)//是否可行 
				if((g[i][j]+=g[i-1][j])>=mo)g[i][j]-=mo;
		}
	int ret=(f[n][0]+g[n][m])%mo;
	for(int j=0;j<=m;++j){
		bool flag=1;
		for(int i=1;i<=n;++i)flag&=p1[i]<=j&&p2[i]>=j+1;
		if((ret-=flag)<0)ret+=mo;//扣掉重复计算的方案 
	}
	return ret;
}
int dp2(){
	p1[0]=0;
	for(int i=1;i<=n;++i){
		p1[i]=p1[i-1];
		if(!p1[i])for(int j=1;j<=m;++j)if(mp[i][j]=='B')p1[i]=1;
	}
	p2[n+1]=0;
	for(int i=n;i>=1;--i){
		p2[i]=p2[i+1];
		if(!p2[i])for(int j=1;j<=m;++j)if(mp[i][j]=='W')p2[i]=1;
	}
	int ret=0;
	for(int i=1;i<=n;++i)
		if(!p1[i]&&!p2[i+1])++ret;//扣掉总的重复计算的方案 
	return ret;
}

class TwoConvexShapes {
public:
	int countWays(vector <string> grid) {
		n=grid.size();m=grid[0].size();
		for(int i=1;i<=n;++i)	
			for(int j=1;j<=m;++j)mp[i][j]=grid[i-1][j-1];
		int ans=dp();
		ans=(ans-dp2()+mo)%mo;
		for(int i=1;i<=n;++i)//交换W跟B再做一次 
			for(int j=1;j<=m;++j)
			if(mp[i][j]=='B')mp[i][j]='W';
			else if(mp[i][j]=='W')mp[i][j]='B';
		ans=(ans+dp())%mo;
		ans=(ans-dp2()+mo)%mo;
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
