#include <vector>
#include <string>
#include <cstring>
using namespace std;
class Incubator{
public:
	struct edge{int to,cap;edge*rev,*next;}E[10010],*ne,*first[110],*cur[110];
	void link(int a,int b,int c){
		*ne=(edge){b,c,ne+1,first[a]};first[a]=ne++;
		*ne=(edge){a,0,ne-1,first[b]};first[b]=ne++;
	}
	int Q[110],D[110];
	int dfs(int i,int c){
		if(i==1||!c)return c;
		int flow=0,f;
		for(edge*&e=cur[i];e;e=e->next)if(e->cap&&D[e->to]==D[i]-1&&(f=dfs(e->to,c<e->cap?c:e->cap))){
			flow+=f;e->cap-=f;e->rev->cap+=f;
			if(!(c-=f))return flow;
		}
		return flow;
	}
	int maxflow(){
		for(int f=0;;){
			memset(D,0,sizeof(D));
			memcpy(cur,first,sizeof(cur));
			for(int head=0,tail=Q[0]=D[1]=1;head<tail;head++)
				for(edge*e=first[Q[head]];e;e=e->next)
					if(e->rev->cap&&!D[e->to])D[Q[tail++]=e->to]=D[Q[head]]+1;
			if(!D[0])return f;
			f+=dfs(0,1<<30);
		}
	}
	bool f[51][51];
	int maxMagicalGirls(vector <string> love){
		int n=love.size();
		for(int i=0;i<n;i++)for(int j=0;j<n;j++)f[i][j]=love[i][j]=='Y';
		for(int k=0;k<n;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)f[i][k]&&f[k][j]?f[i][j]=1:1;
		int ans=0;ne=E;
		for(int i=0;i<n;i++)if(!f[i][i]){
			link(0,i+2,1);link(i+n+2,1,1);ans++;
			for(int j=0;j<n;j++)if(!f[j][j]&&f[i][j])link(i+2,j+n+2,1);
		}
		return ans-maxflow();
	}
};
