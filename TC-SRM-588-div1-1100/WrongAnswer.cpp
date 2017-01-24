// Unsolved:没有推出结论，看了题解
#include <vector>
#include <string>
#define fe(x0,y0) for(int d=0,dx,dy;d<4;d++)if((dx=x0+vx[d])>=0&&dx<R&&(dy=y0+vy[d])>=0&&dy<C&&field[dx][dy]!='#')
#define fc(x0,y0) fe(x0,y0)if((t?DB:DA)[dx][dy]>(t?DB:DA)[x0][y0])
using namespace std;
class GameInDarknessDiv1{
public:
	int DA[55][55],DB[55][55],up[55][55],down[55][55],se[55][55],vis[55][55],vx[4]={-1,0,0,1},vy[4]={0,-1,1,0};
	struct item{int x,y;}Q[2555],*H,*T;
	int max(int a,int b){return a>b?a:b;}
	void cmax(int&a,int&b,int c){c>a?b=a,a=c:c>b?b=c:1;}
	string check(vector <string> field){
		int R=field.size(),C=field[0].length(),xA,yA,xB,yB;
		for(int x=0;x<R;x++)
			for(int y=0;y<C;y++)field[x][y]=='A'?xA=x,yA=y:field[x][y]=='B'?xB=x,yB=y:1;
		for(int t=0;t<2;t++){
			for(*Q=(item){t?xB:xA,t?yB:yA},H=Q,T=Q+1,vis[Q->x][Q->y]=!t;H<T;up[H->x][H->y]=down[H->x][H->y]=0,H++)
				fe(H->x,H->y)if(vis[dx][dy]==t)vis[T->x=dx][T->y=dy]=!t,(t?DB:DA)[dx][dy]=(t?DB:DA)[H->x][H->y]+1,T++;
			while(H-->Q)fc(H->x,H->y)cmax(down[H->x][H->y],se[H->x][H->y],down[dx][dy]+1);
			for(H=Q;H<T;H++)fc(H->x,H->y)up[dx][dy]=max(up[H->x][H->y],down[H->x][H->y]==down[dx][dy]+1?se[H->x][H->y]:down[H->x][H->y])+1;
		}
		for(int x=0,t=1;x<R;x++)for(int y=0;y<C;y++)if(DA[x][y]-DB[x][y]>1){
			int cnt=up[x][y]>2;
			fc(x,y)if(down[dx][dy]>1)cnt++;
			if(cnt>2)return "Bob wins";
		}
		return "Alice wins";
	}
};
return "Alice wins";
	}
};
r[i]*(long long)(l[i]-p);
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
