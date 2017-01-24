#include <vector>
#include <string>
using namespace std;
class ThreeColorability{
public:
	int H,W;
	bool G[110][110],E[110][110],vis[110],val[110];
	int f(int c){return c==0?'N':c==1?'Z':c=='N'?0:1;}
	bool fill(int i,int c){
		vis[i]=1;val[i]=c;
		for(int j=0;j<=H+W;j++)
			if(G[i][j]&&(vis[j]&&val[j]!=(c^E[i][j])||!vis[j]&&!fill(j,c^E[i][j])))return 0;
		return 1;
	}
	vector <string> solve(vector <string> cells){
		vector<string>ans;
		H=cells.size();W=cells[0].size();val[0]=f(cells[0][0]);
		for(int i=0;i<=H+W;vis[i++]=0)
			for(int j=0;j<=H+W;j++)G[i][j]=0;
		for(int i=1;i<H;i++)
			for(int j=1;j<W;j++)if(cells[i][j]!='?')G[i+W][j]=G[j][i+W]=1,E[i+W][j]=E[j][i+W]=f(cells[i][j])^val[0];
		for(int i=1;i<W;i++)if(cells[0][i]!='?'&&!fill(i,f(cells[0][i])))return ans;
		for(int i=1;i<H;i++)if(cells[i][0]!='?'&&!fill(i+W,f(cells[i][0])))return ans;
		for(int i=1;i<W;i++)if(!vis[i]&&!fill(i,0))return ans;
		for(int i=1;i<H;i++)if(!vis[i+W]&&!fill(i+W,0))return ans;
		for(int i=0;i<H;i++)
			for(int j=0;j<W;j++)cells[i][j]=='?'?cells[i][j]=f(val[i?i+W:0]^val[j]^val[0]):1;
		return cells;
	}
	vector <string> lexSmallest(vector <string> cells){
		if(cells[0][0]=='?'){
			cells[0][0]='N';
			vector<string>ans=solve(cells);
			if(ans.size())return ans;
			cells[0][0]='Z';
		}
		return solve(cells);
	}
};
i]+l[i];
		for(int i=0,p=0;i<m;i++){
			while(p<=i||p<l[i]&&l[p]<=r[i])++p;
			ans+=sum[l[i]]-sum[p]-r[i]*(long long)(l[i]-p);
			if(r[i]<l[i]&&p<l[i])ans--;
		}
		return ans;
	}
};
0;i<n;i++){
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
