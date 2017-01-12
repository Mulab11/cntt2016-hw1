#include <bits/stdc++.h>

using namespace std;

int g[26][26],w[26],v[26],mx;

void dfs(int x){
	v[x]=1;mx=max(mx,w[x]);//找最大的 
	for(int i=0;i<26;++i)if(g[x][i]&&!v[i])dfs(i);
}

class GooseTattarrattatDiv1 {
public:
	int getmin(string S) {
		for(int i=0;i<S.size();++i){
			int j=S.size()-i-1;
			if(j<=i)break;
			g[S[i]-'a'][S[j]-'a']=1;
			g[S[j]-'a'][S[i]-'a']=1;//建图 
		}
		for(int i=0;i<S.size();++i)++w[S[i]-'a'];//出现次数 
		int ret=S.size();
		for(int i=0;i<26;++i)if(!v[i]){
			mx=0;
			dfs(i);
			ret-=mx;
		}
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
