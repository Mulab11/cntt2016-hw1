#include <vector>
using namespace std;
class XorCards{
public:
	int n,k[55];long long a[55];
	long long dfs(int i,long long x,long long l){
		if(i==n||!k[i])return x<=l?1ll<<n-i:0;
		if((x>>k[i])<(l>>k[i]))return 1ll<<n-i;
		if((x>>k[i])>(l>>k[i]))return 0;
		return dfs(i+1,x,l)+dfs(i+1,x^a[i],l);
	}
	long long numberOfWays(vector<long long> number, long long limit){
		for(int i=n=number.size();i--;)a[i]=number[i];
		for(int i=k[n]=0;i<n;i++){
			for(int j=i;j<n;j++)if(a[j]>a[i]){long long t=a[j];a[j]=a[i];a[i]=t;}
			for(int j=i+1;j<n;j++)if((a[j]^a[i])<a[j])a[j]^=a[i];
		}
		for(int i=n;i--;)for(k[i]=k[i+1];a[i]>>k[i];k[i]++);
		return dfs(0,0,limit);
	}
};
0,0,limit);
	}
};
>=0;j--)
					if(j*M+i<s.length())(t=K>>j&1?!t:t)==s[j*M+i]-'0'?++a0:++a1;
				a+=min(a0,a1);
			}
			ans=min(ans,a);
		}
		return ans;
	}
};
a);
		}
		return ans;
	}
};
=D[Q[head]]+1;
			if(!D[0])return f;
		}
	}
}solver;
class GearsDiv1{
public:
	int getmin(string color, vector <string> graph){
		int n=color.size(),cnt[3]={0};
		for(int i=0;i<n;i++)++cnt[color[i]=color[i]=='R'?0:color[i]=='G'?1:2];
		int ans=n,tmp;
		for(int a=0,b=1;a<3;b=(++a+1)%3){
			solver.init();
			for(int i=0,x=2;i<n;i++)if(color[i]==a){
				for(int j=0,y=2+cnt[a];j<n;j++)if(color[j]==b)graph[i][j]=='Y'?solver.link(x,y,1<<30),1:1,y++;
				solver.link(0,x++,1);
			}
			for(int i=0,x=2+cnt[a];i<n;i++)if(color[i]==b)solver.link(x++,1,1);
			if((tmp=solver.maxflow())<ans)ans=tmp;
		}
		return ans;
	}
};
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
