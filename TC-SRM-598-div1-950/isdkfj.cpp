#include <bits/stdc++.h>

using namespace std;

int fst[55],to[105],nxt[105],tt,f[55];

void dfs(int x,int fa){
	f[x]=0;int tmp=0;
	for(int i=fst[x];i;i=nxt[i])if(to[i]!=fa){
		dfs(to[i],x);
		if(!f[to[i]])tmp=1,++f[x];//至多一个子树不放 
		else f[x]+=f[to[i]];
	}
	f[x]-=tmp;//不需要TPS的子树不用放 
}

class TPS {
public:
	int minimalBeacons(vector <string> linked) {
		for(int i=0;i<linked.size();++i)
			for(int j=0;j<linked[i].size();++j)
			if(linked[i][j]=='Y'){
				nxt[++tt]=fst[i];fst[i]=tt;to[tt]=j;
			}
		if(linked.size()==1)return 0;
		int ret=linked.size();
		for(int i=0;i<linked.size();++i){//枚举根 
			dfs(i,-1);
			ret=min(ret,f[i]+1);
		}
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
