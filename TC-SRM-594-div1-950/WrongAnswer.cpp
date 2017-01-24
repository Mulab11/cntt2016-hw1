#include <cstdio>
class FoxAndAvatar{
public:
	int w,ans;
	int max(int a,int b){return a>b?a:b;}
	void DFS(int n,int x,int dep){
		if(dep>=ans)return;
		if(n==1){ans=dep;return;}
		if(dep+1>=ans)return;
		if(n<=w&&(x==1||x==n)||n>w&&n<2*w&&x==w||n%w==1&&x==n){ans=dep+1;return;}
		if(dep+2>=ans)return;
		int qn=n/w,rn=n%w,qx=(x-1)/w,rx=(x-1)%w;
		for(int i=x-1,j,k,a,b;i--;){
			j=(a=i/w+1)*(b=i%w+1);k=0;
			if(b<=rx)k=max(k,(qn-qx-1)*b-max(-b,-rn));
			if(a<=qx&&b<w-rx)k=max(k,(qn-qx)*b-max(-b,-max(rn-rx-1,0)));
			DFS(n-j-k,x-j,dep+1);
		}
		DFS(n-max(n-(qx+1)*w,(qn-qx)*(w-rx-1)+max(rn-rx-1,0)),x,dep+1);
	}
	int minimalSteps(int n, int width, int x){
		w=width;ans=4;DFS(n,x,0);return ans;
	}
};
0);return ans;
	}
};
mcpy(cur,first,sizeof(cur));
			for(int head=0,tail=Q[0]=D[1]=1;head<tail;head++)
				for(edge*e=first[Q[head]];e;e=e->next)
					if(e->rev->cap&&!D[e->to])D[Q[tail++]=e->to]=D[Q[head]]+1;
			if(!D[0])return f;
		}
	}
}solver;
class FoxAndGo3{
public:
	int maxEmptyCells(vector <string> board){
		int R=board.size(),C=board[0].length(),cnt=0,vx[4]={-1,0,0,1},vy[4]={0,-1,1,0};
		solver.init();
		for(int i=0;i<R;i++)for(int j=0;j<C;j++){
			if(board[i][j]=='.')solver.link(0,P(i,j),1),cnt++;
			else if(board[i][j]=='o'){
				solver.link(P(i,j),1,1);cnt++;
				for(int d=0,dx,dy;d<4;d++)if((dx=i+vx[d])>=0&&dx<R&&(dy=j+vy[d])>=0&&dy<C&&board[dx][dy]=='.')solver.link(P(dx,dy),P(i,j),1<<30);
			}
		}
		return cnt-solver.maxflow();
	}
};
}
		}
		return cnt-solver.maxflow();
	}
};
low();
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
