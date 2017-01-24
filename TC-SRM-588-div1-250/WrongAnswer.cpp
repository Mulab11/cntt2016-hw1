#include <vector>
#include <algorithm>
using namespace std;
class GUMIAndSongsDiv1{
public:
	struct item{int d,t;bool operator<(const item&it)const{return t<it.t;}}a[51];
	int f[51][51];
	int min(int a,int b){return a<b?a:b;}
	int maxSongs(vector <int> duration, vector <int> tone, int T){
		int n=tone.size(),ans=0;
		for(int i=0;i<n;i++)a[i]=(item){duration[i],tone[i]};
		sort(a,a+n);
		for(int i=n-1;i>=0;i--){
			for(int j=1;i+j<=n;j++){
				if(j==1)f[i][j]=i<n-1?min(a[i].d,a[i+1].t-a[i].t+f[i+1][j]):a[i].d;
				else if(i+j==n)f[i][j]=a[i].d+a[i+1].t-a[i].t+f[i+1][j-1];
				else f[i][j]=min(f[i+1][j],a[i].d+f[i+1][j-1])+a[i+1].t-a[i].t;
				if(f[i][j]<=T&&j>ans)ans=j;
			}
		}
		return ans;
	}
};
t i=1;i<W;i++)if(cells[0][i]!='?'&&!fill(i,f(cells[0][i])))return ans;
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
