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

const int N=55;
struct node{
	int to,NEXT;
}p[N*N*4];
int n,m,tot,NEXT[N],head[N],a[N][N],col[N];
bool vis[N],isok,go[N][N];
vector<string> ans;

int find(int x){
	if(NEXT[x]!=x) NEXT[x]=find(NEXT[x]);
	return NEXT[x];
}
void add(int x,int y){
	p[++tot]=(node){y,head[x]};head[x]=tot;
	p[++tot]=(node){x,head[y]};head[y]=tot;
}
void dfs(int x,int c){
	if(vis[x]){
		if(c!=col[x]) isok=0;
		return;
	}else vis[x]=1,col[x]=c;
	for(int i=head[x];i;i=p[i].NEXT)
		dfs(p[i].to,c^1);
}
//dfs染色并判二分图 
void pre(){
	tot=0;isok=1;
	memset(head,0,sizeof(head));
	memset(vis,0,sizeof(vis));
	memset(go,0,sizeof(go));
	for(int i=0;i<m;i++) NEXT[i]=i;
}

class ThreeColorability{
public:
	vector <string> lexSmallest(vector <string> cells){
		ans=cells;
		n=cells.size();m=cells[0].size();
		pre();
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(cells[i][j]=='N') a[i][j]=0; 
				else if(cells[i][j]=='?') a[i][j]=-1;
				else a[i][j]=1;
		for(int i=1;i<n;i++)
			for(int j=0;j<m;j++)
				for(int k=j+1;k<m;k++)
					if((~a[i][j])&&(~a[i][k])){
						if(a[i][j]^a[i][k])
							go[j][k]=go[k][j]=1;
						else NEXT[find(j)]=find(k);
					}
		for(int i=0;i<m;i++)
			for(int j=i+1;j<m;j++)
				if(go[i][j]) add(find(i),find(j));
		//根据行上的情况，要相同的用并查集连起来，不相同的连边（转化到连通块上） 
		for(int i=0;i<m;i++)
			if(~a[0][i]) dfs(find(i),a[0][i]);
		for(int i=0;i<m;i++)
			if(!vis[find(i)]) dfs(find(i),0);
		//分别处理不是？和？且未被固定的 
		if(!isok){ans.clear();return ans;}
		for(int i=0;i<m;i++)
			a[0][i]=col[find(i)];
		for(int i=1;i<n;i++){
			bool vis[2]={0};
			for(int j=0;j<m;j++)
				if(~a[i][j]) vis[a[i][j]^a[0][j]]=1;
			if(!vis[0]&&!vis[1]){
				if(a[0][0]) vis[1]=1; else vis[0]=1;
			}
			if(vis[0]) for(int j=0;j<m;j++) a[i][j]=a[0][j];
			else for(int j=0;j<m;j++) a[i][j]=a[0][j]^1;
		}
		for(int i=0;i<n;i++)for(int j=0;j<m;j++)
			if(a[i][j]) ans[i][j]='Z'; else ans[i][j]='N';
		//根据列上信息构造答案 
		return ans;
	}
};
