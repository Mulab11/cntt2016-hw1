#include <vector>
#include <string>
#define INF 10000000
using namespace std;
class WallGameDiv1{
public:
	int R,C,c[52][52],S[52][52],f[52][52][52];
	void cmin(int&a,int b){b<a?a=b:a;}
	void cmax(int&a,int b){b>a?a=b:a;}
	// (i,j,k)为当前位于(i,j)，Wall在(j,k]或[k,j)，轮到E时的答案
	int dfs(int i,int j,int k){
		if(i==R-1)return c[i][j];
		int&g=f[i][j][k];
		if(g)return g-1;
		g=c[i][j]+dfs(i+1,j,j); // j不放，走到(i+1,j)
		int t=INF;
		// j放，走到j-1或k+1
		if(j<k){
			if(j)cmin(t,dfs(i,j-1,k)); // 走到j-1，Wall变为(j-1,k]
			if(k+1<C)cmin(t,dfs(i,k+1,j)+S[i][k+1]-S[i][j+1]); // 走到k+1，Wall变为[j,k+1)
		}
		else{
			if(k)cmin(t,dfs(i,k-1,j)+S[i][j]-S[i][k]); // 走到k-1，Wall变为(k-1,j]
			if(j+1<C)cmin(t,dfs(i,j+1,k)); // 走到j+1，Wall变为[k,j+1)
		}
		if(t<INF)cmax(g,t+c[i][j]);
		return g++;
	}
	int play(vector <string> costs){
		R=costs.size();C=costs[0].length();
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
