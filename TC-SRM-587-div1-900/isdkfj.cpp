#include <bits/stdc++.h>

using namespace std;

int n,m,g[55][55],w[55];

bool dfs(int x){//二分图染色 
	for(int i=0;i<n;++i)if(g[x][i]!=-1){
		if(w[i]!=-1){
			if(w[i]!=(w[x]^g[x][i]))return 0;//奇环 
		}else {
			w[i]=w[x]^g[x][i];
			if(!dfs(i))return 0;
		}
	}
	return 1;
}

bool check(vector<string>mp){
	memset(g,-1,sizeof g);
	memset(w,-1,sizeof w);
	for(int k=0;k<m;++k)
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)
			if(mp[i][k]!='?'&&mp[i][k]==mp[j][k]){
				if(g[i][j]==1)return 0;//冲突 
				g[i][j]=0;
			} else if(mp[i][k]!='?'&&mp[j][k]!='?'&&mp[i][k]!=mp[j][k]){
				if(g[i][j]==0)return 0;//冲突 
				g[i][j]=1;
			}
	for(int i=0;i<n;++i)if(w[i]==-1){
		w[i]=0;
		if(!dfs(i))return 0;
	}
	return 1;
}

class ThreeColorability {
public:
	vector <string> lexSmallest(vector <string> cells) {
		n=cells.size();m=cells[0].size();
		for(int i=0;i<m;++i)
			if(cells[0][i]=='?'){
				cells[0][i]='N';
				if(check(cells))continue;
				cells[0][i]='Z';
			}//填第一行 
		bool ans=check(cells);
		for(int i=1;i<n&&ans;++i){
			bool flag=1;
			for(int j=0;j<m;++j)if(cells[i][j]!='?'){
				flag=0;//找到一个填过的判断是否与第一行相同 
				if(cells[i][j]!=cells[0][j]){
					for(int k=0;k<m;++k)
					if(cells[i][k]=='?')cells[i][k]=cells[0][k]=='N'?'Z':'N';
					else if(cells[i][k]==cells[0][k]){ans=0;break;}//填上 
				}else {
					for(int k=0;k<m;++k)
					if(cells[i][k]=='?')cells[i][k]=cells[0][k];
					else if(cells[i][k]!=cells[0][k]){ans=0;break;}//填上 
				}
				break;
			}
			if(flag){//全是问号 
				if(cells[0][0]=='N')for(int k=0;k<m;++k)cells[i][k]=cells[0][k];
				else for(int k=0;k<m;++k)cells[i][k]=cells[0][k]=='N'?'Z':'N';//找字典序最小的 
			}
		}
		if(!ans)cells.clear();//不合法 
		return cells;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
