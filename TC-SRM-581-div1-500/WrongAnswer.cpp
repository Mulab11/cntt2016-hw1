#include <vector>
#include <string>
using namespace std;
class TreeUnion{
public:
	int N,f[2][310],g[310][5];
	void read(vector<string>T,int*f,int&n){
		*f=f[1]=0;n=1;
		for(int i=0;i<T.size();i++)
			for(int j=0;j<T[i].length();j++)T[i][j]==' '?f[++n]=0:(f[n]*=10)+=T[i][j]-'0';
		n++;
	}
	double expectedCycles(vector <string> tree1, vector <string> tree2, int K){
		read(tree1,f[0],N);read(tree2,f[1],N);
		int cnt[2][5]={0};
		for(int t=0;t<2;t++){
			for(int i=0;i<N;i++)
				for(int j=0;j<5;j++)g[i][j]=!j;
			for(int i=N-1;i;i--){
				for(int j=0;j<=4;j++)
					if(g[f[t][i]][j])for(int k=0;j+k<4;k++)cnt[t][j+k+1]+=g[i][k]*g[f[t][i]][j];
				for(int j=0;j<4;j++)g[f[t][i]][j+1]+=g[i][j];
			}
		}
		double ans=0;
		for(int i=1,j=K-2-i;j;i++,j--)ans+=2.0*cnt[0][i]*cnt[1][j];
		return ans/N/(N-1);
	}
};
i+1]])--t[ty[i+1]]==0?ex1--:1,t[ty[i+1]]==cnt[ty[i+1]]-m[ty[i+1]]?ex2--:1;
		}
		return ans;
	}
};
C=costs[0].length();
		for(int i=0;i<R;i++)
			for(int j=S[i][0]=0;j<C;j++)S[i][j+1]=S[i][j]+(c[i][j]=costs[i][j]-'0');
		int ans=INF;
		for(int i=0;i<C;i++)cmin(ans,dfs(0,i,i));
		return ans;
	}
};
-1]);
		int ans=0,sum=0;dl[tmin]=dr[smax]=0;
		for(int i=tmin;i<smax;i=rmax[i],ans++)if(rmax[i]==i)return-1;
		for(int i=tmin+1;i<=smax;i++)dl[i]=1+dl[lmin[i]];
		for(int i=smax-1;i>=tmin;i--)dr[i]=1+dr[rmax[i]];
		for(int i=0;i<n;i++)sum+=min(ans,dl[s[i]]+dr[t[i]]);
		return sum;
	}
};
][1])cmin(f[1<<i][i],max(D[N-1],stores[i][0])+stores[i][2]);
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
