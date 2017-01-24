#include <vector>
#include <string>
using namespace std;
class ConvexPolygonGame{
public:
	int ymin[200010],ymax[200010],xs[200010],ys[200010];
	int fl(long long a,long long b){return a>0||a%b==0?a/b:a/b-1;}
	int ce(long long a,long long b){return a<0||a%b==0?a/b:a/b+1;}
	string winner(vector <int> X, vector <int> Y){
		int cnt=0;
		for(int i=0;i<=200000;i++)ymax[i]=-(ymin[i]=233333);
		for(int i=0;i<X.size();i++)X[i]+=100000,Y[i]+=100000;
		for(int i=0,j;j=(i+1)%X.size(),i<X.size();i++){
			if(X[i]>X[j]){
				ymax[X[i]]=Y[i]-1;ymax[X[j]]=Y[j]-1;
				for(int x=X[j]+1;x<X[i];x++)ymax[x]=Y[j]+fl((x-X[j])*1ll*(Y[i]-Y[j]),X[i]-X[j]);
			}
			else if(X[i]<X[j]){
				ymin[X[i]]=Y[i]+1;ymin[X[j]]=Y[j]+1;
				for(int x=X[i]+1;x<X[j];x++)ymin[x]=Y[i]+ce((x-X[i])*1ll*(Y[j]-Y[i]),X[j]-X[i]);
			}
		}
		for(int i=0;i<=200000&&cnt<200002;i++){
			for(int j=ymin[i];j<=ymax[i]&&cnt<200002;j++)xs[cnt]=i,ys[cnt++]=j;
		}
		if(cnt<3)return"Petya";
		if(cnt>200001)return"Masha";
		for(int i=2;i<cnt;i++)if((ys[i]-ys[0])*1ll*(xs[1]-xs[0])!=(xs[i]-xs[0])*1ll*(ys[1]-ys[0]))return"Masha";
		return"Petya";
	}
};
a";
		return"Petya";
	}
};
	}
		}
		return s;
	}
};
]]);
			}
		}
		return s;
	}
};
k(0,P(i,j),1),cnt++;
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
