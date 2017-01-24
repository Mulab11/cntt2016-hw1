#include <cstring>
#define P(i,j) ((i)+(j)*7)
#define MOD 1234567891
int spl[7][4]={{0,0,0,0},{0,0,0,1},{0,0,1,1},{0,0,1,2},{0,1,0,1},{0,1,0,2},{0,1,2,3}}, // 所有可能的颜色划分 
	dig[7]={4,2,2,1,0,0,0},rot[7]={1,4,2,4,1,2,1}; // dig[i],rot[i]:划分i中相同数字对数,等价旋转方案数 
class TheBrickTowerHardDivOne{
public:
	struct mat{ // 矩阵 
		int N,a[56][56];
		mat(){memset(a,0,sizeof(a));}
		mat operator+(const mat&B)const{ // 矩阵加法 
			mat C;C.N=N;
			for(int i=0;i<N;i++)
				for(int j=0;j<N;j++)C.a[i][j]=(a[i][j]+1ll*B.a[i][j])%MOD;
			return C;
		}
		mat operator*(const mat&B)const{ // 矩阵乘法 
			mat C;C.N=N;
			for(int i=0;i<N;i++)
				for(int j=0;j<N;j++)if(a[i][j])
					for(int k=0;k<N;k++)C.a[i][k]=(C.a[i][k]+1ll*a[i][j]*B.a[j][k])%MOD;
			return C;
		}
	}A,M,S;
	void solve(long long n){ // 计算M=A^n，S=A^0+A^1+...+A^(n-1) 
		if(!n)for(int i=0;i<A.N;i++)M.a[i][i]=1;
		else if(n%2)solve(n-1),S=S+M,M=M*A;
		else solve(n/2),S=S+S*M,M=M*M;
	}
	// 返回to数组对应的划分类型 
	int to[4];
	int find(){
		for(int s=0;s<7;s++)for(int r=0,f;f=1,r<4;r++){
			for(int i=0;i<4;i++)for(int j=i+1;j<4&&f;j++)
				if((spl[s][(i+r)%4]==spl[s][(j+r)%4])!=(to[i]==to[j]))f=0;
			if(f)return s;
		}
	}
	// 枚举s划分的所有转移to并计算方案数，以构造矩阵 
	void dfs(int s,int i,int m,int c,long long p,int k){ // i:枚举to[i]颜色 m:已出现颜色种数 c:剩余颜色种数 p:组成to的方案数 k:相同数对最大个数 
		if(i==4){
			int t=find(),d=dig[s];
			for(int j=0;j<4;j++)d+=(spl[s][j]==to[j]);
			for(int j=d;j<=k;j++)A.a[P(s,j)][P(t,j-d)]=(A.a[P(s,j)][P(t,j-d)]+p)%MOD;
		}
		else for(to[i]=0;to[i]<=m;to[i]++){
			if(to[i]==m)c?dfs(s,i+1,m+1,c-1,p*c%MOD,k),1:1;
			else dfs(s,i+1,m,c,p,k);
		}
	}
	int find(int C, int K, long long H){
		// 构造矩阵 
		A.N=M.N=S.N=7*(K+1);
		for(int s=0;s<7;s++)if(spl[s][3]+1<=C)dfs(s,0,spl[s][3]+1,C-spl[s][3]-1,1,K);
		// 计算答案
		solve(H);
		long long ans=0,v[56]={0},w[56]={0}; // ans为答案，v为系数，w为初始向量 
		for(int s=0;s<7;s++)if(spl[s][3]+1<=C){
			v[s]=rot[s];
			for(int i=0;i<=spl[s][3];i++)(v[s]*=C-i)%=MOD;
			w[P(s,dig[s])]=1;
		}
		for(int s=0;s<7;s++)if(spl[s][3]+1<=C)
			for(int k=0;k<=K;k++)
				for(int i=0;i<A.N;i++)(ans+=S.a[P(s,k)][i]*w[i]%MOD*v[s])%=MOD;
		return ans; 
	}
};
ight;
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
