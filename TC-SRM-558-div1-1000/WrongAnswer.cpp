#include <vector>
#include <string>
#include <cstring>
#define P(i,j) ((i)*C+(j)+2)
#define Q(i,j) ((i)*C+(j)+R*C+2)
#define U 1000000
#define INF 1000000000
using namespace std;
class SurroundingGame{
public:
	struct edge{int to,cap;edge*rev,*next;}E[5610],*ne,*first[810],*cur[810];
	void link(int a,int b,int c){
		*ne=(edge){b,c,ne+1,first[a]};first[a]=ne++;
		*ne=(edge){a,0,ne-1,first[b]};first[b]=ne++;
	}
	int Q[810],D[810];
	int dfs(int i,int c){
		if(i==1||!c)return c;
		int flow=0,f;
		for(edge*&e=cur[i];e;e=e->next)if(e->cap&&D[e->to]==D[i]-1&&(f=dfs(e->to,e->cap<c?e->cap:c))){
			flow+=f;e->cap-=f;e->rev->cap+=f;
			if(!(c-=f))return flow;
		}
		return flow;
	}
	int maxflow(){
		for(int f=0;;f+=dfs(0,INF)){
			memset(D,0,sizeof(D));
			memcpy(cur,first,sizeof(cur));
			for(int head=0,tail=Q[0]=D[1]=1;head<tail;head++)
				for(edge*e=first[Q[head]];e;e=e->next)
					if(e->rev->cap&&!D[e->to])D[Q[tail++]=e->to]=D[Q[head]]+1;
			if(!D[0])return f;
		}
	}
	int vx[4]={-1,0,0,1},vy[4]={0,-1,1,0};
	int dec(char c){return c<='9'?c-'0':c>='a'?c-'a'+10:c-'A'+36;}
	int maxScore(vector <string> cost, vector <string> benefit){
		int R=cost.size(),C=cost[0].length(),ans=U*R*C;ne=E;
		for(int i=0;i<R;i++){
			for(int j=0;j<C;j++){
				if((i+j)%2){
					link(0,P(i,j),U),link(P(i,j),1,U+dec(cost[i][j])); // 奇数格割0表示不选，割1表示选
					for(int d=0,x,y;d<4;d++)
						if((x=i+vx[d])>=0&&x<R&&(y=j+vy[d])>=0&&y<C)link(P(x,y),Q(i,j),INF);
					ans+=dec(benefit[i][j]),link(Q(i,j),P(i,j),dec(benefit[i][j])); // 默认得到利益，如果没被占据则取消利益
				}
				else{
					link(0,P(i,j),U+dec(cost[i][j])),link(P(i,j),1,U); // 偶数格割0表示选，割1表示不选
					for(int d=0,x,y;d<4;d++)
						if((x=i+vx[d])>=0&&x<R&&(y=j+vy[d])>=0&&y<C)link(Q(i,j),P(x,y),INF);
					ans+=dec(benefit[i][j]),link(P(i,j),Q(i,j),dec(benefit[i][j])); // 默认得到利益，如果没被占据则取消利益
				}
			}
		}
		return ans-maxflow();
	}
};
