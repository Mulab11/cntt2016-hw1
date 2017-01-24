#include <vector>
using namespace std;
class TravelOnMars{
public:
	int N,r[60];
	void cmin(int&a,int b){b<a?a=b:1;}
	void cmax(int&a,int b){b>a?a=b:1;}
	int minTimes(vector <int> range, int startCity, int endCity){
		N=range.size();
		for(int i=0;i<N;i++)r[i]=range[(i+startCity)%N];
		endCity=(endCity-startCity+N)%N;
		int L=0,R=N,ll=r[0],rr=N-r[0],ans=0; // 当前经过的区间为[0,L],[R,N)，ans为步数
		while(endCity>L&&endCity<R){
			int lmax=ll,rmin=rr;++ans;
			while(L<ll){
				if(++L==endCity)return ans;
				cmax(lmax,L+r[L]);cmin(rmin,L-r[L]+N);
			}
			while(R>rr){
				if(--R==endCity)return ans;
				cmax(lmax,R+r[R]-N);cmin(rmin,R-r[R]);
			}
			L=ll;ll=lmax;R=rr;rr=rmin;
		}
		return ans;
	}
};
rimes[j]]=primes[j];
				if(i%primes[j]==0)break;
				f2[i*primes[j]]=-f2[i];
			}
		}
		int*iter=mem;
		for(int i=1;i<=16817;i++)if(f2[i]){
			cnt_y[i]=iter;
			*(iter++)=0;
			for(int j=i;j<=430887;j+=i)*iter=iter[-1]+(f2[j]?f2[i]:0),iter++;
		}
	}
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
