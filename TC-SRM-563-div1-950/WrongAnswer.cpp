// FST:ÅĞ¶Ïa,bÊôÓÚ²»Í¬×´Ì¬Ö»ÅĞÁËaÈÔÔÚÆåÅÌbÒÆ³öÆåÅÌ£¬Ã»ÅĞbÈÔÔÚÆåÅÌaÒÆ³öÆåÅÌ 
#include <vector>
#include <string>
#define MOD 1000000009
using namespace std;
class CoinsGame{
public:
	int R,C,tot,id[42][42],vx[4]={-1,0,0,1},vy[4]={0,-1,1,0},pow2[1610];
	vector<int>trans[1610][4];
	bool vis[1610][1610],del[1610];
	struct item{short a,b;}Q[1610*1610],*H,*T;
	int ways(vector <string> board){
		R=board.size();C=board[0].length();
		for(int x=0;x<R;x++)
			for(int y=0;y<C;y++)if(board[x][y]=='.')id[x][y]=++tot;
		for(int x=0;x<R;x++)
			for(int y=0,i;y<C;y++)if(i=id[x][y])
				for(int d=0,dx,dy;d<4;d++)trans[(dx=x+vx[d])>=0&&dx<R&&(dy=y+vy[d])>=0&&dy<C?id[dx][dy]?id[dx][dy]:i:0][d].push_back(i);
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
l ff){ // æ ‘å½¢DPæ±‚å‡ºgï¼Œffä¸ºiçš„ä¸Šæ–¹éƒ¨åˆ†éå†åºæ•°/(n-siz[i])!
		siz[i]=g[i][1][0]=1;
		ll tmp=ff;
		for(edge*e=first[i];e;e=e->next)if(e->to!=fa)(tmp*=f[e->to])%=MOD;
		for(edge*e=first[i];e;e=e->next)if(e->to!=fa){
			dfs1(e->to,i,tmp*fv[e->to]%MOD*inv[n-siz[e->to]]%MOD);
			// AåŒ…å«toï¼Œå°†g[to]æ–¹æ¡ˆæ•°è½¬ç§»ç»™g[i]
			for(int a1=1;a1<=siz[i];a1++)
				for(int a2=1;a2<=siz[e->to]&&a1+a2<=2*k-n;a2++)
					for(int b1=0;a1+b1<=siz[i]&&b1<=n-k;b1++)
						for(int b2=0;a2+b2<=siz[e->to]&&b2<=n-k;b2++)
							(h[a1+a2][b1+b2]+=g[i][a1][b1]*g[e->to][a2][b2])%=MOD;
			// Aä¸åŒ…å«toï¼Œå°†g[i]ä¹˜ä¸Šf[to]è½¬ç§»ç»™g[i]
			for(int a=1;a<=siz[i];a++)
				for(int b=0;a+b<=siz[i]&&b+siz[e->to]<=n-k;b++)
					(h[a][b+siz[e->to]]+=g[i][a][b]*f[e->to])%=MOD;
			for(int a=1;a<=siz[i]+siz[e->to]&&a<=2*k-n;a++)
				for(int b=0;a+b<=siz[i]+siz[e->to]&&b<=n-k;b++)
					((g[i][a][b]*=f[e->to])+=h[a][b])%=MOD,h[a][b]=0;
			siz[i]+=siz[e->to];
		}
		// æ›´æ–°ç­”æ¡ˆ
		(ans+=g[i][2*k-n][n-k]*ff)%=MOD;
		if(i&&siz[i]>=k)(ans+=g[i][2*k-n][siz[i]-k]*ff)%=MOD;
	}
	// å¯¹äº2k<=nçš„æƒ…å†µï¼Œæšä¸¾[0,k)[n-k,n)çš„è¿é€šå—æ›´æ–°ç­”æ¡ˆ
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
