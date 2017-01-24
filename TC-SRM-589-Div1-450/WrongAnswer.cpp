#include <vector>
#include <string>
#include <cstring>
using namespace std;
class Netflow{
public:
	struct edge{int to,cap;edge*rev,*next;}E[5510],*ne,*first[55],*cur[55];
	void init(){ne=E;memset(first,0,sizeof(first));}
	void link(int a,int b,int c){
		*ne=(edge){b,c,ne+1,first[a]};first[a]=ne++;
		*ne=(edge){a,0,ne-1,first[b]};first[b]=ne++;
	}
	int Q[55],D[55];
	int dfs(int i,int c){
		if(i==1||!c)return c;
		int flow=0,f;
		for(edge*&e=cur[i];e;e=e->next)if(e->cap&&D[e->to]==D[i]-1&&(f=dfs(e->to,c<e->cap?c:e->cap))){
			flow+=f;e->cap-=f;e->rev->cap+=f;if(!(c-=f))return flow;
		}
		return flow;
	}
	int maxflow(){
		for(int f=0;;f+=dfs(0,1<<30)){
			memset(D,0,sizeof(D));
			memcpy(cur,first,sizeof(cur));
			for(int head=0,tail=Q[0]=D[1]=1;head<tail;head++)
				for(edge*e=first[Q[head]];e;e=e->next)
					if(e->rev->cap&&!D[e->to])D[Q[tail++]=e->to]=D[Q[head]]+1;
			if(!D[0])return f;
		}
	}
}solver;
class GearsDiv1{
public:
	int getmin(string color, vector <string> graph){
		int n=color.size(),cnt[3]={0};
		for(int i=0;i<n;i++)++cnt[color[i]=color[i]=='R'?0:color[i]=='G'?1:2];
		int ans=n,tmp;
		for(int a=0,b=1;a<3;b=(++a+1)%3){
			solver.init();
			for(int i=0,x=2;i<n;i++)if(color[i]==a){
				for(int j=0,y=2+cnt[a];j<n;j++)if(color[j]==b)graph[i][j]=='Y'?solver.link(x,y,1<<30),1:1,y++;
				solver.link(0,x++,1);
			}
			for(int i=0,x=2+cnt[a];i<n;i++)if(color[i]==b)solver.link(x++,1,1);
			if((tmp=solver.maxflow())<ans)ans=tmp;
		}
		return ans;
	}
};
