#include <vector>
#include <algorithm>
using namespace std;
class BitwiseAnd{
public:
	vector<long long> lexSmallest(vector<long long> subset, int N){
		vector<long long>em;
		if(N>11)return em;
		int cnt[60]={0},belong[60];
		for(int i=0;i<subset.size();i++){
			for(int j=0;j<60;j++)if(subset[i]>>j&1)if(++cnt[j]>2)return em;else belong[j]=i;
			for(int j=i+1;j<subset.size();j++)if(!(subset[i]&subset[j]))return em;
		}
		for(int i=subset.size();i<N;i++){
			long long x=0,sel=0;
			int tot=N-i-1;
			for(int j=0;j<60;j++)if(cnt[j]<2){
				if(cnt[j]==1&&!(sel>>belong[j]&1))cnt[j]++,x|=1ll<<j,sel|=1<<belong[j];
				else if(!cnt[j]&&tot)cnt[j]++,belong[j]=i,x|=1ll<<j,tot--;
			}
			if(sel!=(1<<i)-1)return em;
			subset.push_back(x);
		}
		sort(subset.begin(),subset.end());
		return subset;
	}
};

		return subset;
	}
};
;
			int z=zcnt;
			prob[i]==1000?z--:p/=P[i];
			for(int l=0,r=0;l<n;prob[S[l]]==1000?z++:p*=P[S[l]],l++){
				if(r==l)prob[S[r]]==1000?z--:p/=P[S[r]],r=(r+1)%n;
				while(r!=l&&chk(S[l],S[r]))prob[S[r]]==1000?z--:p/=P[S[r]],r=(r+1)%n;
				if(!z)s+=5e-7*prob[i]*prob[S[l]]*p*(x[i]*y[S[l]]-y[i]*x[S[l]]);
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
