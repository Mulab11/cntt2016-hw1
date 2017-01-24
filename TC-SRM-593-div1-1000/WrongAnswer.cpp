#define MOD 1000000007
class WolfDelaymasterHard{
public:
	char s[2000010];
	int t[2000010],f[2000010];
	int min(int a,int b){return a<b?a:b;}
	int countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd){
		for(int i=0;i<N;i++)s[i]='?';
		long long x=w0;
		for(int i=0;i<wlen;i++)s[x]='w',x=(x*wmul+wadd)%N;
		x=o0;
		for(int i=0;i<olen;i++)s[x]='o',x=(x*omul+oadd)%N;
		for(int i=t[N]=N;i--;)t[i]=s[i]=='o'?i:t[i+1];
		for(int i=N;i--;)if(t[i]>(i+N)/2)t[i]=(i+N)/2;
		f[N]=1;
		for(int l=N,r=N;r>=0;l=r=l-1){
			while(l&&s[l-1]!='w')--l;
			(f[r]+=f[r+2])%=MOD;
			for(int i=r-1;i>=l;i--)f[i]=(f[i]+f[i+2]*2ll-f[2*min(t[i],i+r>>1)-i+2]+MOD)%MOD;
			for(int i=l-1,rr;i>=0&&i>=2*l-r;i--)if((rr=min(t[i],i+r>>1))>=l)f[i]=(f[i]+f[2*l-i]*1ll-f[2*rr-i+2]+MOD)%MOD;
		}
		return (f[0]-f[2]+MOD)%MOD;
	}
};
1013,1009,1051},
				  G[26]={0,1,1008,374,469,802,375,935,762,922,432,122,160,124,904,642,179,81,448,749,637,949,209,586,648,644};
		p=P[N];g=G[N];
		for(int i=0;i<p;i++)sc[i]=0;
		for(int i=0;i<p;i++)s[i*i%p][sc[i*i%p]++]=i,i*N%p==1?iN=i:1,i*g%p==1?ig=i:1;
	}
	vector <int> getPattern(vector <int> amount){
		for(int i=0;i<(N=amount.size());i++)a[i]=amount[i];
		init();
		DFT(a,b);
		ans[0]=-1;
		dfs(0);
		vector<int>res;
		for(int i=0;i<N;i++){
			res.push_back(ans[i]);
			if(ans[i]==-1)break;
		}
		return res;
	}
};
;j++){
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
