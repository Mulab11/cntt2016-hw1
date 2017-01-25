#include <vector>
#include <string>
#include <cstring>
#define U 100000
#define P(x,y) ((x)*m+(y)+2)
using namespace std;
class BoardPainting{
public:
	struct edge{int to,cap;edge*rev,*next;}E[100000],*ne,*first[2510],*cur[2510];
	void link(int a,int b,int c){
		*ne=(edge){b,c,ne+1,first[a]};first[a]=ne++;
		*ne=(edge){a,0,ne-1,first[b]};first[b]=ne++;
	}
	int Q[2510],D[2510];
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
	int minimalSteps(vector <string> target){
		ne=E;memset(first,0,sizeof(first));
		int n=target.size(),m=target[0].length(),s=0;
		bool u,d,l,r;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++)if(target[i][j]=='#'){
				u=i&&target[i-1][j]=='#';d=i<n-1&&target[i+1][j]=='#';
				l=j&&target[i][j-1]=='#';r=j<m-1&&target[i][j+1]=='#';
				// 割0表示属于V集，上下不同的格子有1代价
				link(0,P(i,j),U+!u+!d);
				if(u)link(P(i-1,j),P(i,j),1);
				if(d)link(P(i+1,j),P(i,j),1);
				// 割1表示属于H集，左右不同的格子有1代价
				link(P(i,j),1,U+!l+!r);
				if(l)link(P(i,j),P(i,j-1),1);
				if(r)link(P(i,j),P(i,j+1),1);
				s++;
			}
		}
		return (maxflow()-U*s)/2; // 答案=端点数/2
	}
};
