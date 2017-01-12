#include <bits/stdc++.h>

using namespace std;

int n,l[55],v[55];
bool g[55][55];
int dfs(int x){//匈牙利 
	if(v[x])return 0;
	v[x]=1;
	for(int i=0;i<n;++i)
	if(!g[i][i]&&g[x][i]){
		if(l[i]==-1||(dfs(l[i]))){
			l[i]=x;
			return 1;
		}
	}
	return 0;
}

class Incubator {
public:
	int maxMagicalGirls(vector <string> love) {
		n=love.size();
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)g[i][j]=love[i][j]=='Y';//建图 
		for(int k=0;k<n;++k)
			for(int i=0;i<n;++i)
				for(int j=0;j<n;++j)g[i][j]|=g[i][k]&&g[k][j];//传递闭包 
		memset(l,-1,sizeof l);
		int ret=0;
		for(int i=0;i<n;++i)//求最小路径覆盖 
		if(!g[i][i]){
			++ret;
			memset(v,0,sizeof v);
			ret-=dfs(i);
		}
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
