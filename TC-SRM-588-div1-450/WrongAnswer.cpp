#include <vector>
using namespace std;
class KeyDungeonDiv1{
public:
	int n,dR[12],dG[12],rR[12],rG[12],rW[12],f[1<<12][132];
	bool vis[1<<12][132];
	struct item{int S,R,G,W,cnt;}Q[132<<12],*H,*T;
	int bfs(int R,int G,int W){
		int ans=0;H=Q;T=Q+1;*H=(item){0,R,G,f[0][R]=W,0};vis[0][R]=1;
		for(;H<T;H++){
			H->G-=f[H->S][H->R]-H->W;
			H->W=f[H->S][H->R];
			if(H->R+H->G+H->W>ans)ans=H->R+H->G+H->W;
			for(int i=n;i--;)if(!(H->S>>i&1)){
				*T=(item){H->S|1<<i,H->R-dR[i],H->G-dG[i],H->W,H->cnt+1};
				if(T->R<0)T->W+=T->R,T->R=0;
				if(T->G<0)T->W+=T->G,T->G=0;
				if(T->W>=0){
					T->R+=rR[i];T->G+=rG[i];T->W+=rW[i];
					if(!vis[T->S][T->R])vis[T->S][T->R]=1,f[T->S][T->R]=T->W,T++;
					else if(T->W>f[T->S][T->R])f[T->S][T->R]=T->W;
				}
			}
		}
		return ans;
	}
	int maxKeys(vector <int> doorR, vector <int> doorG, vector <int> roomR, vector <int> roomG, vector <int> roomW, vector <int> keys){
		for(int i=n=doorR.size();i--;)dR[i]=doorR[i],dG[i]=doorG[i],rR[i]=roomR[i],rG[i]=roomG[i],rW[i]=roomW[i];
		return bfs(keys[0],keys[1],keys[2]);
	}
};
^val[j]^val[0]):1;
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
