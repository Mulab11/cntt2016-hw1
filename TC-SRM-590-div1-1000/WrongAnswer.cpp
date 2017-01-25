#include <vector>
#include <string>
#include <cstring>
#define P(i,j) (((i)-1)*(N+1)+(j)+2)
using namespace std;
class FoxAndCity{
public:
	struct edge{int to,cap;edge*rev,*next;}E[300000],*ne,*first[1650],*cur[1650];
	void init(){ne=E;memset(first,0,sizeof(first));}
	void link(int a,int b,int c){
		*ne=(edge){b,c,ne+1,first[a]};first[a]=ne++;
		*ne=(edge){a,0,ne-1,first[b]};first[b]=ne++;
	}
	int Q[1650],D[1650];
	int dfs(int i,int c){
		if(i==1||!c)return c;
		int flow=0,f;
		for(edge*&e=cur[i];e;e=e->next){
			if(e->cap&&D[e->to]<D[i]){
				f=dfs(e->to,c<e->cap?c:e->cap);
				flow+=f;e->cap-=f;e->rev->cap+=f;
				if(!(c-=f))return flow;
			}
		}
		return flow;
	}
	int maxflow(){
		int f=0;
		for(;;){
			memset(D,0,sizeof(D));
			memcpy(cur,first,sizeof(cur));
			for(int head=0,tail=Q[0]=D[1]=1;head<tail;head++)
				for(edge*e=first[Q[head]];e;e=e->next)
					if(e->rev->cap&&!D[e->to])D[Q[tail++]=e->to]=D[Q[head]]+1;
			if(!D[0])return f;
			f+=dfs(0,1<<30);
		}
	}
	int minimalCost(vector <string> linked, vector <int> want){
		int N=linked.size();init();
		for(int i=1;i<=N;i++){
			link(0,P(i,0),1<<30);
			link(P(i,N),1,1<<30);
		}
		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++){
				if(linked[i-1][j-1]=='Y'){
					for(int k=0;k<N;k++){
						link(P(i,k+1),P(j,k),1<<30); 
					}
				}
			}
		}
		for(int i=1;i<=N;i++){
			for(int j=0;j<N;j++){
				if((i==1&&j>0)||(i!=1&&j==0))link(P(i,j),P(i,j+1),1<<30);
				else link(P(i,j),P(i,j+1),(want[i-1]-j)*(want[i-1]-j));
			}
		}
		return maxflow();
	}
};
