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

const int N=105;
int m,num[10][10],b[N][N],from[N],vis[N],fa[N];
bool go[N],pre[N],con[N][N];

inline void add(int x,int y,int z){
	if(x==y) return;
	if(!con[x][y]) con[x][y]=1,b[x][y]=z; else b[x][y]=min(b[x][y],z);
}
int solve(int n){
	memset(go,0,sizeof(go));
	int ans=0;
	for(;;){
		memset(from,-1,sizeof(from));
		memset(vis,0,sizeof(vis));vis[0]=-1;
		for(int i=1;i<=n;i++){
			if(go[i]) continue;
			for(int j=0;j<=n;j++){
				if(go[j]||!con[j][i]) continue;
				if(from[i]==-1||b[j][i]<b[from[i]][i]) from[i]=j;
			}
			if(from[i]==-1) return -1;
		}
		bool isok=0;
		for(int i=1;i<=n;i++){
			if(go[i]||vis[i]) continue;
			int k=i,st;
			while(!vis[k]) vis[k]=i,k=from[k];
			if(vis[k]!=i) continue;
			isok=1;st=k;ans+=b[from[k]][k];
			for(k=from[k];k!=st;k=from[k]) ans+=b[from[k]][k],go[k]=1;
			do{
				for(int j=0;j<=n;j++)
					if(!go[j]&&con[j][k]) add(j,st,b[j][k]-b[from[k]][k]);
				for(int j=0;j<=n;j++)
					if(!go[j]&&con[k][j]) add(st,j,b[k][j]);
				k=from[k];
			}while(k!=st);
			break;
		}
		if(!isok) break;
	}
	for(int i=1;i<=n;i++) if(!go[i]) ans+=b[from[i]][i];
	return ans;
}

class FoxTheLinguist{
public:
	int minimalHours(int n, vector<string> courseInfo){
		string c="";int cnt=0;
		for(int i=0;i<courseInfo.size();i++) c+=courseInfo[i];
		memset(con,0,sizeof(con));
		for(int i=0;i<n;i++) for(int j=0;j<10;j++) num[i][j]=++cnt;
		for(int i=0;i<c.size();i+=12)
			add(num[c[i]-'A'][c[i+1]-'0'],num[c[i+4]-'A'][c[i+5]-'0'],c[i+7]*1000+c[i+8]*100+c[i+9]*10+c[i+10]-'0'*1111);
		for(int i=0;i<n;i++) for(int j=9;j;j--) add(num[i][j],num[i][j-1],0);
		for(int i=0;i<n;i++) add(0,num[i][0],0);
		return solve(n*10);
	}
};
