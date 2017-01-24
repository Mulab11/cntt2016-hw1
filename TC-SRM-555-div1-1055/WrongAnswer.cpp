#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class MapGuessing{
public:
	int n,m;
	long long S[40];
	long long dfs(int i,long long s){
		long long cnt=1ll<<__builtin_popcountll(s);
		while(++i<m)cnt-=dfs(i,s&S[i]);
		return cnt;
	}
	long long T[36<<16];
	int make(int l,int r,int L){
		if(r-l==1){
			long long s=S[l];int R=L+(1<<__builtin_popcountll(s));
			for(int i=R-1;i>=L;i--)T[i]=s,s=(s-1)&S[l];
			return R;
		}
		int M=make(l,l+r>>1,L),R=make(l+r>>1,r,M);
		std::inplace_merge(T+L,T+M,T+R);
		R=std::unique(T+L,T+R)-T;
		return R;
	}
	long long countPatterns(string goal, vector<string> code){
		int l=0,r=0,p=0,pos[555],ch[555],opcnt=0;
		for(int i=0;i<code.size();i++)
			for(int j=0,c;j<code[i].length();j++)
				((c=code[i][j])=='<'?--p:c=='>'?++p:(ch[opcnt]=code[i][j],pos[opcnt++]=p))<l?l=p:p>r?r=p:1;
		n=goal.length();m=0;
		for(int i=0;i<n;i++)if(i+l>=0&&i+r<n){
			long long V=0,W=0;S[m]=0;
			for(int j=0;j<opcnt;j++){
				V|=1ll<<i+pos[j];
				if(goal[i+pos[j]]==ch[j])W&=~(1ll<<i+pos[j]);
				else W|=1ll<<i+pos[j];
				if(!W)S[m]=V;
			}
			m++;
		}
		if(m<=20){
			long long ans=0;
			for(int i=0;i<m;i++)ans+=dfs(i,S[i]);
			return ans;
		}
		return make(0,m,0);
	}
};
0;
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
