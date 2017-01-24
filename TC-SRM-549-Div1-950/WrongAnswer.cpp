#include <vector>
#include <cstring>
#include <cassert>
using namespace std;
class CosmicBlocks{
public:
	// 读入的数据
	int N,cnt[6],Min,Max; // N:颜色种数 cnt[i]:颜色i的方块个数 [Min,Max]:可行拓扑序个数限制区间
	// 由 i->j等价于存在一个j在i上方 构成的分层图
	int G[6],L[6],top; // G[i]:指向i的点集 L[i]:第i层点集 top:最后一层
	int f[64]; // f[S]:点集S的拓扑序个数
	void init_ways(){memset(f,0,sizeof(f));} // 初始化数组为0
	int ways(int S){ // 求点集S的拓扑序个数
		if(f[S])return f[S];
		if(!S)f[S]=1;
		else for(int i=0;i<N;i++)
			if((S>>i&1)&&!(S&G[i]))f[S]+=ways(S-(1<<i)); //枚举入度为0的点删掉
		return f[S];
	}
	// 网络流判断图是否合法
	struct edge{int to,cap;edge*rev,*next;}E[110],*ne,*first[8],*cur[8];
	void init_graph(){ne=E;memset(first,0,sizeof(first));}
	void link(int a,int b,int c){
		*ne=(edge){b,c,ne+1,first[a]};first[a]=ne++;
		*ne=(edge){a,0,ne-1,first[b]};first[b]=ne++;
	}
	int Q[8],D[8];
	int dfs(int i,int c){
		if(i==1||!c)return c;
		int flow=0,f;
		for(edge*&e=cur[i];e;e=e->next)if(e->cap&&D[e->to]==D[i]-1&&(f=dfs(e->to,c<e->cap?c:e->cap))){
			flow+=f;e->cap-=f;e->rev->cap+=f;
			if(!(c-=f))return flow;
		}
		return flow;
	}
	bool check(int S,int T){ // 判断相邻两层S和T是否合法
		init_graph();
		int c[6],sum=0;
		for(int i=0;i<N;i++)if((S|T)>>i&1)c[i]=cnt[i];
		for(int i=0;i<N;i++)if(T>>i&1){
			for(int j=0;j<N;j++)if((S>>j&1)&&(G[i]>>j&1)){
				if(--c[i]<0||--c[j]<0)return 0; // 每条边至少要有1的流量
				link(j+2,i+2,1<<30);
			}
		}
		int tmp=-1;
		for(int i=0;i<N;i++){
			if(S>>i&1)link(0,i+2,c[i]);
			else if(T>>i&1)link(i+2,1,tmp=c[i]),sum+=c[i];
		}
		while(sum){
			memset(D,0,sizeof(D));
			memcpy(cur,first,sizeof(cur));
			int head,tail;
			for(head=0,tail=Q[0]=D[1]=1;head<tail;head++)
				for(edge*e=first[Q[head]];e;e=e->next)
					if(e->rev->cap&&!D[e->to])D[Q[tail++]=e->to]=D[Q[head]]+1;
			if(!D[0])return 0;
			sum-=dfs(0,1<<30);
		}
		return 1;
	}
	// 枚举分层图
	int count_graph(int cur,int rest){ // cur:当前枚举到的点 rest:剩下的点集
		if(top&&!check(L[top-1],L[top]))return 0; // 一旦不满足条件就退出
		if(!rest){ // 枚举完所有点，判断是否可行
			init_ways();
			int w=ways((1<<N)-1);
			return w>=Min&&w<=Max;
		}
		int cnt=0;
		// i放新的一层
		if(cur!=-1)for(int i=0;i<N;i++)if(rest>>i&1){
			L[++top]=1<<i;
			for(G[i]=L[top-1];G[i];G[i]=(G[i]-1)&L[top-1]) // 枚举上一层向i连的边
				cnt+=count_graph(i,rest-(1<<i));
			top--;
		}
		// i放同一层
		for(int i=cur+1;i<N;i++)if(rest>>i&1){
			L[top]|=1<<i;
			if(top)for(G[i]=L[top-1];G[i];G[i]=(G[i]-1)&L[top-1]) // 枚举上一层向i连的边
				cnt+=count_graph(i,rest-(1<<i));
			else G[i]=0,cnt+=count_graph(i,rest-(1<<i));
			L[top]-=1<<i;
		}
		return cnt;
	}
	int getNumOrders(vector <int> blockTypes, int minWays, int maxWays){
		N=blockTypes.size();Min=minWays;Max=maxWays;
		for(int i=0;i<N;i++)cnt[i]=blockTypes[i],G[i]=0;
		*L=top=0;
		return count_graph(-1,(1<<N)-1);
	}
};
