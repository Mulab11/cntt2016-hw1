#include <vector>
#include <string>
using namespace std;
class LittleElephantAndRGB{
public:
	int l[2510],r[2510],lm[2510],rm[2510],cnt[2510],f[2510][2510];
	long long getNumber(vector <string> list, int minGreen){
		string S;
		for(int i=0;i<list.size();i++)
			for(int j=0;j<list[i].length();j++)S.push_back(list[i][j]);
		int n=S.length();
		l[0]=0;lm[0]=-1;r[n]=n;rm[n]=n+1;cnt[n]=0;
		for(int i=1;i<=n;i++)l[i]=S[i-1]=='G'?l[i-1]:i,lm[i]=i-l[i]>=minGreen?i-minGreen:lm[i-1];
		for(int i=n;i--;)r[i]=S[i]=='G'?r[i+1]:i,rm[i]=r[i]-i>=minGreen?i+minGreen:rm[i+1],cnt[i]=cnt[i+1]+n-rm[i]+1;
		for(int i=n;i>=0;i--){
			for(int j=0;j<=n;j++)f[i][j]=i==n?0:f[i+1][j];
			for(int j=i+1;j<rm[i];j++)f[i][(r[i]>j?j:r[i])-i]++;
		}
		for(int j=n;j--;)
			for(int i=0;i<=n;i++)f[i][j]+=f[i][j+1];
		long long ans=0;
		for(int i=0;i<n;i++)
			for(int j=i+1,d;j<=n;j++)ans+=j>=rm[i]?(n-j)*(n-j+1)/2:cnt[j]+f[j][(d=minGreen-j+(l[j]>i?l[j]:i))<0?0:d];
		return ans;
	}
};
;
		return ans;
	}
};
EmptyCells(vector <string> board){
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
