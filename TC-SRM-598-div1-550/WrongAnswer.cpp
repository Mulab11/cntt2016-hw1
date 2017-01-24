// WAonSystemTest
#include <string>
class FoxAndFencing{
public:
	std::string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d){
		// 1的必胜区间为[0,mov1+rng1]
		// 2的必胜区间为[0,mov2+rng2]
		if(d<=mov1+rng1)return"Ciel";
		// (1)对任意x>mov1+rng1，都可将x移到2的必胜区间外（显然包含了mov1+rng1>=mov2+rng2的所有情况）
		if(mov1+rng1+1+mov1>mov2+rng2){
			// 1.1 如果d能移到使对方只能移进1的必胜区间的位置（前提是mov1>mov2），1必胜
			if(mov1>mov2&&mov2+rng2+1+mov2<=mov1+rng1)return"Ciel";
			// 1.2 否则平局
			return"Draw";
		}
		// (2)如果d移不出2的必胜区间，1必败
		if(d+mov1<=mov2+rng2)return"Liss";
		// (3)如果d能移出区间，但会被对方移到d更小的位置，1必败
		if(mov2>mov1)return"Liss";
		// (4)否则平局
		return"Draw";
	}
};
return"Draw";
	}
};
]=inv(fac[M],MOD);
		for(int i=M-1;i>=0;i--)ifac[i]=ifac[i+1]*(i+1)%MOD;
		return solve(M,M-R,M-G,M-B);
	}
};
(M,M-R,M-G,M-B);
	}
};
,ys[cnt++]=j;
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
