#include<bits/stdc++.h>
using namespace std;int n;const int MAXN=60;int id[MAXN][MAXN];vector<int>g[MAXN*MAXN];int col[MAXN*MAXN];const int dx[]={0,-1,-1,0,1,1};const int dy[]={-1,0,1,1,0,-1};bool dfs(int i,int c){if(col[i]==c)return 0;if(col[i]+c==0)return 1;col[i]=c;for(int k=g[i].size();k--;)if(dfs(g[i][k],-c))return 1;return 0;}class HexagonalBoard{public:int minColors(vector<string>mp){n = mp.size(); int cnt=0;for(int i=0;i!=n;++i)for(int j=0;j!=n;++j)if(mp[i][j]=='X')id[i+1][j+1]=++cnt;if(!cnt)return 0;for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)if(id[i][j])for(int k=0;k!=6;++k)if(id[i+dx[k]][j+dy[k]])g[id[i][j]].push_back(id[i+dx[k]][j+dy[k]]);int mx=0;for(int i=1;i<=cnt;++i)if((int)g[i].size()>mx)mx=g[i].size();if(mx==0)return 1;for(int i=1;i<=cnt;++i)if(!col[i]&&dfs(i,1))return 3;return 2;}} sol ;

string a[] = 	
{"XX-XX--"
,"-XX-XXX"
,"X-XX--X"
,"X--X-X-"
,"XX-X-XX"
,"-X-XX-X"
,"-XX-XX-"} ; 


vector<string> gt ; 
int main() { 
		for (int i = 0; i < 7; i ++) gt.push_back(a[i]) ; 
		printf("%d\n", sol.minColors(gt)) ; 
}

