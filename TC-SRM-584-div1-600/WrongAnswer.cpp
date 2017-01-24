#include <vector>
#include <algorithm>
using namespace std;
class Excavations{
public:
	long long C[60][60],f[60][60];
	int tmp[60],cnt[60];
	struct item{int d,t;bool operator<(const item&it)const{return d<it.d||d==it.d&&t<it.t;}}S[60];
	long long count(vector <int> kind, vector <int> depth, vector <int> found, int K){
		int n=kind.size(),m=found.size();
		for(int i=0;i<=n;i++)
			for(int j=*C[i]=1;j<=i;j++)C[i][j]=C[i-1][j-1]+C[i-1][j];
		for(int i=0;i<m;i++)tmp[found[i]]=i+1;
		for(int i=0;i<n;i++)S[i]=(item){depth[i],tmp[kind[i]]};
		sort(S,S+n);S[n].t=0;
		long long ans=0;
		bool need=1;
		for(int i=0;i<=n;i++){
			if(S[i].t)cnt[S[i].t]++,need=1;
			else{
				if(need){
					f[0][0]=1;
					for(int i=1;i<=m;i++)
						for(int j=0;j<=K;j++)
							for(int k=(f[i][j]=0)+1;k<=cnt[i]&&k<=j;k++)f[i][j]+=C[cnt[i]][k]*f[i-1][j-k];
					need=0;
				}
				if(i==n)ans+=f[m][K];
				else for(int x=0;x<K;x++)ans+=f[m][x]*C[n-i-1][K-x-1];
			}
		}
		return ans;
	}
};
int a,u,k0,p[30],cnt;
	long long res;
	void facts(int i,int d){
		if(f2[d])res+=cnt_y[d][u/k0/d]-cnt_y[d][a/k0/d];
		for(;i<cnt;i++)facts(i+1,d*p[i]);
	}
	long long solve(long long N){
		if(!N)return 0;
		res=0;
		for(a=Cbrt(N-1);a;a--)if(f2[a])res+=Sqrt(N/a)-a;
		for(a=Sqrt(Sqrt(N-1));a;a--)if(f3[a]){
			u=Cbrt(N/a);
			for(int k=Cbrt(a);k;k--){
				int g=gcd(a,k*k),a0=a/g;k0=k*k/g;
				if(f2[a0]){
					int tmp=a0;cnt=0;
					while(minp[tmp])tmp/=(p[cnt++]=minp[tmp]);
					if(tmp>1)p[cnt++]=tmp;
					facts(0,1);
				}
			}
		}
		return res;
	}
	long long count(long long L, long long R){
		init();
		return solve(R)-solve(L-1);
	}
};
ong long R){
		init();
		return solve(R)-solve(L-1);
	}
};
[y][1])cmin(f[S|1<<y][y],max(f[S][x]+dis[x][y],stores[y][0])+stores[y][2]);
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
