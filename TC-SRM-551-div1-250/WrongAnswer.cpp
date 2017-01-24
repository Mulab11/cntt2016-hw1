// FST:Two pointers右指针移动左指针忘记移动
#include <vector>
#include <string>
using namespace std;
class ColorfulChocolates{
public:
	vector<int> a[26];
	int maximumSpread(string chocolates, int maxSwaps){
		for(int i=0;i<chocolates.length();i++)a[chocolates[i]-'A'].push_back(i);
		int ans=0;
		for(int c=0;c<26;c++){ // 枚举最大连续段的字符A~Z
			int r=0,n=a[c].size(),sum=0;
			for(int i=0;i<n;i++)a[c][i]-=i; // 将下标减i，方便处理
			for(int l=0;l<n;l++){ // 枚举区间
				for(;r<n&&sum<=maxSwaps;r++){
					if(r-l>ans)ans=r-l; // 更新答案ans
					sum+=a[c][r]-a[c][l+r>>1]; // 更新最小交换次数sum
				}
				if(sum<=maxSwaps&&r-l>ans)ans=r-l; // 更新答案ans
				sum+=a[c][l]-a[c][l+r>>1]; // 更新最小交换次数sum
			}
		}
		return ans;
	}
};
),S=S+S*M,M=M*M;
}
class ConversionMachine{
public:
	int countAll(string word1, string word2, vector <int> costs, int maxCost){
		int L=word1.length(),cnt[3]={0},tot=0;
		for(int i=0;i<L;i++){
			// 转成0,1,2序列，问题变为求000...0变化为给定的0,1,2序列的方案数
			int c1=word1[i]-'a',c2=word2[i]-'a';
			cnt[(c2-c1+3)%3]++;
			for(;c1!=c2;c1=(c1+1)%3){
				maxCost-=costs[c1],tot++;
				if(maxCost<0)return 0;
			}
		}
		maxCost=tot+maxCost/(costs[0]+costs[1]+costs[2])*3+1; // 操作序列最大长度
		for(int i=0;i<=L;i++)
			for(int j=0;i+j<=L;j++)
				X[N]=i,Y[N]=j,Z[N]=L-i-j,id[i][j]=N++;
		for(int i=0;i<N;i++){ // 构造转移矩阵
			if(X[i])A.a[i][id[X[i]-1][Y[i]]]=X[i]; // 2->0
			if(Y[i])A.a[i][id[X[i]+1][Y[i]-1]]=Y[i]; // 0->1
			if(Z[i])A.a[i][id[X[i]][Y[i]+1]]=Z[i]; // 1->2
		}
		solve(maxCost);
		return S.a[id[cnt[0]][cnt[1]]][id[L][0]];
	}
};
,tmp=c[i]),sum+=c[i];
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
