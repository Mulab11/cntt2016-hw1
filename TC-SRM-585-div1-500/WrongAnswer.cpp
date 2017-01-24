#include <vector>
#define MOD 1000000007
using namespace std;
class LISNumber{
public:
	int C[1300][1300];
	int count(vector <int> cardsnum, int K){
		int f[1300]={0,1},S=*C[0]=*C[1]=C[1][1]=1;
		for(int i=0;i<cardsnum.size();i++){
			int g[1300]={0},a=cardsnum[i];
			for(int j=S+1;j<=S+a;j++)
				for(int k=*C[j]=1;k<=j;k++)C[j][k]=(C[j-1][k-1]+C[j-1][k])%MOD;
			for(int j=0;j<=S;j++)if(f[j])
				for(int k=0;k<=j&&k<=a;k++)g[j+a-k]=(g[j+a-k]+f[j]*(long long)C[j][k]%MOD*C[a+S-j-1][a-k])%MOD;
			S+=a;
			for(int j=0;j<=S;j++)f[j]=g[j];
		}
		return f[K];
	}
};
[E[i].v]||E[i].w<fa[E[i].v]->w))fa[E[i].v]=E+i;
			for(int i=1;i<=N;i++)if(!del[i]&&!fa[i])return-1;
			int g=0;vis[0]=-2;
			for(int i=1;i<=N&&!g;i++)if(!del[i]&&!vis[i]){
				int j=i;while(!vis[j])vis[j]=i,j=fa[j]->u;
				if(vis[j]==i)for(g=j;vis[g]!=-1;g=fa[g]->u)vis[g]=-1,g!=j?del[g]=1:1,s+=(in[g]=fa[g]->w);
			}
			if(!g){
				for(int i=1;i<=N;i++)if(!del[i])s+=fa[i]->w;
				return s;
			}
			for(int i=0;i<M;i++){
				if(vis[E[i].v]==-1)vis[E[i].u]!=-1?E[i]=(edge){E[i].u,g,E[i].w-in[E[i].v]},1:E[i].u=-1;
				else if(vis[E[i].u]==-1)E[i].u=g;
			}
			int j=0;for(int i=0;i<M;i++)if(E[i].u>-1)E[j++]=E[i];M=j;
		}
	}
}solver;
class FoxTheLinguist{
public:
	int id(int*s){return s[1]=='0'?0:(s[0]-'A')*9+s[1]-'0';}
	int num(int*s){int x=0;for(int i=0;i<4;i++)x=x*10+s[i]-'0';return x;}
	void add(int*s){solver.link(id(s),id(s+4),num(s+7));}
	int minimalHours(int n, vector <string> courseInfo){
		solver.init(9*n);
		for(int i=0;i<n;i++){
			solver.link(i*9+1,0,0);
			for(int j=2;j<=9;j++)solver.link(i*9+j,i*9+j-1,0);
		}
		int s[12],l=0;
		for(int i=0;i<courseInfo.size();i++)
			for(int j=0,x;j<courseInfo[i].length();j++)
				(x=courseInfo[i][j])==' '?add(s),l=0:s[l++]=x;
		add(s);
		return solver.solve();
	}
};
es[y][2]);
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
