// FST:状态定义反了
#include <vector>
#include <string>
#define MOD 1000000007
using namespace std;
int N,X[78],Y[78],Z[78],id[12][12]; // 共有N种状态，第i种状态包含X[i]个0，Y[i]个1，Z[i]个2
struct mat{
	int a[78][78];
	mat operator+(const mat&B)const{
		mat C;
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)C.a[i][j]=(a[i][j]+B.a[i][j])%MOD;
		return C;
	}
	mat operator*(const mat&B)const{
		mat C;
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++)C.a[i][j]=0;
			for(int j=0;j<N;j++)if(a[i][j])
				for(int k=0;k<N;k++)C.a[i][k]=(C.a[i][k]+a[i][j]*1ll*B.a[j][k])%MOD;
		}
		return C;
	}
}A,M,S; // A为转移矩阵,M=A^n,S=A^0+A^1+...+A^(n-1)
void solve(int n){ // 矩阵快速幂计算M,S
	if(!n)for(int i=0;i<N;i++)M.a[i][i]=1;
	else if(n%2)solve(n-1),S=S+M,M=M*A;
	else solve(n/2),S=S+S*M,M=M*M;
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
