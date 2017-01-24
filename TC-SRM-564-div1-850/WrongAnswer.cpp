#include <vector>
#define MOD 1000000007
using namespace std;
class DefectiveAddition{
public:
	int f[60][3];
	int count(vector <int> cards, int n){
		int m=cards.size(),x=0,ans=0;
		for(int i=0;i<m;i++)x^=++cards[i];
		for(int j=29;j>=0&&(x>>j+1)==(n>>j+1);j--){
			f[m][0]=f[m][1]=0;f[m][2]=1;
			for(int i=m-1;i>=0;i--){
				for(int k=0;k<3;k++)f[i][k]=(1ll*cards[i]%(1<<j)*f[i+1][k]+(k<2&&(cards[i]>>j&1)?(1ll<<j)*f[i+1][!k]:0))%MOD;
				if(cards[i]>>j&1)f[i][1]=(f[i][1]+f[i+1][2])%MOD;
			}
			ans=(ans+f[0][(x>>j&1)!=(n>>j&1)])%MOD;
		}
		return ans;
	}
};
eturn ans;
	}
};
 d=0,dx,dy;d<4;d++)trans[(dx=x+vx[d])>=0&&dx<R&&(dy=y+vy[d])>=0&&dy<C?id[dx][dy]?id[dx][dy]:i:0][d].push_back(i);
		for(int s=1;s<=tot;s++)
			for(int t=0;t<2;t++)if(!vis[t?s:0][t?0:s])
				for(*Q=(item){t?s:0,t?0:s},H=Q,T=Q+1;H<T;H++)
					for(int d=0;d<4;d++)
						for(int i=trans[H->a][d].size();i--;)
							for(int j=trans[H->b][d].size();j--;)
								if(!vis[T->a=trans[H->a][d][i]][T->b=trans[H->b][d][j]])vis[T->a][T->b]=1,T++;
		for(int i=*pow2=1;i<=tot;i++)pow2[i]=pow2[i-1]*2%MOD;
		int ans=pow2[tot]-1;
		for(int i=1;i<=tot;i++)if(!del[i]){
			int siz=0;
			for(int j=1;j<=tot;j++)!vis[i][j]?siz++,del[j]=1:1;
			ans=(ans+MOD-pow2[siz]+1)%MOD;
		}
		return ans;
	}
};
%MOD;
		}
		return ans;
	}
};
l ff){ // 树形DP求出g，ff为i的上方部分遍历序数/(n-siz[i])!
		siz[i]=g[i][1][0]=1;
		ll tmp=ff;
		for(edge*e=first[i];e;e=e->next)if(e->to!=fa)(tmp*=f[e->to])%=MOD;
		for(edge*e=first[i];e;e=e->next)if(e->to!=fa){
			dfs1(e->to,i,tmp*fv[e->to]%MOD*inv[n-siz[e->to]]%MOD);
			// A包含to，将g[to]方案数转移给g[i]
			for(int a1=1;a1<=siz[i];a1++)
				for(int a2=1;a2<=siz[e->to]&&a1+a2<=2*k-n;a2++)
					for(int b1=0;a1+b1<=siz[i]&&b1<=n-k;b1++)
						for(int b2=0;a2+b2<=siz[e->to]&&b2<=n-k;b2++)
							(h[a1+a2][b1+b2]+=g[i][a1][b1]*g[e->to][a2][b2])%=MOD;
			// A不包含to，将g[i]乘上f[to]转移给g[i]
			for(int a=1;a<=siz[i];a++)
				for(int b=0;a+b<=siz[i]&&b+siz[e->to]<=n-k;b++)
					(h[a][b+siz[e->to]]+=g[i][a][b]*f[e->to])%=MOD;
			for(int a=1;a<=siz[i]+siz[e->to]&&a<=2*k-n;a++)
				for(int b=0;a+b<=siz[i]+siz[e->to]&&b<=n-k;b++)
					((g[i][a][b]*=f[e->to])+=h[a][b])%=MOD,h[a][b]=0;
			siz[i]+=siz[e->to];
		}
		// 更新答案
		(ans+=g[i][2*k-n][n-k]*ff)%=MOD;
		if(i&&siz[i]>=k)(ans+=g[i][2*k-n][siz[i]-k]*ff)%=MOD;
	}
	// 对于2k<=n的情况，枚举[0,k)[n-k,n)的连通块更新答案
	void dfs2(int i,int fa,int dep,ll ff){
		if(siz[i]<k)return;
		if(dep==n-2*k+1){
			if(siz[i]>k)return;
			(ans+=ff*f[i])%=MOD;
		}
		else if(fa==-1){
			for(edge*e=first[i];e;e=e->next)(ff*=f[e->to])%=MOD;
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
