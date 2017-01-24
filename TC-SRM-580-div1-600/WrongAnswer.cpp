#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class ShoutterDiv1{
public:
	int n,s[2510],t[2510],lmin[10000],rmax[10000],dl[10000],dr[10000];
	int num(char a,char b,char c,char d){return(((a-'0')*10+b-'0')*10+c-'0')*10+d-'0';}
	int min(int a,int b){return a<b?a:b;}
	int max(int a,int b){return a>b?a:b;}
	int count(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1){
		int smax=-1,tmin=10000;
		for(int i=n=0;i<s1.size();i++)
			for(int j=0;j<s1[i].length();j++,n++)
				smax=max(smax,s[n]=num(s1000[i][j],s100[i][j],s10[i][j],s1[i][j])),
				tmin=min(tmin,t[n]=num(t1000[i][j],t100[i][j],t10[i][j],t1[i][j]));
		if(smax<=tmin)return 0;
		for(int i=0;i<n;i++)s[i]=max(s[i],tmin),t[i]=min(t[i],smax);
		for(int i=tmin;i<=smax;i++)lmin[i]=rmax[i]=i;
		for(int i=0;i<n;i++)lmin[t[i]]=min(lmin[t[i]],s[i]),rmax[s[i]]=max(rmax[s[i]],t[i]);
		for(int i=smax-1;i>=tmin;i--)lmin[i]=min(lmin[i],lmin[i+1]);
		for(int i=tmin+1;i<=smax;i++)rmax[i]=max(rmax[i],rmax[i-1]);
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
