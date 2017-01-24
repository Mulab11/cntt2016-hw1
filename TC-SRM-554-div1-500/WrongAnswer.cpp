#include <vector>
using namespace std;
class TheBrickTowerMediumDivOne{
public:
	vector<int> s[48]; // 从小到大存储每种数值的下标
	bool vis[48]; // vis[i]表示i是否已用过
	vector <int> find(vector <int> heights){
		vector<int> L,R;
		for(int i=0;i<heights.size();i++)s[heights[i]].push_back(i);
		int pos=47;
		for(int i=0;i<heights.size();i++)if(!vis[i]){ // 从前往后考虑第i位应填的数
			for(;pos>heights[i];pos--) // 将比heights[i]大的全部放到右边，同时保证字典序最小
				for(int j=s[pos].size()-1;j>=0&&!vis[s[pos][j]];j--)vis[s[pos][j]]=1,R.push_back(s[pos][j]);
			vis[i]=1;
			L.push_back(i); // 将i放到第i位
		}
		for(int i=R.size()-1;i>=0;i--)L.push_back(R[i]);
		return L;
	}
};
小于1 
		for(int i=0;i<S1.size();i++)link(T1[i],S1[i],S1[i]<T1[i]?-L1[i]:M-L1[i],S1[i]<T1[i]?0:1); // S1[i]到T1[i]距离至少L1[i] 
		for(int i=0;i<S2.size();i++)link(S2[i],T2[i],S2[i]<T2[i]?L2[i]:L2[i]-M,S2[i]<T2[i]?0:-1); // S2[i]到T2[i]距离至多L2[i]
		// 判断是否存在负权环 
		memset(D,63,sizeof(D));
		memset(vis,0,sizeof(vis));
		int head=*Q=*D=*S=0,tail=1;
		for(int x;head<tail;head++){
			vis[x=Q[head]]=0;
			for(edge*e=first[x];e;e=e->next)if(D[x]+e->len<D[e->to]){
				D[e->to]=D[x]+e->len,S[e->to]=S[x]+1;
				if(!vis[e->to])pos[e->to]=tail,vis[Q[tail++]=e->to]=1;
				fr[pos[e->to]]=head,K[pos[e->to]]=e->k;
				if(S[e->to]>N){ // 找到负权环，判断M是太小还是太大 
					int top=1,sum=0;
					memset(vis,0,sizeof(vis));vis[Q[*S=pos[e->to]]]=1;
					for(int i=*S;;i=fr[i]){
						S[top++]=fr[i],sum+=K[i];
						if(vis[Q[fr[i]]]){
							int old_sum=sum;
							do vis[Q[S[--top]]]=0,sum-=K[S[top-1]];
							while(Q[S[top-1]]!=Q[fr[i]]);
							return sum>old_sum?1:-1;
						}
						vis[Q[fr[i]]]=1;
					}
				}
			}
		}
		return 0; // 不存在负权环 
	}
	long long howMany(int n, vector <int> s1, vector <int> t1, vector <int> l1, vector <int> s2, vector <int> t2, vector <int> l2){
		N=n;S1=s1;T1=t1;L1=l1;S2=s2;T2=t2;L2=l2;
		int tmp=check(1ll<<40);
		if(!tmp)return -1;
		if(tmp==-1||check(n-1)==1)return 0;
		long long left=n-1,right=1ll<<40,mid,ans=0;
		while(right-left>1)check(mid=left+right>>1)>0?right=mid:left=mid;
		if(check(left)==-1)return 0;
		ans=right;left=n-1;
		while(right-left>1)check(mid=left+right>>1)<0?left=mid:right=mid;
		return ans-right;
	}
};
�的一层
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
