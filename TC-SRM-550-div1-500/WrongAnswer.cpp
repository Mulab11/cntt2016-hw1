#include <vector>
#include <string>
using namespace std;
class CheckerExpansion{
public:
	vector <string> resultAfter(long long t, long long x0, long long y0, int w, int h){
		t=t*2-2; // 限制所有点x+y<=t
		vector<string> ans;
		for(int i=0;i<h;i++){
			string str="";
			for(int j=0;j<w;j++){
				long long x=x0+j,y=y0+h-1-i;
				int k=50;
				if(x+y<=t&&y<=x){
					bool f=1;
					while(x+y>2){ // 递归求出(x,y)位置的符号
						while(x+y<=(1ll<<k)-2)--k;
						if(y>=1ll<<k-1)x-=1ll<<k-1,y-=1ll<<k-1; // 位于上方三角形
						else if(x-y>=1ll<<k)x-=1ll<<k; // 位于右下方三角形
						else{f=0;break;} // 位于中间三角形
					}
					// 递归边界
					if(!f)str+='.';
					else if(!x&&!y)str+='A';
					else if(x==1&&!y)str+='.';
					else str+='B';
				}
				else str+='.';
			}
			ans.push_back(str);
		}
		return ans;
	}
};
=l&&y+vy[D]<=r)return -1; // 如果还能走说明不合法
		}
		return (d-u+1)*(r-l+1); // 合法，输出最小面积
	}
};
ne++;
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