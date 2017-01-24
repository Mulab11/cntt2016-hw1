#include <vector>
using namespace std;
class BallsSeparating{
public:
	void cmin(int&a,int b){b<a?a=b:1;}
	int minOperations(vector <int> red, vector <int> green, vector <int> blue){
		if(red.size()<3)return -1;
		int f[2][8];
		for(int i=0;i<8;i++)f[0][i]=i?1<<30:0,f[1][i]=1<<30;
		for(int i=0;i<red.size();i++){
			int a[3]={green[i]+blue[i],blue[i]+red[i],red[i]+green[i]};
			for(int j=0;j<8;j++)for(int k=0;k<3;k++)cmin(f[1][j|1<<k],f[0][j]+a[k]);
			for(int j=0;j<8;j++)f[0][j]=f[1][j],f[1][j]=1<<30;
		}
		return f[0][7];
	}
};
int j=i+1;j<=m&&j<N;j++)if(h[j]>=h[i]){
				int l=pos[j]-h[j]+h[i],r=pos[j]+h[j]-h[i]+1;
				cmax(l,0);cmin(r,W);a[l]++;a[r]--;
			}
			for(int j=0;j<W;a[j+1]+=a[j],a[j++]=0)if(a[j])s++,p=j;
			if(s)s=1ll*s*dfs(i-1,m)%MOD; // 搜索剩下部分
			if(m==i+1)f[m][pos[m]]=s+1;
			return s;
		}
		int hl=0,hll=0,hr=0,hrr=0; // hl,hll,hr,hrr分别为L[i],L[i]-1,R[i],R[i]+1当前高度
		for(int j=i+1;j<=m&&j<N;j++){
			cmax(hl,h[j]-diff(L[i],pos[j]));
			cmax(hll,h[j]-diff(L[i]-1,pos[j]));
			cmax(hr,h[j]-diff(R[i],pos[j]));
			cmax(hrr,h[j]-diff(R[i]+1,pos[j]));
		}
		int pl=L[i],pr=R[i];
		cmax(pl,hr-h[i]+R[i]+1);
		cmin(pr,h[i]+L[i]-hl-1);
		if(L[i])cmax(pl,h[i]+L[i]-hll-1);
		if(R[i]<W-1)cmin(pr,hrr-h[i]+R[i]+1);
		for(p=pl;p<=pr;p++)s=(s+dfs(i-1,!L[i]&&R[i]==W-1?i:m))%MOD;
		if(m==i+1)f[m][pos[m]]=s+1;
		return s;
	}
	int countPlacements(vector <int> heights, vector <string> visibility){
		N=heights.size();W=visibility[0].length();
		for(int i=0;i<N;i++){
			h[i]=heights[i];
			for(L[i]=0;L[i]<W&&visibility[i][L[i]]=='-';L[i]++);
			for(R[i]=W-1;R[i]>=0&&visibility[i][R[i]]=='-';R[i]--);
		}
		return dfs(N-1,99);
	}
};
t[i][j]=1:1;
		int sum=cnt[n-1][0];
		for(int i=1;i<n;i++)sum+=cnt[i-1][i];
		if(sum<x.size())return 0; // 判掉无解的情况
		// DP
		for(int l=n-2;l>=0;l--){
			for(int r=l+1;r<n;r++){
				// 1:l~r只有一条边，要求k=0且l l+1 r-1 r多边形内没有点
				f[l][r][0]=l+1==r||!poly(l,l+1,r-1,r)?l+1<r-1?g[l+1][r-1]:1:0;
				f[l][r][1]=0;
				// 2:l~r有多条边，枚举l的下一个点i，要求l l+1 i-1 i多边形内没有点
				for(int i=l+1;i<r;i++)if(!cut[l][i]&&(l+1==i||!poly(l,l+1,i-1,i))){
					long long t=l+1<i-1?g[l+1][i-1]:1;
					f[l][r][0]=(f[l][r][0]+t*f[i][r][0])%MOD;
					f[l][r][1]=(f[l][r][1]+t*f[i][r][!poly(l,i,r)])%MOD;
				}
				g[l][r]=l+1<r?poly(l,l+1,r)?0:g[l+1][r]:1;
				for(int i=l+1;i<=r;i++){
					if(!cut[l][i]&&(i==r||!poly(l,i,i+1,r)))g[l][r]=(g[l][r]+1ll*f[l][i][1]*(i+1<r?g[i+1][r]:1))%MOD;
				}
			}
		}
		return g[0][n-1];
	}
};
};
=1ll*P*(p-l)%MOD;
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
