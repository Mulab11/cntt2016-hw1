#include <vector>
#include <string>
using namespace std;
class FlippingBitsDiv1{
public:
	int min(int a,int b){return a<b?a:b;}
	int getmin(vector <string> S, int M){
		string s;
		for(int i=0;i<S.size();i++)s+=S[i];
		int n=s.length()/M,ans=1<<30;
		if(M<=17)for(int K=0;K<(1<<M);K++){
			int a0=0,a1=0,b,p;
			for(int i=0;i<n;i++){
				for(int j=p=0;j<M;j++)p+=(s[i*M+j]-'0'!=(K>>j&1));
				b=p+min(a0,a1+1);a1=M-p+min(a0+1,a1);a0=b;
			}
			for(int j=p=0;n*M+j<s.length();j++)p+=(s[n*M+j]-'0'!=(K>>j&1));
			ans=min(ans,min(a0,a1+1)+p);
		}
		else for(int K=0;K<(1<<n);K++){
			int a=0;
			for(int i=0;i<n;i++)a+=K>>i&1;
			for(int i=0;i<M;i++){
				int a0=0,a1=0,t=0;
				for(int j=n;j>=0;j--)
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
