#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int u[4][2]={1,0,0,1,-1,0,0,-1};
vector<string> a;
bool vis[55][55];
int n,m,ax,ay,bx,by,stp[55][55];
int dfs(int x,int y){
	vis[x][y]=1;
	int maxx=0;
	for(int i=0;i<4;i++){
		int tx=x+u[i][0],ty=y+u[i][1];
		if(tx<0||ty<0||tx>=n||ty>=m||a[tx][ty]=='#'||vis[tx][ty]) continue;
		stp[tx][ty]=stp[x][y]+1;
		maxx=max(maxx,dfs(tx,ty));
	}
	return maxx+1;
}
bool check(int x,int y){
	memset(vis,0,sizeof(vis));
	memset(stp,0,sizeof(stp));
	vis[x][y]=1;
	int cnt=0;
	for(int i=0;i<4;i++){
		int tx=x+u[i][0],ty=y+u[i][1];
		if(tx<0||ty<0||tx>=n||ty>=m||a[tx][ty]=='#') continue;
		stp[tx][ty]=1;
		if(dfs(tx,ty)>=3) cnt++;//计算可以延伸长度为3的点的个数 
	}
	return cnt>=3&&(stp[ax][ay]-stp[bx][by]>=2);//判判断当前点与A,B距离关系 
}

class GameInDarknessDiv1{
public:
	string check(vector<string> field){
		a=field;n=a.size();m=a[0].size();
		bool isok=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(a[i][j]=='A') ax=i,ay=j;
				else if(a[i][j]=='B') bx=i,by=j;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++)
				if(a[i][j]!='#'&&::check(i,j)) {pisok=1;break;}
			if(isok) break;
		}
		if(isok) return "Bob wins";
		return "Alice wins";
	}
};
