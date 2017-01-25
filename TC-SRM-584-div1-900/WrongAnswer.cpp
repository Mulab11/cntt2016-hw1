// FST:求最小树形图时vis[j]表示编号最小的能到j的点编号，但一开始初始化时写vis[0]=1导致和1出发的点混淆于是WA
#include <vector>
#include <string>
using namespace std;
class Solver{
private:
	int N,M;
	struct edge{int u,v,w;}E[1010];
	edge*fa[1010];
	int in[1010],del[1010],vis[1010];
public:
	void init(int n){N=n;M=0;}
	void link(int a,int b,int l){E[M++]=(edge){a,b,l};}
	int solve(){
		for(int i=0;i<=N;i++)del[i]=0;
		for(int s=0;;){
			for(int i=1;i<=N;i++)fa[i]=0,vis[i]=0;
			for(int i=0;i<M;i++)if(E[i].u!=E[i].v&&(!fa[E[i].v]||E[i].w<fa[E[i].v]->w))fa[E[i].v]=E+i;
			for(int i=1;i<=N;i++)if(!del[i]&&!fa[i])return-1;
			int g=0;vis[0]=-2;
			for(int i=1;i<=N&&!g;i++)if(!del[i]&&!vis[i]){
				int j=i;while(!vis[j])vis[j]=i,j=fa[j]->u;
				if(vis[j]==i)for(g=j;vis[g]!=-1;g=fa[g]->u)vis[g]=-1,g!=j?del[g]=1:1,s+=(in[g]=fa[g]->w);
			}
			if(!g){
				for(int i=1;i<=N;i++)if(!del[i])s+=fa[i]->w;
				return s;
			}
			for(int i=0;i<M;i++){
				if(vis[E[i].v]==-1)vis[E[i].u]!=-1?E[i]=(edge){E[i].u,g,E[i].w-in[E[i].v]},1:E[i].u=-1;
				else if(vis[E[i].u]==-1)E[i].u=g;
			}
			int j=0;for(int i=0;i<M;i++)if(E[i].u>-1)E[j++]=E[i];M=j;
		}
	}
}solver;
class FoxTheLinguist{
public:
	int id(int*s){return s[1]=='0'?0:(s[0]-'A')*9+s[1]-'0';}
	int num(int*s){int x=0;for(int i=0;i<4;i++)x=x*10+s[i]-'0';return x;}
	void add(int*s){solver.link(id(s),id(s+4),num(s+7));}
	int minimalHours(int n, vector <string> courseInfo){
		solver.init(9*n);
		for(int i=0;i<n;i++){
			solver.link(i*9+1,0,0);
			for(int j=2;j<=9;j++)solver.link(i*9+j,i*9+j-1,0);
		}
		int s[12],l=0;
		for(int i=0;i<courseInfo.size();i++)
			for(int j=0,x;j<courseInfo[i].length();j++)
				(x=courseInfo[i][j])==' '?add(s),l=0:s[l++]=x;
		add(s);
		return solver.solve();
	}
};
