#include <string>
using namespace std;
class LittleElephantAndBalls{
public:
	int f(char c){return c=='R'?0:c=='G'?1:2;}
	int getNumber(string S){
		int cnt[3]={0},ans=0;
		for(int i=0;i<S.length();i++){
			for(int j=0;j<3;j++)ans+=cnt[j];
			if(++cnt[f(S[i])]>2)cnt[f(S[i])]=2;
		}
		return ans;
	}
};
y-1&1),t2=k2||y&&(S2>>y-1&1);
		if(g)return g-1;
		g=(g+dfs(x,y+1,S1-(k1<<y),S2-(k2<<y))*(24ll+e[x+y]))%MOD;
		if(e[x+y])g=(g+dfs(x,y+1,S1+(t1<<y)-(k1<<y),S2+(t2<<y)-(k2<<y)))%MOD;
		else g=(g+dfs(x,y+1,S1+(t1<<y)-(k1<<y),S2-(k2<<y))+1ll*dfs(x,y+1,S1-(k1<<y),S2+(t2<<y)-(k2<<y)))%MOD;
		return g++;
	}
	int countBoards(int n, int m, string A, string B){
		N=n;M=m;
		for(int i=0;i<N+M-1;i++)e[i]=A[i]==B[i];
		return dfs(0,0,1,1);
	}
};
		memcpy(cur,first,sizeof(cur));
			for(int head=0,tail=Q[0]=D[1]=1;head<tail;head++)
				for(edge*e=first[Q[head]];e;e=e->next)
					if(e->rev->cap&&!D[e->to])D[Q[tail++]=e->to]=D[Q[head]]+1;
			if(!D[0])return f;
			f+=dfs(0,1<<30);
		}
	}
	int minimalCost(vector <string> linked, vector <int> want){
		int N=linked.size();init();
		for(int i=1;i<=N;i++){
			link(0,P(i,0),1<<30);
			link(P(i,N),1,1<<30);
		}
		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++){
				if(linked[i-1][j-1]=='Y'){
					for(int k=0;k<N;k++){
						link(P(i,k+1),P(j,k),1<<30); 
					}
				}
			}
		}
		for(int i=1;i<=N;i++){
			for(int j=0;j<N;j++){
				if((i==1&&j>0)||(i!=1&&j==0))link(P(i,j),P(i,j+1),1<<30);
				else link(P(i,j),P(i,j+1),(want[i-1]-j)*(want[i-1]-j));
			}
		}
		return maxflow();
	}
};
(i*9+1,0,0);
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
