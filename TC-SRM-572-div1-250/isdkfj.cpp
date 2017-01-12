#include <bits/stdc++.h>

using namespace std;

int g[55][55],cnt[55],vis[55],n,sum;
char v[55];

void dfs(int x){//搜联通块 
	vis[x]=1;++cnt[v[x]-'a'];++sum;
	for(int i=0;i<n;++i)if(g[x][i]&&!vis[i])dfs(i);
}

class NewArenaPassword {
public:
	int minChange(string oldPassword, int K) {
		n=oldPassword.size();
		for(int i=0;i<n;++i)v[i]=oldPassword[i];
		for(int i=0,j=n-K;i<K;++i,++j)g[i][j]=g[j][i]=1;//i和j一样 
		int ans=0;
		for(int i=0;i<n;++i)if(!vis[i]){
			memset(cnt,0,sizeof cnt);
			sum=0;dfs(i);
			ans+=sum;
			int ma=0;
			for(int j=0;j<26;++j)ma=max(ma,cnt[j]);//找出现次数最多的 
			ans-=ma;
		}
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
