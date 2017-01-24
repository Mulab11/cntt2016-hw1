#include <vector>
using namespace std;
class CentaurCompany{
public:
	struct edge{int to;edge*next;}E[80],*ne,*first[40];
	void link(int a,int b){*ne=(edge){b,first[a]};first[a]=ne++;}
	int siz[40]; // siz[i]:i子树大小
	double mem[40][2][80],*f[40][2],*g[2]; // f(i,j,k):i子树内满足i选择状态为j(j=0,1)且V-2E-2=k的点集个数/2^siz[i]
	void dfs(int i,int fa){
		siz[i]=1;
		for(int j=0;j<2;j++)
			for(int k=-2;k<1;k++)f[i][j][k]=0.5*(k==j-2);
		for(edge*e=first[i];e;e=e->next)if(e->to!=fa){
			dfs(e->to,i);
			for(int j=0;j<2;j++)
				for(int k=-siz[i]-siz[e->to]-2;k<siz[i]+siz[e->to];k++)g[j][k]=0;
			for(int j1=0;j1<2;j1++)
				for(int j2=0;j2<2;j2++)
					for(int k1=-siz[i]-2;k1<siz[i];k1++)if(f[i][j1][k1])
						for(int k2=-siz[e->to]-2;k2<siz[e->to];k2++)if(f[e->to][j2][k2])
							g[j1][k1+k2+2*(!j1||!j2)]+=f[i][j1][k1]*f[e->to][j2][k2];
			siz[i]+=siz[e->to];
			for(int j=0;j<2;j++)
				for(int k=-siz[i]-2;k<siz[i];k++)f[i][j][k]=g[j][k];
		}
	}
	double getvalue(vector <int> a, vector <int> b){
		int N=a.size()+1;ne=E;
		for(int i=1;i<=N;i++){
			first[i]=0;
			f[i][0]=mem[i][0]+40;f[i][1]=mem[i][1]+40;
		}
		g[0]=mem[0][0]+40;g[1]=mem[0][1]+40;
		for(int i=0;i<a.size();i++)link(a[i],b[i]),link(b[i],a[i]);
		dfs(1,0);
		double ans=0;
		for(int i=1;i<siz[1];i++)ans+=(f[1][0][i]+f[1][1][i])*i;
		return ans*2;
	}
};
��乘及逆元
		for(ll i=*fac=1;i<=K;i++)fac[i]=fac[i-1]*i%MOD;
		ifac[K]=inv(fac[K],MOD);
		for(ll i=K;i;i--)ifac[i-1]=ifac[i]*i%MOD;
		// 计算答案
		ll ans=0,ans2=0;
		for(ll d=P;d<=N;d*=P)(ans+=sum(d))%=MOD,(ans2+=sum2(d))%=Q;
		return(ans+MOD-ans2)*inv(Q,MOD)%MOD;
	}
};
[i])||!i&&c)continue;
			if(!t)select[id[i]]=1,stype[id[i]]=c^type[i];
			if(link(ex[i],ex[i]+1,c)&&link(ey[i],ey[i]+1,c)
				&&link(ex[i]+1,ey[i],c?0:(ex[i]^ey[i]^1)%2)&&dfs2(i+1))return 1; // 每条边内同类点必须偶数个 
			if(!t)select[id[i]]=0;undo(old);
		}
		return 0;
	}
	string getPossibility(vector <int> labels){
		for(int i=ecnt=top=opcnt=0;i<labels.size();i++) // 预处理边集
			if(labels[i]==-1)list[top++]=i;
			else for(int j=i+1;j<labels.size();j++)if(labels[i]==labels[j])ex[ecnt]=i,ey[ecnt++]=j;
		init(labels.size());
		for(int i=0;i<ecnt;i++)
			for(int j=i+1;j<ecnt;j++)if(cross(i,j)&&!link(i,j,1))return"IMPOSSIBLE"; // 输入的不合法则退出
		if(top<=12)return dfs1(0)?"POSSIBLE":"IMPOSSIBLE"; // 搜索1
		for(int j=0;j<ecnt;j++)id[j]=find_fa(j),type[j]=find_val(j),select[j]=0;
		init(labels.size());link(0,labels.size(),0);
		return dfs2(0)?"POSSIBLE":"IMPOSSIBLE"; // 搜索2
	}
};
1ll*P*(p-l)%MOD;
				}
			}
			ans=(ans+P)%MOD;
		}
		return ans; 
	}
};

			for(edge*e=first[i];e;e=e->next){
				if(siz[e->to]==n-k)dfs2(e->to,i,dep+1,ff*fv[e->to]%MOD);
			}
		}
		else for(edge*e=first[i];e;e=e->next)
			if(e->to!=fa)dfs2(e->to,i,dep+1,ff);
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
