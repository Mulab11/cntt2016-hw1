// Unsolved:²»»á×ö£¬¿´ÁËÌâ½âµÄ½áÂÛ£¬½áÂÛÒ²²»»áÖ¤Ã÷
// FST:Ã»ÓĞÏŞÖÆaºÍb¸÷×ÔµÄÁ÷Á¿£¬ÒÔ¼°Á÷Á¿ÎŞÇî´óÊ±Ïà¼Ó±¬intÁË
#include <vector>
#include <string>
#include <cstring>
using namespace std;
class Netflow{
public:
	struct edge{int to,cap;edge*rev,*next;}E[5010],*ne,*first[60],*cur[60];
	void init(){ne=E;memset(first,0,sizeof(first));}
	void link(int a,int b,int c1,int c2=0){
		*ne=(edge){b,c1,ne+1,first[a]};first[a]=ne++;
		*ne=(edge){a,c2,ne-1,first[b]};first[b]=ne++;
	}
	int Q[60],D[60];
	int dfs(int i,int c){
		if(i==1||!c)return c;
		int flow=0,f;
		for(edge*&e=cur[i];e;e=e->next)if(e->cap&&D[e->to]==D[i]-1&&(f=dfs(e->to,c<e->cap?c:e->cap))){
			flow+=f;e->cap-=f;e->rev->cap+=f;if(!(c-=f))return flow;
		}
		return flow;
	}
	int maxflow(){
		for(int f=0;;f+=dfs(0,1<<30)){
			memset(D,0,sizeof(D));
			memcpy(cur,first,sizeof(cur));
			for(int head=0,tail=Q[0]=D[1]=1;head<tail;head++)
				for(edge*e=first[Q[head]];e;e=e->next)
					if(e->rev->cap&&!D[e->to])D[Q[tail++]=e->to]=D[Q[head]]+1;
			if(!D[0])return f;
		}
	}
}solver;
class OldBridges{
public:
	string isPossible(vector <string> bridges, int a1, int a2, int an, int b1, int b2, int bn){
		for(int n=bridges.size(),t=2;t--;){
			solver.init();
			solver.link(0,a1+2,an<<1);
			solver.link(0,(t?b1:b2)+2,bn<<1);
			solver.link(a2+2,1,an<<1);
			solver.link((t?b2:b1)+2,1,bn<<1);
			for(int i=n;i--;)for(int j=n;--j>i;)
				if(bridges[i][j]!='X')solver.link(i+2,j+2,bridges[i][j]=='N'?1<<30:2,bridges[i][j]=='N'?1<<30:2);
			if(solver.maxflow()<an+bn<<1)return"No";
		}
		return"Yes";
	}
};
n+bn<<1)return"No";
		}
		return"Yes";
	}
};
.a[P(s,j)][P(t,j-d)]=(A.a[P(s,j)][P(t,j-d)]+p)%MOD;
		}
		else for(to[i]=0;to[i]<=m;to[i]++){
			if(to[i]==m)c?dfs(s,i+1,m+1,c-1,p*c%MOD,k),1:1;
			else dfs(s,i+1,m,c,p,k);
		}
	}
	int find(int C, int K, long long H){
		// æ„é€ çŸ©é˜µ 
		A.N=M.N=S.N=7*(K+1);
		for(int s=0;s<7;s++)if(spl[s][3]+1<=C)dfs(s,0,spl[s][3]+1,C-spl[s][3]-1,1,K);
		// è®¡ç®—ç­”æ¡ˆ
		solve(H);
		long long ans=0,v[56]={0},w[56]={0}; // ansä¸ºç­”æ¡ˆï¼Œvä¸ºç³»æ•°ï¼Œwä¸ºåˆå§‹å‘é‡ 
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
°çš„ä¸€å±‚
		if(cur!=-1)for(int i=0;i<N;i++)if(rest>>i&1){
			L[++top]=1<<i;
			for(G[i]=L[top-1];G[i];G[i]=(G[i]-1)&L[top-1]) // æšä¸¾ä¸Šä¸€å±‚å‘iè¿çš„è¾¹
				cnt+=count_graph(i,rest-(1<<i));
			top--;
		}
		// iæ”¾åŒä¸€å±‚
		for(int i=cur+1;i<N;i++)if(rest>>i&1){
			L[top]|=1<<i;
			if(top)for(G[i]=L[top-1];G[i];G[i]=(G[i]-1)&L[top-1]) // æšä¸¾ä¸Šä¸€å±‚å‘iè¿çš„è¾¹
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
