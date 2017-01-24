#include <vector>
#include <string>
#define INF 1000000000
using namespace std;
class TravellingPurchasingMan{
public:
	int N,M,E,stores[60][3],roads[60][3];
	void read(vector<string>S,int A[][3],int&n){
		n=S.size();
		for(int i=0,j;i<n;i++){
			j=A[i][0]=0;
			for(int k=0;k<S[i].length();k++)S[i][k]==' '?A[i][++j]=0:(A[i][j]*=10)+=S[i][k]-'0';
		}
	}
	struct edge{int to,len;edge*next;}edges[110],*ne,*first[60];
	void link(int a,int b,int l){
		*ne=(edge){b,l,first[a]};first[a]=ne++;
		*ne=(edge){a,l,first[b]};first[b]=ne++;
	}
	int Q[2510],D[60],dis[16][16];
	bool inq[60];
	void shortest_path(int s){
		for(int i=0;i<N;i++)D[i]=INF,inq[i]=0;
		Q[0]=s;D[s]=0;
		for(int head=0,tail=1,i;head<tail;head++){
			inq[i=Q[head]]=0;
			for(edge*e=first[i];e;e=e->next)if(D[i]+e->len<D[e->to]){
				D[e->to]=D[i]+e->len;
				if(!inq[e->to])inq[Q[tail++]=e->to]=1;
			}
		}
	}
	int f[1<<16][16],popc[1<<16];
	int max(int a,int b){return a>b?a:b;}
	void cmin(int&a,int b){b<a?a=b:1;}
	int maxStores(int N, vector <string> interestingStores, vector <string> roads){
		this->N=N;read(interestingStores,stores,M);read(roads,this->roads,E);ne=edges;
		for(int i=0;i<E;i++)link(this->roads[i][0],this->roads[i][1],this->roads[i][2]);
		for(int S=0;S<(1<<M);S++)
			for(int x=0;x<M;x++)f[S][x]=INF;
		for(int i=0;i<M;i++){
			shortest_path(i);
			for(int j=0;j<M;j++)dis[i][j]=D[j];
			if(D[N-1]<=stores[i][1])cmin(f[1<<i][i],max(D[N-1],stores[i][0])+stores[i][2]);
		}
		int ans=0;
		for(int S=1;S<(1<<M);S++){
			popc[S]=popc[S&(S-1)]+1;
			for(int x=0;x<M;x++)if((S>>x&1)&&f[S][x]<INF){
				if(popc[S]>ans)ans=popc[S];
				for(int y=0;y<M;y++)if(!(S>>y&1)&&f[S][x]+dis[x][y]<=stores[y][1])cmin(f[S|1<<y][y],max(f[S][x]+dis[x][y],stores[y][0])+stores[y][2]);
			}
		}
		return ans;
	}
};
][0])+stores[y][2]);
			}
		}
		return ans;
	}
};
ej=first[E[j].to];ej;ej=ej->next)if(!ej->del&&ej!=E[j].rev)solver.w[solver.nx][solver.ny++]=f[ei->to][ej-E];
			solver.nx++;
		}
		f[i][j]+=solver.match();
	}
	int getmax(vector <int> a, vector <int> b){
		N=a.size()+1;ne=E;
		for(int i=0;i<N-1;i++)link(a[i],b[i]);
		now=0;dfs(0,-1);
		int ans=0,tmp;
		for(int i=1;i<N;i++){
			fe[i]->del=fe[i]->rev->del=1;
			memset(f,0,sizeof(f));
			for(int j=0;j<N;j++)if(pre[j]<pre[i]||pre[j]>=pos[i]){
				for(edge*ei=first[i];ei;ei=ei->next)if(!ei->del)
					for(edge*ej=first[j];ej;ej=ej->next)if(!ej->del)calc(ei->to,ej-E);
				solver.nx=0;
				for(edge*ei=first[i];ei;ei=ei->next)if(!ei->del){
					solver.ny=0;
					for(edge*ej=first[j];ej;ej=ej->next)if(!ej->del)solver.w[solver.nx][solver.ny++]=f[ei->to][ej-E];
					solver.nx++;
				}
				if((tmp=1+solver.match())>ans)ans=tmp;
			}
			fe[i]->del=fe[i]->rev->del=0;
		}
		return ans;
	}
};
ver.match())>ans)ans=tmp;
			}
			fe[i]->del=fe[i]->rev->del=0;
		}
		return ans;
	}
};
ep+1,ff);
	}
	int getCount(vector <int> edge1, vector <int> edge2, int k){
		this->n=edge1.size()+1;this->k=k;ne=E;ans=0;
		for(int i=0;i<edge1.size();i++)link(edge1[i],edge2[i]),link(edge2[i],edge1[i]);
		init();
		if(k==1)return fac[n];
		if(2*k>n){
			init(0,-1);
			dfs1(0,-1,1);
			return ans*fac[2*k-n]%MOD*fac[n-k]%MOD*fac[n-k]%MOD;
		}
		for(int i=0;i<n;i++){
			init(i,-1);
			dfs2(i,-1,0,inv[k]);
		}
		return ans*fac[k]%MOD*fac[k]%MOD;
	}
};
