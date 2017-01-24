// Unsolved:不会做，看了题解的结论，结论也不会证明
// FST:没有限制a和b各自的流量，以及流量无穷大时相加爆int了
#include <vector>
#include <string>
#include <cstring>
using namespace std;
class Netflow{
public:
	struct edge{int to,cap;edge*rev,*next;}E[5010],*ne,*first[60],*cur[60];
	void init(){ne=E;memset(first,0,sizeof(first));}
	void link(int a,int b,int c1,int c2=0){
		*ne=(edge){b,c1,ne+1,first[a]};first[a]=ne++;
		*ne=(edge){a,c2,ne-1,first[b]};first[b]=ne++;
	}
	int Q[60],D[60];
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
class OldBridges{
public:
	string isPossible(vector <string> bridges, int a1, int a2, int an, int b1, int b2, int bn){
		for(int n=bridges.size(),t=2;t--;){
			solver.init();
			solver.link(0,a1+2,an<<1);
			solver.link(0,(t?b1:b2)+2,bn<<1);
			solver.link(a2+2,1,an<<1);
			solver.link((t?b2:b1)+2,1,bn<<1);
			for(int i=n;i--;)for(int j=n;--j>i;)
				if(bridges[i][j]!='X')solver.link(i+2,j+2,bridges[i][j]=='N'?1<<30:2,bridges[i][j]=='N'?1<<30:2);
			if(solver.maxflow()<an+bn<<1)return"No";
		}
		return"Yes";
	}
};
